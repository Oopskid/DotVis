#include "pch.h"
#include "Canvas.h"

using namespace DVF;

Canvas::Canvas()
{
	
}

void DVF::Canvas::setAsRenderTarget(ID3D11DeviceContext* devCon)
{
	devCon->RSSetViewports(1, &view);
	devCon->OMSetRenderTargets(1, &textureTarget, depthStencilView);
}

void DVF::Canvas::clearColour(ID3D11DeviceContext* devCon, const FLOAT* colour)
{
	devCon->ClearRenderTargetView(textureTarget, colour);
}

void DVF::Canvas::updateMeta(bool refreshPort)
{
	//This should be rarely called
	texture->GetDesc(&textureDesc);

	if (refreshPort)
	{
		setPort(textureDesc.Width, textureDesc.Height);
	}
}

void DVF::Canvas::setPort(float width, float height, float x, float y)
{
	view.Width = width;
	view.Height = height;
	view.TopLeftX = x;
	view.TopLeftY = y;
}

void DVF::Canvas::setDepth(float min, float max)
{
	view.MinDepth = min;
	view.MaxDepth = max;
}
