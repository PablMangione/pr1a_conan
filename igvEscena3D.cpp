#include <cstdlib>
#include <stdio.h>
#include "igvEscena3D.h"

igvEscena3D::igvEscena3D() {
    ejes = false;
}

igvEscena3D::~igvEscena3D() {
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

    modelo.visualizar();

    glPopMatrix();
}

bool igvEscena3D::get_ejes() {
    return ejes;
}

void igvEscena3D::set_ejes(bool _ejes) {
    ejes = _ejes;
}

void igvEscena3D::cambiarModoSombreado() {
    modelo.cambiarModoSombreado();
}

void igvEscena3D::cambiarUsoNormales() {
    modelo.cambiarUsoNormales();
}

void igvEscena3D::rotarBaseLampara(float incremento) {
    modelo.rotarBase(incremento);
}

void igvEscena3D::rotarBrazo1Lampara(float incremento) {
    modelo.rotarBrazo1(incremento);
}

void igvEscena3D::rotarBrazo2Lampara(float incremento) {
    modelo.rotarBrazo2(incremento);
}

void igvEscena3D::rotarPantallaLampara(float incremento) {
    modelo.rotarPantalla(incremento);
}

void igvEscena3D::resetearPoseLampara() {
    modelo.resetearPose();
}

void igvEscena3D::visualizarModoSeleccion() {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glPushMatrix();
    modelo.visualizarConColoresSeleccion();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

unsigned char *igvEscena3D::capturarBufferSeleccion(int x, int y) {
    static unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    return pixel;
}

int igvEscena3D::identificarPartePorColor(unsigned char r, unsigned char g, unsigned char b) {
    const int tolerancia = 50;

    if (r > 255 - tolerancia && g < tolerancia && b < tolerancia) return 0;
    if (r < tolerancia && g > 255 - tolerancia && b < tolerancia) return 1;
    if (r < tolerancia && g < tolerancia && b > 255 - tolerancia) return 2;
    if (r > 255 - tolerancia && g > 255 - tolerancia && b < tolerancia) return 3;
    return -1;
}

void igvEscena3D::seleccionarParte(int x, int y, int alto_ventana) {
    GLfloat colorFondoAnterior[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, colorFondoAnterior);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    visualizarModoSeleccion();

    glFlush();
    glFinish();

    unsigned char *pixel = capturarBufferSeleccion(x, alto_ventana - y);

    parteSeleccionada = identificarPartePorColor(pixel[0], pixel[1], pixel[2]);

    glClearColor(colorFondoAnterior[0], colorFondoAnterior[1],
                 colorFondoAnterior[2], colorFondoAnterior[3]);
}
