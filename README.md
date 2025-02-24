# LCC_UNR_Programacion2_TP-Final
# Trabajo Practico Final de Alejandro Comba Sanz para Programacion 2.
Este proyecto se trata de generar un laberinto, dado por un tablero bidimensional cuadrado con
una posicion de **Inicio**, un **Objetivo** y **Obstaculos**. El proyecto consta de dos programas.
Uno escrito en **C** que se encarga de generar un archivo de texto con la disposicion del laberinto
a partir de un archivo con la configuracion del mismo, que contiene datos tales como la dimension,
las coordenadas de Inicio y Objetivo del mismo, asi como las de obstaculos fijos, y la cantidad de
obstaculos puestos en ubicaciones aleatorias. El otro escrito en **Python**, que ejecutara el
programa generador e intentará encontrar el camino mas corto desde el Inicio hasta el Objetivo.
Esto lo logrará usando el algoritmo **BFS** (Breadth First Seart) sobre el laberinto.
Si resulta que el laberinto no puede ser resuelto (no existe un camino desde el Inicio hasta
el objetivo) se ejecutara de nuevo el programa generador hasta que el laberinto generado pueda ser
resuelto.

## Observaciones importantes.
* El archivo configuracion debe ser llamado `config.txt`, ya que el programa resolvedor ejecutara al generador con ese archivo como argumento.
* El proyecto esta pensado para usarse en un sistema operativo basado en Linux, debido a la diferencia en las extensiones de los ejecutables generados por gcc en Windows y Linux.

# Tests con Pytest
Para correr los tests de funciones en python, instalar **pytest** y usar:
`pytest`

# Compilacion y ejecucion de los programas
## Programa generador del laberinto (escrito en C)

### Para compilar el programa se debe usar:
`gcc -Wall -Wextra -Werror genLabyrinth.c functions.c`
> _Nota: **No** ponerle un nombre al ejectuable con la bandera -o [nombre], ya que_
> _el programa en python fallará, debido a que este busca el archivo llamado a.out (en Linux)._

### Para ejectuarlo se debe usar:
`./a.out config.txt`

## Programa resolvedor del laberinto (escrito en Python)

### Para ejecutar el programa se debe usar:
`python3 SolveLabyrinth.py`

# Salida del programa
El programa generador imprimira en pantalla el proceso de generacion del laberinto y creara un archivo llamado `labyrinth.txt`, que contiene tanto la dimension del laberinto como su disposicion.
El programa resolvedor, al ser ejecutado, imprimira en pantalla el camino mas corto encontrado
desde el Inicio al Objetivo, casilla por casilla.