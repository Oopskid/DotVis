#include "VisionApp.h"

VisionApp::VisionApp() : Window()
{
	imguiCon = nullptr;
}

VisionApp::~VisionApp()
{

}

void VisionApp::onStart()
{
	Window::onStart();

	DVAssert(renderDevice.create() == S_OK, "Failed to create the device obj");
	DVAssert(renderDevice.makeSwapChain(wHandle) == S_OK, "Failed to create the swapchain");
	DVAssert(renderDevice.makeBackBuffer() == S_OK, "Failed to create the backbuffer");

	imguiCon = ImGui::CreateContext();
	ImGui::SetCurrentContext(imguiCon);
	assert(ImGui_ImplWin32_Init(wHandle));
	assert(ImGui_ImplDX11_Init(renderDevice.getDevice(), renderDevice.getContext()));
	ImGui::GetIO().Fonts->AddFontDefault();
	ImGui::GetIO().Fonts->Build();
	ImGui_ImplDX11_CreateDeviceObjects();

	#if isDebug
		//ImGui::GetIO().MouseDrawCursor = true;
	#endif

	tracer.init(&renderDevice, std::wstring(CURRENT_DIRECTORY).append(L"/shaders"));
}

void VisionApp::onEnd()
{
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext(imguiCon);
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

void VisionApp::onResize()
{
	if (renderDevice.getContext())
	{
		if (renderDevice.resize(getWidth(), getHeight()) != S_OK)
		{
			std::cout << "UH \n";
		}
	}

	RECT rect{ 0, 0, getWidth(), getHeight() };
	InvalidateRect(wHandle, &rect, TRUE);

	if (imguiCon)
	{
		ImVec2 wSize = ImVec2{ (float)getWidth(), (float)getHeight() };
		ImGui::SetNextWindowSize(wSize);
		ImGui::GetIO().DisplaySize = wSize;

		ImGui_ImplDX11_InvalidateDeviceObjects();
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

void VisionApp::onMove()
{
	if (imguiCon)
	{
		ImGui::SetNextWindowPos(ImVec2{ (float)getX(), (float)getY() });
	}
}

void VisionApp::render(float dt)
{
	renderGUI();
}

void VisionApp::renderGUI()
{
	if (ImGui::Begin("DEBUGWINDOW", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_None))
	{
		ImGui::Text("oof dddddddddddddddddd");
	}
	ImGui::End();
}
