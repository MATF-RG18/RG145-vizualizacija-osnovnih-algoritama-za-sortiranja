#ifndef __CALLBACKFUNC_HPP__
#define __CALLBACKFUNC_HPP__ 1

#include <iostream>
#include <GL/glut.h>

#define MAX_ARR_BARS 20
#define MAX_ARR_SPHERES 10
#define PI 3.141592653589793

struct Sphere{
    GLfloat radius;
    GLfloat x_axis;
    GLfloat y_axis;
    GLfloat z_axis;
};

extern Sphere array_of_spheres[10];
extern int start_screen;
extern int global_i, global_j, swapping_ongonig;
extern int* array;
extern int array_lenght;
extern int sorting;
extern int window_width;
extern int window_height;
extern GLfloat lineWidthRange[2];
extern int type_of_sort;
extern std::string sorting_string[4];

void drawSphere(Sphere s);
void drawArrayOfSpheres(void);
void init_array_of_spheres();
void init(void);
void init_callbacks(void);
void on_display(void);
void on_display1(void);
// deo sa osvetljenjem prekucan sa casa
void on_display2(void);
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);
// crta mrezu po kojoj se crtaju kulice
void drawGrid(void);

void sorting_spheres_text(void);
void display(void);

void init_array(int lenght);
//funkcija preuzeta sa interneta
void bitmap_output(float x, float y, std::string string, void *font);
void sorting_bars_text(void);
void display_start_screen_text(void);
void draw_circle(float radius, float x, float y);
// crta jedan kvadar
void draw_cuboid(int height, int indicator);
// iscrtava kvadar za svaki element niza prema njegovoj velicini
void draw_array();


#endif