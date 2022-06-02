#include "VisionApp.h"

VisionApp::VisionApp() : Window()
{

}

VisionApp::~VisionApp()
{

}

void VisionApp::onStart()
{
	Window::onStart();

	renderDevice.create();
	renderDevice.makeSwapChain(wHandle);

	imguiCon = ImGui::CreateContext();
	ImGui::SetCurrentContext(imguiCon);
	assert(ImGui_ImplWin32_Init(wHandle));
	assert(ImGui_ImplDX11_Init(renderDevice.getDevice(), renderDevice.getContext()));
	ImGui::GetIO().Fonts->AddFontDefault();
	ImGui::GetIO().Fonts->Build();
	ImGui_ImplDX11_CreateDeviceObjects();
}

void VisionApp::main()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	render(0.0f);

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	renderDevice.swapBuffer();
}

void VisionApp::onEnd()
{
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext(imguiCon);
}

void VisionApp::render(float dt)
{
	ImGui::Begin("DEBUGWINDOW");
		ImGui::Text("oof");
	ImGui::End();
}
