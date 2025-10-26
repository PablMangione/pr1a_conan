#ifndef __IGV_MODELO_ARTICULADO
#define __IGV_MODELO_ARTICULADO

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "igvMallaTriangulos.h"

/**
 * Clase que encapsula un modelo articulado.
 * Implementa la lámpara de Pixar con estructura jerárquica
 * preparada para convertirse en grafo de escena.
 */
class igvModeloArticulado {
private:
    // Primitivas que conforman la lámpara
    igvMallaTriangulos* base;           // Base de la lámpara
    igvMallaTriangulos* brazo1;         // Primer brazo (inferior)
    igvMallaTriangulos* articulacion1;  // Esfera de articulación 1
    igvMallaTriangulos* brazo2;         // Segundo brazo (superior)
    igvMallaTriangulos* articulacion2;  // Esfera de articulación 2
    igvMallaTriangulos* pantalla;       // Pantalla/cabeza de la lámpara

    // Ángulos de rotación para las articulaciones (grados de libertad)
    float anguloBase;          // Rotación sobre Y de toda la lámpara
    float anguloBrazo1;        // Rotación del brazo 1 sobre Z
    float anguloBrazo2;        // Rotación del brazo 2 sobre Z
    float anguloPantalla;      // Rotación de la pantalla sobre Z

    // Dimensiones de los componentes
    struct Dimensiones {
        float radioBase;
        float alturaBase;
        float longitudBrazo1;
        float radioBrazo1;
        float radioArticulacion;
        float longitudBrazo2;
        float radioBrazo2;
        float radioPantalla;
        float alturaPantalla;
    } dim;

    // Métodos privados para dibujar cada parte
    void dibujarBase();
    void dibujarBrazo1();
    void dibujarArticulacion1();
    void dibujarBrazo2();
    void dibujarArticulacion2();
    void dibujarPantalla();

    void crearPrimitivas();

public:
    // Constructor y destructor
    igvModeloArticulado();
    ~igvModeloArticulado();

    // Métodos de visualización
    void visualizar();
    void cambiarModoSombreado();
    void cambiarUsoNormales();

    // Métodos para manipular las articulaciones
    void rotarBase(float incremento);
    void rotarBrazo1(float incremento);
    void rotarBrazo2(float incremento);
    void rotarPantalla(float incremento);

    // Métodos para obtener/establecer ángulos
    float getAnguloBase() const { return anguloBase; }
    float getAnguloBrazo1() const { return anguloBrazo1; }
    float getAnguloBrazo2() const { return anguloBrazo2; }
    float getAnguloPantalla() const { return anguloPantalla; }

    void setAnguloBase(float angulo) { anguloBase = angulo; }
    void setAnguloBrazo1(float angulo) { anguloBrazo1 = angulo; }
    void setAnguloBrazo2(float angulo) { anguloBrazo2 = angulo; }
    void setAnguloPantalla(float angulo) { anguloPantalla = angulo; }

    void resetearPose();
};

#endif // __IGV_MODELO_ARTICULADO