#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif   // defined(__APPLE__) && defined(__MACH__)

/**
 * Los objetos de esta clase representan escenas 3D para su visualización
 */
class igvEscena3D
{  public:
      const int EscenaA = 1;   ///< Identificador interno de la escena A
      const int EscenaB = 2;   ///< Identificador interno de la escena B
      const int EscenaC = 3;   ///< Identificador interno de la escena C

      const char *Nombre_EscenaA = "Escena A";   ///< Etiqueta de la escena A
      const char *Nombre_EscenaB = "Escena B";   ///< Etiqueta de la escena B
      const char* Nombre_EscenaC = "Escena C";   ///< Etiqueta de la escena C

   private:
      // Atributos
      bool ejes  = true;   ///< Indica si hay que dibujar los ejes coordenados o no
      // TODO: Declarar atributos para manejar las transformaciones para las escenas B y C

   public:
      // Constructores por defecto y destructor
      /// Constructor por defecto
      igvEscena3D() = default;
      /// Destructor
      ~igvEscena3D() = default;

      // Métodos
      // método con las llamadas OpenGL para visualizar la escena
      void visualizar ( int escena );

      bool get_ejes();
      void set_ejes(bool _ejes);

   private:
      void renderEscenaA();
      void renderEscenaB();
      void renderEscenaC();
      void pintar_ejes ();
};

#endif   // __IGVESCENA3D
