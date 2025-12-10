#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else
#include <GL/glut.h>
#endif   // defined(__APPLE__) && defined(__MACH__)

#include <string>
#include "igvEscena3D.h"
#include "igvCamara.h"

// ============================================
// CONSTANTES DE MENÚ
// ============================================

// Menú principal
enum MenuPrincipal {
    IGV_MENU_SALIR = 0
};

// Submenú de materiales del suelo
enum MenuMateriales {
    IGV_MENU_MATERIAL_1 = 10,
    IGV_MENU_MATERIAL_2,
    IGV_MENU_MATERIAL_3
};

// Submenú de texturas
enum MenuTexturas {
    IGV_MENU_TEXTURA_OFF = 20,
    IGV_MENU_TEXTURA_1,
    IGV_MENU_TEXTURA_2,
    IGV_MENU_TEXTURA_AJEDREZ
};

// Submenú de filtros de textura
enum MenuFiltros {
    IGV_MENU_FILTRO_MAG_NEAREST = 30,
    IGV_MENU_FILTRO_MAG_LINEAR,
    IGV_MENU_FILTRO_MIN_NEAREST,
    IGV_MENU_FILTRO_MIN_LINEAR
};

// Submenú de luces (activar/desactivar)
enum MenuLuces {
    IGV_MENU_LUZ_AMBIENTE = 40,
    IGV_MENU_LUZ_DIRECCIONAL,
    IGV_MENU_LUZ_PUNTUAL,
    IGV_MENU_LUZ_CONO
};

// Submenú de movimiento de luces
enum MenuMoverLuces {
    IGV_MENU_MOVER_NINGUNA = 50,
    IGV_MENU_MOVER_PUNTUAL,
    IGV_MENU_MOVER_CONO
};

// Submenú de sombreado (existente)
enum MenuSombreado {
    IGV_MENU_SOMBREADO_PLANO = 60,
    IGV_MENU_SOMBREADO_GOURAUD
};

// Submenú de animación (existente)
enum MenuAnimacion {
    IGV_MENU_ANIMAR_BRAZO = 70,
    IGV_MENU_ANIMAR_CAMARA,
    IGV_MENU_ANIMAR_TODO,
    IGV_MENU_DETENER_TODO
};

// Submenú de control (existente)
enum MenuControl {
    IGV_MENU_MODO_TECLADO = 80,
    IGV_MENU_MODO_RATON
};

class igvInterfaz {
public:
    static igvInterfaz &getInstancia();

    ~igvInterfaz() = default;

    static void keyboardFunc(unsigned char key, int x, int y);

    static void specialFunc(int key, int x, int y);

    static void reshapeFunc(int w, int h);

    static void timerFunc(int value);

    static void displayFunc();

    static void mouseFunc(int button, int state, int x, int y);

    static void motionFunc(int x, int y);

    void configura_entorno(int argc, char **argv
                           , int _ancho_ventana, int _alto_ventana
                           , int _pos_X, int _pos_Y
                           , std::string _titulo
    );

    void create_menu();

    void inicializa_callbacks();

    void inicia_bucle_visualizacion();

    int get_ancho_ventana();

    int get_alto_ventana();

    void set_ancho_ventana(int _ancho_ventana);

    void set_alto_ventana(int _alto_ventana);

    bool getModoMultiViewport() const { return modoMultiViewport; }

    void cambiaModoMultiViewPort() { modoMultiViewport = !modoMultiViewport; }

private:
    int ancho_ventana = 0;
    int alto_ventana = 0;
    igvCamara camara;
    bool modoMultiViewport = false;

    bool animacionModelo = false;

    bool animacionCamara = false;

    int timerAnimacion = 16;

    bool arrastrando = false;
    int mouseX_anterior = 0;
    int mouseY_anterior = 0;

    igvEscena3D escena;
    static igvInterfaz *_instancia;

    igvInterfaz();
};

#endif   // __IGVINTERFAZ