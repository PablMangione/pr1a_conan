#include <cstdlib>

#include "igvInterfaz.h"

igvInterfaz *igvInterfaz::_instancia = nullptr;

igvInterfaz::igvInterfaz() {
    camara.set(igvPunto3D(1.5, 1.0, 2.0),
               igvPunto3D(0.0, 0.0, 0.0),
               igvPunto3D(0.0, 1.0, 0.0));
}

igvInterfaz &igvInterfaz::getInstancia() {
    if (!_instancia) {
        _instancia = new igvInterfaz;
    }

    return *_instancia;
}

void igvInterfaz::configura_entorno(int argc, char **argv
                                    , int _ancho_ventana, int _alto_ventana
                                    , int _pos_X, int _pos_Y
                                    , std::string _titulo) {
    ancho_ventana = _ancho_ventana;
    alto_ventana = _alto_ventana;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_ancho_ventana, _alto_ventana);
    glutInitWindowPosition(_pos_X, _pos_Y);
    glutCreateWindow(_titulo.c_str());


    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
}


void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop();
}

void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'e':
        case 'E':
            _instancia->escena.set_ejes(!_instancia->escena.get_ejes());
            break;
        case '1':
            _instancia->escena.seleccionarObjeto(0);
            break;
        case '2':
            _instancia->escena.seleccionarObjeto(1);
            break;
        case '3':
            _instancia->escena.seleccionarObjeto(2);
            break;
        case 'u':
            _instancia->escena.trasladar(0.0f, 0.1f, 0.0f);
            break;
        case 'U':
            _instancia->escena.trasladar(0.0f, -0.1f, 0.0f);
            break;
        case 'x':
            _instancia->escena.rotar('x', 5.0f);
            break;
        case 'X':
            _instancia->escena.rotar('x', -5.0f);
            break;
        case 'y':
            _instancia->escena.rotar('y', 5.0f);
            break;
        case 'Y':
            _instancia->escena.rotar('y', -5.0f);
            break;
        case 'z':
            _instancia->escena.rotar('z', 5.0f);
            break;
        case 'Z':
            _instancia->escena.rotar('z', -5.0f);
            break;
        case 's':
            _instancia->escena.escalar(1.1f);
            break;
        case 'S':
            _instancia->escena.escalar(0.9f);
            break;
        case 'm':
        case 'M':
            _instancia->escena.cambiarModo();
            break;
        case 27:
            exit(1);
    }
    glutPostRedisplay();
}

void igvInterfaz::specialFunc(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            _instancia->escena.trasladar(0.1f, 0.0f, 0.0f);
            break;
        case GLUT_KEY_LEFT:
            _instancia->escena.trasladar(-0.1f, 0.0f, 0.0f);
            break;
        case GLUT_KEY_UP:
            _instancia->escena.trasladar(0.0f, 0.0f, -0.1f);
            break;
        case GLUT_KEY_DOWN:
            _instancia->escena.trasladar(0.0f, 0.0f, 0.1f);
            break;
    }
    glutPostRedisplay();
}

void igvInterfaz::reshapeFunc(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    _instancia->set_ancho_ventana(w);
    _instancia->set_alto_ventana(h);
    _instancia->camara.aplicar();
}

void igvInterfaz::displayFunc() {
    if (_instancia->modoMultiViewport) {
        // Modo 4 viewports
        for (int i = 0; i < 4; i++) {
            _instancia->camara.aplicarViewport(i,
                                               _instancia->ancho_ventana,
                                               _instancia->alto_ventana);
            _instancia->escena.visualizar();

            // Dibujar bordes del viewport para claridad
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, 1, 0, 1, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glDisable(GL_LIGHTING);
            glColor3f(0.3f, 0.3f, 0.3f);
            glBegin(GL_LINE_LOOP);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(1.0f, 0.0f);
            glVertex2f(1.0f, 1.0f);
            glVertex2f(0.0f, 1.0f);
            glEnd();
            glEnable(GL_LIGHTING);
        }

        // Añadir etiquetas de texto para cada vista
        glDisable(GL_LIGHTING);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, _instancia->ancho_ventana, 0, _instancia->alto_ventana);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(0.0f, 0.0f, 0.0f);

        // Etiqueta ALZADO (superior izquierda)
        glRasterPos2i(10, _instancia->alto_ventana - 20);
        const char* texto1 = "ALZADO";
        for (const char* c = texto1; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        // Etiqueta PLANTA (superior derecha)
        glRasterPos2i(_instancia->ancho_ventana/2 + 10, _instancia->alto_ventana - 20);
        const char* texto2 = "PLANTA";
        for (const char* c = texto2; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        // Etiqueta PERFIL (inferior izquierda)
        glRasterPos2i(10, _instancia->alto_ventana/2 - 20);
        const char* texto3 = "PERFIL";
        for (const char* c = texto3; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        // Etiqueta NORMAL (inferior derecha)
        glRasterPos2i(_instancia->ancho_ventana/2 + 10, _instancia->alto_ventana/2 - 20);
        const char* texto4 = "NORMAL";
        for (const char* c = texto4; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }

        glEnable(GL_LIGHTING);
    }
    else {
        // Modo vista única normal
        _instancia->camara.aplicar();
        _instancia->escena.visualizar();
    }
}

void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
}

int igvInterfaz::get_ancho_ventana() {
    return ancho_ventana;
}

int igvInterfaz::get_alto_ventana() {
    return alto_ventana;
}

void igvInterfaz::set_ancho_ventana(int _ancho_ventana) {
    ancho_ventana = _ancho_ventana;
}

void igvInterfaz::set_alto_ventana(int _alto_ventana) {
    alto_ventana = _alto_ventana;
}