#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    //Para fcntl y O_* flags
#include <unistd.h>   //Para fork y sleep
#include <sys/file.h> //Para flock
#include <sys/wait.h> //Para wait

#define FILE_PATH "numeros.txt"

//Función que usamos para leer el último número en el archivo
int leer_ultimo_numero(FILE *archivo) {
    int numero = 0;

    //Leemos cada número del archivo hasta el final
    while (fscanf(archivo, "%d", &numero) != EOF);
    return numero;
}

//Función para poder escribir un nuevo número en el archivo
void escribir_numero(FILE *archivo, int numero) {
    fprintf(archivo, "%d\n", numero);
    fflush(archivo);//Aseguramos que los datos se escriban inmediatamente con fflush
}

int main() {
    //Creamos un proceso hijo
    if (fork() == 0) {
        //El proceso hijo ejecuta este bloque en bucle infinito
        while (1) {
            //Abrimos el archivo en modo lectura_escritura
            FILE *archivo = fopen(FILE_PATH, "a+");
            if (!archivo) {
                perror("Error al abrir el archivo");
                exit(1);
            }

            //Obtenemos bloqueo exclusivo del archivo para evitar que otros procesos lo usen
            if (flock(fileno(archivo), LOCK_EX) != 0) {
                perror("Error al bloquear el archivo");
                fclose(archivo);
                exit(1);
            }

            //Leemos el último número del archivo
            rewind(archivo); // Ir al inicio para leer todo el archivo
            int ultimo_numero = leer_ultimo_numero(archivo);

            //Escribimos el siguiente número en el archivo
            escribir_numero(archivo, ultimo_numero + 1);

            //Quitamos el bloqueo
            flock(fileno(archivo), LOCK_UN);
            fclose(archivo);

            //Pausamos un segundo para observar cambios más fácilmente
            sleep(1);
        }
    }

    //El proceso padre espera al hijo a pesar de que aquí el hijo está en bucle infinito
    wait(NULL);

    return 0;
}
