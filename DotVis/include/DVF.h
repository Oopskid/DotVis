//Core DotVis framework

//Direct3D
#ifndef D3DV_H
	#define D3DV_H

	//D3D Library linkage
	#pragma comment(lib,"d3d11")
	
	//D3D includes
	#include "d3d11.h"
#endif

#ifndef DVF_H
	#define DVF_H

	//Macro helpers
	#define DVXFirebreak(result) if(FAILED(result)) { return result; }

	//Function helpers
	namespace DVF
	{
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
	}

#endif