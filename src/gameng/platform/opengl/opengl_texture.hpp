#pragma once

#include "gameng/renderer/texture.hpp"

namespace gameng
{

class OpenGLTexture2D : public Texture2D
{
public:
  OpenGLTexture2D(const std::string& path);
  virtual ~OpenGLTexture2D();
  virtual uint32_t GetWidth() const override { return m_width; }
  virtual uint32_t GetHeigth() const override { return m_heigth; } 
  void Bind(uint32_t slot) const override;

private:
  uint32_t m_rendererId;
  std::string m_path;
  uint32_t m_width;
  uint32_t m_heigth;
};

} // namespace gameng
