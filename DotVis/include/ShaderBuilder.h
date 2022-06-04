#pragma once

//Dependencies
#include "ShaderComponents.h"

//Framework
#include "DVF.h"

namespace DVF
{
	namespace ShaderBuild
	{
		HRESULT compileShader(ID3DBlob** byteResult, const BYTE* source, size_t sourceLen, ShaderComponents& rules, LPCSTR model, LPCSTR tag = nullptr, UINT flags = D3DCOMPILE_ENABLE_STRICTNESS, ID3DBlob** errorResult = nullptr);

		//Standards
		static ShaderComponents VERTEXSH_STANDARD_RULES;
		static ShaderComponents PIXELSH_STANDARD_RULES;
		static ShaderComponents GEOMETRYSH_STANDARD_RULES;
		static ShaderComponents DOMAINSH_STANDARD_RULES;
		static ShaderComponents HULLSH_STANDARD_RULES;
		static ShaderComponents COMPUTESH_STANDARD_RULES;

		static constexpr const char* PRECOMPILE_EXT = ".cso";
	}
}