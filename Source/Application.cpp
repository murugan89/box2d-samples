#include "Application.h"
#include "Graphics.h"

#include "World.h"
#include "Body.h"
#include "Joint.h"

namespace
{
	Body bodies[200];
	Joint joints[100];

	Body* bomb = NULL;

	float timeStep = 1.0f / 60.0f;
	int iterations = 10;
	Vec2 gravity(0.0f, -10.0f);

	int numBodies = 0;
	int numJoints = 0;

	int demoIndex = 0;

	World world(gravity, iterations);
}


//Image *texture1;
void DrawBody(Body* body)
{
	Mat22 R(body->rotation);
	Vec2 x = body->position;
	Vec2 h = 0.5f * body->width;

	Vec2 v1 = x + R * Vec2(-h.x, -h.y);
	Vec2 v2 = x + R * Vec2( h.x, -h.y);
	Vec2 v3 = x + R * Vec2( h.x,  h.y);
	Vec2 v4 = x + R * Vec2(-h.x,  h.y);

		GLfloat color[12];
	if (body == bomb)
		color[0] = 0.4f, color[1] = 0.9f, color[2] = 0.4f,
					    color[3] = 0.4f, color[4] = 0.9f, color[5] = 0.4f,
					    color[6] = 0.4f, color[7] = 0.9f, color[8] = 0.4f,
					    color[9] = 0.4f, color[10] = 0.9f, color[11] = 0.4f;
	else
		color[0] = 0.8f, color[1] = 0.8f, color[2] = 0.9f,
					    color[3] = 0.8f, color[4] = 0.8f, color[5] = 0.9f,
					    color[6] = 0.8f, color[7] = 0.8f, color[8] = 0.9f,
					    color[9] = 0.8f, color[10] = 0.8f, color[11] = 0.9f;
	GLfloat vertices[]= {
	v1.x, v1.y,0.0,
	v2.x, v2.y,0.0,
	v3.x, v3.y,0.0,
	v4.x, v4.y,0.0};
	Graphics::Instance()->drawQuad(GL_TRIANGLES,vertices,color);

}


void DrawJoint(Joint* joint)
{
	Body* b1 = joint->body1;
	Body* b2 = joint->body2;

	Mat22 R1(b1->rotation);
	Mat22 R2(b2->rotation);

	Vec2 x1 = b1->position;
	Vec2 p1 = x1 + R1 * joint->localAnchor1;

	Vec2 x2 = b2->position;
	Vec2 p2 = x2 + R2 * joint->localAnchor2;

	GLfloat color[]={0.5f, 0.5f, 0.8f,
		0.5f, 0.5f, 0.8f,
		0.5f, 0.5f, 0.8f,
		0.5f, 0.5f, 0.8f
	};

	GLfloat vertices[]= {
	x1.x, x1.y,0.0,
	x1.x, x1.y,0.0,
	p1.x, p1.y,0.0,
	p1.x, p1.y,0.0
	};
	Graphics::Instance()->drawQuad(GL_LINES,vertices,color);
	GLfloat vertices1[]={
		x2.x, x2.y,0.0,
		x2.x, x2.y,0.0,
		p2.x, p2.y,0.0,
		p2.x, p2.y,0.0};
	Graphics::Instance()->drawQuad(GL_LINES,vertices1,color);

}


void LaunchBomb()
{
	if (!bomb)
	{
		bomb = bodies + numBodies;
		bomb->Set(Vec2(1.0f, 1.0f), 50.0f);
		bomb->friction = 0.2f;
		world.Add(bomb);
		++numBodies;
	}

	bomb->position.Set(Random(-15.0f, 15.0f), 15.0f);
	bomb->rotation = Random(-1.5f, 1.5f);
	bomb->velocity = -1.5f * bomb->position;
	bomb->angularVelocity = Random(-20.0f, 20.0f);
}


// Single box
void Demo1(Body* b, Joint* j)
{
	b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b->position.Set(0.0f, -0.5f * b->width.y);
	world.Add(b);
	++b; ++numBodies;

	b->Set(Vec2(1.0f, 1.0f), 200.0f);
	b->position.Set(0.0f, 4.0f);
	world.Add(b);
	++b; ++numBodies;
}

// A simple pendulum
void Demo2(Body* b, Joint* j)
{
	Body* b1 = b + 0;
	b1->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b1->friction = 0.2f;
	b1->position.Set(0.0f, -0.5f * b1->width.y);
	b1->rotation = 0.0f;
	world.Add(b1);

	Body* b2 = b + 1;
	b2->Set(Vec2(1.0f, 1.0f), 100.0f);
	b2->friction = 0.2f;
	b2->position.Set(9.0f, 11.0f);
	b2->rotation = 0.0f;
	world.Add(b2);

	numBodies += 2;

	j->Set(b1, b2, Vec2(0.0f, 11.0f));
	world.Add(j);

	numJoints += 1;
}

// Varying friction coefficients
void Demo3(Body* b, Joint* j)
{
	b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b->position.Set(0.0f, -0.5f * b->width.y);
	world.Add(b);
	++b; ++numBodies;

	b->Set(Vec2(13.0f, 0.25f), FLT_MAX);
	b->position.Set(-2.0f, 11.0f);
	b->rotation = -0.25f;
	world.Add(b);
	++b; ++numBodies;

	b->Set(Vec2(0.25f, 1.0f), FLT_MAX);
	b->position.Set(5.25f, 9.5f);
	world.Add(b);
	++b; ++numBodies;

	b->Set(Vec2(13.0f, 0.25f), FLT_MAX);
	b->position.Set(2.0f, 7.0f);
	b->rotation = 0.25f;
	world.Add(b);
	++b; ++numBodies;

	b->Set(Vec2(0.25f, 1.0f), FLT_MAX);
	b->position.Set(-5.25f, 5.5f);
	world.Add(b);
	++b; ++numBodies;

	b->Set(Vec2(13.0f, 0.25f), FLT_MAX);
	b->position.Set(-2.0f, 3.0f);
	b->rotation = -0.25f;
	world.Add(b);
	++b; ++numBodies;

	float friction[5] = {0.75f, 0.5f, 0.35f, 0.1f, 0.0f};
	for (int i = 0; i < 5; ++i)
	{
		b->Set(Vec2(0.5f, 0.5f), 25.0f);
		b->friction = friction[i];
		b->position.Set(-7.5f + 2.0f * i, 14.0f);
		world.Add(b);
		++b; ++numBodies;
	}
}

// A vertical stack
void Demo4(Body* b, Joint* j)
{
	b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b->friction = 0.2f;
	b->position.Set(0.0f, -0.5f * b->width.y);
	b->rotation = 0.0f;
	world.Add(b);
	++b; ++numBodies;

	for (int i = 0; i < 10; ++i)
	{
		b->Set(Vec2(1.0f, 1.0f), 1.0f);
		b->friction = 0.2f;
		float x = Random(-0.1f, 0.1f);
		b->position.Set(x, 0.51f + 1.05f * i);
		world.Add(b);
		++b; ++numBodies;
	}
}

// A pyramid
void Demo5(Body* b, Joint* j)
{
	b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b->friction = 0.2f;
	b->position.Set(0.0f, -0.5f * b->width.y);
	b->rotation = 0.0f;
	world.Add(b);
	++b; ++numBodies;

	Vec2 x(-6.0f, 0.75f);
	Vec2 y;

	for (int i = 0; i < 12; ++i)
	{
		y = x;

		for (int j = i; j < 12; ++j)
		{
			b->Set(Vec2(1.0f, 1.0f), 10.0f);
			b->friction = 0.2f;
			b->position = y;
			world.Add(b);
			++b; ++numBodies;

			y += Vec2(1.125f, 0.0f);
		}

		//x += Vec2(0.5625f, 1.125f);
		x += Vec2(0.5625f, 2.0f);
	}
}

// A teeter
void Demo6(Body* b, Joint* j)
{
	Body* b1 = b + 0;
	b1->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b1->position.Set(0.0f, -0.5f * b1->width.y);
	world.Add(b1);

	Body* b2 = b + 1;
	b2->Set(Vec2(12.0f, 0.25f), 100.0f);
	b2->position.Set(0.0f, 1.0f);
	world.Add(b2);

	Body* b3 = b + 2;
	b3->Set(Vec2(0.5f, 0.5f), 25.0f);
	b3->position.Set(-5.0f, 2.0f);
	world.Add(b3);

	Body* b4 = b + 3;
	b4->Set(Vec2(0.5f, 0.5f), 25.0f);
	b4->position.Set(-5.5f, 2.0f);
	world.Add(b4);

	Body* b5 = b + 4;
	b5->Set(Vec2(1.0f, 1.0f), 100.0f);
	b5->position.Set(5.5f, 15.0f);
	world.Add(b5);

	numBodies += 5;

	j->Set(b1, b2, Vec2(0.0f, 1.0f));
	world.Add(j);

	numJoints += 1;
}

// A suspension bridge
void Demo7(Body* b, Joint* j)
{
	b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b->friction = 0.2f;
	b->position.Set(0.0f, -0.5f * b->width.y);
	b->rotation = 0.0f;
	world.Add(b);
	++b; ++numBodies;

	const int numPlanks = 15;
	float mass = 50.0f;

	for (int i = 0; i < numPlanks; ++i)
	{
		b->Set(Vec2(1.0f, 0.25f), mass);
		b->friction = 0.2f;
		b->position.Set(-8.5f + 1.25f * i, 5.0f);
		world.Add(b);
		++b; ++numBodies;
	}

	// Tuning
	float frequencyHz = 2.0f;
	float dampingRatio = 0.7f;

	// frequency in radians
	float omega = 2.0f * k_pi * frequencyHz;

	// damping coefficient
	float d = 2.0f * mass * dampingRatio * omega;

	// spring stifness
	float k = mass * omega * omega;

	// magic formulas
	float softness = 1.0f / (d + timeStep * k);
	float biasFactor = timeStep * k / (d + timeStep * k);

	for (int i = 0; i < numPlanks; ++i)
	{
		j->Set(bodies+i, bodies+i+1, Vec2(-9.125f + 1.25f * i, 5.0f));
		j->softness = softness;
		j->biasFactor = biasFactor;

		world.Add(j);
		++j; ++numJoints;
	}

	j->Set(bodies + numPlanks, bodies, Vec2(-9.125f + 1.25f * numPlanks, 5.0f));
	j->softness = softness;
	j->biasFactor = biasFactor;
	world.Add(j);
	++j; ++numJoints;
}

// Dominos
void Demo8(Body* b, Joint* j)
{
	Body* b1 = b;
	b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b->position.Set(0.0f, -0.5f * b->width.y);
	world.Add(b);
	++b; ++numBodies;

	b->Set(Vec2(12.0f, 0.5f), FLT_MAX);
	b->position.Set(-1.5f, 10.0f);
	world.Add(b);
	++b; ++numBodies;

	for (int i = 0; i < 10; ++i)
	{
		b->Set(Vec2(0.2f, 2.0f), 10.0f);
		b->position.Set(-6.0f + 1.0f * i, 11.125f);
		b->friction = 0.1f;
		world.Add(b);
		++b; ++numBodies;
	}

	b->Set(Vec2(14.0f, 0.5f), FLT_MAX);
	b->position.Set(1.0f, 6.0f);
	b->rotation = 0.3f;
	world.Add(b);
	++b; ++numBodies;

	Body* b2 = b;
	b->Set(Vec2(0.5f, 3.0f), FLT_MAX);
	b->position.Set(-7.0f, 4.0f);
	world.Add(b);
	++b; ++numBodies;

	Body* b3 = b;
	b->Set(Vec2(12.0f, 0.25f), 20.0f);
	b->position.Set(-0.9f, 1.0f);
	world.Add(b);
	++b; ++numBodies;

	j->Set(b1, b3, Vec2(-2.0f, 1.0f));
	world.Add(j);
	++j; ++numJoints;

	Body* b4 = b;
	b->Set(Vec2(0.5f, 0.5f), 10.0f);
	b->position.Set(-10.0f, 15.0f);
	world.Add(b);
	++b; ++numBodies;

	j->Set(b2, b4, Vec2(-7.0f, 15.0f));
	world.Add(j);
	++j; ++numJoints;

	Body* b5 = b;
	b->Set(Vec2(2.0f, 2.0f), 20.0f);
	b->position.Set(6.0f, 2.5f);
	b->friction = 0.1f;
	world.Add(b);
	++b; ++numBodies;

	j->Set(b1, b5, Vec2(6.0f, 2.6f));
	world.Add(j);
	++j; ++numJoints;

	Body* b6 = b;
	b->Set(Vec2(2.0f, 0.2f), 10.0f);
	b->position.Set(6.0f, 3.6f);
	world.Add(b);
	++b; ++numBodies;

	j->Set(b5, b6, Vec2(7.0f, 3.5f));
	world.Add(j);
	++j; ++numJoints;
}

// A multi-pendulum
void Demo9(Body* b, Joint* j)
{
	b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b->friction = 0.2f;
	b->position.Set(0.0f, -0.5f * b->width.y);
	b->rotation = 0.0f;
	world.Add(b);

	Body * b1 = b;
	++b;
	++numBodies;

	float mass = 10.0f;

	// Tuning
	float frequencyHz = 4.0f;
	float dampingRatio = 0.7f;

	// frequency in radians
	float omega = 2.0f * k_pi * frequencyHz;

	// damping coefficient
	float d = 2.0f * mass * dampingRatio * omega;

	// spring stiffness
	float k = mass * omega * omega;

	// magic formulas
	float softness = 1.0f / (d + timeStep * k);
	float biasFactor = timeStep * k / (d + timeStep * k);

	const float y = 12.0f;

	for (int i = 0; i < 15; ++i)
	{
		Vec2 x(0.5f + i, y);
		b->Set(Vec2(0.75f, 0.25f), mass);
		b->friction = 0.2f;
		b->position = x;
		b->rotation = 0.0f;
		world.Add(b);

		j->Set(b1, b, Vec2((float)i, y));
		j->softness = softness;
		j->biasFactor = biasFactor;
		world.Add(j);

		b1 = b;
		++b;
		++numBodies;
		++j;
		++numJoints;
	}
}

void (*demos[])(Body* b, Joint* j) = {Demo1, Demo2, Demo3, Demo4, Demo5, Demo6, Demo7, Demo8, Demo9};

void InitDemo(int index)
{
	world.Clear();
	numBodies = 0;
	numJoints = 0;
	bomb = NULL;

	demoIndex = index;
	demos[index](bodies, joints);
}

void Application::init(int width, int height)
{
	InitDemo(7);

	this->width = width;
	this->height = height;
	this->fl_scale=2.3f;
	//OpenGL initialize
	{
		glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable( GL_BLEND );

		//set view port
		glViewport ( 0, 0, width, height);
	}
	//Application initialize
	{
		MatrixManager::Instance()->setOrthoProjection(0.0, (GLfloat)this->width, (GLfloat)this->height, 0.0, -60.0, 60.0);

		Graphics::Instance()->init();
//		#ifdef OS_ANDROID
//			//texture1 = new Image("/../../Test/Data/Gameloft_logo.jpg");
//			texture1 = new Image("/mnt/sdcard/texture.png");
//		#else
//			texture1 = new Image("Data/texture.png");
//		#endif
	}
}
void Application::update()
{
	//Applicatin upate code
	Graphics::Instance()->update();

}

void Application::draw()
{
	//Application draw code
	MatrixManager::Instance()->matrixLoadIdentity(MatrixManager::Instance()->getOrthoProjection());
	// Clear the color buffer
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

//	texture1->drawImage(0.0f,0.0f);
//	Graphics::Instance()->drawRectangle(0.0f,0.0f,1.0f,1.0f);
	MatrixManager::Instance()->translate(MatrixManager::Instance()->getOrthoProjection(),0.0f,-0.50f, 0.0f);

	MatrixManager::Instance()->scale(MatrixManager::Instance()->getOrthoProjection(),0.03f*this->fl_scale,0.05f*this->fl_scale,1.0f);
	world.Step(timeStep);

	for (int i = 0; i < numBodies; ++i)
		DrawBody(bodies + i);

	for (int i = 0; i < numJoints; ++i)
		DrawJoint(joints + i);
}

void Application::keyDown(unsigned char key)
{
	switch(key){
			case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		InitDemo(key - '1');
		break;

	case' ':
		LaunchBomb();
		break;
	case'A':
		this->fl_scale=this->fl_scale+1.0f;
	break;
	case'B':
		this->fl_scale=this->fl_scale-1.0f;
	break;
	}
}

void Application::keyUp(unsigned char key)
{
}

void Application::mouseMoved(int x, int y)
{
}

void Application::mousePressed(int x, int y)
{
}

void Application::mouseReleased(int x, int y)
{
	if(x<100){
		if(y<100){
			InitDemo(0);
		} else if(y<200){
			InitDemo(1);
		} else if(y<300){
			InitDemo(2);
		}
	}else if(x<200){
		if(y<100){
			InitDemo(3);
		} else if(y<200){
			InitDemo(4);
		} else if(y<300){
			InitDemo(5);
		}
	}else if(x<300){
		if(y<100){
			InitDemo(6);
		} else if(y<200){
			InitDemo(7);
		} else if(y<300){
			InitDemo(8);
		}
	}else
	LaunchBomb();
}
