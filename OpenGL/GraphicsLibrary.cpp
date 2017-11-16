#include"GraphicsLibrary.h"
#include <algorithm>  
#include "AET.h"
#include "global_variable.h"
#include <SOIL/SOIL.h>

const int VERTEX_POINT_SIZE = 6;
const int EDGE_POINT_SIZE = 1;



struct less_than_key
{
	inline bool operator() (const GL::Vertex& struct1, const GL::Vertex& struct2)
	{
		return (struct1.GetY() < struct2.GetY());
	}
};
void GL::FillPolygon(GL::Polygon * p)
{
	float thisPolygonFillColorR = polygonFillColorR;
	float thisPolygonFillColorG = polygonFillColorG;
	float thisPolygonFillColorB = polygonFillColorB;
	float thisNormalVectorX = normalVectorX;
	float thisNormalVectorY = normalVectorY;
	float thisNormalVectorZ = normalVectorZ;
	float thisLightVectorX = lightVectorX;
	float thisLightVectorY = lightVectorY;
	float thisLightVectorZ = lightVectorZ;

	float thisNormalDisorderX = normalDisorderX;
	float thisNormalDisorderY = normalDisorderY;
	float thisNormalDisorderZ = normalDisorderZ;

	unsigned char* texture = nullptr;
	unsigned char* normalMap = nullptr;
	unsigned char* heightMap = nullptr;
	int textureWidth, textureHight;
	if (isTexture)
	{
		char* s = "";
		switch (textureNr)
		{
		case 0:
			s = "t0.png";
			break;
		case 1:
			s = "t1.png";
			break;
		case 2:
			s = "t2.png";
			break;
		default:
			s = "t0.png";
			break;
		}
		texture = SOIL_load_image(s, &textureWidth, &textureHight, 0, SOIL_LOAD_RGB);
		if (texture == 0)
			cout << "Can't load texture\n";
	}
	int normalMapWidth, normalMapHeight;
	if (isNormalMap == 0)
	{
		char* s = "";
		switch (normalMapNr)
		{
		case 0:
			s = "n0.png";
			break;
		case 1:
			s = "n1.bmp";
			break;
		case 2:
			s = "n2.jpg";
			break;
		case 3:
			s = "n3.png";
			break;
		default:
			s = "n0.png";
			break;
		}
		normalMap = SOIL_load_image(s, &normalMapWidth, &normalMapHeight, 0, SOIL_LOAD_RGB);
		if (normalMap == 0)
			cout << "Can't load texture\n";
	}
	int heightMapWidth, heightMapHeight;
	if (isDisorder)
	{
		heightMap = SOIL_load_image("h0.png", &heightMapWidth, &heightMapHeight, 0, SOIL_LOAD_RGB);
		if (heightMap == 0)
			cout << "Can't load texture\n";
	}
	if (isLightAnimated)
	{
		lightPositionX = lightRadius* cosf(lightAngle) + (WINDOW_WIDTH - MENU_WIDTH) / 2;
		lightPositionY = lightRadius* sinf(lightAngle) + WINDOW_HEIGHT / 2;
		lightAngle += lightStep;
		glutPostRedisplay();
	}
	glPointSize(1);
	glBegin(GL_POINTS);
	vector<GL::Vertex> v = p->GetVertices();
	int size = v.size();
	for (int i = 0; i < size; i++)
		v[i].nr = i;
	std::sort(v.begin(), v.end(), less_than_key());
	int* indexes = new int[size];
	for (int i = 0; i < v.size(); i++)
		indexes[i] = v[i].nr;
	v = p->GetVertices();
	for (int i = 0; i < size; i++)
		v[i].nr = i;
	int ymin = v[indexes[0]].GetY();
	int ymax = v[indexes[size - 1]].GetY();
	vector<GL::AET> AET = vector<GL::AET>();
	int vIndex = 0;
	for (int vertexY = ymin; vertexY <= ymax; vertexY++)
	{
		vector<GL::Vertex> vPrev = vector<GL::Vertex>();
		while (v[indexes[vIndex]].GetY() == vertexY - 1)
			vPrev.push_back(v[indexes[vIndex++]]);
		for (int i = 0; i < vPrev.size(); i++)
		{
			GL::Vertex v_prev = v[(vPrev[i].nr - 1 + size) % size];
			if (v_prev.GetY() > vPrev[i].GetY())
				AET.push_back(GL::AET(v_prev, vPrev[i]));
			else if (v_prev.GetY() < vPrev[i].GetY())
			{
				int j = 0;
				for (j = 0; j < AET.size(); j++)
				{
					if ((v_prev == AET[j].v1) && (vPrev[i] == AET[j].v2) ||
						(v_prev == AET[j].v2) && (vPrev[i] == AET[j].v1))
						break;
				}
				AET.erase(AET.begin() + j);
			}

			GL::Vertex v_next = v[(vPrev[i].nr + 1) % size];
			if (v_next.GetY() > vPrev[i].GetY())
				AET.push_back(GL::AET(v_next, vPrev[i]));
			else if (v_next.GetY() < vPrev[i].GetY())
			{
				int j = 0;
				for (j = 0; j < AET.size(); j++)
				{
					if (((v_next == AET[j].v1) && (vPrev[i] == AET[j].v2)) ||
						((v_next == AET[j].v2) && (vPrev[i] == AET[j].v1)))
						break;
				}
				AET.erase(AET.begin() + j);
			}
		}
		vPrev.clear();
		std::sort(AET.begin(), AET.end());
		for (int l = 0; l < AET.size(); l += 2)
		{
			int vertexX = AET[l].x;
			while (vertexX <= (int)round(AET[l + 1].x))
			{
				if (isTexture)
				{
					int qq = (int)round(vertexX);
					int ww = (int)round(vertexY);
					qq = textureWidth - qq% textureWidth;
					ww = textureHight - fabs(ww%textureHight);
					int thisNum = (qq + ww*textureWidth) * 3;
					unsigned char r = texture[thisNum + 0];
					unsigned char g = texture[thisNum + 1];
					unsigned char b = texture[thisNum + 2];
					thisPolygonFillColorR = (float)r / 255;
					thisPolygonFillColorG = (float)g / 255;
					thisPolygonFillColorB = (float)b / 255;
				}
				if (isNormalMap == 0)
				{
					int qq = (int)round(vertexX);
					int ww = (int)round(vertexY);
					qq = normalMapWidth - qq% normalMapWidth;
					ww = normalMapHeight - fabs(ww%normalMapHeight);
					int thisNum = (qq + ww*normalMapWidth) * 3;
					unsigned char r = normalMap[thisNum + 0];
					unsigned char g = normalMap[thisNum + 1];
					unsigned char b = normalMap[thisNum + 2];
					thisNormalVectorX = (float)r / 128 - 1;
					thisNormalVectorY = (float)g / 128 - 1;
					thisNormalVectorZ = (float)b / 255;
				}
				else if (isNormalMap == 2)
				{
					if (sqrt((vertexX - hemispherePosX)*(vertexX - hemispherePosX) + (vertexY - hemispherePosY)*(vertexY - hemispherePosY)) < hemisphereRadius)
					{
						thisNormalVectorX = -vertexX + hemispherePosX;
						thisNormalVectorY = vertexY - hemispherePosY;
						thisNormalVectorZ = sqrt(hemisphereRadius*hemisphereRadius - thisNormalVectorX*thisNormalVectorX - thisNormalVectorY*thisNormalVectorY);
					}
					else
					{
						thisNormalVectorX = 0;
						thisNormalVectorY = 0;
						thisNormalVectorZ = 1;
					}
				}
				if (isDisorder)
				{
					//int Tx = 1;
					//int Ty = 0;
					//int Tz = -thisNormalVectorX;
					//int Bx = 0;
					//int By = 1;
					//int Bz = -thisNormalVectorY;
					//int qq = (int)round(vertexX);
					//int ww = (int)round(vertexY);
					//qq = heightMapWidth - qq% heightMapWidth;
					//ww = heightMapHeight - fabs(ww%heightMapHeight);
					//int thisNum = (qq + ww*heightMapWidth) * 3;
					//int nextNum = (qq + (ww + 1)*heightMapWidth) * 3;
					//int nextNum2 = (qq + (ww)*(heightMapWidth + 1)) * 3;
					//unsigned char r0 = normalMap[thisNum + 0];
					///*unsigned char g0 = normalMap[thisNum + 1];
					//unsigned char b0 = normalMap[thisNum + 2];*/
					//unsigned char r1 = normalMap[nextNum + 0];
					///*unsigned char g1 = normalMap[nextNum + 1];
					//unsigned char b1 = normalMap[nextNum + 2];*/
					//unsigned char r2 = normalMap[nextNum2 + 0];
					//float dhx = r1 - r0;
					//float dhy = r2 - r0;
				}
				float normNorm = 1;
				normNorm = sqrt(thisNormalVectorX*thisNormalVectorX + thisNormalVectorY*thisNormalVectorY + thisNormalVectorZ*thisNormalVectorZ);

				float cosinus = 0;
				float lightNorm = 1;
				if (isLightAnimated)
				{
					float lightPositionXtmp = lightPositionX - (int)round(vertexX);
					lightPositionXtmp = -lightPositionXtmp;
					float lightPositionYtmp = lightPositionY - (int)round(vertexY);
					lightNorm = sqrt(lightPositionXtmp*lightPositionXtmp + lightPositionYtmp*lightPositionYtmp + lightPositionZ*lightPositionZ);
					cosinus =
						(lightPositionXtmp*thisNormalVectorX +
							lightPositionYtmp*thisNormalVectorY +
							lightPositionZ * thisNormalVectorZ) / lightNorm / normNorm;
				}
				else
					cosinus =
					(lightVectorX *thisNormalVectorX +
						lightVectorY*thisNormalVectorY +
						lightVectorZ * thisNormalVectorZ) / lightNorm / normNorm;

				glColor3f(
					lightColorR*thisPolygonFillColorR*cosinus,
					lightColorG*thisPolygonFillColorG*cosinus,
					lightColorB*thisPolygonFillColorB*cosinus);
				glVertex2i((int)round(vertexX++), (int)round(vertexY));
			}

		}
		for (int l = 0; l < AET.size(); l++)
		{
			AET[l].x += AET[l].m;
		}
	}
	glEnd();
	glColor3f(vertexColorR, vertexColorG, vertexColorB);
	glPointSize(VERTEX_POINT_SIZE);
	glBegin(GL_POINTS);
	for (int q = 0; q < size; q++)
		glVertex2i(v[q].GetX(), v[q].GetY());
	glEnd();
	delete indexes;
}

void GL::DrawPolygons(vector<GL::Polygon*> p, int highlightP, int highlightV, int highlightE, int choosedP1, int choosedP2)
{
	for (int i = 0; i < p.size(); i++)
	{
		if (p[i]->IsLooped())
			GL::FillPolygon(p[i]);
		/*else*/
		GL::DrawPolygon(p[i], (i == choosedP1) || (i == choosedP2));
	}
	if (highlightP != -1)
	{
		if (highlightV != -1)
			GL::DrawVertice(p[highlightP]->GetVertex(highlightV), true);
		else if (highlightE != -1)
			GL::DrawEdge(p[highlightP]->GetVertex(highlightE),
				p[highlightP]->GetVertex(highlightE + 1), true);
	}
}
void GL::DrawPolygon(GL::Polygon * p, bool choosed)
{
	vector<GL::Vertex> vertices = p->GetVertices();
	int i = 0;
	auto size = (int)vertices.size() - 1;
	for (; i < size; i++)
	{
		GL::DrawEdge(vertices[i], vertices[i + 1], choosed);
		GL::DrawVertice(vertices[i], choosed);
	}
	if (size != -1)
	{
		if (p->IsLooped())
			GL::DrawEdge(vertices[i], vertices[0], choosed);
		DrawVertice(vertices[i], choosed);
	}
}

void GL::DrawVertice(GL::Vertex v, bool highlight)
{
	if (highlight)
		glColor3f(vertexHColorR, vertexHColorG, vertexHColorB);
	else
		glColor3f(vertexColorR, vertexColorG, vertexColorB);
	glPointSize(VERTEX_POINT_SIZE);
	glBegin(GL_POINTS);
	glVertex2i(v.GetX(), v.GetY());
	glEnd();
}
void GL::DrawEdge(GL::Vertex v1, GL::Vertex v2, bool highlight)
{
	vector<pair<int, int>> edge = CalculateLinePixels(v1, v2);
	if (highlight)
		glColor3f(edgeHColorR, edgeHColorG, edgeHColorB);
	else
		glColor3f(edgeColorR, edgeColorG, edgeColorB);
	glPointSize(EDGE_POINT_SIZE);
	glBegin(GL_POINTS);
	for (pair<int, int> p : edge)
		glVertex2i(p.first, p.second);
	glEnd();
}
vector<pair<int, int>> GL::CalculateLinePixels(GL::Vertex v1, GL::Vertex v2)
{
	vector<pair<int, int>> line;
	int x1 = v1.GetX();
	int y1 = v1.GetY();
	int x2 = v2.GetX();
	int y2 = v2.GetY();
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = dx - dy;

	line.push_back(make_pair(x2, y2));
	while (x1 != x2 || y1 != y2)
	{
		line.push_back(make_pair(x1, y1));
		int error2 = error * 2;
		if (error2 > -dy)
		{
			error -= dy;
			x1 += signX;
		}
		if (error2 < dx)
		{
			error += dx;
			y1 += signY;
		}
	}
	return line;
}

