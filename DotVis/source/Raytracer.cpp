#include "pch.h"
#include "Raytracer.h"

using namespace DVF;

Raytracer::Raytracer()
{
	
}

HRESULT Raytracer::init(RDevice* dev)
{
	return traceSh.fromFileSimple("TraceScene", dev);
}
