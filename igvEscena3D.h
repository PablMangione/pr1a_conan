#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include "Mallas/igvModeloArticulado.h"
#include "igvMaterial.h"
#include "igvTextura.h"
#include "igvFuenteLuz.h"

class igvEscena3D {
public:
    igvEscena3D();

    ~igvEscena3D();

    void visualizar();

    bool get_ejes();

    void set_ejes(bool _ejes);

    void cambiarModoSombreado();

    void cambiarUsoNormales();

    void rotarBaseLampara(float incremento);

    void rotarBrazo1Lampara(float incremento);

    void rotarBrazo2Lampara(float incremento);

    void rotarPantallaLampara(float incremento);

    void resetearPoseLampara();

    int getParteSeleccionada() const { return parteSeleccionada; }

    void setParteSeleccionada(int parte) { parteSeleccionada = parte; }

    void seleccionarParte(int x, int y, int alto_ventana);

    // ============================================
    // MÉTODOS PARA SUELO Y MATERIALES
    // ============================================
    void setMaterialSuelo(int indice);

    int getMaterialSuelo() const { return materialActual; }

    // ============================================
    // MÉTODOS PARA TEXTURAS
    // ============================================
    void setTexturaSuelo(int indice);

    void toggleTexturas();

    bool getTexturasActivas() const { return texturasActivas; }

    void setFiltroMag(GLenum filtro);

    void setFiltroMin(GLenum filtro);

    // ============================================
    // MÉTODOS PARA LUCES
    // ============================================
    void toggleLuzAmbiente();

    void toggleLuzDireccional();

    void toggleLuzPuntual();

    void toggleLuzCono();

    void moverLuzPuntual(float dx, float dy, float dz);

    void moverLuzCono(float dx, float dy, float dz);

    igvFuenteLuz &getLuzPuntual() { return luzPuntual; }
    igvFuenteLuz &getLuzCono() { return luzCono; }

    void inicializaLMT();

private:
    bool ejes = true;
    igvModeloArticulado modelo;
    int parteSeleccionada = -1;

    // SUELO
    // ============================================
    int materialActual = 0; // Índice del material actual (0, 1, 2)
    igvMaterial materialesSuelo[3]; // 3 materiales predefinidos

    // ============================================
    // TEXTURAS
    // ============================================
    bool texturasActivas = false; // Si se aplican texturas o no
    int texturaActual = 0; // Índice de textura actual (0, 1, 2)
    igvTextura *texturas[3]; // 3 texturas (incluyendo ajedrez)
    GLenum filtroMag = GL_LINEAR; // Filtro de magnificación
    GLenum filtroMin = GL_LINEAR; // Filtro de minificación

    // ============================================
    // LUCES
    // ============================================
    igvFuenteLuz luzAmbiente; // Luz ambiental global
    igvFuenteLuz luzDireccional; // Luz direccional (tipo sol)
    igvFuenteLuz luzPuntual; // Luz puntual (bombilla)
    igvFuenteLuz luzCono; // Cono de luz (spotlight)

    bool luzAmbienteActiva = true;
    bool luzDireccionalActiva = true;
    bool luzPuntualActiva = true;
    bool luzConoActiva = true;

    void visualizarModoSeleccion();

    unsigned char *capturarBufferSeleccion(int x, int y);

    int identificarPartePorColor(unsigned char r, unsigned char g, unsigned char b);

    void pintar_ejes();

    void dibujarSuelo();
};

#endif
