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
    // initialize vertex array
    m_vertexArray.reset(gameng::VertexArray::Create());
    m_squareVA.reset(gameng::VertexArray::Create());
    m_pyramidVA.reset(gameng::VertexArray::Create());
  
    // triangle vertices for the colored squares
    float triangleVerticies[3*7] = {
      // vertex coordinates   Colors
      -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f, 
      0.0f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f, 1.0f 
    };
    
    unsigned int triangleIndices[3] = {0,1,2};

    // square vertices for the texture
    float squareVertices[5*4] = {
      // vertex coordinates Texture coordinates
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
      0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 
      0.5f,  0.5f,  0.0f,   1.0f, 1.0f, 
      -0.5f, 0.5f,  0.0f,   0.0f, 1.0f 
    };
    
    unsigned int squareIndices[6] = {0,1,2,2,3,0};
    
    // pyramid vertices
    float pyramidVertices[] =
    { //     COORDINATES     /        COLORS              /   TexCoord  //
    	-0.5f,  0.5f, 0.0f,    0.83f, 0.70f, 0.44f, 1.0f,	  0.0f, 0.0f,
    	-0.5f, -0.5f, 0.0f,    0.83f, 0.70f, 0.44f, 1.0f,	  5.0f, 0.0f,
    	 0.5f, -0.5f, 0.0f,    0.83f, 0.70f, 0.44f, 1.0f,	  0.0f, 0.0f,
    	 0.5f,  0.5f, 0.0f,    0.83f, 0.70f, 0.44f, 1.0f,	  5.0f, 0.0f,
    	 0.0f,  0.0f, 0.8f,    0.92f, 0.86f, 0.76f, 1.0f,	  2.5f, 5.0f
    };

    // indices for the pyramid
    unsigned int indices[] =
    {
    	0, 1, 2,
    	0, 2, 3,
    	0, 1, 4,
    	1, 2, 4,
    	2, 3, 4,
    	3, 0, 4
    };

    // vertex buffer setup for the triangles
    gameng::Ref<gameng::VertexBuffer> triangleVB;
    triangleVB.reset(gameng::VertexBuffer::Create(triangleVerticies, sizeof(triangleVerticies)));
  
    gameng::BufferLayout layout = {
      {gameng::ShaderDataType::Float3, "a_position"},
      {gameng::ShaderDataType::Float4, "a_color"}
    };

    triangleVB->SetLayout(layout);
    m_vertexArray->AddVertexBuffer(triangleVB);

    // index buffer setup for the triangles
    gameng::Ref<gameng::IndexBuffer> triangleIB;
    triangleIB.reset(gameng::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices ) / sizeof(uint32_t)));
    m_vertexArray->SetIndexBuffer(triangleIB);
  
    // vertex buffer setup for the texture square
    gameng::Ref<gameng::VertexBuffer> squareVB;
    squareVB.reset(gameng::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout( {
      {gameng::ShaderDataType::Float3, "a_position"},
      {gameng::ShaderDataType::Float2, "a_textCoord"},
    });
    m_squareVA->AddVertexBuffer(squareVB);

    // inxed buffer setup for the texture square
    gameng::Ref<gameng::IndexBuffer> squareIB;
    squareIB.reset(gameng::IndexBuffer::Create(squareIndices, sizeof(squareIndices ) / sizeof(uint32_t)));
    m_squareVA->SetIndexBuffer(squareIB);

    // vertex buffer setup for the pyramid 
    gameng::Ref<gameng::VertexBuffer> pyramidVB;
    pyramidVB.reset(gameng::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    pyramidVB->SetLayout( {
      {gameng::ShaderDataType::Float3, "a_position"},
      {gameng::ShaderDataType::Float4, "a_color"},
      {gameng::ShaderDataType::Float2, "a_textCoord"}
    });
    m_pyramidVA->AddVertexBuffer(pyramidVB);

    // inxed buffer setup for the texture square
    gameng::Ref<gameng::IndexBuffer> pyramidIB;
    pyramidIB.reset(gameng::IndexBuffer::Create(squareIndices, sizeof(squareIndices ) / sizeof(uint32_t)));
    m_pyramidVA->SetIndexBuffer(pyramidIB);
    // shader for the colored triangles
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

    // shaders for the texture square
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
    
    // load and create the shaders for the texture, triangle and coloring
    m_triangleShader = gameng::Shader::Create("vertex", vertexSrc, fragmentSource);
    m_flatColorShader = gameng::Shader::Create("flatColor", flatColorVertexSource, flatColorFragmentSource);
    auto textureShader = m_shaderLibrary.Load("sandbox/assets/shaders/texture.glsl");

    // load the textures, bind and upload the uniforms for it
    m_texture = gameng::Texture2D::Create("sandbox/assets/textures/Checkerboard.png");
    m_logoTexture = gameng::Texture2D::Create("sandbox/assets/textures/logo.png");
    std::dynamic_pointer_cast<gameng::OpenGLShader>(m_shaderLibrary.Get("texture"))->Bind(); 
    std::dynamic_pointer_cast<gameng::OpenGLShader>(m_shaderLibrary.Get("texture"))->UploadUniformInt("u_texture", 0); 
  }

  void OnUpdate(gameng::Timestep ts) override
  {
    // key input handling
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

    // camera setup
    m_camera.SetPosition(m_cameraPosition);
    m_camera.SetPosition(m_cameraPosition); 
    m_camera.SetRotation(m_cameraRotation);
    
    // Renderer initialization
    gameng::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    gameng::RenderCommand::Clear();
    gameng::Renderer::BeginScene(m_camera);

    // rendering the flat colored sqaures
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

    // rendering the textures  
    m_texture->Bind(0);
    gameng::Renderer::Submit(m_shaderLibrary.Get("texture"), m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));  
    m_logoTexture->Bind(0);
    gameng::Renderer::Submit(m_shaderLibrary.Get("texture"), m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));  
    
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
  // shader related members
  gameng::ShaderLibrary m_shaderLibrary;
  gameng::Ref<gameng::Shader> m_triangleShader;
  gameng::Ref<gameng::Shader> m_flatColorShader;
  
  // textures
  gameng::Ref<gameng::Texture2D> m_texture, m_logoTexture;
  
  // vertex arrays
  gameng::Ref<gameng::VertexArray> m_vertexArray;
  gameng::Ref<gameng::VertexArray> m_squareVA;
  gameng::Ref<gameng::VertexArray> m_pyramidVA;
  
  // camera-> this should be dependency injected: strategy pattern in the future
  gameng::OrtographicCamera m_camera;
  
  // camera motion specific
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