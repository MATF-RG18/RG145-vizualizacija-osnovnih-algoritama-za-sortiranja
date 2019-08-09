#include <iostream>
#include <cstdio>
#include <ctime>
#include <GL/glut.h>
#include "callbackfunc.hpp"
#include "sorting.hpp"

using namespace std;


int main(int argc, char **argv){
    //postavljanje seed-a
    srand(time(NULL));
    
    //postavljanje dozvoljenih vrednosti za debljinu linije
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
    
    //inicijalizacija glut funkcija i postavljanje prozora
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-window_width)/2, (glutGet(GLUT_SCREEN_HEIGHT)-window_height)/2);
    glutCreateWindow("Sortiranje");
    
    //inicijalizacija callbackfunkcija
    init_callbacks();

    //ulazak u glavnu petlju
    glutMainLoop();
}
