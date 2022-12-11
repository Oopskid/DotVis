//Core DotVis framework

//Direct3D
#ifndef D3DV_H
	#define D3DV_H

	//D3D Library linkage
	#pragma comment(lib,"d3d11")
	#pragma comment(lib,"d3dcompiler")
	
	//D3D includes
	#include "d3d11.h"
	#include "d3dcompiler.h"
#endif

#ifndef DVF_H
	#define DVF_H

	//Includes
	#include <cassert>

	//Macro helpers
	#define DVXFirebreak(result) if(FAILED(result)) { return result; }
	#define isDebug (DEBUG || _DEBUG)

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

		//Complex assert (can be redirected)
		inline bool DVAssert(bool expression, const char* txt)
		{
			#if isDebug
				assert(expression && txt);
				return false;
			#else
				return !expression;
			#endif
		}
	}

#endif