## Bitácora de Actividades del Equipo

Para garantizar el cumplimiento de la rúbrica de un equipo de 3 integrantes, se ha definido el siguiente registro de actividades técnicas:

### 1. Emmanuel Castaño Sepúlveda (Líder / Arquitecto)
* **Diseño de Arquitectura**: Definición de la estructura modular (`src/`, `include/`, `build/`).
* **Core del Sistema**: Implementación del bucle REPL principal y el sistema de gestión de señales.
* **Parser de Comandos**: Desarrollo del analizador de texto encargado de la tokenización y manejo de espacios.
* **Automatización**: Creación y refinamiento del `Makefile` para la compilación modular.

### 2. Luis Miguel Mira Mejía (Desarrollador)
* **Lógica de Comandos Básicos**: Implementación de las funciones para los 6 comandos obligatorios (`listar`, `leer`, `tiempo`, `calc`, `ayuda`, `salir`).
* **Lógica de Comandos Avanzados**: Desarrollo de las funciones de manipulación de archivos (`crear`, `eliminar`, `renombrar`, `buscar`).
* **Integración**: Vinculación de las funciones de comandos con el despachador de la shell (`executor.c`).

### 3. Nicolas Reyes Cano (Tester / QA)
* **Gestión de Memoria**: Auditoría constante con Valgrind para asegurar un estado de "0 leaks".
* **Control de Errores**: Implementación del sistema de manejo de errores (`error_handler.c`) y validación de `errno`.
* **Pruebas de Estrés**: Ejecución de casos de prueba con entradas largas y argumentos inválidos para garantizar la robustez del sistema.
* **Documentación Técnica**: Registro de resultados de pruebas y mantenimiento del `CHANGELOG.md`.

---

## Resumen de Contribuciones

| Actividad | Porcentaje de Impacto | Responsable |
| :--- | :---: | :--- |
| Estructura y Core | 33.3% | Emmanuel Castaño |
| Funcionalidades (10 comandos) | 33.3% | Luis Miguel Mira |
| Robustez y Calidad (QA) | 33.3% | Nicolas Reyes |
