#ifndef __CALLBACKFUNC_HPP__
#define __CALLBACKFUNC_HPP__ 1

#include <iostream>
#include <GL/glut.h>

#define MAX_ARR_LENGHT 20
#define PI 3.14

extern int* array;
extern int array_length;
extern int sorting;
extern int window_width;
extern int window_height;
extern GLfloat lineWidthRange[2];
extern int sort_count;
extern std::string sorting_string[4];

void init(void);
void init_callbacks(void);
void on_display(void);
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);
void on_timer(int value);
void drawGrid(void);

void display(void);

void init_array(int lenght);
void draw_cuboid(int height, int width);
void bitmap_output(float x, float y, std::string string, void *font);
void display_text();
void draw_circle();
void draw_array();


#endif