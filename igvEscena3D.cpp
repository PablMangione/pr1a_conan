#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// M�todos constructores -----------------------------------

// M�todos p�blicos ----------------------------------------

/**
 * M�todo para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes ()
{  GLfloat rojo[] = { 1,0,0,1.0 };
   GLfloat verde[] = { 0,1,0,1.0 };
   GLfloat azul[] = { 0,0,1,1.0 };

   glBegin(GL_LINES);
   glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
   glVertex3f(1000, 0, 0);
   glVertex3f(-1000, 0, 0);

   glMaterialfv(GL_FRONT, GL_EMISSION, verde);
   glVertex3f(0, 1000, 0);
   glVertex3f(0, -1000, 0);

   glMaterialfv(GL_FRONT, GL_EMISSION, azul);
   glVertex3f(0, 0, 1000);
   glVertex3f(0, 0, -1000);
   glEnd();
}

/**
 * M�todo con las llamadas OpenGL para visualizar la escena
 * @param escena Identificador del tipo de escena a dibujar
 * @pre Se asume que el valor del par�metro es correcto
 */
void igvEscena3D::visualizar ( int escena )
{  // borra la ventana y el Z-buffer
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   //Luces
   GLfloat light0[] = { 10, 8, 9, 1 }; // point light source
   glLightfv ( GL_LIGHT0, GL_POSITION, light0 );
   glEnable ( GL_LIGHT0 );

   glPushMatrix (); // guarda la matriz de modelado

   // se pintan los ejes
   if ( ejes )
   {  pintar_ejes ();
   }

   // Escena seleccionada a trav�s del men� (clic bot�n derecho)
   if ( escena == EscenaA )
   {  renderEscenaA ();
   }
   else
   {  if ( escena == EscenaB )
      {  renderEscenaB ();
      }
      else
      {  if ( escena == EscenaC )
         {  renderEscenaC ();
         }
      }
   }

   glPopMatrix (); // restaura la matriz de modelado
   glutSwapBuffers (); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvEscena3D::renderModelo() {
   GLfloat color_cubo[] = { 0, 0.25, 0 };
   GLfloat color_cilindro[] = { 0, 0, 0.5 };

   glMaterialfv(GL_FRONT, GL_EMISSION, color_cubo);
   glPushMatrix();
      glutSolidCube(1);
   glPopMatrix();

   glMaterialfv(GL_FRONT, GL_EMISSION, color_cilindro);
   GLUquadric* quad = gluNewQuadric();

   glPushMatrix();
      glTranslatef(0, 0.75, 0);
      glRotatef(90, 1, 0, 0);
      gluCylinder(quad, 0.2, 0.2, 0.5, 20, 20);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0, -0.75, 0);
      glRotatef(90, 1, 0, 0);
      gluCylinder(quad, 0.2, 0.2, 0.5, 20, 20);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(0.75, 0, 0);
      glRotatef(90, 0, 1, 0);
      gluCylinder(quad, 0.2, 0.2, 0.5, 20, 20);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-0.75, 0, 0);
      glRotatef(90, 0, 1, 0);
      gluCylinder(quad, 0.2, 0.2, 0.5, 20, 20);
   glPopMatrix();

   gluDeleteQuadric(quad);
}


/**
 * Pinta la escena A llamando a las funciones de OpenGL
 */
void igvEscena3D::renderEscenaA ()
{  GLfloat color_pieza[] = { 0, 0.25, 0 };

   glPushMatrix();
      renderModelo();
   glPopMatrix();
}

/**
 * Pinta la escena B llamando a las funciones de OpenGL
 */
void igvEscena3D::renderEscenaB ()
{  GLfloat color_pieza[] = { 0, 0, 0.5 };

   for (int i = 0; i < num_instacias; i++) {
      glPushMatrix();
      glTranslatef(0, i * 1.5, 0);
      renderModelo();
      glPopMatrix();
   }
}

/**
 * Pinta la escena C llamando a las funciones de OpenGL
 */
void igvEscena3D::renderEscenaC ()
{  GLfloat color_pieza[] = { 0.5, 0, 0 };

   for (int x = 0; x < num_pilas_x; x++) {
      for (int z = 0; z < num_pilas_z; z++) {
         glPushMatrix();
         // Centrar las pilas en el origen
         glTranslatef(x * 2.5 - (num_pilas_x - 1) * 1.25,
                     0,
                     z * 2.5 - (num_pilas_z - 1) * 1.25);

         // Dibujar pila vertical
         for (int y = 0; y < num_instacias; y++) {
            glPushMatrix();
            glTranslatef(0, y * 1.5, 0);
            renderModelo();
            glPopMatrix();
         }
         glPopMatrix();
      }
   }
}

/**
 * M�todo para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes ()
{  return ejes;
}

/**
 * M�todo para activar o desactivar el dibujado de los ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como par�metro
 */
void igvEscena3D::set_ejes ( bool _ejes )
{  ejes = _ejes;
}




