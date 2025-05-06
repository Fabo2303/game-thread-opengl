# OPENGL GAME

Este proyecto fue propuesto para el curso de programación paralela y concurrente del ciclo VII de la carrera de Ingeniería de Sistemas de la Universidad Nacional Mayor de San Marcos.

La finalidad de este proyecto era aplicar los conocimientos en programación paralela y concurrente mediante un lenguaje de programación, a elección del alumno.

Se aplicó:
- Aplicación de threads.
- Aplicación de mutex.
- Aplicación de divide y vencerás.
- Aplicación de semáforos.
- Aplicación de variables de condición.

## Características principales

Este juego trata sobre una nave que se va a encargar de eliminar a los alienígenas que vienen a destruir la tierra, consta de tres niveles, en los dos primeros vienen alienígenas comunes y en el último nivel aparece el jefe final, este enemigo puede ser eliminado con 8 balas. Puedes ir de derecha a izquierda con las teclas `a` y `d`, también puedes disparar con la barra espaciadora.

## Herramientas utilizadas
- OpenGL para manejar los gráficos.
- PisKel para los sprites a mostrar.
- Visual Studio Code para programar el proyecto.

## Requisitos

- Instalar mingw (Una versión que soporte threads).
- Instalar la librería de OpenGL (freeglut).
- Instalar CMake para compilar

## Instrucciones para su uso

- Clonar el repositorio.
  ```bash
  git clone git@github.com:Fabo2303/game-thread-opengl.git
  ```
- Ubicarnos en la carpeta src.
  ```bash
  cd src/
  ```
- Ejecutar un comando en la terminal para compilar el proyecto.
  ```bash
  make
  ```
- Ejecutar el archivo generado por la compilación
  ```bash
  ./build/main
  ```

## Estructura del proyecto

```
parallax-defender/
├── 📁 files/
│   └── 📝 scores.txt
├── 📁 include/
│   ├── 📁 characters/
│   │   ├── 📄 boss.h
│   │   ├── 📄 bullet.h
│   │   ├── 📄 defender.h
│   │   └── 📄 enemy.h
│   └── 📁 utils/
│   │   ├── 📄 calculateSpeedUp.h
│   │   ├── 📄 drawUtils.h
│   │   └── 📄 operations.h
├── 📁 src/
│   ├── 📁 characters/
│   │   ├── ➕ boss.cpp
│   │   ├── ➕ bullet.cpp
│   │   ├── ➕ defender.cpp
│   │   └── ➕ enemy.cpp
│   ├── 📁 utils/
│   │   ├── ➕ calculateSpeedUp.cpp
│   │   ├── ➕ drawUtils.cpp
│   │   └── ➕ operations.cpp
│   └── ➕ main.cpp
├── 📄 .gitignore
├── 📄 build.sh
├── 📄 Makefile
└── 📝 README.md
```

## Sprites utilizados

No se utilizaron sprites en el sentido tradicional, sino que se realizó el dibujo a través de una matriz de colores. A continuación, mostraré los sprites que se emplearon.

- Nave espacial
  ![Nave](https://github.com/Fabo2303/game-thread-opengl/assets/115574987/1e253006-da39-4e41-8e00-6e633fbe295b)
  Recreado desde https://acortar.link/J3bPs3

- Enemigos comunes
  - Alien anaranjado
    ![alien-anaranjado](https://github.com/Fabo2303/game-thread-opengl/assets/115574987/5bd9d729-44c0-4add-ba2d-aec19ed992d7)
    Recreado desde https://acortar.link/5sIcGv
  - Alien morado 
    ![alien-morado](https://github.com/Fabo2303/game-thread-opengl/assets/115574987/b8206514-0258-4bb6-b958-51e6150ac36e)
    Recreado desde https://acortar.link/YMkiyG
- Jefe Final
    ![jefe-final](https://github.com/Fabo2303/game-thread-opengl/assets/115574987/0148402b-0263-4959-b774-2efd7d0b46c9)
    Recreado desde https://acortar.link/6o5XUE

  ### Procedimiento para la conversión de la imagen a una matriz de colores en hexadecimal.

  A primera vista, puede parecer que es un proceso complejo, y probablemente lo sea, pero en este caso, nos apoyaremos en la herramienta Piskel para facilitar el trabajo.

  Nos dirigiremos a [Piskel](https://www.piskelapp.com/) para crear un nuevo sprite. Este paso podría ser el más desafiante, ya que implica la transformación de una imagen en un sprite pixelado. Sin embargo, para facilitar este proceso, aprovecharemos la propiedad de simetría de los sprites.

  Una vez que hayamos terminado el sprite, necesitaremos ajustar el panel a la imagen y pintar el fondo con un color muy diferente al que se utilizó en el sprite. Guardaremos el archivo con la extensión .piskel y, al exportarlo, seleccionaremos la opción Others, donde procederemos a descargar el archivo en C.

  Al abrir el archivo en C, observaremos que existe un vector que contiene todo el sprite. Si lo prefieres, puedes utilizarlo de esta manera, pero si necesitas una matriz, deberemos formatearlo. Para ello, puedes utilizar este script de Python. Al final, este generará un archivo txt con la matriz.
  ```python
  data = [AGREGAR EL VECTOR]
  rows = AGREGAR LAS FILAS
  columns = AGREGAR LAS COLUMNAS

  matrix = [data[i:i+columns] for i in range(0, len(data), columns)]

  with open("matrix2.txt", "w") as file:
      for row in matrix:
          file.write("{")
          for i, value in enumerate(row):
              file.write(hex(value))
              if i != len(row) - 1:
                  file.write(", ")

          file.write("},\n")
  ```
  Finalmente, ya está en tu control como lo dibujarás con esta matriz, aunque si lo necesitas puedes ver la manera en la que yo lo hago.

## CAPTURAS DE EJECUCIÓN

![Captura 1](https://github.com/Fabo2303/game-thread-opengl/assets/115574987/8b824297-58b0-4f17-a2ea-07fcbfa23dcb)

![Captura 2](https://github.com/Fabo2303/game-thread-opengl/assets/115574987/23edf3a4-61a7-4656-be33-514aeda0245a)

![Captura 3](https://github.com/Fabo2303/game-thread-opengl/assets/115574987/4638c9dd-7edb-4039-a2cb-f0cb38561f9b)
