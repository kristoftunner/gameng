#pragma once

#include <stdint.h>

#include "gameng/core.hpp"

namespace gameng
{

class Texture
{
public:
  virtual ~Texture() = default;
  virtual uint32_t GetWidth() const = 0;
  virtual uint32_t GetHeigth() const = 0;
  
  virtual void Bind(uint32_t slot) const = 0;
};

class Texture2D : public Texture
{
public:
  virtual ~Texture2D() = default; 
  static Ref<Texture2D> Create(const std::string& path);
};

} // namespace gameng
