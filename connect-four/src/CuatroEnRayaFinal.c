#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include "libreriaPersonal.h"


char barraSup[] =          "  1   2   3   4   5   6   7   ";
char barrasIntermedias[] = "|---|---|---|---|---|---|---|";
char barraInf[] =          "|===|===|===|===|===|===|===|";
int tablero[6][7]; 			// si es 0 esta vacio, si es 1 ficha de la persona, si es 2 ficha de computadora
int cerrarPrograma = 1; 	// si es 1 termina el juego y cierra el programa
int espaciosColumna[7]; 	// cuantos espacio fueron ocupados por columna
int puntDesempateJ;			// en caso de empate: cuenta los puntos a acumulados por el Jugador
int puntDesempatePC;		// en caso de empate: cuenta los puntos a acumulados por la PC
int columnaElegida;			// las columnas validas son del 1 al 7 y si se elije -1 el jugador se rinde (a cada valor que elija, se le resta 1)
int turnoInicio; 			// si es 1 persona, 0 maquina, random
int turnoMax; 				// nro. maximo de turno , elegido por el usuario, <= 21
int turnosJugador;			// cuantos turnos le queda al jugador
int turno; 					// turno en el que estamos
int ganador; 				// 0 si es empate, 1 si gana persona y 2 si gana computadora
int finalPartida; 			// no se modifica si es que el jugador quiere volver a jugar


void printTableroCompu() //Esta impresion se tiene la caracteristica de imprimir el ascii art de la pc a la par que el tablero
{
	// imprime el tablero cuando es el turno de la pc
	system("cls");
	printf("%s",PCTurno);
	printf("%s\n", barraSup);
	int n = 0;
	for (int i = 0; i < 6; i++)
	{
		printf("|");
		for (int j = 0; j < 7; j++)
		{
			if (tablero[i][j] == 1)
			{ // en el codigo es X y O, pero en la impresion es O de distintos colores para ambos
				if (turnoInicio == 0)
				{
					printf(" o ");
				}	
				else
				{
					printf(" x ");
				}
			}
			else
			{
				if (tablero[i][j] == 2)
				{
					if (turnoInicio == 0)
					{
						printf(" x ");
					}
					else
					{
						printf(" o ");
					}
					
				}
				else
				{
					printf("   ");
				}
			}
			if (j < 6)
			{
				printf("|");
			}
		}

		printf("|");
		printf("%d\t\t", 6 - i);
		printCompu(n); n++; // indica la linea del ascii art de la pc (se hace uso del arch. "printPC.h")
		if (i < 5) 
		{
			printf("%s\t\t", barrasIntermedias);
			printCompu(n);n++;
		}
		else
		{
			printf("%s\t\t", barraInf);
		}
	}
	for (int i = 10; i < 19; i++) // imprime la ultima parte de el ascii art de la pc, ya que n no llega hasta el
	{							  // valor necesario para imprimirlo totalmente
		printCompu(i);
	}
	sleep(2);
}

void printTableroJugador() //
{
	// imprime el tablero y los turnos restantes del jugador cuando es su turno
	// tambien se le pide al jugador el nro. de la columna en el que quiere ingresar una ficha
	system("cls");
	printf("%s",tuTurno);
	printf("%s\n", barraSup);
	for (int i = 0; i < 6; i++)
	{
		printf("|");
		for (int j = 0; j < 7; j++)
		{
			if (tablero[i][j] == 1)
			{ // en el codigo es X y O, pero en la impresion es O de distintos colores para ambos
				if (turnoInicio == 0)
				{
					printf(" o ");
				}	
				else
				{
					printf(" x ");
				}
			}
			else
			{
				if (tablero[i][j] == 2)
				{
					if (turnoInicio == 0)
					{
						printf(" x ");
					}
					else
					{
						printf(" o ");
					}
				}
				else
				{
					printf("   ");
				}
			}
			if (j < 6)
			{
				printf("|");
			}
		}
		printf("|");
		printf("%d\n", 6 - i);
		if (i < 5)
		{
			if (6-i == 2) 
			{
				printf("%s   Turnos restantes: %d\n", barrasIntermedias, turnosJugador);
			}
			else
			{
				printf("%s\n", barrasIntermedias);	
			}
		}
		else
		{
			printf("%s   Cual sera tu jugada? (p/ rendirse elija 0): ", barraInf);
		}
	}
}

void printTablero() //
{ // imprime el tablero actualizado sin ningun otro detalle
	printf("%s\n", barraSup);
	for (int i = 0; i < 6; i++)
	{
		printf("|");
		for (int j = 0; j < 7; j++)
		{
			if (tablero[i][j] == 1)
			{ // en el codigo es X y O, pero en la impresion es O de distintos colores para ambos
				if (turnoInicio == 0)
				{
					printf(" o ");
				}	
				else
				{
					printf(" x ");
				}
			}
			else
			{
				if (tablero[i][j] == 2)
				{
					if (turnoInicio == 0)
					{
						printf(" x ");
					}
					else
					{
						printf(" o ");
					}
				}
				else // tablero[i][j] == 0 
				{
					printf("   "); 
				}
			}
			if (j < 6)
			{
				printf("|");
			}
		}
		printf("|");
		printf("%d\n", 6 - i);
		if (i < 5)
		{
			printf("%s\n", barrasIntermedias);	
		}
		else
		{
			printf("%s\n", barraInf);
		}
	}
}

void tableroVacio() //
{
	// se "vacia" el tablero. En cada posicion se guarda un 0 que luego, a la hora de imprimir, es interpretado como un espacio 
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			tablero[i][j] = 0; 
		}
	}
	for(int i; i < 7; i++)
	{
		espaciosColumna[i]=0; //tambien se vacia el array espaciosColumna para que concuerde con el tablero vacio
	}
}

void mensaje(int n) //
{
	// dependiendo del valor de n, se imprimira el mensaje que corresponda (se hace uso del arch. "asciiArt.h")
	switch (n)
	{
	case Bienvenida: 	
		printf("%s", bienvenidaJuego);
		sleep(tiempoMimir);
		system("cls");
		break;
	case empate:
		printf("%s\n", empate_);
		sleep(tiempoMimir);
		break;
	case ganaPC:
		printf("%s %s\n", gana_PC, suerteLaProxima);
		printTablero();
		sleep(tiempoMimir);
		break;
	case ganaJugador:
		printf("%s\n", enhorabuena);
		printTablero();
		sleep(tiempoMimir);
		break;
	case finalJuego:
		printf("%s", hastaLaProxima);
		break;
	case surrender:
		printf("%s", teHasRendido);
		sleep(tiempoMimir);
		break;
	case pedirColumna: 
		printTableroJugador();
		break;
	case solicitarRondas: 	
		printf("%s",preguntaRondas);
		break;
	case PlayAgain: 
		system("cls");
		printf("%s", jugamosOtra);
		break;
	case datoNoEntero: 	
		system("cls");
		printf("%s",errorMensajeNoValido);
		sleep(tiempoMimir);
		system("cls");
		break;
	case datoFueraRango:
		system("cls");
		printf("%s", errorFueraDeRango);
		sleep(tiempoMimir);
		system("cls");
		break;
	case columnaLlena:
		system("cls");
		printf("%s", errorColumnaLlena);
		sleep(tiempoMimir);
		system("cls");
		break;
	case despedida:
		printf("%s", hastaLaProxima);
		break;
    case ganaJugadorD:
		system("cls");
		printTablero();
		printf("%s", porDesempate);
		printf("%s\n", enhorabuena);
		break;
    case ganaPCD:
		system("cls");
		printTablero();
		printf("%s", porDesempate);
		printf("%s\n", gana_PC);
		break;
	case empiezasTu:
		system("cls");
		printf("%s",EmpiezasTu);
		printTablero();
		sleep(tiempoMimir);
		break;
	case empiezaPC:
		system("cls");
		printf("%s",EmpiezaPC);
		printTablero();
		sleep(tiempoMimir);
		break;
	default:
		printf("ERROR\n");
		break;
	}
}

int getInt(int minimo, int maximo, int MENSAJE) //
{ 	// MENSAJE puede ser, pedirColumna (8) o solicitarRondas (11).
	// El usuario ingresa un numero y este es verificado por el programa. En caso de no cumplir los requisitos, se vuelve a solicitar.
	char cadena[10]; // Se le puede ingresar cualquier valor. Si usamos tipo int, explota la pc.
	int cDigits, cadenaTrans, cadenaDeCeros, i, largorCadena;
	int terminarCiclo = False;
	
	do
	{
		mensaje(MENSAJE);		  // Pedimos que ingrese la columna o nro de turnos. 
		fgets(cadena, 10, stdin); // Pide caracteres de 10 de longitud (\n cuenta como 1, el enter que hacemos al final).
		fflush(stdin);			  // Limpia buffer del teclado.
		if (cadena[strlen(cadena) - 1] == '\n')
		{									   // No se cumple si es que se llena la cadena, por ejemplo.
			cadena[strlen(cadena) - 1] = '\0'; // "Eliminamos" el \n de la cadena.
		}
		cadenaTrans = atoi(cadena);										// Carga a "cadenaTrans" el valor equivalente de cadena en un valores enteros (elimina los careceteres de la cadena, deja solo los nros enteros)
		cDigits = (cadenaTrans == 0) ? 1 : log10(abs(cadenaTrans)) + 1; // Asgina a "cDigits" la cantidad de digitos de la "cadenaTrans".
		largorCadena = (int)strlen(cadena);								// Se crea un valor donde se cargo la cantidad de caracteres en la cadena.
		if (cadena[0] == '-')
		{ // Si la cadena empieza con el signo menos, este se elimina del conteo en largor cadena.
			largorCadena--;
		}
		if (cadenaTrans == 0)
		{ // Verifica si todo los elementos de la cadena son 0s en el caso especial de que cadenaTrans sea 0.
			i = 0;
			cadenaDeCeros = False;
			while (True)
			{
				if (cadena[i] == '0' || (i == 0 && cadena[i] == '-'))
				{
					i++;
				}
				else
				{
					break;
				}
				if (i == strlen(cadena))
				{
					cadenaDeCeros = True; // Si se da este caso, significa que se ingreso como cadena "0000...0" o en
				}						  // su defecto "-0000...0", cuyos valores s� son 0 as� que verifican.
			}
		}
		if (cDigits == largorCadena)
		{ // Verificamos que TODOS los caracteres pueden transformarse en digitos, ejemplo de no seria -> 34ab.
		  // Basicamente, verificamos si todos los caracteres que se hallan ingresado son nros.
			if (cadenaTrans <= maximo && cadenaTrans >= minimo)
			{ // Verificamos que la "cadenaTrans" este dentro del rango solicitado.
				terminarCiclo = True;
				if (cadenaTrans == 0)
				{
					terminarCiclo = False;
					if (cadenaTrans == 0)
					{
						if (cadenaDeCeros == True)
						{ // Dado que todas estas condiciones se cumplirian en el caso de que se ingresasen solo letras 
						  // y el 0 estuviese incluido en el rango, aqui filtramos la posibilidad de tal caso.
							terminarCiclo = True;
						}else{mensaje(datoNoEntero);}
					}
				}
			}else{mensaje(datoFueraRango);}
		}else{mensaje(datoNoEntero);}
	} while (terminarCiclo == False); // Se repite hasta que se ingrese un valor valido.
	return cadenaTrans;
}

int verificarVictoria(int columna)
{
	// Verificar si se gano la partida en este turno mediante la ficha ingresada.
	// Se analiza la ultima ficha que se ha ingresado. Se compara con las fichas que lo rodean, si es que 
	// la variable "contador" llega a 4, entonces hay un ganador y se retorna 1, en caso contrario se retorna 0.

	int i = 6 - espaciosColumna[columna];
	int j = columna;
	int contador, aux_i, aux_j, cont_2;

	// Vertical abajo: El unico caso de linea vertical posible es la creada por la linea abajo de la ficha ingresada
	if (i <= 2) // Si la fila en la que se encuentra tiene un numero < a 3 filas por debajo
	{			// entonces ya no nos interesa saber si es que se gana de forma vertical desde esa posicion ya que no es posible
		if (tablero[i][j] == tablero[i+1][j] && tablero[i][j] == tablero[i+2][j] && tablero[i][j] == tablero[i+3][j]) //se verifica que los 3 elementos por debajo de la ficha
																													  //ingresada sean iguales a esta
		{
			return 1; // en caso afirmativo, se encontró un caso de victoria
		}
	}

	contador = 1; // El contador empieza en 1, se irá modificando hasta llegar a 4 fichas que formen una linea
	//Linea Horizontal
	// Horizontal derecha.
	for(aux_j = j; aux_j+1 < 7; aux_j++) //Recorremos y verificamos los elementos que se encuentren a la derecha de la ficha ingresada que pertenezcan a la matriz
	{
		if(tablero[i][j] == tablero[i][aux_j+1])
		{
			contador += 1;
			if (contador == 4) 
			{
				return 1; // Hay un ganador.
			}
		}
		else 
		{
			break; //se deja de contar al momento de encontrar un elemento no igual a la ficha ingresada
		}
	}
	//se mantiene el numero obtenido en la linea horizontal derecha ya que todos en conjunto forman una sola linea
	// Horizontal izquierda.
	for (aux_j = j; aux_j-1 > -1; aux_j--)
	{
		if (tablero[i][j] == tablero[i][aux_j - 1]) //se recorre y verifica los elementos que se encuentren a la izquierda de la ficha ingresada que
		{											//pertenezcan a la matriz
			contador += 1;
			if (contador == 4)
			{
				return 1; // Hay un ganador.
			}
		}
		else 
		{
			break; //se deja de contar al momento de encontrar un elemento no igual a la ficha ingresada
		}
	}
	//Si no se llegó a ninguna condición de victoria, se reinicia el contador a 1 y se verifican las siguientes
	contador = 1;
	aux_i = i;
	//Linea Diagonal principal
	//Sabemos que todos los miembros de la diagonal pricipal tendran la forma de (i+-n;j+-n)
	//Diogonal Principal superior izquierda
	for(aux_j = j; aux_j-1 > -1 && aux_i-1 > -1; aux_j--) 
	{
		if(tablero[i][j] == tablero[aux_i-1][aux_j-1])  //Recorremos y verificamos los elementos que se encuentren en la parte superior izquierda de
		{												//la diagonal principal que pertenezcan a la matriz
			contador += 1;
			if (contador == 4) 
			{
				return 1; // Hay un ganador.
			}
		}else 
		{
			break; //se deja de contar al momento de encontrar un elemento no igual a la ficha ingresada
		}
		aux_i -= 1;
	}
	//se mantiene el contador ya que ambas forman la misma linea
	// Diagonal principal inferior derecha.
	aux_i = i;
	for (aux_j = j; aux_j + 1 < 7 && aux_i + 1 < 6; aux_j++) 
	{
		if (tablero[i][j] == tablero[aux_i + 1][aux_j + 1]) //Recorremos y verificamos los elementos que se encuentren en la parte inferior derecha de
		{													//la diagonal principal que pertenezcan a la matriz
			contador += 1;
			if (contador == 4)
			{
				return 1; // Hay un ganador.
			}
		}else 
		{
			break; //se deja de contar al momento de encontrar un elemento no igual a la ficha ingresada
		}
		aux_i += 1;
	}
	//ya que no se encontró ningun caso de victoria, se reinicia el contador
	contador = 1;
	aux_i = i;
	// Diagonal secundaria
	//Sabemos que todos los miembros de la diagonal principal tendran la forma (a;N-a),N=i+j-1,a=i+-n
	//Diagonal secundaria superior derecha
	for (aux_j = j; aux_j + 1 < 7 && aux_i - 1 > -1; aux_j++)
	{
		if (tablero[i][j] == tablero[aux_i - 1][aux_j + 1]) //Recorremos y verificamos los elementos que se encuentren en la parte superior derecha de
		{													//la diagonal principal que pertenezcan a la matriz
			contador += 1;
			if (contador == 4)
			{
				return 1; // Hay un ganador.
			}
		}else 
		{
			break; //se deja de contar al momento de encontrar un elemento no igual a la ficha ingresada
		}
		aux_i -= 1;
	}
	//se conserva el contador ya que ambas partes de la diagonal forman parte de la misma linea
	// Diagonal secundaria inferior izquierda
	aux_i = i;
	for (aux_j = j; aux_j - 1 > -1 && aux_i + 1 < 6; aux_j--)
	{
		if (tablero[i][j] == tablero[aux_i + 1][aux_j - 1]) //Recorremos y verificamos los elementos que se encuentren en la parte inferior izquierda de
		{													//la diagonal principal que pertenezcan a la matriz
			contador += 1;
			if (contador == 4)
			{
				return 1; // Hay un ganador.
			}
		}
		else 
		{
			break; //se deja de contar al momento de encontrar un elemento no igual a la ficha ingresada
		}
		aux_i += 1;
	}

	return 0; // No hay ganador, en ninguna de las condiciones de victoria posible se llegó a una conclusión satisfactoria
}

void insertFicha()
{
	switch (turnoInicio)
	{
	case 1:					// turnos impares son la persona, turnos pares son la pc
		if (turno % 2 != 0) // el turno es impar
		{
			tablero[6 - espaciosColumna[columnaElegida]][columnaElegida] = 1;
		}
		else // el turno es par
		{
			tablero[6 - espaciosColumna[columnaElegida]][columnaElegida] = 2;
		}
		break;

	case 0:					// turnos pares son la persona, turnos impares son la pc
		if (turno % 2 != 0) // el turno es impar
		{
			tablero[6 - espaciosColumna[columnaElegida]][columnaElegida] = 2;
		}
		else // el turno es par
		{
			tablero[6 - espaciosColumna[columnaElegida]][columnaElegida] = 1;
		}
		break;

	default:
		mensaje(error);
		break;
	}
}

void turnoComputadora()
{
	// se elige en cual columna ingresara la computadora una ficha
	columnaElegida = -1; // en otras palabras, el indice columna de la matriz que la computadora elige
	do
	{
		columnaElegida = rand() % 7; //se genera un numero randomizado entre 0 y 7
	} while (!(espaciosColumna[columnaElegida] < 6)); //se verifica si la columna del numero generado tiene espacios disponibles, sino, se vuelve a generar otro
	espaciosColumna[columnaElegida]++;//se registra que la columna tiene un nuevo miembro
	insertFicha();//se ingresa la ficha en la columna del numero generado
	
}

void turnoJugador()
{
	columnaElegida = -2;
	do
	{
		columnaElegida = getInt(0, 7, pedirColumna) - 1; // Ingrese 0 (-1) para rendirse, ingrese el numero entre 1 al 7 para jugar  una columna

		if (columnaElegida == -1) {
			return; //el jugador eligio rendirse, se retorna la funcion anterior
		}
		if(!(espaciosColumna[columnaElegida] < 6))
		{
			mensaje(columnaLlena);
		}
		else
		{
			break;
		}
	} while (1); //se verifica que la columna seleccionada por el jugador tiene espacios disponibles, sino, se vuelve a solicitar
	espaciosColumna[columnaElegida]++;//se registra que la columna tiene un nuevo miembro
	insertFicha(); //se ingresa la ficha en la columna seleccioanda
	turnosJugador--; //se disminuye en 1 el conteo de la cantidad de turnos que tendrá la partida
}

void verificarAdyacencia(int i, int j) //
{
	// analizamos cada ficha de cada jugador y sumamos +1 a sendas variables gobales: "puntDesempateJ" y "puntDesempatePC" 
	// por punto que se logre por cada ficha de cada jugador
	if (tablero[i][j] != 0)
	{
		for (int ai = i - 1; ai <= i + 1; ai++)
		{
			for (int aj = j - 1; aj <= j + 1; aj++) // recorremos una submatriz 3x3 conformada por todos los elementos a los alrededores del elemento seleccionado
			{										// Si este da valores fuera de la matriz se descarta el valor
				if ((ai >= 0 && ai < 6) && (aj >= 0 && aj < 7) && !(ai == i && aj == j)) // los primeros 2 parentesis verifican
				{ // que i y j pertenezcan a la matriz, y el ultimo verifica si el elemento del recorrido es igual o no al cargado en la funcion
					if (tablero[ai][aj] == tablero[i][j])
					{
						if (tablero[ai][aj] == 1)
						{
							puntDesempatePC++;
						}
						else if (tablero[ai][aj] == 2)
						{
							puntDesempateJ++;
						}
						return;
					}
				}
			}
		}
	}
}

void verificarEmpate() //
{
	// si es que hay empate, se verifica quien ha ganado por puntos acumulado por conteo de alineacion de fichas, en el caso de que exista un ganador
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			verificarAdyacencia(i, j); // verifica cuantos puntos se generan por cada ficha de cada jugador
		}
	}

	// se da un ganador o hay empate, dependiendo del resultado de la comparacion entre las variables globales
	// "puntDesempateJ" y "puntDesempatePC" modificadas anteriormente en la funcion "verificarAdyacencia()"
	if (puntDesempateJ > puntDesempatePC)
	{
		mensaje(ganaJugadorD);
	}
	else if (puntDesempateJ < puntDesempatePC)
	{
		mensaje(ganaPCD);
	}
	else
	{
		mensaje(empate);
	}
	printf("PJ: %d\tPPC: %d\n", puntDesempateJ, puntDesempatePC);
	sleep(2);
}

void mensajeFinalPartida() //
{
	// dependiendo del valor de "ganador" se imprime un mensaje mediante la funcion mensaje o, en caso de -1, se verifica si es posible desempartar por puntos.
	switch (ganador)
	{
	case -1:
		verificarEmpate();
		break;
	case 1:
		system("cls");
		mensaje(ganaJugador);
		break;
	case 2:
		system("cls");
		mensaje(ganaPC);
		
		break;
	case 3 : 
		mensaje(surrender);
		break;
	default:
		mensaje(error);
		break;
	}
}

void tableroInicio() // 
{
	// se inicializan todas las variables que necesiten ser reseteadas y el tablero se limpia
	
	tableroVacio();
	ganador = -1;
	finalPartida = False;
	
	turno = 0;
	turnoMax = getInt(1, 21, solicitarRondas);
	turnosJugador = turnoMax;
	turnoMax *= 2;
    
	// utilizados en caso de empate en "verificarAdyacencia()"
	puntDesempateJ = 0;	
    puntDesempatePC = 0;
	
	// se elige de forma aleatoria el jugador que empieza
	turnoInicio = -1;
	turnoInicio = rand() % 2;
	if (turnoInicio == 1)
	{
		mensaje(empiezasTu);
	}
	else
	{
		mensaje(empiezaPC);
	}
}

void playAgain() //
{
	// modifica "cerrarPrograma" (por default 0) en caso de que no se quiera volver a jugar
	cerrarPrograma = getInt(0, 1, PlayAgain); // preguntar si se quiere jugar de nuevo, 0 en caso
	system("cls");							  // de que se quiera volver a jugar y 1 si es que no
}

void partidaCaso0() //
{
	// en caso de que empiece jugando la pc, el orden de juego se establece de la sgte. manera
	do
	{
		turnoComputadora();
		turno++;
		printTableroCompu();
		if (verificarVictoria(columnaElegida) == 1)
		{
			ganador = 2;
			break;
		}
		else
		{
			printTableroJugador();
			turnoJugador();
			turno++;
			if (columnaElegida == -1) // si el jugador elige 0 (-1), se rinde
			{ 
				ganador = 3;
				break;
			}
			if (verificarVictoria(columnaElegida) == 1)
			{
				ganador = 1;
				break;
			}
			if (turno == turnoMax)
			{
				ganador = -1; // empate
				break;
			}
		}
	} 
	while(True);
}

void partidaCaso1() //
{
	// en caso de que empiece jugando el usuario, el orden de se establece juego de la sgte. manera
	do
	{
		printTableroJugador();
		turnoJugador();
		turno++;
		if (columnaElegida == -1)
		{ // si el jugador elige -1, se rinde
			ganador = 3;
			break;
		}
		if (verificarVictoria(columnaElegida) == 1)
		{
			ganador = 1;
			break;
		}else
		{
			turnoComputadora();
			turno++;
			printTableroCompu();
			if (verificarVictoria(columnaElegida) == 1)
			{
				ganador = 2;
				break;
			}
			if (turno == turnoMax){
				ganador = -1;
				break;
			}
		}
		
	} while (finalPartida == False);
}

void partida() //
{
	// dependiendo del valor de "turnoInicio", el orden de juego sera de una u otra manera (especificadas en "partidaCaso0" y "partidaCaso1")
	switch (turnoInicio)
	{
	case 0:
		partidaCaso0();
		break;
	case 1:
		partidaCaso1();
		break;
	default:
		mensaje(error);
		break;
	}
	
}


int main()
{
	system("mode con COLS=200"); // define el tamaño con el que se abre la terminal 
	mensaje(Bienvenida); //se da la bienvenida al usuario
	srand(time(NULL)); //se inicializa la funcion srand para la generación de numeros aleatorios
	do
	{
		tableroInicio(); //se inicializan las variables y el tablero
		partida(); //se ejecuta la partida en el debido orden dependiendo del caso elegido en tableroInicio
		mensajeFinalPartida(); //se informa de los resultados finales de la partida Jugada
		playAgain(); //se pregunta si se volverá a Jugar otra partida o si finalizar programa
	}
	while (cerrarPrograma == 1); 
	mensaje(despedida);
}
