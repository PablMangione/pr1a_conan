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
    bool modo1 = true; // true = TRS, false = Secuencial

    // Estructura para almacenar cada transformación individual
    struct Transformacion {
        enum Tipo { TRASLACION, ROTACION_X, ROTACION_Y, ROTACION_Z, ESCALADO };
        Tipo tipo;
        float param1, param2, param3; // Para traslación (dx,dy,dz), para rotación (ángulo), para escalado (factor)
    };

    // UNA SOLA secuencia de transformaciones compartida
    std::vector<Transformacion> secuenciaTransformaciones;

    struct Objeto3D {
        // Posición inicial fija de cada objeto
        float tx_inicial = 0.0f, ty_inicial = 0.0f, tz_inicial = 0.0f;
        bool seleccionado = false;
    };

    Objeto3D objetos[3];
    int objetoSeleccionado = 0;

    void pintar_ejes();
    void renderObjeto1();
    void renderObjeto2();
    void renderObjeto3();
    void aplicarTransformaciones();
    void dibujarIndicadorSeleccion();
    void aplicarTransformacion(const Transformacion& t);
};

#endif