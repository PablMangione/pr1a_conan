#include "igvModeloArticulado.h"
#include "igvCilindro.h"
#include "igvEsfera.h"
#include "igvCono.h"
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
    base = new igvCilindro(dim.radioBase, dim.alturaBase, 30, 5);
    brazo1 = new igvCilindro(dim.radioBrazo1, dim.longitudBrazo1, 20, 10);
    articulacion1 = new igvEsfera(dim.radioArticulacion, 20, 20);
    brazo2 = new igvCilindro(dim.radioBrazo2, dim.longitudBrazo2, 20, 10);
    articulacion2 = new igvEsfera(dim.radioArticulacion * 0.8f, 20, 20);
    pantalla = new igvCono(dim.radioPantalla, dim.alturaPantalla, 30);
}

igvModeloArticulado::~igvModeloArticulado() {
    if (base) delete base;
    if (brazo1) delete brazo1;
    if (articulacion1) delete articulacion1;
    if (brazo2) delete brazo2;
    if (articulacion2) delete articulacion2;
    if (pantalla) delete pantalla;
}

void igvModeloArticulado::dibujarBase() {
    GLfloat colorBase[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBase);

    glPushMatrix();
        base->visualizar();
    glPopMatrix();
}

void igvModeloArticulado::dibujarBrazo1() {
    GLfloat colorBrazo[] = {0.8f, 0.8f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBrazo);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        brazo1->visualizar();
    glPopMatrix();
}

void igvModeloArticulado::dibujarArticulacion1() {
    GLfloat colorArticulacion[] = {0.2f, 0.2f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorArticulacion);

    glPushMatrix();
        glTranslatef(0.0f, dim.alturaBase, 0.0f);
        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        articulacion1->visualizar();
    glPopMatrix();
}

void igvModeloArticulado::dibujarBrazo2() {
    GLfloat colorBrazo[] = {0.8f, 0.8f, 0.2f, 1.0f};  // Amarillo
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBrazo);

    glPushMatrix();

        glTranslatef(0.0f, dim.alturaBase, 0.0f);


        glRotatef(anguloBrazo1, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, dim.longitudBrazo1, 0.0f);
        glRotatef(anguloBrazo2, 0.0f, 0.0f, 1.0f);
        brazo2->visualizar();
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

        articulacion2->visualizar();
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
    if (base) base->cambiarvis();
    if (brazo1) brazo1->cambiarvis();
    if (articulacion1) articulacion1->cambiarvis();
    if (brazo2) brazo2->cambiarvis();
    if (articulacion2) articulacion2->cambiarvis();
    if (pantalla) pantalla->cambiarvis();
}

void igvModeloArticulado::cambiarUsoNormales() {
    if (base) base->cambiarnormales();
    if (brazo1) brazo1->cambiarnormales();
    if (articulacion1) articulacion1->cambiarnormales();
    if (brazo2) brazo2->cambiarnormales();
    if (articulacion2) articulacion2->cambiarnormales();
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