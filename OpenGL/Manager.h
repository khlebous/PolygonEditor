#pragma once
#include "Polygon.h"

class Manager
{
	GL::Polygon* polygon;
	GL::Polygon* polygon2;

	int highlightVertice;
	int highlightEdge;
	int _x;
	int _y;
	bool isMoving = false;
	bool checkBox = false;

	static Manager* instance;
	Manager();
public:
	static Manager* getInstance();
	~Manager();

	void mouseFunc(int button, int state, int x, int y);
	void mousePassiveFunc(int x, int y);
	void keyboardFunc(unsigned char key, int x, int y);
	void motionFuncLeft(int x, int y);
	void motionFuncRight(int x, int y);

private:
	void NewVerticeAndEdge(GL::Polygon* p, int x, int y);
	bool CheckVertices(int x, int y);
	void CheckEdges(int x, int y);
};
