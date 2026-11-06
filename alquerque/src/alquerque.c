// INCLUSION DE LAS LIBRERIAS USADAS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include<unistd.h>
#include <gtk/gtk.h>


// DEFINICION DE VARIABLES NUMERICAS Y BOOLEANAS
#define PC 0
#define PERSONA 1
#define SIN_VICTORIA 0
#define VICTORIA_BLANCAS 1
#define VICTORIA_NEGRAS 2
#define PLAY_AGAIN 1
#define TURNO_BLANCAS 0
#define TURNO_NEGRAS 1
#define FALSO 0
#define VERDADERO 1
#define VACIO -1
#define ES_CORRECTO 0
#define ERROR_SEMANTICA 1
#define ERROR_SINTAXIS 2

// DIRECCIONES IMAGENES GTK
#define CIRCULO_NEGRO "Images/negro circulo.png"
#define CIRCULO_BLANCO "Images/blanco circulo.png"
#define CIRCULO_VACIO "Images/vacío.png"
#define CIRCULO_MARCADO_NEGRO "Images/marcado negro circulo.png"
#define CIRCULO_MARCADO_BLANCO "Images/marcado blanco circulo.png"
#define CIRCULO_MARCADO_VACIO "Images/marcado vacío.png"

// DEFINICION DE CHARS UTILIZADOS PARA LA IMPRESION DE LA TABLA EN EL PROGRAMA
#define CHAR_BLANCO '@'
#define CHAR_NEGRO  'O'
#define CHAR_VACIO  ' '

// DEFINICION DE LOS MENSAJES
#define PEDIR_MODO "Seleccione el modo de juego:\n[P]C vs PC\n[S]ingle Player\n[M]ultiplayer\nRespuesta: "
#define ASK_COLOUR "Elija el color con el que jugara:\n[B]lancas\n[N]egras\n\nRespuesta: "
#define ASK_ORDEN "Elija el orden de los turnos:\n[B]lancas primero\n[N]egras primero\n[R]andom\n\nRespuesta: "
#define ASK_PLAYAGAIN "Quiere jugar de nuevo?\n[S]i\n[N]o\n\nRespuesta: "

/* DECLARACION DE VARIABLES GLOBALES
 * 	jBLanco y jNegro 			 -> hacemos referencia a quién le toca las fichas blancas o negras. Ej.: jBlanco es la PC (0)
 * 	fichasBlancas y fichasNegras -> nro. de fichas en cada momento de cada jugador durante el juego
 * 	turno 						 -> hace referencia al jugardor a quien le toca jugar en ese momento
 * 	tablero[5][6]				 -> estructura de la tabla donde se juega
*/
char jBlanco = VACIO, jNegro = VACIO, fichasBlancas = 12, fichasNegras = 12, turno = VACIO;
char miColor = CHAR_VACIO, empiezaColor = CHAR_VACIO, modo_juego = CHAR_VACIO;

char tablero[5][6];

//				= {
//	{CHAR_NEGRO,CHAR_NEGRO,CHAR_NEGRO,CHAR_NEGRO,CHAR_NEGRO,'\0'},
//	{CHAR_NEGRO,CHAR_NEGRO,CHAR_NEGRO,CHAR_NEGRO,CHAR_NEGRO,'\0'},
//	{CHAR_NEGRO,CHAR_NEGRO,CHAR_VACIO,CHAR_BLANCO,CHAR_BLANCO,'\0'},
//	{CHAR_BLANCO,CHAR_BLANCO,CHAR_BLANCO,CHAR_BLANCO,CHAR_BLANCO,'\0'},
//	{CHAR_BLANCO,CHAR_BLANCO,CHAR_BLANCO,CHAR_BLANCO,CHAR_BLANCO,'\0'}
//};

typedef struct posiblePlay{
	char coordenada[13][2];
	unsigned int len;
} posiblePlay;

posiblePlay posibleJugada =
{
	.coordenada ={
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1},
			{-1,-1}
	}, .len = 0
};

gchar stringJugador1[30];
gchar stringJugador2[30];
guint i,j;
GtkWidget *imagen;

// ventanaBienvenida
GtkWidget * ventanaBienvenida;
GtkWidget * box1_ventanaBienvenida;
GtkWidget * menubar2;
GtkWidget * menuitem5;
GtkWidget * menuitem6;
GtkWidget * menuitem7;
GtkWidget * menuitem8;
GtkWidget * separator2;
GtkWidget * fixed_ventanaBienvenida;
GtkWidget * box2_ventanaBienvenida;
GtkWidget * bienvenida; // label sin modificar
GtkWidget * box3_ventanaBienvenida;
GtkWidget * boton_jugar;
GtkWidget * boton_ajustes;
GtkWidget * boton_salir1;
GtkWidget * boton_creditos;
GtkWidget * statusbar2;

//ventanaCreditos
GtkWidget * ventanaCreditos;
GtkWidget * boton_volver_creditos;

//ventanaAjustes
GtkWidget * ventanaAjustes;
GtkWidget * boton_volver_ajustes;

// ventanaElegirModo1
GtkWidget * ventanaElegirModo1;
GtkWidget * menubar5;
GtkWidget * separator5;
GtkWidget * fixed_ventanaElegirModo1;
GtkWidget * statusbar6;
GtkWidget * menuitem17;
GtkWidget * menuitem18;
GtkWidget * menuitem19;
GtkWidget * menuitem20;
GtkWidget * menu13;
GtkWidget * menu14;
GtkWidget * imagemenuitem46;
GtkWidget * imagemenuitem47;
GtkWidget * imagemenuitem48;
GtkWidget * imagemenuitem49;
GtkWidget * menu15;
GtkWidget * imagemenuitem50;
GtkWidget * box2_ventanaElegirModo1;
GtkWidget * statusbar6;
GtkWidget * elijaElModoDeJuego;
GtkWidget * grid1_ventanaElegirModo1;
GtkWidget * box3_ventanaElegirModo1;
GtkWidget * box4_ventanaElegirModo1;
GtkWidget * modo; // label sin modificar
GtkWidget * colorDeMiFicha; // label sin modificar
GtkWidget * empiezaElColor; // label sin modificar
GtkWidget * nombreJugador1; // label sin modificar
GtkWidget * nombreJugador2; // label sin modificar
GtkWidget * label_mensajes_ventanaElegirModo1;
GtkWidget * box4_ventanaElegirModo1;
GtkWidget * grid2_ventanaElegirModo1;
GtkWidget * grid3_ventanaElegirModo1;
GtkWidget * grid4_ventanaElegirModo1;
GtkWidget * entry_nombreJugador1;
GtkWidget * entry_nombreJugador2;
GtkWidget * boton_enter_modo;
GtkWidget * boton_singleplayer;
GtkWidget * boton_multiplayer;
GtkWidget * boton_PCvsPC;
GtkWidget * boton_miColorBlanco;
GtkWidget * boton_miColorNegro;
GtkWidget * boton_miColorRandom;
GtkWidget * boton_empiezaBlanco;
GtkWidget * boton_empiezaNegro;
GtkWidget * boton_empiezaRandom;
GtkWidget * boton_volver_modo;
GtkWidget * boton_random;

// ventanaJuego
GtkWidget * ventanaJuego;
GtkWidget * label_nombreJNegro;
GtkWidget * label_nombreJBlanco;
GtkWidget * label_nroFichaNegras;
GtkWidget * label_nroFichaBlancas;
GtkWidget * box1_ventanaJuego;
GtkWidget * box2_ventanaJuego;
GtkWidget * box3_ventanaJuego;
GtkWidget * fixed_ventanaJuego;
GtkWidget * grid1_ventanaJuego;
GtkWidget * box4_ventanaJuego;
GtkWidget * box5_ventanaJuego;
GtkWidget * box6_ventanaJuego;
GtkWidget * grid2_ventanaJuego;
GtkWidget * boton_enter_jugar;
GtkWidget * label_mensajes_ventanaJuego;
GtkWidget * label_jugada;
GtkWidget * eventBox_tablero;
GtkWidget * label_vaGanando;
GtkWidget * label_turnoActual;
GtkWidget * label_modoDeJuego;

// ventanaVictoria
GtkWidget * ventanaVictoria;
GtkWidget * box1_ventanaVictoria;
GtkWidget * fixed_ventanaVictoria;
GtkWidget * box2_ventanaVictoria;
GtkWidget * label_mensajeDeVictoria;
GtkWidget * box3_ventanaVictoria;
GtkWidget * boton_volverAjugar;
GtkWidget * boton_salir2;
GtkWidget * boton_menu;

GtkWidget *GTKtablero;
GtkWidget *box_tablero;

void generarJugadaPC();
void actualizarVentanaJuego();
void chooseMode(char, char , char );


/* Limpia el buffer de teclado
 * Utilizado en la funcion: checkAnswer()
 * Parametros: nada
 * Return: nada (es void)
 */
void cleanBuffer()
{
 	char c;
	while ((c = getchar()) != '\n');
}

/* Se resetean los valores de tablero[5][6] (global)
 * Utilizadon en el main()
 * Parametros: nada
 * Return: nada (es void)
 */
void resetTablero()
{
	// Se resetean la posición de cada ficha en la tabla
	int j = 0,i = 0;
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5;j++)
		{
			if (i < 2)
				tablero[i][j] = CHAR_NEGRO;
			else if (i == 2)
			{
				if(j < 2)
					tablero[i][j] = CHAR_NEGRO;
				else if (j > 2)
					tablero[i][j] = CHAR_BLANCO;
				else
					tablero[i][j] = CHAR_VACIO;
			}
			else
				tablero[i][j] = CHAR_BLANCO;
		}
		tablero[i][j] = '\0'; // al final de cada fila (en la ultima columna) se pone el \0
	}
}

/* Se verifica si la respuesta ingresada por teclado forma parte de la cadena respuestasP[]
 * Esto se repite hasta que la respuesta sea igual a uno de los valores de respuestasP[]
 * Utilizado en las funciones: askPlayAgain() y chooseMode()
 * Parametros:
 * 	mensaje[]	  -> mensaje que se mostrara por pantalla antes de pedir la respuesta (ej.: PEDIR_MODO -> cadena global)
 * 	respuestasP[] -> contiene las respuestas validas
 * 	nRespuestas	  -> longitud de respuestasP[]
 * Return: tipo char
 * 	respuesta -> contiene uno de los elementos de respuestasP[]
 */
char checkAnswer(char mensaje[], char respuestasP[], int nRespuestas)
{

	// quedarse: actua como bandera del while
	// respuesta: almacenara el caracter introducido por teclado
	char respuesta, quedarse = VERDADERO;

	// Pide la respuesta a la persona hasta que su valor esté dentro de respuestaP[]"
	do
	{
		printf("%s", mensaje);
		respuesta = getchar();
		cleanBuffer();
		respuesta = toupper(respuesta);
		// Se recorre nRespuestas[] para verificar si el contenido de respuesta se encuentra dentro
		for(int i = 0; i < nRespuestas; i++)
		{
			if(respuesta == respuestasP[i] )
			{
				quedarse = FALSO; // Si "respuesta" está dentro de "nRespuestas[]", entonces se habilita la salida del while
				break;
			}
		}
		puts("");
	}
	while(quedarse);

	return respuesta; // Devuelve uno de los elementos de "respuestasP[]"
}

/* Pregunta si se quiere volver a jugar o no
 * Utilizado en la funcion: main()
 * Parametros: nada
 * Return: tipo char
 * 	 PLAY_AGAIN (1) -> si la funcion checkAnswer() retorna 'S'
 * 	!PLAY_AGAIN (0) -> si la funcion checkAnswer() retorna 'N'
 */
char askPlayAgain()
{
	char respuestasPosibles[] = {'S','N'};

	return checkAnswer(ASK_PLAYAGAIN, respuestasPosibles, 2) == 'S' ? PLAY_AGAIN : !PLAY_AGAIN;
}

/* Verificamos si llegamos o no a una victoria
 * Tres casos posibles: no ha ganado nadie, gano el jugador blanco o gano el jugador negro
 * Utilizado en la funcion: play()
 * Parametros: nada
 * Return: tipo char
 *	VICTORIA_NEGRAS  (2) -> si el jugador con fichas blancas se queda sin fichas, es decir, si fichasBlancas == 0
 *	VICTORIA_BLANCAS (1) -> si el jugador con fichas negras se queda sin fichas, es decir, si fichasNegras == 0
 *	SIN_VICTORIA	 (0) -> si todavia no hay jugador cuyo numero de fichas sea 0
 */
char askVictory()
{
	if (fichasBlancas == 0)
		return VICTORIA_NEGRAS;
	else if (fichasNegras == 0)
		return VICTORIA_BLANCAS;
	else
		return SIN_VICTORIA;
}

/* Se solicitar el modo de juego (PERSONA vs PC (Singleplayer), PC vs PC o PERSONA vs PERSONA (Multiplayer))
 * Utilizado en la funcion: main()
 * Tambien se elige que color de ficha empieza moviendo
 * Modificacion de globales: (una de las dos posibilidades dependiendo de lo que elija la persona)
 * 	jBlanco y jNegro -> PERSONA (1)
 * 					 -> PC (0)
 * 	turno -> TURNO_BLANCAS (0)
 * 		  -> TURNO_NEGRAS  (1)
 * Parametros: nada
 * Return: nada (es void)
 */
void chooseMode(char miColor, char empiezaColor, char modo_juego)
{
//	char respuesta, respuestasModo[] = {'P','S','M'}, respuestasColor[]={'B','N'}, respuestasOrden[] = {'B','N','R'};

	// Preguntamos si se quiere jugar Singleplayer (PERSONA vs PC), PC vs PC o Multiplayer (PERSONA vs PERSONA)
//	respuesta = checkAnswer(PEDIR_MODO, respuestasModo, 3);

	// Si el modo de juego es 'R' (random), asignamos de forma random a modo_juego: 'P', 'S' o 'M'

	if (modo_juego == 'P') // PC vs PC
		jBlanco = jNegro = PC;
	else if (modo_juego == 'M') // Multiplayer
		jBlanco = jNegro = PERSONA;
	else // Singleplayer
	{
		// Si es Singleplayer, entonces se pregunta qué color de piezas se quiere ser y, dependiendo de la respuesta,
		// se asignan los valores a jBlanco y jNegro (a quien le toca cada ficha)

//		respuesta = checkAnswer(ASK_COLOUR, respuestasColor, 2);

		if (miColor == 'B')
		{
			jBlanco = PERSONA;
			jNegro = PC;
		}
		else if (miColor == 'N')
		{
			jBlanco = PC;
			jNegro = PERSONA;
		}
		else // miColor == 'R'
		{
			char aux = rand() % 2;
			if (aux == 1)
			{
				jBlanco = PERSONA;
				jNegro = PC;
			}
			else
			{
				jBlanco = PC;
				jNegro = PERSONA;
			}
		}
    }

	// Preguntamos quién empieza primero (negras, blancas o random)
//    respuesta = checkAnswer(ASK_ORDEN, respuestasOrden, 3);
    if (empiezaColor == 'B') {
		// El turno actual corresponde al jugador cuyas fichas son las blancas
        turno = TURNO_BLANCAS;
    } else if (empiezaColor == 'N') {
		// El turno actual corresponde al jugador cuyas fichas son las negras
    	turno = TURNO_NEGRAS;
    } else {
		// El turno actual corresponde a un jugador random
    	turno = rand()%2;
    }

}

/* Se imprime la tabla completa en su estado actual
 * Utilizado en la funcion: play()
 * Parametros: nada
 * Return: nada (es void)
 */
void printTable()
{
	// Matriz que muestras los caminos posibles para cada ficha dentro de la tabla
	// Será utilizada en una función para graficar la tabla entera
	const char caminosTablero[5][10] = {"|\\|/|\\|/|", "|/|\\|/|\\|", "|\\|/|\\|/|", "|/|\\|/|\\|"};

	// Se recorre tablero[5][6]
    printf("\n  0 1 2 3 4\n");
	for(int i = 0; i < 5; i++)
	{
        printf("%i ", i);
		for(int j = 0; j < 5; j++)
		{
			// Imprime CHAR_BLANCO, CHAR_NEGRO o CHAR_VACIO dependiendo del valor de tablero[i][j]
			printf("%c", tablero[i][j]);
			printf("%c", j < 4 ? '-' : '\n');
		}
		printf("  %s\n", caminosTablero[i]);
	}
	printf("Fichas Blancas: %i\tFichas Negras: %i\n\n", fichasBlancas, fichasNegras);
}

/* Revisa si cada caracter de la cadena es un numero
 * Utilizado en la funcion: revisar_Syntax_Cad()
 * Parametros:
 * 	&str -> direccion que contiene la cadena donde esta la jugada ingresada
 * Return: tipo int
 * 	FALSO (0) 	  -> si no todos los caracteres son numeros o no hay numeros
 * 	VERDADERO (1) -> si todos los caracteres son numeros
 */
int isNumeric(char* str)
{
    // printf("%s",str);
    while(VERDADERO)
    {
        // printf("%c\n",*str);
        if(*str == '\0')
        	break;

        if(isdigit(*str) == FALSO)
            return FALSO;

        str++;
    }

    // printf("Es numerico\n\n");
    return VERDADERO;

}

/* Se revisa si la posicion esta dentro del rango, si no esta, se retorna FALSO
 * Utilizado en la funcion: revisar_Syntax_Cad()
 * Parametros:
 * 	int num -> numero a ser analizado
 * 	int min -> valor minimo del intervalo cerrado
 * 	int max -> valor maximo del intervalo cerrado
 * Return: tipo int
 * 	FALSO (0) -> si num no forma parte del intervalo cerrado [min, max]
 * 	VERDADERO (1) -> si num forma parte del intervalo cerrado [min, max]
 */
int dentroRangoInclusive(int num, int min, int max)
{
	if (num <= max && num >= min)
		return VERDADERO;
	else
		return FALSO;
}

/* Revisa si el movimiento en diagonal es valido
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 * 	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere mover
 * 	char coord_sgte[3] 	-> contiene la posicion a la que se quiere llegar
 * 	coord_comido[3]		-> incialmente vacio; se modifica si hay alguna ficha entre coord_actual y coord_sgte
 * Return:
 * 	FALSO 		-> si la ficha no puede realizar el movimiento diagonal
 * 	VERDADERO   -> si la ficha puede realizar el movimiento diagonal
 */
int mov_diagonal_cuadrantes(char aux[5][6], char coord_actual[3], char coord_sgte[3], char coord_comido[3])
{
	// Movimiento hacia el 2do cuadrante
	if ((coord_sgte[0] == coord_actual[0] - 2 && coord_sgte[1] == coord_actual[1] - 2))
	{
		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_sgte[0] - '0' + 1][coord_sgte[1] - '0' + 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0]  + 1;
				coord_comido[1] =  coord_sgte[1] + 1;
			}
		}
		else if (aux[coord_sgte[0] - '0' + 1][coord_sgte[1] - '0' + 1] != CHAR_BLANCO)
		{
			return FALSO;
		}
		else
		{
			coord_comido[0] = coord_sgte[0] + 1;
			coord_comido[1] =  coord_sgte[1]  + 1;
		}
	}
	// Movimiento hacia el 1er cuadrante
	else if ((coord_sgte[0] == coord_actual[0] + 2 && coord_sgte[1] == coord_actual[1] - 2))
	{
		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_sgte[0] - '0' - 1][coord_sgte[1] - '0' + 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0] - 1;
				coord_comido[1] =  coord_sgte[1] + 1;
			}
		}
		else
		{
			if (aux[coord_sgte[0] - '0' - 1][coord_sgte[1] - '0' + 1] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0] - 1;
				coord_comido[1] =  coord_sgte[1] + 1;
			}
		}

	}
	// Movimiento hacia el 3er cuadrante
	else if ((coord_sgte[0] == coord_actual[0] - 2 && coord_sgte[1] == coord_actual[1] + 2))
	{
		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_sgte[0] - '0' + 1][coord_sgte[1] - '0' - 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0] + 1;
				coord_comido[1] =  coord_sgte[1] - 1;
			}
		}
		else
		{
			if (aux[coord_sgte[0] - '0' + 1][coord_sgte[1] - '0' - 1] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0] + 1;
				coord_comido[1] =  coord_sgte[1] - 1;
			}
		}
	}
	// Movimiento hacia el 4to cuadrante
	else if ((coord_sgte[0] == coord_actual[0] + 2 && coord_sgte[1] == coord_actual[1] + 2))
	{
		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_sgte[0] - '0' - 1][coord_sgte[1] - '0' - 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_sgte[0] - 1;
				coord_comido[1] =  coord_sgte[1] - 1;
			}
		}
		else if (aux[coord_sgte[0] - '0' - 1][coord_sgte[1] - '0' - 1] != CHAR_BLANCO)
		{
			return FALSO;
		}
		else
		{
			coord_comido[0] = coord_sgte[0] - 1;
			coord_comido[1] =  coord_sgte[1] - 1;
		}
	}
	return VERDADERO; // El movimiento en diagonal es valido
}

/* Verifica si la ficha seleccionada (mediante la posicion) es del color del jugador cuyo turno corresponde
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 * 	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere revisar
 * Return:
 * 	FALSO 		-> si la ficha no concuerda con el turno
 * 	VERDADERO   -> si la ficha concuerda con el turno
 */
int coincide_ficha_turno(char aux[5][6], char coord_actual[3])
{
	if (turno == TURNO_BLANCAS && aux[coord_actual[0]-'0'][coord_actual[1]-'0'] != CHAR_BLANCO)
		return FALSO;

	if(turno == TURNO_NEGRAS && aux[coord_actual[0]-'0'][coord_actual[1]-'0'] != CHAR_NEGRO)
		return FALSO;

	return VERDADERO;
}

/* Verifica si el movimiento VERTICAL es valido
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 *	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere mover
 * 	char coord_sgte[3] 	-> contiene la posicion a la que se quiere llegar
 * 	coord_comido[3]		-> incialmente vacio; se modifica si hay alguna ficha entre coord_actual y coord_sgte
 * 	&mov_doble			-> 	FALSO 	  -> la cadena debe ser unicamente de 1 movimiento
 * 			  				VERDADERO -> la cadena es de +1 movimiento
 * Return:
 * 	FALSO 		-> si la ficha no puede realizar el movimiento sobre el eje y
 * 	VERDADERO   -> si la ficha puede realizar el movimiento sobre el eje y
 */
int mov_eje_Y(char aux[5][6], char coord_sgte[3], char coord_comido[3], char coord_actual[3], int *mov_doble)
{
	if(abs(coord_actual[0] - coord_sgte[0]) == 1) // Se movio 1 paso hacia arriba o abajo
	{
		if (*mov_doble)
			return FALSO;
	}
	else if ((coord_actual[0] - coord_sgte[0]) == 2) // Se movio 2 pasos hacia arriba
	{
		*mov_doble = VERDADERO;

		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_actual[0] - '0' - 1][coord_actual[1] - '0'] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0] - 1;
				coord_comido[1] =  coord_actual[1];
			}
		}
		else
		{
			if (aux[coord_actual[0] - '0' - 1][coord_actual[1] - '0'] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0]  - 1;
				coord_comido[1] =  coord_actual[1] ;
			}
		}
	}
	else if ((coord_actual[0] - coord_sgte[0]) == -2) // Se movio 2 pasos hacia abajo
	{
		*mov_doble = VERDADERO;

		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_actual[0] - '0' + 1][coord_actual[1] - '0'] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0]  + 1;
				coord_comido[1] = coord_actual[1] ;
			}
		}
		else
		{
			if (aux[coord_actual[0] - '0' + 1][coord_actual[1] - '0'] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0]+1;
				coord_comido[1] =  coord_actual[1];
			}
		}
	}
	else // Si se mueve una distancia mayor entonces está mal
	{
		return FALSO;
	}

	return VERDADERO;
}

/* Verifica si el movimiento HORIZONTAL es valido
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 *	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere mover
 * 	char coord_sgte[3] 	-> contiene la posicion a la que se quiere llegar
 * 	coord_comido[3]		-> incialmente vacio; se modifica si hay alguna ficha entre coord_actual y coord_sgte
 * 	&mov_doble			-> 	FALSO 	  -> la cadena debe ser unicamente de 1 movimiento
 * 			  				VERDADERO -> la cadena es de +1 movimiento
 * Return:
 * 	FALSO 		-> si la ficha no puede realizar el movimiento sobre el eje x
 * 	VERDADERO   -> si la ficha puede realizar el movimiento sobre el eje x
 */
int mov_eje_X(char aux[5][6], char coord_sgte[3], char coord_comido[3], char coord_actual[3], int *mov_doble)
{
	if(abs(coord_actual[1] - coord_sgte[1]) == 1) // Se movio 1 paso hacia la izquierda o derecha
	{
		if (*mov_doble)
			return FALSO;
	}
	else if ((coord_actual[1] - coord_sgte[1]) == 2) // Se movio 2 pasos hacia la izquierda
	{
		*mov_doble = VERDADERO;

		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_actual[0] - '0'][coord_actual[1] - '0' - 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0];
				coord_comido[1] =  coord_actual[1]-1;
			}
		}
		else
		{
			if (aux[coord_actual[0] - '0'][coord_actual[1] - '0' - 1] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0];
				coord_comido[1] =  coord_actual[1]-1;
			}
		}
	}
	else if ((coord_actual[1] - coord_sgte[1]) == -2) // Se movio 2 pasos hacia la derecha
	{
		*mov_doble = VERDADERO;

		if (turno == TURNO_BLANCAS)
		{
			if (aux[coord_actual[0] - '0'][coord_actual[1] - '0' + 1] != CHAR_NEGRO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0];
				coord_comido[1] =  coord_actual[1]+1;
			}
		}
		else
		{
			if (aux[coord_actual[0] - '0'][coord_actual[1] - '0' + 1] != CHAR_BLANCO)
				return FALSO;
			else
			{
				coord_comido[0] = coord_actual[0];
				coord_comido[1] =  coord_actual[1]+1;
			}
		}
	}
	else // Si se mueve una distancia mayor entonces está mal
	{
		return FALSO;
	}

	return VERDADERO;
}

/* Se copia en aux[5][6] el movimiento realizado
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 *	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	coord_actual[3] 	-> contiene la posicion de la ficha que se quiere mover
 * 	char coord_sgte[3] 	-> contiene la posicion a la que se quiere llegar
 * 	coord_comido[3]		-> incialmente vacio (\0); se modifica si hay alguna ficha entre coord_actual y coord_sgte
 * 	&mov_doble			-> 	FALSO 	  -> la cadena debe ser unicamente de 1 movimiento
 * 			  				VERDADERO -> la cadena es de +1 movimiento
 * Return: nada (void)
 */
void cargar_movEn_aux(char aux[5][6], char coord_sgte[3], char coord_comido[3], char coord_actual[3], int *mov_doble,int *aux_fichasBlancas,int *aux_fichasNegras)
{
	aux[coord_actual[0] - '0'][coord_actual[1] - '0'] = CHAR_VACIO;

	if (turno == TURNO_BLANCAS)
		aux[coord_sgte[0] - '0'][coord_sgte[1] - '0'] = CHAR_BLANCO;
	else
		aux[coord_sgte[0] - '0'][coord_sgte[1] - '0'] = CHAR_NEGRO;

	if (*mov_doble && coord_comido[0] != '\0' && coord_comido[1] != '\0')
	{
		aux[coord_comido[0] - '0'][coord_comido[1] - '0'] = CHAR_VACIO;
		if(turno == TURNO_BLANCAS)
			(*aux_fichasNegras)--;
		else
			(*aux_fichasBlancas)--;
	}
}

/* Si llegamos al final de la cadena str_respuesta, se copia en tablero[5][6] tdo el contenido de aux[5][6]
 * Utilizado en la funcion: revisar_Semantica_Y_Carga()
 * Parametros:
 *	aux[5][6] 			-> matriz auxiliar donde se realizan las pruebas de movimiento
 * 	&str_respuesta		-> direccion de str_respuesta (cadena con la jugada entera)
 * Return:
 * 	FALSO: si todavia no se llego al final de la cadena str_respuesta
 * 	VERDADERO: si ya se llego al final de la cadena str_respuesta. Se utiliza para salir del while de revisar_Semantica_Y_Carga()
 */
int cargar_auxEn_tablero(char aux[5][6], char *str_respuesta)
{
	if(*str_respuesta == '\n')
	{

		for(int i = 0; i < 5; i++)
			strncpy(tablero[i], aux[i], 5);

		// Si llegamos hasta aca y no dio FALSO en ningun lugar, entonces tdo esta correcto y
		// mandamos VERDADERO para que salga del while
		return VERDADERO;
	}
	else
		return FALSO; // Todavia no se llego al final de la cadena str_respuesta
}

/* Busca si existe algun movimiento invalido dentro de la cadena que contiene la jugada (lo que apunta str_respuesta)
 * Si el movimiento analizado es valido, entonces carga a la matriz auxiliar la jugada
 * Si no es posible, entonces no carga nada a la matriz y devuelve FALSO
 * Si se llega sin problemas al final de la cadena que contiene la jugada, entonces se copian todos los elementos de la matriz
 * auxiliar a tablero[5][6] (global) mediante la funcion cargar_movEn_tablero()
 * Parametros:
 *  char *str_respuesta -> contiene la cadena con la jugada ingresada
 * Return: tipo int
 * 	FALSO (0) -> si se encuentra algun movimiento invalido dentro de lo que apunta str_respuesta
 * 	VERDADERO (1) -> si todos los movimientos dentro de lo que apunta str_respuesta son validos
 */
int revisar_Semantica_Y_Carga(char *str_respuesta)
{
	// Matriz auxiliar que contendra el tablero con sus ultimos cambios
    char aux[5][6];

    int aux_fichasNegras = 0, aux_fichasBlancas = 0;

    /* mov_doble: FALSO -> la cadena debe ser unicamente de 1 movimiento
     * 			  VERDADERO -> la cadena es de +1 movimiento
     * diagonalPitagoras: 2 -> movimiento de un solo paso
     * 					  8 -> movimiento de doble paso
     * mov_diag_habilitado: FALSO -> la ficha en coord_actual no puede moverse en diagonal
     * 						VERDADERO -> la ficha en coord_actual puede moverse en diagonal
     */
    int mov_diag_habilitado = FALSO, mov_doble = FALSO, diagonalPitagoras;

    /* Con respecto a la matriz aux[5][6] y la cadena a la que apunta str_respuesta:
     * 	coord_actual[3]: cadena de 3 elementos que contendra la posicion actual de la cadena que apunta str_respuesta
     * 	coord_sgte[3]: cadena de 3 elementos que contendra la posicion del primer/unico movimiento de la cadena que apunta str_respuesta
     * 	coord_comido[3]: cadena de 3 elementos que contendra la posicion de la ficha que ha sido comida
	 */
    char coord_actual[3], coord_sgte[3], coord_comido[3];
    coord_actual[2] = coord_sgte[2] = coord_comido[2] = '\0';

    // Copiamos el contenido de cada fila de tablero a las filas de aux
	for (int i = 0; i < 5; i++)
		strncpy(aux[i], tablero[i], 6);

	// Se almacena en coord_actual la posicion actual de la ficha
    strncpy(coord_actual, str_respuesta, 2*sizeof(char));

    // Cambiamos donde apunta str_respuesta a donde empieza el 1er movimiento
    str_respuesta += 3;

    // Se almacena en coord_sgte el primer/unico movimiento de str_respuesta
    strncpy(coord_sgte, str_respuesta, 2);

    // Se analiza cada movimiento de la cadena apuntada por str_respuesta
    // Apenas se encuentra un movimiento invalido y sale de la funcion devolviendo FALSO
    while (VERDADERO)
    {
    	// Reseteo de variables
        mov_diag_habilitado = FALSO;
        coord_comido[0] = coord_comido[1] = '\0';

        // Verifica si la ficha seleccionada (mediante la posicion) es del color del jugador cuyo turno corresponde
        if ( !(coincide_ficha_turno(aux, coord_actual)) )
        	return FALSO;

        // Verificamos si existe movimiento, es decir, si es que el primer movimiento es distinto a la posicion actual
        if (coord_actual[0] == coord_sgte[0] && coord_actual[1] == coord_sgte[1])
            return FALSO;

        // Verificamos si el espacio al que se quiere mover esta vacio
        if (aux[coord_sgte[0] - '0'][coord_sgte[1] - '0'] != ' ')
            return FALSO;

        /* Verificamos si la ficha actual se encuentra en la diagonal principal, secundaria o en uno de los puntos
         * medios de los lados. Si se cumple una de las condiciones, tiene habilitado para moverse en todas las direcciones
         * Si ninguno se cumple, entonces la ficha solo se puede mover horizontal y verticalmente.
         */
        if (coord_actual[0] == coord_actual[1] || (coord_actual[0]-'0' + coord_actual[1] - '0') == 4 ||
        		(coord_actual[0] == '0' && coord_actual[1] == '2') || (coord_actual[0] == '2' && coord_actual[1] == '0') ||
						(coord_actual[0] == '2' && coord_actual[1] == '4') || (coord_actual[0] == '4' && coord_actual[1] == '2'))
            mov_diag_habilitado = VERDADERO;

        // Se verifica si el movimiento es diagonal
        if (coord_actual[0] != coord_sgte[0] && coord_actual[1] != coord_sgte[1])
            if (!mov_diag_habilitado)
                return FALSO;
            else // Para lo sgte. damos por hecho de que la ficha actual puede realizar un movimiento en diagonal en su posicion actual
            {
                // Si la diagonal por pitagoras da 2 significa que son catetos de lado 1, si da 8 son catetos de lado 2,
            	// cualquier otro numero es invalido
                diagonalPitagoras = (int) (pow(coord_sgte[0]- coord_actual[0] , 2) + pow(coord_sgte[1] - coord_actual[1], 2));

                // Si el sgte movimiento es de un solo paso y el movimiento anterior fue de doble paso, entonces la jugada es invalida
                if(diagonalPitagoras == 2) // Movimiento de un solo paso (si el cuadrado de la distancia es un 2)
                {
                	if (mov_doble) // Si anteriormente ya se hizo un movimiento doble
                		return FALSO;
                }
                else if (diagonalPitagoras == 8) // Movimiento de doble paso (si el cuadrado de la distancia es un 8)
                {
                    mov_doble = VERDADERO;

                    // Se buscan movimientos diagonales INVALIDOS
                    // Como diagonalPitagoras == 8, sabemos que entre coord_sgte y coord_actual hay una ficha

                    if ( !(mov_diagonal_cuadrantes(aux, coord_actual, coord_sgte,coord_comido)) )
                    	return FALSO;
                }
                else
                	return FALSO;
            }
        // Se verifica si el movimiento es sobre el eje x o y
        else if (coord_actual[0] != coord_sgte[0]) // Movimiento sobre el eje Y
        {
            if ( !(mov_eje_Y(aux, coord_sgte, coord_comido, coord_actual, &mov_doble)) )
            	return FALSO;
        }
        else // Movimiento sobre el eje X
        {
        	if ( !(mov_eje_X(aux, coord_sgte, coord_comido, coord_actual, &mov_doble)) )
        		return FALSO;
        }

        // Al llegar hasta aqui, sabemos que el movimiento es valido
        // Por lo tanto, cargamos el movimiento en aux
        cargar_movEn_aux(aux, coord_sgte, coord_comido, coord_actual, &mov_doble, &aux_fichasBlancas, &aux_fichasNegras);

        // Nos movemos 2 caraceteres por delante, el cual puede ser una, o un enter
        str_respuesta += 2;

        // En el caso de que mov_doble sea falso, significa que no puede existir otro movimiento
        // Despues del primero, por lo que si el siguiente caracter es una coma en lugar de
        // un enter, directamente la jugada es inválida
        if(*str_respuesta == ',' && mov_doble == FALSO)
            return FALSO;

        // Si llegamos al final de la cadena, salimos del while; caso contrario, se continua analizando la sgte. jugada
        // Se carga a la matriz trablero (original) la jugada entera
        if (cargar_auxEn_tablero(aux, str_respuesta)){
        	fichasNegras += aux_fichasNegras;
        	fichasBlancas += aux_fichasBlancas;
        	break;
        }

        // Copiamos el valor del siguiente en el actual, ya que es ahi
        // donde se encuentra actualmente nuestra ficha
        strcpy(coord_actual, coord_sgte);

        // Verificamos que el siguiente termino, el cual debe ser o una coma o un enter
        str_respuesta++;

        // Cargamos la sgte posicion de str_respuesta a coord_sgte
        strncpy(coord_sgte, str_respuesta, 2);
    }
    return VERDADERO;
}

/* Revisa si la sintaxis de la cadena ingresada es correcta
 * Ej. de cadena valida: 33:21,20,11,05
 * Utilizada en la funcion: pedirJugada()
 * Parametros:
 * 	char* str -> apunta a la cadena ingresada cuya sintaxis se quiere revisar
 * Return: tipo int
 * 	FALSO (0) -> si hay un error en la estructura de la cadena ingresada
 * 	VERDADERO (1) -> si la estructura de la cadena es completamente valida
 */
int revisar_Syntax_Cad(char* str)
{
    if(strlen(str) < 5) // El minimo es de 5 posiciones en la cadena apuntada por str. Debe haber al menos 1 movimiento
        return FALSO;

    char tempStr[3];
    tempStr[2] = '\0';

    /* Se recorre la cadena enterar (hasta \0) verificando si todos los caracteres != ',', != '\n' y != ':'
     * sean numeros y si estos estan entre 0 y 4 inclusive
     * Se utiliza aritmetica de punteros (str++) para recorres la cadena hasta el \0
     */
    do
    {
        strncpy(tempStr, str, 2);

        // Se revisa si los dos caracteres de tempStr son numeros.
        // Si esto no se cumple, la cadena es invalida y se retorna FALSO
        if(isNumeric(tempStr) == FALSO)
            return FALSO;

        // Se revisa si cada caracter/numero de tempStr estan dentro del rango establecido
        // Si no se cumple, la cadena es invalida y se retorna FALSO
        if(dentroRangoInclusive( (int)(*str++ - '0'), 0, 4) == FALSO || dentroRangoInclusive((int)(*str++ - '0'), 0, 4) == FALSO)
            return FALSO;

        if(*str != ',' && *str != '\n' && *str != ':')
            return FALSO;

        str++;
    }
    while(*str != '\0');

    return VERDADERO;
}

/* Pide al jugador una cadena que contenga su posicion actual y su jugada
 * Se debe respetar la estructura de la cadena jugada. Ej. de cadena correcta: 41:13,11,43 (termina con enter)
 * Utilizada en la funcion: play()
 * Parametros: nada
 * Return: tipo *char
 * 	 str_respuesta -> cadena cuya estructura es valida
 */
char *pedirJugada()
{
    int esInvalido = VERDADERO; // Bandera para el do-while
    char * str_respuesta = NULL; // Para almacenar la cadena ingredasa por teclado
    size_t str_size = 0; // Tamaño de str_respuesta. Solo se utilizada como parametro de getline()

    do
    {
        printf("Jugada fichas %s: ", turno == TURNO_BLANCAS ? "blancas" : "negras");
        getline(&str_respuesta, &str_size, stdin);

        // Si ambos son verdaderos, entonces la cadena es completamente valida y se puede realiza la jugada;
        // caso contrario, se vuelve a solicitar la cadena
        if (revisar_Syntax_Cad(str_respuesta) == VERDADERO)
        {
            if(revisar_Semantica_Y_Carga(str_respuesta) == VERDADERO)
                esInvalido = FALSO;
            else
                puts("\nERROR: Jugada invalida.\n");
        }
        else
            puts("\nERROR: Sintaxis invalida.\n");
    }
    while(esInvalido);

    return str_respuesta;
}

/* Se genera la cadena que contiene la jugada de la PC
 * Parametros: nada
 * Return:
 * 	direccion de char * str_cad_pc
 */
void generarJugadaPC()
{
	char jugadaRandom[7];

	do
	{
		jugadaRandom[0] = '0' + rand()%5;
		jugadaRandom[1] = '0' + rand()%5;

		jugadaRandom[2] = ':';

		jugadaRandom[3] = '0' + rand()%5;
		jugadaRandom[4] = '0' + rand()%5;
		jugadaRandom[5] = '\n';
		jugadaRandom[6] = '\0';

		if(revisar_Semantica_Y_Carga(jugadaRandom))
			break;

	}
	while(VERDADERO);

	printf("Jugada de la pc con las fichas %s: %s", turno == TURNO_BLANCAS? "blancas":"negras", jugadaRandom);

}

/* Se empieza a jugar. Se dan los turno de cada jugador
 * Utilizado en la funcion: main()
 * Parametros: nada
 * Return: nada (es void)
 */
void play()
{
    // fichasBlancas y fichasNegras: numero de turnos para cada jugador
	// victoria: bandera para el do-while
	fichasBlancas = 12, fichasNegras = 12;
	char victoria = SIN_VICTORIA;

	// Se repetira el proceso hasta que se acabe la cantidad de fichas de uno de los jugadores
	printTable();
	do
	{
		// Turno de la PC
        if ((turno == TURNO_BLANCAS && jBlanco == PC) || (turno == TURNO_NEGRAS && jNegro == PC))
        {
        	generarJugadaPC();
        }
        else // Turno de la persona (si es multiplayer, se utiliza para ambas personas)
        {
        	pedirJugada();
        }
        printTable();
		turno = !turno; // Invertimos el valor de turno para que el sgte. jugador juegue
	}
	while ((victoria = askVictory()) == SIN_VICTORIA);

	printf("\nHa ganado el jugador con fichas %s!!!\n", victoria == VICTORIA_BLANCAS ? "blancas" : "negras");
}

			/*** GTK ***/

void jugarPc(){
	generarJugadaPC();
//	sleep(1);
	turno = !turno;
}

// ventanaBienvenida
void f_boton_jugar(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_hide (ventanaBienvenida);
	 gtk_widget_show_all (ventanaElegirModo1);
}

void f_boton_creditos(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_hide (ventanaBienvenida);
	 gtk_widget_show_all (ventanaCreditos);
}

void f_boton_ajustes(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_hide (ventanaBienvenida);
	 gtk_widget_show_all (ventanaAjustes);
}

// ventanaCreditos
void f_boton_volver_creditos(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	 gtk_widget_hide (ventanaCreditos);
	 gtk_widget_show_all (ventanaBienvenida);
}

// ventanaAjustes
void f_boton_volver_ajustes(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	gtk_widget_hide (ventanaAjustes);
	gtk_widget_show_all (ventanaBienvenida);
}

// ventanaVictoria
void f_boton_menu(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	gtk_widget_hide (ventanaJuego);
	gtk_widget_hide (ventanaVictoria);
	gtk_widget_show_all (ventanaAjustes);
}

void f_boton_volverAjugar(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	gtk_widget_hide (ventanaJuego);
	gtk_widget_hide (ventanaVictoria);
	gtk_widget_show_all (ventanaBienvenida);
}

void f_ventanaVictoria()
{
//	 gtk_widget_hide (ventanaJuego);
	 gtk_widget_show_all (ventanaVictoria);

	 gchar *temp;

	 if (fichasNegras == 0)
		 temp = g_strdup_printf("Felicidades %s, has ganado!!!", stringJugador2);
	 else if (fichasBlancas == 0)
		 temp = g_strdup_printf("Felicidades %s, has ganado!!!", stringJugador1);
	 else
		 temp = g_strdup_printf("Han empatado!");

	 gtk_label_set_text(GTK_LABEL(label_mensajeDeVictoria), temp);

	 g_free(temp);
}

// ventanaElegirModo
void f_boton_volver_modo(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	gtk_widget_hide (ventanaElegirModo1);
	gtk_widget_show_all (ventanaBienvenida);
}

void f_boton_enter_modo(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{

	gchar *temp = g_strdup_printf("%d", fichasNegras);
	gtk_label_set_text(GTK_LABEL(label_nroFichaNegras), temp);
	gchar *temp1 = g_strdup_printf("%d", fichasBlancas);
	gtk_label_set_text(GTK_LABEL(label_nroFichaBlancas), temp1);

	g_free(temp);
	g_free(temp1);

	strncpy(stringJugador1, gtk_entry_get_text(GTK_ENTRY(entry_nombreJugador1)), 15); // guardamos en el puntero lo que se introduce por teclado
	strncpy(stringJugador2, gtk_entry_get_text(GTK_ENTRY(entry_nombreJugador2)), 15); // guardamos en el puntero lo que se introduce por teclado

	if (strlen(stringJugador1) == 0)
		strcpy(stringJugador1, "Jugador Negro");

	if (strlen(stringJugador2) == 0)
		strcpy(stringJugador2, "Jugador Blanco");

	if (modo_juego == 'R')
	{
		char aux = rand() % 3;
		if (aux == 0)
			modo_juego = 'P';
		else if (aux == 1)
			modo_juego = 'S';
		else
			modo_juego = 'M';
	}

	if ((modo_juego == 'P' || (modo_juego == 'S' && miColor != ' ') || modo_juego == 'M') && empiezaColor != ' ')
	{

		gchar *temp0;
		temp0 = g_strdup_printf("%s", modo_juego == 'P' ? "PC VS PC" : modo_juego == 'S' ? "SINGLEPLAYER" : "MULTIPLAYER");
		gtk_label_set_text(GTK_LABEL(label_modoDeJuego), temp0);

		gchar *temp2 = g_strdup_printf("%s", stringJugador1);
		gtk_label_set_text(GTK_LABEL(label_nombreJNegro), temp2);

		gchar *temp3 = g_strdup_printf("%s", stringJugador2);
		gtk_label_set_text(GTK_LABEL(label_nombreJBlanco), temp3);

		gtk_widget_hide (ventanaElegirModo1);
		gtk_widget_show_all (ventanaJuego);

		chooseMode(miColor, empiezaColor, modo_juego);
	}
	else
	{
		gchar *temp4 = g_strdup_printf("Error: ingrese los datos correctamente");
		gtk_label_set_text(GTK_LABEL(label_mensajes_ventanaElegirModo1), temp4);
		g_free(temp4);
	}

	miColor = empiezaColor = modo_juego = CHAR_VACIO;

	gchar *temp5 = g_strdup_printf("%s",turno?stringJugador1:stringJugador2);
	gtk_label_set_text(GTK_LABEL(label_turnoActual), temp5);
	g_free(temp5);
	fichasBlancas = 12;
	fichasNegras = 12;
	resetTablero();
}

// ventanaJuego
void f_eventBox_tablero(GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	i = (GUINT_FROM_LE(event->y) / 98); // 98 = espaciado (48 px) + 50 px
	j = (GUINT_FROM_LE(event->x) / 98);

	if (tablero[i][j] == CHAR_BLANCO)
		gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(grid1_ventanaJuego),j,i)), CIRCULO_MARCADO_BLANCO);
	else if (tablero[i][j] == CHAR_NEGRO)
		gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(grid1_ventanaJuego),j,i)), CIRCULO_MARCADO_NEGRO);
	else
		gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(grid1_ventanaJuego),j,i)), CIRCULO_MARCADO_VACIO);

	posibleJugada.coordenada[posibleJugada.len][0] = j;
	posibleJugada.coordenada[posibleJugada.len][1] = i;
	posibleJugada.len++;
	char mensaje[300];

	int iAux,indiceMensaje;
	for (iAux  = 0, indiceMensaje = 0; iAux < (posibleJugada.len); iAux++)
	{
		mensaje[indiceMensaje++] = (posibleJugada.coordenada[iAux][1]) + '0';
		mensaje[indiceMensaje++] = ',';
		mensaje[indiceMensaje++] = posibleJugada.coordenada[iAux][0] + '0';

		if(iAux == 0)
		{
			mensaje[indiceMensaje++] = ':';
			mensaje[indiceMensaje++] = ' ';
		}
		else if(iAux <  posibleJugada.len - 1)
		{
			mensaje[indiceMensaje++] = ' ';
			mensaje[indiceMensaje++] = '-';
			mensaje[indiceMensaje++] = ' ';
		}
	}
	mensaje[indiceMensaje++] = '\0';

	gchar *temp = g_strdup_printf("%s", mensaje);
	gtk_label_set_text(GTK_LABEL(label_jugada), temp);
	g_free(temp);
}

void f_elegirModo (GtkWidget *event_box, GdkEventButton *event, gpointer data)
{
	gchar *temp;

	if (strcmp(data, "miBlanco") == 0)
		miColor = 'B';
	else if (strcmp(data, "miNegro") == 0)
		miColor = 'N';
	else if (strcmp(data, "miRandom") == 0)
		miColor = 'R';
	else if (strcmp(data, "Singleplayer") == 0)
		modo_juego = 'S';
	else if (strcmp(data, "Multiplayer") == 0)
		modo_juego = 'M';
	else if (strcmp(data, "PCvsPC") == 0)
		modo_juego = 'P';
	else if (strcmp(data, "Random") == 0)
	        modo_juego = 'R';
	else if (strcmp(data, "empiezaBlanco") == 0)
		empiezaColor = 'B';
	else if (strcmp(data, "empiezaNegro") == 0)
		empiezaColor = 'N';
	else if (strcmp(data, "empiezaRandom") == 0)
		empiezaColor = 'R';
	else
	{
		temp = g_strdup_printf("Error: aprete al menos un boton de cada trio");
		gtk_label_set_text(GTK_LABEL(label_mensajes_ventanaElegirModo1), temp);
		g_free(temp);
	}
	temp = g_strdup_printf("Modo de juego: %s\nMi color: %s\nEmpieza el color: %s",
			modo_juego == 'S'?"SinglePlayer":modo_juego == 'M'?"Multiplayer":modo_juego == 'P'?"PcvsPc":modo_juego == 'R'?"Random": "",
			miColor == 'B'?"Blanco":miColor == 'N'?"Negro": miColor == 'R'?"Random": "",
			empiezaColor == 'B'?"Blanco":empiezaColor == 'N'?"Negro":empiezaColor == 'R'?"Random": "");
	gtk_label_set_text(GTK_LABEL(label_mensajes_ventanaElegirModo1), temp);
	g_free(temp);

}

void actualizarVentanaJuego()
{
	// Se actualizan las imagenes de las fichas de cada posicion de la tabla de juego
	for (int auxI = 0; auxI < 5; auxI++)
	{
		for (int auxJ = 0; auxJ < 5; auxJ++)
		{
			if (tablero[auxI][auxJ] == CHAR_BLANCO)
				gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(grid1_ventanaJuego),auxJ,auxI)), CIRCULO_BLANCO);
			else if (tablero[auxI][auxJ] == CHAR_NEGRO)
				gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(grid1_ventanaJuego),auxJ,auxI)), CIRCULO_NEGRO);
			else
				gtk_image_set_from_file(GTK_IMAGE(gtk_grid_get_child_at(GTK_GRID(grid1_ventanaJuego),auxJ,auxI)), CIRCULO_VACIO);
		}
	}

	// Mostramos en label_nroFichaBlancas y label_nroFichaNegras el numero de fichas actuales de cada jugador
	gchar *temp1 = g_strdup_printf("%d", fichasNegras);
	gtk_label_set_text(GTK_LABEL(label_nroFichaNegras), temp1);
	gchar *temp2 = g_strdup_printf("%d", fichasBlancas);
	gtk_label_set_text(GTK_LABEL(label_nroFichaBlancas), temp2);

	// Mostramos en label_turnoActual el nombre del jugador cuyo turno corresponde
	gchar *temp0 = g_strdup_printf("%s", turno ? stringJugador1 : stringJugador2);
	gtk_label_set_text(GTK_LABEL(label_turnoActual), temp0);

	gchar *temp3;
	// Imprimimos en label_vaGanando el jugador con mas fichas
	if (fichasNegras > fichasBlancas)
		temp3 = g_strdup_printf("%s", stringJugador1);
	else if (fichasNegras < fichasBlancas)
		temp3 = g_strdup_printf("%s", stringJugador2);
	else
		temp3 = g_strdup_printf("Empate");

	gtk_label_set_text(GTK_LABEL(label_vaGanando), temp3);

	g_free(temp0);
	g_free(temp1);
	g_free(temp2);
	g_free(temp3);
}

void f_boton_enter_jugar (GtkWidget *event_box, GdkEventButton *event, gpointer data){

	if ((turno == TURNO_BLANCAS && jBlanco == PC) || (turno == TURNO_NEGRAS && jNegro == PC))
		jugarPc();
	else
	{
		char mensaje;
		int auxI, auxIndice;
		char jugada[50];

		for (auxI = 0, auxIndice = 0; auxI<posibleJugada.len + 1; auxI++)
		{
			jugada[auxIndice++] = posibleJugada.coordenada[auxI][1] + '0';
			jugada[auxIndice++] = posibleJugada.coordenada[auxI][0] + '0';

			if (auxI == 0)
				jugada[auxIndice++] = ':';
			else if (auxI <  posibleJugada.len - 1)
				jugada[auxIndice++] = ',';
		}
		jugada[auxIndice-2] = '\n';
		jugada[auxIndice-1] = '\0';

		if (revisar_Syntax_Cad(jugada) == VERDADERO)
		{
			if(revisar_Semantica_Y_Carga(jugada) == VERDADERO)
				mensaje = ES_CORRECTO;
			else
				mensaje = ERROR_SEMANTICA;
		}
		else
			mensaje = ERROR_SINTAXIS;

		gchar *temp = g_strdup_printf("%s", mensaje == ES_CORRECTO? "Jugada Validada": mensaje == ERROR_SEMANTICA? "Error: Ingrese una jugada Valida":"Error de sintaxis");
		gtk_label_set_text(GTK_LABEL(label_mensajes_ventanaJuego), temp);

		posibleJugada.len = 0;

		if(mensaje == ES_CORRECTO)
			turno = !turno;
	}
	actualizarVentanaJuego();

	if (fichasNegras == 0 || fichasBlancas == 0)
		f_ventanaVictoria();
}

int main(int argc, char *argv[])
{
	guint ret;
	GtkBuilder *builder;
	GError *error = NULL;

	gtk_init (&argc, &argv);

	builder = gtk_builder_new();
	ret = gtk_builder_add_from_file(builder, "play.glade", &error);

	if (ret == 0)
	{
		g_print("Error en la función gtk_builder_add_from_file:\n%s", error->message);
		return 1;
	}
	srand(time(NULL));
	resetTablero();

	eventBox_tablero = GTK_WIDGET(gtk_builder_get_object(builder, "eventBox_tablero"));
	grid1_ventanaJuego = GTK_WIDGET(gtk_builder_get_object(builder, "grid1_ventanaJuego"));

	ventanaBienvenida = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaBienvenida"));
	ventanaElegirModo1 = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaElegirModo1"));
	ventanaJuego = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaJuego"));
	ventanaVictoria = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaVictoria"));
	ventanaCreditos = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaCreditos"));
	ventanaAjustes = GTK_WIDGET(gtk_builder_get_object(builder, "ventanaAjustes"));

	boton_jugar = GTK_WIDGET(gtk_builder_get_object(builder, "boton_jugar"));
	boton_ajustes = GTK_WIDGET(gtk_builder_get_object(builder, "boton_ajustes"));
	boton_salir1 = GTK_WIDGET(gtk_builder_get_object(builder, "boton_salir1"));
	boton_enter_modo = GTK_WIDGET(gtk_builder_get_object(builder, "boton_enter_modo"));
	boton_singleplayer = GTK_WIDGET(gtk_builder_get_object(builder, "boton_singleplayer"));
	boton_multiplayer = GTK_WIDGET(gtk_builder_get_object(builder, "boton_multiplayer"));
	boton_PCvsPC = GTK_WIDGET(gtk_builder_get_object(builder, "boton_PCvsPC"));
	boton_jugar = GTK_WIDGET(gtk_builder_get_object(builder, "boton_jugar"));
	boton_miColorBlanco = GTK_WIDGET(gtk_builder_get_object(builder, "boton_miColorBlanco"));
	boton_miColorNegro = GTK_WIDGET(gtk_builder_get_object(builder, "boton_miColorNegro"));
	boton_miColorRandom = GTK_WIDGET(gtk_builder_get_object(builder, "boton_miColorRandom"));
	boton_empiezaBlanco = GTK_WIDGET(gtk_builder_get_object(builder, "boton_empiezaBlanco"));
	boton_empiezaNegro = GTK_WIDGET(gtk_builder_get_object(builder, "boton_empiezaNegro"));
	boton_empiezaRandom = GTK_WIDGET(gtk_builder_get_object(builder, "boton_empiezaRandom"));
	boton_enter_jugar = GTK_WIDGET(gtk_builder_get_object(builder, "boton_enter_jugar"));
	boton_menu = GTK_WIDGET(gtk_builder_get_object(builder, "boton_menu"));
	boton_salir2 = GTK_WIDGET(gtk_builder_get_object(builder, "boton_salir2"));
	boton_creditos = GTK_WIDGET(gtk_builder_get_object(builder, "boton_creditos"));
	boton_volver_creditos = GTK_WIDGET(gtk_builder_get_object(builder, "boton_volver_creditos"));
	boton_volver_ajustes = GTK_WIDGET(gtk_builder_get_object(builder, "boton_volver_ajustes"));
	boton_volver_modo = GTK_WIDGET(gtk_builder_get_object(builder, "boton_volver_modo"));
	boton_random = GTK_WIDGET(gtk_builder_get_object(builder, "boton_random"));

	label_mensajes_ventanaElegirModo1 = GTK_WIDGET(gtk_builder_get_object(builder, "label_mensajes_ventanaElegirModo1"));
	label_nombreJNegro = GTK_WIDGET(gtk_builder_get_object(builder, "label_nombreJNegro"));
	label_nombreJBlanco = GTK_WIDGET(gtk_builder_get_object(builder, "label_nombreJBlanco"));
	label_nroFichaNegras = GTK_WIDGET(gtk_builder_get_object(builder, "label_nroFichaNegras"));
	label_nroFichaBlancas = GTK_WIDGET(gtk_builder_get_object(builder, "label_nroFichaBlancas"));
	label_mensajes_ventanaJuego = GTK_WIDGET(gtk_builder_get_object(builder, "label_mensajes_ventanaJuego"));
	label_jugada = GTK_WIDGET(gtk_builder_get_object(builder, "label_jugada"));
	label_mensajeDeVictoria = GTK_WIDGET(gtk_builder_get_object(builder, "label_mensajeDeVictoria"));
	label_vaGanando = GTK_WIDGET(gtk_builder_get_object(builder, "label_vaGanando"));
	label_turnoActual = GTK_WIDGET(gtk_builder_get_object(builder, "label_turnoActual"));
	label_modoDeJuego = GTK_WIDGET(gtk_builder_get_object(builder, "label_modoDeJuego"));

	entry_nombreJugador1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_nombreJugador1"));
	entry_nombreJugador2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_nombreJugador2"));
	gtk_entry_set_max_length (GTK_ENTRY (entry_nombreJugador1), 15);
	gtk_entry_set_max_length (GTK_ENTRY (entry_nombreJugador2), 15);

	// ventanaBienvenida
	g_signal_connect(boton_jugar, "button-press-event", G_CALLBACK(f_boton_jugar), NULL);
	g_signal_connect(boton_creditos, "button-press-event", G_CALLBACK(f_boton_creditos), NULL);
	g_signal_connect(boton_ajustes, "button-press-event", G_CALLBACK(f_boton_ajustes), NULL);
	g_signal_connect(boton_salir1, "button-press-event", G_CALLBACK(gtk_main_quit), NULL);

	// ventanaCreditos
	g_signal_connect(boton_volver_creditos, "button-press-event", G_CALLBACK(f_boton_volver_creditos), NULL);

	// ventanaAjustes
	g_signal_connect(boton_volver_ajustes, "button-press-event", G_CALLBACK(f_boton_volver_ajustes), NULL);

	// ventanaElegirModo1
	g_signal_connect(boton_singleplayer, "button-press-event", G_CALLBACK(f_elegirModo), "Singleplayer");
	g_signal_connect(boton_multiplayer, "button-press-event", G_CALLBACK(f_elegirModo), "Multiplayer");
	g_signal_connect(boton_PCvsPC, "button-press-event", G_CALLBACK(f_elegirModo), "PCvsPC");
	g_signal_connect(boton_random, "button-press-event", G_CALLBACK(f_elegirModo), "Random");

	g_signal_connect(boton_miColorBlanco, "button-press-event", G_CALLBACK(f_elegirModo), "miBlanco");
	g_signal_connect(boton_miColorNegro, "button-press-event", G_CALLBACK(f_elegirModo), "miNegro");
	g_signal_connect(boton_miColorRandom, "button-press-event", G_CALLBACK(f_elegirModo), "miRandom");

	g_signal_connect(boton_empiezaBlanco, "button-press-event", G_CALLBACK(f_elegirModo), "empiezaBlanco");
	g_signal_connect(boton_empiezaNegro, "button-press-event", G_CALLBACK(f_elegirModo), "empiezaNegro");
	g_signal_connect(boton_empiezaRandom, "button-press-event", G_CALLBACK(f_elegirModo), "empiezaRandom");

	g_signal_connect(boton_enter_modo, "button-press-event", G_CALLBACK(f_boton_enter_modo), NULL);
	g_signal_connect(boton_volver_modo, "button-press-event", G_CALLBACK(f_boton_volver_modo), NULL);

	// ventanaJuego
	g_signal_connect(boton_enter_jugar, "button-press-event", G_CALLBACK(f_boton_enter_jugar), NULL);
	g_signal_connect(eventBox_tablero, "button-press-event", G_CALLBACK(f_eventBox_tablero), NULL);

	//ventanaVictoria
	g_signal_connect(boton_menu, "button-press-event", G_CALLBACK(f_boton_menu), NULL);
	g_signal_connect(boton_volverAjugar, "button-press-event", G_CALLBACK(f_boton_volverAjugar), NULL);
	g_signal_connect(boton_salir2, "button-press-event", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all (ventanaBienvenida);

	gtk_main ();

//	srand(time(NULL));
//	do
//	{
//		resetTablero();
//		chooseMode();
//		play();
//	}
//	while (askPlayAgain() == PLAY_AGAIN);

	return 0;
}
