#include "renderTarget.h"
#include <iostream>

namespace Funny
{
	RenderTarget::RenderTarget(unsigned int width, unsigned int height, GLenum type, unsigned int nrColorAttachments, bool depthAndStencil)
	{
		Width = width;
		Height = height;
		Type = type;
		glGenFramebuffers(1, &ID);
		glBindFramebuffer(GL_FRAMEBUFFER, ID);
		for (unsigned int i = 0; i < nrColorAttachments; ++i)
		{
			Texture texture;
			texture.FilterMax = GL_LINEAR;
			texture.FilterMin = GL_LINEAR;
			texture.WrapS = GL_CLAMP_TO_EDGE;
			texture.WrapT = GL_CLAMP_TO_EDGE;
			texture.Mipmapping = false;

			GLenum internalFormat = GL_RGBA;
			if (type == GL_HALF_FLOAT)
			{
				internalFormat = GL_RGBA16F;
			}
			else if(type == GL_FLOAT)
			{
				internalFormat = GL_RGBA32F;
			}
			texture.Generate(width, height, internalFormat, GL_RGBA, type, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture.ID, 0);
			mColorAttachments.push_back(texture);
		}

		HasDepthAndStencil = depthAndStencil;
		if (depthAndStencil)
		{
			Texture texture;
			texture.FilterMin = GL_LINEAR;
			texture.FilterMax = GL_LINEAR;
			texture.WrapS = GL_CLAMP_TO_EDGE;
			texture.WrapT = GL_CLAMP_TO_EDGE;
			texture.Mipmapping = false;
			texture.Generate(width, height, GL_DEPTH_STENCIL, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture.ID, 0);
			mDepthStencil = texture;
		}
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "Frame buffer not complete." << std::endl;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Texture* RenderTarget::GetDepthStencilTexture()
	{
		return &mDepthStencil;
	}

	Texture* RenderTarget::GetColorTexture(unsigned int index)
	{
		if (index < mColorAttachments.size())
			return &mColorAttachments[index];
		else
		{
			std::cout << "RenderTarget color texture requested, but not available: " <<std::endl;
			return nullptr;
		}
	}

	void RenderTarget::Resize(unsigned int width, unsigned int height)
	{
		Width = width;
		Height = height;

		for (unsigned int i = 0; i < mColorAttachments.size(); ++i)
		{
			mColorAttachments[i].Resize(width, height);
		}
		// generate Depth/Stencil texture if requested
		if (HasDepthAndStencil)
		{
			mDepthStencil.Resize(width, height);
		}
	}

	void RenderTarget::SetTarget(GLenum target)
	{
		mTarget = target;
	}
}