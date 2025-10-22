#include "igvDisco.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * Constructor por defecto
 */
igvDisco::igvDisco() : igvMallaTriangulos()
{
}

/**
 * Constructor parametrizado
 * @param radio Radio del disco
 * @param divisiones Número de divisiones radiales
 * @pre Se asume que los parámetros tienen valores válidos
 * @post Se crea una nueva malla de triángulos que representa un disco
 */
igvDisco::igvDisco(float radio, int divisiones)
{
    if (divisiones < 3) divisiones = 3;
    
    // Vértices: 1 central + divisiones en el perímetro
    num_vertices = divisiones + 1;
    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];
    
    // Vértice central (0, 0, 0)
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;
    
    // Normal del vértice central (apunta en Y+)
    normales[0] = 0.0f;
    normales[1] = 1.0f;
    normales[2] = 0.0f;
    
    // Vértices del perímetro
    for (int i = 0; i < divisiones; ++i)
    {
        float angulo = (i / (float)divisiones) * 2.0f * (float)M_PI;
        float x = radio * std::cos(angulo);
        float z = radio * std::sin(angulo);
        
        int idx = (i + 1) * 3;
        vertices[idx + 0] = x;
        vertices[idx + 1] = 0.0f;
        vertices[idx + 2] = z;
        
        // Todas las normales apuntan hacia arriba (Y+)
        normales[idx + 0] = 0.0f;
        normales[idx + 1] = 1.0f;
        normales[idx + 2] = 0.0f;
    }
    
    // Triángulos: un triángulo por cada división
    num_triangulos = divisiones;
    triangulos = new unsigned int[num_triangulos * 3];
    
    int t = 0;
    for (int i = 0; i < divisiones; ++i)
    {
        triangulos[t++] = 0;  // Vértice central
        triangulos[t++] = i + 1;
        triangulos[t++] = ((i + 1) % divisiones) + 1;
    }
}

/**
 * Destructor
 */
igvDisco::~igvDisco()
{
}
