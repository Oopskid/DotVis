#pragma once

//Structure
#include <vector>
#include <map>

//Framework
#include "Core/DVF.h"

namespace DVF
{
	namespace ShaderBuild
	{
		class ShaderComponents
		{
			public:
			//Versioning
			ShaderComponents& addVersionThreshold(D3D_FEATURE_LEVEL min, LPCSTR versionModel);
			LPCSTR getModel(D3D_FEATURE_LEVEL version);

			//Macros
			ShaderComponents& addDefinition(LPCSTR tag, LPCSTR definition);
			size_t getDefCount() const;
			const D3D_SHADER_MACRO* getDefinitions() const;

			//Includes
			ID3DInclude* getIncludes();

			//Class linkage
			ID3D11ClassLinkage* getLinkage();

			//Entry point
			LPCSTR getEntry();
			private:
			//Macro definitions
			std::vector<D3D_SHADER_MACRO> definitions;
			//Shader model choices
			std::map<D3D_FEATURE_LEVEL, LPCSTR> fallbackVersioning;

			ID3D11ClassLinkage* linkage = nullptr;
			ID3DInclude* includes = D3D_COMPILE_STANDARD_FILE_INCLUDE;
			LPCSTR entry = nullptr;
		};

	}
}
