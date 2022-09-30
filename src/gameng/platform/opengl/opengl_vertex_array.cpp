#include "gameng/platform/opengl/opengl_vertex_array.hpp"

#include "glad/glad.h"

namespace gameng
{
  static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
  {
    switch(type)
    {
      case ShaderDataType::Float:   return GL_FLOAT; 
      case ShaderDataType::Float2:return GL_FLOAT; 
      case ShaderDataType::Float3:return GL_FLOAT; 
      case ShaderDataType::Float4:return GL_FLOAT; 
      case ShaderDataType::Int:     return GL_INT; 
      case ShaderDataType::Int2:return GL_INT; 
      case ShaderDataType::Int3:return GL_INT; 
      case ShaderDataType::Int4:return GL_INT; 
      case ShaderDataType::Mat3:return GL_FLOAT; 
      case ShaderDataType::Mat4:return GL_FLOAT; 
      case ShaderDataType::Bool:return GL_BOOL; 
    }

    GAMENG_CORE_ERR("Unknown ShaderDataType");
    return 0;
  }

  OpenGLVertexArray::OpenGLVertexArray()
  {
    glCreateVertexArrays(1, &m_rendererId);    
  }

  void OpenGLVertexArray::Bind() const
  {
    glBindVertexArray(m_rendererId);
  }

  void OpenGLVertexArray::UnBind() const
  {
    glBindVertexArray(0);
  } 

  void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) 
  {
    glBindVertexArray(m_rendererId);
    vertexBuffer->Bind();
    
    if(vertexBuffer->GetLayout().GetElements().size() == 0)
    {
      GAMENG_CORE_ERR("Empty vertex buffer layout");
      return;
    }

    uint32_t index = 0;
    const auto& layout = vertexBuffer->GetLayout();
    for(const auto& element : vertexBuffer->GetLayout())
    {
      glEnableVertexAttribArray(index);
      glVertexAttribPointer(index, 
        element.GetComponentCount(), 
        ShaderDataTypeToOpenGLBaseType(element.type), 
        element.normalized ? GL_TRUE : GL_FALSE, 
        layout.GetStride(), 
        (const void*)element.offset);
      index++;
    }

    m_vertexBuffers.push_back(vertexBuffer);
  } 

  void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer)
  {
    glBindVertexArray(m_rendererId);
    indexBuffer->Bind();

    m_indexBuffer = indexBuffer;
  } 
  
} // namespace gameng
