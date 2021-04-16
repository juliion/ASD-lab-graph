#include<windows.h>
#include<math.h>
#include <stdio.h>
#include "graph.h"
#include "draw_graph.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[]="Лабораторна робота 3";
const int  N = 10;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName=ProgName;
    w.hInstance=hInstance;
    w.lpfnWndProc=WndProc;
    w.hCursor=LoadCursor(NULL, IDC_ARROW);
    w.hIcon=0;
    w.lpszMenuName=0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style=CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;

    hWnd=CreateWindow(ProgName,
        "Лабораторна робота 3. Виконала Іонова Ю.",
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        600,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    printMatrix();
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    while(GetMessage(&lpMsg, hWnd, 0, 0)) {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    return(lpMsg.wParam);
    }


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
    {
    HDC hdc;
    PAINTSTRUCT ps;

    switch(messg){
        case WM_PAINT :
            hdc = BeginPaint(hWnd, &ps);
            int x0 = 100;
            int y0 = 100;
            int dist = 100;
            graph* graphNotOrient = createGraph(N, 0);
            setCoordinatesVertices(N, x0, y0, dist, graphNotOrient->vertices);
            drawEdge(hdc, graphNotOrient->adjacencyMatrix, graphNotOrient->vertices, N, 0);
            drawVertices(hdc, graphNotOrient->vertices, N);
            graph* graphOrient = createGraph(N, 1);
            setCoordinatesVertices(N, x0, y0*5, dist, graphOrient->vertices);
            drawEdge(hdc, graphOrient->adjacencyMatrix, graphOrient->vertices, N, 1);
            drawVertices(hdc, graphOrient->vertices, N);

            EndPaint(hWnd, &ps);//малювання закінчене
            break;

//сообщение выхода - разрушение окна
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
    }
    return 0;
}

void printMatrix()
{
    AllocConsole();
    FILE* pf;
    freopen_s(&pf, "CONOUT$", "w", stdout);
    int** matrix = createAdjacencyMatrix(N);
    printf("Adjacency matrix:\n");
    printf("    ");
    for (int k = 0; k < N; k++)
        printf("%d  ", k + 1);
    printf("\n    -----------------------------\n");
	for (int i = 0; i < N; i++)
	{
	    if(i >= 9)
            printf("%d| ", i + 1);
        else
	        printf("%d | ", i + 1);
		for (int j = 0; j < N; j++)
		{
			printf("%d  ", matrix[i][j]);
		}
		printf("\n");
	}
}
