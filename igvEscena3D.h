#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif   // defined(__APPLE__) && defined(__MACH__)

class igvEscena3D {
public:
    igvEscena3D();

    ~igvEscena3D() = default;

    void visualizar();

    bool get_ejes();

    void set_ejes(bool _ejes);

    void seleccionarObjeto(int indice);

    int getObjetoSeleccionado() { return objetoSeleccionado; }

    void trasladar(float dx, float dy, float dz);

    void rotar(char eje, float angulo);

    void escalar(float factor);

private:
    bool ejes = true;

    struct Objeto3D {
        //CONSEJO PARA EVITAR COPIAS: convertir el struct en una clase
        //10 atributos, constructores, destructor, getters y setters
        float tx = 0.0f, ty = 0.0f, tz = 0.0f;
        float rx = 0.0f, ry = 0.0f, rz = 0.0f;
        float sx = 1.0f, sy = 1.0f, sz = 1.0f;
        bool seleccionado = false;
    };

    Objeto3D objetos[3];
    int objetoSeleccionado = 0;

    void pintar_ejes();

    void renderObjeto1();

    void renderObjeto2();

    void renderObjeto3();

    void aplicarTransformaciones(int indice);

    void dibujarIndicadorSeleccion();
};

#endif   // __IGVESCENA3D
