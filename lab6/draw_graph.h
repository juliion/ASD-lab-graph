#pragma once
#include<windows.h>
#include <math.h>
#include "graph.h"

void drawVertix(HDC hdc, HPEN pen, vertex** vertices, int k);
void drawVertices(HDC hdc, vertex** vertices, int n);
void drawEdgeNotOrient(HDC hdc, HPEN pen, graph* gr, int from, int to, int withW);
void drawEdgeOrient(HDC hdc, HPEN pen, graph* gr, int from, int to);
void drawEdges(HDC hdc, graph* gr, int n, int oriented);
int lieOnDiagonal(int x1, int y1, int x2, int y2, int x3, int y3);
void drawLoop(HDC hdc, int x0, int y0, int endX, int x, int y, char w[17], int withW);
void arrow(HDC hdc, float fi, int px, int py);
void drawLoopWithArrow(HDC hdc, int x0, int y0, int endX, int x, int y);
void drawDoubleArc(HDC hdc, int x1, int y1, int x2, int y2, int midX, int midY, int k);
