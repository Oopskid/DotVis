#pragma once

//Structures
#include "ComputeSh.h"
#include "RDevice.h"

//Framework
#include "DVF.h"

namespace DVF
{
	class Raytracer
	{
		public:
		Raytracer();

		HRESULT init(RDevice* dev);

		private:
		ComputeSh traceSh;

	};
}