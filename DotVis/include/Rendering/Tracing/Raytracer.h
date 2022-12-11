#pragma once

//Structures
#include "Shaders/ComputeSh.h"
#include "Rendering/RDevice.h"

//Framework
#include "Core/DVF.h"

namespace DVF
{
	class Raytracer
	{
		public:
		Raytracer();

		HRESULT init(RDevice* dev);

		void use(RDevice* dev);

		private:
		ComputeSh traceSh;
		ID3D11ShaderResourceView* buffy;
	};
}