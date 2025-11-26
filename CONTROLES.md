# Controles de la Práctica - Lámpara Articulada

## Selección de Partes del Modelo

| Tecla | Parte |
|-------|-------|
| **1** | Seleccionar BASE |
| **2** | Seleccionar BRAZO 1 |
| **3** | Seleccionar BRAZO 2 |
| **4** | Seleccionar PANTALLA |
| **0** | Deseleccionar (ninguna parte) |

## Movimiento de Partes

### Con Teclado
- **Cursores (↑↓←→)**: Rotan la parte actualmente seleccionada

### Con Ratón
- **Clic izquierdo** sobre una parte: La selecciona (usa selección por color)
- **Arrastrar** manteniendo clic izquierdo: Rota la parte seleccionada
    - **Base**: Movimiento horizontal (izquierda/derecha) la rota
    - **Brazos y Pantalla**: Movimiento vertical (arriba/abajo) los rota

## Animación Automática

| Tecla | Función |
|-------|---------|
| **A** | Activar/desactivar animación automática del MODELO |
| **G** | Activar/desactivar movimiento automático de la CÁMARA (órbita) |

## Control de Cámara

> **Nota:** Los cursores controlan la cámara solo cuando NO hay ninguna parte seleccionada (pulsa **0** para deseleccionar)

| Tecla | Función |
|-------|---------|
| **Cursores ←→** | Orbitar cámara horizontalmente |
| **Cursores ↑↓** | Cabeceo de cámara (vertical) |
| **C** | Activar/desactivar modo movimiento de cámara |
| **F** | Avanzar cámara (requiere modo movimiento activo) |
| **B** | Retroceder cámara (requiere modo movimiento activo) |
| **+** | Zoom in |
| **-** | Zoom out |
| **P** | Cambiar proyección (paralela/perspectiva) |

## Visualización

| Tecla | Función |
|-------|---------|
| **E** | Mostrar/ocultar ejes de coordenadas |
| **S** | Cambiar modo de sombreado (Gouraud/Flat) |
| **V** | Activar/desactivar modo multi-viewport (4 vistas) |
| **R** | Resetear pose de la lámpara |

## Otros

| Tecla | Función |
|-------|---------|
| **ESC** | Salir de la aplicación |

---

## Información Técnica

### Selección por Color (Buffer de Color)
Cada parte de la lámpara se renderiza con un color único para permitir la selección:

| Parte | Color RGB |
|-------|-----------|
| Base | Rojo (255, 0, 0) |
| Brazo 1 | Verde (0, 255, 0) |
| Brazo 2 | Azul (0, 0, 255) |
| Pantalla | Amarillo (255, 255, 0) |

### Grados de Libertad del Modelo
El modelo articulado tiene **4 grados de libertad**:

1. **Base**: Rotación sobre eje Y (0° - 360°)
2. **Brazo 1**: Rotación sobre eje Z (0° - 120°)
3. **Brazo 2**: Rotación sobre eje Z (-150° - 30°)
4. **Pantalla**: Rotación sobre eje Z (-90° - 45°)

### Modos de Visualización
- **Sombreado Gouraud**: Interpolación suave de colores entre vértices
- **Sombreado Flat**: Color uniforme por cada cara/triángulo
- **Multi-viewport**: 4 vistas simultáneas (frontal, superior, lateral, perspectiva)