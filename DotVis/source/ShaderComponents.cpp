#include "pch.h"
#include "ShaderComponents.h"

using namespace DVF;
using namespace ShaderBuild;

ShaderComponents& ShaderComponents::addVersionThreshold(D3D_FEATURE_LEVEL min, LPCSTR versionModel)
{
	fallbackVersioning.insert(std::make_pair(min, versionModel));

	return *this;
}

LPCSTR ShaderComponents::getModel(D3D_FEATURE_LEVEL version)
{
	//Find the most suitable model version
	for (auto milestone = fallbackVersioning.rbegin(); milestone != fallbackVersioning.rend(); milestone++)
	{
		if (version >= milestone->first)
		{
			return milestone->second;
		}
	}

	return nullptr;
}

ShaderComponents& ShaderComponents::addDefinition(LPCSTR tag, LPCSTR definition)
{
	definitions.push_back({ tag, definition });

	return *this;
}

const D3D_SHADER_MACRO* ShaderComponents::getDefinitions() const
{
	return definitions.data();
}

ID3DInclude* ShaderComponents::getIncludes()
{
	return includes;
}

ID3D11ClassLinkage* ShaderComponents::getLinkage()
{
	return linkage;
}

LPCSTR ShaderComponents::getEntry()
{
	return entry;
}

size_t ShaderComponents::getDefCount() const
{
	return definitions.size();
}
