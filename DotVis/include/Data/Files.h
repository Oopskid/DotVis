#pragma once

//Structures
#include <string>
#include <vector>
#include <map>

//Dependencies
#include <filesystem>

//Framework
#include "Core/DVF.h"

namespace DVF
{
	namespace Data
	{
		typedef char* CString; //C-style string
		typedef const char* CStringC; //Constant c-style string
		typedef const char* const Literal; //C-style string which should not be deleted

		typedef wchar_t* CWString;
		typedef const wchar_t* CWStringC;
		typedef const wchar_t* const WLiteral;

		//Searches for a valid file. Returns path in order of prefered extension then sub folder. null directory = current directory. Empty extensions = ANY. Returns if successful
		bool findFileRecursive(std::wstring& foundPath, const std::wstring& file, std::vector<std::wstring> extensions, WLiteral cd = nullptr);

	}
}