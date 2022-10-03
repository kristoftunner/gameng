#include "opengl_texture.hpp"
#include "gameng/log.hpp"
#include "gameng/core/filesystem.hpp"

#include "glad/glad.h"
#include "stb_image.h"

namespace gameng
{
  OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
   : m_path(path)
  {
    int width, heigth, channels;
    stbi_set_flip_vertically_on_load(1);
    const std::string absouletPath = FileSystem::GetInstance().GetAbsolutePath(path);
    stbi_uc* data = stbi_load(absouletPath.c_str(), &width, &heigth, &channels, 0);
    if(data == nullptr)
    {
      GAMENG_CORE_ERR("Unable to load image");
      return;
    }
    m_width = width;
    m_heigth = heigth;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererId);
    
    GLenum internalFormat = 0, dataFormat = 0;
    if(channels == 4)
    {
      internalFormat = GL_RGBA8;
      dataFormat = GL_RGBA;
    }
    else if(channels ==3)
    {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
    }
    else
    {
      GAMENG_CORE_ERR("Bad texture data format");
    }

    glTextureStorage2D(m_rendererId, 1, internalFormat, m_width, m_heigth);

    glTextureParameteri(m_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
    glTextureSubImage2D(m_rendererId, 0, 0, 0, m_width, m_heigth, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }

  OpenGLTexture2D::~OpenGLTexture2D()
  {
    glDeleteTextures(1, &m_rendererId);
  }

  void OpenGLTexture2D::Bind(uint32_t slot) const
  {
    glBindTextureUnit(slot, m_rendererId);
  } 
  
} // namespace gameng
