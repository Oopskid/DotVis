#pragma once

//Structures
#include "ShaderPart.h"

namespace DVF
{
	class ComputeSh : public ShaderPart
	{
		public:
		ComputeSh();

		ID3D11ComputeShader* getShader();

		//Note:: could be made more generic with lambda for more shaders
		HRESULT fromFile(const std::wstring& path, RDevice* rdev, ShaderBuild::ShaderComponents* buildRules = &ShaderBuild::COMPUTESH_STANDARD_RULES);
		HRESULT fromFileSimple(const std::wstring name, RDevice* rdev, Data::WLiteral cd = nullptr, ShaderBuild::ShaderComponents* buildRules = &ShaderBuild::COMPUTESH_STANDARD_RULES);

		//Run the compute shader
		void deploy(RDevice* rdev, UINT groupX, UINT groupY = 0, UINT groupZ = 0);
	};
}