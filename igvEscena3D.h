#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif   // defined(__APPLE__) && defined(__MACH__)

#include <cmath>
class igvEscena3D {
public:
    igvEscena3D();

    ~igvEscena3D() = default;

    void visualizar();

    bool get_ejes();

    void set_ejes(bool _ejes);

    void seleccionarObjeto(int indice);

    int getObjetoSeleccionado();

    void trasladar(float dx, float dy, float dz);

    void rotar(char eje, float angulo);

    void escalar(float factor);

    void cambiarModo() { modo1 = !modo1; }

    bool getModo() { return modo1; }

private:
    bool ejes = true;

    bool modo1 = true;

    struct Objeto3D {
        //CONSEJO PARA EVITAR COPIAS: convertir el struct en una clase
        //10 atributos, constructores, destructor, getters y setters
        //OTRA IDEA, crear un array de tres posiciones para cada parámetro, por ej
        //tx[0] sería la traslación en el eje x del elemento 0 y así....
        float tx = 0.0f, ty = 0.0f, tz = 0.0f;
        float rx = 0.0f, ry = 0.0f, rz = 0.0f;
        float sx = 1.0f, sy = 1.0f, sz = 1.0f;
        bool seleccionado = false;
        GLfloat matrizTransformacion[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    };

    Objeto3D objetos[3];

    int objetoSeleccionado = 0;

    void pintar_ejes();

    void renderObjeto1();

    void renderObjeto2();

    void renderObjeto3();

    void aplicarTransformaciones(int indice);

    void dibujarIndicadorSeleccion();

    void multiplicarMatrices(GLfloat* nueva, GLfloat* acumulada);
};

#endif   // __IGVESCENA3D
