#include "igvModeloArticulado.h"
#include "igvCilindro.h"
#include "igvCubo.h"
#include "igvDisco.h"
#include "igvEsfera.h"
#include "igvOctaedro.h"
#include "igvTetraedro.h"

igvModeloArticulado::igvModeloArticulado() {
    // Por ahora creamos primitivas básicas para pruebas
    // En el futuro aquí se construirá el grafo de escena
    primitivas.push_back(new igvCubo(1.0f));
    primitivas.push_back(new igvEsfera(0.8f, 30, 30));
    primitivas.push_back(new igvCilindro(0.6f, 1.5f, 30, 10));
    primitivas.push_back(new igvDisco(0.7f, 40));
    primitivas.push_back(new igvOctaedro(1.0f));
    primitivas.push_back(new igvTetraedro(1.0f));
}

igvModeloArticulado::~igvModeloArticulado() {
    for (auto primitiva : primitivas) {
        if (primitiva != nullptr) {
            delete primitiva;
            primitiva = nullptr;
        }
    }
    primitivas.clear();
}

void igvModeloArticulado::visualizar() {
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
}

void igvModeloArticulado::cambiarModoSombreado() {
    for (auto primitiva : primitivas) {
        if (primitiva != nullptr) {
            primitiva->cambiarvis();
        }
    }
}

void igvModeloArticulado::cambiarUsoNormales() {
    for (auto primitiva : primitivas) {
        if (primitiva != nullptr) {
            primitiva->cambiarnormales();
        }
    }
}