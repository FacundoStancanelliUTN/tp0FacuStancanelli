#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;
	const char* firstMessageToBeLogged = "Soy un log";
	char* propertyToBeLoggedFromConfig;
	const char* messageKeyToBeExtractedFromConfig = "CLAVE";
	const char* portKeyToBeExtractedFromConfig = "PUERTO";
	const char* ipKeyToBeExtractedFromConfig = "IP";

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger, firstMessageToBeLogged);

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	if (config != NULL){
		if (config_has_property(config, messageKeyToBeExtractedFromConfig)){
			propertyToBeLoggedFromConfig = config_get_string_value(config, messageKeyToBeExtractedFromConfig);
			log_info(logger, propertyToBeLoggedFromConfig);
		}
		if (config_has_property(config, portKeyToBeExtractedFromConfig)){
			puerto = config_get_string_value(config, portKeyToBeExtractedFromConfig);
			log_info(logger, "Lei el puerto %s", puerto);
		}
		if (config_has_property(config, ipKeyToBeExtractedFromConfig)){
			ip = config_get_string_value(config, ipKeyToBeExtractedFromConfig);
			log_info(logger, "Lei la ip %s", ip);
		}
	}

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
	//enviar_mensaje(propertyToBeLoggedFromConfig, conexion);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	return log_create("tp0.log", "tp0", true, LOG_LEVEL_INFO);
}

t_config* iniciar_config(void)
{
	return config_create("tp0.config");
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");
	while (strcmp(leido, "") != 0){
		log_info(logger, leido);
		leido = readline("> ");
	}
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();
	leido = readline(">2 ");
		while (strcmp(leido, "") != 0){
			agregar_a_paquete(paquete, leido, strlen(leido));
			leido = readline(">2 ");
		}
		enviar_paquete(paquete, conexion);

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
