import subprocess

def run_genLabyrinth(tries):
    '''
    Ejecuta el programa generador del laberinto con la configuracion
    dada en "config.txt". Si el programa falla, se intentara de nuevo 
    la cantidad de veces dada en el argumento. Si se queda sin intentos
    y falla de nuevo en generar el laberinto, devolvera 0.
    Si no, devuelve 1.
    '''
    tries_before_crashing = tries                                               # Numero de reintentos si el generador falla antes de salir del programa.
    response = subprocess.run(["./a.out", "config.txt"])                        # Ejecuta el programa generador con la configuracion dada en el archivo.

    while(response.returncode!=0 and tries_before_crashing):                    # Mientras haya intentos restantes y el programa generador de errores:
        print("Error en la ejecucion del programa generador del laberinto.")
        print(f"Intentos restantes antes de terminar la ejecucion:\
            {tries_before_crashing}\n\n")
        response = subprocess.run(["./a.out", "config.txt"])                    # Ejecuta el programa generador de nuevo
        tries_before_crashing -= 1                                              # Resta un intento

    if(not tries_before_crashing):                                              # Si se queda sin intentos y sigue habiendo un error en el generador, fuerza el fallo de un assert
        print("El programa generador no pudo ejecutarse correctamente\n.")
        return 0
    
    return 1

def get_dimension(fp):
    '''
    Toma un archivo con un laberinto y
    devuelve la dimension de este.
    '''
    return int(fp.readline())                                                   # Se lee la primer linea, que contiene la dimension del laberinto

def get_labyrinth(path):
    '''
    Desde un archivo con un laberinto, titulado "labyrinth.txt"
    devuelve su dimension, una lista de listas con su disposicion
    y las coordenadas de inicio y objetivo como tuplas.
    '''
    fp = open(path, "r")                                             # Abre el archivo con el laberinto
    dimension = get_dimension(fp)                                               # Obtiene la dimension del laberinto
    
    lab = [[] for _ in range(dimension)]                                        # Genera una lista con [dimension] listas vacias.
    i=0
    j=0
    for line in fp:                                                             # Por cada linea del laberinto:
        while(j<dimension):                                                     # Itera por cada caracter de la linea
            lab[i].append(line[j])                                              # Agrega el caracter a la lista correspondiente
            
            if(line[j] == 'I'):                                                 # Si el caracter es el que indica el inicio, guarda sus coords
                start = (i, j)
            if(line[j] == 'X'):                                                 # Si el caracter es el que indica el objetivo, guarda sus coords
                objective = (i, j)
            
            j+=1
        j=0
        i+=1
    
    fp.close()                                                                  # Cierra el archivo del laberinto
        
    return dimension, lab, start, objective                                     # Retorna la dimension, el laberinto transcripto y las coorsd de inicio y objetivo

def solve_labyrinth(lab, dimension, start):
    '''
    Dado una disposicion de laberinto, su dimension y sus coordenadas
    de Inicio, aplica un algoritmo BFS (Breadth Firt Search) en busca
    de su objetivo o meta. Construyeç un diccionario donde 
    cada entrada esta dada por los nodos visitados y su valor es el
    nodo desde el cual se los encontro. Si logra visitar el objetivo
    devuelve dicha tabla de valores. Si no, devuelve None.
    '''
    queue = [start]                                                             # Crea una cola de nodos a visitar y agrega el Inicio
    visited = {start: None}                                                     # Crea una diccionario donde las keys son los nodos visitados, y los valores son el nodo desde el cual se los encontro.
    found_obj = False
    
    while queue and not found_obj:                                              # Mientras la cola no se vacie y no se encuentre el objetivo:
        curr = queue.pop(0)                                                     # Obtiene el primer elemento de la cola y lo borra de la misma
                                                                                # A partir de ese nodo se visitan los adyacentes, si es posible
        if( (curr[0]-1)>=0 and \
            (curr[0]-1,curr[1]) not in visited.keys() and \
            (lab[curr[0]-1][curr[1]] == '0' or \
            lab[curr[0]-1][curr[1]] == 'X')):                                   # Chequea la validez del nodo de "arriba" y si es posible visitarlo
            
            visited[(curr[0]-1, curr[1])] = curr                                # Lo agrega al diccionario de nodos visitados, y su valor es el nodo actual
            queue.append((curr[0]-1, curr[1]))                                  # Agrega el nodo adyacente a la cola
            found_obj = found_obj or lab[curr[0]-1][curr[1]] == 'X'             # Si dicho nodo es el objetivo, se guarda en una bandera que se logro encontrarlo.
            
        if( (curr[0]+1)<dimension and \
            (curr[0]+1,curr[1]) not in visited.keys() and \
            (lab[curr[0]+1][curr[1]] == '0' or \
            lab[curr[0]+1][curr[1]] == 'X')):                                   # Chequea la validez del nodo de "abajo" y si es posible visitarlo
            
            visited[(curr[0]+1, curr[1])] = curr                                #
            queue.append((curr[0]+1, curr[1]))                                  # Se repite el procedimiento anterior
            found_obj = found_obj or lab[curr[0]+1][curr[1]] == 'X'             #
            
        if( (curr[1]-1)>=0 and \
            (curr[0],curr[1]-1) not in visited.keys() and \
            (lab[curr[0]][curr[1]-1] == '0' or \
            lab[curr[0]][curr[1]-1] == 'X')):                                   # Chequea la validez del nodo de la "izquierda" y si es posible visitarlo
            
            visited[(curr[0], curr[1]-1)] = curr                                #
            queue.append((curr[0], curr[1]-1))                                  # Se repite el procedimiento anterior
            found_obj = found_obj or lab[curr[0]][curr[1]-1] == 'X'             #
            
        if( (curr[1]+1)<dimension and \
            (curr[0],curr[1]+1) not in visited.keys() and \
            (lab[curr[0]][curr[1]+1] == '0' or \
            lab[curr[0]][curr[1]+1] == 'X')):                                   # Chequea la validez del nodo de la "derecha" y si es posible visitarlo
            
            visited[(curr[0], curr[1]+1)] = curr                                #
            queue.append((curr[0], curr[1]+1))                                  # Se repite el procedimeinto anterior
            found_obj = found_obj or lab[curr[0]][curr[1]+1] == 'X'             #
            
    if(found_obj):                                                              # Si se logro visitar el objetivo, devuelte la tabla
        return visited                                                          # de nodos y desde donde fueron encontrados u "origen"
    else:
        return None                                                             # Si no se logro visitar el objetivo, devuelve None


def build_path(bfs_res, curr):
    '''
    A partir de una tabla de valores construida por la funcion
    solve_labyrinth() y un nodo, imprime el camino mas corto
    desde dicho nodo hasta el que se le dio como Inicio a
    solve_labyrinth()
    '''
    if(bfs_res[curr] is None):
        print(f"({curr[0]+1}, {curr[1]+1})")                                    # Si el nodo no tiene origen, entonces es el Inicio y solo lo imprime
    else:
        print(f"({curr[0]+1}, {curr[1]+1}) <- ", end="")                        # Imprime el nodo actual
        build_path(bfs_res, bfs_res[curr])                                      # Se vuelve a llamar pero con el origen del nodo actual
