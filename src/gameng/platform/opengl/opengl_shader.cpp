#include "gameng/platform/opengl/opengl_shader.hpp"
#include "gameng/log.hpp"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

namespace gameng
{
OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
{
  // Create an empty vertex shader handle
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Send the vertex shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  const char *source = (const GLchar *)vertexSource.c_str();
  glShaderSource(vertexShader, 1, &source, 0);

  // Compile the vertex shader
  glCompileShader(vertexShader);

  GLint isCompiled = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE)
  {
  	GLint maxLength = 0;
  	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

  	// The maxLength includes the NULL character
  	std::vector<GLchar> infoLog(maxLength);
  	glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
  
  	// We don't need the shader anymore.
  	glDeleteShader(vertexShader);

  	// Use the infoLog as you see fit.
    GAMENG_CORE_ERR("Vertex shader compilation failed!");
    GAMENG_CORE_ERR("{0}", infoLog.data()); 
  	// In this simple program, we'll just leave
  	return;
  }

  // Create an empty fragment shader handle
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Send the fragment shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  source = (const GLchar *)fragmentSource.c_str();
  glShaderSource(fragmentShader, 1, &source, 0);

  // Compile the fragment shader
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
  	GLint maxLength = 0;
  	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

  	// The maxLength includes the NULL character
  	std::vector<GLchar> infoLog(maxLength);
  	glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
  
  	// We don't need the shader anymore.
  	glDeleteShader(fragmentShader);
  	// Either of them. Don't leak shaders.
  	glDeleteShader(vertexShader);

  	// Use the infoLog as you see fit.
    GAMENG_CORE_ERR("Fragment shader compilation failed!");
    GAMENG_CORE_ERR("{0}", infoLog.data()); 
     
  	// In this simple program, we'll just leave
  	return;
  }

  // Vertex and fragment shaders are successfully compiled.
  // Now time to link them together into a program.
  // Get a program object.
  m_rendererId = glCreateProgram();

  // Attach our shaders to our program
  glAttachShader(m_rendererId, vertexShader);
  glAttachShader(m_rendererId, fragmentShader);

  // Link our m_rendererId
  glLinkProgram(m_rendererId);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE)
  {
  	GLint maxLength = 0;
  	glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength);

  	// The maxLength includes the NULL character
  	std::vector<GLchar> infoLog(maxLength);
  	glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]);
  
  	// We don't need the program anymore.
  	glDeleteProgram(m_rendererId);
  	// Don't leak shaders either.
  	glDeleteShader(vertexShader);
  	glDeleteShader(fragmentShader);

  	// Use the infoLog as you see fit.
    GAMENG_CORE_ERR("Shadre link failed!");
    GAMENG_CORE_ERR("{0}", infoLog.data()); 
  
  	// In this simple program, we'll just leave
  	return;
}

// Always detach shaders after a successful link.
glDetachShader(m_rendererId, vertexShader);
glDetachShader(m_rendererId, fragmentShader);  
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
