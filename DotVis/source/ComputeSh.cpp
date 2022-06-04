#include "pch.h"
#include "ComputeSh.h"

using namespace DVF;

ComputeSh::ComputeSh()
{

}

void ComputeSh::fromFile(const std::string& path, RDevice* rdevice, ShaderBuild::ShaderComponents* buildRules)
{
	HRESULT result = S_OK;

	BYTE* byteCode = nullptr;
	size_t codeLength = NULL;
	
	std::string impliedName = std::filesystem::path(path).filename().string();

	if (buildRules)
	{
		result = fetchRawCompile(path, &byteCode, codeLength,
			buildRules->getModel(rdevice->getLevel()), 
			_strdup(impliedName.c_str()), 
			buildRules);
	}
	else
	{
		//Greater possibility of failing
		result = fetchRaw(path, &byteCode, codeLength);
	}

	//Finally make the shader object
	if (codeLength && byteCode && SUCCEEDED(result))
	{
		ID3D11ComputeShader* computeShader = nullptr;
		result = rdevice->getDevice()->CreateComputeShader(byteCode, codeLength, buildRules ? buildRules->getLinkage() : nullptr, &computeShader);

		if (FAILED(result))
		{
			DVXClear(computeShader);
		}
		else
		{
			setShader(computeShader);
		}
	}

	delete[] byteCode;
}