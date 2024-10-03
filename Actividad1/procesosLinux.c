#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NAMES 100
#define MAX_NAME_LENGTH 100

// Función para ordenar nombres en orden alfabético descendente
void ordenar_nombres(char nombres[][MAX_NAME_LENGTH], int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            if (strcmp(nombres[i], nombres[j]) < 0) {
                //Hace el intercambio
                char temp[MAX_NAME_LENGTH];
                strcpy(temp, nombres[i]);
                strcpy(nombres[i], nombres[j]);
                strcpy(nombres[j], temp);
            }
        }
    }
}

// Función para encontrar los nombres con la longitud mínima y máxima
void encontrar_min_max_nombres(char nombres[][MAX_NAME_LENGTH], int cantidad) {
    int min_len = strlen(nombres[0]);
    int max_len = strlen(nombres[0]);
    char nombre_min[MAX_NAME_LENGTH];
    char nombre_max[MAX_NAME_LENGTH];
    strcpy(nombre_min, nombres[0]);
    strcpy(nombre_max, nombres[0]);

    for (int i = 1; i < cantidad; i++) {
        int len = strlen(nombres[i]);
        if (len < min_len) {
            min_len = len;
            strcpy(nombre_min, nombres[i]);
        }
        if (len > max_len) {
            max_len = len;
            strcpy(nombre_max, nombres[i]);
        }
    }

    printf("Nombre con menos letras: %s, Nombre con más letras: %s\n", nombre_min, nombre_max);
}

// Función para imprimir nombres con número par de caracteres
void imprimir_nombres_pares(char nombres[][MAX_NAME_LENGTH], int cantidad) {
    printf("Nombres con número par de caracteres:\n");
    for (int i = 0; i < cantidad; i++) {
        if (strlen(nombres[i]) % 2 == 0) {
            printf("%s (%lu caracteres)\n", nombres[i], strlen(nombres[i]));
        }
    }
}

// Función para imprimir nombres con número impar de caracteres
void imprimir_nombres_impares(char nombres[][MAX_NAME_LENGTH], int cantidad) {
    printf("Nombres con número impar de caracteres:\n");
    for (int i = 0; i < cantidad; i++) {
        if (strlen(nombres[i]) % 2 != 0) {
            printf("%s (%lu caracteres)\n", nombres[i], strlen(nombres[i]));
        }
    }
}

int main() {
    FILE *archivo = fopen("nombres.txt", "r");
    if (!archivo) {
        printf("Error al abrir el archivo");
        return 1;
    }

    char nombres[MAX_NAMES][MAX_NAME_LENGTH];
    int cantidad = 0;

    // Leer los nombres del archivo
    while (fscanf(archivo, "%[^,],", nombres[cantidad]) != EOF && cantidad < MAX_NAMES) {
        cantidad++;
    }
    fclose(archivo);

    // Ordenar los nombres en orden alfabético descendente (Tarea del padre)
    ordenar_nombres(nombres, cantidad);
    printf("Nombres ordenados: ");
    for (int i = 0; i < cantidad; i++) {
        printf("%s", nombres[i]);
        if (i < cantidad - 1) {
            printf(", ");
        }
    }
    printf("\n");

    pid_t pid1, pid2, pid3;

    // Primer proceso hijo: Encontrar los nombres con longitud mínima y máxima
    pid1 = fork();
    if (pid1 == 0) {
        encontrar_min_max_nombres(nombres, cantidad);
        exit(0);
    }

    // Segundo proceso hijo: Imprimir nombres con longitud par
    pid2 = fork();
    if (pid2 == 0) {
        imprimir_nombres_pares(nombres, cantidad);
        exit(0);
    }

    // Tercer proceso hijo: Imprimir nombres con longitud impar
    pid3 = fork();
    if (pid3 == 0) {
        imprimir_nombres_impares(nombres, cantidad);
        exit(0);
    }

    // Esperar a que todos los procesos hijos terminen
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
