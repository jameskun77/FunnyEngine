#include "scene.h"
#include "sceneNode.h"

#include <stack>

namespace Funny
{
	SceneNode* Scene::Root = new SceneNode(0);
	unsigned int Scene::CounterID = 0;

	void Scene::Clear()
	{
		Scene::DeleteSceneNode(Root);
		Scene::Root = new SceneNode(0);
	}

	SceneNode* Scene::MakeSceneNode()
	{
		SceneNode* node = new SceneNode(Scene::CounterID++);
		Root->AddChild(node);
		return node;
	}

	SceneNode* Scene::MakeSceneNode(Mesh* mesh, Material* material)
	{
		SceneNode* node = new SceneNode(Scene::CounterID++);

		node->mMesh = mesh;
		node->mMaterial = material;

		Root->AddChild(node);
		return node;
	}

	SceneNode* Scene::MakeSceneNode(SceneNode* node)
	{
		SceneNode* newNode = new SceneNode(Scene::CounterID++);
		newNode->mMesh = node->mMesh;
		newNode->mMaterial = node->mMaterial;
		newNode->BoxMax = node->BoxMax;
		newNode->BoxMin = node->BoxMin;

		// traverse through the list of children and add them correspondingly
		std::stack<SceneNode*> nodeStack;
		for (unsigned int i = 0; i < node->GetChildCount(); i++)
		{
			nodeStack.push(node->GetChildByIndex(i));
		}
		while (!nodeStack.empty())
		{
			SceneNode* child = nodeStack.top();
			nodeStack.pop();

			SceneNode* newChild = new SceneNode(CounterID++);
			newChild->mMaterial = child->mMaterial;
			newChild->mMesh = child->mMesh;
			newChild->BoxMin = child->BoxMin;
			newChild->BoxMax = child->BoxMax;

			for (unsigned int i = 0; i < child->GetChildCount(); i++)
			{
				nodeStack.push(child->GetChildByIndex(i));
			}
		}

		Root->AddChild(newNode);
		return newNode;
	}

	void Scene::DeleteSceneNode(SceneNode* node)
	{
		if (node->GetParent())
		{
			node->GetParent()->RemoveChild(node->GetID());
		}

		delete node;
	}
}