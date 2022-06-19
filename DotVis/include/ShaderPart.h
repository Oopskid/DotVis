#pragma once

//Structures
#include <string>

//Dependencies
#include <fstream>
#include <filesystem>
#include "Files.h"
#include "ShaderComponents.h"
#include "ShaderBuilder.h"
#include "RDevice.h"

//Framework
#include "DVF.h"

namespace DVF
{
	//Standard structure for shader types
	class ShaderPart
	{
		public:
		~ShaderPart();

		void setTag(const std::string& newTag);

		protected:
		//Freeform reference to the source
		char* tag = nullptr;

		//Fetches a file, returns the input stream and success
		bool getFile(std::ifstream& in, const std::string& path, bool asContext = true);

		size_t fetchRaw(const std::string& path, BYTE** raw, bool asContext = true);
		HRESULT fetchRawCompile(const std::string& path, BYTE** raw, size_t& rawCount, LPCSTR model = nullptr, LPCSTR name = nullptr, ShaderBuild::ShaderComponents* compileRules = nullptr, UINT flags = D3DCOMPILE_ENABLE_STRICTNESS, bool asContext = true, bool cache = true);

		bool isCompiled(const std::string& path);

		void destroyTag();

		void terminateShader();

		void setShader(IUnknown* shader);

		//Returns the shader object
		template<typename T> T* getShader()
		{
			return dynamic_cast<T*>(shaderObj);
		}

		private:
		IUnknown* shaderObj = nullptr;
	};
}