#include "pch.h"
#include "Rendering/RDevice.h"

using namespace DVF;

RDevice::RDevice()
{

}

RDevice::~RDevice()
{
	DVXClear(swapChain);
}

HRESULT RDevice::create(UINT flags)
{
	if (dev || devCon) { return NTE_EXISTS; }

	HRESULT result = S_OK;
	#if isDebug
		flags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

    result = D3D11CreateDevice(
            nullptr,                    //Default adapter
            D3D_DRIVER_TYPE_HARDWARE,   //Hardware accelerated
            0,                          
            flags,                
            featureLevels,              //Supported features
            ARRAYSIZE(featureLevels),
            D3D11_SDK_VERSION,
            &dev,                       //Returns device handle
            &supportedL,                //Returns supported features
            &devCon                     //Returns device context
    );

    if (FAILED(result))
    {
        //Fallback! (currently just clears)
        DVXClear(dev, devCon);
    }

	return result;
}

HRESULT RDevice::makeSwapChain(HWND context, DXGI_FORMAT bufferFormat)
{
    //Standard swapchain requirements
    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
    desc.Windowed = TRUE;
    desc.BufferCount = 2;
    desc.BufferDesc.Format = bufferFormat;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.OutputWindow = context;

    return makeSwapChain(context, desc);
}

HRESULT RDevice::makeSwapChain(HWND context, DXGI_SWAP_CHAIN_DESC options)
{
    if (DVAssert(dev && devCon, "Context not built before swapchain")) { return NTE_NOT_FOUND; }

    HRESULT result = S_OK;

    //Get the DXGI association
    IDXGIDevice1* deviceObj = nullptr;
    result = dev->QueryInterface(&deviceObj);
    DVXFirebreak(result);

    //Fetch adapter
    IDXGIAdapter* adapter = nullptr;
    result = deviceObj->GetAdapter(&adapter);
    DVXFirebreak(result);

    //Create a swapchain factory
    IDXGIFactory* factory;
    result = adapter->GetParent(IID_PPV_ARGS(&factory));
    DVXFirebreak(result);

    //Create swapchain
    result = factory->CreateSwapChain(dev, &options, &swapChain);

    return result;
}

HRESULT RDevice::makeBackBuffer()
{
    if (DVAssert(dev && devCon && swapChain, "Full context is required for creation of the back buffer")) { return NTE_NOT_FOUND; }
    HRESULT result = S_OK;

    //Fetch back buffer from the swap chain
    ID3D11Texture2D* backBufferTexture = nullptr;
    result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture);
    backBuffer.holdTexture(backBufferTexture); //Wait this counts as a DX reference?

    //Create render view
    ID3D11RenderTargetView* backBufferTarget = nullptr;
    result = dev->CreateRenderTargetView(backBufferTexture, nullptr, &backBufferTarget);
    backBuffer.holdTarget(backBufferTarget);

    //Cache metadata and set viewport
    backBuffer.updateMeta();

    return result;
}

void RDevice::clearBackBuffer()
{
    backBuffer.clearColour(devCon);
}

HRESULT RDevice::resize(size_t width, size_t height)
{
    if (DVAssert(swapChain, "Swapchain is required for resize of the back buffer")) { return NTE_NOT_FOUND; }

    HRESULT result = S_OK;

    //Get rid of prior swap chain references
    backBuffer.release();
    Canvas::setNoRenderTarget(devCon);

    devCon->Flush(); //Release everything in real time

    result = swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
    DVXFirebreak(result);

    backBuffer.setPort(width, height);
    result = makeBackBuffer();

    return result;
}

void RDevice::setBackBufferTarget()
{
    backBuffer.setAsRenderTarget(devCon);
}

HRESULT RDevice::swapBuffer(UINT flags)
{
    return swapChain->Present(1, flags);
}

ID3D11Device* RDevice::getDevice()
{
    return dev;
}

ID3D11DeviceContext* RDevice::getContext()
{
    return devCon;
}

D3D_FEATURE_LEVEL RDevice::getLevel()
{
    return supportedL;
}
