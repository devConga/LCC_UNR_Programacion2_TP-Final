#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int get_dimension(FILE* fp);

void initialize_labyrinth(int dimension, char** labyrinth);

void set_fixed_obstacles(FILE* fp, char** labyrinth);

int get_number_of_rnd_obstacles(FILE* fp);

void set_inicial_pos(FILE* fp, char** labyrinth);

void set_objetive_pos(FILE* fp, char** labyrinth);

void print_labyrinth(int dimension, char** labyrinth);

void free_charpointer_array(char** array, int largo);

#endif