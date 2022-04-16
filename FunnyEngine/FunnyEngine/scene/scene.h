#pragma once

namespace Funny
{
	class SceneNode;
	class Material;
	class Mesh;

	/*
		The global scene object.holds a root node to which other scene nodes can be attached.

	*/

	class Scene
	{
	public:
		static SceneNode* Root;
		static unsigned int CounterID;

	public:
		static void Clear(); //clear all scene node

		static SceneNode* MakeSceneNode(); //build empty node

		static SceneNode* MakeSceneNode(Mesh* mesh, Material* material);

		static SceneNode* MakeSceneNode(SceneNode* node);

		static void DeleteSceneNode(SceneNode* node);
	};
}
