#pragma once

#include "renderer.h"
#include "../shading/texture.h"
#include "../glad/glad.h"

#include <vector>

namespace Funny
{
	class RenderTarget
	{
		friend Renderer;
	public:
		unsigned int ID;

		unsigned int Width;
		unsigned int Height;
		GLenum Type;

		bool HasDepthAndStencil;

	private:
		GLenum mTarget = GL_TEXTURE_2D;
		Texture mDepthStencil;
		std::vector<Texture> mColorAttachments;

	public:
		RenderTarget(unsigned int width, unsigned int height, GLenum type = GL_UNSIGNED_BYTE, unsigned int nrColorAttachments = 1, bool depthAndStencil = true);

		Texture *GetDepthStencilTexture();
		Texture *GetColorTexture(unsigned int index);

		void Resize(unsigned int width, unsigned int height);
		void SetTarget(GLenum target);
	};
}
