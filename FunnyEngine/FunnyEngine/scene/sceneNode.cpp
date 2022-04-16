#include "sceneNode.h"

#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

namespace Funny {

	SceneNode::SceneNode(unsigned int id):mID(id)
	{

	}

	SceneNode::~SceneNode()
	{
		for (unsigned int i = 0; i < mChildren.size(); i++)
		{
			delete mChildren[i];
		}
	}

	void SceneNode::SetPosition(glm::vec3 position)
	{
		mPosition = position;
		mDirty = true;
	}

	void SceneNode::SetRotation(glm::vec4 rotation)
	{
		mRotation = rotation;
		mDirty = true;
	}

	void SceneNode::SetScale(glm::vec3 scale)
	{
		mScale = scale;
		mDirty = true;
	}

	void SceneNode::SetScale(float scale)
	{
		mScale = glm::vec3(scale);
		mDirty = true;
	}

	glm::vec3 SceneNode::GetLocalPosition()
	{
		return mPosition;
	}

	glm::vec4 SceneNode::GetLocalRotation()
	{
		return mRotation;
	}

	glm::vec3 SceneNode::GetLocalScale()
	{
		return mScale;
	}

	glm::vec3 SceneNode::GetWorldPosition()
	{
		glm::mat4 transform = GetTransform();
		glm::vec4 pos = transform * glm::vec4(mPosition, 1.0f);
		return glm::vec3(pos.x, pos.y, pos.z);
	}

	glm::vec3 SceneNode::GetWorldScale()
	{
		glm::mat4 transform = GetTransform();
		glm::vec3 scale = glm::vec3(transform[0][0], transform[1][1], transform[2][2]);
		if (scale.x < 0.0f) scale.x *= -1.0f;
		if (scale.y < 0.0f) scale.y *= -1.0f;
		if (scale.z < 0.0f) scale.z *= -1.0f;
		return scale;
	}

	unsigned int SceneNode::GetID()
	{
		return mID;
	}

	void SceneNode::AddChild(SceneNode* node)
	{
		//check if this child already has a parent,if so,first remove this scene node from its
		if (node->GetParent())
		{
			node->GetParent()->RemoveChild(node->mID);
		}
		node->mParent = this;
		mChildren.push_back(node);
	}

	void SceneNode::RemoveChild(unsigned int id)
	{
		auto it = std::find(mChildren.begin(), mChildren.end(), GetChild(id));
		if (it != mChildren.end())
			mChildren.erase(it);
	}

	std::vector<SceneNode*> SceneNode::GetChildren()
	{
		return mChildren;
	}

	unsigned int SceneNode::GetChildCount()
	{
		return mChildren.size();
	}

	SceneNode* SceneNode::GetChild(unsigned int id)
	{
		for (unsigned int i = 0; i < mChildren.size(); i++)
		{
			if (mChildren[i]->GetID() == id)
			{
				return mChildren[i];
			}
		}

		return nullptr;
	}

	SceneNode* SceneNode::GetChildByIndex(unsigned int index)
	{
		assert(index < mChildren.size());
		return mChildren[index];
	}

	SceneNode* SceneNode::GetParent()
	{
		return mParent;
	}

	glm::mat4 SceneNode::GetTransform()
	{
		if (mDirty)
		{
			UpdateTransform(false);
		}
		return mTransform;
	}

	glm::mat4 SceneNode::GetPrevTransform()
	{
		return mPreTransform;
	}

	void SceneNode::UpdateTransform(bool updatePrevTransform)
	{
		//if specified, store current transform as prev transform (for calculating motion vectors)
		if (updatePrevTransform)
		{
			mPreTransform = mTransform;
		}

		if (mDirty)
		{
			mTransform = glm::translate(mTransform, mPosition);
			mTransform = glm::rotate(mTransform, mRotation.w,glm::vec3(mRotation.x,mRotation.y,mRotation.z));
			mTransform = glm::scale(mTransform, mScale);
	
			if (mParent)
			{
				mTransform = mParent->mTransform * mTransform;
			}
		}

		for (int i = 0; i < mChildren.size(); ++i)
		{
			if (mDirty)
			{
				mChildren[i]->mDirty = true;
			}
			mChildren[i]->UpdateTransform(updatePrevTransform);
		}
		mDirty = false;
	}

}