#ifndef MYGL_H
#define MYGL_H

#include <stdlib.h>
#include <string.h>

#include "core.h"

void InitMyGl(void); // Inicializa o frame buffer 
unsigned char* GetFBMemPtr(void); // Retorna o ponteiro do framebuffer buffer
void CloseMyGl(void); // Desaloca a memória do framebuffer

// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);

//
// >>> Caro aluno: declare aqui as funções que você implementar <<<
//

void PutPixel(int x, int y, int R, int G, int B, int A);
void MidPointLine(int xi, int yi, int xf, int yf, int R, int G, int B, int A);
void MidPointLineEsp(int xi, int yi, int xf, int yf, int R, int G, int B, int A);
void MidPointLinePraValer(int xi, int yi, int xf, int yf, int R, int G, int B, int A);
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int R, int G, int B, int A);

#endif  // MYGL_H
