#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

#include <iostream>
#include <ostream>

igvEscena3D::igvEscena3D() {
    // Posiciones iniciales. DEPENDEN DE CÓMO SEAN VUESTROS OBJETOS
    objetos[0].tx = -3.0f;
    objetos[0].ty = 0.0f;
    objetos[0].tz = 0.0f;
    objetos[1].tx = 0.0f;
    objetos[1].ty = 0.0f;
    objetos[1].tz = 0.0f;
    objetos[2].tx = 3.0f;
    objetos[2].ty = 0.0f;
    objetos[2].tz = 0.0f;
    objetos[0].seleccionado = true;
}

void igvEscena3D::pintar_ejes() {
    GLfloat rojo[] = {1, 0, 0, 1.0};
    GLfloat verde[] = {0, 1, 0, 1.0};
    GLfloat azul[] = {0, 0, 1, 1.0};

    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);

    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);

    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

void igvEscena3D::renderObjeto1() {
    GLfloat color[] = {0.8f, 0.2f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glPushMatrix();
    glutSolidCube(1.0f);
    glPopMatrix();
}

void igvEscena3D::renderObjeto2() {
    GLfloat color[] = {0.2f, 0.8f, 0.2f, 1.0f};
    GLUquadric *quad = gluNewQuadric();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glPushMatrix();
    glTranslatef(0,0.7,0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(quad, 0.6f, 0.6f, 1.5f, 20, 20);
    glPopMatrix();
    gluDeleteQuadric(quad);
}

void igvEscena3D::renderObjeto3() {
    GLfloat color[] = {0.6f, 0.3f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glPushMatrix();
    glScalef(1.5f, 0.5f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void igvEscena3D::aplicarTransformaciones(int indice) {
    glTranslatef(objetos[indice].tx, objetos[indice].ty, objetos[indice].tz);
    glRotatef(objetos[indice].rx, 1, 0, 0);
    glRotatef(objetos[indice].ry, 0, 1, 0);
    glRotatef(objetos[indice].rz, 0, 0, 1);
    glScalef(objetos[indice].sx, objetos[indice].sy, objetos[indice].sz);
}

void igvEscena3D::dibujarIndicadorSeleccion() {
    GLfloat color_seleccion[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, color_seleccion);

    glPushMatrix();
    if (objetoSeleccionado == 0) {
        aplicarTransformaciones(0);
    } else if (objetoSeleccionado == 1) {
        aplicarTransformaciones(1);
    } else if (objetoSeleccionado == 2) {
        aplicarTransformaciones(2);
    }
    glutWireCube(2.0f);
    glPopMatrix();
    GLfloat no_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
}

void igvEscena3D::seleccionarObjeto(int indice) {
    // Validación simple
    std::cout << indice << std::endl;
    objetos[objetoSeleccionado].seleccionado = false;
    objetos[indice].seleccionado = true;
    objetoSeleccionado = indice;
}

void igvEscena3D::visualizar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat light0[] = {10, 8, 9, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glEnable(GL_LIGHT0);
    glPushMatrix();
    if (ejes) {
        pintar_ejes();
    }
    glPushMatrix();
    aplicarTransformaciones(0);
    renderObjeto1();
    glPopMatrix();
    glPushMatrix();
    aplicarTransformaciones(1);
    renderObjeto2();
    glPopMatrix();
    glPushMatrix();
    aplicarTransformaciones(2);
    renderObjeto3();
    glPopMatrix();
    dibujarIndicadorSeleccion();
    glPopMatrix();
    glutSwapBuffers();
}

void igvEscena3D::trasladar(float dx, float dy, float dz) {
    objetos[objetoSeleccionado].tx += dx;
    objetos[objetoSeleccionado].ty += dy;
    objetos[objetoSeleccionado].tz += dz;
}

void igvEscena3D::rotar(char eje, float angulo) {
    switch (eje) {
        case 'x':
            objetos[objetoSeleccionado].rx += angulo;
            break;
        case 'y':
            objetos[objetoSeleccionado].ry += angulo;
            break;
        case 'z':
            objetos[objetoSeleccionado].rz += angulo;
            break;
    }
}

void igvEscena3D::escalar(float factor) {
    objetos[objetoSeleccionado].sx *= factor;
    objetos[objetoSeleccionado].sy *= factor;
    objetos[objetoSeleccionado].sz *= factor;
}

bool igvEscena3D::get_ejes() {
    return ejes;
}

void igvEscena3D::set_ejes(bool _ejes) {
    ejes = _ejes;
}
