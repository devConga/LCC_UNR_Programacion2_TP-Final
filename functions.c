#include "functions.h"

FILE* open_file_s(char* path, char* mode){
    FILE* fp = fopen(path, mode);
    assert(fp!=NULL);                                               // Chequea si se logro abrir el archivo correctamente
    return fp;
}

int get_dimension(FILE* fp){
    int dimension;
    fscanf(fp, "%*s ");                                             // Saltea la primera linea, que es la que dice "dimension"
    fscanf(fp, "%d ", &dimension);                                  // Obtiene el valor de la linea con la dimension del laberinto
    return dimension;
}


void initialize_labyrinth(Labyrinth* labyrinth){
    for(int i=0; i<labyrinth->dimension; i++){                      // Itera por cada espacio del array bidimensional del laberinto
        for(int j=0; j<labyrinth->dimension; j++){                  // colocando '0' en cada uno.
            labyrinth->layout[i][j]='0';            
        }
    }
}

void assign_layout_mem(Labyrinth* labyrinth){
    labyrinth->layout = malloc(labyrinth->dimension*sizeof(char*));             // Se pide memoria para guardar todo el laberinto en
    for(int i=0; i<labyrinth->dimension; i++)                                   // un array bidimensional de dimension x dimension
        labyrinth->layout[i] = malloc(labyrinth->dimension*(sizeof(char)));
}

void set_fixed_obstacles(FILE* fp, Labyrinth* labyrinth){
    int xPos;
    int yPos;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "obstaculos fijos"

    while(fscanf(fp, "(%d,%d) ", &xPos, &yPos)!=0){                 // Lee los valores de ambas coordenadas de cada obstaculo fijo
        printf("Obstaculo fijo: %d, %d\n", xPos, yPos);             // y coloca '1' en dicha posicion del laberinto
        labyrinth->layout[xPos-1][yPos-1] = '1';
        labyrinth->nmb_obstacles++;
    }

}

int get_number_of_rnd_obstacles(FILE* fp){
    int rnd_obstacles;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "obstaculos aleatorios"
    fscanf(fp, "%d ", &rnd_obstacles);                              // Lee el valor de la linea con el numero de obstaculos aleatorios
    return rnd_obstacles;
}

void set_inicial_pos(FILE* fp, Labyrinth* labyrinth){
    int xPos;
    int yPos;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "posicion inicial"
    fscanf(fp, "(%d,%d) ", &xPos, &yPos);                           // Lee los valores de las coordenadas de la posicion iniciar
    labyrinth->layout[xPos-1][yPos-1] = 'I';                        // y coloca 'I' en dicha posicion del laberinto
}

void set_objetive_pos(FILE* fp, Labyrinth* labyrinth){
    int xPos;
    int yPos;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "objetivo"
    fscanf(fp, "(%d,%d) ", &xPos, &yPos);                           // Lee los valores de las coordenadas del objetivo
    labyrinth->layout[xPos-1][yPos-1] = 'X';                        // y coloca 'X' en dicha posicion del laberinto
}

void set_random_obstacles(Labyrinth* labyrinth, int num){
    srand(time(NULL));                                              // Setea la semilla de la funcion rand al tiempo actual, logrando
    while(num>0){                                                   // aleatoreidad
    
        int rand_num1 = rand()%labyrinth->dimension;                // Genera dos numeros aleatorios entre 0 y la dimension
        int rand_num2 = rand()%labyrinth->dimension;                // del laberinto sin incluir.

        printf("Obstaculo random elegido: %d, %d\n", rand_num1+1, rand_num2+1);

        if(labyrinth->layout[rand_num1][rand_num2]=='0'){           // Si la posicion dada por los dos numeros aleatorios esta libre
            labyrinth->layout[rand_num1][rand_num2] = '1';          // coloca un obstaculo '1', si no, vuelve a generar dos numeros.
            num--;                          

            printf("Coordenadas Validas\n");        
        }                                                           // Esto se repite hasta generar la cantidad de obstaculos 
    }                                                               // aleatorios indicada.
    printf("\n\n");
}

int check_number_of_obstacles(Labyrinth* lab){
    int counter = 0;
    for(int i=0; i<lab->dimension; i++){                            // Itera por todo el laberinto
        for(int j=0; j<lab->dimension; j++){
            if(lab->layout[i][j] == '1')                            // Si la celda en la posicion actual tiene un obstaculo,
                counter++;                                          // incrementa en 1 el contador
        }
    }
    return lab->nmb_obstacles == counter;
}

void write_labyrinth_file(Labyrinth* labyrinth){
    FILE* fp = open_file_s("labyrinth.txt", "w");                         // Crea o sobreescribe el archivo donde se guardara
                                                                    // el laberinto en modo escritura
    fprintf(fp, "%d\n", labyrinth->dimension);

    for(int i=0; i<labyrinth->dimension; i++){                      // Itera por el laberinto.
        for(int j=0; j<labyrinth->dimension; j++){                  
            fputc(labyrinth->layout[i][j], fp);                     // En el archivo indicado, escribe el valor del laberinto
        }                                                           // en la posicion actual.
        if(i<labyrinth->dimension-1)
        fputc('\n', fp);                                            // Cuando salta de linea, si no es la final, coloca un salto de linea.
    }
    
    fclose(fp);                                                     // Se cierra el archivo del laberinto
}

void print_labyrinth(Labyrinth* labyrinth){
    for(int i=0; i<labyrinth->dimension; i++){                      // Itera por el laberinto.
        for(int j=0; j<labyrinth->dimension; j++){
            printf("%c", labyrinth->layout[i][j]);                  // Imprime el valor de la celda actual.
        }
        printf("\n");
    }
}

void free_charpointer_array(char** array, int largo){
    for(int i=0; i<largo; free(array[i++]));
    free(array);
}

