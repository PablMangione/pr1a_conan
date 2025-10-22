#include "igvTetraedro.h"
#include <cmath>

/**
 * Constructor por defecto
 */
igvTetraedro::igvTetraedro() : igvMallaTriangulos()
{
}

/**
 * Constructor parametrizado
 * @param lado Longitud de la arista del tetraedro
 * @pre Se asume que el parámetro tiene un valor válido
 * @post Se crea una nueva malla de triángulos que representa un tetraedro regular
 */
igvTetraedro::igvTetraedro(float lado)
{
    // Un tetraedro regular tiene 4 vértices y 4 caras triangulares
    
    num_vertices = 4;
    vertices = new float[num_vertices * 3];
    normales = new float[num_vertices * 3];
    
    // Cálculos para un tetraedro regular centrado en el origen
    float a = lado / std::sqrt(2.0f);
    float h = lado * std::sqrt(2.0f / 3.0f);
    float d = lado * std::sqrt(3.0f) / 6.0f;
    
    // Vértice 0: base, esquina frontal
    vertices[0] = 0.0f;
    vertices[1] = -h / 4.0f;
    vertices[2] = a / 2.0f;
    
    // Vértice 1: base, esquina izquierda
    vertices[3] = -a / 2.0f;
    vertices[4] = -h / 4.0f;
    vertices[5] = -lado / (2.0f * std::sqrt(3.0f));
    
    // Vértice 2: base, esquina derecha
    vertices[6] = a / 2.0f;
    vertices[7] = -h / 4.0f;
    vertices[8] = -lado / (2.0f * std::sqrt(3.0f));
    
    // Vértice 3: vértice superior (ápice)
    vertices[9] = 0.0f;
    vertices[10] = 3.0f * h / 4.0f;
    vertices[11] = 0.0f;
    
    // Calcular normales aproximadas (promedio de las normales de las caras adyacentes)
    // Para un tetraedro regular, las normales apuntan desde el centro hacia cada vértice
    
    // Centro del tetraedro
    float cx = (vertices[0] + vertices[3] + vertices[6] + vertices[9]) / 4.0f;
    float cy = (vertices[1] + vertices[4] + vertices[7] + vertices[10]) / 4.0f;
    float cz = (vertices[2] + vertices[5] + vertices[8] + vertices[11]) / 4.0f;
    
    for (int i = 0; i < num_vertices; ++i)
    {
        float nx = vertices[i * 3 + 0] - cx;
        float ny = vertices[i * 3 + 1] - cy;
        float nz = vertices[i * 3 + 2] - cz;
        float longitud = std::sqrt(nx * nx + ny * ny + nz * nz);
        
        normales[i * 3 + 0] = nx / longitud;
        normales[i * 3 + 1] = ny / longitud;
        normales[i * 3 + 2] = nz / longitud;
    }
    
    // 4 caras triangulares
    num_triangulos = 4;
    triangulos = new unsigned int[num_triangulos * 3];
    
    int t = 0;
    
    // Cara base (vértices 0, 1, 2)
    triangulos[t++] = 0;
    triangulos[t++] = 2;
    triangulos[t++] = 1;
    
    // Cara frontal (vértices 0, 3, 2)
    triangulos[t++] = 0;
    triangulos[t++] = 3;
    triangulos[t++] = 2;
    
    // Cara izquierda (vértices 0, 1, 3)
    triangulos[t++] = 0;
    triangulos[t++] = 1;
    triangulos[t++] = 3;
    
    // Cara derecha (vértices 1, 2, 3)
    triangulos[t++] = 1;
    triangulos[t++] = 2;
    triangulos[t++] = 3;
}

/**
 * Destructor
 */
igvTetraedro::~igvTetraedro()
{
}
