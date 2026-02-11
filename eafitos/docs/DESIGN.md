# Diseño Arquitectónico - EAFITos

## 1. Patrón de Diseño
EAFITos utiliza un modelo de **Arquitectura en Capas**. El objetivo principal es el **Bajo Acoplamiento**: que el Parser no necesite saber cómo funciona el comando `buscar`, y que los comandos no necesiten saber cómo se capturó la entrada.

## 2. Flujo de Datos
1. **Captura**: `shell_loop.c` obtiene la cadena mediante `fgets`.
2. **Transformación**: `parser.c` limpia la cadena y la convierte en un vector de punteros (`char **args`).
3. **Despacho**: El ejecutor identifica el comando y llama a la función correspondiente en la capa de `commands/`.
4. **Retorno**: Cada comando devuelve un entero (1 para continuar, 0 para salir).

## 3. Estrategia de Memoria
Para garantizar **0 Memory Leaks**, implementamos un **Memory Manager** en `utils/`. Toda función que requiera memoria dinámica debe usar nuestros wrappers, permitiendo un rastreo centralizado durante la fase de QA con Valgrind.