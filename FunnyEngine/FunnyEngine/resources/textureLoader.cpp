#include "textureLoader.h"
#include "../shading/texture.h"
#include "../stb/stb_image.h"

#include <iostream>

namespace Funny
{
	Texture TextureLoader::LoadTexture(std::string path, GLenum target, GLenum internalFormat, bool srgb)
	{
		Texture texture;
		texture.Target = target;
		texture.InternalFormat = internalFormat;
		if (texture.InternalFormat == GL_RGB || texture.InternalFormat == GL_SRGB)
		{
			texture.InternalFormat = srgb ? GL_SRGB : GL_RGB;
		}

		if (texture.InternalFormat == GL_RGBA || texture.InternalFormat == GL_SRGB_ALPHA)
		{
			texture.InternalFormat = srgb ? GL_SRGB_ALPHA : GL_SRGB;
		}

		// flip textures on their y coordinate while loading
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
			{
				format = GL_RED;
			}
			else if (nrComponents == 3)
			{
				format = GL_RGB;
			}
			else if(nrComponents == 4)
			{
				format = GL_RGBA;
			}

			if (target == GL_TEXTURE_1D)
			{

			}else if (target == GL_TEXTURE_2D)
			{
				texture.Generate(width, height, internalFormat, format, GL_UNSIGNED_BYTE, data);
			}
			stbi_image_free(data);
		}
		else 
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
			return texture;
		}
		texture.Width = width;
		texture.Height = height;
		
		return texture;
	}
}