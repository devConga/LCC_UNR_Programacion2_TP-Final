#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


typedef struct{
    char** layout;
    int dimension;
    int nmb_obstacles;
} Labyrinth;
/*
    Toma el archivo de configuracion y
    devuelve la dimension del laberinto
    indicada.
*/
int get_dimension(FILE* fp);

/*
    Toma un laberinto y lo inicializa
    con '0' en cada uno de sus espacios,
    indicando que esta libre.
*/
void initialize_labyrinth(Labyrinth* labyrinth);

/*
    Toma un archivo de configuracion y un laberinto.
    Lee cada uno de los obstaculos fijos del archivo
    y los coloca en el laberinto, indicado con '1'.
*/
void set_fixed_obstacles(FILE* fp, Labyrinth* labyrinth);

/*
    Toma un archivo de configuracion y
    devuelve la cantidad de obstaculos
    aleatorios que debe tener el laberinto.
    Tambien 
*/
int get_number_of_rnd_obstacles(FILE* fp);

/*
    Toma un archivo de configuracion y un laberinto.
    Coloca la posicion inicial dada por el archivo
    en el laberinto, indicada con 'I'.
*/
void set_inicial_pos(FILE* fp, Labyrinth* labyrinth);

/*
    Toma un archivo de configuracion y un laberinto.
    Coloca el objetivo del laberinto en las coordenadas
    dadas por el archivo, indicado por 'X'.
*/
void set_objetive_pos(FILE* fp, Labyrinth* labyrinth);

/*
    Toma un laberinto y la cantidad de obstaculos aleatorios.
    Selecciona aleatoriamente una posicion del laberinto.
    Si esta libre, coloca un obstaculo, indicado por '1'.
    Si esta ocupada, vuelve a elegir otra posicion.
    Esto se repite hasta que se hayan colocado la
    cantidad de obstaculos dada.
*/
void set_random_obstacles(Labyrinth* labyrinth, int num);

/*

*/
int check_number_of_obstacles(Labyrinth* labyrinth);

/*
    Toma un laberinto y crea un archivo de texto
    con la disposicion del laberinto.
*/
void write_labyrinth_file(Labyrinth* labyrinth);

/*
    Toma un laberinto e imprime su disposicion en
    consola.
*/
void print_labyrinth(Labyrinth* labyrinth);

/*
    Toma un array bidimensional cuadrado de caracteres
    y su largo y lo libera.
*/
void free_charpointer_array(char** array, int largo);

#endif