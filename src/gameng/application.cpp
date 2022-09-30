
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "gameng/applicaiton.hpp"
#include "gameng/application_event.hpp"
#include "gameng/log.hpp"
#include "gameng/input.hpp"
namespace gameng
{
#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

Application* Application::s_instance = nullptr;

Application::Application()
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

  m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
  
  BufferLayout layout = {
    {ShaderDataType::Float3, "a_position"},
    {ShaderDataType::Float4, "a_color"}
  };
  
  m_vertexBuffer->SetLayout(layout);
  m_vertexArray->AddVertexBuffer(m_vertexBuffer);

  unsigned int indices[3] = {0,1,2};
  m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

  std::string vertexSrc = R"(
    #version 330 core
    
    layout(location=0) in vec3 a_position;
    layout(location=1) in vec4 a_color;

    out vec3 v_position;
    out vec4 v_color;

    void main()
    {
      v_position = a_position;
      v_color = a_color;
      gl_Position = vec4(a_position, 1.0);
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
  m_shader.reset(new Shader(vertexSrc, fragmentSource));
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
    glClearColor(0.1f,0.1f,0.1f,1);
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader->Bind();

    glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
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
