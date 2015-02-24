#include "Graphics.h"

Graphics::Graphics(void)
{
	
}
Graphics::~Graphics(void)
{
	
}
void Graphics::setProgramObject(GLuint programObj)
{
	daulft_programObject = programObj;
}

void Graphics::init()
{

		daulft_programObject = ShaderLoader::Instance()->loadProgram("uniform mat4 u_mvpMatrix;\n attribute vec4 a_Position;\n attribute vec4 a_Color;\n varying vec4 v_Color;\n void main()\n {\n gl_Position =  u_mvpMatrix*a_Position;\n v_Color = a_Color;\n}\n",
			"precision mediump float;\n varying vec4 v_Color;\n void main()\n {\n gl_FragColor = v_Color;\n }\n ");
	
	aColorLoc = glGetAttribLocation(daulft_programObject,"a_Color");
	aPositonLoc = glGetAttribLocation(daulft_programObject,"a_Position");
	uniformViewLoc = glGetUniformLocation( daulft_programObject, "u_mvpMatrix");
}
void Graphics::update()
{
	/*MatrixManager::Instance()->matrixLoadIdentity(&modelMatrix);

	Matrix *ortho = MatrixManager::Instance()->getOrthoProjection();
	
	MatrixManager::Instance()->matrixMultiply( ortho,&modelMatrix,ortho);*/
}
void Graphics::drawTriangle(GLfloat vVertices[],GLfloat vColor[])
{
	
	glUseProgram (daulft_programObject);
   // Load the vertex data
   glVertexAttribPointer ( aPositonLoc, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
   glVertexAttribPointer ( aColorLoc, 3, GL_FLOAT, GL_FALSE, 0, vColor);

   glEnableVertexAttribArray( aColorLoc );
   glEnableVertexAttribArray( aPositonLoc );
   
   Matrix *ortho = MatrixManager::Instance()->getOrthoProjection();

   glUniformMatrix4fv( uniformViewLoc, 1, GL_FALSE, (GLfloat*) &ortho->m[0][0]);

   glDrawArrays ( GL_TRIANGLES, 0, 3 );

}
void Graphics::drawRectangle(GLfloat x,GLfloat y,GLfloat width, GLfloat hight)
{
	int numIndices = 6;
	GLfloat vertices[]= { x, y, 0.0f,
                          x, y+hight, 0.0f, 
						   x+width, y+hight , 0.0f,
						   x+width, y, 0.0f};

	GLfloat color[] = {1.0,1.0,1.0,
					    0.0,1.0,1.0,
					    1.0,1.0,0.0,
					    1.0,0.0,1.0};

	GLuint indices[] = {0,1,2,
						0,2,3};

	glUseProgram (daulft_programObject);
   // Load the vertex data
   glVertexAttribPointer ( aPositonLoc, 3, GL_FLOAT, GL_FALSE, 0, vertices );
   glVertexAttribPointer ( aColorLoc, 3, GL_FLOAT, GL_FALSE, 0, color);

   glEnableVertexAttribArray( aColorLoc );
   glEnableVertexAttribArray( aPositonLoc );

   Matrix *ortho = MatrixManager::Instance()->getOrthoProjection();
   glUniformMatrix4fv( uniformViewLoc, 1, GL_FALSE, (GLfloat*) &ortho->m[0][0]);
   glDrawElements ( GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, indices );
}


void Graphics::drawQuad(GLenum type,GLfloat vertices[],GLfloat color[])
{
	int numIndices = 6;

	GLuint indices[] = {0,1,2,
						0,2,3};

	glUseProgram (daulft_programObject);
   // Load the vertex data
   glVertexAttribPointer ( aPositonLoc, 3, GL_FLOAT, GL_FALSE, 0, vertices );
   glVertexAttribPointer ( aColorLoc, 3, GL_FLOAT, GL_FALSE, 0, color);

   glEnableVertexAttribArray( aColorLoc );
   glEnableVertexAttribArray( aPositonLoc );

   Matrix *ortho = MatrixManager::Instance()->getOrthoProjection();
   glUniformMatrix4fv( uniformViewLoc, 1, GL_FALSE, (GLfloat*) &ortho->m[0][0]);
   glDrawElements ( type, numIndices, GL_UNSIGNED_INT, indices );
}

void Graphics::drawCube(GLfloat vertices[],GLfloat color[])
{
	int numIndices=36;
// index array of vertex array for glDrawElements() & glDrawRangeElement()
GLuint indices[]  = { 0, 1, 2,   2, 3, 0,      // front
                       4, 5, 6,   6, 7, 4,      // right
                       8, 9,10,  10,11, 8,      // top
                      12,13,14,  14,15,12,      // left
                      16,17,18,  18,19,16,      // bottom
                      20,21,22,  22,23,20 };    // back


	glUseProgram (daulft_programObject);
   // Load the vertex data
   glVertexAttribPointer ( aPositonLoc, 3, GL_FLOAT, GL_FALSE, 0, vertices );
   glVertexAttribPointer ( aColorLoc, 3, GL_FLOAT, GL_FALSE, 0, color);

   glEnableVertexAttribArray( aColorLoc );
   glEnableVertexAttribArray( aPositonLoc );

   Matrix *ortho = MatrixManager::Instance()->getOrthoProjection();
   glUniformMatrix4fv( uniformViewLoc, 1, GL_FALSE, (GLfloat*) &ortho->m[0][0]);
   glDrawElements ( GL_LINES, numIndices, GL_UNSIGNED_INT, indices );
}