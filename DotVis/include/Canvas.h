#pragma once

//Structures
#include "Texture2DResource.h"

//Framework
#include "DVF.h"

namespace DVF
{
	//Representation of a texture with rendering capabilities
	class Canvas : public Texture2DResource
	{
		public:
		Canvas();

		protected:
		//Depth stencil works for 2d and 3d
		ID3D11Texture2D* depthStencil;
		ID3D11DepthStencilView* depthStencilView;

		//Metadata
		D3D11_TEXTURE2D_DESC textureDesc; //For automatic resizing and other dynamic adjustments
		D3D11_VIEWPORT view; //Porthole onto the texture

		private:
		
	};
}