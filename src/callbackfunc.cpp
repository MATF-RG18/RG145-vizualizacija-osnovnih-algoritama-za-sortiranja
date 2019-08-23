#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <GL/glut.h>
#include "callbackfunc.hpp"
#include "sorting.hpp"

int start_screen = 0; // da li je pocetni ekran
int sorting = 0; // da li se trenutno sortira
int global_i = 0, global_j = 0, swapping_ongonig = 0; // globalni indeksu za sortiranje
int type_of_sort = 0; // vrsta sort

Sphere array_of_spheres[MAX_ARR_SPHERES]; // niz informacija o sferama
int array_lenght = 0; // duzina niza koji se sortira
int* array; // niz koji se sortira

int window_width = 1200;
int window_height = 800;
GLfloat lineWidthRange[2] = {0.0f, 5.0f}; // dozvoljene vrednosti za debljinu linije
std::string sorting_string[3] = {"Selection Sort","Insertion Sort", "Bubble Sort"}; // dozvoljeni sortovi

int speed = 0;
int speed_for_bars[5] = {1000, 700, 500, 300, 100};
int speed_for_spheres[5] = {70, 60, 50, 30, 10};

// pocetni ekran sa tekstom
void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 10, 0);
    
    display_start_screen_text();
    
    glFlush();
    glutSwapBuffers();
}

// pocetni ekran za sortiranje kulica
void on_display1(void){
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
    
    // iscrtavanje kulica i mreze, ispis teksta
    sorting_bars_text();
    drawGrid();
    draw_array();
    
    glTranslatef(11, -3, 45);
    glRotatef(-40, 1, 0, 0);
    
    glFlush(); 
    glutSwapBuffers();
}

// pocetni ekran za sortiranje sfera
void on_display2(void){
    
    // postavljanje svetla i scene
    GLfloat light_position[] = { 1, 1, 1, 0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
    GLfloat ambient_coeffs[] = { 1.0, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0.0, 0.0, 0.8, 1 };
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    GLfloat shininess = 20;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 10, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glColor3f(1, 1, 0);
    
    // iscrtavanje sfera
    glTranslatef(-4.5, 0, 0);
    drawArrayOfSpheres();
    glTranslatef(4.5, 0, 0);
    
    // onemogucujemo svetlost zbog uticaja na tekst
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    
    // ispis teksta za upravljanje
    glTranslatef(-4.5, 0, 0);
    sorting_spheres_text();
    glTranslatef(4.5, 0, 0);
    
    glFlush(); 
    glutSwapBuffers();
}

void on_reshape(int width, int height){
    glViewport(0, 0,  (GLsizei)width,  (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, (float) width / height, 1, 10);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void on_keyboard(unsigned char key, int x, int y){
    // ako se niz ne sortira mozemo menjati sort, brzinu, randomizujemo ili zapocnemo sortiranje
    // inace mozemo da pauziramo ili izadjemo
    
    if(sorting == 0 && start_screen != 0){
        switch(key){
            case 's': case 'S':{
                // zapocinje se sort
                sorting = 1;
                break;
            }
            case 'r': case 'R':{
                // randomizuje se niz, na osnovu toga da li se sortiraju sfere ili kule
                if(start_screen == 1)
                    init_array(array_lenght);
                else if(start_screen == 2)
                    init_array_of_spheres();
                glutPostRedisplay();
                break;
            }
            case 'a': case 'A':{
                // menjamo algoritam
                type_of_sort = (type_of_sort + 1) % 3;
                break;
            }case 'f':case 'F':{
                // menjamo brzinu
                speed = (speed + 1) % 5;
            }
        }
    }else if(sorting == 1 && start_screen != 0){
        switch(key){
            case 'p': case 'P':{
                // niz se sortira, pa ga pauziramo
                sorting = 0;
                break;
            }
        }
    }else if(start_screen == 0){
        // ako smo na pocetnom ekranu mozemo da izaberemo kule ili sfere
        switch(key){
            case 'k': case 'K':{
                // predstavljanje kulicama
                start_screen = 1;
                init_array(MAX_ARR_BARS);
                glutDisplayFunc(on_display1);
                glutTimerFunc(30, barTimer, 1);
                break;
            }
            case 'l': case 'L':{
                // predstavljanje lopticama
                start_screen = 2;
                init_array(MAX_ARR_SPHERES);
                init_array_of_spheres();
                glutDisplayFunc(on_display2);
                glutTimerFunc(30, sphereTimer, 2);
                break;
            }
        }
    }
    switch(key){
        case 27: 
            exit(EXIT_SUCCESS);
            break;
    }
}


void barTimer(int value){
    if(value != 1)
        return;
    if(sorting){
        switch(type_of_sort){
            case 0: selectionSort(); break;
            case 1: insertionSort();break;
            case 2: bubbleSort();break;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(speed_for_bars[speed], barTimer, 1);
}
void sphereTimer(int value){
    if(value != 2)
        return;
    
    if(sorting){
        switch(type_of_sort){
            case 0: selectionSortSphere(); break;
            case 1: insertionSortSphere();break;
            case 2: bubbleSortSphere();break;
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(speed_for_spheres[speed], sphereTimer, 2);
}

void init_callbacks(void) {
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
}

void init_array(int lenght){
    global_i = global_j = 0;
    array_lenght = lenght;
    array = (int*) malloc(sizeof(int) * lenght);
    for(int i=0; i < lenght; i++){
        array[i] = rand() % lenght + 1;
    }
}

void init_array_of_spheres(){
    // inicijalizujemo globalne promenljive 
    // u slucaju randomizacije da bi postavili na pocetno stanje
    global_i = global_j = swapping_ongonig = 0;
    
    for(int i=0;i<MAX_ARR_SPHERES;i++){
        array[i] = rand() % 10 + 1;
        array_of_spheres[i].radius = array[i] / 20.0;
        
        // inicijalizujemo vrednosti kooordinata
        array_of_spheres[i].y_axis = 0.2;
        if(i == 0){
            array_of_spheres[i].x_axis = 0;
        }else{
            array_of_spheres[i].x_axis = array_of_spheres[i-1].x_axis + 1;            
        }
        
    }
}

void drawGrid(){
    
    for(int i=0;i<46;i++){
        glPushMatrix();
        
        if(i < 23){
            // horizontalne
            glTranslatef(0, 0, i);
        }
        if(i >= 23){
            // vertikalne
            glTranslatef(i-23, 0, 0);
            glRotatef(-90, 0, 1, 0);
        }
        
        // crtanje bele linije
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

void draw_circle(float radius, float x, float y){
    glColor3f(0.6f, 0.137255, 0.556863);	
    glTranslatef(x, y, 0);
    
    glPushMatrix();
        glBegin(GL_POLYGON);
            for(double i = 0; i < 2 * PI; i += PI / 6) 
                glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
        glEnd();
    glPopMatrix();
    
    glTranslatef(-x, -y, 0);
}

void drawSphere(Sphere s){
    glPushMatrix();
    glTranslatef(s.x_axis, s.y_axis,0);
    glutSolidSphere(s.radius, 50, 50);
    glTranslatef(-s.x_axis, -s.y_axis,0);
    glPopMatrix;
}

void drawArrayOfSpheres(void){
    for(int i=0;i<10;i++){
        drawSphere(array_of_spheres[i]);
    }
}

void draw_cuboid(int height, int indicator){
    // omogucimo normalizaciju
    glEnable(GL_NORMALIZE);
    
    // pravougaonik na vrhu
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glNormal3f(0.0f, 1.0f, 0.0f);
        
        glVertex3f(-0.5f, 0.5f * height, 0.5f);
        glVertex3f(0.5f, 0.5f * height, 0.5f);
        glVertex3f(0.5f, 0.5f * height, -0.5f);
        glVertex3f(-0.5f, 0.5f * height, -0.5f);
    glEnd();
    
    // dodavanje okvira oko pravougaonika da 
    // bi zamene bile ociglednije
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        
        glVertex3f(0.5f, 0, 0.5f);
        glVertex3f(0.5f, 0.5f * height, 0.5f);
        glVertex3f(-0.5f, 0.5f * height, 0.5f);
        glVertex3f(-0.5f, 0, 0.5f);
    glEnd();
    glLineWidth(1.0f);
    
    // prednji pravougaonik
    glBegin(GL_QUADS);
        // u slucaju zamene boji te dve kule drugom bojom
        if(indicator == 0)
            glColor3f(0.0f, 1.0f, 0.0f);
        else
            glColor3f(1.0f, 1.0f, 0.0f);        
        glNormal3f(0.0f, 0.0f, 1.0f);
        
        glVertex3f(0.5f, 0, 0.5f);
        glVertex3f(0.5f, 0.5f * height, 0.5f);
        glVertex3f(-0.5f, 0.5f * height, 0.5f);
        glVertex3f(-0.5f, 0, 0.5f);	
    glEnd();
    
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f * height, -0.5f);
    glVertex3f(0.5f, 0.5f * height, 0.5f);
    glVertex3f(0.5f, 0, 0.5f);
    glVertex3f(0.5f, 0, -0.5f);
    glEnd();
    glLineWidth(1.0f);
    
    // desni pravougaonik
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        glNormal3f(1.0f, 0.0f, 0.0f);

        glVertex3f(0.5f, 0.5f * height, -0.5f);
        glVertex3f(0.5f, 0.5f * height, 0.5f);
        glVertex3f(0.5f, 0, 0.5f);
        glVertex3f(0.5f, 0, -0.5f);
    glEnd();
    
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        
        glVertex3f(-0.5f, 0, 0.5f);
        glVertex3f(-0.5f, 0.5f * height, 0.5f);
        glVertex3f(-0.5f, 0.5f * height, -0.5f);
        glVertex3f(-0.5f, 0, -0.5f);
    glEnd();
    glLineWidth(1.0f);
    
    // levi pravougaonik
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.5f);
        glNormal3f(-1.0f, 0.0f, 0.0f);
    
        glVertex3f(-0.5f, 0, 0.5f);
        glVertex3f(-0.5f, 0.5f * height, 0.5f);
        glVertex3f(-0.5f, 0.5f * height, -0.5f);
        glVertex3f(-0.5f, 0, -0.5f);
    glEnd();
    
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        
        glVertex3f(0.5f, 0.5f * height, -0.5f);
        glVertex3f(0.5f, 0, -0.5f);
        glVertex3f(-0.5f, 0, -0.5f);
        glVertex3f(-0.5f, 0.5f * height, -0.5f);
    glEnd();
    glLineWidth(1.0f);
    
    // zadnji pravougaonik
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.5f, 0.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
    
        glVertex3f(0.5f, 0.5f * height, -0.5f);
        glVertex3f(0.5f, 0, -0.5f);
        glVertex3f(-0.5f, 0, -0.5f);
        glVertex3f(-0.5f, 0.5f * height, -0.5f);	
    glEnd();
    
    // donji pravougaonik
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.0f, 0.0f);
        glNormal3f(0.0f, -1.0f, 0.0f);
        
        glVertex3f(0.5f, 0, 0.5f);
        glVertex3f(-0.5f, 0, 0.5f);
        glVertex3f(-0.5f, 0, -0.5f);
        glVertex3f(0.5f, 0, -0.5f);
    glEnd();
}

void draw_array(){
    glTranslatef(1, 0, 10);
    
    // cuva razmak izmedju brojeva
    float razmak = 0;
    
    for(int i=0; i<MAX_ARR_BARS; i++){
        // provera da li je trenutni element koji se iscrtava 
        // onaj koji menja mesto, ako jeste saljemo indikator 
        // funkciji za iscrtavanje
        
        if(q == i){
            draw_cuboid(array[i], 1);
            q = -1;
        }else if(p == i){
            draw_cuboid(array[i], 1);
            p = -1;
        }else{
            draw_cuboid(array[i], 0);
        }
        
        // proveravamo da li je broj dvocifren ili jednocifren zbog razmaka
        if(std::to_string(array[i]).size() == 2){
            glColor3f(1.0, 0.0, 0.0);
            write_text(razmak, 12, (std::to_string(array[i])), GLUT_BITMAP_TIMES_ROMAN_24);
            razmak -= 0.05;
        }else{
            glColor3d(1.0, 0.0, 0.0);
            write_text(razmak + 0.2,  12, (std::to_string(array[i])), GLUT_BITMAP_TIMES_ROMAN_24);
            razmak -= 0.025;
        }
        
        glTranslatef(1, 0, 0);
    }
    
    glTranslatef(-1, 0, -10);
}

// preuzeta sa interneta
void write_text(float x, float y, std::string string, void *font){
    glPushMatrix();
        int len, i;
        
        glRasterPos2f(x, y);
        len = string.size();
        glScalef(0.009f,-0.08f,0);
        for (i = 0; i < len; i++) {
                glutBitmapCharacter(font, string[i]);
        }
    glPopMatrix();
}

void sorting_bars_text(void){    
    glColor3f(0.6f, 0.137255, 0.556863);
    write_text(-3, -50, "VIZUELIZACIJA ALGORITMA",   GLUT_BITMAP_TIMES_ROMAN_24 );
    glLineWidth(3);
    
    // linija pre teksta
    glBegin(GL_LINE_LOOP);
        glVertex2f(-4, -49);
        glVertex2f(-20, -49);
    glEnd();
    
    // linija posle teksta
    glBegin(GL_LINE_LOOP);
        glVertex2f(42, -49);
        glVertex2f(22, -49);
    glEnd();

    // ukoliko se niz ne sortira prikazi komande 
    // ukoliko se sortira prikazi komandu pauziranja
    
    if(sorting == 0){        
        write_text(-5, 17, "Komande:",GLUT_BITMAP_TIMES_ROMAN_24);
        
        // iscrtavanje tackice pre teksta i tekst
        draw_circle(0.15, -5.3, 16.3);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-5, 16, "Pritiskom na s algoritam se startuje",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.15, -5.6, 15.3);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-5.3f, 15, "Pritiskom na a menja se algoritam",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.15,-5.9,14.3);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-5.6, 14, "Pritiskom na r niz se randomizuje",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.15,-6.2,13.3);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-5.9, 13, "Esc za izlaz iz programa",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.15, -6.5,12.3);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-6.2, 12, "Izabrani sort: ",GLUT_BITMAP_TIMES_ROMAN_24);
        
        write_text(-6.5, 11, sorting_string[type_of_sort],GLUT_BITMAP_9_BY_15);
        
        draw_circle(0.15, 11.6,16.3);
        glColor3f(0.87, 0.6, 0.8);
        write_text(12, 16, "Promeniti brzinu algoritma pritiskom na f:",GLUT_BITMAP_TIMES_ROMAN_24);
        switch(speed){
            case 0:
                glColor3f(0.87, 0.6, 0.8);
                write_text(13, 15, "vrlo sporo",GLUT_BITMAP_9_BY_15);
                break;
            case 1:
                glColor3f(0.87, 0.6, 0.8);
                write_text(13, 15, "sporo",GLUT_BITMAP_9_BY_15);
                break;
            case 2:
                glColor3f(0.87, 0.6, 0.8);
                write_text(13, 15, "srednje",GLUT_BITMAP_9_BY_15);
                break;
            case 3:
                glColor3f(0.87, 0.6, 0.8);
                write_text(13, 15, "brzo",GLUT_BITMAP_9_BY_15);
                break;
            case 4:
                glColor3f(0.87, 0.6, 0.8);
                write_text(13, 15, "vrlo brzo",GLUT_BITMAP_9_BY_15);
                break;
        }
        
    }else if(sorting == 1){
        glColor3f(0.5,0.5,0.5);
        
        write_text(-5, 17, "Niz se sortira... Za promenu algoritma, randomizaciju niza ili izlazak iz programa prvo se mora pauzirati. ", GLUT_BITMAP_9_BY_15);
        
        write_text(-5, 16, "Pritisni p za pauzu.",GLUT_BITMAP_9_BY_15);
    }
}

void sorting_spheres_text(void){
    glColor3f(0.6f, 0.137255, 0.556863);
    write_text(2.8, -2.0, "VIZUELIZACIJA ALGORITMA",   GLUT_BITMAP_TIMES_ROMAN_24 );

    // linija pre teksta
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.8, -1.94);
        glVertex2f(2.75, -1.94);
    glEnd();
    
    // linija posle teksta
    glBegin(GL_LINE_LOOP);
        glVertex2f(5.85, -1.94);
        glVertex2f(9.5, -1.94);
    glEnd();
    
    // ukoliko se niz ne sortira prikazi komande 
    // ukoliko se ne sortira prikazi komandu pauziranja
    if(sorting == 0){
        glColor3f(0.6f, 0.137255, 0.556863);
        write_text(-0.5, 3, "Komande:",GLUT_BITMAP_TIMES_ROMAN_24);

        // iscrtavanje tackice pre teksta i tekst
        draw_circle(0.03, -0.4, 2.85);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-0.32, 2.8, "Pritiskom na s algoritam se startuje",GLUT_BITMAP_TIMES_ROMAN_24);
    
        draw_circle(0.03, -0.4, 2.65);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-0.32, 2.6, "Pritiskom na a menja se algoritam",GLUT_BITMAP_TIMES_ROMAN_24);
    
        draw_circle(0.03,-0.4,2.45);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-0.32, 2.4, "Pritiskom na r niz se randomizuje",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.03,-0.4,2.25);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-0.32, 2.2, "Esc za izlaz iz programa",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.03, -0.4, 2.05);
        glColor3f(0.87, 0.6, 0.8);
        write_text(-0.32, 2.0, "Izabrani sort: ",GLUT_BITMAP_TIMES_ROMAN_24);
        
        write_text(-0.2, 1.8, sorting_string[type_of_sort],GLUT_BITMAP_9_BY_15);
        
        draw_circle(0.03, 4.4, 2.85);
        glColor3f(0.87, 0.6, 0.8);
        write_text(4.5, 2.8, "Promeniti brzinu algoritma pritiskom na f:",GLUT_BITMAP_TIMES_ROMAN_24);
        switch(speed){
            case 0:
                glColor3f(0.87, 0.6, 0.8);
                write_text(4.7, 2.6, "vrlo sporo",GLUT_BITMAP_9_BY_15);
                break;
            case 1:
                glColor3f(0.87, 0.6, 0.8);
                write_text(4.7, 2.6, "sporo",GLUT_BITMAP_9_BY_15);
                break;
            case 2:
                glColor3f(0.87, 0.6, 0.8);
                write_text(4.7, 2.6, "srednje",GLUT_BITMAP_9_BY_15);
                break;
            case 3:
                glColor3f(0.87, 0.6, 0.8);
                write_text(4.7, 2.6, "brzo",GLUT_BITMAP_9_BY_15);
                break;
            case 4:
                glColor3f(0.87, 0.6, 0.8);
                write_text(4.7, 2.6, "vrlo brzo",GLUT_BITMAP_9_BY_15);
                break;
        }
        
    }else if(sorting == 1){
        glColor3f(0.5,0.5,0.5);
        
        write_text(0, 3, "Niz se sortira... Za promenu algoritma, randomizaciju niza ili izlazak iz programa prvo se mora pauzirati. ", GLUT_BITMAP_9_BY_15);
        
        write_text(0.2, 2.8, "Pritisni p za pauzu.",GLUT_BITMAP_9_BY_15);
    }
}

void display_start_screen_text(void){
    glTranslatef(0, -1.5, 0); 
    
    // iscrtavanje okvira oko teksta i tekst
    glColor3f(0.439216f, 0.858824, 0.576471);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
            glVertex2f(-3, 2);
            glVertex2f(3, 2);
            glVertex2f(3, 0.5);
            glVertex2f(-3, 0.5);
    glEnd();
    
    glColor3f(0.439216f, 0.858824, 0.576471);
    write_text(-2.7, 1.7, "PREDSTAVLJANJE ALGORITAMA ZA SORTIRANJE: ",   GLUT_BITMAP_TIMES_ROMAN_24 );
    
    draw_circle(0.05, -2.6, 1.47);
    glColor3f(0.439216f, 0.858824, 0.576471);
    write_text(-2.5, 1.4, "za predstavljanje algoritama kulicama pritisnite k...",   GLUT_BITMAP_TIMES_ROMAN_24 );
    
    draw_circle(0.05, -2.6, 1.17);
    glColor3f(0.439216f, 0.858824, 0.576471);
    write_text(-2.5, 1.1, "za predstavljanje algoritama lopticama pritisnite l...",   GLUT_BITMAP_TIMES_ROMAN_24 );
    
    glTranslatef(0, 1.5, 0);
}