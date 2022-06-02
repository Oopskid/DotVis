//Framework
#include "DVF.h"

namespace DVF
{
	namespace Tex
	{
		//Metadata on texture resources
		typedef char ResourceFlags;
		static constexpr char OWNERSHIP_BASE = 0b00000001;
		static constexpr char OWNERSHIP_TARGET = 0b00000010;
		static constexpr char OWNERSHIP_VIEW = 0b00000100;

	}
}