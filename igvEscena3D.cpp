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
    // Desactivar iluminación para colores planos
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glPushMatrix();

    // Dibujar cada parte con un color único identificador
    modelo.visualizarConColoresSeleccion();

    glPopMatrix();

    // Reactivar iluminación
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

unsigned char* igvEscena3D::capturarBufferSeleccion(int x, int y) {
    static unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    return pixel;
}

int igvEscena3D::identificarPartePorColor(unsigned char r, unsigned char g, unsigned char b) {
    // Colores identificadores:
    // Base: RGB(255, 0, 0) = rojo
    // Brazo1: RGB(0, 255, 0) = verde
    // Brazo2: RGB(0, 0, 255) = azul
    // Pantalla: RGB(255, 255, 0) = amarillo

    if (r == 255 && g == 0 && b == 0) return 0; // Base
    if (r == 0 && g == 255 && b == 0) return 1; // Brazo1
    if (r == 0 && g == 0 && b == 255) return 2; // Brazo2
    if (r == 255 && g == 255 && b == 0) return 3; // Pantalla

    return -1; // Ninguna parte
}

void igvEscena3D::seleccionarParte(int x, int y, int alto_ventana) {
    // Renderizar en modo selección (offscreen)
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    visualizarModoSeleccion();

    glFlush();

    // Capturar el color en la posición del clic
    // Invertir Y porque OpenGL usa coordenadas desde abajo
    unsigned char* pixel = capturarBufferSeleccion(x, alto_ventana - y);

    // Identificar la parte
    parteSeleccionada = identificarPartePorColor(pixel[0], pixel[1], pixel[2]);

    // Restaurar color de fondo
    glClearColor(1.0, 1.0, 1.0, 0.0);
}