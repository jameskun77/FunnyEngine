#pragma once

#include "renderCommand.h"
#include "../glm/glm.hpp"

#include <map>
#include <vector>

namespace Funny
{
	class Renderer;
	class Mesh;
	class Material;
	class RenderTarget;

	class CommandBuffer
	{
	private:
		Renderer* mRenderer;

		std::vector<RenderCommand> mDeferredRenderCommands;
		std::vector<RenderCommand> mAlphaRenderCommands;
		std::vector<RenderCommand> mPostProcessingRenderCommands;
		std::map<RenderTarget*, std::vector<RenderCommand>> mCustomRenderCommands;

	public:
		CommandBuffer(Renderer* renderer);
		~CommandBuffer();

		void Push(Mesh* mesh, Material* material, glm::mat4 transform = glm::mat4(1.0f), glm::mat4 prevTransform = glm::mat4(1.0f), glm::vec3 boxMin = glm::vec3(-99999.0f), glm::vec3 boxMax = glm::vec3(99999.0f), RenderTarget* target = nullptr);

		void Clear();

		void Sort();

		std::vector<RenderCommand> GetDeferredRenderCommands(bool cull = false);

		std::vector<RenderCommand> GetAlphaRenderCommands(bool cull = false);

		// returns the list of custom render commands per render target.
		std::vector<RenderCommand> GetCustomRenderCommands(RenderTarget *target, bool cull = false);

		// returns the list of post-processing render commands.
		std::vector<RenderCommand> GetPostProcessingRenderCommands();

		// returns the list of all render commands with mesh shadow casting
		std::vector<RenderCommand> GetShadowCastRenderCommands();
	};
}