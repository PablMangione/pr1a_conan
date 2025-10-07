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
            if (_instancia->camara.getMovimientoActivo())
                _instancia->camara.rotacionEjeY(5.0);
            else
                _instancia->escena.rotar('y', 5.0f);
            break;
        case 'Y':
            if (_instancia->camara.getMovimientoActivo())
                _instancia->camara.rotacionEjeY(-5.0);
            else
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
        case 'c':
        case 'C':
            _instancia->camara.activarMovimiento();
            break;
        case 'f':
        case 'F':
            if (_instancia->camara.getMovimientoActivo())
                _instancia->camara.desplazarAdelante(0.2);
            break;
        case 'b':
        case 'B':
            if (_instancia->camara.getMovimientoActivo())
                _instancia->camara.desplazarAdelante(-0.2);
            break;
        case '+':
            _instancia->camara.zoom(10.0);
            break;
        case '-':
            _instancia->camara.zoom(-10.0);
            break;
        case 'p':
        case 'P':
            _instancia->cambiaModoMultiViewPort();
            break;
        case 27:
            exit(1);
    }
    glutPostRedisplay();
}

void igvInterfaz::specialFunc(int key, int x, int y) {
    if (_instancia->camara.getMovimientoActivo()) {
        switch (key) {
            case GLUT_KEY_LEFT:
                _instancia->camara.orbita(-5.0);
                break;
            case GLUT_KEY_RIGHT:
                _instancia->camara.orbita(5.0);
                break;
            case GLUT_KEY_UP:
                _instancia->camara.cabeceo(5.0);
                break;
            case GLUT_KEY_DOWN:
                _instancia->camara.cabeceo(-5.0);
                break;
        }
    } else {
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
    _instancia->escena.visualizar();
    _instancia->camara.aplicar();
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
