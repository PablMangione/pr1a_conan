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
 * Por ahora contiene primitivas básicas, en el futuro
 * implementará un grafo de escena con jerarquía y articulaciones.
 */
class igvModeloArticulado {
private:
    std::vector<igvMallaTriangulos*> primitivas;
    
public:
    // Constructor y destructor
    igvModeloArticulado();
    ~igvModeloArticulado();
    
    // Métodos
    void visualizar();
    void cambiarModoSombreado();
    void cambiarUsoNormales();
    
    // Métodos para futuro grafo de escena
    // void aplicarTransformacion(...);
    // void seleccionarParte(int id);
    // void moverParteSeleccionada(...);
};

#endif // __IGV_MODELO_ARTICULADO