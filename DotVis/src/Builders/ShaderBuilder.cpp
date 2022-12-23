#include "pch.h"
#include "Builders/ShaderBuilder.h"

using namespace DVF;

HRESULT ShaderBuild::compileShader(ID3DBlob** byteResult, const BYTE* source, size_t sourceLen, ShaderComponents& rules, LPCSTR model, LPCSTR tag, UINT flags, ID3DBlob** errorResult)
{
	HRESULT result = S_OK;

	#if isDebug
		if (errorResult) { flags |= D3DCOMPILE_DEBUG; }
	#endif

	result = D3DCompile(source, sourceLen, tag, rules.getDefinitions(), rules.getIncludes(), rules.getEntry(), model, flags, NULL, byteResult, errorResult);

	if (FAILED(result))
	{
		if (byteResult)
		{
			DVXClear(*byteResult);
		}

		//Report errors only in debug mode. Error log MUST be destroyed externally
		#if isDebug
		if (errorResult)
		{
			OutputDebugStringA((char*)(*errorResult)->GetBufferPointer());
		}
		#endif	
	}

	return result;
}
