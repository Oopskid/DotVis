#pragma once

//Structures
#include <string>
#include <vector>
#include <map>

//Dependencies
#include <filesystem>

//Framework
#include "DVF.h"

namespace DVF
{
	namespace Data
	{
		typedef char* CString; //C-style string
		typedef const char* CStringC; //Constant c-style string
		typedef const char* const Literal; //C-style string which should not be deleted

		//Searches for a valid file. Returns path in order of prefered extension then sub folder. null directory = current directory. Empty extensions = ANY. Returns if successful
		bool findFileRecursive(std::string& foundPath, const std::string& file, std::vector<std::string> extensions, Literal cd = nullptr);
	}
}