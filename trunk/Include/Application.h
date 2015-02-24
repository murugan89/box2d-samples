#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "common.h"

class Application
{
public:
	static Application* Instance()
	{
		static Application *app = NULL;

		if(app == NULL)
			app = new Application();

		return app;
	}

	void init(int width, int height);

	void update();

	void draw();

	int getWidth() { return width; }

	int getHeight() { return height; }
	void setWidth(int width ){this->width = width;}
	void setHeight(int width ){this->height = height;}

	void keyDown(unsigned char key);
	void keyUp(unsigned char key);

	void mouseMoved(int x, int y);
	void mousePressed(int x, int y);
	void mouseReleased(int x, int y);
	

private:
	int width, height;
	float fl_scale;
	Application() {}
	~Application() {}
};

#endif //_APPLICATION_H_