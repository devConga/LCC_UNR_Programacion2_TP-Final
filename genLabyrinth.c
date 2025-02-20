#include "genLabyrinth.h"

int main(int argc, char* argv[]){                                               // Se ingresa el nombre del archivo como argumento del ejecutable

    if(argc<2){
        printf("Ingrese la ruta del archivo de configuracion "); 
        printf("del laberinto junto al ejecutable por favor.\n");
        return 1;
    }
    
    FILE* fp = open_file_s(argv[1], "r");                                       // Abre el archivo de configuracion en modo lectura
    
    Labyrinth* labyrinth = malloc(sizeof(Labyrinth));               

    labyrinth->dimension = get_dimension(fp);                                   // Se obtiene la dimension del laberinto a construir
    if(labyrinth->dimension<2){                                                 // Verifica que la dimension sea valida.
        printf("La dimension del laberinto debe ser mayor a 1\n");
        return 1;
    }

    printf("Dimension del laberinto: %d\n\n", labyrinth->dimension);

    labyrinth->nmb_obstacles = 0;                                               // Se inicializan los espacios ocupados.

    assign_layout_mem(labyrinth);

    initialize_labyrinth(labyrinth);                                            // Se inicializa el laberinto con '0' en cada espacio

    set_fixed_obstacles(fp, labyrinth);                                         // Se colocan los obstaculos fijos
    
    int rnd_obstacles = get_number_of_rnd_obstacles(fp);                        // Se obtiene el numero de obstaculos aleatorios a colocar
    if(rnd_obstacles<0){
        printf("Numero invalido de obstaculos random\n");
        return 1;
    }
    
    printf("\nObstaculos random: %d\n\n", rnd_obstacles);
    if(labyrinth->nmb_obstacles+2+rnd_obstacles >= 
       labyrinth->dimension*labyrinth->dimension){                              // Se le suman dos celdas por las posiciones de inicio y meta
        printf("Los obstaculos random ocupan todo el laberinto.\n");
        return 1;
    }

    labyrinth->nmb_obstacles+=rnd_obstacles;

    set_inicial_pos(fp, labyrinth);                                             // Se coloca la posicion inicial del laberinto

    set_objetive_pos(fp, labyrinth);                                            // Se coloca la meta del laberinto

    fclose(fp);                                                                 // Cierra el archivo de configuracion

    set_random_obstacles(labyrinth, rnd_obstacles);                             // Se colocan los obstaculos aleatorios

    if(!check_number_of_obstacles(labyrinth)){                                  // Chequea si se colocaron todos los obstaculos deseados.
        printf("Error al colocar los obstaculos. ");
        printf("La cantidad puesta no coincide con la deseada\n");
        return 1;
    }
    
    write_labyrinth_file(labyrinth);

    print_labyrinth(labyrinth);                                                 // Se imprime en consola el laberinto creado

    // Liberaciones de memoria
    free_charpointer_array(labyrinth->layout, labyrinth->dimension);
    free(labyrinth);

    return 0;                                                                   // Se retorna la dimension del laberinto para
                                                                                // facilitar el programa en python.
}