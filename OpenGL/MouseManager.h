#pragma once
#include "Polygon.h"

class MouseManager
{
	GL::Polygon* polygon;
private:
	int highlightVertice;
	int highlightEdge;

	bool isMoving = false;

	static MouseManager* instance;
	MouseManager();
public:
	static MouseManager* getInstance();
	~MouseManager();

	static void mouseFunc(int button, int state, int x, int y);
	static void mousePassiveFunc(int x, int y);
	static void loopPolygon(unsigned char key, int x, int y);

private:
	void NewVerticeAndEdge(int x, int y);
	bool CheckVertices(int x, int y);
	void CheckEdges(int x, int y);
};
