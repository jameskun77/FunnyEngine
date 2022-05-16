#pragma once

class GLSample
{
public:
	GLSample() 
	{
	
	}

	virtual ~GLSample() 
	{

	}

public:
	virtual void Init() = 0;

	virtual void Draw(int windowW,int windowH) = 0;

	virtual void Destroy() = 0;
};