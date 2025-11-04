#include "igvModeloArticulado.h"
#include "igvCilindro.h"
#include "igvEsfera.h"
#include "igvCono.h"
#include "igvDisco.h"
#include <cmath>

igvModeloArticulado::igvModeloArticulado() {
    anguloBase = 0.0f;
    anguloBrazo1 = 45.0f;
    anguloBrazo2 = -60.0f;
    anguloPantalla = -30.0f;

    dim.radioBase = 0.5f;
    dim.alturaBase = 0.2f;
    dim.longitudBrazo1 = 2.0f;
    dim.radioBrazo1 = 0.1f;
    dim.radioArticulacion = 0.15f;
    dim.longitudBrazo2 = 1.5f;
    dim.radioBrazo2 = 0.08f;
    dim.radioPantalla = 0.6f;
    dim.alturaPantalla = 0.8f;

    crearPrimitivas();
}

void igvModeloArticulado::crearPrimitivas() {
    cilindro = new igvCilindro(1.0f, 1.0f, 20, 10);
    esfera = new igvEsfera(1.0f, 20, 20);
    disco = new igvDisco(1.0f, 30);
    pantalla = new igvCono(dim.radioPantalla, dim.alturaPantalla, 30);
}

igvModeloArticulado::~igvModeloArticulado() {
    if (cilindro) delete cilindro;
    if (esfera) delete esfera;
    if (disco) delete disco;
    if (pantalla) delete pantalla;
}

void igvModeloArticulado::dibujarBase() {
    GLfloat colorBase[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBase);

    glPushMatrix();
        glPushMatrix();
            glScalef(dim.radioBase, dim.alturaBase, dim.radioBase);
            cilindro->visualizar();
        glPopMatrix();
        glPushMatrix();
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            glScalef(dim.radioBase, 1.0f, dim.radioBase);
            disco->visualizar();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glScalef(dim.radioBase, 1.0f, dim.radioBase);
            disco->visualizar();
        glPopMatrix();
    glPopMatrix();
}

void igvModeloArticulado::dibujarBrazo1() {
    GLfloat colorBrazo[] = {0.8f, 0.8f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBrazo);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glScalef(dim.radioBrazo1, dim.longitudBrazo1, dim.radioBrazo1);
        cilindro->visualizar();
    glPopMatrix();
}

void igvModeloArticulado::dibujarArticulacion1() {
    GLfloat colorArticulacion[] = {0.2f, 0.2f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorArticulacion);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glScalef(dim.radioArticulacion, dim.radioArticulacion, dim.radioArticulacion);
        esfera->visualizar();
    glPopMatrix();
}

void igvModeloArticulado::dibujarBrazo2() {
    GLfloat colorBrazo[] = {0.8f, 0.8f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBrazo);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
        glScalef(dim.radioBrazo2, dim.longitudBrazo2, dim.radioBrazo2);
        cilindro->visualizar();
    glPopMatrix();
}

void igvModeloArticulado::dibujarArticulacion2() {
    GLfloat colorArticulacion[] = {0.2f, 0.2f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorArticulacion);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);

        float radio2 = dim.radioArticulacion * 0.8f;
        glScalef(radio2, radio2, radio2);
        esfera->visualizar();
    glPopMatrix();
}


void igvModeloArticulado::dibujarPantalla() {
    GLfloat colorPantalla[] = {0.9f, 0.9f, 0.9f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorPantalla);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
        glRotatef(anguloPantalla, 0.0f, 0.0f, 1.0f);
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -dim.alturaPantalla, 0.0f);

        pantalla->visualizar();
    glPopMatrix();
}

void igvModeloArticulado::visualizar() {
    glPushMatrix();
        glRotatef(anguloBase, 0.0f, 1.0f, 0.0f);
        dibujarBase();
        dibujarBrazo1();
        dibujarArticulacion1();
        dibujarBrazo2();
        dibujarArticulacion2();
        dibujarPantalla();
    glPopMatrix();
}

void igvModeloArticulado::cambiarModoSombreado() {
    if (cilindro) cilindro->cambiarvis();
    if (esfera) esfera->cambiarvis();
    if (disco) disco->cambiarvis();
    if (pantalla) pantalla->cambiarvis();
}

void igvModeloArticulado::cambiarUsoNormales() {
    if (cilindro) cilindro->cambiarnormales();
    if (esfera) esfera->cambiarnormales();
    if (disco) disco->cambiarnormales();
    if (pantalla) pantalla->cambiarnormales();
}

void igvModeloArticulado::rotarBase(float incremento) {
    anguloBase += incremento;
    while (anguloBase >= 360.0f) anguloBase -= 360.0f;
    while (anguloBase < 0.0f) anguloBase += 360.0f;
}

void igvModeloArticulado::rotarBrazo1(float incremento) {
    anguloBrazo1 += incremento;
    if (anguloBrazo1 > 120.0f) anguloBrazo1 = 120.0f;
    if (anguloBrazo1 < 0.0f) anguloBrazo1 = 0.0f;
}

void igvModeloArticulado::rotarBrazo2(float incremento) {
    anguloBrazo2 += incremento;
    if (anguloBrazo2 > 30.0f) anguloBrazo2 = 30.0f;
    if (anguloBrazo2 < -150.0f) anguloBrazo2 = -150.0f;
}

void igvModeloArticulado::rotarPantalla(float incremento) {
    anguloPantalla += incremento;
    if (anguloPantalla > 45.0f) anguloPantalla = 45.0f;
    if (anguloPantalla < -90.0f) anguloPantalla = -90.0f;
}

void igvModeloArticulado::resetearPose() {
    anguloBase = 0.0f;
    anguloBrazo1 = 45.0f;
    anguloBrazo2 = -60.0f;
    anguloPantalla = -30.0f;
}

void igvModeloArticulado::visualizarConColoresSeleccion() {
    glPushMatrix();
        glRotatef(anguloBase, 0.0f, 1.0f, 0.0f);

        // Base - Color ROJO (255, 0, 0)
        glColor3ub(255, 0, 0);
        glPushMatrix();
            glPushMatrix();
                glScalef(dim.radioBase, dim.alturaBase, dim.radioBase);
                cilindro->visualizar();
            glPopMatrix();
            glPushMatrix();
                glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
                glScalef(dim.radioBase, 1.0f, dim.radioBase);
                disco->visualizar();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0f, dim.alturaBase, 0.0f);
                glScalef(dim.radioBase, 1.0f, dim.radioBase);
                disco->visualizar();
            glPopMatrix();
        glPopMatrix();

        // Brazo1 - Color VERDE (0, 255, 0)
        glColor3ub(0, 255, 0);
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glScalef(dim.radioBrazo1, dim.longitudBrazo1, dim.radioBrazo1);
            cilindro->visualizar();
        glPopMatrix();

        // Articulación 1 - mismo color que Brazo1
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
            glScalef(dim.radioArticulacion, dim.radioArticulacion, dim.radioArticulacion);
            esfera->visualizar();
        glPopMatrix();

        // Brazo2 - Color AZUL (0, 0, 255)
        glColor3ub(0, 0, 255);
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
            glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
            glScalef(dim.radioBrazo2, dim.longitudBrazo2, dim.radioBrazo2);
            cilindro->visualizar();
        glPopMatrix();

        // Articulación 2 - mismo color que Brazo2
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
            glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
            float radio2 = dim.radioArticulacion * 0.8f;
            glScalef(radio2, radio2, radio2);
            esfera->visualizar();
        glPopMatrix();

        // Pantalla - Color AMARILLO (255, 255, 0)
        glColor3ub(255, 255, 0);
        glPushMatrix();
            glTranslatef(0.0f, dim.alturaBase, 0.0f);
            glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
            glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, dim.longitudBrazo2, 0.0f);
            glRotatef(anguloPantalla, 0.0f, 0.0f, 1.0f);
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            glTranslatef(0.0f, -dim.alturaPantalla, 0.0f);
            pantalla->visualizar();
        glPopMatrix();

    glPopMatrix();
}