#include "pch.h"
#include "Data/Files.h"

using namespace DVF;

bool Data::findFileRecursive(std::wstring& foundPath, const std::wstring& file, std::vector<std::wstring> extensions, WLiteral cd)
{
	namespace fs = std::filesystem;

	//Cache extensions
	std::map<std::wstring, size_t> extensionMap;
	for (size_t i = 0; i < extensions.size(); i++)
	{
		extensionMap.insert(std::make_pair(extensions[i], i));
	}

	//Iterate directories
	size_t bestExtension = ~0; //(use 'infinity' as null)
	size_t bestLevel = NULL;
	fs::recursive_directory_iterator start(cd ? cd : fs::current_path());
	fs::recursive_directory_iterator end = fs::end(start);
	for (auto it = start; it != end; it++)
	{
		//If detect depth change and result is pending, return
		if ((bestExtension != ~0) && bestLevel != it.depth()) { return true; }

		const fs::path& thisPath = it->path();
		//Get same file
		if (thisPath.has_filename() && thisPath.stem() == file)
		{
			//Return without extensions
			if (extensions.size() <= 0) { foundPath = thisPath.wstring(); return true; }

			//Check for extensions
			if (thisPath.has_extension())
			{
				auto extensionIt = extensionMap.find(thisPath.extension().wstring());
				if (extensionIt != extensionMap.end())
				{
					//If best extension found then no need to continue searching
					if (extensionIt->second <= 0) { foundPath = thisPath.wstring(); return true; }

					//Instead cache if better result
					if (extensionIt->second < bestExtension)
					{
						bestExtension = extensionIt->second;
						bestLevel = it.depth();

						foundPath = thisPath.wstring();
					}
				}
			}
		}
	}

	return bestExtension != ~0;
}
