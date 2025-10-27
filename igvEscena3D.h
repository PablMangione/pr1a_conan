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

    void visualizarParaSeleccion();
    ParteSeleccionable seleccionarPorColor(unsigned char r, unsigned char g, unsigned char b);
    void setParteSeleccionada(ParteSeleccionable parte);
    ParteSeleccionable getParteSeleccionada() const;
    void rotarParteSeleccionada(float incremento);

private:
    bool ejes = true;
    igvModeloArticulado modelo;

    void pintar_ejes();
};

#endif