# EAFITos - Shell Project (Reto 1)

**EAFITos** es una shell personalizada desarrollada en C para la asignatura de Sistemas Operativos en la **Universidad EAFIT**. Este proyecto implementa un intérprete de comandos modular, diseñado para equipos de 3 integrantes, con un enfoque estricto en la gestión de memoria y el uso de llamadas al sistema.

---

## Características Principales
* **Gestión de Memoria Impecable**: Verificado con Valgrind (0 memory leaks) gracias al uso de un `memory_manager` propio.
* **Arquitectura Modular**: Código organizado en `src/`, `include/` y `build/`.
* **Parser Robusto**: Manejo de múltiples tokens y validación de argumentos antes de la ejecución.
* **Seguridad**: Implementación nativa que evita el uso de la función prohibida `system()`.

---

## Comandos Implementados

### Comandos Básicos (Obligatorios)
| Comando | Uso | Descripción |
| :--- | :--- | :--- |
| `listar` | `listar` | Lista archivos y directorios en la ruta actual. |
| `leer` | `leer <archivo>` | Despliega el contenido de un archivo en consola. |
| `tiempo` | `tiempo` | Muestra la fecha y hora actual del sistema. |
| `calc` | `calc <n1> <op> <n2>` | Realiza operaciones matemáticas básicas. |
| `ayuda` | `ayuda` | Muestra el manual de usuario. |
| `salir` | `salir` | Finaliza la ejecución de EAFITos. |

### Comandos Avanzados (Implementados)
| Comando | Uso | Descripción |
| :--- | :--- | :--- |
| **`crear`** | `crear <nombre>` | Crea un nuevo archivo en el sistema de archivos. |
| **`eliminar`** | `eliminar <nombre>` | Remueve un archivo de forma permanente. |
| **`renombrar`** | `renombrar <orig> <dest>` | Cambia el nombre de un archivo o lo mueve de ruta. |
| **`buscar`** | `buscar <texto> <arch>` | Busca coincidencias (case-insensitive) dentro de un archivo. |

---

## Instalación y Uso

### Compilación Modular
Para compilar el proyecto asegurando una limpieza previa:
```bash
make clean && make
```
```bash
./EAFITos
```

### Ejecución con Pruebas de Memoria 
Como líderes del proyecto, garantizamos la estabilidad mediante Valgrind:
```bash
valgrind --leak-check=full ./EAFITos
```

---

## Equipo de Trabajo y Roles

| Integrante | Usuario GitHub | Rol | Responsabilidad Principal |
| :--- | :--- | :--- | :--- |
| **Emmanuel Castaño** | [@ecastanos23](https://github.com/ecastanos23) | Líder / Arquitecto | Core, Parser y Makefile |
| **Luis Miguel Mira** | [@lmira](https://github.com/lmira) | Desarrollador | Comandos Básicos y Avanzados |
| **Nicolas Reyes** | [@nreyes](https://github.com/nreyes) | Tester | QA, Valgrind y Errores |

---

## Arquitectura del Proyecto: EAFITos

La estructura de **EAFITos** sigue un modelo modular multicapa, diseñado para facilitar la colaboración en equipos de 3 personas y garantizar la separación de responsabilidades.

```text
eafitos/
├── src/                        # Capa de Implementación (.c)
│   ├── core/                   # Núcleo del shell (El Motor)
│   │   ├── main.c              # Punto de entrada del programa
│   │   ├── shell_loop.c        # Ciclo REPL (Read-Eval-Print Loop)
│   │   └── parser.c            # Tokenización y análisis de comandos
│   ├── commands/               # Lógica de Comandos (Funcionalidades)
│   │   ├── basic_commands.c    # 6 comandos obligatorios (ayuda, salir, etc.)
│   │   ├── system_commands.c   # Interacción con el entorno del SO
│   │   └── advanced_commands.c # Comandos complejos (buscar, renombrar)
│   └── utils/                  # Servicios de Soporte
│       ├── memory_manager.c    # Gestión centralizada de memoria (0 leaks)
│       ├── error_handler.c     # Manejo de excepciones y errno
│       └── helpers.c           # Funciones auxiliares de procesamiento
├── include/                    # Capa de Definición (Headers .h)
│   ├── shell.h                 # Definiciones globales y core
│   ├── commands.h              # Prototipos de toda la lógica de comandos
│   ├── parser.h                # Estructuras del analizador léxico
│   └── utils.h                 # Prototipos de herramientas de soporte
├── tests/                      # Suite de Pruebas (Calidad)
│   ├── unit_tests.c            # Pruebas de funciones individuales
│   ├── integration_tests.c     # Pruebas de flujo completo de comandos
│   └── test_runner.sh          # Script de automatización de pruebas
├── docs/                       # Documentación Técnica
│   ├── API.md                  # Documentación de funciones internas
│   ├── DESIGN.md               # Justificación de la arquitectura
│   └── USER_GUIDE.md           # Manual de usuario final
├── scripts/                    # Automatización de Tareas
│   ├── build.sh                # Script de compilación rápida
│   └── format.sh               # Formateo de código (Clang-format)
├── Makefile                    # Sistema de construcción (Build System)
├── README.md                   # Presentación general del proyecto
├── CONTRIBUTORS.md             # Roles y porcentajes de participación
├── CHANGELOG.md                # Historial de versiones y correcciones
└── LICENSE                     # Licencia de uso del software