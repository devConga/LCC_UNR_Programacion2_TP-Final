#include "genLabyrinth.h"

int main(int argc, char* argv[]){                                   // Se ingresa el nombre del archivo como argumento del ejecutable
    
    if(argc<2){
        printf("Ingrese la ruta del archivo de configuracion "); 
        printf("del laberinto junto al ejecutable por favor.");
        return 1;
    }
    
    FILE* fp = fopen(argv[1], "r");                                 // Abre el archivo en modo lectura
    
    Labyrinth* labyrinth = malloc(sizeof(Labyrinth));

    labyrinth->dimension = get_dimension(fp);
    printf("Dimension del laberinto: %d\n\n", labyrinth->dimension);

    labyrinth->layout = malloc(labyrinth->dimension*sizeof(char*));             // Se pide memoria para guardar todo el laberinto en
    for(int i=0; i<labyrinth->dimension; i++)                                  // un array bidimensional de dimension x dimension.
        labyrinth->layout[i] = malloc(labyrinth->dimension*(sizeof(char)));

    initialize_labyrinth(labyrinth);

    set_fixed_obstacles(fp, labyrinth);
    
    int rnd_obstacles = get_number_of_rnd_obstacles(fp);
    printf("\nObstaculos random: %d\n\n", rnd_obstacles);

    set_inicial_pos(fp, labyrinth);

    set_objetive_pos(fp, labyrinth);

    print_labyrinth(labyrinth);

    // Liberaciones de memoria
    free_charpointer_array(labyrinth->layout, labyrinth->dimension);
    free(labyrinth);
    fclose(fp);                                                     // Cierra el archivo.

    return 0;
}