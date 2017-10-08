#pragma once
#include "Polygon.h"

class MouseManager
{
	GL::Polygon* polygon;
private:
	static MouseManager* instance;
	MouseManager();
public:
	static MouseManager* getInstance();
	~MouseManager();

	void mouse(int button, int state, int x, int y);
	static void mouse2(int button, int state, int x, int y);
};
