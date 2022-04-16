#pragma once

#include <vector>
#include "../glm/glm.hpp"

namespace Funny
{
	class Scene;
	class Mesh;
	class Material;

	/*
		An individual scene node that links a mesh to a material
	  to render the mesh with while at the same time
	  maintaining a parent-child hierarchy for transform
	  relations.

	  Each node can have any number of children (via a linked
	  list) and represents a single render entity in a
	  larger scene where each child transform on top of their
	  parent node.
	*/
	class SceneNode
	{
	public:
		//each Node contain relevant render state
		Mesh* mMesh;
		Material* mMaterial;

		glm::vec3 BoxMin = glm::vec3(-99999.0f);
		glm::vec3 BoxMax = glm::vec3(99999.0f);

	private:
		std::vector<SceneNode*> mChildren;
		SceneNode* mParent;

		//per node transform
		glm::mat4 mTransform;
		glm::mat4 mPreTransform;
		glm::vec3 mPosition = glm::vec3(0.0f);
		glm::vec4 mRotation; //axis-angle for now
		glm::vec3 mScale = glm::vec3(1.0f);

		// mark the current node's transform as dirty if it needs to be re-calculated this frame
		bool mDirty;

		// each node is uniquely identified by a 32-bit incrementing unsigned integer
		unsigned int mID;

		static unsigned int CounterID;

	public:
		SceneNode(unsigned int id);
		~SceneNode();

		// scene node transform
		void SetPosition(glm::vec3 position);
		void SetRotation(glm::vec4 rotation);
		void SetScale(glm::vec3 scale);
		void SetScale(float scale);
		glm::vec3 GetLocalPosition();
		glm::vec4 GetLocalRotation();
		glm::vec3 GetLocalScale();
		glm::vec3 GetWorldPosition();
		glm::vec3 GetWorldScale();

		//scene graph
		unsigned int GetID();
		void AddChild(SceneNode* node);
		void RemoveChild(unsigned int id);
		std::vector<SceneNode*> GetChildren();
		unsigned int GetChildCount();
		SceneNode* GetChild(unsigned int id);
		SceneNode* GetChildByIndex(unsigned int index);
		SceneNode* GetParent();

		// returns the transform of the current node combined with its parents transform.
		glm::mat4 GetTransform();
		glm::mat4 GetPrevTransform();

		// re-calculates this node and its children's transform components if its parent or the 
		// node itself is dirty.
		void UpdateTransform(bool updatePrevTransform = false);
	};
}