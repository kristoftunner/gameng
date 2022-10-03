#include "gameng/platform/opengl/opengl_shader.hpp"
#include "gameng/log.hpp"
#include "gameng/core/filesystem.hpp"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <array>
#include <fstream>
#include <iostream>

namespace gameng
{

static GLenum ShaderTypeFromString(const std::string& type)
{
  if(type == "vertex")
    return GL_VERTEX_SHADER;
  else if(type == "fragment" || type == "pixel")
    return GL_FRAGMENT_SHADER;

  GAMENG_CORE_ERR("Unknown Shader type:{0}", type);
  return 0;
}

std::string OpenGLShader::ReadFile(const std::string& filepath)
{
  FileSystem& s = FileSystem::GetInstance();
  const std::string path = s.GetAbsolutePath(filepath);
  std::string result;
  std::ifstream in;
  in.open(path, std::ios::in);
  if(in.is_open())
  {
    in.seekg(0, std::ios::end);
    result.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&result[0], result.size());
    in.close();
  }
  else
  {
    GAMENG_CORE_ERR("Could not open file:'{0}'",filepath);
  }
  return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& stringSource)
{
  std::unordered_map<GLenum, std::string> shaderSources;
  const char* typeToken = "#type";
  size_t typeTokenLength = strlen(typeToken);
  size_t pos = stringSource.find(typeToken, 0);
  while(pos != std::string::npos)
  {
    size_t eol = stringSource.find_first_of("\r\n",pos);
    if(eol == std::string::npos)
      GAMENG_CORE_ERR("GLSL syntax error");
    size_t begin = pos + typeTokenLength + 1;
    std::string type = stringSource.substr(begin, eol - begin);
    if((type == "vertex") || (type == "fragment") || (type == "pixel"))
    {
      size_t nextLinePos = stringSource.find_first_not_of("\r\n", eol);
      pos = stringSource.find(typeToken, nextLinePos);
      shaderSources[ShaderTypeFromString(type)] = stringSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? stringSource.size() - 1 : nextLinePos));
    }
    else
      GAMENG_CORE_ERR("GLSL syntax error");
  }

  return shaderSources; 
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
  GLuint program = glCreateProgram();
  std::array<GLenum, 2> glShaderIds;
  int shaderIdIndex = 0;
  for(auto& kv : shaderSources)
  {
    GLenum type = kv.first;
    const std::string& source = kv.second;
    // Create an empty vertex shader handle
    GLuint shader = glCreateShader(type);
    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const char *sourceCStr = (const GLchar *)source.c_str();
    glShaderSource(shader, 1, &sourceCStr, 0);

    // Compile the vertex shader
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
    	GLint maxLength = 0;
    	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    	std::vector<GLchar> infoLog(maxLength);
    	glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
  
    	glDeleteShader(shader);

      GAMENG_CORE_ERR("Shader compilation failed!");
      GAMENG_CORE_ERR("{0}", infoLog.data()); 
    	return;
    }
    
    glAttachShader(program, shader);
    glShaderIds[shaderIdIndex++] = shader;
  }

  glLinkProgram(program);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE)
  {
  	GLint maxLength = 0;
  	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

  	// The maxLength includes the NULL character
  	std::vector<GLchar> infoLog(maxLength);
  	glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
  
  	// We don't need the program anymore.
  	glDeleteProgram(program);
  	// Don't leak shaders either.
    for(auto id : glShaderIds)
    {
  	  glDeleteShader(id);
    }

  	// Use the infoLog as you see fit.
    GAMENG_CORE_ERR("Shadre link failed!");
    GAMENG_CORE_ERR("{0}", infoLog.data()); 
  
  	// In this simple program, we'll just leave
  	return;
  }

  // Always detach shaders after a successful link.
  for(auto id : glShaderIds)
  {
    glDetachShader(m_rendererId, id);
  }
  
  m_rendererId = program;
}

OpenGLShader::OpenGLShader(const std::string& filepath)
{
  std::string source = ReadFile(filepath);
  auto shaderSources = PreProcess(source);
  Compile(shaderSources);

  // assets/shaders/texture.glsl
  auto lastSlash = filepath.find_last_of("/\\");
  lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
  auto lastDot = filepath.rfind(".");
  auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
  m_name = filepath.substr(lastSlash, count);
}

OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
  : m_name(name)
{
  std::unordered_map<GLenum, std::string> sources;
  sources[GL_FRAGMENT_SHADER] = fragmentSource;
  sources[GL_VERTEX_SHADER] = vertexSource;
  Compile(sources);
}

OpenGLShader::~OpenGLShader()
{
  glDeleteProgram(m_rendererId);
}

void OpenGLShader::Bind() const
{
  glUseProgram(m_rendererId);
}

void OpenGLShader::UnBind() const
{
  glUseProgram(0);
}


void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
{
  int location = glGetUniformLocation(m_rendererId, name.c_str());
  glUniform1f(location, value);
}

void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
{
  int location = glGetUniformLocation(m_rendererId, name.c_str());
  glUniform2f(location, values.x, values.y);
}

void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
{
  int location = glGetUniformLocation(m_rendererId, name.c_str());
  glUniform3f(location, values.x, values.y, values.z);
}

void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
{
  int location = glGetUniformLocation(m_rendererId, name.c_str());
  glUniform4f(location, values.x, values.y, values.z, values.w);
}
void OpenGLShader::UploadUniformInt(const std::string& name, int value)
{
  int location = glGetUniformLocation(m_rendererId, name.c_str());
  glUniform1i(location, value);
}

void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
{
  int location = glGetUniformLocation(m_rendererId, name.c_str());
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
  int location = glGetUniformLocation(m_rendererId, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
}// namsepace gameng
