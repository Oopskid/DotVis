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
	renderDevice.makeBackBuffer();

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

	renderDevice.clearBackBuffer();

	renderDevice.setBackBufferTarget();
	render(0.0f);
	renderDevice.setBackBufferTarget();

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

void VisionApp::onResize()
{
	renderDevice.resize(getWidth(), getHeight());
	if (imguiCon)
	{
		ImGui::SetNextWindowSize(ImVec2{ (float)getWidth(), (float)getHeight() });
	}
}

void VisionApp::onKeyDown(char vkey)
{
	switch (vkey)
	{
		case VK_LBUTTON:
		ImGui::GetIO().AddMouseButtonEvent(0, true);
		break;
	}
}

void VisionApp::onKeyUp(char vkey)
{
	switch (vkey)
	{
		case VK_LBUTTON:
		ImGui::GetIO().AddMouseButtonEvent(0, false);
		break;
	}
}

void VisionApp::onMouseMove(short x, short y)
{
	ImGui::GetIO().MousePos = { (float)x, (float)y };
}

void VisionApp::render(float dt)
{
	if (ImGui::Begin("DEBUGWINDOW", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("oof");
	}
	ImGui::End();
}
