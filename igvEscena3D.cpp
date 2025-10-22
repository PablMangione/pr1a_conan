#include <cstdlib>
#include <stdio.h>
#include "igvEscena3D.h"
#include "igvCilindro.h"
#include "igvCubo.h"
#include "igvDisco.h"
#include "igvEsfera.h"
#include "igvOctaedro.h"
#include "igvTetraedro.h"
#include <iostream>
#include <cmath>

igvEscena3D::igvEscena3D() {
    ejes = false;

    primitivas.push_back(new igvCubo(1.0f));
    primitivas.push_back(new igvEsfera(0.8f, 30, 30));
    primitivas.push_back(new igvCilindro(0.6f, 1.5f, 30, 10));
    primitivas.push_back(new igvDisco(0.7f, 40));
    primitivas.push_back(new igvOctaedro(1.0f));
    primitivas.push_back(new igvTetraedro(1.0f));
}

igvEscena3D::~igvEscena3D() {
    for (auto primitiva: primitivas) {
        if (primitiva != nullptr) {
            delete primitiva;
            primitiva = nullptr;
        }
    }
    primitivas.clear();
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

    GLfloat colores[][3] = {
        {0.9f, 0.2f, 0.2f},
        {0.2f, 0.9f, 0.2f},
        {0.2f, 0.5f, 0.9f},
        {0.9f, 0.9f, 0.2f},
        {0.9f, 0.3f, 0.9f},
        {0.2f, 0.9f, 0.9f}
    };

    float separacionX = 2.5f;
    float separacionZ = 2.5f;
    int primitivasPorFila = 3;

    for (size_t i = 0; i < primitivas.size(); i++) {
        if (primitivas[i] != nullptr) {
            glPushMatrix();

            int fila = i / primitivasPorFila;
            int columna = i % primitivasPorFila;

            float offsetX = -(primitivasPorFila - 1) * separacionX / 2.0f;
            float posX = offsetX + columna * separacionX;
            float posZ = fila * separacionZ;

            glTranslatef(posX, 0.0f, posZ);

            GLfloat color[4] = {colores[i][0], colores[i][1], colores[i][2], 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

            primitivas[i]->visualizar();

            glPopMatrix();
        }
    }

    glPopMatrix();
}

bool igvEscena3D::get_ejes() {
    return ejes;
}

void igvEscena3D::set_ejes(bool _ejes) {
    ejes = _ejes;
}
