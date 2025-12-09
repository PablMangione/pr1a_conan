# Planificación Práctica 3 - Iluminación y Texturas
## Análisis de Reutilización del Código del Ejemplo

---

## 📁 RESUMEN DE ARCHIVOS

### Archivos del Ejemplo que se COPIAN DIRECTAMENTE (sin modificaciones)

| Archivo | Descripción | Acción |
|---------|-------------|--------|
| `igvColor.h` | Clase para colores RGBA | ✅ Copiar sin cambios |
| `igvColor.cpp` | Implementación de igvColor | ✅ Copiar sin cambios |
| `igvFuenteLuz.h` | Clase para fuentes de luz | ✅ Copiar sin cambios |
| `igvFuenteLuz.cpp` | Implementación de igvFuenteLuz | ✅ Copiar sin cambios |
| `igvMaterial.h` | Clase para materiales | ⚠️ Copiar con pequeñas modificaciones |
| `igvMaterial.cpp` | Implementación de igvMaterial | ✅ Copiar sin cambios |
| `igvTextura.h` | Clase para texturas | ⚠️ Copiar con modificaciones |
| `igvTextura.cpp` | Implementación de igvTextura | ⚠️ Copiar con modificaciones |
| `lodepng.h` | Librería para cargar PNG | ✅ Copiar sin cambios |
| `lodepng.cpp` | Implementación de lodepng | ✅ Copiar sin cambios |
| `mapa.png` | Textura de ejemplo | ✅ Copiar + añadir más texturas |

### Archivos del Proyecto Original que se MODIFICAN

| Archivo | Descripción | Acción |
|---------|-------------|--------|
| `igvPunto3D.h` | Clase para puntos 3D | 🔄 Añadir método `cloneToFloatArray()` |
| `igvPunto3D.cpp` | Implementación | 🔄 Añadir método `cloneToFloatArray()` |
| `igvEscena3D.h` | Clase escena | 🔄 Modificar significativamente |
| `igvEscena3D.cpp` | Implementación escena | 🔄 Modificar significativamente |
| `igvInterfaz.h` | Clase interfaz | 🔄 Añadir menús y callbacks |
| `igvInterfaz.cpp` | Implementación interfaz | 🔄 Añadir menús y callbacks |
| `CMakeLists.txt` | Configuración CMake | 🔄 Añadir nuevos archivos |

### Archivos que se MANTIENEN del Proyecto Original (Práctica 2)

| Archivo | Descripción |
|---------|-------------|
| `pr1a.cpp` | Main del programa |
| `igvCamara.h/cpp` | Clase cámara (mantener funcionalidad P2) |
| `Mallas/*` | Todas las mallas (modelo articulado, cilindro, esfera, etc.) |

---

## 📋 DETALLE DE MODIFICACIONES POR ARCHIVO

---

### 1. `igvColor.h` y `igvColor.cpp`
**Acción: ✅ COPIAR SIN CAMBIOS**

Copiar directamente desde `/home/claude/Pr3_ejemplo/Pr3/pr3_conan_resuelta/`

El archivo ya incluye todo lo necesario:
- Enum `cColor` para R, G, B, A
- Constructor RGB y RGBA
- Operadores de acceso `[]`
- Método `aplicar()` para glColor4dv
- Método `cloneToFloatArray()` para conversión a float*

---

### 2. `igvFuenteLuz.h` y `igvFuenteLuz.cpp`
**Acción: ✅ COPIAR SIN CAMBIOS**

El archivo ya incluye todo lo necesario:
- Constructor para luz puntual
- Constructor para foco (spotlight)
- Atributos: posición, colores, atenuación, dirección/ángulo foco
- Método `aplicar()` completamente implementado con:
  - `glLightfv()` para posición, colores
  - `glLightf()` para atenuación
  - Parámetros de spotlight (GL_SPOT_DIRECTION, GL_SPOT_CUTOFF, GL_SPOT_EXPONENT)
- Método `mover(dx, dy, dz)` para movimiento interactivo
- Métodos `encender()` / `apagar()` / `esta_encendida()`

---

### 3. `igvMaterial.h`
**Acción: ⚠️ COPIAR CON MODIFICACIONES**

**Código original del ejemplo:**
```cpp
class igvMaterial {
private:
    igvColor Ka = { 0, 0, 0 };
    igvColor Kd = { 0, 0, 0 };
    igvColor Ks = { 0, 0, 0 };
    double Ns = 0;
public:
    igvMaterial () = default;
    ~igvMaterial () = default;
    igvMaterial ( const igvMaterial &p );
    igvMaterial ( igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns );
    void aplicar ();
    void set ( igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns );
    void incrementarRDifuso(float cantidad) { Kd[0] += cantidad; }
    void incrementarREspecular(float cantidad) { Ks[0] += cantidad; }
    void incrementarExpPhong(float cantidad) { Ns += cantidad; }
};
```

**Modificaciones necesarias:** Añadir getters para acceso desde menú
```cpp
// AÑADIR estos métodos:
igvColor& getKa() { return Ka; }
igvColor& getKd() { return Kd; }
igvColor& getKs() { return Ks; }
double getNs() const { return Ns; }
```

---

### 4. `igvMaterial.cpp`
**Acción: ✅ COPIAR SIN CAMBIOS**

El método `aplicar()` ya está completamente implementado:
```cpp
void igvMaterial::aplicar() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ka.cloneToFloatArray());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Kd.cloneToFloatArray());
    glMaterialfv(GL_FRONT, GL_SPECULAR, Ks.cloneToFloatArray());
    glMaterialf(GL_FRONT, GL_SHININESS, Ns);
    GLfloat emision[] = { 0, 0, 0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, emision);
}
```

---

### 5. `igvTextura.h`
**Acción: ⚠️ COPIAR CON MODIFICACIONES**

**Código original del ejemplo:**
```cpp
class igvTextura {
private:
    unsigned int idTextura = 0;
    unsigned int alto = 0, ancho = 0;
public:
    igvTextura () = default;
    igvTextura ( std::string fichero );
    ~igvTextura ();
    void aplicar ();
    void setIdTextura ( unsigned int id );
    unsigned int getIdTextura ();
};
```

**Modificaciones necesarias para la práctica:**
```cpp
class igvTextura {
private:
    unsigned int idTextura = 0;
    unsigned int alto = 0, ancho = 0;
    
    // AÑADIR: Parámetros de filtrado actuales
    GLenum filtroMag = GL_LINEAR;
    GLenum filtroMin = GL_LINEAR;
    
public:
    igvTextura () = default;
    igvTextura ( std::string fichero );
    ~igvTextura ();
    
    void aplicar ();
    void desactivar(); // AÑADIR: Para desactivar textura
    
    void setIdTextura ( unsigned int id );
    unsigned int getIdTextura ();
    
    // AÑADIR: Métodos para cambiar filtros
    void setFiltroMag(GLenum filtro);
    void setFiltroMin(GLenum filtro);
    
    // AÑADIR: Constructor para textura procedural (tablero ajedrez)
    static igvTextura* crearTableroAjedrez(int tamano, int numCuadros);
};
```

---

### 6. `igvTextura.cpp`
**Acción: ⚠️ COPIAR CON MODIFICACIONES**

**Código base del ejemplo (mantener):**
```cpp
igvTextura::igvTextura(std::string fichero) {
    glEnable(GL_TEXTURE_2D);
    if (!glIsTexture(idTextura)) {
        std::vector<unsigned char> texeles;
        unsigned int error = lodepng::decode(texeles, ancho, alto, fichero);
        if (error) {
            throw std::runtime_error("Error leyendo archivo " + fichero);
        }
        glGenTextures(1, &idTextura);
        glBindTexture(GL_TEXTURE_2D, idTextura);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, 
                     GL_RGBA, GL_UNSIGNED_BYTE, texeles.data());
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}
```

**AÑADIR estos métodos:**
```cpp
void igvTextura::desactivar() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void igvTextura::setFiltroMag(GLenum filtro) {
    filtroMag = filtro;
    glBindTexture(GL_TEXTURE_2D, idTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtro);
}

void igvTextura::setFiltroMin(GLenum filtro) {
    filtroMin = filtro;
    glBindTexture(GL_TEXTURE_2D, idTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtro);
}

igvTextura* igvTextura::crearTableroAjedrez(int tamano, int numCuadros) {
    igvTextura* tex = new igvTextura();
    std::vector<unsigned char> imagen(tamano * tamano * 4);
    int tamCuadro = tamano / numCuadros;
    
    for (int y = 0; y < tamano; y++) {
        for (int x = 0; x < tamano; x++) {
            int cuadroX = x / tamCuadro;
            int cuadroY = y / tamCuadro;
            bool blanco = (cuadroX + cuadroY) % 2 == 0;
            
            int idx = (y * tamano + x) * 4;
            unsigned char color = blanco ? 255 : 0;
            imagen[idx] = imagen[idx+1] = imagen[idx+2] = color;
            imagen[idx+3] = 255;
        }
    }
    
    tex->ancho = tamano;
    tex->alto = tamano;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &tex->idTextura);
    glBindTexture(GL_TEXTURE_2D, tex->idTextura);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tamano, tamano, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, imagen.data());
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    return tex;
}
```

---

### 7. `lodepng.h` y `lodepng.cpp`
**Acción: ✅ COPIAR SIN CAMBIOS**

Son archivos de librería externa. Copiar directamente.

---

### 8. `igvPunto3D.h` (del proyecto original)
**Acción: 🔄 AÑADIR MÉTODO**

El archivo del proyecto original NO tiene el método `cloneToFloatArray()` que es necesario para las funciones de iluminación.

**Añadir en la sección public:**
```cpp
float *cloneToFloatArray() const; // Devuelve el punto en un array de float
```

---

### 9. `igvPunto3D.cpp` (del proyecto original)
**Acción: 🔄 AÑADIR MÉTODO**

**Añadir al final del archivo:**
```cpp
/**
 * Reserva un bloque de memoria con las coordenadas en formato flotante y en
 * coordenadas homogéneas (es decir, con cuarta coordenada = 1)
 * @return La dirección de memoria del bloque reservado
 * @note El bloque debe ser liberado con delete[] en algún momento en el código
 */
float *igvPunto3D::cloneToFloatArray() const {
    float *res = new float[4] { (float) c[0], (float) c[1], (float) c[2], 1.0f };
    return res;
}
```

---

### 10. `igvEscena3D.h`
**Acción: 🔄 MODIFICAR SIGNIFICATIVAMENTE**

**Contenido actual del proyecto (mantener):**
- Clase `igvModeloArticulado modelo`
- Métodos de selección y parte seleccionada
- Métodos para rotar partes de la lámpara

**AÑADIR basándose en el ejemplo:**
```cpp
#ifndef __IGVESCENA3D
#define __IGVESCENA3D

// ... includes existentes ...

// AÑADIR estos includes:
#include "igvFuenteLuz.h"
#include "igvMaterial.h"
#include "igvTextura.h"

class igvEscena3D {
private:
    bool ejes = true;
    
    // MANTENER del proyecto original:
    igvModeloArticulado modelo;
    int parteSeleccionada = -1;
    
    // AÑADIR para iluminación:
    igvFuenteLuz* luzPuntual;      // GL_LIGHT0
    igvFuenteLuz* luzDireccional;  // GL_LIGHT1
    igvFuenteLuz* luzSpotlight;    // GL_LIGHT2
    
    // AÑADIR para materiales:
    igvMaterial* materiales[3];    // 3 materiales predefinidos
    int materialActual = 0;
    
    // AÑADIR para texturas:
    igvTextura* texturas[3];       // 3 texturas (incluye tablero ajedrez)
    int texturaActual = -1;        // -1 = sin textura
    bool texturaActiva = false;
    
    // AÑADIR: modo de movimiento de luz
    int modoMovimientoLuz = 0;     // 0=ninguno, 1=puntual, 2=spotlight

public:
    igvEscena3D();
    ~igvEscena3D();
    
    void visualizar();
    
    // MANTENER métodos existentes para el modelo articulado...
    
    // AÑADIR getters para luces (para mover desde interfaz):
    igvFuenteLuz* getLuzPuntual() { return luzPuntual; }
    igvFuenteLuz* getLuzDireccional() { return luzDireccional; }
    igvFuenteLuz* getLuzSpotlight() { return luzSpotlight; }
    
    // AÑADIR para materiales:
    void cambiarMaterial(int indice);
    igvMaterial* getMaterialActual() { return materiales[materialActual]; }
    
    // AÑADIR para texturas:
    void cambiarTextura(int indice);  // -1 para desactivar
    void setFiltroMag(GLenum filtro);
    void setFiltroMin(GLenum filtro);
    
    // AÑADIR para modo movimiento luz:
    void setModoMovimientoLuz(int modo) { modoMovimientoLuz = modo; }
    int getModoMovimientoLuz() const { return modoMovimientoLuz; }

private:
    void pintar_ejes();
    void pintar_quads(int div_x, int div_z);  // AÑADIR basado en ejemplo
    void inicializarLuces();
    void inicializarMateriales();
    void inicializarTexturas();
};

#endif
```

---

### 11. `igvEscena3D.cpp`
**Acción: 🔄 MODIFICAR SIGNIFICATIVAMENTE**

**Estructura del archivo modificado:**

```cpp
#include <cstdlib>
#include <stdio.h>
#include "igvEscena3D.h"

// ============ CONSTRUCTOR ============
igvEscena3D::igvEscena3D() {
    ejes = true;
    
    inicializarLuces();
    inicializarMateriales();
    inicializarTexturas();
}

// ============ DESTRUCTOR ============
igvEscena3D::~igvEscena3D() {
    delete luzPuntual;
    delete luzDireccional;
    delete luzSpotlight;
    
    for (int i = 0; i < 3; i++) {
        delete materiales[i];
        if (texturas[i]) delete texturas[i];
    }
}

// ============ INICIALIZAR LUCES ============
void igvEscena3D::inicializarLuces() {
    // Luz puntual (GL_LIGHT0)
    luzPuntual = new igvFuenteLuz(
        GL_LIGHT0,
        igvPunto3D(2, 3, 2),           // Posición sobre la escena
        igvColor(0.1, 0.1, 0.1, 1),    // Ambiente
        igvColor(1, 1, 1, 1),          // Difuso
        igvColor(1, 1, 1, 1),          // Especular
        1, 0, 0                         // Atenuación
    );
    luzPuntual->encender();
    
    // Luz direccional (GL_LIGHT1) - simula el sol
    luzDireccional = new igvFuenteLuz(
        GL_LIGHT1,
        igvPunto3D(0, 1, 0),           // Dirección (w=0 para direccional)
        igvColor(0.2, 0.2, 0.2, 1),
        igvColor(0.8, 0.8, 0.7, 1),
        igvColor(0.5, 0.5, 0.5, 1),
        1, 0, 0
    );
    luzDireccional->encender();
    
    // Spotlight (GL_LIGHT2)
    luzSpotlight = new igvFuenteLuz(
        GL_LIGHT2,
        igvPunto3D(3, 2, 3),           // Posición
        igvColor(0, 0, 0, 1),
        igvColor(1, 1, 0.8, 1),        // Luz cálida
        igvColor(1, 1, 1, 1),
        1, 0, 0,
        igvPunto3D(0, -1, 0),          // Dirección: hacia abajo
        30,                             // Ángulo de apertura
        10                              // Exponente
    );
    luzSpotlight->encender();
}

// ============ INICIALIZAR MATERIALES ============
void igvEscena3D::inicializarMateriales() {
    // Material 1: Rojo brillante
    materiales[0] = new igvMaterial(
        igvColor(0.15, 0.0, 0.0),      // Ka
        igvColor(0.6, 0.1, 0.1),       // Kd
        igvColor(0.8, 0.8, 0.8),       // Ks
        100                             // Ns
    );
    
    // Material 2: Azul mate
    materiales[1] = new igvMaterial(
        igvColor(0.0, 0.0, 0.15),
        igvColor(0.1, 0.1, 0.5),
        igvColor(0.2, 0.2, 0.3),
        20
    );
    
    // Material 3: Dorado
    materiales[2] = new igvMaterial(
        igvColor(0.24725, 0.1995, 0.0745),
        igvColor(0.75164, 0.60648, 0.22648),
        igvColor(0.628281, 0.555802, 0.366065),
        51.2
    );
}

// ============ INICIALIZAR TEXTURAS ============
void igvEscena3D::inicializarTexturas() {
    texturas[0] = nullptr;  // Se carga bajo demanda
    texturas[1] = nullptr;
    texturas[2] = nullptr;
}

// ============ PINTAR EJES (mantener del original) ============
void igvEscena3D::pintar_ejes() {
    // ... código existente del proyecto original ...
}

// ============ PINTAR QUADS (del ejemplo) ============
void igvEscena3D::pintar_quads(int div_x, int div_z) {
    float ini_x = -2.5f;  // Centrado en origen
    float ini_z = -2.5f;
    float tam_x = 5.0f;
    float tam_z = 5.0f;
    
    float longX = tam_x / div_x;
    float longZ = tam_z / div_z;
    
    glNormal3f(0, 1, 0);
    
    for (int i = 0; i < div_x; i++) {
        for (int j = 0; j < div_z; j++) {
            glBegin(GL_QUADS);
            
            float x0 = ini_x + i * longX;
            float z0 = ini_z + j * longZ;
            float x1 = ini_x + (i + 1) * longX;
            float z1 = ini_z + (j + 1) * longZ;
            
            // Coordenadas de textura normalizadas [0,1]
            float s0 = (float)i / div_x;
            float t0 = (float)j / div_z;
            float s1 = (float)(i + 1) / div_x;
            float t1 = (float)(j + 1) / div_z;
            
            glTexCoord2f(s0, t0); glVertex3f(x0, 0.0f, z0);
            glTexCoord2f(s0, t1); glVertex3f(x0, 0.0f, z1);
            glTexCoord2f(s1, t1); glVertex3f(x1, 0.0f, z1);
            glTexCoord2f(s1, t0); glVertex3f(x1, 0.0f, z0);
            
            glEnd();
        }
    }
}

// ============ VISUALIZAR ============
void igvEscena3D::visualizar() {
    glPushMatrix();
    
    if (ejes) {
        pintar_ejes();
    }
    
    // === APLICAR LUCES ===
    luzPuntual->aplicar();
    luzDireccional->aplicar();
    luzSpotlight->aplicar();
    
    // === DIBUJAR SUELO ===
    glPushMatrix();
    glTranslatef(0, -0.5f, 0);  // Posicionar suelo debajo del modelo
    
    // Aplicar material del suelo
    materiales[materialActual]->aplicar();
    
    // Aplicar textura si está activa
    if (texturaActiva && texturas[texturaActual] != nullptr) {
        glEnable(GL_TEXTURE_2D);
        texturas[texturaActual]->aplicar();
    } else {
        glDisable(GL_TEXTURE_2D);
    }
    
    pintar_quads(50, 50);
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // === DIBUJAR MODELO ARTICULADO (de Práctica 2) ===
    modelo.visualizar();
    
    glPopMatrix();
}

// ============ MÉTODOS PARA MATERIALES ============
void igvEscena3D::cambiarMaterial(int indice) {
    if (indice >= 0 && indice < 3) {
        materialActual = indice;
    }
}

// ============ MÉTODOS PARA TEXTURAS ============
void igvEscena3D::cambiarTextura(int indice) {
    if (indice < 0) {
        texturaActiva = false;
        texturaActual = -1;
    } else if (indice < 3) {
        // Cargar textura bajo demanda
        if (texturas[indice] == nullptr) {
            switch(indice) {
                case 0:
                    texturas[0] = new igvTextura("mapa.png");
                    break;
                case 1:
                    texturas[1] = new igvTextura("textura2.png");
                    break;
                case 2:
                    texturas[2] = igvTextura::crearTableroAjedrez(256, 8);
                    break;
            }
        }
        texturaActual = indice;
        texturaActiva = true;
    }
}

void igvEscena3D::setFiltroMag(GLenum filtro) {
    for (int i = 0; i < 3; i++) {
        if (texturas[i] != nullptr) {
            texturas[i]->setFiltroMag(filtro);
        }
    }
}

void igvEscena3D::setFiltroMin(GLenum filtro) {
    for (int i = 0; i < 3; i++) {
        if (texturas[i] != nullptr) {
            texturas[i]->setFiltroMin(filtro);
        }
    }
}

// MANTENER todos los métodos existentes del modelo articulado:
// - rotarBaseLampara()
// - rotarBrazo1Lampara()
// - rotarBrazo2Lampara()
// - rotarPantallaLampara()
// - resetearPoseLampara()
// - seleccionarParte()
// - visualizarModoSeleccion()
// etc.
```

---

### 12. `igvInterfaz.h`
**Acción: 🔄 AÑADIR CALLBACKS Y MENÚS**

**Añadir a la clase:**
```cpp
class igvInterfaz {
private:
    // ... atributos existentes ...
    
    // AÑADIR para menú:
    static int menuPrincipal;
    static int submenuLuces;
    static int submenuMateriales;
    static int submenuTexturas;
    static int submenuFiltros;

public:
    // ... métodos existentes ...
    
    // AÑADIR:
    static void menuCallback(int opcion);
    static void crearMenu();
};
```

---

### 13. `igvInterfaz.cpp`
**Acción: 🔄 AÑADIR MENÚS Y MODIFICAR CALLBACKS**

**AÑADIR función para crear menú:**
```cpp
// IDs de opciones de menú
enum MenuOpciones {
    // Luces
    MENU_LUZ_DIRECCIONAL = 1,
    MENU_LUZ_PUNTUAL,
    MENU_LUZ_SPOTLIGHT,
    MENU_MOVER_LUZ_PUNTUAL,
    MENU_MOVER_LUZ_SPOTLIGHT,
    
    // Materiales
    MENU_MATERIAL_1,
    MENU_MATERIAL_2,
    MENU_MATERIAL_3,
    
    // Texturas
    MENU_TEXTURA_NINGUNA,
    MENU_TEXTURA_1,
    MENU_TEXTURA_2,
    MENU_TEXTURA_AJEDREZ,
    
    // Filtros
    MENU_FILTRO_MAG_NEAREST,
    MENU_FILTRO_MAG_LINEAR,
    MENU_FILTRO_MIN_NEAREST,
    MENU_FILTRO_MIN_LINEAR,
    
    MENU_SALIR
};

void igvInterfaz::crearMenu() {
    // Submenú Luces
    submenuLuces = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Toggle Luz Direccional", MENU_LUZ_DIRECCIONAL);
    glutAddMenuEntry("Toggle Luz Puntual", MENU_LUZ_PUNTUAL);
    glutAddMenuEntry("Toggle Spotlight", MENU_LUZ_SPOTLIGHT);
    glutAddMenuEntry("---------------", -1);
    glutAddMenuEntry("Mover Luz Puntual", MENU_MOVER_LUZ_PUNTUAL);
    glutAddMenuEntry("Mover Spotlight", MENU_MOVER_LUZ_SPOTLIGHT);
    
    // Submenú Materiales
    submenuMateriales = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Material 1 (Rojo)", MENU_MATERIAL_1);
    glutAddMenuEntry("Material 2 (Azul)", MENU_MATERIAL_2);
    glutAddMenuEntry("Material 3 (Dorado)", MENU_MATERIAL_3);
    
    // Submenú Texturas
    submenuTexturas = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Sin Textura", MENU_TEXTURA_NINGUNA);
    glutAddMenuEntry("Textura Mapa", MENU_TEXTURA_1);
    glutAddMenuEntry("Textura 2", MENU_TEXTURA_2);
    glutAddMenuEntry("Tablero Ajedrez", MENU_TEXTURA_AJEDREZ);
    
    // Submenú Filtros
    submenuFiltros = glutCreateMenu(menuCallback);
    glutAddMenuEntry("MAG: GL_NEAREST", MENU_FILTRO_MAG_NEAREST);
    glutAddMenuEntry("MAG: GL_LINEAR", MENU_FILTRO_MAG_LINEAR);
    glutAddMenuEntry("MIN: GL_NEAREST", MENU_FILTRO_MIN_NEAREST);
    glutAddMenuEntry("MIN: GL_LINEAR", MENU_FILTRO_MIN_LINEAR);
    
    // Menú principal
    menuPrincipal = glutCreateMenu(menuCallback);
    glutAddSubMenu("Luces", submenuLuces);
    glutAddSubMenu("Materiales", submenuMateriales);
    glutAddSubMenu("Texturas", submenuTexturas);
    glutAddSubMenu("Filtros Textura", submenuFiltros);
    glutAddMenuEntry("---------------", -1);
    glutAddMenuEntry("Salir", MENU_SALIR);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void igvInterfaz::menuCallback(int opcion) {
    switch(opcion) {
        // Luces
        case MENU_LUZ_DIRECCIONAL:
            if (_instancia->escena.getLuzDireccional()->esta_encendida())
                _instancia->escena.getLuzDireccional()->apagar();
            else
                _instancia->escena.getLuzDireccional()->encender();
            break;
        case MENU_LUZ_PUNTUAL:
            if (_instancia->escena.getLuzPuntual()->esta_encendida())
                _instancia->escena.getLuzPuntual()->apagar();
            else
                _instancia->escena.getLuzPuntual()->encender();
            break;
        case MENU_LUZ_SPOTLIGHT:
            if (_instancia->escena.getLuzSpotlight()->esta_encendida())
                _instancia->escena.getLuzSpotlight()->apagar();
            else
                _instancia->escena.getLuzSpotlight()->encender();
            break;
        case MENU_MOVER_LUZ_PUNTUAL:
            _instancia->escena.setModoMovimientoLuz(1);
            printf("Modo: Mover luz puntual (cursores)\n");
            break;
        case MENU_MOVER_LUZ_SPOTLIGHT:
            _instancia->escena.setModoMovimientoLuz(2);
            printf("Modo: Mover spotlight (cursores)\n");
            break;
            
        // Materiales
        case MENU_MATERIAL_1:
            _instancia->escena.cambiarMaterial(0);
            break;
        case MENU_MATERIAL_2:
            _instancia->escena.cambiarMaterial(1);
            break;
        case MENU_MATERIAL_3:
            _instancia->escena.cambiarMaterial(2);
            break;
            
        // Texturas
        case MENU_TEXTURA_NINGUNA:
            _instancia->escena.cambiarTextura(-1);
            break;
        case MENU_TEXTURA_1:
            _instancia->escena.cambiarTextura(0);
            break;
        case MENU_TEXTURA_2:
            _instancia->escena.cambiarTextura(1);
            break;
        case MENU_TEXTURA_AJEDREZ:
            _instancia->escena.cambiarTextura(2);
            break;
            
        // Filtros
        case MENU_FILTRO_MAG_NEAREST:
            _instancia->escena.setFiltroMag(GL_NEAREST);
            break;
        case MENU_FILTRO_MAG_LINEAR:
            _instancia->escena.setFiltroMag(GL_LINEAR);
            break;
        case MENU_FILTRO_MIN_NEAREST:
            _instancia->escena.setFiltroMin(GL_NEAREST);
            break;
        case MENU_FILTRO_MIN_LINEAR:
            _instancia->escena.setFiltroMin(GL_LINEAR);
            break;
            
        case MENU_SALIR:
            exit(0);
            break;
    }
    glutPostRedisplay();
}
```

**MODIFICAR specialFunc para mover luces:**
```cpp
void igvInterfaz::specialFunc(int key, int x, int y) {
    int modoLuz = _instancia->escena.getModoMovimientoLuz();
    
    // Si hay modo de movimiento de luz activo
    if (modoLuz > 0) {
        igvFuenteLuz* luz = (modoLuz == 1) ? 
            _instancia->escena.getLuzPuntual() : 
            _instancia->escena.getLuzSpotlight();
            
        switch (key) {
            case GLUT_KEY_UP:    luz->mover(0, 0.2, 0); break;
            case GLUT_KEY_DOWN:  luz->mover(0, -0.2, 0); break;
            case GLUT_KEY_LEFT:  luz->mover(-0.2, 0, 0); break;
            case GLUT_KEY_RIGHT: luz->mover(0.2, 0, 0); break;
        }
    }
    // Si no, usar comportamiento existente (mover parte del modelo o cámara)
    else {
        // ... código existente del proyecto original ...
    }
    
    glutPostRedisplay();
}
```

**AÑADIR en inicializa_callbacks():**
```cpp
void igvInterfaz::inicializa_callbacks() {
    glutKeyboardFunc(keyboardFunc);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(specialFunc);
    glutMouseFunc(mouseFunc);      // Mantener del original
    glutMotionFunc(motionFunc);    // Mantener del original
    
    crearMenu();  // AÑADIR esta línea
}
```

---

### 14. `CMakeLists.txt`
**Acción: 🔄 AÑADIR NUEVOS ARCHIVOS**

**Modificar la sección add_executable:**
```cmake
add_executable(${PROJECT_NAME}
        # Archivos existentes del proyecto original
        igvEscena3D.cpp
        igvEscena3D.h
        igvInterfaz.cpp
        igvInterfaz.h
        pr1a.cpp
        igvCamara.cpp
        igvCamara.h
        igvPunto3D.cpp
        igvPunto3D.h
        
        # Mallas (mantener todas)
        Mallas/igvMallaTriangulos.cpp
        Mallas/igvMallaTriangulos.h
        Mallas/igvCilindro.cpp
        Mallas/igvCilindro.h
        Mallas/igvCubo.cpp
        Mallas/igvCubo.h
        Mallas/igvDisco.cpp
        Mallas/igvDisco.h
        Mallas/igvOctaedro.cpp
        Mallas/igvOctaedro.h
        Mallas/igvTetraedro.cpp
        Mallas/igvTetraedro.h
        Mallas/igvEsfera.cpp
        Mallas/igvEsfera.h
        Mallas/igvModeloArticulado.h
        Mallas/igvModeloArticulado.cpp
        Mallas/igvCono.cpp
        Mallas/igvCono.h
        
        # NUEVOS ARCHIVOS para Práctica 3
        igvColor.cpp
        igvColor.h
        igvFuenteLuz.cpp
        igvFuenteLuz.h
        igvMaterial.cpp
        igvMaterial.h
        igvTextura.cpp
        igvTextura.h
        lodepng.cpp
        lodepng.h
)
```

---

## 📊 RESUMEN DE ACCIONES

| Categoría | Archivos | Acción |
|-----------|----------|--------|
| **Copiar sin cambios** | igvColor.h/cpp, igvFuenteLuz.h/cpp, igvMaterial.cpp, lodepng.h/cpp | 7 archivos |
| **Copiar con modificaciones menores** | igvMaterial.h, igvTextura.h/cpp | 3 archivos |
| **Modificar del proyecto original** | igvPunto3D.h/cpp, igvEscena3D.h/cpp, igvInterfaz.h/cpp, CMakeLists.txt | 7 archivos |
| **Mantener sin cambios** | pr1a.cpp, igvCamara.h/cpp, Mallas/* | Múltiples |
| **Añadir recursos** | mapa.png, textura2.png | 2 archivos |

---

## ⏱️ ORDEN DE IMPLEMENTACIÓN RECOMENDADO

1. **Paso 1:** Copiar archivos sin modificaciones (igvColor, igvFuenteLuz, lodepng)
2. **Paso 2:** Modificar igvPunto3D (añadir cloneToFloatArray)
3. **Paso 3:** Copiar y modificar igvMaterial
4. **Paso 4:** Copiar y modificar igvTextura
5. **Paso 5:** Modificar igvEscena3D (luces, materiales, texturas, suelo)
6. **Paso 6:** Modificar igvInterfaz (menús y callbacks)
7. **Paso 7:** Actualizar CMakeLists.txt
8. **Paso 8:** Añadir archivos de textura
9. **Paso 9:** Probar y ajustar
