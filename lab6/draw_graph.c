#include "draw_graph.h"

void drawVertix(HDC hdc, HPEN pen, vertex** vertices, int k)
{
    int dx = 16, dy = 16, dtx = 5;
    SelectObject(hdc, pen);
    vertex* vertix = vertices[k];
    Ellipse(hdc, vertix->x-dx, vertix->y-dy, vertix->x+dx, vertix->y+dy);
        if(k >= 9)
            dtx = 8;
    TextOut(hdc, vertix->x-dtx, vertix->y-dy/2, vertix->name, 2);
}

void drawVertices(HDC hdc, vertex** vertices, int n)
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    SelectObject(hdc, pen);
    for(int i=0; i < n; i++)
    {
        drawVertix(hdc, pen, vertices, i);
    }
}

void drawEdgeNotOrient(HDC hdc, HPEN pen, graph* gr, int from, int to, int withW)
{
    SelectObject(hdc, pen);
    int dt = 5;
    char w[17];
    int x0 = gr->x0;
    int y0 = gr->y0;
    int endX = gr->endX;
    int endY = gr->endY;
    vertex** vertices = gr->vertices;
    int** weight = gr->weightMatrix;
    itoa(weight[from][to], w, 10);
    int midX = (x0 + endX) / 2;
    int midY = (y0 + endY) / 2;
    int x1 = vertices[from]->x;
    int y1 = vertices[from]->y;
    int x2 = vertices[to]->x;
    int y2 = vertices[to]->y;
    if(from == to)
    {
        drawLoop(hdc, x0, y0, endX, x1, y1, w, withW);
    } else if ((x1 == midX && y1 == midY)||(x2 == midX  && y2 == midY))
    {
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        if(withW)
            TextOut(hdc, (x1+x2)/2, (y1+y2)/2, w, 3);
    } else if (from != to + 1 && from + 1 != to)
    {
        if(y1 == y2)
        {
            Arc(hdc, x1, y1-30, x2, y2+30, x2, y2, x1, y1);
            if(x1 > x2 && withW)
                TextOut(hdc, (x1+x2)/2, (y1+y2)/2 + 20, w, 3);
            else if(withW)
                TextOut(hdc, (x1+x2)/2, (y1+y2)/2 - 40, w, 3);
        }
        else if (x1 == x2)
        {
            Arc(hdc, x1+30, y1, x2-30, y2, x2, y2, x1, y1);
            if(withW)
                TextOut(hdc, (x1+x2)/2 + 40, (y1+y2)/2 + 10, w, 3);
        }
        else if(lieOnDiagonal(x1, y1, x2, y2, midX, midY))
        {
            if(x1 == 0)
            {
                MoveToEx(hdc, x1, y1, NULL);
                LineTo(hdc, midX + 18, midY - 18);
                LineTo(hdc, x2, y2);
                if(withW)
                    TextOut(hdc, midX + 20, midY - 20, w, 3);
            }
            else
            {
                MoveToEx(hdc, x1, y1, NULL);
                LineTo(hdc, midX - 18, midY - 18);
                LineTo(hdc, x2, y2);
                if(withW)
                    TextOut(hdc, midX - 20, midY + 20, w, 3);
            }
        } else
        {
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);
            if(withW)
            {
                if(from == 1 && to == 6)
                    TextOut(hdc, (x1+x2)/2 - 20, (y1+y2)/2, w, 3);
                if(from == 2 && to == 7)
                    TextOut(hdc, (x1+x2)/2, (y1+y2)/2-10, w, 3);
                else
                    TextOut(hdc, (x1+x2)/2, (y1+y2)/2, w, 3);
            }
        }
        } else
        {
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);
            if(withW)
                TextOut(hdc, (x1+x2)/2, (y1+y2)/2, w, 3);
        }

}
void drawEdgeOrient(HDC hdc, HPEN pen, graph* gr, int from, int to)
{
    SelectObject(hdc, pen);
    int x0 = gr->x0;
    int y0 = gr->y0;
    int endX = gr->endX;
    int endY = gr->endY;
    vertex** vertices = gr->vertices;
    int** adjacencyMatrix = gr->adjacencyMatrix;
    int k = 0;
    int midX = (x0 + endX) / 2;
    int midY = (y0 + endY) / 2;
    int x1 = vertices[from]->x;
    int y1 = vertices[from]->y;
    int x2 = vertices[to]->x;
    int y2 = vertices[to]->y;
    if(from == to)
    {
        drawLoopWithArrow(hdc, x0, y0, endX, x1, y1);
    } else if(adjacencyMatrix[from][to] && adjacencyMatrix[to][from])
    {
        k++;
        drawDoubleArc(hdc, x1, y1, x2, y2, midX, midY, k);
        if(k == 2)
            k = 0;
        adjacencyMatrix[to][from] = 0;
    } else if ((x1 == midX && y1 == midY)||(x2 == midX  && y2 == midY))
    {
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        if(x1 == x2)
            arrow(hdc, 90, x2, y2 + 16);
        else if(y1 == y2)
            arrow(hdc, 0, x2- 16, y2);
        else if(x2 == endX)
        {
            if (y2 == y0)
                 arrow(hdc, 45, x2- 16, y2+10);
            else
                 arrow(hdc, -35, x2- 16, y2-10);
        } else if( to == 1)
                 arrow(hdc, 110, x2+10, y2+16);
        else
                 arrow(hdc, 70, x2-10, y2+16);
    } else if (from != to + 1 && from + 1 != to)
    {
        if(y1 == y2)
        {
            if(y1 == y0)
            {
                Arc(hdc, x1, y1-30, x2, y2+30, x2, y2, x1, y1);
                arrow(hdc, -25, x2-9, y2-10);
            } else if(y1 == endY)
            {
                Arc(hdc, x2, y2-30, x1, y1+30, x1, y1, x2, y2);
                arrow(hdc, 25, x2-10, y2+8);
            }
        } else if (x1 == x2)
        {
            Arc(hdc, x2+30, y2, x1-30, y1, x1, y1, x2, y2);
            arrow(hdc, 135, x2+10, y2+8);
        } else if(lieOnDiagonal(x1, y1, x2, y2, midX, midY))
        {
            if(x1 == 0)
            {
                MoveToEx(hdc, x1, y1, NULL);
                LineTo(hdc, midX + 18, midY - 18);
                LineTo(hdc, x2, y2);
            } else
            {
                MoveToEx(hdc, x1, y1, NULL);
                LineTo(hdc, midX - 18, midY - 18);
                LineTo(hdc, x2, y2);
            }
        } else
        {
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);
            if(x1 == x0 && y1 == endY)
                arrow(hdc, 45, x2-10, y2+10);
            else if(x2 == endX && y2 == endY)
                arrow(hdc, -45, x2-10, y2-10);
            else if(x1 == midX)
                arrow(hdc, 100, x2+2, y2+14);
            else if (x2 == midX && from == 4)
                arrow(hdc, -155, x2+14, y2-11);
            else if(x2 == midX && from == 2)
                arrow(hdc, -100, x2+4, y2-16);
            else
                arrow(hdc, 160, x2+13, y2+4);
        }
    } else
    {
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        if (from < to)
        {
            if(y1 == y2 && y1 == y0)
                arrow(hdc, 0, x2-16, y2);
            else if (y1 == y2 && y1 == endY)
                arrow(hdc, 180, x2-16, y2);
            else if (x1 == x2 && from == 3)
                arrow(hdc, -90, x2, y2-16);
            else if (x1 == x2)
                arrow(hdc, 90, x2, y2+16);
        } else if (from > to)
            if(y1 == y2 && y1 == y0)
                arrow(hdc, 180, x2+16, y2);
            else if (y1 == y2 && y1 == endY)
                arrow(hdc, 0, x2-16, y2);
            else if (x1 == x2)
                arrow(hdc, 90, x2, y2+16);
    }
}

void drawEdges(HDC hdc, graph* gr, int n, int oriented)
{
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    int** adjacencyMatrix = gr->adjacencyMatrix;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            //для неорінтовного
            if(oriented == 0 && adjacencyMatrix[i][j] && i <= j)
            {
                 drawEdgeNotOrient(hdc, pen, gr, i, j, 0);
            }
            //для оріентованого
            else if(oriented == 1 && adjacencyMatrix[i][j])
            {
                drawEdgeOrient(hdc, pen, gr, i, j);
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

void drawLoop(HDC hdc, int x0, int y0, int endX, int x, int y, char w[17], int withW)
{
    if(x == x0)
    {
        Arc(hdc, x-50, y+10, x, y-10, x, y, x, y);
        if(withW)
            TextOut(hdc, x-40, y, w, 3);
    }
    else if (x > x0 && x < endX)
    {
        if(y == y0)
            Arc(hdc, x-10, y-50, x+10, y, x, y, x, y);
        else
            Arc(hdc, x-10, y+50, x+10, y, x, y, x, y);
    }
    else
    {
        Arc(hdc, x+50, y+10, x, y-10, x, y, x, y);
        if(withW)
            TextOut(hdc, x+20, y, w, 3);
    }
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

void drawDoubleArc(HDC hdc, int x1, int y1, int x2, int y2, int midX, int midY, int k)
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

