#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "igvMallaTriangulos.h"


igvMallaTriangulos::igvMallaTriangulos(long int _num_vertices, float *_vertices
                                       , long int _num_triangulos
                                       , unsigned int *_triangulos) : num_vertices(_num_vertices)
                                                                      , num_triangulos(_num_triangulos) {
    num_vertices = _num_vertices;
    vertices = new float[num_vertices * 3];
    for (long int i = 0; i < (num_vertices * 3); ++i) {
        vertices[i] = _vertices[i];
    }

    normales = nullptr;

    num_triangulos = _num_triangulos;
    triangulos = new unsigned int[num_triangulos * 3];
    for (long int i = 0; i < (num_triangulos * 3); ++i) {
        triangulos[i] = _triangulos[i];
    }
}

igvMallaTriangulos::~igvMallaTriangulos() {
    if (vertices) {
        delete []vertices;
        vertices = nullptr;
    }

    if (normales) {
        delete []normales;
        normales = nullptr;
    }

    if (triangulos) {
        delete []triangulos;
        triangulos = nullptr;
    }
}

void igvMallaTriangulos::visualizar() {
    if (!gouraud) {
        glShadeModel(GL_FLAT);
    } else {
        glShadeModel(GL_SMOOTH);
    }

    glEnable(GL_NORMALIZE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    if (usarnormales) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, normales);
    }

    glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, triangulos);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}
