#include "pch.h"
#include "Shaders/ComputeSh.h"

using namespace DVF;
using namespace DVF::ShaderBuild;

ComputeSh::ComputeSh()
{

}

ID3D11ComputeShader* ComputeSh::getShader()
{
	return ShaderPart::getShader<ID3D11ComputeShader>();
}

HRESULT ComputeSh::fromFile(const std::wstring& path, RDevice* rdev, ShaderBuild::ShaderComponents* buildRules)
{
	HRESULT result = S_OK;

	BYTE* byteCode = nullptr;
	size_t codeLength = NULL;
	
	std::string impliedName = std::filesystem::path(path).stem().string();

	if (buildRules)
	{
		result = fetchRawCompile(path, &byteCode, codeLength,
			buildRules->getModel(rdev->getLevel()), 
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
		result = rdev->getDevice()->CreateComputeShader(byteCode, codeLength, buildRules ? buildRules->getLinkage() : nullptr, &computeShader);

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

	return result;
}

HRESULT ComputeSh::fromFileSimple(const std::wstring name, RDevice* rdev, Data::WLiteral cd, ShaderBuild::ShaderComponents* buildRules)
{
	std::wstring path;
	if (!Data::findFileRecursive(path, name, { PRECOMPILED_EXT, FORMATTED_EXT }, cd)) { return STG_E_FILENOTFOUND; }

	return fromFile(path, rdev, buildRules);
}

void ComputeSh::deploy(RDevice* rdev, UINT groupX, UINT groupY, UINT groupZ)
{
	rdev->getContext()->Dispatch(groupX, groupY, groupZ);
}
