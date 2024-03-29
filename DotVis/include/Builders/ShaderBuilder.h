#pragma once

//Dependencies
#include "Shaders/ShaderComponents.h"
#include "Data/Files.h"

//Framework
#include "Core/DVF.h"

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

		static constexpr Data::WLiteral PRECOMPILED_EXT = L".cso";
		static constexpr Data::WLiteral FORMATTED_EXT = L".hlsl";
		static constexpr Data::WLiteral INTERFACE_EXT = L".hlsli";
	}
}