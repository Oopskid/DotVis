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
		void fromFile(const std::string& path, RDevice* rdevice, ShaderBuild::ShaderComponents* buildRules = nullptr);


	};
}