#pragma once
#include "../glm/glm.hpp"

namespace Funny
{
	class Mesh;
	class Material;

	struct RenderCommand
	{
		glm::mat4 Transforam;
		glm::mat4 PrevTransform;
		Mesh* Mesh;
		Material* Material;
		glm::vec3 BoxMin;
		glm::vec3 BoxMax;
	};
}
