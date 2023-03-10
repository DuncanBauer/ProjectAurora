// Aurora Engine Library
// Source file

// For more information visit: https://github.com/DuncanBauer/ProjectAurora

// Developed by Duncan Bauer and every direct or indirect contributors to the GitHub.
// LICENSING INFORMATION

// It is recommended that you don't modify any source code! It will become difficult for you to update the library.
// Note that 'Aurora::' being a namespace, you can add functions into the namespace from your own source files, without
// modifying Util.h or Util.cpp. Discussing your changes on the GitHub Issue Tracker may lead you
// to a better solution or official support for them.

// Index of this file:
// CODE
//   - [SECTION] INCLUDES
//   - [SECTION] STATIC VARIABLE INITIALIZATION
//   - [SECTION] FUNCTIONS

/************************************************************************************
* [SECTION] INCLUDES
************************************************************************************/
#pragma region Includes
// PCH
#include "AuroraEnginePCH.h"

// Project Specific Header
#include "Aurora/Core/Util.h"
#include "ImGuiLayer.h"
#include "Aurora/Core/Application.h"

// C++ Headers

// Third Party Library Headers
#include "imgui.h"
#include "backends/imgui_impl_glfw.h" 
#include "backends/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma endregion

namespace Aurora
{
/************************************************************************************
* [SECTION] STATIC VARIABLE INITIALIZATION
************************************************************************************/
#pragma region Static Initialization
#pragma endregion

/************************************************************************************
* [SECTION] FUNCTIONS
************************************************************************************/
#pragma region Functions
    void ImGuiLayer::OnAttach() 
    {
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();

      ImGuiIO& io = ImGui::GetIO();
      io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
      io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
      io.ConfigFlags  |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
      io.ConfigFlags  |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
      io.ConfigFlags  |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

      ImGui::StyleColorsDark();
      ImGuiStyle& style = ImGui::GetStyle();
      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
      }

      ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
      ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach() 
    {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin()
    {
      ImGuiIO& io = ImGui::GetIO();
      Application& app = Application::Get();

      long long time = Time::GetTimeSeconds();
      io.DeltaTime = m_Time > 0.0 ? ((float)time - m_Time) : (1.0f / 60.0f);
      m_Time = (float)time;

      ImGui_ImplGlfw_NewFrame();
      ImGui_ImplOpenGL3_NewFrame();
      ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
      ImGuiIO& io = ImGui::GetIO();
      Application& app = Application::Get();
      io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
      
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
      }
    }

    void ImGuiLayer::OnUpdate()
    {
    }

    void ImGuiLayer::OnImGuiRender()
    {
      static bool show_demo = false;
      ImGui::ShowDemoWindow(&show_demo);
    }

    void ImGuiLayer::OnEvent(Aurora::Event& e)
    {
      EventDispatcher dispatcher(e);
    // Handled in GLFW and OPENGL backends
      //dispatcher.Dispatch<WindowGainedFocusEvent>(BIND_EVENT_FN(ImGuiLayer, OnWindowGainedFocus));
      //dispatcher.Dispatch<WindowLostFocusEvent>(BIND_EVENT_FN(ImGuiLayer, OnWindowLoseFocus));
      //dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(ImGuiLayer, OnWindowClosed));
      //dispatcher.Dispatch<WindowMaximizedEvent>(BIND_EVENT_FN(ImGuiLayer, OnWindowMaximized));
      //dispatcher.Dispatch<WindowMinimizedEvent>(BIND_EVENT_FN(ImGuiLayer, OnWindowMinimized));
      //dispatcher.Dispatch<WindowRestoredEvent>(BIND_EVENT_FN(ImGuiLayer, OnWindowRestored));
      //dispatcher.Dispatch<WindowMovedEvent>(BIND_EVENT_FN(ImGuiLayer, OnWindowMoved));
      //dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(ImGuiLayer, OnWindowResized));

      //dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer, OnMouseButtonPressedEvent));
      //dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer, OnMouseButtonReleasedEvent));
      //dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer, OnMouseMovedEvent));
      //dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer, OnMouseScrolledEvent));

      //dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer, OnKeyboardButtonPressedEvent));
      //dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer, OnKeyboardButtonReleasedEvent));
      //dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer, OnKeyboardButtonTypedEvent));
    }

  // Handled in GLFW and OPENGL backends
    //bool ImGuiLayer::OnWindowGainedFocus(Aurora::WindowGainedFocusEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  
    //  return IsBlocking();
    //}

    //bool ImGuiLayer::OnWindowLoseFocus(Aurora::WindowLostFocusEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  
    //  return IsBlocking();
    //}

    //bool ImGuiLayer::OnWindowClosed(Aurora::WindowClosedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  
    //  return IsBlocking();
    //}

    //bool ImGuiLayer::OnWindowMaximized(Aurora::WindowMaximizedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  
    //  return IsBlocking();
    //}

    //bool ImGuiLayer::OnWindowMinimized(Aurora::WindowMinimizedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  
    //  return IsBlocking();
    //}

    //bool ImGuiLayer::OnWindowRestored(Aurora::WindowRestoredEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  
    //  return IsBlocking();
    //}

    //bool ImGuiLayer::OnWindowMoved(Aurora::WindowMovedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();

    //  return IsBlocking();
    //}

    //bool ImGuiLayer::OnWindowResized(Aurora::WindowResizedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  
    //  io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
    //  io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    //  glViewport(0, 0, e.GetWidth(), e.GetWidth());
    //  
    //  return IsBlocking();
    //}
 
    //bool ImGuiLayer::OnMouseButtonPressedEvent(Aurora::MouseButtonPressedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  io.MouseDown[e.GetMouseButton()] = true;
    //  return IsBlocking();
    //}
    //
    //bool ImGuiLayer::OnMouseButtonReleasedEvent(Aurora::MouseButtonReleasedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  io.MouseDown[e.GetMouseButton()] = false;
    //  return IsBlocking();
    //}
    //
    //bool ImGuiLayer::OnMouseScrolledEvent(Aurora::MouseScrolledEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  
    //  io.MouseWheelH += e.GetXOffset();
    //  io.MouseWheel += e.GetYOffset();
    //  
    //  return IsBlocking();
    //}

    //bool ImGuiLayer::OnMouseMovedEvent(Aurora::MouseMovedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  io.MousePos = ImVec2(e.GetX(), e.GetY());
    //  return IsBlocking();
    //}
    //
    //bool ImGuiLayer::OnKeyboardButtonPressedEvent(Aurora::KeyPressedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  
    //  io.KeysDown[e.GetKey()] = true;
    //  io.KeyCtrl  = io.KeysDown[Key::LeftControl || Key::RightControl];
    //  io.KeyAlt   = io.KeysDown[Key::LeftAlt     || Key::RightAlt];
    //  io.KeyShift = io.KeysDown[Key::LeftShift   || Key::RightShift];
    //  io.KeySuper = io.KeysDown[Key::LeftSuper   || Key::RightSuper];

    //  return IsBlocking();
    //}
    //
    //bool ImGuiLayer::OnKeyboardButtonReleasedEvent(Aurora::KeyReleasedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();
    //  io.KeysDown[e.GetKey()] = false;
    //  return IsBlocking();
    //}

    //// For typing into input boxes
    //bool ImGuiLayer::OnKeyboardButtonTypedEvent(Aurora::KeyTypedEvent& e)
    //{
    //  ImGuiIO& io = ImGui::GetIO();

    //  int keycode = e.GetKey();
    //  if (keycode > 0 && keycode < 0x10000)
    //  {
    //    io.AddInputCharacter((unsigned short)keycode);
    //  }

    //  return IsBlocking();
    //}
#pragma endregion
}