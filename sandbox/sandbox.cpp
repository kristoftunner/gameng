#include "gameng.hpp"
#include <iostream>
#include <memory>
#include <experimental/filesystem>

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public gameng::Layer
{
public:
  ExampleLayer() : Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_cameraPosition(0.0f), m_squarePosition(0.0f)
  {
    m_vertexArray.reset(gameng::VertexArray::Create());
  
    float vertices[3*7] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
      0.0f, 0.5f, 0.0f,1.0f, 0.0f, 0.0f, 1.0f 
    };

    gameng::Ref<gameng::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(gameng::VertexBuffer::Create(vertices, sizeof(vertices)));
  
    gameng::BufferLayout layout = {
      {gameng::ShaderDataType::Float3, "a_position"},
      {gameng::ShaderDataType::Float4, "a_color"}
    };
  
    vertexBuffer->SetLayout(layout);
    m_vertexArray->AddVertexBuffer(vertexBuffer);

    unsigned int indices[3] = {0,1,2};
    gameng::Ref<gameng::IndexBuffer> indexBuffer;
    indexBuffer.reset(gameng::IndexBuffer::Create(indices, sizeof(indices ) / sizeof(uint32_t)));
    m_vertexArray->SetIndexBuffer(indexBuffer);
    m_squareVA.reset(gameng::VertexArray::Create());
  
    float squareVertices[5*4] = {
      -0.5f, -0.5f, 0.0f,0.0f, 0.0f,
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
      0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 
      -0.5f, 0.5f, 0.0f, 0.0f, 1.0f 
    };
    gameng::Ref<gameng::VertexBuffer> squareVB;
    squareVB.reset(gameng::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout( {
      {gameng::ShaderDataType::Float3, "a_position"},
      {gameng::ShaderDataType::Float2, "a_textCoord"},
    });
    m_squareVA->AddVertexBuffer(squareVB);
    unsigned int squareIndices[6] = {0,1,2,2,3,0};
    gameng::Ref<gameng::IndexBuffer> squareIndexBuffer;
    squareIndexBuffer.reset(gameng::IndexBuffer::Create(squareIndices, sizeof(squareIndices ) / sizeof(uint32_t)));
    m_squareVA->SetIndexBuffer(squareIndexBuffer);


    std::string vertexSrc = R"(
      #version 330 core

      layout(location=0) in vec3 a_position;
      layout(location=1) in vec4 a_color;

      out vec3 v_position;
      out vec4 v_color;

      uniform mat4 u_viewProjection;
      uniform mat4 u_transform;

      void main()
      {
        v_position = a_position;
        v_color = a_color;
        gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
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
  
    std::string flatColorVertexSource = R"(
      #version 330 core

      layout(location=0) in vec3 a_position;
      layout(location=1) in vec4 a_color;

      uniform mat4 u_viewProjection;
      uniform mat4 u_transform;

      out vec3 v_position;

      void main()
      {
        v_position = a_position;
        gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
      }
    )";

    std::string flatColorFragmentSource = R"(
      #version 330 core

      layout(location=0) out vec4 color;

      in vec3 v_position;
      uniform vec3 u_color;

      void main()
      {
        color = vec4(u_color, 1.0);
      }
    )";
    
    std::string textureShaderVertexSource = R"(
      #version 330 core

      layout(location=0) in vec3 a_position;
      layout(location=1) in vec2 a_textCoord;

      uniform mat4 u_viewProjection;
      uniform mat4 u_transform;

      out vec3 v_position;
      out vec2 v_textCoord;
      void main()
      {
        v_textCoord = a_textCoord;
        v_position = a_position;
        gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
      }
    )";

    std::string textureShaderFragmentSource = R"(
      #version 330 core

      layout(location=0) out vec4 color;

      in vec2 v_textCoord;

      uniform sampler2D u_texture;

      void main()
      {
        color = texture(u_texture, v_textCoord);
      }
    )";
    m_shader.reset(gameng::Shader::Create(vertexSrc, fragmentSource));
    m_flatColorShader.reset(gameng::Shader::Create(flatColorVertexSource, flatColorFragmentSource));
    m_textureShader.reset(gameng::Shader::Create(textureShaderVertexSource, textureShaderFragmentSource));
    m_texture = gameng::Texture2D::Create("../sandbox/assets/textures/Checkerboard.png");
    std::dynamic_pointer_cast<gameng::OpenGLShader>(m_textureShader)->Bind(); 
    std::dynamic_pointer_cast<gameng::OpenGLShader>(m_textureShader)->UploadUniformInt("u_texture", 0); 
  }

  void OnUpdate(gameng::Timestep ts) override
  {
    if(gameng::Input::IsKeyPressed(GAMENG_KEY_LEFT))
    {
      m_cameraPosition.x += m_cameraMoveSpeed * ts;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_RIGHT))
    {
      m_cameraPosition.x -= m_cameraMoveSpeed * ts;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_UP))
    {
      m_cameraPosition.y -= m_cameraMoveSpeed* ts;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_DOWN))
    {
      m_cameraPosition.y += m_cameraMoveSpeed* ts;
    }
    
    if(gameng::Input::IsKeyPressed(GAMENG_KEY_A))
    {
      m_cameraRotation += m_cameraRotationSpeed* ts;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_D))
    {
      m_cameraRotation -= m_cameraRotationSpeed* ts;
    } 

    if(gameng::Input::IsKeyPressed(GAMENG_KEY_J))
    {
      m_squarePosition.x += m_squareMoveSpeed * ts;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_L))
    {
      m_squarePosition.x -= m_squareMoveSpeed * ts;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_I))
    {
      m_squarePosition.y += m_squareMoveSpeed * ts;
    } 
    else if(gameng::Input::IsKeyPressed(GAMENG_KEY_K))
    {
      m_squarePosition.y -= m_squareMoveSpeed * ts;
    } 

    m_camera.SetPosition(m_cameraPosition);
    gameng::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    gameng::RenderCommand::Clear();
    m_camera.SetPosition(m_cameraPosition); 
    m_camera.SetRotation(m_cameraRotation);
    gameng::Renderer::BeginScene(m_camera);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    std::dynamic_pointer_cast<gameng::OpenGLShader>(m_flatColorShader)->Bind(); 
    std::dynamic_pointer_cast<gameng::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_color", m_squareColor); 
    for(int x = 0; x < 20; x++)
    {
      for(int y = 0; y < 5; y++)
      {
        glm::vec3 position(x * 0.11f, y* 0.11f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
        gameng::Renderer::Submit(m_flatColorShader, m_squareVA, transform);  
      } 
    }

    m_texture->Bind(0);
    gameng::Renderer::Submit(m_textureShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));  
    //gameng::Renderer::Submit(m_shader, m_vertexArray);  
    
    gameng::Renderer::EndScene();
  }
  
  void OnEvent(gameng::Event& event) override
  {
  }

  virtual void OnImguiRender() override
  {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square color", glm::value_ptr(m_squareColor));
  }

private:
  gameng::Ref<gameng::Shader> m_shader;
  gameng::Ref<gameng::Shader> m_flatColorShader, m_textureShader;
  gameng::Ref<gameng::Texture2D> m_texture;
  gameng::Ref<gameng::VertexArray> m_vertexArray;
  gameng::Ref<gameng::VertexArray> m_squareVA;
  gameng::OrtographicCamera m_camera;
  glm::vec3 m_cameraPosition;
  float m_cameraMoveSpeed = 5.0f;
  float m_cameraRotation = 0.0f;
  float m_cameraRotationSpeed = 180.0f;
  float m_squareMoveSpeed = 1.0f;
  glm::vec3 m_squarePosition;

  glm::vec3 m_squareColor = {0.2f,0.3f,0.8f};

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