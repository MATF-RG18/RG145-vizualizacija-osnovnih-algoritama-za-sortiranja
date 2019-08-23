#ifndef __CALLBACKFUNC_HPP__
#define __CALLBACKFUNC_HPP__ 1

#include <iostream>
#include <GL/glut.h>

#define MAX_ARR_BARS 20
#define MAX_ARR_SPHERES 10
#define PI 3.141592653589793

// struktura koja cuva podatke o loptama
// velicinu, i njihov polozaj u prostoru
struct Sphere{
    GLfloat radius;
    GLfloat x_axis;
    GLfloat y_axis;
    GLfloat z_axis;
};

// brzina kojom se izvrsava algoritam
extern int speed; 
// izbor  brizina
extern int speed_for_bars[5]; 
extern int speed_for_spheres[5]; 

extern Sphere array_of_spheres[10];
extern int array_lenght;
extern int* array;

extern int sorting;
extern int start_screen;
// da li se trenutno menja pozicija elementima kod sfera
extern int swapping_ongonig; 

extern int global_i, global_j;

extern int window_width;
extern int window_height;
extern GLfloat lineWidthRange[2];

extern int type_of_sort;
extern std::string sorting_string[3];

void draw_circle(float radius, float x, float y);
void drawGrid(void);
void drawSphere(Sphere s);
void drawArrayOfSpheres(void);
void draw_cuboid(int height, int indicator);
void draw_array();

void init_array_of_spheres();
void init_array(int lenght);

void init_callbacks(void);
void barTimer(int value);
void sphereTimer(int value);
void on_display(void);
void on_display1(void);
void on_display2(void);
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);

void write_text(float x, float y, std::string string, void *font);
void sorting_bars_text(void);
void sorting_spheres_text(void);
void display_start_screen_text(void);

#endif