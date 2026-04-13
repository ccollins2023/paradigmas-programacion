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
c = \frac{\int_S x \cdot \mu(x) \, dx}{\int_S \mu(x) \, dx}
\]

donde \(\mu(x)\) es la función de pertenencia del conjunto difuso de salida y \(S\) es el rango de integración.

Esta aproximación se implementa en el código generado por MATLAB con una resolución discreta (`FIS_RESOLUTION = 101`).

## Nota técnica: Diferencia de costo computacional entre Mamdani y TSK

Para comprender mejor la diferencia en costo computacional entre ambos métodos de inferencia difusa, es necesario analizar cómo se implementa cada uno sobre el hardware Arduino.

**Método Mamdani (centroide):**
En la implementación real de la Experiencia 1, el código generado por MATLAB define la constante `FIS_RESOLUSION = 101`. Esto significa que, para calcular la salida, el microcontrolador debe dividir el rango de salida en 101 puntos y evaluar la función de pertenencia en cada uno de ellos. Por cada ciclo de control, se ejecuta implícitamente un bucle de 101 iteraciones con operaciones de punto flotante.

**Método Takagi-Sugeno-Kang (TSK):**
En cambio, este modelo elimina por completo la etapa de defuzzificación. Cada regla produce directamente un valor numérico mediante una operación matemática simple (por ejemplo, una combinación lineal de las entradas). La salida final se obtiene como un promedio ponderado de esos valores, utilizando los grados de activación de las reglas como pesos.

**Consecuencia práctica sobre el hardware:**
- Mamdani: 101 iteraciones + múltiples operaciones flotantes por ciclo
- TSK: unas pocas operaciones aritméticas, sin bucles largos

Esto se traduce en un procesamiento más rápido, mayor frecuencia de muestreo de sensores y menor consumo de recursos del microcontrolador, aspectos críticos en sistemas embebidos de tiempo real.

*Esta nota complementa el análisis realizado en la Sección 2 de la reflexión principal.*
## Material de referencia
El artículo base aborda:
- Inferencia difusa tipo Mamdani
- Fuzzificación y defuzzificación
- Funciones de pertenencia
- Reglas del tipo SI-ENTONCES
- Implementación embebida en Arduino (Mega y Nano)

## Archivos incluidos
- Código fuente Experiencia 1 → [`experiencia1.ino`](./actividad4/Codigo_Arduino/experiencia1.ino)
- Código fuente Experiencia 2 → [`experiencia2.ino`](./actividad4/Codigo_Arduino/experiencia2.ino)

## Autor
**Cristian Collins**  
Licenciatura en Gestión de Recursos Tecnológicos  
Universidad Gastón Dachary – 2026

---

**Repositorio creado para la Actividad 4 de Paradigmas y Lenguajes de Programación**
