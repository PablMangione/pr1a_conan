#include <cstdlib>
#include <stdio.h>
#include "igvEscena3D.h"
#include "igvCilindro.h"
#include <iostream>
#include <cmath>

igvEscena3D::igvEscena3D() {
    ejes = false;
    malla = new igvCilindro(1.0f, 2.0f, 20, 10);
}

void igvEscena3D::pintar_ejes() {
    GLfloat rojo[] = {1, 0, 0, 1.0};
    GLfloat verde[] = {0, 1, 0, 1.0};
    GLfloat azul[] = {0, 0, 1, 1.0};

    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

void igvEscena3D::visualizar() {
    GLfloat light0[] = {10, 8, 9, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glEnable(GL_LIGHT0);
    glPushMatrix();
    if (ejes) {
        pintar_ejes();
    }
    if (malla != nullptr) {
        glPushMatrix();
        GLfloat color_malla[] = {0.2f, 0.6f, 0.8f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_malla);
        malla->visualizar();
        glPopMatrix();
    }
    glPopMatrix();
}

void igvEscena3D::set_ejes(bool _ejes) {
    ejes = _ejes;
}

bool igvEscena3D::get_ejes() {
    return ejes;
}


igvEscena3D::~igvEscena3D() {
    if (malla != nullptr) {
        delete malla;
        malla = nullptr;
    }
}
