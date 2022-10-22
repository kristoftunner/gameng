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
  ExampleLayer() : Layer("Example"),  m_cameraPosition({0.0f, -0.5f, -4.0f}), m_squarePosition(0.0f)
  {
    // initialize camera
    m_camera.reset(new gameng::PerspectiveCamera(1.0f, 45.0f, 0.1f, 100.0f));
    //m_camera.reset(new gameng::OrtographicCamera(-1.6f, 1.6f, -0.9f, 0.9f));
    
    // initialize vertex array
    m_pyramidVA.reset(gameng::VertexArray::Create());
  
    // pyramid vertices
    float pyramidVertices[] =
    { //     COORDINATES   Texture coordinates 
    	-0.5f, 0.0f,  0.5f,  0.0f, 0.0f,
    	-0.5f, 0.0f, -0.5f,  5.0f, 0.0f,
    	 0.5f, 0.0f, -0.5f,  0.0f, 0.0f,
    	 0.5f, 0.0f,  0.5f,  5.0f, 0.0f,
    	 0.0f, 0.8f,  0.0f,  2.5f, 5.0f
    };

    // indices for the pyramid
    unsigned int pyramidIndices[] =
    {
    	0, 1, 2,
    	0, 2, 3,
    	0, 1, 4,
    	1, 2, 4,
    	2, 3, 4,
    	3, 0, 4
    };

    // vertex buffer setup for the pyramid 
    gameng::Ref<gameng::VertexBuffer> pyramidVB;
    pyramidVB.reset(gameng::VertexBuffer::Create(pyramidVertices, sizeof(pyramidVertices)));
    pyramidVB->SetLayout( {
      {gameng::ShaderDataType::Float3, "a_position"},
      {gameng::ShaderDataType::Float2, "a_textCoord"}
    });
    m_pyramidVA->AddVertexBuffer(pyramidVB);

    // inxed buffer setup for the texture square
    gameng::Ref<gameng::IndexBuffer> pyramidIB;
    pyramidIB.reset(gameng::IndexBuffer::Create(pyramidIndices, sizeof(pyramidIndices ) / sizeof(uint32_t)));
    m_pyramidVA->SetIndexBuffer(pyramidIB);

    // load and create the shaders for the texture, triangle and coloring
    auto textureShader = m_shaderLibrary.Load("sandbox/assets/shaders/texture.glsl");

    // load the textures, bind and upload the uniforms for it
    m_texture = gameng::Texture2D::Create("sandbox/assets/textures/brick.png");
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

    // camera setup
    m_camera->SetPosition(m_cameraPosition);
    m_camera->SetRotation(m_cameraRotation);
    
    // Renderer initialization
    gameng::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    gameng::RenderCommand::Clear();
    gameng::Renderer::BeginScene(m_camera);

    // rendering the flat colored sqaures
    //glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    //std::dynamic_pointer_cast<gameng::OpenGLShader>(m_flatColorShader)->Bind(); 
    //std::dynamic_pointer_cast<gameng::OpenGLShader>(m_flatColorShader)->UploadUniformFloat3("u_color", m_squareColor); 
    //for(int x = 0; x < 20; x++)
    //{
    //  for(int y = 0; y < 5; y++)
    //  {
    //    glm::vec3 position(x * 0.11f, y* 0.11f, 0.0f);
    //    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
    //    gameng::Renderer::Submit(m_flatColorShader, m_squareVA, transform);  
    //  } 
    //}

    //// rendering the textures  
    //m_texture->Bind(0);
    //gameng::Renderer::Submit(m_shaderLibrary.Get("texture"), m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));  
    //m_logoTexture->Bind(0);
    //gameng::Renderer::Submit(m_shaderLibrary.Get("texture"), m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));  
    
    // rendering the pyramid
    m_texture->Bind(0);
    gameng::Renderer::Submit(m_shaderLibrary.Get("texture"), m_pyramidVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));  
    m_logoTexture->Bind(0);
    gameng::Renderer::Submit(m_shaderLibrary.Get("texture"), m_pyramidVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));  
    
    
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
  gameng::Ref<gameng::Camera> m_camera;
  
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