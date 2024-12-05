#include "functions.h"

int get_dimension(FILE* fp){
    int dimension;
    fscanf(fp, "%*s ");                                         // Saltea la primera linea, que es la que dice "dimension"
    fscanf(fp, "%d ", &dimension);
    return dimension;
}

void initialize_labyrinth(int dimension, char** labyrinth){
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            labyrinth[i][j]='0';
        }
    }
}

void set_fixed_obstacles(FILE* fp, char** labyrinth){
    int xPos;
    int yPos;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "obstaculos fijos"

    while(fscanf(fp, "(%d,%d) ", &xPos, &yPos)!=0){
        printf("hola: %d, %d\n", xPos, yPos);
        labyrinth[xPos-1][yPos-1] = '1';
    }

}

int get_number_of_rnd_obstacles(FILE* fp){
    int rnd_obstacles;
    fscanf(fp, "%*[^\n] ");                                         // Saltea la primera linea, que es la que dice "obstaculos aleatorios"
    fscanf(fp, "%d ", &rnd_obstacles);
    return rnd_obstacles;
}

void print_labyrinth(int dimension, char** labyrinth){
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            printf("%c", labyrinth[i][j]);
        }
        printf("\n");
    }
}

void free_charpointer_array(char** array, int largo){
    for(int i=0; i<largo; free(array[i++]));
    free(array);
}


