#pragma once

#include "../glm/glm.hpp"

namespace Funny
{
	class Camera;

	struct FrustumPlane
	{
		glm::vec3 Normal;
		float D;

		void SetNormalD(glm::vec3 normal, glm::vec3 point)
		{
			Normal = glm::normalize(normal);
			D = -glm::dot(Normal, point);
		}

		float Distance(glm::vec3 point)
		{
			return glm::dot(Normal, point) + D;
		}
	};

	/*

	 Container object managing all 6 camera frustum planes as calculated from any Camera object.

	 The CameraFrustum allows to quickly determine (using simple collision primitives like point,
	 sphere, box) whether an object is within the frustum (or crossing the frustum's edge(s)).
	 This gives us the option to significantly reduce draw calls for objects that aren't visible
	 anyways. Note that the frustum needs to be re-calculated every frame.

   */
	class CameraFrustum
	{
	public:
		union
		{
			FrustumPlane Planes[6];
			struct
			{
				FrustumPlane Left;
				FrustumPlane Right;
				FrustumPlane Top;
				FrustumPlane Bottom;
				FrustumPlane Near;
				FrustumPlane Far;
			};
		};

	public:
		CameraFrustum() { } 

		void Update(Camera* camera);

		bool Intersect(glm::vec3 point);
		bool Intersect(glm::vec3 point, float radius);
		bool Intersect(glm::vec3 boxMin, glm::vec3 boxMax);
	};
}