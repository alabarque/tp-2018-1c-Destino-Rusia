#include "instancia.h"

int main() {
		int coordinador_socket;
		FILE* archivoDatos;

		cargar_configuracion();

		configureLoggers(nombre_Instancia);

		coordinador_socket = conectarseA(coordinador_IP, coordinador_Puerto);
		enviarInt(coordinador_socket, INSTANCIA);
		enviarMensaje(coordinador_socket,nombre_Instancia);

		log_trace(logT,"Conectado a Coordinador OK.\n");

		recibirInt(coordinador_socket, &qEntradas);
		recibirInt(coordinador_socket, &tamanioEntrada);

		archivoDatos = inicializarPuntoMontaje(punto_Montaje, nombre_Instancia);

		tablaEntradas =  list_create();

		operacionNumero = 0;

		// TODO: levantar tabla de entradas anterior, de ser necesario

		calcularSiguienteEntrada(1);

		while(1){

			int instruccion;
			recibirInt(coordinador_socket,&instruccion);
			int cantidadEntradas;
			switch(instruccion){
				case ENVIO_ENTRADA:
					operacionNumero++;
					log_trace(logT,"Se recibe instruccion SET.\n");
					cantidadEntradas = recibirEntrada(coordinador_socket,archivoDatos);

					if(cantidadEntradas<=0){
										//TODO que hace si da error?
					}

					enviarInt(coordinador_socket,obtenerCantidadEntradasOcupadas());
					break;
				case STORE_ENTRADA:
					operacionNumero++;
						log_trace(logT,"Se recibe instruccion STORE.\n");
					ejecutarStore(coordinador_socket, archivoDatos);
					enviarInt(coordinador_socket,obtenerCantidadEntradasOcupadas());
					break;

			}


		}


		destroyLoggers();

	//}


	return 0;
}


void calcularSiguienteEntrada(int lenValue){
	switch (reemplazo_Algoritmo){

		case CIRCULAR  :
		  numEntradaActual = calculoCircular(lenValue);
		  break;
		case LRU  :
		  numEntradaActual = calculoLRU();
		  break;
		case BSU  :
		  numEntradaActual = 0; /* calculoBSU(); */
		break;
		default:
		  numEntradaActual = reemplazo_Algoritmo;
		/* Acusar error, exit_gracefully */
	}
}

/*

char* coordinador_IP;
int coordinador_Puerto;
char* reemplazo_Algoritmo;
char* punto_Montaje;
char* nombre_Instancia;
int intervalo_dump;

*/
