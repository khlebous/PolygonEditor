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
	bool drawingArea = false;
	int lastTexture = 0;
	int lastNormalMap = 0;
	int choosedPolygon1 = -1;
	int choosedPolygon2 = -1;

	static Manager* instance;
	Manager();
public:
	static Manager* getInstance();
	~Manager();

	static void mouseFunc(int button, int state, int x, int y);
	static void mousePassiveFunc(int x, int y);
	//
	static void drawScene();
	//
private:
	void NewVertexAndEdge(int x, int y);
	bool CheckVertices(int x, int y);
	void CheckEdges(int x, int y);

	void drawGUI();
	void ClippingPolygons();
	
	void SutherlandHodgman(int clipPolygon, int subjectPolygon); //clipPolygon - convex
	static void keyboardFunc(unsigned char key, int x, int y);
	static void motionFuncLeft(int x, int y);
	static void motionFuncRight(int x, int y);

	static void mouseCallback(int button, int state, int x, int y);
	static void mouseDragCallback(int x, int y);
	static void mouseMoveCallback(int x, int y);
	static void keyboardCallback(unsigned char nChar, int x, int y);
	bool mouseEvent(int button, int state, int x, int y);
	bool keyboardEvent(unsigned char nChar, int nX, int nY);
};
