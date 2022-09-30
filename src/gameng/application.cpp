
#include "GLFW/glfw3.h"

#include "gameng/applicaiton.hpp"
#include "gameng/application_event.hpp"
#include "gameng/log.hpp"
#include "gameng/input.hpp"
#include "gameng/renderer/renderer.hpp"
namespace gameng
{
#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

Application* Application::s_instance = nullptr;

Application::Application()
  : m_camera(-1.0f, 1.0f, -1.0f, 1.0f)
{
  if(s_instance == nullptr)
    s_instance = this;
  else 
    GAMENG_CORE_ERR("Multiple Application instances!");
  m_window = std::unique_ptr<Window>(Window::Create());
  m_window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
  m_imguiLayer = new ImguiLayer();
  PushOverlay(m_imguiLayer);

  m_vertexArray.reset(VertexArray::Create());
  
  float vertices[3*7] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
    0.0f, 0.5f, 0.0f,1.0f, 0.0f, 0.0f, 1.0f 
  };

  std::shared_ptr<VertexBuffer> vertexBuffer;
  vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
  
  BufferLayout layout = {
    {ShaderDataType::Float3, "a_position"},
    {ShaderDataType::Float4, "a_color"}
  };
  
  vertexBuffer->SetLayout(layout);
  m_vertexArray->AddVertexBuffer(vertexBuffer);

  unsigned int indices[3] = {0,1,2};
  std::shared_ptr<IndexBuffer> indexBuffer;
  indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices ) / sizeof(uint32_t)));
  m_vertexArray->SetIndexBuffer(indexBuffer);
  m_squareVA.reset(VertexArray::Create());
  
  float squareVertices[3*4] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,  
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };
  std::shared_ptr<VertexBuffer> squareVB;
  squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  squareVB->SetLayout( {
    {ShaderDataType::Float3, "a_position"},
  });
  m_squareVA->AddVertexBuffer(squareVB);
  unsigned int squareIndices[6] = {0,1,2,2,3,0};
  std::shared_ptr<IndexBuffer> squareIndexBuffer;
  squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices ) / sizeof(uint32_t)));
  m_squareVA->SetIndexBuffer(squareIndexBuffer);


  std::string vertexSrc = R"(
    #version 330 core
    
    layout(location=0) in vec3 a_position;
    layout(location=1) in vec4 a_color;

    out vec3 v_position;
    out vec4 v_color;

    uniform vec4 u_viewProjection;

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
    
    uniform vec4 u_viewProjection;

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
  m_shader.reset(new Shader(vertexSrc, fragmentSource));
  m_blueShader.reset(new Shader(vertexSrc2, fragmentSource2));
}

Application::~Application()
{

}

void Application::PushLayer(Layer* layer)
{
  m_layerStack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
  m_layerStack.PushOverlay(layer);
  layer->OnAttach();
}

void Application::OnEvent(Event& e)
{
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

  for(auto it = m_layerStack.end(); it != m_layerStack.begin();)
  {
    (*--it)->OnEvent(e);
    if(e.Handled())
      break;
  }

  GAMENG_CORE_INFO("{0}",e);
}

bool Application::OnWindowClosed(WindowCloseEvent& e)
{
  m_running = false;
  return true;
}

void Application::Run()
{
  WindowResizeEvent e(1200,800);
  GAMENG_CORE_TRACE(e);
  
  while(m_running)
  {
    
    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    RenderCommand::Clear();
    
    Renderer::BeginScene();
    
    m_blueShader->Bind();
    Renderer::Submit(m_squareVA);  
    m_shader->Bind();
    Renderer::Submit(m_vertexArray);  
    
    Renderer::EndScene();

    for(Layer* layer : m_layerStack)
    {
      layer->OnUpdate();
    }

    m_imguiLayer->Begin();
    for(Layer* layer : m_layerStack)
    {
      layer->OnImguiRender();
    }
    m_imguiLayer->End();

    m_window->OnUpdate(); 
  }
}
} // namespace gameng
