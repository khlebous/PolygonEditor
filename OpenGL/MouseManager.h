#pragma once
#include "Polygon.h"

class MouseManager
{
	GL::Polygon* polygon;
private:
	GL::Point highlightVertice;
	vector<GL::Point> highlightEdge;

	static MouseManager* instance;
	MouseManager();
public:
	static MouseManager* getInstance();
	~MouseManager();

	static void mouse(int button, int state, int x, int y);
	static void mouse2(int x, int y);
// additional methods
private:
	void DrawNewVerticeAndEdge(int x, int y);
	bool CheckVertices(int x, int y);
	bool CheckEdges(int x, int y);
};
