import subprocess

def get_dimension(fp):
    return int(fp.readline())                                                   # Se lee la primer linea, que contiene la dimension del laberinto

def get_labyrinth(fp, dimension):
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
        
    return lab, start, objective

def solve_labyrinth(labyrinth, start, objective):
    ...

def main():

    tries_before_crashing = 5

    response = subprocess.run(["./a.out", "config.txt"])

    while(response.returncode!=0 and tries_before_crashing):
        print("Error en la ejecucion del programa generador del laberinto.")
        print(f"Intentos restantes antes de terminar la ejecucion: {tries_before_crashing}\n\n")
        response = subprocess.run(["./a.out", "config.txt"])
        tries_before_crashing -= 1

    if(not tries_before_crashing):
        print("El programa generador no pudo ejecutarse correctamente\n.")
        return 1

    print("\n\nInicio de la ejecucion del programa en python\n\n")

    fp = open("labyrinth.txt", "r")
    dimension = get_dimension(fp)
    
    labyrinth, start, objective = get_labyrinth(fp, dimension)
    
    fp.close()
    
    for l in labyrinth:
        print(l)
        
    print(f"\n{start}")
    print(objective)
    
    
    
    
    
if __name__ == "__main__":
    main()