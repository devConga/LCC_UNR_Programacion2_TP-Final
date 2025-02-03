#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct{
    char** layout;
    int dimension;
} Labyrinth;


void initialize_labyrinth(Labyrinth* labyrinth);

void set_fixed_obstacles(FILE* fp, Labyrinth* labyrinth);

int get_number_of_rnd_obstacles(FILE* fp);

void set_inicial_pos(FILE* fp, Labyrinth* labyrinth);

void set_objetive_pos(FILE* fp, Labyrinth* labyrinth);

void print_labyrinth(Labyrinth* labyrinth);

void print_cellsID(Labyrinth* labyrinth);

void free_charpointer_array(char** array, int largo);

#endif