#pragma once

#include "gameng/log.hpp"

#include <stdint.h>

namespace gameng
{

enum class ShaderDataType 
{
  None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};
static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
  switch(type)
  {
    case ShaderDataType::Float:  return sizeof(float);
    case ShaderDataType::Float2: return sizeof(float)*2;
    case ShaderDataType::Float3: return sizeof(float)*3;
    case ShaderDataType::Float4: return sizeof(float)*4;
    case ShaderDataType::Mat3:   return sizeof(float)*3*3;
    case ShaderDataType::Mat4:   return sizeof(float)*4*4;
    case ShaderDataType::Int:    return sizeof(int);
    case ShaderDataType::Int2:   return sizeof(int)*2;
    case ShaderDataType::Int3:   return sizeof(int)*3;
    case ShaderDataType::Int4:   return sizeof(int)*4;
    case ShaderDataType::Bool:   return 1;
    default: GAMENG_CORE_ERR("Unknown shader data type");
  }

  return 0;
}

struct BufferElement
{
  std::string name;
  ShaderDataType type;
  uint32_t offset;
  uint32_t size;
  uint32_t count;
  bool normalized;

  BufferElement(){}
  BufferElement( ShaderDataType type, const std::string& name, bool normalized = false)
  : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) 
  {

  }
  
  uint32_t GetComponentCount() const
  {
    switch(type)
    {
      case ShaderDataType::Float:   return 1;
      case ShaderDataType::Float2:  return 2;
      case ShaderDataType::Float3:  return 3;
      case ShaderDataType::Float4:  return 4;
      case ShaderDataType::Int:   return 1;
      case ShaderDataType::Int2:  return 2;
      case ShaderDataType::Int3:  return 3;
      case ShaderDataType::Int4:  return 4;
      case ShaderDataType::Bool:  return 1;
      case ShaderDataType::Mat3:  return 3*3;
      case ShaderDataType::Mat4:  return 4*4;
    }
    GAMENG_CORE_ERR("Wrong element count");
    return 0;
  }
};

class BufferLayout
{
public:
  BufferLayout(){}
  BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements) 
  {
    CalculateOffsetAndStride();
  }
  inline const std::vector<BufferElement>& GetElements() const {return m_elements;}
  std::vector<BufferElement>::iterator begin() {return m_elements.begin();}
  std::vector<BufferElement>::iterator end() {return m_elements.end();}
  std::vector<BufferElement>::const_iterator begin() const {return m_elements.begin();}
  std::vector<BufferElement>::const_iterator end() const {return m_elements.end();}
  inline const uint32_t GetStride() const {return m_stride;}
private:
  void CalculateOffsetAndStride()
  {
    uint32_t offset = 0;
    m_stride = 0;
    for(auto& element : m_elements)
    {
      element.offset = offset;
      offset += element.size;
      m_stride += element.size;
    }
  }
private:
  std::vector<BufferElement> m_elements;
  uint32_t m_stride = 0;
};

class VertexBuffer
{
public:
  ~VertexBuffer(){}
  
  virtual void Bind() const {}
  virtual void UnBind() const {};
  virtual void SetLayout(const BufferLayout& layout) = 0;
  virtual const BufferLayout& GetLayout() const = 0;
  static VertexBuffer* Create(float* vertices, uint32_t size);
};

class IndexBuffer
{
public:
  ~IndexBuffer(){}
  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;

  virtual uint32_t GetCount() const  = 0;

  static IndexBuffer* Create(uint32_t* indices, uint32_t size);
};

} // namespace gameng
