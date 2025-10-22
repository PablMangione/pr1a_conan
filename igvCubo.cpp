#include "igvCubo.h"
#include <cmath>

/**
 * Constructor por defecto
 */
igvCubo::igvCubo() : igvMallaTriangulos()
{
}

/**
 * Constructor parametrizado
 * @param lado Longitud del lado del cubo
 * @pre Se asume que el parámetro tiene un valor válido
 * @post Se crea una nueva malla de triángulos que representa un cubo
 */
igvCubo::igvCubo(float lado)
{
    float mitad = lado / 2.0f;
    
    // 8 vértices del cubo
    num_vertices = 8;
    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];
    
    // Definir los 8 vértices del cubo
    // Vértice 0: (-mitad, -mitad, mitad)
    vertices[0] = -mitad; vertices[1] = -mitad; vertices[2] = mitad;
    // Vértice 1: (mitad, -mitad, mitad)
    vertices[3] = mitad; vertices[4] = -mitad; vertices[5] = mitad;
    // Vértice 2: (mitad, mitad, mitad)
    vertices[6] = mitad; vertices[7] = mitad; vertices[8] = mitad;
    // Vértice 3: (-mitad, mitad, mitad)
    vertices[9] = -mitad; vertices[10] = mitad; vertices[11] = mitad;
    // Vértice 4: (-mitad, -mitad, -mitad)
    vertices[12] = -mitad; vertices[13] = -mitad; vertices[14] = -mitad;
    // Vértice 5: (mitad, -mitad, -mitad)
    vertices[15] = mitad; vertices[16] = -mitad; vertices[17] = -mitad;
    // Vértice 6: (mitad, mitad, -mitad)
    vertices[18] = mitad; vertices[19] = mitad; vertices[20] = -mitad;
    // Vértice 7: (-mitad, mitad, -mitad)
    vertices[21] = -mitad; vertices[22] = mitad; vertices[23] = -mitad;
    
    // Calcular normales (promedio de las caras adyacentes a cada vértice)
    float factor = 1.0f / std::sqrt(3.0f);
    
    normales[0] = -factor; normales[1] = -factor; normales[2] = factor;   // v0
    normales[3] = factor; normales[4] = -factor; normales[5] = factor;    // v1
    normales[6] = factor; normales[7] = factor; normales[8] = factor;     // v2
    normales[9] = -factor; normales[10] = factor; normales[11] = factor;  // v3
    normales[12] = -factor; normales[13] = -factor; normales[14] = -factor; // v4
    normales[15] = factor; normales[16] = -factor; normales[17] = -factor;  // v5
    normales[18] = factor; normales[19] = factor; normales[20] = -factor;   // v6
    normales[21] = -factor; normales[22] = factor; normales[23] = -factor;  // v7
    
    // 12 triángulos (2 por cada cara del cubo)
    num_triangulos = 12;
    triangulos = new unsigned int[num_triangulos * 3];
    
    int t = 0;
    
    // Cara frontal (Z+)
    triangulos[t++] = 0; triangulos[t++] = 1; triangulos[t++] = 2;
    triangulos[t++] = 0; triangulos[t++] = 2; triangulos[t++] = 3;
    
    // Cara trasera (Z-)
    triangulos[t++] = 5; triangulos[t++] = 4; triangulos[t++] = 7;
    triangulos[t++] = 5; triangulos[t++] = 7; triangulos[t++] = 6;
    
    // Cara izquierda (X-)
    triangulos[t++] = 4; triangulos[t++] = 0; triangulos[t++] = 3;
    triangulos[t++] = 4; triangulos[t++] = 3; triangulos[t++] = 7;
    
    // Cara derecha (X+)
    triangulos[t++] = 1; triangulos[t++] = 5; triangulos[t++] = 6;
    triangulos[t++] = 1; triangulos[t++] = 6; triangulos[t++] = 2;
    
    // Cara superior (Y+)
    triangulos[t++] = 3; triangulos[t++] = 2; triangulos[t++] = 6;
    triangulos[t++] = 3; triangulos[t++] = 6; triangulos[t++] = 7;
    
    // Cara inferior (Y-)
    triangulos[t++] = 4; triangulos[t++] = 5; triangulos[t++] = 1;
    triangulos[t++] = 4; triangulos[t++] = 1; triangulos[t++] = 0;
}

/**
 * Destructor
 */
igvCubo::~igvCubo()
{
}
