#pragma once

#include "../glad/glad.h"
#include <string>

namespace Funny
{
	class Texture;

	class TextureLoader
	{
	public:
		static Texture LoadTexture(std::string path, GLenum target, GLenum internalFormat, bool srgb = false);
	};
}
