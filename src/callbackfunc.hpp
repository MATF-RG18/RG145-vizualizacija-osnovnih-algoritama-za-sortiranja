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

// niz koji cuva podatke o 10 sfera
extern Sphere array_of_spheres[10];
// promenljiva koja cuva informaciju da li je 
// trenutni prozor pocetni ili ne
extern int start_screen;
// cuvaju inormaciju o indeksima u sortiranju
extern int global_i, global_j;
// da li se trenutno menja mesto dvema sferama ili ne
extern int  swapping_ongonig;
// niz u kome se cuvaju trenutni elementi 
// koji se sortiraju po vrednosti
extern int* array;
// duzina niza
extern int array_lenght;
// da li se trenutno niz sortira
extern int sorting;

// visina i sirina prozora
extern int window_width;
extern int window_height;

// dozvoljena debljina linije
extern GLfloat lineWidthRange[2];

// trenutni redni br tipa sortiranja
extern int type_of_sort;
// niz sa dozvoljenim algoritmima za sortiranje
extern std::string sorting_string[3];

// fja za iscrtavanje jedne sfere
void drawSphere(Sphere s);
// fja za iscrtavanje niza sfera
void drawArrayOfSpheres(void);
// inicijalizacija niza za sfere
void init_array_of_spheres();

void init_callbacks(void);
void on_display(void);
void on_display1(void);
// deo sa osvetljenjem prekucan sa casa
void on_display2(void);
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);
// crta mrezu po kojoj se crtaju kulice
void drawGrid(void);
// tekst ukoliko sortiramo sfere
void sorting_spheres_text(void);
// inicijalizacija niza
void init_array(int lenght);

//funkcija preuzeta sa interneta
void bitmap_output(float x, float y, std::string string, void *font);
// tekst pre sortiranja kulica
void sorting_bars_text(void);
// tekst pre pojavljivanja pocetnog ekrana
void display_start_screen_text(void);
// nacrtaj kruzic
void draw_circle(float radius, float x, float y);
// crta jedan kvadar
void draw_cuboid(int height, int indicator);
// iscrtava kvadar za svaki element niza prema njegovoj velicini
void draw_array();


#endif