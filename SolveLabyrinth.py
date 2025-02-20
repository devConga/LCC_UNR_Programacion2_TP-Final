from time import sleep
from pyFunctions import *

def main():  
    tries = 0
    bfs_result = None
    
    while(bfs_result is None):
        assert(run_genLabyrinth(3))                                             # Ejecuta el programa de generacion del laberinto y se asegura que lo haga correctamente
        dimension, labyrinth, start, objective = get_labyrinth("labyrinth.txt") # Obtiene la dimension, disposicion y coords de inicio y llegada del laberinto
        for l in labyrinth:                                                     # Imprime el laberinto
            print(l)                                                            
        print(f"\nInicio: {start}")                                             # y sus coords de inicio y llegada
        print(f"Objetivo: {objective}\n")
        bfs_result = solve_labyrinth(labyrinth, dimension, start)               # Ejecuta un algoritmo BFS sobre el laberinto partiendo del inicio.
        if(bfs_result is None):                                                 # Si BFS no logro encontrar el objetivo, el laberinto no puede resolverse
            print("\n\nEl laberinto no se puede resolver.\
                 Generandolo de nuevo...\n\n")
            sleep(1)                                                            # Da tiempo a que cambie la semilla que genero el laberinto.
        tries +=1
                                                                                # Esto se repite hasta que se genere un laberinto que pueda resolverse
    
    print("\n")
    
    print(f"\nSe ha resuelto el laberinto en {tries} intento(s)")
    print("Camino mas corto encontrado:")
    build_path(bfs_result, objective)                                           # Construye el camino encontrado por BFS y lo imprime.
    
    
if __name__ == "__main__":
    main()