#include "mcpch.h"
#include "Application.h"
#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <tchar.h>
#include "MCP/Renderer/RenderCommand.h"

#include <glad/glad.h>

namespace MC
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{

	}

	void ImGuiLayer::OnUpdate(DeltaTime& deltaTime)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = deltaTime;
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
		ImGui_ImplWin32_Shutdown();
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsClassic();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigDockingWithShift = true;

		ImGui_ImplWin32_Init(Application::Get()->GetWindow().GetNativeWindow());
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnImGuiRender()
	{

	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrollEvent));
		//dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		//dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		//dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()-1] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()-1] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return true;
	}

	bool ImGuiLayer::OnMouseScrollEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.KeysDown[e.GetKeyCode()] = true;
// 
// 		io.KeyCtrl = io.KeysDown[(int)MC_KEYS::MC_KEY_CTRL] || io.KeysDown[(int)MC_KEYS::MC_KEY_LCTRL];
// 		io.KeyShift = io.KeysDown[(int)MC_KEYS::MC_KEY_SHIFT] || io.KeysDown[(int)MC_KEYS::MC_KEY_LSHIFT];
// 		io.KeyAlt = io.KeysDown[(int)MC_KEYS::MC_KEY_ALT];

		return false;

	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
// 		ImGuiIO& io = ImGui::GetIO();
// 
// 		unsigned short keycode = e.GetKeyCode();
// 
// 		//if (keycode > 0 && keycode < 0x10000)
// 			io.AddInputCharacter(keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());		
	}
}