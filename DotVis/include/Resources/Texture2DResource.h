#pragma once

//Structures
#include <string>

//Framework
#include "Core/DVF.h"
#include "Builders/TextureCommon.h"

namespace DVF
{
	class Texture2DResource
	{
		public:
		Texture2DResource();
		Texture2DResource(Texture2DResource&& parent);
		~Texture2DResource();

		ID3D11Texture2D* getTexture();
		ID3D11RenderTargetView* getTarget();
		ID3D11ShaderResourceView* getView();

		std::wstring getName();

		//Reference copy, NOT managed
		void borrowTexture(ID3D11Texture2D* loanedTexture);
		void borrowTarget(ID3D11RenderTargetView* loanedTarget);

		//Ownership, managed
		void holdTexture(ID3D11Texture2D* providedTexture);
		void holdTarget(ID3D11RenderTargetView* providedTarget);

		void release(); //Releases everything

		protected:
		void terminateTexture();
		void terminateTextureTarget();
		void terminateTextureView();

		std::wstring name; //Value to discriminate this resource

		ID3D11Texture2D* texture;
		ID3D11RenderTargetView* textureTarget;
		ID3D11ShaderResourceView* textureView;

		Tex::ResourceFlags flags;

		private:

	};
}