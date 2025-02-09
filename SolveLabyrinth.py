import subprocess
import time

def run_genLabyrinth():
    tries_before_crashing = 5

    response = subprocess.run(["./a.out", "config.txt"])

    while(response.returncode!=0 and tries_before_crashing):
        print("Error en la ejecucion del programa generador del laberinto.")
        print(f"Intentos restantes antes de terminar la ejecucion: {tries_before_crashing}\n\n")
        response = subprocess.run(["./a.out", "config.txt"])
        tries_before_crashing -= 1

    if(not tries_before_crashing):
        print("El programa generador no pudo ejecutarse correctamente\n.")
        return 0
    
    return 1

def get_dimension(fp):
    return int(fp.readline())                                                   # Se lee la primer linea, que contiene la dimension del laberinto

def get_labyrinth():
    
    fp = open("labyrinth.txt", "r")
    dimension = get_dimension(fp)
    
    lab = [[] for i in range(dimension)]
    i=0
    j=0
    for line in fp:
        while(j<dimension):
            lab[i].append(line[j])
            
            if(line[j] == 'I'):
                start = (i, j)
            if(line[j] == 'X'):
                objective = (i, j)
            
            j+=1
        j=0
        i+=1
    
    fp.close()
        
    return dimension, lab, start, objective

def build_path(bfs_res, curr):
    if(bfs_res[curr] is None):
        print(curr)
    else:
        print(f"{curr} -> ", end="")
        build_path(bfs_res, bfs_res[curr])

def solve_labyrinth(lab, dimension, start):
    queue = [start]
    visited = {start: None}
    found_obj = False
    
    while queue and not found_obj:
        curr = queue.pop(0)
        
        if( (curr[0]-1)>=0 and \
            (curr[0]-1,curr[1]) not in visited.keys() and \
            (lab[curr[0]-1][curr[1]] == '0' or \
            lab[curr[0]-1][curr[1]] == 'X')):
            
            visited[(curr[0]-1, curr[1])] = curr
            queue.append((curr[0]-1, curr[1]))
            found_obj = found_obj or lab[curr[0]-1][curr[1]] == 'X'
            
        if( (curr[0]+1)<dimension and \
            (curr[0]+1,curr[1]) not in visited.keys() and \
            (lab[curr[0]+1][curr[1]] == '0' or \
            lab[curr[0]+1][curr[1]] == 'X')):
            
            visited[(curr[0]+1, curr[1])] = curr
            queue.append((curr[0]+1, curr[1]))
            found_obj = found_obj or lab[curr[0]+1][curr[1]] == 'X'
            
        if( (curr[1]-1)>=0 and \
            (curr[0],curr[1]-1) not in visited.keys() and \
            (lab[curr[0]][curr[1]-1] == '0' or \
            lab[curr[0]][curr[1]-1] == 'X')):
            
            visited[(curr[0], curr[1]-1)] = curr
            queue.append((curr[0], curr[1]-1))
            found_obj = found_obj or lab[curr[0]][curr[1]-1] == 'X'
            
        if( (curr[1]+1)<dimension and \
            (curr[0],curr[1]+1) not in visited.keys() and \
            (lab[curr[0]][curr[1]+1] == '0' or \
            lab[curr[0]][curr[1]+1] == 'X')):
            
            visited[(curr[0], curr[1]+1)] = curr
            queue.append((curr[0], curr[1]+1))
            found_obj = found_obj or lab[curr[0]][curr[1]+1] == 'X'
            
    if(found_obj):
        print("Tabla de visitados: ")
        for k in visited.keys():
            print(f"{k}: {visited[k]}")
        return visited
    else:
        for k in visited.keys():
            print(f"{k}: {visited[k]}")
        return None
    

def main():  
    bfs_result = None
    intentos = 0
    
    while(bfs_result is None):
        assert(run_genLabyrinth())
        dimension, labyrinth, start, objective = get_labyrinth()
        for l in labyrinth:
            print(l)
        print(f"\nInicio: {start}")
        print(f"Objetivo: {objective}\n")
        bfs_result = solve_labyrinth(labyrinth, dimension, start)
        if(bfs_result is None):
            print("\n\nEl laberinto no se puede resolver. Generandolo de nuevo...\n\n")
            time.sleep(1)
        intentos +=1
    
    print("\n")
    
    print(f"\nSe ha resuelto el laberinto en {intentos} intento(s)")
    print("Camino mas corto encontrado:")
    build_path(bfs_result, objective)
    
    
if __name__ == "__main__":
    main()