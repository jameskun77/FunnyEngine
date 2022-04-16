#include "commandBuffer.h"

namespace Funny
{
	CommandBuffer::CommandBuffer(Renderer* renderer)
	{
		mRenderer = renderer;
	}

	CommandBuffer::~CommandBuffer()
	{
		Clear();
	}

	void CommandBuffer::Push(Mesh* mesh, Material* material, glm::mat4 transform, glm::mat4 prevTransform, glm::vec3 boxMin, glm::vec3 boxMax, RenderTarget* target)
	{
		RenderCommand command = {};
		command.Mesh = mesh;
		command.Material = material;
		command.Transforam = transform;
		command.PrevTransform = prevTransform;
		command.BoxMax = boxMax;
		command.BoxMin = boxMin;
		
		
	}

	void CommandBuffer::Clear()
	{
		
	}

	void CommandBuffer::Sort()
	{

	}

	std::vector<RenderCommand> CommandBuffer::GetDeferredRenderCommands(bool cull)
	{

	}

	std::vector<RenderCommand> CommandBuffer::GetAlphaRenderCommands(bool cull)
	{

	}

	std::vector<RenderCommand> CommandBuffer::GetCustomRenderCommands(RenderTarget *target, bool cull)
	{

	}

	std::vector<RenderCommand> CommandBuffer::GetPostProcessingRenderCommands()
	{

	}

	std::vector<RenderCommand> CommandBuffer::GetShadowCastRenderCommands()
	{

	}
}