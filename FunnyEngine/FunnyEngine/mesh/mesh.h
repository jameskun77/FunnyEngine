#pragma once

#include <vector>
#include <functional>

#include "../glm/glm.hpp"

namespace Funny
{
	enum TOPOLOGY
	{
		POINTS,
		LINES,
		LINES_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
	};

	class Mesh
	{
	public:
		unsigned int mVAO;
		unsigned int mVBO;
		unsigned int mEBO;

	public:
		std::vector<glm::vec3> Position;
		std::vector<glm::vec2> UV;
		std::vector<glm::vec3> Normals;
		std::vector<glm::vec3> Tangents;
		std::vector<glm::vec3> Bitangents;

		TOPOLOGY Topology = TRIANGLES;

		std::vector<unsigned int> Indices;

		Mesh();
		Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices);
		Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<unsigned int> indices);
		Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<unsigned int> indices);
		Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents, std::vector<unsigned int> indices);

		void SetPosition(std::vector<glm::vec3> positions);
		void SetUVs(std::vector<glm::vec2> uv);
		void SetNormals(std::vector<glm::vec3> normals);
		void SetTangents(std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents);

		// commits all buffers and attributes to the GPU driver
		void Finalize(bool interleaved = true);

		// generate triangulated mesh from signed distance field
		void FromSDF(std::function<float(glm::vec3)>& sdf, float maxDistance, uint16_t gridResolution);

	private:
		void caculateNormals(bool smooth = true);
		void caculateTangents();
	};
}