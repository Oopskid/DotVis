#pragma once

//Framework
#include "Core/DVF.h"

namespace DVF
{
	namespace Tex
	{
		//Metadata on texture resources
		typedef char ResourceFlags;
		enum Ownership
		{
			OWNERSHIP_BASE = 0b00000001,
			OWNERSHIP_TARGET = 0b00000010,
			OWNERSHIP_VIEW = 0b00000100
		};

	}
}