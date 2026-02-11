# CHANGELOG - EAFITos

Todos los cambios notables en este proyecto serán documentados en este archivo. El formato se basa en [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

---

## [0.3.0] - 2026-02-10
### Añadido
- **Gestión de Memoria Robusta**: Verificación completa con Valgrind exitosa (0 leaks, 0 errores).
- **Contador de Argumentos**: Implementación de lógica para validar el número de tokens ingresados por el usuario.
- **Documentación de Roles**: Creación del archivo `CONTRIBUTORS.md` con la distribución de tareas para el equipo de 3 integrantes.

### Corregido
- **Error de Enlace (Linker)**: Se resolvió la referencia indefinida (`undefined reference`) a `ejecutar_comando` y `shell_loop` mediante la inclusión correcta de headers y actualización del Makefile.
- **Error de Directorio**: Ajuste en el procedimiento de pruebas para evitar intentar ejecutar carpetas con Valgrind.

---

## [0.2.0] - 2026-02-03
### Añadido
- **Núcleo REPL**: Implementación del bucle principal de la shell (Read-Eval-Print Loop).
- **Parser Inicial**: Lógica base para la tokenización de entradas usando `strtok`.
- **Sistema de Construcción**: Configuración del `Makefile` para compilación modular en carpetas `build/`, `src/` e `include/`.

---

## [0.1.0] - 2026-01-21
### Añadido
- **Estructura de Proyecto**: Creación de la arquitectura de carpetas siguiendo el estándar para equipos de 3+ personas.
- **Archivos Base**: Inicialización de `README.md`, `.gitignore` y licencia del proyecto.
- **Planificación**: Definición del nombre del proyecto como "EAFITos".

---

### [Pendiente por Integrar]
- Finalización de los 4 comandos avanzados por parte del Desarrollador y el Tester.
- Script de pruebas automáticas en la carpeta `scripts/`.