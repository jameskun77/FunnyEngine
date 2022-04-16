#include "material.h"

namespace Funny
{
	Material::Material()
	{

	}

	Material::Material(Shader* shader)
	{
		mShader = shader;
	}

	Shader* Material::GetShader()
	{
		return mShader;
	}

	void Material::SetShader(Shader* shader)
	{
		mShader = shader;
	}

	Material Material::Copy()
	{
		Material copy(mShader);

		copy.Type = Type;
		copy.Color = Color;

		copy.DepthTest = DepthTest;
		copy.DepthWrite = DepthWrite;
		copy.DepthCompare = DepthCompare;

		copy.Cull = Cull;
		copy.CullFace = CullFace;
		copy.CullWindingOrder = CullWindingOrder;

		copy.Blend = Blend;
		copy.BlendSrc = BlendSrc;
		copy.BlendDst = BlendDst;
		copy.BlendEquation = BlendEquation;

		copy.mUniforms = mUniforms;
		copy.mSamplerUniforms = mSamplerUniforms;

		return copy;
	}

	void Material::SetBool(std::string name, bool value)
	{
		mUniforms[name].Type = SHADER_TYPE_BOOL;
		mUniforms[name].Bool = value;
	}

	void Material::SetInt(std::string name, int value)
	{
		mUniforms[name].Type = SHADER_TYPE_INT;
		mUniforms[name].Int = value;
	}

	void Material::SetFloat(std::string name, float value)
	{
		mUniforms[name].Type = SHADER_TYPE_FLOAT;
		mUniforms[name].Float = value;
	}

	void Material::SetTexture(std::string name, Texture* value, unsigned int unit)
	{
		mSamplerUniforms[name].Unit = unit;
		switch (value->Target)
		{
		case GL_TEXTURE_1D:
			mSamplerUniforms[name].Type = SHADER_TYPE_SAMPLER1D;
			break;
		case GL_TEXTURE_2D:
			mSamplerUniforms[name].Type = SHADER_TYPE_SAMPLER2D;
			break;
		case GL_TEXTURE_3D:
			mSamplerUniforms[name].Type = SHADER_TYPE_SAMPLER3D;
			break;
		default:
			break;
		}
	}

	void Material::SetVector(std::string name, glm::vec2 value)
	{
		mUniforms[name].Type = SHADER_TYPE_VEC2;
		mUniforms[name].Vec2 = value;
	}

	void Material::SetVector(std::string name, glm::vec3 value)
	{
		mUniforms[name].Type = SHADER_TYPE_VEC3;
		mUniforms[name].Vec3 = value;
	}

	void Material::SetVector(std::string name, glm::vec4 value)
	{
		mUniforms[name].Type = SHADER_TYPE_VEC4;
		mUniforms[name].Vec4 = value;
	}

	void Material::SetMatrix(std::string name, glm::mat2 value)
	{
		mUniforms[name].Type = SHADER_TYPE_MAT2;
		mUniforms[name].Mat2 = value;
	}

	void Material::SetMatrix(std::string name, glm::mat3 value)
	{
		mUniforms[name].Type = SHADER_TYPE_MAT3;
		mUniforms[name].Mat3 = value;
	}

	void Material::SetMatrix(std::string name, glm::mat4 value)
	{
		mUniforms[name].Type = SHADER_TYPE_MAT4;
		mUniforms[name].Mat4 = value;
	}

	std::map<std::string, UniformValue>* Material::GetUniforms()
	{
		return &mUniforms;
	}

	std::map<std::string, UniformValueSampler>* Material::GetSamplerUniforms()
	{
		return &mSamplerUniforms;
	}
}