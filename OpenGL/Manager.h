#pragma once
#include "Polygon.h"

class Manager
{
	vector<GL::Polygon*> polygons;

	int highlightVertice;
	int highlightEdge;
	int highlightPolygon;

	int _nr;
	int _x;
	int _y;
	bool isMoving = false;
	bool checkBox = false;

	static Manager* instance;
	Manager();
public:
	static Manager* getInstance();
	~Manager();

	static void mouseFunc(int button, int state, int x, int y);
	static void mousePassiveFunc(int x, int y);
	static void keyboardFunc(unsigned char key, int x, int y);
	static void motionFuncLeft(int x, int y);
	static void motionFuncRight(int x, int y);

private:
	void NewVertexAndEdge(int x, int y);
	bool CheckVertices(int x, int y);
	void CheckEdges(int x, int y);
};
