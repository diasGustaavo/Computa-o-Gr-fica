#include "mygl.h"

unsigned char* fb_ptr = NULL;

void InitMyGl(void) {
    fb_ptr = (unsigned char *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * 4 * sizeof(char));	

    for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; ++i) {
        fb_ptr[i * 4] = 0;
        fb_ptr[i * 4 + 1] = 0;
        fb_ptr[i * 4 + 2] = 0;
        fb_ptr[i * 4 + 3] = 255;
    }    
}

unsigned char* GetFBMemPtr(void) {
	return fb_ptr;
}

void CloseMyGl(void) {
    if (!fb_ptr)
        free(fb_ptr);
}

//
// >>> Caro aluno: defina aqui as funções que você implementar <<<
//

void PutPixel(int x, int y, int R, int G, int B, int A) {
    int posicao = ( (x * 4) + (y * 4 * 512) );

    fb_ptr[posicao] = R; // componente R
    posicao++;
    fb_ptr[posicao] = G; // componente G
    posicao++;
    fb_ptr[posicao] = B; // componente B
    posicao++;
    fb_ptr[posicao] = A; // componente A
    posicao++;
}

void DrawLine(int xi, int yi, int xf, int yf, int R, int G, int B, int A){
    int dx = xf - xi;
    int dy = yf - yi;
    float M = (float)dy/dx;

    ////// PRIMEIRO OCTANTE
    ////
    //
    if((0<=M) && (M<=1)){
        if ((xi >= xf) && (yi >= yf)){
            int xiAux = xi;
            int yiAux = yi;
            xi = xf;
            yi = yf;
            xf = xiAux;
            yf = yiAux;
        }

        dx = xf - xi;
        dx = yf - yi;
        int D = 2 * dy - dx;
        int inc_L = 2 * dy;
        int inc_NE = 2 * (dy - dx);


        int x = xi;
        int y = yi;

        PutPixel(x, y, R, G, B, A);

        while (x < xf) {
            if (D <= 0){
                D += inc_L;
                x++;
            }
            else{
                D += inc_NE;
                x++;
                y++;
            }

            PutPixel(x, y, R, G, B, A);
        }
    }

    //////ULTIMO OCTANTE
    ////
    //

    else if((0 > M) && (M >= -1)){
        if ((xi > xf) && (yi < yf)){
            int xiAux = xi;
            int yiAux = yi;
            xi = xf;
            yi = yf;
            xf = xiAux;
            yf = yiAux;
        }

        dx = xf - xi;
        dx = yf - yi;
        int D = 2 * dy + dx;
        int inc_L = 2 * dy;
        int inc_SE = 2 * (dy + dx);
        int x = xi;
        int y = yi;

        PutPixel(x, y, R, G, B, A);

        while (x < xf) {
            if (D > 0){
                D += inc_L;
                x++;
            }
            else{
                D += inc_SE;
                x++;
                y--;
            }

            PutPixel(x, y, R, G, B, A);
        }
    }

    //////PENULTIMO OCTANTE
    /////
    ////
    else if(-1 > M){
        if ((xi > xf) && (yi < yf)){
                int xiAux = xi;
                int yiAux = yi;
                xi = xf;
                yi = yf;
                xf = xiAux;
                yf = yiAux;
            }

            int aux = yi;
            yi = xi;
            xi = aux;
            aux = yf;
            yf = xf;
            xf = aux;
            dx = xf - xi;
            dy = yf - yi;
            int D = 2 * dy + dx;
            int inc_L = 2 * dy;
            int inc_SE = 2 * (dy + dx);
            int x = xi;
            int y = yi;

            PutPixel(y, x, R, G, B, A);

            while (x > xf) {
                if (D < 0){
                    D += inc_L;
                    x--;
                }
                else{
                    D += inc_SE;
                    x--;
                    y++;
                }

                PutPixel(y, x, R, G, B, A);
            }
        }
        else{
            if ((xi > xf) && (yi > yf)){
            int xiAux = xi;
            int yiAux = yi;
            xi = xf;
            yi = yf;
            xf = xiAux;
            yf = yiAux;
        }

        int xfaux = xf;
        int yfaux = yf;
        xf = yi;
        yf = xi;
        xi = yfaux;
        yi = xfaux;
        int dx = xf - xi;
        int dy = yf - yi;
        int D = 2 * dy + dx;
        int inc_L = 2 * dy;
        int inc_NE = 2 * (dy - dx);
        int x = xi;
        int y = yi;

        // printf("putting pixel(fora)... x = %d y = %d R = %d G = %d B = %d A = %d\n", x, y, R, G, B, A);
        PutPixel(y, x, R, G, B, A);

        while (x > xf) {
            if (D > 0){
                // printf("entrou if\n");
                D += inc_L;
                x--;
            }
            else{
                // printf("entrou else\n");
                D += inc_NE;
                x--;
                y--;
            }

            // printf("putting pixel... x = %d y = %d R = %d G = %d B = %d A = %d\n", x, y, R, G, B, A);
            PutPixel(y, x, R, G, B, A);
        }
    }

}

void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int R, int G, int B, int A){
    DrawLine(x1, y1, x2, y2, R, G, B, A);
    DrawLine(x2, y2, x3, y3, R, G, B, A);
    DrawLine(x3, y3, x1, y1, R, G, B, A);
}

// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {
    //
    // >>> Caro aluno: chame aqui as funções que você implementou <<<
    //
    DrawTriangle(0, 0, 256, 512, 512, 0, 255, 255, 0, 255);

    // G
    DrawLine(50, 10, 100, 10, 255, 255, 255, 255);
    DrawLine(50, 10, 50, 70, 255, 255, 255, 255);
    DrawLine(50, 70, 100, 70, 255, 255, 255, 255);
    DrawLine(100, 10, 100, 35, 255, 255, 255, 255);
    DrawLine(100, 35, 75, 35, 255, 255, 255, 255);

    // U
    DrawLine(110, 10, 160, 10, 255, 255, 255, 255);
    DrawLine(110, 10, 110, 70, 255, 255, 255, 255);
    DrawLine(160, 10, 160, 70, 255, 255, 255, 255);

    // G
    DrawLine(170, 10, 220, 10, 255, 255, 255, 255);
    DrawLine(170, 10, 170, 70, 255, 255, 255, 255);
    DrawLine(170, 70, 220, 70, 255, 255, 255, 255);
    DrawLine(220, 10, 220, 35, 255, 255, 255, 255);
    DrawLine(220, 30, 195, 35, 255, 255, 255, 255);

    //A
    DrawLine(230, 10, 230, 70, 255, 255, 255, 255);
    DrawLine(230, 70, 280, 70, 255, 255, 255, 255);
    DrawLine(280, 70, 280, 10, 255, 255, 255, 255);
    DrawLine(280, 35, 230, 45, 255, 255, 255, 255);
}
