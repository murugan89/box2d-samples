#ifndef _SHADERLOADER_H_
#define _SHADERLOADER_H_

#include "common.h"
class ShaderLoader
{
public:
	static ShaderLoader* Instance()
	{
		static ShaderLoader *sLoader = NULL;
		if(sLoader == NULL)
			sLoader = new ShaderLoader();
		return sLoader;
	}
	// Load program object
	GLuint loadProgram (const char *vertShaderSrc,const char *fragShaderSrc );
	// Load Shader object
	GLuint loadShader(GLenum shaderType,const char *shaderSrc);
	// read shader file
	char* readFile(const char *file);
private:
	ShaderLoader(void);
	~ShaderLoader(void);
};
#endif