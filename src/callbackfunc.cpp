#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <GL/glut.h>
#include "callbackfunc.hpp"
#include "sorting.hpp"

int sorting = 0;
int array_length = 0;
int* array;
int window_width = 1200;
int window_height = 1000;
GLfloat lineWidthRange[2] = {0.0f, 5.0f};
int sort_count = 0;
std::string sorting_string[4] = {"Selection Sort","Insertion Sort", "Bubble Sort", "Quick Sort"};

void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0f, 3.0f, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0, 0, 0, 1);
    
    glTranslatef(-11, 3, -45);
    glRotatef(40, 1, 0, 0);
    
    display_text();
    drawGrid();
    draw_array();
    
    glutSwapBuffers();
}

void on_reshape(int width, int height){
    window_width = width;
    window_height = height;
}
void on_keyboard(unsigned char key, int x, int y){
    if(sorting == 0){
        switch(key){
            case 27: 
                exit(EXIT_SUCCESS);
                break;
            case 's': case 'S':{
                sorting = 1;
                break;
            }
            case 'r': case 'R':{
            init_array(MAX_ARR_LENGHT);
            glutPostRedisplay();break;
            }
            case 'a': case 'A':{
                sort_count = (sort_count + 1) % 4;
            }
        }
    }else{
        switch(key){
            case 'p': case 'P':{
                sorting = 0;
                break;
            }
        }
    }
}
void on_timer(int value){
    
}

void init_callbacks(void) {
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
}

void drawGrid(){
    int i;
    for(i=0;i<46;i++){
        glPushMatrix();
        if(i < 23){
            glTranslatef(0, 0, i);
        }
        if(i >= 23){
            glTranslatef(i-23, 0, 0);
            glRotatef(-90, 0, 1, 0);
        }
        glColor3f(1, 1, 1);
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(1.0f);
        glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(22, 0, 0);
        glEnd();
        
        glPopMatrix();
    }
}

void init_array(int lenght){
    beg[0] = 0;
    ending[0] = MAX_ARR_LENGHT;
    array_length = lenght;
    array = (int*) malloc(sizeof(int) * array_length);
    for(int i=0; i < array_length; i++){
        array[i] = rand() % MAX_ARR_LENGHT + 1;
    }
}

void draw_cuboid(int height, int width){
    glBegin(GL_QUADS);
    // top
    glColor3f(1.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
        
    glVertex3f(-0.5f, 0.5f * height, 0.5f);
    glVertex3f(0.5f, 0.5f * height, 0.5f);
    glVertex3f(0.5f, 0.5f * height, -0.5f);
    glVertex3f(-0.5f, 0.5f * height, -0.5f);
    
    glEnd();
	
    glBegin(GL_QUADS);
    // front
    glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
        
    glVertex3f(0.5f, 0, 0.5f);
    glVertex3f(0.5f, 0.5f * height, 0.5f);
    glVertex3f(-0.5f, 0.5f * height, 0.5f);
    glVertex3f(-0.5f, 0, 0.5f);	
    glEnd();
    
    glBegin(GL_QUADS);
    // right
    glColor3f(0.0f, 0.0f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);

    glVertex3f(0.5f, 0.5f * height, -0.5f);
    glVertex3f(0.5f, 0.5f * height, 0.5f);
    glVertex3f(0.5f, 0, 0.5f);
    glVertex3f(0.5f, 0, -0.5f);
    
    glEnd();
    
    glBegin(GL_QUADS);
    // left
    glColor3f(0.0f, 0.0f, 0.5f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    
    glVertex3f(-0.5f, 0, 0.5f);
    glVertex3f(-0.5f, 0.5f * height, 0.5f);
    glVertex3f(-0.5f, 0.5f * height, -0.5f);
    glVertex3f(-0.5f, 0, -0.5f);
    
    glEnd();
    
    glBegin(GL_QUADS);
    // bottom
    glColor3f(0.5f, 0.0f, 0.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
        
    glVertex3f(0.5f, 0, 0.5f);
    glVertex3f(-0.5f, 0, 0.5f);
    glVertex3f(-0.5f, 0, -0.5f);
    glVertex3f(0.5f, 0, -0.5f);
 	
    glEnd();
 	
    glBegin(GL_QUADS);
    // back
    glColor3f(0.0f, 0.5f, 0.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    
    glVertex3f(0.5f, 0.5f * height, -0.5f);
    glVertex3f(0.5f, 0, -0.5f);
    glVertex3f(-0.5f, 0, -0.5f);
    glVertex3f(-0.5f, 0.5f * height, -0.5f);	
    
    glEnd();
}

void draw_array(){
    glTranslatef(1, 0, 10);
    for(int i=0; i<array_length; i++){
        draw_cuboid(array[i], 0);
        glTranslatef(1, 0, 0);
    }
    glTranslatef(-1, 0, -10);
}
void bitmap_output(float x, float y, std::string string, void *font)
{
    glPushMatrix();
	int len, i;

	glRasterPos2f(x, y);
	len = string.size();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
    glPopMatrix();
}

void display_text()
{
	glColor3f(0.6f, 0.137255, 0.556863);
	bitmap_output(-3, -50, "VIZUELIZACIJA ALGORITMA",   GLUT_BITMAP_TIMES_ROMAN_24 );
	glBegin(GL_LINE_LOOP);
		glVertex2f(-4, -49);
		glVertex2f(-20, -49);
	glEnd();

        glBegin(GL_LINE_LOOP);
		glVertex2f(42, -49);
		glVertex2f(22, -49);
	glEnd();


	if (sorting == 0)
	{
		bitmap_output(-5, 17, "Komande:",GLUT_BITMAP_TIMES_ROMAN_24);
                glTranslatef(-5.3,16.3,0);
                draw_circle();
                glTranslatef(5.3,-16.3,0);
		bitmap_output(-5, 16, "Pritiskom na s algoritam se startuje",GLUT_BITMAP_TIMES_ROMAN_24);
                glTranslatef(-5.6,15.3,0);
                draw_circle();
                glTranslatef(5.6,-15.3,0);
		bitmap_output(-5.3f, 15, "Pritiskom na a menja se algoritam",GLUT_BITMAP_TIMES_ROMAN_24);
                glTranslatef(-5.9,14.3,0);
                draw_circle();
                glTranslatef(5.9,-14.3,0);
		bitmap_output(-5.6, 14, "Pritiskom na r niz se randomizuje",GLUT_BITMAP_TIMES_ROMAN_24);
                glTranslatef(-6.2,13.3,0);
                draw_circle();
                glTranslatef(6.2,-13.3,0);
		bitmap_output(-5.9, 13, "Esc za izlaz iz programa",GLUT_BITMAP_TIMES_ROMAN_24);
                glTranslatef(-6.5,12.3,0);
                draw_circle();
                glTranslatef(6.5,-12.3,0);
		bitmap_output(-6.2, 12, "Izabrani sort: ",GLUT_BITMAP_TIMES_ROMAN_24);
		bitmap_output(-6.5, 11, sorting_string[sort_count],GLUT_BITMAP_9_BY_15);
	}
	else if (sorting == 1)	// while sorting
	{
		glColor3f(0.5,0.5,0.5);
		bitmap_output(-5, 17, "Niz se sortira...",GLUT_BITMAP_9_BY_15);
		bitmap_output(-5, 16, "Pritisni p za pauzu.",GLUT_BITMAP_9_BY_15);
		glColor3f(0.0,0.0,0.0);
	}
}

void draw_circle(){
    glPushMatrix();
    float radius = 0.15;
    glPushMatrix();
    glColor3f(0.2, 0.3, 0.5);  
    glBegin(GL_POLYGON);
    for(double i = 0; i < 2 * PI; i += PI / 6) 
        glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
    glEnd();
    glPopMatrix();
}