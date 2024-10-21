
import time
import subprocess

def lanzar_procesos(app,time_app):
    print("Subproceso ejecutándose...",time_app-1)
    subprocess.Popen(app)  # Inicia el proceso sin bloquea
    time.sleep(time_app)
    print("Subproceso 1 terminado")

def mostrar_lanzados_y_no_lanzados(lanzadas,no_lanzadas):
    for lanzada in lanzadas:
        print("lanzada: ",lanzada)

    for no_lanzada in no_lanzadas:
        print("no lanzadas: ",no_lanzada)
    

if __name__ == "__main__":
    archivo = open("nombres_procesos.txt")
    texto_archivo=archivo.read()
    print(texto_archivo)

    apps_sin_lanzar=texto_archivo.split(",")
    apps_lanzadas=[]

    print(apps_sin_lanzar)
    # Crear procesos
    
    for i in range(0,3,1):
        lanzar_procesos(apps_sin_lanzar[i],i+1)
        apps_lanzadas.append(apps_sin_lanzar[i])
        apps_sin_lanzar.remove(apps_sin_lanzar[i])

    mostrar_lanzados_y_no_lanzados(apps_lanzadas,apps_sin_lanzar)


    