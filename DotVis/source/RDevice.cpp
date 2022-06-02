#include "pch.h"
#include "RDevice.h"

using namespace DVF;

RDevice::RDevice()
{

}

RDevice::~RDevice()
{
	DVXClear(swapChain);
}

HRESULT DVF::RDevice::create(UINT flags)
{
	if (dev || devCon) { return NTE_EXISTS; }

	HRESULT result = S_OK;
	#ifdef _DEBUG
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

HRESULT DVF::RDevice::makeSwapChain(HWND context, DXGI_FORMAT bufferFormat)
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
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    desc.OutputWindow = context;

    return makeSwapChain(context, desc);
}

HRESULT DVF::RDevice::makeSwapChain(HWND context, DXGI_SWAP_CHAIN_DESC options)
{
    if (!dev || !devCon) { return NTE_NOT_FOUND; }

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

HRESULT DVF::RDevice::swapBuffer(UINT flags)
{
    return swapChain->Present(1, flags);
}

ID3D11Device* DVF::RDevice::getDevice()
{
    return dev;
}

ID3D11DeviceContext* DVF::RDevice::getContext()
{
    return devCon;
}

D3D_FEATURE_LEVEL DVF::RDevice::getLevel()
{
    return supportedL;
}
