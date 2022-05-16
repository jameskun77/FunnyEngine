#include "commandBuffer.h"

#include "renderer.h"
#include "../camera/camera.h"
#include "../shading/material.h"
#include "../mesh/mesh.h"

#include <algorithm>
#include <tuple>

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
		
		// if material requires alpha support, add it to alpha render commands for later rendering.
		if (material->Blend)
		{
			material->Type = MATERIAL_CUSTOM;
			mAlphaRenderCommands.push_back(command);
		}
		else
		{
			// check the type of the material and process differently where necessary
			if (material->Type == MATERIAL_DEFAULT)
			{
				mDeferredRenderCommands.push_back(command);
			}
			else if (material->Type == MATERIAL_CUSTOM)
			{
				// check if this render target has been pushed before, if so add to vector, 
				// otherwise create new vector with this render target.
				if (mCustomRenderCommands.find(target) != mCustomRenderCommands.end())
					mCustomRenderCommands[target].push_back(command);
				else
				{
					mCustomRenderCommands[target] = std::vector<RenderCommand>();
					mCustomRenderCommands[target].push_back(command);
				}
			}
			else if (material->Type == MATERIAL_POST_PROCESS)
			{
				mPostProcessingRenderCommands.push_back(command);
			}
		}
	}

	void CommandBuffer::Clear()
	{
		mDeferredRenderCommands.clear();
		mCustomRenderCommands.clear();
		mPostProcessingRenderCommands.clear();
		mAlphaRenderCommands.clear();
	}

	// --------------------------------------------------------------------------------------------
	// custom per-element sort compare function used by the CommandBuffer::Sort() function.
	bool renderSortDeferred(const RenderCommand &a, const RenderCommand &b)
	{
		return a.Material->GetShader()->ID < b.Material->GetShader()->ID;
	}
	// sort render state
	bool renderSortCustom(const RenderCommand &a, const RenderCommand &b)
	{
		/*

		  We want strict weak ordering, which states that if two objects x and y are equivalent
		  then both f(x,y) and f(y,x) should be false. Thus when comparing the object to itself
		  the comparison should always equal false.

		  We also want to do multiple sort comparisons in a single pass, so we encapsulate all
		  relevant properties inside an n-tuple with n being equal to the number of sort queries
		  we want to do. The tuple < comparison operator initially compares its left-most element
		  and then works along the next elements of the tuple until an outcome is clear.

		  Another (non C++11) alternative is to write out both the < and > case with the == case
		  defaulting to false as in:

		  if(a1 < b1)
			return true;
		  if(b1 > a1)
			return false;

		  if(a2 < b2)
			return true;
		  if(b2 > a2)
			return false;
		  [...] and so on for each query you want to perform
		  return false;

		*/
		return std::make_tuple(a.Material->Blend, a.Material->GetShader()->ID) <
			std::make_tuple(b.Material->Blend, b.Material->GetShader()->ID);
	}

	void CommandBuffer::Sort()
	{
		std::sort(mDeferredRenderCommands.begin(), mDeferredRenderCommands.end(), renderSortDeferred);
		for (auto rtIt = mCustomRenderCommands.begin(); rtIt != mCustomRenderCommands.end(); rtIt++)
		{
			std::sort(rtIt->second.begin(), rtIt->second.end(), renderSortCustom);
		}
	}

	std::vector<RenderCommand> CommandBuffer::GetDeferredRenderCommands(bool cull)
	{
		if (cull)
		{
			std::vector<RenderCommand> commands;
			for (auto it = mDeferredRenderCommands.begin(); it != mDeferredRenderCommands.end(); ++it)
			{
				RenderCommand command = *it;
				//todo ÔÝÊ±×¢ÊÍ´úÂë
				/*if (mRenderer->GetCamera()->Frustum.Intersect(command.BoxMin, command.BoxMax)) {
					commands.push_back(command);
				}*/
			}
			return commands;
		}
		else
		{
			return mDeferredRenderCommands;
		}
	}

	std::vector<RenderCommand> CommandBuffer::GetAlphaRenderCommands(bool cull)
	{
		if (cull)
		{
			std::vector<RenderCommand> commands;
			for (auto it = mAlphaRenderCommands.begin(); it != mAlphaRenderCommands.end(); ++it)
			{
				RenderCommand command = *it;
				//todo ÔÝÊ±×¢ÊÍ´úÂë
				/*if (mRenderer->GetCamera()->Frustum.Intersect(command.BoxMin, command.BoxMax)) {
					commands.push_back(command);
				}*/
			}
			return commands;
		}
		else
		{
			return mAlphaRenderCommands;
		}
	}

	std::vector<RenderCommand> CommandBuffer::GetCustomRenderCommands(RenderTarget *target, bool cull)
	{
		// only cull when on main/null render target
		if (target == nullptr && cull)
		{
			std::vector<RenderCommand> commands;
			for (auto it = mCustomRenderCommands[target].begin(); it != mCustomRenderCommands[target].end(); ++it)
			{
				RenderCommand command = *it;
				//todo ÔÝÊ±×¢ÊÍ´úÂë
				/*if (mRenderer->GetCamera()->Frustum.Intersect(command.BoxMin, command.BoxMax)) {
					commands.push_back(command);
				}*/
			}
			return commands;
		}
		else
		{
			return mCustomRenderCommands[target];
		}
	}

	std::vector<RenderCommand> CommandBuffer::GetPostProcessingRenderCommands()
	{
		return mPostProcessingRenderCommands;
	}

	std::vector<RenderCommand> CommandBuffer::GetShadowCastRenderCommands()
	{
		std::vector<RenderCommand> commands;
		for (auto it = mDeferredRenderCommands.begin(); it != mDeferredRenderCommands.end(); ++it)
		{
			if (it->Material->ShadowCast)
			{
				commands.push_back(*it);
			}
		}
		for (auto it = mCustomRenderCommands[nullptr].begin(); it != mCustomRenderCommands[nullptr].end(); ++it)
		{
			if (it->Material->ShadowCast)
			{
				commands.push_back(*it);
			}
		}
		return commands;
	}
}