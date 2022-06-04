#pragma once

//Structures
#include "ShaderPart.h"

namespace DVF
{
	class ComputeSh : public ShaderPart
	{
		public:
		ComputeSh();

		//Note:: could be made more generic with lambda for more shaders
		HRESULT fromFile(const std::string& path, RDevice* rdevice, ShaderBuild::ShaderComponents* buildRules = &ShaderBuild::COMPUTESH_STANDARD_RULES);
		HRESULT fromFileSimple(const std::string name, RDevice* rdevice, ShaderBuild::ShaderComponents* buildRules = &ShaderBuild::COMPUTESH_STANDARD_RULES, Data::Literal cd = nullptr);

	};
}