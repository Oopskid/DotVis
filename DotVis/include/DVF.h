//Core DotVis framework

//Direct3D
#ifndef D3DV_H
	#define D3DV_H
	#include "d3d11.h"
#endif

//IUnknown* release
template<typename R> void DVXClear(R& res)
{
	if (res)
	{
		res->Release();
		res = nullptr;
	}
}

template<typename F, typename... T> void DVXClear(F& first, T&... rest)
{
	DVXClear(first);
	DVXClear(rest...);
}