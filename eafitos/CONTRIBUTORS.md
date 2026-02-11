# Contribuciones y Roles del Equipo - EAFITos

Este documento detalla la distribución de responsabilidades, el impacto en el repositorio y el cumplimiento de los roles asignados para el Reto 1 de Sistemas Operativos.

---

## Tabla de Roles y Responsabilidades

| Integrante | Rol | Responsabilidades Técnicas |
| :--- | :--- | :--- |
| **Emmanuel Castaño Sepúlveda** | Líder / Arquitecto | Diseño del Core, arquitectura del Parser, lógica del Bucle REPL y configuración del Makefile. |
| **Luis Miguel Mira Mejia** | Desarrollador | Implementación técnica de los 10 comandos requeridos (6 básicos y 4 avanzados). |
| **Nicolas Reyes Cano** | Tester | Pruebas de fuga de memoria con Valgrind, desarrollo de scripts de automatización y gestión de errores. |

---

## Participación y Distribución

| Integrante | Porcentaje de Participación | Estado de Tareas |
| :--- | :---: | :--- |
| Emmanuel Castaño | 33.3% | Completado |
| Luis Miguel Mira | 33.3% | En Progreso |
| Nicolas Reyes | 33.3% | Completado |

> **Nota:** La participación se ha distribuido de manera equitativa para garantizar el cumplimiento de todos los módulos de la rúbrica.

---

## Bitácora de Commits y Gestión de Ramas (Git)

Siguiendo las buenas prácticas de Git, el trabajo se distribuyó en las siguientes ramas para mantener la integridad del código base:

* **Emmanuel Castaño Sepúlveda**:
    * `main`: Estabilización de versiones y merges.
    * `branch_fix_core_logic`: Depuración de errores de enlace y lógica del núcleo.
* **Luis Miguel Mira Mejia**:
    * `branch_comandos_basicos`: Implementación de lógica para `listar`, `leer`, `tiempo`, etc.
* **Nicolas Reyes Cano**:
    * `branch_comandos_avanzados`: Implementación de los 4 comandos de mayor complejidad.
    * *Nota*: Nicolas también colaboró en la supervisión de pruebas en las ramas de comandos.

---

## Verificación de Calidad (Checklist)
- [x] **0 Memory Leaks**: Verificado por el Tester con Valgrind.
- [x] **No uso de `system()`**: Verificado por el Líder en el Code Review.
- [x] **Modularidad**: Estructura de carpetas `src/`, `include/` y `build/` respetada.