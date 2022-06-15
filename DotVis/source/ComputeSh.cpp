#include "pch.h"
#include "ComputeSh.h"

using namespace DVF;

ComputeSh::ComputeSh()
{

}

ID3D11ComputeShader* ComputeSh::getShader()
{
	return ShaderPart::getShader<ID3D11ComputeShader>();
}

HRESULT ComputeSh::fromFile(const std::string& path, RDevice* rdev, ShaderBuild::ShaderComponents* buildRules)
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

HRESULT ComputeSh::fromFileSimple(const std::string name, RDevice* rdev, ShaderBuild::ShaderComponents* buildRules, Data::Literal cd)
{
	std::string path;
	if (!Data::findFileRecursive(path, name, { ".cso", ".hlsl" }, cd)) { return STG_E_FILENOTFOUND; }

	return fromFile(path, rdev, buildRules);
}

void ComputeSh::deploy(RDevice* rdev, UINT groupX, UINT groupY, UINT groupZ)
{
	rdev->getContext()->Dispatch(groupX, groupY, groupZ);
}
