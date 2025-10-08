#include <cstdlib>
#include <stdio.h>
#include "igvEscena3D.h"
#include <iostream>
#include <cmath>

igvEscena3D::igvEscena3D() {
    modo = true;
    ejes = false;
    objetos[0].seleccionado = true;
    objetoSeleccionado = 0;
    objetos[0].tx_inicial = -3.0f;
    objetos[0].ty_inicial = 0.0f;
    objetos[0].tz_inicial = 0.0f;
    objetos[1].tx_inicial = 0.0f;
    objetos[1].ty_inicial = 0.0f;
    objetos[1].tz_inicial = 0.0f;
    objetos[2].tx_inicial = 3.0f;
    objetos[2].ty_inicial = 0.0f;
    objetos[2].tz_inicial = 0.0f;
    secuenciaTransformaciones.clear();
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
    GLfloat colorNuevo[] = {0.2f, 0.8f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorNuevo);
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glScalef(1.0f, 1.0f, 3.0f);
    glutSolidCube(0.5f);
    glPopMatrix();
}

void igvEscena3D::renderObjeto2() {
    GLfloat color[] = {0.2f, 0.8f, 0.2f, 1.0f};
    GLUquadric *quad = gluNewQuadric();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glPushMatrix();
    glTranslatef(0, 0.7, 0);
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

void igvEscena3D::aplicarTransformacion(const Transformacion& t) {
    switch(t.tipo) {
        case Transformacion::TRASLACION:
            glTranslatef(t.param1, t.param2, t.param3);
            break;
        case Transformacion::ROTACION_X:
            glRotatef(t.param1, 1, 0, 0);
            break;
        case Transformacion::ROTACION_Y:
            glRotatef(t.param1, 0, 1, 0);
            break;
        case Transformacion::ROTACION_Z:
            glRotatef(t.param1, 0, 0, 1);
            break;
        case Transformacion::ESCALADO:
            glScalef(t.param1, t.param1, t.param1);
            break;
    }
}

void igvEscena3D::aplicarTransformaciones() {
    glTranslatef(objetos[objetoSeleccionado].tx_inicial,
                     objetos[objetoSeleccionado].ty_inicial,
                     objetos[objetoSeleccionado].tz_inicial);
    if (modo) {
        for (const auto& t : secuenciaTransformaciones) {
            if (t.tipo == Transformacion::TRASLACION) {
                aplicarTransformacion(t);
            }
        }
        for (const auto& t : secuenciaTransformaciones) {
            if (t.tipo == Transformacion::ROTACION_X ||
                t.tipo == Transformacion::ROTACION_Y ||
                t.tipo == Transformacion::ROTACION_Z) {
                aplicarTransformacion(t);
                }
        }
        for (const auto& t : secuenciaTransformaciones) {
            if (t.tipo == Transformacion::ESCALADO) {
                aplicarTransformacion(t);
            }
        }
    } else {
        for (int i = secuenciaTransformaciones.size() - 1; i >= 0; i--) {
            aplicarTransformacion(secuenciaTransformaciones[i]);
        }
    }
}

void igvEscena3D::dibujarIndicadorSeleccion() {
    GLfloat color_seleccion[] = {1.0f, 0.0f, 0.0f, 1.0f};
    if (!modo) {
        color_seleccion[0] = 0.1f;
        color_seleccion[1] = 0.7f;
        color_seleccion[2] = 0.1f;
    }
    glMaterialfv(GL_FRONT, GL_EMISSION, color_seleccion);
    glPushMatrix();
    aplicarTransformaciones();
    glutWireCube(2.0f);
    glPopMatrix();
    GLfloat no_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
}

void igvEscena3D::visualizar() {
    GLfloat light0[] = {10, 8, 9, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glEnable(GL_LIGHT0);

    glPushMatrix();
    if (ejes) {
        pintar_ejes();
    }
    for(int i = 0; i < 3; i++) {
        glPushMatrix();
        if (i == objetoSeleccionado) {
            aplicarTransformaciones();
        } else {
            glTranslatef(objetos[i].tx_inicial,
                        objetos[i].ty_inicial,
                        objetos[i].tz_inicial);
        }

        if(i == 0) renderObjeto1();
        else if(i == 1) renderObjeto2();
        else renderObjeto3();

        glPopMatrix();
    }
    dibujarIndicadorSeleccion();
    glPopMatrix();
}

void igvEscena3D::trasladar(float dx, float dy, float dz) {
    Transformacion t;
    t.tipo = Transformacion::TRASLACION;
    t.param1 = dx;
    t.param2 = dy;
    t.param3 = dz;
    secuenciaTransformaciones.push_back(t);
}

void igvEscena3D::rotar(char eje, float angulo) {
    Transformacion t;
    switch(eje) {
        case 'x':
            t.tipo = Transformacion::ROTACION_X;
            break;
        case 'y':
            t.tipo = Transformacion::ROTACION_Y;
            break;
        case 'z':
            t.tipo = Transformacion::ROTACION_Z;
            break;
    }
    t.param1 = angulo;
    secuenciaTransformaciones.push_back(t);
}

void igvEscena3D::escalar(float factor) {
    Transformacion t;
    t.tipo = Transformacion::ESCALADO;
    t.param1 = factor;
    secuenciaTransformaciones.push_back(t);
}

void igvEscena3D::seleccionarObjeto(int indice) {
    if (indice != objetoSeleccionado) {
        secuenciaTransformaciones.clear();
        objetos[objetoSeleccionado].seleccionado = false;
        objetos[indice].seleccionado = true;
        objetoSeleccionado = indice;
    }
}

bool igvEscena3D::get_ejes() {
    return ejes;
}

int igvEscena3D::getObjetoSeleccionado() {
    return objetoSeleccionado;
}

void igvEscena3D::set_ejes(bool _ejes) {
    ejes = _ejes;
}