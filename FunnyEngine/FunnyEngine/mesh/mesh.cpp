#include "mesh.h"

#include "../glad/glad.h"

namespace Funny
{
	Mesh::Mesh()
	{

	}

	Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices)
	{
		Position = positions;
		Indices = indices;
	}

	Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<unsigned int> indices)
	{
		Position = positions;
		UV = uv;
		Indices = indices;
	}

	Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<unsigned int> indices)
	{
		Position = positions;
		UV = uv;
		Normals = normals;
		Indices = indices;
	}

	Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents, std::vector<unsigned int> indices)
	{
		Position = positions;
		UV = uv;
		Normals = normals;
		Tangents = tangents;
		Bitangents = bitangents;
		Indices = indices;
	}

	void Mesh::SetPosition(std::vector<glm::vec3> positions)
	{
		Position = positions;
	}
	
	void Mesh::SetUVs(std::vector<glm::vec2> uv)
	{
		UV = uv;
	}

	void Mesh::SetNormals(std::vector<glm::vec3> normals)
	{
		Normals = normals;
	}
	
	void Mesh::SetTangents(std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents)
	{
		Tangents = tangents;
		Bitangents = bitangents;
	}

	void Mesh::Finalize(bool interleaved)
	{
		if (!mVAO)
		{
			glGenVertexArrays(1, &mVAO);
			glGenBuffers(1, &mVBO);
			glGenBuffers(1, &mEBO);
		}

		// process buffer data as interleaved or segregate when specified
		std::vector<float> data;
		if (interleaved)
		{
			for (int i = 0; i < Position.size(); i++)
			{
				data.push_back(Position[i].x);
				data.push_back(Position[i].y);
				data.push_back(Position[i].z);

				if (UV.size() > 0)
				{
					data.push_back(UV[i].x);
					data.push_back(UV[i].y);
				}
				if (Normals.size() > 0)
				{
					data.push_back(Normals[i].x);
					data.push_back(Normals[i].y);
					data.push_back(Normals[i].z);
				}
				if (Tangents.size() > 0)
				{
					data.push_back(Tangents[i].x);
					data.push_back(Tangents[i].y);
					data.push_back(Tangents[i].z);
				}
				if (Bitangents.size() > 0)
				{
					data.push_back(Bitangents[i].x);
					data.push_back(Bitangents[i].y);
					data.push_back(Bitangents[i].z);
				}
			}
		}
		else
		{
			for (int i = 0; i < Position.size(); ++i)
			{
				data.push_back(Position[i].x);
				data.push_back(Position[i].y);
				data.push_back(Position[i].z);
			}
			for (int i = 0; i < UV.size(); ++i)
			{
				data.push_back(UV[i].x);
				data.push_back(UV[i].y);
			}
			for (int i = 0; i < Normals.size(); ++i)
			{
				data.push_back(Normals[i].x);
				data.push_back(Normals[i].y);
				data.push_back(Normals[i].z);
			}
			for (int i = 0; i < Tangents.size(); ++i)
			{
				data.push_back(Tangents[i].x);
				data.push_back(Tangents[i].y);
				data.push_back(Tangents[i].z);
			}
			for (int i = 0; i < Bitangents.size(); ++i)
			{
				data.push_back(Bitangents[i].x);
				data.push_back(Bitangents[i].y);
				data.push_back(Bitangents[i].z);
			}
		}
		glBindVertexArray(mVAO);
		glBindBuffer(GL_VERTEX_ARRAY, mVBO);
		glBufferData(GL_VERTEX_ARRAY, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

		if (Indices.size() > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int),&Indices[0], GL_STATIC_DRAW);
		}

		if (interleaved)
		{
			size_t stride = 3 * sizeof(float);
			if (UV.size() > 0) stride += 2 * sizeof(stride);
			if (Normals.size() > 0)    stride += 3 * sizeof(float);
			if (Tangents.size() > 0)   stride += 3 * sizeof(float);
			if (Bitangents.size() > 0) stride += 3 * sizeof(float);

			size_t offset = 0;
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 3 * sizeof(float);
			if (UV.size() > 0)
			{
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
				offset += 2 * sizeof(float);
			}
			if (Normals.size() > 0)
			{
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
				offset += 3 * sizeof(float);
			}
			if (Tangents.size() > 0)
			{
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
				offset += 3 * sizeof(float);
			}
			if (Bitangents.size() > 0)
			{
				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
				offset += 3 * sizeof(float);
			}
		}
		else
		{
			size_t offset = 0;
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += Position.size() * sizeof(float);
			if (UV.size() > 0)
			{
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
				offset += UV.size() * sizeof(float);
			}
			if (Normals.size() > 0)
			{
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
				offset += Normals.size() * sizeof(float);
			}
			if (Tangents.size() > 0)
			{
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
				offset += Tangents.size() * sizeof(float);
			}
			if (Bitangents.size() > 0)
			{
				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
				offset += Bitangents.size() * sizeof(float);
			}
		}

		glBindVertexArray(0);
	}

	void Mesh::caculateNormals(bool smooth /* = true */)
	{

	}

	void Mesh::caculateTangents()
	{

	}
}