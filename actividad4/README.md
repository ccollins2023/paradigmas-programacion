# Actividad 4 - Reflexión sobre Lógica Difusa (UGD)

## Descripción
Reflexión sobre paradigmas y lenguajes de programación aplicada a los prototipos de **lógica difusa** desarrollados en el artículo “Lógica difusa con Matlab, SciLab y Arduino”.

En este trabajo se analizan dos experiencias prácticas:
- **Experiencia 1**: Prototipo de detección del estado ambiental (temperatura y humedad).
- **Experiencia 2**: Mecanismo de avance autoajustable (seguimiento de objeto en movimiento).

Se profundiza en la combinación de **paradigmas declarativo** (lógica difusa Mamdani) e **imperativo** (C++ en Arduino), junto con propuestas de mejora (migración a TSK y mayor modularidad orientada a objetos).

## Contenido del repositorio
- `Actividad 4 - Reflexión.pdf` → Versión final entregada de la reflexión.
- Carpeta `/codigo-arduino/` → Código fuente completo de ambas experiencias.
- Carpeta `/capturas-ide/` → Imágenes del Arduino IDE mostrando el código generado.

## Explicación clave: Método de defuzzificación por centroide
En ambos prototipos se utiliza el **método del centroide** (también llamado “ponderada al centro”) para obtener el valor numérico de salida. Su fórmula es:

\[
C = \frac{\int_S x \cdot \mu(x) \, dx}{\int_S \mu(x) \, dx}
\]

donde \(\mu(x)\) es la función de pertenencia del conjunto difuso de salida y \(S\) es el rango de integración.

Esta aproximación se implementa en el código generado por MATLAB con una resolución discreta (`FIS_RESOLUTION = 101`).

## Material de referencia
El artículo base aborda:
- Inferencia difusa tipo Mamdani
- Fuzzificación y defuzzificación
- Funciones de pertenencia
- Reglas del tipo SI-ENTONCES
- Implementación embebida en Arduino (Mega y Nano)

## Archivos incluidos
- **[Ver la Reflexión completa (PDF)](./actividad4/articulo_para_reflexion_A4.pdf)**
- Código fuente Experiencia 1 → [`experiencia1.ino`](./codigo-arduino/experiencia1.ino)
- Código fuente Experiencia 2 → [`experiencia2.ino`](./codigo-arduino/experiencia2.ino)

## Autor
**Cristian Collins**  
Licenciatura en Gestión de Recursos Tecnológicos  
Universidad Gastón Dachary – 2026

---

**Repositorio creado para la Actividad 4 de Paradigmas y Lenguajes de Programación**
