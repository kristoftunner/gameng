#include "gameng.hpp"
#include <iostream>
#include "imgui.h"
class ExampleLayer : public gameng::Layer
{
public:
  ExampleLayer() : Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_cameraPosition(0.0f)
  {
    m_vertexArray.reset(gameng::VertexArray::Create());
  
    float vertices[3*7] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
      0.0f, 0.5f, 0.0f,1.0f, 0.0f, 0.0f, 1.0f 
    };

    std::shared_ptr<gameng::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(gameng::VertexBuffer::Create(vertices, sizeof(vertices)));
  
    gameng::BufferLayout layout = {
      {gameng::ShaderDataType::Float3, "a_position"},
      {gameng::ShaderDataType::Float4, "a_color"}
    };
  
    vertexBuffer->SetLayout(layout);
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    unsigned int indices[3] = {0,1,2};
    std::shared_ptr<gameng::IndexBuffer> indexBuffer;
    indexBuffer.reset(gameng::IndexBuffer::Create(indices, sizeof(indices ) / sizeof(uint32_t)));
    m_vertexArray->SetIndexBuffer(indexBuffer);
    m_squareVA.reset(gameng::VertexArray::Create());
  
    float squareVertices[3*4] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,  
      0.5f, 0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f
    };
    std::shared_ptr<gameng::VertexBuffer> squareVB;
    squareVB.reset(gameng::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout( {
      {gameng::ShaderDataType::Float3, "a_position"},
    });
    m_squareVA->AddVertexBuffer(squareVB);
    unsigned int squareIndices[6] = {0,1,2,2,3,0};
    std::shared_ptr<gameng::IndexBuffer> squareIndexBuffer;
    squareIndexBuffer.reset(gameng::IndexBuffer::Create(squareIndices, sizeof(squareIndices ) / sizeof(uint32_t)));
    m_squareVA->SetIndexBuffer(squareIndexBuffer);


    std::string vertexSrc = R"(
      #version 330 core

      layout(location=0) in vec3 a_position;
      layout(location=1) in vec4 a_color;

      out vec3 v_position;
      out vec4 v_color;

      uniform mat4 u_viewProjection;

      void main()
      {
        v_position = a_position;
        v_color = a_color;
        gl_Position = u_viewProjection * vec4(a_position, 1.0);
      }
    )";

    std::string fragmentSource = R"(
      #version 330 core

      layout(location=0) out vec4 color;

      in vec3 v_position;
      in vec4 v_color;

      void main()
      {
        color = vec4(v_position * 0.5 + 0.5, 1.0);
        color = v_color;
      }
    )";
  
    std::string vertexSrc2 = R"(
      #version 330 core

      layout(location=0) in vec3 a_position;
      layout(location=1) in vec4 a_color;

      uniform mat4 u_viewProjection;

      out vec3 v_position;

      void main()
      {
        v_position = a_position;
        gl_Position = u_viewProjection * vec4(a_position, 1.0);
      }
    )";

    std::string fragmentSource2 = R"(
      #version 330 core

      layout(location=0) out vec4 color;

      in vec3 v_position;

      void main()
      {
        color = vec4(0.2, 0.3, 0.8, 1.0);
      }
    )";
    m_shader.reset(new gameng::Shader(vertexSrc, fragmentSource));
    m_blueShader.reset(new gameng::Shader(vertexSrc2, fragmentSource2));
  }

  void OnUpdate() override
  {
    if(gameng::Input::IsKeyPressed(GAMENG_KEY_LEFT))
    {
      m_cameraPosition.x += m_cameraMoveSpeed;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_RIGHT))
    {
      m_cameraPosition.x -= m_cameraMoveSpeed;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_UP))
    {
      m_cameraPosition.y -= m_cameraMoveSpeed;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_DOWN))
    {
      m_cameraPosition.y += m_cameraMoveSpeed;
    }
    
    if(gameng::Input::IsKeyPressed(GAMENG_KEY_A))
    {
      m_cameraRotation += m_cameraRotationSpeed;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_D))
    {
      m_cameraRotation -= m_cameraRotationSpeed;
    } 

    m_camera.SetPosition(m_cameraPosition);
    gameng::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    gameng::RenderCommand::Clear();
    m_camera.SetPosition(m_cameraPosition); 
    m_camera.SetRotation(m_cameraRotation);
    gameng::Renderer::BeginScene(m_camera);
    
    gameng::Renderer::Submit(m_blueShader, m_squareVA);  
    gameng::Renderer::Submit(m_shader, m_vertexArray);  
    
    gameng::Renderer::EndScene();
  }
  
  void OnEvent(gameng::Event& event) override
  {
  }

private:
  std::shared_ptr<gameng::Shader> m_shader;
  std::shared_ptr<gameng::Shader> m_blueShader;
  
  std::shared_ptr<gameng::VertexArray> m_vertexArray;
  std::shared_ptr<gameng::VertexArray> m_squareVA;
  gameng::OrtographicCamera m_camera;
  glm::vec3 m_cameraPosition;
  float m_cameraMoveSpeed = 0.1f;
  float m_cameraRotation = 0.0f;
  float m_cameraRotationSpeed = 1.0f;
};
class Sandbox : public gameng::Application{
public:
  Sandbox()
  {
    PushLayer(new ExampleLayer());
  }
  ~Sandbox(){}
};

gameng::Application* gameng::CreateApplication()
{
  return new Sandbox();
}