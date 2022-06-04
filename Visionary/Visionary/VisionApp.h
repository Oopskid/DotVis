#pragma once

//UI
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"

//Graphics dependencies
#include "RDevice.h"

//Application
#include "Window.h"

using namespace WSTR;
using namespace DVF;

class VisionApp : public Window
{
	public:
	VisionApp();
	~VisionApp();

	protected:
	virtual void onStart() override;
	virtual void main() override;
	virtual void onEnd() override;
	virtual void onResize() override;
	virtual void onKeyDown(char vkey) override;
	virtual void onKeyUp(char vkey) override;
	virtual void onMouseMove(short x, short y) override;

	void render(float dt);

	private:
	ImGuiContext* imguiCon;
	RDevice renderDevice;
};

