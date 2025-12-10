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

    create_menu();

    _instancia->escena.inicializaLMT();
}

void igvInterfaz::inicia_bucle_visualizacion() {
    glutMainLoop();
}

void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {
    igvInterfaz& interfaz = igvInterfaz::getInstancia();
    switch (key) {
        case 'e':
        case 'E':
            interfaz.escena.set_ejes(!interfaz.escena.get_ejes());
            break;

        case 'c':
        case 'C':
            interfaz.camara.activarMovimiento();
            break;

        case 'f':
        case 'F':
            if (interfaz.camara.getMovimientoActivo())
                interfaz.camara.desplazarAdelante(0.2);
            break;

        case 'b':
        case 'B':
            if (interfaz.camara.getMovimientoActivo())
                _instancia->camara.desplazarAdelante(-0.2);
            break;

        case '+':
            interfaz.camara.zoom(10.0);
            break;

        case '-':
            interfaz.camara.zoom(-10.0);
            break;

        case 'p':
        case 'P':
            if (interfaz.camara.getTipo() == IGV_PARALELA)
                interfaz.camara.set(IGV_PERSPECTIVA);
            else
                interfaz.camara.set(IGV_PARALELA);
            break;

        case 'v':
        case 'V':
            interfaz.cambiaModoMultiViewPort();
            break;

        case 's':
        case 'S':
            interfaz.escena.cambiarModoSombreado();
            interfaz.escena.cambiarUsoNormales();
            printf("Modo de sombreado cambiado\n");
            break;

        case 'r':
        case 'R':
            interfaz.escena.resetearPoseLampara();
            printf("Pose reseteada\n");
            break;

        case 'a':
        case 'A':
            interfaz.animacionModelo = !interfaz.animacionModelo;
            if (interfaz.animacionModelo) {
                printf("Animacion automatica del MODELO activada\n");
                if (!interfaz.animacionCamara) {
                    glutTimerFunc(interfaz.timerAnimacion, timerFunc, 0);
                }
            } else {
                printf("Animacion automatica del MODELO desactivada\n");
            }
            break;

        case 'g':
        case 'G':
            interfaz.animacionCamara = !interfaz.animacionCamara;
            if (_instancia->animacionCamara) {
                printf("Movimiento automatico de CAMARA activado\n");
                if (!interfaz.animacionModelo) {
                    glutTimerFunc(interfaz.timerAnimacion, timerFunc, 0);
                }
            } else {
                printf("Movimiento automatico de CAMARA desactivado\n");
            }
            break;

        case '1':
            interfaz.escena.setParteSeleccionada(0);
            printf("Parte seleccionada: BASE - Usa cursores para rotar\n");
            break;

        case '2':
            interfaz.escena.setParteSeleccionada(1);
            printf("Parte seleccionada: BRAZO 1 - Usa cursores para rotar\n");
            break;

        case '3':
            interfaz.escena.setParteSeleccionada(2);
            printf("Parte seleccionada: BRAZO 2 - Usa cursores para rotar\n");
            break;

        case '4':
            interfaz.escena.setParteSeleccionada(3);
            printf("Parte seleccionada: PANTALLA - Usa cursores para rotar\n");
            break;

        case '0':
            interfaz.escena.setParteSeleccionada(-1);
            printf("Ninguna parte seleccionada\n");
            break;

            // ============================================
            // MOVIMIENTO DE LUCES (cuando hay una seleccionada)
            // ============================================
        case 'x':  // Mover en -X
            if (interfaz.luzEnMovimiento == 0) {
                interfaz.escena.moverLuzPuntual(-0.5f, 0, 0);
            } else if (interfaz.luzEnMovimiento == 1) {
                interfaz.escena.moverLuzCono(-0.5f, 0, 0);
            }
            break;
        case 'X':  // Mover en +X
            if (interfaz.luzEnMovimiento == 0) {
                interfaz.escena.moverLuzPuntual(0.5f, 0, 0);
            } else if (interfaz.luzEnMovimiento == 1) {
                interfaz.escena.moverLuzCono(0.5f, 0, 0);
            }
            break;
        case 'y':  // Mover en -Y
            if (interfaz.luzEnMovimiento == 0) {
                interfaz.escena.moverLuzPuntual(0, -0.5f, 0);
            } else if (interfaz.luzEnMovimiento == 1) {
                interfaz.escena.moverLuzCono(0, -0.5f, 0);
            }
            break;
        case 'Y':  // Mover en +Y
            if (interfaz.luzEnMovimiento == 0) {
                interfaz.escena.moverLuzPuntual(0, 0.5f, 0);
            } else if (interfaz.luzEnMovimiento == 1) {
                interfaz.escena.moverLuzCono(0, 0.5f, 0);
            }
            break;
        case 'z':  // Mover en -Z
            if (interfaz.luzEnMovimiento == 0) {
                interfaz.escena.moverLuzPuntual(0, 0, -0.5f);
            } else if (interfaz.luzEnMovimiento == 1) {
                interfaz.escena.moverLuzCono(0, 0, -0.5f);
            }
            break;
        case 'Z':  // Mover en +Z
            if (interfaz.luzEnMovimiento == 0) {
                interfaz.escena.moverLuzPuntual(0, 0, 0.5f);
            } else if (interfaz.luzEnMovimiento == 1) {
                interfaz.escena.moverLuzCono(0, 0, 0.5f);
            }
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

void igvInterfaz::menuHandle(int opcion) {
    igvInterfaz& interfaz = igvInterfaz::getInstancia();

    switch (opcion) {
        // ============================================
        // MATERIALES DEL SUELO
        // ============================================
        case IGV_MENU_MATERIAL_1:
            interfaz.escena.setMaterialSuelo(0);
            break;
        case IGV_MENU_MATERIAL_2:
            interfaz.escena.setMaterialSuelo(1);
            break;
        case IGV_MENU_MATERIAL_3:
            interfaz.escena.setMaterialSuelo(2);
            break;

        // ============================================
        // TEXTURAS
        // ============================================
        case IGV_MENU_TEXTURA_OFF:
            interfaz.escena.toggleTexturas();
            break;
        case IGV_MENU_TEXTURA_1:
            interfaz.escena.setTexturaSuelo(0);
            break;
        case IGV_MENU_TEXTURA_2:
            interfaz.escena.setTexturaSuelo(1);
            break;
        case IGV_MENU_TEXTURA_AJEDREZ:
            interfaz.escena.setTexturaSuelo(2);
            break;

        // ============================================
        // FILTROS DE TEXTURA
        // ============================================
        case IGV_MENU_FILTRO_MAG_NEAREST:
            interfaz.escena.setFiltroMag(GL_NEAREST);
            break;
        case IGV_MENU_FILTRO_MAG_LINEAR:
            interfaz.escena.setFiltroMag(GL_LINEAR);
            break;
        case IGV_MENU_FILTRO_MIN_NEAREST:
            interfaz.escena.setFiltroMin(GL_NEAREST);
            break;
        case IGV_MENU_FILTRO_MIN_LINEAR:
            interfaz.escena.setFiltroMin(GL_LINEAR);
            break;

        // ============================================
        // LUCES (ACTIVAR/DESACTIVAR)
        // ============================================
        case IGV_MENU_LUZ_AMBIENTE:
            interfaz.escena.toggleLuzAmbiente();
            break;
        case IGV_MENU_LUZ_DIRECCIONAL:
            interfaz.escena.toggleLuzDireccional();
            break;
        case IGV_MENU_LUZ_PUNTUAL:
            interfaz.escena.toggleLuzPuntual();
            break;
        case IGV_MENU_LUZ_CONO:
            interfaz.escena.toggleLuzCono();
            break;

        // ============================================
        // MOVIMIENTO DE LUCES
        // ============================================
        case IGV_MENU_MOVER_NINGUNA:
            interfaz.luzEnMovimiento = -1;
            break;
        case IGV_MENU_MOVER_PUNTUAL:
            interfaz.luzEnMovimiento = 0;
            break;
        case IGV_MENU_MOVER_CONO:
            interfaz.luzEnMovimiento = 1;
            break;

        // ============================================
        // SOMBREADO
        // ============================================
        case IGV_MENU_SOMBREADO_PLANO:
            glShadeModel(GL_FLAT);
            break;
        case IGV_MENU_SOMBREADO_GOURAUD:
            glShadeModel(GL_SMOOTH);
            break;

        // ============================================
        // ANIMACIÓN
        // ============================================
        case IGV_MENU_ANIMAR_BRAZO:
            interfaz.animacionModelo = !interfaz.animacionModelo;
            break;
        case IGV_MENU_ANIMAR_CAMARA:
            interfaz.animacionCamara = !interfaz.animacionCamara;
            break;
        case IGV_MENU_ANIMAR_TODO:
            interfaz.animacionModelo = true;
            interfaz.animacionCamara = true;
            break;
        case IGV_MENU_DETENER_TODO:
            interfaz.animacionModelo = false;
            interfaz.animacionCamara = false;
            break;

        // ============================================
        // SALIR
        // ============================================
        case IGV_MENU_SALIR:
            exit(0);
            break;
    }

    glutPostRedisplay();
}

void igvInterfaz::create_menu() {
    // ============================================
    // SUBMENÚ: MATERIALES DEL SUELO
    // ============================================
    int submenu_materiales = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Material 1 (Rojo brillante)", IGV_MENU_MATERIAL_1);
    glutAddMenuEntry("Material 2 (Verde mate)", IGV_MENU_MATERIAL_2);
    glutAddMenuEntry("Material 3 (Azul metalico)", IGV_MENU_MATERIAL_3);

    // ============================================
    // SUBMENÚ: TEXTURAS
    // ============================================
    int submenu_texturas = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Activar/Desactivar Texturas", IGV_MENU_TEXTURA_OFF);
    glutAddMenuEntry("Textura 1 (Mapa)", IGV_MENU_TEXTURA_1);
    glutAddMenuEntry("Textura 2", IGV_MENU_TEXTURA_2);
    glutAddMenuEntry("Tablero Ajedrez", IGV_MENU_TEXTURA_AJEDREZ);

    // ============================================
    // SUBMENÚ: FILTROS DE TEXTURA
    // ============================================
    int submenu_filtros = glutCreateMenu(menuHandle);
    glutAddMenuEntry("MAG: GL_NEAREST", IGV_MENU_FILTRO_MAG_NEAREST);
    glutAddMenuEntry("MAG: GL_LINEAR", IGV_MENU_FILTRO_MAG_LINEAR);
    glutAddMenuEntry("MIN: GL_NEAREST", IGV_MENU_FILTRO_MIN_NEAREST);
    glutAddMenuEntry("MIN: GL_LINEAR", IGV_MENU_FILTRO_MIN_LINEAR);

    // ============================================
    // SUBMENÚ: LUCES (ACTIVAR/DESACTIVAR)
    // ============================================
    int submenu_luces = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Toggle Luz Ambiental", IGV_MENU_LUZ_AMBIENTE);
    glutAddMenuEntry("Toggle Luz Direccional", IGV_MENU_LUZ_DIRECCIONAL);
    glutAddMenuEntry("Toggle Luz Puntual", IGV_MENU_LUZ_PUNTUAL);
    glutAddMenuEntry("Toggle Cono de Luz", IGV_MENU_LUZ_CONO);

    // ============================================
    // SUBMENÚ: MOVER LUCES
    // ============================================
    int submenu_mover = glutCreateMenu(menuHandle);
    glutAddMenuEntry("No mover ninguna luz", IGV_MENU_MOVER_NINGUNA);
    glutAddMenuEntry("Mover Luz Puntual", IGV_MENU_MOVER_PUNTUAL);
    glutAddMenuEntry("Mover Cono de Luz", IGV_MENU_MOVER_CONO);

    // ============================================
    // SUBMENÚ: SOMBREADO
    // ============================================
    int submenu_sombreado = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Sombreado Plano (Flat)", IGV_MENU_SOMBREADO_PLANO);
    glutAddMenuEntry("Sombreado Suave (Gouraud)", IGV_MENU_SOMBREADO_GOURAUD);

    // ============================================
    // SUBMENÚ: ANIMACIÓN
    // ============================================
    int submenu_animacion = glutCreateMenu(menuHandle);
    glutAddMenuEntry("Animar Brazo (A)", IGV_MENU_ANIMAR_BRAZO);
    glutAddMenuEntry("Orbitar Camara (G)", IGV_MENU_ANIMAR_CAMARA);
    glutAddMenuEntry("Activar Todo", IGV_MENU_ANIMAR_TODO);
    glutAddMenuEntry("Detener Todo", IGV_MENU_DETENER_TODO);

    // ============================================
    // MENÚ PRINCIPAL
    // ============================================
    int menu_principal = glutCreateMenu(menuHandle);
    glutAddSubMenu("Materiales Suelo", submenu_materiales);
    glutAddSubMenu("Texturas", submenu_texturas);
    glutAddSubMenu("Filtros Textura", submenu_filtros);
    glutAddSubMenu("Luces", submenu_luces);
    glutAddSubMenu("Mover Luces", submenu_mover);
    glutAddSubMenu("Sombreado", submenu_sombreado);
    glutAddSubMenu("Animacion", submenu_animacion);
    glutAddMenuEntry("Salir", IGV_MENU_SALIR);

    // Asociar menú al botón derecho del ratón
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}