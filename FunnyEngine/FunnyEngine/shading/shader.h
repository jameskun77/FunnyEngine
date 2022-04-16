#pragma once

#include <string>
#include <vector>

#include "../glm/glm.hpp"

#include "shadingType.h"

namespace Funny
{
	class Shader
	{
	public:
		unsigned int ID;
		std::string Name;

		std::vector<Uniform> Uniforms;
		std::vector<VertexAttribute> Attributes;

	public:
		Shader();
		Shader(std::string name, std::string vsCode, std::string fsCode, std::vector<std::string> defines = std::vector<std::string>());

		void Load(std::string name, std::string vsCode, std::string fsCode, std::vector<std::string> defines = std::vector<std::string>());

		void Use();

		bool HasUniform(std::string name);

		void SetInt(std::string location, int   value);
		void SetBool(std::string location, bool  value);
		void SetFloat(std::string location, float value);
		void SetVector(std::string location, glm::vec2  value);
		void SetVector(std::string location, glm::vec3  value);
		void SetVector(std::string location, glm::vec4  value);
		void SetVectorArray(std::string location, int size, const std::vector<glm::vec2>& values);
		void SetVectorArray(std::string location, int size, const std::vector<glm::vec3>& values);
		void SetVectorArray(std::string location, int size, const std::vector<glm::vec4>& values);
		void SetMatrix(std::string location, glm::mat2 value);
		void SetMatrix(std::string location, glm::mat3 value);
		void SetMatrix(std::string location, glm::mat4 value);
		void SetMatrixArray(std::string location, int size, glm::mat2* values);
		void SetMatrixArray(std::string location, int size, glm::mat3* values);
		void SetMatrixArray(std::string location, int size, glm::mat4* values);

	private:
		int getUniformLocation(std::string name);
	};
}