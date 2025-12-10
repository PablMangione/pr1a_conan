# Guía de Implementación - Práctica 3: Iluminación y Texturas

## Resumen de Requisitos

| Requisito | Estado | Descripción |
|-----------|--------|-------------|
| Suelo (quad) | ❌ Pendiente | Quad como suelo con materiales y texturas |
| 3 Materiales | ❌ Pendiente | Materiales predefinidos intercambiables |
| 3 Texturas | ❌ Pendiente | Incluyendo tablero de ajedrez |
| Filtros textura | ❌ Pendiente | MAG/MIN con NEAREST/LINEAR |
| Luz ambiental | ❌ Pendiente | Luz global de escena |
| Luz direccional | ❌ Pendiente | Luz tipo sol |
| Luz puntual | ⚠️ Parcial | Existe una fija, falta control |
| Cono de luz | ❌ Pendiente | Spotlight |
| Menú GLUT | ❌ Pendiente | `create_menu()` vacío |
| Movimiento luces | ❌ Pendiente | Control interactivo X,Y,Z |

---

## 1. Constantes de Menú

### Archivo: `igvInterfaz.h`

Añadir después de los includes y antes de la clase:

```cpp
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
```

---

## 2. Atributos de Estado en igvInterfaz

### Archivo: `igvInterfaz.h`

Añadir en la sección `private` de la clase:

```cpp
private:
    // ... atributos existentes ...

    // ============================================
    // NUEVOS ATRIBUTOS PARA PR3
    // ============================================

    // Control de qué luz se está moviendo
    // -1 = ninguna, 0 = puntual, 1 = cono
    int luzEnMovimiento = -1;
```

---

## 3. Atributos de Estado en igvEscena3D

### Archivo: `igvEscena3D.h`

Añadir includes necesarios:

```cpp
#include "igvMaterial.h"
#include "igvTextura.h"
#include "igvFuenteLuz.h"
```

Añadir en la sección `private` de la clase:

```cpp
private:
    // ... atributos existentes ...

    // ============================================
    // SUELO
    // ============================================
    int materialActual = 0;          // Índice del material actual (0, 1, 2)
    igvMaterial materialesSuelo[3];  // 3 materiales predefinidos

    // ============================================
    // TEXTURAS
    // ============================================
    bool texturasActivas = false;    // Si se aplican texturas o no
    int texturaActual = 0;           // Índice de textura actual (0, 1, 2)
    igvTextura* texturas[3];         // 3 texturas (incluyendo ajedrez)
    GLenum filtroMag = GL_LINEAR;    // Filtro de magnificación
    GLenum filtroMin = GL_LINEAR;    // Filtro de minificación

    // ============================================
    // LUCES
    // ============================================
    igvFuenteLuz luzAmbiente;        // Luz ambiental global
    igvFuenteLuz luzDireccional;     // Luz direccional (tipo sol)
    igvFuenteLuz luzPuntual;         // Luz puntual (bombilla)
    igvFuenteLuz luzCono;            // Cono de luz (spotlight)

    bool luzAmbienteActiva = true;
    bool luzDireccionalActiva = true;
    bool luzPuntualActiva = true;
    bool luzConoActiva = true;
```

Añadir en la sección `public`:

```cpp
public:
    // ... métodos existentes ...

    // ============================================
    // MÉTODOS PARA SUELO Y MATERIALES
    // ============================================
    void setMaterialSuelo(int indice);
    int getMaterialSuelo() const { return materialActual; }

    // ============================================
    // MÉTODOS PARA TEXTURAS
    // ============================================
    void setTexturaSuelo(int indice);
    void toggleTexturas();
    bool getTexturasActivas() const { return texturasActivas; }
    void setFiltroMag(GLenum filtro);
    void setFiltroMin(GLenum filtro);

    // ============================================
    // MÉTODOS PARA LUCES
    // ============================================
    void toggleLuzAmbiente();
    void toggleLuzDireccional();
    void toggleLuzPuntual();
    void toggleLuzCono();

    void moverLuzPuntual(float dx, float dy, float dz);
    void moverLuzCono(float dx, float dy, float dz);

    igvFuenteLuz& getLuzPuntual() { return luzPuntual; }
    igvFuenteLuz& getLuzCono() { return luzCono; }
```

---

## 4. Implementación del Constructor de igvEscena3D

### Archivo: `igvEscena3D.cpp`

Modificar/añadir en el constructor:

```cpp
igvEscena3D::igvEscena3D() {
    // ... código existente ...

    // ============================================
    // INICIALIZACIÓN DE MATERIALES DEL SUELO
    // ============================================

    // Material 1: Rojo brillante
    materialesSuelo[0].set(
        igvColor(0.2, 0.0, 0.0),    // Ka - ambiental
        igvColor(0.8, 0.1, 0.1),    // Kd - difuso
        igvColor(1.0, 1.0, 1.0),    // Ks - especular
        50.0                         // Ns - exponente Phong
    );

    // Material 2: Verde mate
    materialesSuelo[1].set(
        igvColor(0.0, 0.2, 0.0),    // Ka
        igvColor(0.1, 0.6, 0.1),    // Kd
        igvColor(0.2, 0.2, 0.2),    // Ks
        10.0                         // Ns
    );

    // Material 3: Azul metálico
    materialesSuelo[2].set(
        igvColor(0.0, 0.0, 0.2),    // Ka
        igvColor(0.1, 0.1, 0.8),    // Kd
        igvColor(1.0, 1.0, 1.0),    // Ks
        100.0                        // Ns
    );

    // ============================================
    // INICIALIZACIÓN DE TEXTURAS
    // ============================================

    // Textura 1: Desde archivo
    texturas[0] = new igvTextura("mapa.png");

    // Textura 2: Otra imagen (crear o usar existente)
    texturas[1] = new igvTextura("textura2.png");

    // Textura 3: Tablero de ajedrez (procedural)
    texturas[2] = igvTextura::crearTableroAjedrez(256, 8);

    // ============================================
    // INICIALIZACIÓN DE LUCES
    // ============================================

    // Luz ambiental global (usando GL_LIGHT0)
    // Nota: Para luz ambiental global usar glLightModelfv
    luzAmbiente = igvFuenteLuz(
        GL_LIGHT0,
        igvPunto3D(0, 0, 0),           // Posición (no relevante para ambiental)
        igvColor(0.3, 0.3, 0.3),       // Ambiental
        igvColor(0.0, 0.0, 0.0),       // Difuso (0 para luz ambiental pura)
        igvColor(0.0, 0.0, 0.0),       // Especular
        1.0, 0.0, 0.0                  // Atenuación
    );

    // Luz direccional (GL_LIGHT1) - posición con w=0
    luzDireccional = igvFuenteLuz(
        GL_LIGHT1,
        igvPunto3D(-1, -1, -1),        // Dirección (w=0 para direccional)
        igvColor(0.1, 0.1, 0.1),       // Ambiental
        igvColor(0.7, 0.7, 0.7),       // Difuso
        igvColor(0.5, 0.5, 0.5),       // Especular
        1.0, 0.0, 0.0                  // Atenuación
    );

    // Luz puntual (GL_LIGHT2)
    luzPuntual = igvFuenteLuz(
        GL_LIGHT2,
        igvPunto3D(5, 5, 5),           // Posición
        igvColor(0.1, 0.1, 0.1),       // Ambiental
        igvColor(0.8, 0.8, 0.6),       // Difuso (amarillento)
        igvColor(1.0, 1.0, 1.0),       // Especular
        1.0, 0.01, 0.001               // Atenuación
    );

    // Cono de luz / Spotlight (GL_LIGHT3)
    luzCono = igvFuenteLuz(
        GL_LIGHT3,
        igvPunto3D(0, 8, 0),           // Posición
        igvColor(0.0, 0.0, 0.0),       // Ambiental
        igvColor(1.0, 1.0, 1.0),       // Difuso
        igvColor(1.0, 1.0, 1.0),       // Especular
        1.0, 0.0, 0.0,                 // Atenuación
        igvPunto3D(0, -1, 0),          // Dirección del foco (hacia abajo)
        30.0,                          // Ángulo de apertura (grados)
        15.0                           // Exponente del foco
    );

    // Encender las luces por defecto
    luzAmbiente.encender();
    luzDireccional.encender();
    luzPuntual.encender();
    luzCono.encender();
}
```

---

## 5. Método para Dibujar el Suelo

### Archivo: `igvEscena3D.cpp`

Añadir nuevo método:

```cpp
void igvEscena3D::dibujarSuelo() {
    glPushMatrix();

    // Aplicar material actual
    materialesSuelo[materialActual].aplicar();

    // Aplicar textura si está activa
    if (texturasActivas && texturas[texturaActual] != nullptr) {
        texturas[texturaActual]->setFiltroMag(filtroMag);
        texturas[texturaActual]->setFiltroMin(filtroMin);
        texturas[texturaActual]->aplicar();
    }

    // Dibujar quad (suelo)
    float tamano = 10.0f;
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);  // Normal hacia arriba

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-tamano, 0.0f, -tamano);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(tamano, 0.0f, -tamano);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(tamano, 0.0f, tamano);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-tamano, 0.0f, tamano);
    glEnd();

    // Desactivar textura si estaba activa
    if (texturasActivas && texturas[texturaActual] != nullptr) {
        texturas[texturaActual]->desactivar();
    }

    glPopMatrix();
}
```

Declarar en `igvEscena3D.h` (sección private):

```cpp
private:
    void dibujarSuelo();
```

---

## 6. Modificar el Método visualizar()

### Archivo: `igvEscena3D.cpp`

Modificar el método `visualizar()`:

```cpp
void igvEscena3D::visualizar() {
    // ============================================
    // CONFIGURACIÓN DE ILUMINACIÓN
    // ============================================

    // Luz ambiental global de la escena
    GLfloat luzAmbienteGlobal[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbienteGlobal);

    // Aplicar cada luz si está activa
    if (luzAmbienteActiva) {
        luzAmbiente.encender();
    } else {
        luzAmbiente.apagar();
    }
    luzAmbiente.aplicar();

    if (luzDireccionalActiva) {
        luzDireccional.encender();
    } else {
        luzDireccional.apagar();
    }
    luzDireccional.aplicar();

    if (luzPuntualActiva) {
        luzPuntual.encender();
    } else {
        luzPuntual.apagar();
    }
    luzPuntual.aplicar();

    if (luzConoActiva) {
        luzCono.encender();
    } else {
        luzCono.apagar();
    }
    luzCono.aplicar();

    // ============================================
    // DIBUJAR ESCENA
    // ============================================

    // Dibujar ejes si están activos
    if (ejes) {
        pintar_ejes();
    }

    // Dibujar el suelo
    dibujarSuelo();

    // Dibujar el modelo articulado
    modelo.visualizar();
}
```

---

## 7. Implementación de Métodos de Control

### Archivo: `igvEscena3D.cpp`

Añadir implementaciones:

```cpp
// ============================================
// MÉTODOS DE MATERIALES
// ============================================

void igvEscena3D::setMaterialSuelo(int indice) {
    if (indice >= 0 && indice < 3) {
        materialActual = indice;
    }
}

// ============================================
// MÉTODOS DE TEXTURAS
// ============================================

void igvEscena3D::setTexturaSuelo(int indice) {
    if (indice >= 0 && indice < 3) {
        texturaActual = indice;
    }
}

void igvEscena3D::toggleTexturas() {
    texturasActivas = !texturasActivas;
}

void igvEscena3D::setFiltroMag(GLenum filtro) {
    filtroMag = filtro;
}

void igvEscena3D::setFiltroMin(GLenum filtro) {
    filtroMin = filtro;
}

// ============================================
// MÉTODOS DE LUCES
// ============================================

void igvEscena3D::toggleLuzAmbiente() {
    luzAmbienteActiva = !luzAmbienteActiva;
}

void igvEscena3D::toggleLuzDireccional() {
    luzDireccionalActiva = !luzDireccionalActiva;
}

void igvEscena3D::toggleLuzPuntual() {
    luzPuntualActiva = !luzPuntualActiva;
}

void igvEscena3D::toggleLuzCono() {
    luzConoActiva = !luzConoActiva;
}

void igvEscena3D::moverLuzPuntual(float dx, float dy, float dz) {
    luzPuntual.mover(dx, dy, dz);
}

void igvEscena3D::moverLuzCono(float dx, float dy, float dz) {
    luzCono.mover(dx, dy, dz);
}
```

---

## 8. Callback del Menú (menuHandle)

### Archivo: `igvInterfaz.cpp`

Añadir función estática (antes de create_menu o donde estén los otros callbacks):

```cpp
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
```

Declarar en `igvInterfaz.h` (sección public, junto a otros callbacks estáticos):

```cpp
public:
    static void menuHandle(int opcion);
```

---

## 9. Implementación de create_menu()

### Archivo: `igvInterfaz.cpp`

Implementar el método:

```cpp
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
```

---

## 10. Control de Movimiento de Luces por Teclado

### Archivo: `igvInterfaz.cpp`

Modificar `keyboardFunc()` para añadir control de luces:

```cpp
void igvInterfaz::keyboardFunc(unsigned char key, int x, int y) {
    igvInterfaz& interfaz = igvInterfaz::getInstancia();

    switch (key) {
        // ... casos existentes ...

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
    }

    glutPostRedisplay();
}
```

---

## 11. Método mover() en igvFuenteLuz (si no existe)

### Archivo: `igvFuenteLuz.cpp`

Verificar que existe o añadir:

```cpp
void igvFuenteLuz::mover(float dx, float dy, float dz) {
    posicion[X] += dx;
    posicion[Y] += dy;
    posicion[Z] += dz;
}
```

---

## 12. Inicialización del Menú

### Archivo: `igvInterfaz.cpp`

En el método `configura_entorno()`, asegurar que se llama a `create_menu()`:

```cpp
void igvInterfaz::configura_entorno(...) {
    // ... código existente de inicialización GLUT ...

    // Crear el menú contextual
    create_menu();

    // ... resto del código ...
}
```

---

## 13. Luz Direccional - Nota Importante

### Archivo: `igvFuenteLuz.cpp`

Para que una luz sea **direccional** (tipo sol), el componente `w` de la posición debe ser `0`:

```cpp
// En aplicar(), para luz direccional:
void igvFuenteLuz::aplicar() {
    if (encendida) {
        glEnable(idLuz);

        // Para luz direccional, usar w=0
        // Para luz puntual, usar w=1
        float pos[4];
        pos[0] = posicion[X];
        pos[1] = posicion[Y];
        pos[2] = posicion[Z];
        pos[3] = esLuzDireccional ? 0.0f : 1.0f;  // Añadir flag si es necesario

        glLightfv(idLuz, GL_POSITION, pos);
        // ... resto de parámetros ...
    }
}
```

Alternativa: Crear constructor específico para luz direccional o añadir un flag `bool esDireccional`.

---

## Resumen de Archivos a Modificar

| Archivo | Cambios |
|---------|---------|
| `igvInterfaz.h` | Constantes de menú, atributo `luzEnMovimiento`, declaración `menuHandle()` |
| `igvInterfaz.cpp` | Implementar `create_menu()`, `menuHandle()`, modificar `keyboardFunc()` |
| `igvEscena3D.h` | Includes, atributos de materiales/texturas/luces, métodos de control |
| `igvEscena3D.cpp` | Constructor con inicialización, `dibujarSuelo()`, `visualizar()` modificado, métodos toggle/set |
| `igvFuenteLuz.cpp` | Método `mover()` si no existe, considerar flag para luz direccional |

---

## Estructura del Menú Final

```
[Click Derecho]
├── Materiales Suelo
│   ├── Material 1 (Rojo brillante)
│   ├── Material 2 (Verde mate)
│   └── Material 3 (Azul metálico)
├── Texturas
│   ├── Activar/Desactivar Texturas
│   ├── Textura 1 (Mapa)
│   ├── Textura 2
│   └── Tablero Ajedrez
├── Filtros Textura
│   ├── MAG: GL_NEAREST
│   ├── MAG: GL_LINEAR
│   ├── MIN: GL_NEAREST
│   └── MIN: GL_LINEAR
├── Luces
│   ├── Toggle Luz Ambiental
│   ├── Toggle Luz Direccional
│   ├── Toggle Luz Puntual
│   └── Toggle Cono de Luz
├── Mover Luces
│   ├── No mover ninguna luz
│   ├── Mover Luz Puntual
│   └── Mover Cono de Luz
├── Sombreado
│   ├── Sombreado Plano (Flat)
│   └── Sombreado Suave (Gouraud)
├── Animación
│   ├── Animar Brazo (A)
│   ├── Orbitar Cámara (G)
│   ├── Activar Todo
│   └── Detener Todo
└── Salir
```

---

## Controles de Teclado para Mover Luces

| Tecla | Acción |
|-------|--------|
| `x` | Mover luz seleccionada en -X |
| `X` | Mover luz seleccionada en +X |
| `y` | Mover luz seleccionada en -Y |
| `Y` | Mover luz seleccionada en +Y |
| `z` | Mover luz seleccionada en -Z |
| `Z` | Mover luz seleccionada en +Z |

Nota: Primero seleccionar qué luz mover desde el menú "Mover Luces".
