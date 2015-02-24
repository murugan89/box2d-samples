#ifndef _MATRIXMANAGER_H_
#define _MATRIXMANAGER_H_
#include "common.h"
typedef struct MatrixDef
{
    GLfloat   m[4][4];
}Matrix;
class MatrixManager
{
public:
	static MatrixManager* Instance()
	{
		static MatrixManager *matrix = NULL;

		if(matrix == NULL)
			matrix = new MatrixManager();

		return matrix;
	}
	//Render view
	void perspectiveView(Matrix *result, float fovy, float aspect, float nearZ, float farZ);
	void orthoView(Matrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
	void setOrthoProjection(Matrix *orthoView);
	void setOrthoProjection(float left, float right, float bottom, float top, float nearZ, float farZ);
	Matrix* getOrthoProjection();
	// scale
	void scale(Matrix *result, GLfloat sx, GLfloat sy, GLfloat sz);
	// transform
	void translate(Matrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
	//rotate
	void rotate(Matrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	
	void frustum(Matrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
	// mutliply two matrix and store in result matrix
	void matrixMultiply(Matrix *result, Matrix *srcA, Matrix *srcB);
	void matrixLoadIdentity(Matrix *result);

private:
	Matrix *orthoProjection;
	MatrixManager(void);
	~MatrixManager(void);
};
#endif
