#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "igvMallaTriangulos.h"

class igvEscena3D {
public:
    igvEscena3D();

    ~igvEscena3D();

    void visualizar();

    bool get_ejes();

    void set_ejes(bool _ejes);

private:
    bool ejes = true;
    igvMallaTriangulos* malla = nullptr;

    void pintar_ejes();

    igvMallaTriangulos* getMalla() const { return malla; }
};

#endif
