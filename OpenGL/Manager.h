#pragma once
#include "Polygon.h"

class Manager
{
	GL::Polygon* polygon;
private:
	int highlightVertice;
	int highlightEdge;

	int x;
	int y;

	bool isMoving = false;

	static Manager* instance;
	Manager();
public:
	static Manager* getInstance();
	~Manager();

	static void mouseFunc(int button, int state, int x, int y);
	static void mousePassiveFunc(int x, int y);
	static void keyboardFunc(unsigned char key, int x, int y);
	static void idleFunc();
	static void motionFunc(int x, int y);


private:
	void NewVerticeAndEdge(int x, int y);
	bool CheckVertices(int x, int y);
	void CheckEdges(int x, int y);
};
