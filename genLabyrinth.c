#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANT_LINEAS_INIC 20

int main(int argc, char* argv[]){                                   // Se ingresa el nombre del archivo como argumento del ejecutable
    
    
    FILE* file = fopen(argv[argc-1], "r");                               // Abre el archivo en modo lectura

    char buff[250];

    while(fscanf(file, "%[^\n] ", buff)!=EOF){

        for(size_t i=0; i<strlen(buff); printf("%c", buff[i++]));
        printf("\n");
    }
    

    fclose(file);                                                   // Cierra el archivo.

    return 0;
}