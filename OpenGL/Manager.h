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
	//
	static void drawScene();
	//
	void NewVertexAndEdge(int x, int y);
private:
	bool CheckVertices(int x, int y);
	void CheckEdges(int x, int y);

	void ClippingPolygons();
	
	//clipPolygon - convex
	void SutherlandHodgman(int clipPolygon, int subjectPolygon);

	void drawGUI();
	static void mouseCallback(int button, int state, int x, int y);
	static void mouseDragCallback(int x, int y);
	static void mouseMoveCallback(int x, int y);
	static void keyboardCallback(unsigned char nChar, int x, int y);
	bool mouseEvent(int button, int state, int x, int y);
	bool keyboardEvent(unsigned char nChar, int nX, int nY);
};
