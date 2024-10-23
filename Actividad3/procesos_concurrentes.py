import time
import subprocess
import multiprocessing

def lanzar_proceso(app,tiempo_espera):
    print(f"Subproceso lanzando {app}, espera {tiempo_espera} segundos...")
    subprocess.Popen(app)
    time.sleep(tiempo_espera)
    print(f"Subproceso {app} terminado después de {tiempo_espera} segundos.")

def mostrar_lanzados_y_no_lanzados(lanzadas, no_lanzadas):
    print("\nProcesos lanzados:")
    for lanzada in lanzadas:
        print(lanzada)

    print("\nProcesos no lanzados:")
    for no_lanzada in no_lanzadas:
        print(no_lanzada)

if __name__ == "__main__":
    with open("nombres_procesos.txt") as archivo:
        texto_archivo = archivo.read()

    # Lista de procesos desde el archivo
    apps_sin_lanzar = texto_archivo.split(",")
    apps_lanzadas = []

    # Creaamos el proceso padre y lanzamos la primera app
    padre=multiprocessing.Process(target=lanzar_proceso, args=(apps_sin_lanzar[0], 1))
    padre.start()
    padre.join()# Espera a que el proceso padre termine
    apps_lanzadas.append(apps_sin_lanzar[0])
    apps_sin_lanzar.pop(0)

    # Crear el primer hijo y lanzamos la segunda app
    hijo1 = multiprocessing.Process(target=lanzar_proceso, args=(apps_sin_lanzar[0], 2))
    hijo1.start()
    hijo1.join()
    apps_lanzadas.append(apps_sin_lanzar[0])
    apps_sin_lanzar.pop(0)

    # Crear el segundo hijo y lanzamos la tercera app
    hijo2=multiprocessing.Process(target=lanzar_proceso, args=(apps_sin_lanzar[0], 3))
    hijo2.start()
    hijo2.join()
    apps_lanzadas.append(apps_sin_lanzar[0])
    apps_sin_lanzar.pop(0)

    # Crear el tercer hijo y mostramos los procesos lanzados y no lanzados
    hijo3=multiprocessing.Process(target=mostrar_lanzados_y_no_lanzados, args=(apps_lanzadas, apps_sin_lanzar))
    hijo3.start()
    hijo3.join()
