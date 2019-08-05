#include <iostream>
#include <cstdio>
#include <ctime>
#include <GL/glut.h>
#include "callbackfunc.hpp"
#include "sorting.hpp"

using namespace std;


int main(int argc, char **argv){
    srand(time(NULL));
    init_array(MAX_ARR_LENGHT);
    
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-window_width)/2,
                       (glutGet(GLUT_SCREEN_HEIGHT)-window_height)/2);
    glutCreateWindow("Sortiranje");
    init_callbacks();

    glutTimerFunc(300,glutTimer,1);
    glutMainLoop();
}