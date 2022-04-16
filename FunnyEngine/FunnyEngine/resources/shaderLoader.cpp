#include "shaderLoader.h"
#include <iostream>

namespace Funny
{
	Shader ShaderLoader::Load(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defines)
	{
		std::ifstream vsFile, fsFile;
		vsFile.open(vsPath);
		fsFile.open(fsPath);
		if (!vsFile.is_open() || !fsFile.is_open())
		{
			std::cout << "Shader failed load" << std::endl;
			return Shader();
		}

		std::string vsDirectory = vsPath.substr(0, vsPath.find_last_of("/\\"));
		std::string fsDirectory = fsPath.substr(0, fsPath.find_last_of("/\\"));
		std::string vsSource = readShader(vsFile, name, vsPath);
		std::string fsSource = readShader(fsFile, name, fsPath);

		// now build the shader with the source code
		Shader shader(name, vsSource, fsSource, defines);

		vsFile.close();
		fsFile.close();

		return shader;
	}

	std::string ShaderLoader::readShader(std::ifstream& file, const std::string& name, std::string path)
	{
		std::string directory = path.substr(0, path.find_last_of("/\\"));
		std::string source, line;
		while (std::getline(file,line))
		{
			if (line.substr(0,8) == "#include")
			{
				std::string includePath = directory + "/" + line.substr(9);
				std::ifstream includeFile(includePath);
				if (includeFile.is_open())
				{
					source += readShader(includeFile, name, includePath);
				}
				else
				{
					std::cout << "Shader include failed to open" << std::endl;
				}
				includeFile.close();
			}
			source += line + "\n";

		}
		return source;
	}
}