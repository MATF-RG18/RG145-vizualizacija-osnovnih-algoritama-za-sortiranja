#ifndef CALLBACKFUNC_HPP
#define CALLBACKFUNC_HPP

#include <iostream>
#include <GL/glut.h>


static int window_width = 1000;
static int window_height = 800;
static GLfloat lineWidthRange[2] = {0.0f, 5.0f};

void init(void);
void init_callbacks(void);
void on_display(void);
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);
void on_timer(int value);
void drawGrid(void);

int* init_array(int lenght);
void draw_cuboid(int height, int width);


#endif