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