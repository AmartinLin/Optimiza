 /*
 *  Programa principal.
 *
 *
 *               Autores : Alejandro Martín Linares
 *               Cursos  : 2021-2022
 */

#include <string.h>
#include "grafo.h"

void menu (unsigned dirigido, char &opcion)
//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
{
    cout << "\n**********************************************************************************************";
    cout << "\nOptimiza!cion en Grafos, 2021-2022 Alejandro Martín Linares" << endl;
    cout << "c. [c]argar grafo desde fichero" << endl;
    if (dirigido == 0) //Grafo no dirigido
            {
            cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
            cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
            cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo por sucesores\n";
            cout << "r. Realizar un recorrido en p[r]ofundidad del grafo desde un nodo por sucesores\n";
	    //Aqu� se a�aden m�s opciones al men� del grafo no dirigido
            }
    else
            {
            cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
            cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
            cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
            cout << "m. Realizar un recorrido en a[m]plitud del grafo desde un nodo por sucesores\n";
            cout << "r. Realizar un recorrido en p[r]ofundidad del grafo desde un nodo por sucesores\n";

	    //Aqu� se a�aden m�s opciones al men� del grafo dirigido
            };
    cout << "q. Finalizar el programa" << endl;
    cout << "Introduce la letra de la accion a ejecutar  > ";
    cin >> opcion;
};


// El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un men� inicial si no hay un grafo cargado
int main(int argc, char *argv[])
{
    int error_apertura;
    char nombrefichero[85], opcion;
    //clrscr();
    //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
    if (argc > 1)
    {
	cout << "Cargando datos desde el fichero dado como argumento" << endl;
        strcpy(nombrefichero, argv[1]);
    }
    else
    {
        cout << "Introduce el nombre completo del fichero de datos" << endl;
        cin >> nombrefichero;
    };
    GRAFO G(nombrefichero, error_apertura);
    if (error_apertura == 1)
    {
        cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
        //pressanykey();
        //clrscr();
    }
    else
    {
        cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
        //pressanykey();
        //clrscr();
        do
        {
            menu(G.Es_dirigido(), opcion);
            switch (opcion)
            {
                case 'c' :
         	    cout << "\nIntroduce el nombre completo del fichero de datos" << endl;
                    cin >> nombrefichero;
                    G.actualizar(nombrefichero, error_apertura);
                    if (error_apertura == 1) {
                        cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
                    } else {
                        cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
                    };
                    break;
                case 'i' :
		            cout << "Grafo cargado desde " << nombrefichero << endl;
                    G.Info_Grafo();
                    break;
                case 'a' :
                    cout << "Lista de adyacencia:\n";
                    cout << "[ESQUEMA] Nodo x: (nodo adyacente, coste)\n";
                    G.Mostrar_Listas(0);
                    break;
                case 's' :
                    cout << "\nSucesores del grafo: \n";
                    cout << "[ESQUEMA] Nodo x: (sucesor, coste)\n";
                    G.Mostrar_Listas(0);
                    break;
                case 'p' :
                    cout << "\nPredecesores del grafo: \n";
                    cout << "[ESQUEMA] Nodo x: (predecesor, coste)\n";
                    G.Mostrar_Listas(1);
                    break;
                case 'm' :
                    cout << "\nConstruiremos un recorrido en amplitud\n";
                    G.RecorridoAmplitud();
                    break;
                case 'r' :
                    cout << "\nConstruiremos un recorrido en profundidad\n";
                    G.RecorridoProfundidad();
                    break;
                default: 
                    cout << "Instrucción no correspondida, inténtelo de nuevo\n";
                    break;

		 //Situar aqu� el resto de opciones del men�
            }
    }
    while (opcion != 'q');
    }
    cout << "\nFin del programa" << endl;
    exit(EXIT_SUCCESS);
	return 0;
};
