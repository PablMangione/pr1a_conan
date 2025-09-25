#include <cstdlib>

#include "igvInterfaz.h"

// Aplicación del patrón Singleton
igvInterfaz* igvInterfaz::_instancia = nullptr;

// Métodos constructores -----------------------------------

/**
 * Constructor por defecto
 */
igvInterfaz::igvInterfaz(): menuSelection(escena.EscenaA)
{}

// Métodos públicos ----------------------------------------

/**
 * Método para acceder al objeto único de la clase, en aplicación del patrón de
 * diseño Singleton
 * @return Una referencia al objeto único de la clase
 */
igvInterfaz& igvInterfaz::getInstancia ()
{  if ( !_instancia )
   {  _instancia = new igvInterfaz;
   }

   return *_instancia;
}

/**
 * Inicializa todos los parámetros para crear una ventana de visualización
 * @param argc Número de parámetros por línea de comandos al ejecutar la
 *             aplicación
 * @param argv Parámetros por línea de comandos al ejecutar la aplicación
 * @param _ancho_ventana Ancho inicial de la ventana de visualización
 * @param _alto_ventana Alto inicial de la ventana de visualización
 * @param _pos_X Coordenada X de la posición inicial de la ventana de
 *               visualización
 * @param _pos_Y Coordenada Y de la posición inicial de la ventana de
 *               visualización
 * @param _titulo Título de la ventana de visualización
 * @pre Se asume que todos los parámetros tienen valores válidos
 * @post Cambia el alto y ancho de ventana almacenado en el objeto
 */
void igvInterfaz::configura_entorno ( int argc, char** argv
                                      , int _ancho_ventana, int _alto_ventana
                                      , int _pos_X, int _pos_Y
                                      , std::string _titulo )
{  // inicialización de los atributos de la interfaz
   ancho_ventana = _ancho_ventana;
   alto_ventana = _alto_ventana;

   // inicialización de la ventana de visualización
   glutInit ( &argc, argv );
   glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
   glutInitWindowSize ( _ancho_ventana, _alto_ventana );
   glutInitWindowPosition ( _pos_X, _pos_Y );
   glutCreateWindow ( _titulo.c_str () );

   create_menu ();

   glEnable ( GL_DEPTH_TEST ); // activa el ocultamiento de superficies por z-buffer
   glClearColor ( 1.0, 1.0, 1.0, 0.0 ); // establece el color de fondo de la ventana

   glEnable ( GL_LIGHTING ); // activa la iluminación de la escena
   glEnable ( GL_NORMALIZE ); // normaliza los vectores normales para cálculo de iluminación
}

/**
 * Crea un menú asociado al botón derecho del ratón
 */
void igvInterfaz::create_menu ()
{  int menu_id = glutCreateMenu ( menuHandle );
   glutAddMenuEntry ( _instancia->escena.Nombre_EscenaA
                      , _instancia->escena.EscenaA );
   glutAddMenuEntry ( _instancia->escena.Nombre_EscenaB
                      , _instancia->escena.EscenaB );
   glutAddMenuEntry ( _instancia->escena.Nombre_EscenaC
                      , _instancia->escena.EscenaC );

   glutAttachMenu ( GLUT_RIGHT_BUTTON );
}

/**
 * Método para visualizar la escena y esperar a eventos sobre la interfaz
 */
void igvInterfaz::inicia_bucle_visualizacion ()
{  glutMainLoop (); // inicia el bucle de visualización de GLUT
}

/**
 * Método para control de eventos del teclado
 * @param key Código de la tecla pulsada
 * @param x Coordenada X de la posición del cursor del ratón en el momento del
 *          evento de teclado
 * @param y Coordenada Y de la posición del cursor del ratón en el momento del
 *          evento de teclado
 * @pre Se asume que todos los parámetros tienen valores válidos
 * @post La escena puede cambiar dependiendo de la tecla pulsada
 */
void igvInterfaz::keyboardFunc ( unsigned char key, int x, int y )
{  switch ( key )
   {  case 'e': // activa/desactiva la visualización de los ejes
      case 'E':
         _instancia->escena.set_ejes ( !_instancia->escena.get_ejes () );
         break;
      case 27: // tecla de escape para SALIR
         exit ( 1 );
         break;
   }
   glutPostRedisplay (); // renueva el contenido de la ventana de vision
}

/**
 * Método que define la cámara de visión y el viewport. Se llama automáticamente
 * cuando se cambia el tamaño de la ventana.
 * @param w Nuevo ancho de la ventana
 * @param h Nuevo alto de la ventana
 * @pre Se asume que todos los parámetros tienen valores válidos
 */
void igvInterfaz::reshapeFunc ( int w, int h )
{  // dimensiona el viewport al nuevo ancho y alto de la ventana
   glViewport ( 0, 0, (GLsizei) w, (GLsizei) h );

   // guardamos valores nuevos de la ventana de visualizacion
   _instancia->set_ancho_ventana ( w );
   _instancia->set_alto_ventana ( h );

   // establece el tipo de proyeccion a utilizar
   glMatrixMode ( GL_PROJECTION );
   glLoadIdentity ();

   glOrtho ( -1 * 5, 1 * 5, -1 * 5, 1 * 5, -1 * 5, 200 );

   // se define la camara de vision
   glMatrixMode ( GL_MODELVIEW );
   glLoadIdentity ();

   gluLookAt ( 1.5, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ); // vista en perspectiva
   //gluLookAt(1.5,0,0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // vista en planta desde el eje X positivo
}

/**
 * Método para visualizar la escena
 */
void igvInterfaz::displayFunc ()
{  _instancia->escena.visualizar ( _instancia->menuSelection );
}

/**
 * Método para gestionar la selección de opciones de menú
 * @param value Nueva opción seleccionada
 * @pre Se asume que el valor del parámetro es correcto
 * @post Se almacena en el objeto la opción seleccionada
 */
void igvInterfaz::menuHandle ( int value )
{  _instancia->menuSelection = value;
   glutPostRedisplay (); // renew the content of the window
}

/**
 * Método para inicializar los callbacks
 */
void igvInterfaz::inicializa_callbacks()
{  glutKeyboardFunc ( keyboardFunc );
   glutReshapeFunc ( reshapeFunc );
   glutDisplayFunc ( displayFunc );
}

/**
 * Método para consultar el ancho de la ventana de visualización
 * @return El valor almacenado como ancho de la ventana de visualización
 */
int igvInterfaz::get_ancho_ventana ()
{  return ancho_ventana;
}

/**
 * Método para consultar el alto de la ventana de visualización
 * @return El valor almacenado como alto de la ventana de visualización
 */
int igvInterfaz::get_alto_ventana ()
{  return alto_ventana;
}

/**
 * Método para cambiar el ancho de la ventana de visualización
 * @param _ancho_ventana Nuevo valor para el ancho de la ventana de visualización
 * @pre Se asume que el parámetro tiene un valor válido
 * @post El ancho de ventana almacenado en la aplicación cambia al nuevo valor
 */
void igvInterfaz::set_ancho_ventana ( int _ancho_ventana )
{  ancho_ventana = _ancho_ventana;
}

/**
 * Método para cambiar el alto de la ventana de visualización
 * @param _alto_ventana Nuevo valor para el alto de la ventana de visualización
 * @pre Se asume que el parámetro tiene un valor válido
 * @post El alto de ventana almacenado en la aplicación cambia al nuevo valor
 */
void igvInterfaz::set_alto_ventana ( int _alto_ventana )
{  alto_ventana = _alto_ventana;
}
