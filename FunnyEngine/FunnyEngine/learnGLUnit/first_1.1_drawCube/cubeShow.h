#pragma once

#include "../GLSample.h"
#include "../../shading/shader.h"
#include "../../shading/texture.h"


class CubeShow : public GLSample
{
public:
	CubeShow();

	~CubeShow();

public:
	virtual void Init();

	virtual void Draw(int windowW, int windowH);

	virtual void Destroy();

private:
	Funny::Shader mShader;
	Funny::Texture mTexture1;
	Funny::Texture mTexture2;
	GLuint mVAO;
	GLuint mVBO;
	GLuint mEBO;

};