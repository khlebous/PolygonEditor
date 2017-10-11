#pragma once
#include "Polygon.h"

class MouseManager
{
	GL::Polygon* polygon;
private:
	GL::Vertice highlightVertice;
	GL::Edge highlightEdge;

	static MouseManager* instance;
	MouseManager();
public:
	static MouseManager* getInstance();
	~MouseManager();

	static void mouseFunc(int button, int state, int x, int y);
	static void mousePassiveFunc(int x, int y);

	void UnhighlightVertice();
	void UnhighlightEdge();
// additional methods
private:
	void DrawNewVerticeAndEdge(int x, int y);
	bool CheckVertices(int x, int y);
	void CheckEdges(int x, int y);
};
