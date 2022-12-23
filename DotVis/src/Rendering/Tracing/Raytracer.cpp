#include "pch.h"
#include "Rendering/Tracing/Raytracer.h"

using namespace DVF;

Raytracer::Raytracer()
{
	
}

HRESULT Raytracer::init(RDevice* dev, const std::wstring& resourceDir)
{
	return traceSh.fromFileSimple(L"TraceScene", dev, resourceDir.data());
}

void DVF::Raytracer::use(RDevice* dev)
{
	traceSh.deploy(dev, 1000, 1000);
}
