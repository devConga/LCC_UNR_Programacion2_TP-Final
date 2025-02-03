#include "functions.h"

int get_dimension(FILE* fp){
    int dimension;
    fscanf(fp, "%*s ");                                         // Saltea la primera linea, que es la que dice "dimension"
    fscanf(fp, "%d ", &dimension);
    return dimension;
}


void initialize_labyrinth(Labyrinth* labyrinth){
    for(int i=0; i<labyrinth->dimension; i++){
        for(int j=0; j<labyrinth->dimension; j++){
            labyrinth->layout[i][j]='0';
        }
    }
}

void set_fixed_obstacles(FILE* fp, Labyrinth* labyrinth){
    int xPos;
    int yPos;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "obstaculos fijos"

    while(fscanf(fp, "(%d,%d) ", &xPos, &yPos)!=0){
        printf("Obstaculo fijo: %d, %d\n", xPos, yPos);
        labyrinth->layout[xPos-1][yPos-1] = '1';
    }

}

int get_number_of_rnd_obstacles(FILE* fp){
    int rnd_obstacles;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "obstaculos aleatorios"
    fscanf(fp, "%d ", &rnd_obstacles);
    return rnd_obstacles;
}

void set_inicial_pos(FILE* fp, Labyrinth* labyrinth){
    int xPos;
    int yPos;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "posicion inicial"
    fscanf(fp, "(%d,%d) ", &xPos, &yPos);
    labyrinth->layout[xPos-1][yPos-1] = 'I';
}

void set_objetive_pos(FILE* fp, Labyrinth* labyrinth){
    int xPos;
    int yPos;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "objetivo"
    fscanf(fp, "(%d,%d) ", &xPos, &yPos);
    labyrinth->layout[xPos-1][yPos-1] = 'X';
}

void set_random_obstacles(Labyrinth* labyrinth, int num){
    srand(time(NULL));
    while(num>0){
        int rand_num1 = rand()%labyrinth->dimension;
        int rand_num2 = rand()%labyrinth->dimension;

        printf("Obstaculo random elegido: %d, %d\n", rand_num1+1, rand_num2+1);

        if(labyrinth->layout[rand_num1][rand_num2]=='0'){
            labyrinth->layout[rand_num1][rand_num2] = '1';
            num--;

            printf("Coordenadas Validas\n");
        }
    }
    printf("\n\n");
}

void print_labyrinth(Labyrinth* labyrinth){
    for(int i=0; i<labyrinth->dimension; i++){
        for(int j=0; j<labyrinth->dimension; j++){
            printf("%c", labyrinth->layout[i][j]);
        }
        printf("\n");
    }
}

void free_charpointer_array(char** array, int largo){
    for(int i=0; i<largo; free(array[i++]));
    free(array);
}

