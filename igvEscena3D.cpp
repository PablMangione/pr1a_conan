#include <cstdlib>
#include <stdio.h>
#include "igvEscena3D.h"

igvEscena3D::igvEscena3D() {
    ejes = false;
    // ============================================
    // INICIALIZACIÓN DE MATERIALES DEL SUELO
    // ============================================

    // Material 1: Rojo brillante
    materialesSuelo[0].set(
        igvColor(0.2, 0.0, 0.0),    // Ka - ambiental
        igvColor(0.8, 0.1, 0.1),    // Kd - difuso
        igvColor(1.0, 1.0, 1.0),    // Ks - especular
        50.0                         // Ns - exponente Phong
    );

    // Material 2: Verde mate
    materialesSuelo[1].set(
        igvColor(0.0, 0.2, 0.0),    // Ka
        igvColor(0.1, 0.6, 0.1),    // Kd
        igvColor(0.2, 0.2, 0.2),    // Ks
        10.0                         // Ns
    );

    // Material 3: Azul metálico
    materialesSuelo[2].set(
        igvColor(0.0, 0.0, 0.2),    // Ka
        igvColor(0.1, 0.1, 0.8),    // Kd
        igvColor(1.0, 1.0, 1.0),    // Ks
        100.0                        // Ns
    );

    // ============================================
    // INICIALIZACIÓN DE TEXTURAS
    // ============================================

    // Textura 1: Desde archivo
    texturas[0] = new igvTextura("mapa.png");

    // Textura 2: Otra imagen (crear o usar existente)
    texturas[1] = new igvTextura("textura2.png");

    // Textura 3: Tablero de ajedrez (procedural)
    texturas[2] = igvTextura::crearTableroAjedrez(256, 8);

    // ============================================
    // INICIALIZACIÓN DE LUCES
    // ============================================

    // Luz ambiental global (usando GL_LIGHT0)
    // Nota: Para luz ambiental global usar glLightModelfv
    luzAmbiente = igvFuenteLuz(
        GL_LIGHT0,
        igvPunto3D(0, 0, 0),           // Posición (no relevante para ambiental)
        igvColor(0.3, 0.3, 0.3),       // Ambiental
        igvColor(0.0, 0.0, 0.0),       // Difuso (0 para luz ambiental pura)
        igvColor(0.0, 0.0, 0.0),       // Especular
        1.0, 0.0, 0.0                  // Atenuación
    );

    // Luz direccional (GL_LIGHT1) - posición con w=0
    luzDireccional = igvFuenteLuz(
        GL_LIGHT1,
        igvPunto3D(-1, -1, -1),        // Dirección (w=0 para direccional)
        igvColor(0.1, 0.1, 0.1),       // Ambiental
        igvColor(0.7, 0.7, 0.7),       // Difuso
        igvColor(0.5, 0.5, 0.5),       // Especular
        1.0, 0.0, 0.0                  // Atenuación
    );

    // Luz puntual (GL_LIGHT2)
    luzPuntual = igvFuenteLuz(
        GL_LIGHT2,
        igvPunto3D(5, 5, 5),           // Posición
        igvColor(0.1, 0.1, 0.1),       // Ambiental
        igvColor(0.8, 0.8, 0.6),       // Difuso (amarillento)
        igvColor(1.0, 1.0, 1.0),       // Especular
        1.0, 0.01, 0.001               // Atenuación
    );

    // Cono de luz / Spotlight (GL_LIGHT3)
    luzCono = igvFuenteLuz(
        GL_LIGHT3,
        igvPunto3D(0, 8, 0),           // Posición
        igvColor(0.0, 0.0, 0.0),       // Ambiental
        igvColor(1.0, 1.0, 1.0),       // Difuso
        igvColor(1.0, 1.0, 1.0),       // Especular
        1.0, 0.0, 0.0,                 // Atenuación
        igvPunto3D(0, -1, 0),          // Dirección del foco (hacia abajo)
        30.0,                          // Ángulo de apertura (grados)
        15.0                           // Exponente del foco
    );

    // Encender las luces por defecto
    luzAmbiente.encender();
    luzDireccional.encender();
    luzPuntual.encender();
    luzCono.encender();
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
