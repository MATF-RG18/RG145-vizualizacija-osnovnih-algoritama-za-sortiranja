#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <GL/glut.h>
#include "callbackfunc.hpp"
#include "sorting.hpp"

int sorting = 0;
int array_length = 0;
int* array;
int window_width = 1000;
int window_height = 800;
GLfloat lineWidthRange[2] = {0.0f, 5.0f};

void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0f, 3.0f, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0, 0, 0, 1);
    
    glTranslatef(-11, 5, -45);
    glRotatef(40, 1, 0, 0);
    
    drawGrid();
    draw_array();
    
    glutSwapBuffers();
}

void on_reshape(int width, int height){
    window_width = width;
    window_height = height;
}
void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27: 
            exit(EXIT_SUCCESS);break;
        case 's': case 'S':{
            sorting = 1;
            break;
        }
        case 'r': case 'R':{
            init_array(MAX_ARR_LENGHT);
            glutPostRedisplay();break;
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
//         if(i > 21){
//             glColor3f(1, 0, 0);
//             glTranslatef(10, 0, 0.4);        
//             glutWireCube(1);
//             glTranslatef(-10, 0, -0.4);        
//         }
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