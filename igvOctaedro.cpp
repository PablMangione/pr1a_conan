#include "igvOctaedro.h"
#include <cmath>

/**
 * Constructor por defecto
 */
igvOctaedro::igvOctaedro() : igvMallaTriangulos()
{
}

/**
 * Constructor parametrizado
 * @param lado Longitud de la arista del octaedro
 * @pre Se asume que el parámetro tiene un valor válido
 * @post Se crea una nueva malla de triángulos que representa un octaedro regular
 */
igvOctaedro::igvOctaedro(float lado)
{
    // Un octaedro regular tiene 6 vértices y 8 caras triangulares
    // Los vértices están ubicados en los ejes coordenados
    
    float mitad = lado / std::sqrt(2.0f);
    
    num_vertices = 6;
    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];
    
    // Vértice 0: (mitad, 0, 0) - derecha
    vertices[0] = mitad; vertices[1] = 0.0f; vertices[2] = 0.0f;
    // Vértice 1: (-mitad, 0, 0) - izquierda
    vertices[3] = -mitad; vertices[4] = 0.0f; vertices[5] = 0.0f;
    // Vértice 2: (0, mitad, 0) - arriba
    vertices[6] = 0.0f; vertices[7] = mitad; vertices[8] = 0.0f;
    // Vértice 3: (0, -mitad, 0) - abajo
    vertices[9] = 0.0f; vertices[10] = -mitad; vertices[11] = 0.0f;
    // Vértice 4: (0, 0, mitad) - frente
    vertices[12] = 0.0f; vertices[13] = 0.0f; vertices[14] = mitad;
    // Vértice 5: (0, 0, -mitad) - atrás
    vertices[15] = 0.0f; vertices[16] = 0.0f; vertices[17] = -mitad;
    
    // Calcular normales (apuntan hacia afuera desde el centro)
    for (int i = 0; i < num_vertices; ++i)
    {
        float x = vertices[i * 3 + 0];
        float y = vertices[i * 3 + 1];
        float z = vertices[i * 3 + 2];
        float longitud = std::sqrt(x * x + y * y + z * z);
        
        normales[i * 3 + 0] = x / longitud;
        normales[i * 3 + 1] = y / longitud;
        normales[i * 3 + 2] = z / longitud;
    }
    
    // 8 caras triangulares
    num_triangulos = 8;
    triangulos = new unsigned int[num_triangulos * 3];
    
    int t = 0;
    
    // 4 caras superiores (conectadas al vértice 2: arriba)
    // Cara frontal-derecha-superior
    triangulos[t++] = 2; triangulos[t++] = 0; triangulos[t++] = 4;
    // Cara frontal-izquierda-superior
    triangulos[t++] = 2; triangulos[t++] = 4; triangulos[t++] = 1;
    // Cara trasera-izquierda-superior
    triangulos[t++] = 2; triangulos[t++] = 1; triangulos[t++] = 5;
    // Cara trasera-derecha-superior
    triangulos[t++] = 2; triangulos[t++] = 5; triangulos[t++] = 0;
    
    // 4 caras inferiores (conectadas al vértice 3: abajo)
    // Cara frontal-derecha-inferior
    triangulos[t++] = 3; triangulos[t++] = 4; triangulos[t++] = 0;
    // Cara frontal-izquierda-inferior
    triangulos[t++] = 3; triangulos[t++] = 1; triangulos[t++] = 4;
    // Cara trasera-izquierda-inferior
    triangulos[t++] = 3; triangulos[t++] = 5; triangulos[t++] = 1;
    // Cara trasera-derecha-inferior
    triangulos[t++] = 3; triangulos[t++] = 0; triangulos[t++] = 5;
}

/**
 * Destructor
 */
igvOctaedro::~igvOctaedro()
{
}
