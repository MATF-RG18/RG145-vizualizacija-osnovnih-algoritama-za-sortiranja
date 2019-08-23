#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <GL/glut.h>
#include "callbackfunc.hpp"
#include "sorting.hpp"

int start_screen = 0;
Sphere array_of_spheres[10];
int sorting = 0;
int array_lenght = 0;
int global_i = 0, global_j = 0, swapping_ongonig = 0; 
int* array;
int window_width = 1200;
int window_height = 800;
GLfloat lineWidthRange[2] = {0.0f, 5.0f};
int type_of_sort = 0;
std::string sorting_string[3] = {"Selection Sort","Insertion Sort", "Bubble Sort"};

void on_display(void){
    //postavljanje pozadine ekrana
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Podesava se vidna tacka
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 10, 0);
    
    display_start_screen_text();
    
    glFlush();
    glutSwapBuffers();
}

void on_display1(void){
    // ciscenje bafera
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //podesavanje pogleda
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0f, 3.0f, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    
    // podesavanje boje pozadine
    glClearColor(0, 0, 0, 1);
    
    glTranslatef(-11, 3, -45);
    glRotatef(40, 1, 0, 0);
    
    // iscrtavanje mreze, teksta i niza
    sorting_bars_text();
    drawGrid();
    draw_array();
    
    glFlush(); 
    glutSwapBuffers();
}

void on_display2(void){
    // pozicija svetla
    GLfloat light_position[] = { 1, 1, 1, 0 };
    //ambijentalna boja svetla
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
    // Difuzna boja svetla
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    // Spekularna boja svetla
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
    // Koeficijenti ambijentalne refleksije materijala
    GLfloat ambient_coeffs[] = { 1.0, 0.1, 0.1, 1 };
    // Koeficijenti difuzne refleksije materijala
    GLfloat diffuse_coeffs[] = { 0.0, 0.0, 0.8, 1 };
    // Koeficijenti spekularne refleksije materijala.
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    // Koeficijent glatkosti materijala.
    GLfloat shininess = 20;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    
    // Podesava se vidna tacka
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 10, 0);

    // Ukljucuje se osvjetljenje i podesavaju parametri svetla
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Podesavaju se parametri materijala
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    // Iscrtavanje loptica
    glColor3f(1, 1, 0);
    
    // translacija za bolje prilagodjavanje
    glTranslatef(-4.5, 0, 0);
    drawArrayOfSpheres();
    glTranslatef(4.5, 0, 0);
    
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    
    glTranslatef(-4.5, 0, 0);
    sorting_spheres_text();
    glTranslatef(4.5, 0, 0);
    
    glFlush(); 
    glutSwapBuffers();
}

void on_reshape(int width, int height){
    //podesavanje pogleda 
    glViewport(0, 0,  (GLsizei)width,  (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, (float) width / height, 1, 10);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void on_keyboard(unsigned char key, int x, int y){
    if(sorting == 0 && start_screen != 0){
        // ako niz nije u procesu sortiranja mozemo da ga randomizujemo, da promenimo sort 
        // ili da zapocnemo opet sortiranje
        switch(key){
            case 's': case 'S':{
                // zapocni sortiranje
                sorting = 1;
                break;
            }
            case 'r': case 'R':{
                // randomizuj nizove, ako su izabrane kulice onda inicijalizujemo niz
                // ako su loptice onda onda niz i koordinate
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
                speed = (speed + 1) % 5;
            }
        }
    }else if(sorting == 1 && start_screen != 0){
        // ako je niz u procesu sortiranja i nije na pocetnom ekranu 
        // omoguceno je da se zaustavi sortiranje
        switch(key){
            case 'p': case 'P':{
                sorting = 0;
                break;
            }
        }
    }else if(start_screen == 0){
        // ako smo na pocetnom ekranu mozemo da izaberemo 
        // nacin prikazivanja sortiranja
        switch(key){
            case 'k': case 'K':{
                // zove se predstavljanje kulicama
                    start_screen = 1;
                    init_array(MAX_ARR_BARS);
                    glutDisplayFunc(on_display1);
                    glutTimerFunc(30, barTimer, 1);
                    break;
            }
            case 'l': case 'L':{
                // zove se predstavljanje lopticama
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
        // u bilom kom slucaju ako se pritisne esc izlazi se iz programa
        case 27: 
            exit(EXIT_SUCCESS);
            break;
    }
}

void init_callbacks(void) {
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
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

void init_array(int lenght){
    global_i = global_j = 0;
    array_lenght = lenght;
    array = (int*) malloc(sizeof(int) * lenght);
    for(int i=0; i < lenght; i++){
        array[i] = rand() % lenght + 1;
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
        //
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
    // pomerimo se za 1 da bi se lepse uklopilo sa mrezom
    glTranslatef(1, 0, 10);
    
    // cuva razmak izmedju brojeva
    float razmak = 0;
    
    for(int i=0; i<MAX_ARR_BARS; i++){
        // provera da li je trenutni element koji se iscrtava 
        // onaj koji se pomera, ako jeste saljemo indikator 
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
        
        // ispisujemo i brojeve
        // proveravamo da li je broj dvocifren ili jednocifren zbog razmaka
        if(std::to_string(array[i]).size() == 2){
            glColor3f(1.0, 0.0, 0.0);
            bitmap_output(razmak, 12, (std::to_string(array[i])), GLUT_BITMAP_TIMES_ROMAN_24);
            razmak -= 0.05;
        }else{
            glColor3d(1.0, 0.0, 0.0);
            bitmap_output(razmak + 0.2,  12, (std::to_string(array[i])), GLUT_BITMAP_TIMES_ROMAN_24);
            razmak -= 0.025;
        }
        
        // pomerimo se za 1, i iscrtavamo sledecu...
        glTranslatef(1, 0, 0);
    }
    glTranslatef(-1, 0, -10);
}

void bitmap_output(float x, float y, std::string string, void *font){
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
    bitmap_output(-3, -50, "VIZUELIZACIJA ALGORITMA",   GLUT_BITMAP_TIMES_ROMAN_24 );
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
        bitmap_output(-5, 17, "Komande:",GLUT_BITMAP_TIMES_ROMAN_24);
        
        // iscrtavanje tackice pre teksta i tekst
        
        draw_circle(0.15, -5.3, 16.3);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-3, -50, "VIZUELIZACIJA ALGORITMA",   GLUT_BITMAP_TIMES_ROMAN_24 );
        bitmap_output(-5, 16, "Pritiskom na s algoritam se startuje",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.15, -5.6, 15.3);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-5.3f, 15, "Pritiskom na a menja se algoritam",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.15,-5.9,14.3);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-5.6, 14, "Pritiskom na r niz se randomizuje",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.15,-6.2,13.3);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-5.9, 13, "Esc za izlaz iz programa",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.15, -6.5,12.3);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-6.2, 12, "Izabrani sort: ",GLUT_BITMAP_TIMES_ROMAN_24);
        
        bitmap_output(-6.5, 11, sorting_string[type_of_sort],GLUT_BITMAP_9_BY_15);
        
    }else if(sorting == 1){
        glColor3f(0.5,0.5,0.5);
        
        bitmap_output(-5, 17, "Niz se sortira... Za promenu algoritma, randomizaciju niza ili izlazak iz programa prvo se mora pauzirati. ", GLUT_BITMAP_9_BY_15);
        
        bitmap_output(-5, 16, "Pritisni p za pauzu.",GLUT_BITMAP_9_BY_15);
    }
}

void sorting_spheres_text(void){
    glColor3f(0.6f, 0.137255, 0.556863);
    bitmap_output(2.8, -2.0, "VIZUELIZACIJA ALGORITMA",   GLUT_BITMAP_TIMES_ROMAN_24 );

    glLineWidth(2);
    // linija pre teksta
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
        bitmap_output(-0.5, 3, "Komande:",GLUT_BITMAP_TIMES_ROMAN_24);

        // iscrtavanje tackice pre teksta i tekst
        
        draw_circle(0.03, -0.4, 2.85);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-0.32, 2.8, "Pritiskom na s algoritam se startuje",GLUT_BITMAP_TIMES_ROMAN_24);
    
        draw_circle(0.03, -0.4, 2.65);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-0.32, 2.6, "Pritiskom na a menja se algoritam",GLUT_BITMAP_TIMES_ROMAN_24);
    
        draw_circle(0.03,-0.4,2.45);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-0.32, 2.4, "Pritiskom na r niz se randomizuje",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.03,-0.4,2.25);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-0.32, 2.2, "Esc za izlaz iz programa",GLUT_BITMAP_TIMES_ROMAN_24);
        
        draw_circle(0.03, -0.4, 2.05);
        glColor3f(0.87, 0.6, 0.8);
        bitmap_output(-0.32, 2.0, "Izabrani sort: ",GLUT_BITMAP_TIMES_ROMAN_24);
        
        bitmap_output(-0.2, 1.8, sorting_string[type_of_sort],GLUT_BITMAP_9_BY_15);
        
    }else if(sorting == 1){
        glColor3f(0.5,0.5,0.5);
        
        bitmap_output(0, 3, "Niz se sortira... Za promenu algoritma, randomizaciju niza ili izlazak iz programa prvo se mora pauzirati. ", GLUT_BITMAP_9_BY_15);
        
        bitmap_output(0.2, 2.8, "Pritisni p za pauzu.",GLUT_BITMAP_9_BY_15);
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
    bitmap_output(-2.7, 1.7, "PREDSTAVLJANJE ALGORITAMA ZA SORTIRANJE: ",   GLUT_BITMAP_TIMES_ROMAN_24 );
    
    // iscrtavanje tackice pre teksta i tekst    
    draw_circle(0.05, -2.6, 1.47);
    
    glColor3f(0.439216f, 0.858824, 0.576471);
    bitmap_output(-2.5, 1.4, "za predstavljanje algoritama kulicama pritisnite k...",   GLUT_BITMAP_TIMES_ROMAN_24 );
    
    draw_circle(0.05, -2.6, 1.17);
    
    glColor3f(0.439216f, 0.858824, 0.576471);
    bitmap_output(-2.5, 1.1, "za predstavljanje algoritama lopticama pritisnite l...",   GLUT_BITMAP_TIMES_ROMAN_24 );
    
    glTranslatef(0, 1.5, 0);
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