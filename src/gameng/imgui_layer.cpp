#include "imgui_layer.hpp"

#include "imgui.h"
#include "platform/opengl/imgui_opengl_renderer.hpp"

namespace gameng
{
  ImguiLayer::ImguiLayer() : Layer("ImguiLayer")
  {

  }

  ImguiLayer::~ImguiLayer()
  {

  }

  void ImguiLayer::OnAttach()
  {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  }

  void ImguiLayer::OnDetach()
  {

  } 

  void ImguiLayer::OnUpdate()
  {

  } 

  void ImguiLayer::OnEvent(Event& event)
  {

  } 
  
} // namespace gameng
