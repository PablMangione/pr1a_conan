#include <cstdlib>
#include <cstdio>

#include "igvInterfaz.h"

igvInterfaz *igvInterfaz::_instancia = nullptr;

igvInterfaz::igvInterfaz() {
    camara.set(igvPunto3D(3.5, 4.0, 10.0),
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
            if (_instancia->camara.getTipo() == IGV_PARALELA)
                _instancia->camara.set(IGV_PERSPECTIVA);
            else
                _instancia->camara.set(IGV_PARALELA);
            break;

        case 'v':
        case 'V':
            _instancia->cambiaModoMultiViewPort();
            break;

        case 's':
        case 'S':
            _instancia->escena.cambiarModoSombreado();
            _instancia->escena.cambiarUsoNormales();
            printf("Modo de sombreado cambiado\n");
            break;

        case 'r':
        case 'R':
            _instancia->escena.resetearPoseLampara();
            printf("Pose reseteada\n");
            break;

        case 'a':
        case 'A':
            _instancia->animacionModelo = !_instancia->animacionModelo;
            if (_instancia->animacionModelo) {
                printf("Animacion automatica del MODELO activada\n");
                if (!_instancia->animacionCamara) {
                    glutTimerFunc(_instancia->timerAnimacion, timerFunc, 0);
                }
            } else {
                printf("Animacion automatica del MODELO desactivada\n");
            }
            break;

        case 'g':
        case 'G':
            _instancia->animacionCamara = !_instancia->animacionCamara;
            if (_instancia->animacionCamara) {
                printf("Movimiento automatico de CAMARA activado\n");
                if (!_instancia->animacionModelo) {
                    glutTimerFunc(_instancia->timerAnimacion, timerFunc, 0);
                }
            } else {
                printf("Movimiento automatico de CAMARA desactivado\n");
            }
            break;

        case '1':
            _instancia->escena.setParteSeleccionada(0);
            printf("Parte seleccionada: BASE - Usa cursores para rotar\n");
            break;

        case '2':
            _instancia->escena.setParteSeleccionada(1);
            printf("Parte seleccionada: BRAZO 1 - Usa cursores para rotar\n");
            break;

        case '3':
            _instancia->escena.setParteSeleccionada(2);
            printf("Parte seleccionada: BRAZO 2 - Usa cursores para rotar\n");
            break;

        case '4':
            _instancia->escena.setParteSeleccionada(3);
            printf("Parte seleccionada: PANTALLA - Usa cursores para rotar\n");
            break;

        case '0':
            _instancia->escena.setParteSeleccionada(-1);
            printf("Ninguna parte seleccionada\n");
            break;

        case 27:
            exit(1);
    }
    glutPostRedisplay();
}

void igvInterfaz::specialFunc(int key, int x, int y) {
    int parteSeleccionada = _instancia->escena.getParteSeleccionada();

    if (parteSeleccionada >= 0) {
        switch (key) {
            case GLUT_KEY_LEFT:
            case GLUT_KEY_DOWN:
                switch (parteSeleccionada) {
                    case 0: _instancia->escena.rotarBaseLampara(-5.0f); break;
                    case 1: _instancia->escena.rotarBrazo1Lampara(-5.0f); break;
                    case 2: _instancia->escena.rotarBrazo2Lampara(-5.0f); break;
                    case 3: _instancia->escena.rotarPantallaLampara(-5.0f); break;
                }
                break;

            case GLUT_KEY_RIGHT:
            case GLUT_KEY_UP:
                switch (parteSeleccionada) {
                    case 0: _instancia->escena.rotarBaseLampara(5.0f); break;
                    case 1: _instancia->escena.rotarBrazo1Lampara(5.0f); break;
                    case 2: _instancia->escena.rotarBrazo2Lampara(5.0f); break;
                    case 3: _instancia->escena.rotarPantallaLampara(5.0f); break;
                }
                break;
        }
    } else {
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
    }

    glutPostRedisplay();
}

void igvInterfaz::reshapeFunc(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    _instancia->set_ancho_ventana(w);
    _instancia->set_alto_ventana(h);
    _instancia->camara.aplicar();
}

void igvInterfaz::mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            _instancia->escena.seleccionarParte(x, y, _instancia->alto_ventana);
            int parte = _instancia->escena.getParteSeleccionada();
            if (parte >= 0) {
                _instancia->arrastrando = true;
                _instancia->mouseX_anterior = x;
                _instancia->mouseY_anterior = y;
                switch(parte) {
                    case 0:
                        printf("Base seleccionada - Arrastra o usa cursores para rotar\n");
                        break;
                    case 1:
                        printf("Brazo 1 seleccionado - Arrastra o usa cursores para rotar\n");
                        break;
                    case 2:
                        printf("Brazo 2 seleccionado - Arrastra o usa cursores para rotar\n");
                        break;
                    case 3:
                        printf("Pantalla seleccionada - Arrastra o usa cursores para rotar\n");
                        break;
                }
            } else {
                printf("No se selecciono ninguna parte - Haz clic en la lampara o usa teclas 1-4\n");
            }
        } else if (state == GLUT_UP) {
            _instancia->arrastrando = false;
        }
    }
    glutPostRedisplay();
}

void igvInterfaz::motionFunc(int x, int y) {
    if (_instancia->arrastrando) {
        int parteSeleccionada = _instancia->escena.getParteSeleccionada();

        if (parteSeleccionada >= 0) {
            int dx = x - _instancia->mouseX_anterior;
            int dy = y - _instancia->mouseY_anterior;

            float sensibilidad = 0.5f;

            switch (parteSeleccionada) {
                case 0:
                    _instancia->escena.rotarBaseLampara(dx * sensibilidad);
                    break;

                case 1:
                    _instancia->escena.rotarBrazo1Lampara(-dy * sensibilidad);
                    break;

                case 2:
                    _instancia->escena.rotarBrazo2Lampara(-dy * sensibilidad);
                    break;

                case 3:
                    _instancia->escena.rotarPantallaLampara(-dy * sensibilidad);
                    break;
            }

            _instancia->mouseX_anterior = x;
            _instancia->mouseY_anterior = y;

            glutPostRedisplay();
        }
    }
}

void igvInterfaz::displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_instancia->modoMultiViewport) {
        for (int i = 0; i < 4; i++) {
            _instancia->camara.aplicarViewport(i,
                                               _instancia->ancho_ventana,
                                               _instancia->alto_ventana);

            _instancia->escena.visualizar();
        }
    } else {
        glViewport(0, 0, _instancia->ancho_ventana, _instancia->alto_ventana);
        _instancia->camara.aplicar();
        _instancia->escena.visualizar();
    }

    glutSwapBuffers();
}

void igvInterfaz::timerFunc(int value) {
    bool hayAnimacion = false;

    if (_instancia->animacionModelo) {
        _instancia->escena.rotarBaseLampara(1.0f);
        hayAnimacion = true;
    }

    if (_instancia->animacionCamara) {
        _instancia->camara.orbita(0.5);
        hayAnimacion = true;
    }

    if (hayAnimacion) {
        glutPostRedisplay();
        glutTimerFunc(_instancia->timerAnimacion, timerFunc, 0);
    }
}

void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
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