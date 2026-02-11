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

# Especificaciones de Diseño - EAFITos

Detalle específico de la lógica interna de los componentes núcleo de la shell, asegurando un flujo de datos coherente y modular.

---

## Módulo: Parser
El **Parser** es el encargado del análisis léxico de la entrada del usuario. 

* **Implementación**: Utilizamos la función estándar `strtok()` de la librería `<string.h>`.
* **Justificación**: Se eligió `strtok()` por ser la función estándar de C más eficiente para la tokenización de cadenas basándose en delimitadores específicos:
    * Espacios en blanco (` `)
    * Tabuladores (`\t`)
    * Saltos de línea (`\n`)
    * Retornos de carro (`\r`)

---

## Bucle REPL (Read-Eval-Print Loop)
La arquitectura de **EAFITos** se basa en un ciclo continuo que procesa las instrucciones del usuario en cuatro fases críticas:

### Proceso paso a paso:

1.  **Read (Lectura)**: 
    * Capturamos la entrada bruta del usuario mediante `fgets()`. Esta función es preferida sobre `scanf()` por su capacidad para manejar espacios y prevenir desbordamientos de búfer al especificar el tamaño máximo.
2.  **Eval (Evaluación)**: 
    * La entrada se envía al **Parser** para descomponerla en comandos y argumentos. Posteriormente, el motor de ejecución busca la función correspondiente en la tabla de comandos implementados.
3.  **Print (Impresión)**: 
    * Una vez que el comando es localizado y ejecutado, este imprime directamente su resultado o mensajes de error en la salida estándar (`stdout` / `stderr`).
4.  **Loop (Ciclo)**: 
    * Tras liberar la memoria temporal utilizada en la evaluación, la shell reinicia el ciclo y vuelve a mostrar el *prompt* al usuario.

---

## Punto de Entrada: Main
El archivo `main.c` actúa como el orquestador inicial del sistema. 

* **Misión**: Su diseño es minimalista y robusto siguiendo el principio de responsabilidad única. Su única función es realizar las configuraciones iniciales de entorno y arrancar el **Bucle REPL**.
* **Seguridad**: Al mantener el `main` sencillo, reducimos la probabilidad de errores de inicialización y facilitamos la depuración del ciclo de vida del programa.