#include "draw_graph.h"

void drawVertices(HDC hdc, vertex** vertices, int n)
{
    int dx = 16, dy = 16, dtx = 5;
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    SelectObject(hdc, pen);
    for(int i=0; i < n; i++)
    {
        vertex* currVert = vertices[i];
        Ellipse(hdc, currVert->x-dx, currVert->y-dy, currVert->x+dx, currVert->y+dy);
        if(i >= 9)
            dtx = 8;
        TextOut(hdc, currVert->x-dtx, currVert->y-dy/2, currVert->name, 2);
    }
}
void drawEdge(HDC hdc, int** adjacencyMatrix, vertex** vertices, int n, int oriented)
{
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    SelectObject(hdc, pen);

    int x0 = vertices[0]->x;
    int y0 = vertices[0]->y;
    int endX = vertices[0]->x;
    int endY = vertices[0]->y;
    for(int k = 0; k < n; k++)
    {
        endX = vertices[k]->x > endX ? vertices[k]->x : endX;
        endY = vertices[k]->y > endY ? vertices[k]->y : endY;
    }
    int midX = (x0 + endX) / 2;
    int midY = (y0 + endY) / 2;

    int xi = 0;
    int yi = 0;
    int xj = 0;
    int yj = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            xi = vertices[i]->x;
            yi = vertices[i]->y;
            xj = vertices[j]->x;
            yj = vertices[j]->y;
            //для неорінтовного
            if(oriented == 0 && adjacencyMatrix[i][j] && i <= j)
            {
                if(i == j)
                {
                    drawLoop(hdc, x0, y0, endX, xi, yi);
                } else if ((xi == midX && yi == midY)||(xj == midX  && yj == midY))
                {
                      MoveToEx(hdc, xi, yi, NULL);
                      LineTo(hdc, xj, yj);
                } else if (i != j + 1 && i + 1 != j)
                {
                      if(yi == yj)
                          Arc(hdc, xi, yi-30, xj, yj+30, xj, yj, xi, yi);
                      else if (xi == xj)
                          Arc(hdc, xi+30, yi, xj-30, yj, xj, yj, xi, yi);
                      else if(lieOnDiagonal(xi, yi, xj, yj, midX, midY))
                      {
                          if(xi == 0)
                          {
                              MoveToEx(hdc, xi, yi, NULL);
                              LineTo(hdc, midX + 18, midY - 18);
                              LineTo(hdc, xj, yj);
                         }
                          else
                          {
                              MoveToEx(hdc, xi, yi, NULL);
                              LineTo(hdc, midX - 18, midY - 18);
                              LineTo(hdc, xj, yj);
                          }
                      } else
                      {
                         MoveToEx(hdc, xi, yi, NULL);
                         LineTo(hdc, xj, yj);
                      }
                } else
                {
                    MoveToEx(hdc, xi, yi, NULL);
                    LineTo(hdc, xj, yj);
                }
                //для оріентованого
            } else if(oriented == 1 && adjacencyMatrix[i][j])
            {
                if(i == j)
                {
                    drawLoopWithArrow(hdc, x0, y0, endX, xi, yi);
                } else if(adjacencyMatrix[i][j] && adjacencyMatrix[j][i])
                {
                   drawDoubleArc(hdc, xi, yi, xj, yj, midX, midY);
                   adjacencyMatrix[j][i] = 0;
                } else if ((xi == midX && yi == midY)||(xj == midX  && yj == midY))
                {

                      MoveToEx(hdc, xi, yi, NULL);
                      LineTo(hdc, xj, yj);
                      if(xi == xj)
                        arrow(hdc, 90, xj, yj + 16);
                      else if(yi == yj)
                        arrow(hdc, 0, xj- 16, yj);
                      else if(xj == endX)
                      {
                          if (yj == y0)
                            arrow(hdc, 45, xj- 16, yj+10);
                          else
                             arrow(hdc, -35, xj- 16, yj-10);
                      } else if( j == 1)
                          arrow(hdc, 110, xj+10, yj+16);
                        else
                          arrow(hdc, 70, xj-10, yj+16);

                } else if (i != j + 1 && i + 1 != j)
                {
                      if(yi == yj)
                      {
                          if(yi == y0)
                          {
                               Arc(hdc, xi, yi-30, xj, yj+30, xj, yj, xi, yi);
                               arrow(hdc, -25, xj-9, yj-10);
                          }else if(yi == endY)
                          {
                               Arc(hdc, xj, yj-30, xi, yi+30, xi, yi, xj, yj);
                               arrow(hdc, 25, xj-10, yj+8);
                          }
                      }
                      else if (xi == xj)
                      {
                          Arc(hdc, xj+30, yj, xi-30, yi, xi, yi, xj, yj);
                          arrow(hdc, 135, xj+10, yj+8);
                      }
                      else if(lieOnDiagonal(xi, yi, xj, yj, midX, midY))
                      {
                          if(xi == 0)
                          {
                              MoveToEx(hdc, xi, yi, NULL);
                              LineTo(hdc, midX + 18, midY - 18);
                              LineTo(hdc, xj, yj);
                         } else
                          {
                              MoveToEx(hdc, xi, yi, NULL);
                              LineTo(hdc, midX - 18, midY - 18);
                              LineTo(hdc, xj, yj);
                          }
                      } else
                      {
                         MoveToEx(hdc, xi, yi, NULL);
                         LineTo(hdc, xj, yj);
                         if(xi == x0 && yi == endY)
                            arrow(hdc, 45, xj-10, yj+10);
                         else if(xj == endX && yj == endY)
                            arrow(hdc, -45, xj-10, yj-10);
                         else if(xi == midX)
                            arrow(hdc, 100, xj+2, yj+14);
                         else if (xj == midX)
                         {
                             arrow(hdc, -100, xj+4, yj-16);
                             arrow(hdc, -155, xj+14, yj-11);
                         }
                         else
                            arrow(hdc, 160, xj+13, yj+4);
                      }
                } else
                {
                    MoveToEx(hdc, xi, yi, NULL);
                    LineTo(hdc, xj, yj);
                    if (i < j)
                    {
                        if(yi == yj && yi == y0)
                            arrow(hdc, 0, xj-16, yj);
                        else if (yi == yj && yi == endY)
                            arrow(hdc, 180, xj-16, yj);
                        else if (xi == xj)
                            arrow(hdc, 90, xj, yj+16);
                    }
                    else if (i > j)
                        if(yi == yj && yi == y0)
                           arrow(hdc, 180, xj+16, yj);
                        else if (yi == yj && yi == endY)
                            arrow(hdc, 0, xj-16, yj);
                        else if (xi == xj)
                            arrow(hdc, 90, xj, yj+16);
                }
            }

            }
        }
}

int lieOnDiagonal(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int res = 0;
    if ((x3 - x1) * (y2 - y1) == (y3 - y1) * (x2 - x1))
        res = 1;
    return res;
}

void drawLoop(HDC hdc, int x0, int y0, int endX, int x, int y)
{
    if(x == x0)
        Arc(hdc, x-50, y+10, x, y-10, x, y, x, y);
    else if (x > x0 && x < endX)
    {
        if(y == y0)
            Arc(hdc, x-10, y-50, x+10, y, x, y, x, y);
        else
            Arc(hdc, x-10, y+50, x+10, y, x, y, x, y);
    }
    else
        Arc(hdc, x+50, y+10, x, y-10, x, y, x, y);
}

 void arrow(HDC hdc, float fi, int px, int py)
{
    fi = 3.1416*(180.0 - fi)/180.0;
    int lx,ly,rx,ry;
    lx = px+15*cos(fi+0.3);
    rx = px+15*cos(fi-0.3);
    ly = py+15*sin(fi+0.3);
    ry = py+15*sin(fi-0.3);
    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
    return 0;
}

void drawLoopWithArrow(HDC hdc, int x0, int y0, int endX, int x, int y)
{
    if(x == x0)
    {
         Arc(hdc, x-50, y+10, x, y-10, x, y, x, y);
         arrow(hdc, 0, x-16, y-10);
    }
    else if (x > x0 && x < endX)
    {
        if(y == y0)
        {
            Arc(hdc, x-10, y-50, x+10, y, x, y, x, y);
            arrow(hdc, -90, x+8, y-16);
        }
        else
        {
            Arc(hdc, x-10, y+50, x+10, y, x, y, x, y);
            arrow(hdc, 90, x-8, y+16);
        }
    }
    else
    {
        Arc(hdc, x+50, y+10, x, y-10, x, y, x, y);
        arrow(hdc, 180, x+16, y+9);
    }
}

void drawDoubleArc(HDC hdc, int x1, int y1, int x2, int y2, int midX, int midY)
{
    if(y1 == y2)
    {
         Arc(hdc, x1, y1-10, x2, y2+10, x2, y2, x1, y1);
         arrow(hdc, -10, x2-16, y2-6);
         Arc(hdc, x2, y2-10, x1, y1+10, x1, y1, x2, y2);
         arrow(hdc, 175, x1+16, y1+6);
    } else if (x1 == x2)
    {
         Arc(hdc, x1+10, y1, x2-10, y2, x2, y2, x1, y1);
         arrow(hdc, -80, x2-6, y2-16);
         Arc(hdc, x2+10, y2, x1-10, y1, x1, y1, x2, y2);
         arrow(hdc, 100, x1+6, y1+16);
    }
    else
    {
        int mid1 = (x1 + x2) / 2;
        int mid2 = (y1 + y2) / 2;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, mid1 + 8, mid2 - 8);
        LineTo(hdc, x2, y2);
        if (x2 == midX && y2 == midY)
            arrow(hdc, -45, x2 - 16, y2 - 15);
        else
            arrow(hdc, -45, x2 - 16, y2 - 10);
        MoveToEx(hdc, x2, y2, NULL);
        LineTo(hdc, mid1 - 8, mid2 + 8);
        LineTo(hdc, x1, y1);
        arrow(hdc, 135, x1 + 13, y1 + 10);
    }
}

 void drawCondGraph(HDC hdc, int** adjMatrix, int** compon, int n)
 {
    int xPos[] = {75, 175, 275, 275, 75, 75,200,150,50,300 };
    int yPos[] = {75, 75, 75, 225, 225, 50,250,250,150,150 };
    int drawVert[] = { 0,0,0,0,0,0,0,0,0,0 };
    char* ellipseName[10] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
    int dx = 16, dy = 16, dtx = 5, xDif, yDif, fi;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            if (compon[i][j] == 0)
                continue;
            for (int count = 0; count < n;count++) {
                if (adjMatrix[j][count]) {
                    for (int count2 = 0; count2 < n;count2++) {
                        if (compon[count2][count]) {
                                if(i + 1 != count2 && i - 1 != count2 && yPos[i] == yPos[count2])
                                {
                                    Arc(hdc, xPos[i], yPos[i]-30, xPos[count2], yPos[count2]+30, xPos[count2], yPos[count2], xPos[i], yPos[i]);
                                    arrow(hdc, -25, xPos[2] - 10, yPos[2] - 12);
                                }
                                else
                                {
                                    MoveToEx(hdc, xPos[i], yPos[i], NULL);
                                    LineTo(hdc, xPos[count2], yPos[count2]);

                                    if(yPos[i] == yPos[count2])
                                    {
                                        if(xPos[count2] > xPos[i])
                                            arrow(hdc, 0, xPos[count2] - dx, yPos[count2]);
                                        else
                                            arrow(hdc, 180, xPos[count2] + dx, yPos[count2]);
                                    }
                                    else if(xPos[i] == xPos[count2])
                                        arrow(hdc, 90, xPos[count2], yPos[count2] + dy);
                                    else
                                        arrow(hdc, 135, xPos[count2] + 11, yPos[count2] + 7);
                                }

                        }
                    }
                }
            }
            drawVert[i] = 1;
        }
    }
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    SelectObject(hdc, pen);
    for (int i = 0;i < n;i++) {
        if (drawVert[i]) {
            Ellipse(hdc, xPos[i] - dx, yPos[i] - dy, xPos[i] + dx, yPos[i] + dy);
            TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, ellipseName[i], 1);
        }
    }
 }

