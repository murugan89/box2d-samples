#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include "MatrixManager.h"
#include "common.h"
#include "ShaderLoader.h"

class Graphics
{
public:
	static Graphics* Instance()
	{
		static Graphics *graphics = NULL;
		if(graphics == NULL)
			graphics = new Graphics();
		return graphics;
	}

	void setProgramObject(GLuint programObj);
	// draw trigangle from given points
	void init();
	void update();
	void drawTriangle(GLfloat vVertices[],GLfloat vColor[]);
	void drawCube(GLfloat vVertices[],GLfloat vColor[]);
	void drawQuad(GLenum type,GLfloat vVertices[],GLfloat vColor[]);
	// draw rectangle
	void drawRectangle(GLfloat x,GLfloat y,GLfloat width, GLfloat height);

private:
	Graphics(void);
	~Graphics(void);
	GLuint daulft_programObject;

	Matrix modelMatrix;
	//Matrix ortho;

	int uniformViewLoc;
	int aPositonLoc;
	int aColorLoc;


};
#endif