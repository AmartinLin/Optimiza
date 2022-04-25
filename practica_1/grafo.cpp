 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Antonio Sedeno Noda, Sergio Alonso
 *  Cursos   : 2012-2021
 */
// Editado por: Alejandro Martín Linares (alu0101476476@ull.edu.es)
#include "grafo.h"

void GRAFO :: destroy()
{
	for (unsigned i=0; i< n; i++)
    {
		LS[i].clear();
		//A[i].clear();
		if (dirigido == 1)
        {
            LP[i].clear();
        };
	}
	LS.clear();
	LP.clear();
	//A.clear();

}

void GRAFO :: build (char nombrefichero[85], int &errorapertura) {
    ElementoLista     dummy;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open()) {
		unsigned i, j, k;
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores (LS = Lista de sucesores, LP = lista de predecesores)
		LS.resize(n);
		// construcci�n de LP, si es dirigido
        if (dirigido == 1) {
            LP.resize(n);
        }
        // leemos los m arcos
		for (k = 0; k < m; k++) {
			textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
			//damos los valores a dummy.j y dummy.c
            dummy.j = j - 1;
			//situamos en la posici�n del nodo i a dummy mediante push_back
            LS[i - 1].push_back(dummy);
			//pendiente de hacer un segundo push_back si es no dirigido. O no.
            if (dirigido == 1) {
                dummy.j = i - 1;
                LP[j - 1].push_back(dummy);
            }
			//pendiente del valor a devolver en errorapertura
			//...
        }
    } else {
        errorapertura = 1;
    }
}

GRAFO::~GRAFO() {
	destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
{
	build (nombrefichero, errorapertura);
}

void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
{
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido() {
    unsigned dirigido_o_no{0};
    if (this->dirigido == 1) {
        dirigido_o_no = 1;
    }
    return dirigido_o_no;
}

void GRAFO::Info_Grafo() {
    std::cout << "\nNumero de nodos: " << this -> n;
    std::cout << "\nNumero de arcos: " << this -> m;
    if (Es_dirigido() == 1) {
        std::cout << "\nTipo de grafo: Dririgido\n";
    } else {
        std::cout << "\nTipo de grafo: No Dririgido\n";
    }
}

void Mostrar_Lista(vector<LA_nodo> L) {
    for (int i{0}; i < L.size(); i++) {
        if (L[i].size() == 0) {
            std::cout << "Nodo " << i + 1 << ": " << "Vacío\n";
        }
        for (int j{0}; j < L[i].size(); j++) {
            std::cout << "Nodo " << i + 1 << ": (" << L[i][j].j + 1 << ", " << L[i][j].c << ")\n";
        }
    }
}

void GRAFO :: Mostrar_Listas (int l) {
    if (l == 1 && dirigido == 0) {
        std::cout << "El grafo es NO dirigido\n";
    }
    if (l == 1) {
        Mostrar_Lista(LP);
    } else {
        Mostrar_Lista(LS);
    }
}

/* void GRAFO::Mostrar_Matriz() //Muestra la matriz de adyacencia, tanto los nodos adyacentes como sus costes
{

}
 */

/**
 * @brief Hace un recorrido dfs de un grafo tanto con recorridos
 *        enum y postnum
 * 
 * @param i nodo desde el que realizamos el recorrido en profundidad
 * @param L lista que recorremos, LS o LP; por defecto LS
 * @param visitado vector que informa de si un nodo ha sido visitado
 * @param prenum almacenamos en la posición i el preorden del nodo i+1
 * @param prenum_ind contador del preorden
 * @param postnum almacenamos en la posición i el postorden del nodo i+1
 * @param postnum_ind contador del postorden
 */
void GRAFO::dfs_num( unsigned i, 
                     vector<LA_nodo>  L, 
                     vector<bool> &visitado, 
                     vector<unsigned> &prenum, 
                     unsigned &prenum_ind, 
                     vector<unsigned> &postnum, 
                     unsigned &postnum_ind 
                    ) {
    std::cout << "[DEBUG]1\n";
	visitado[i] = true;
    std::cout << "[DEBUG]2\n";
    //asignamos el orden de visita prenum que corresponde el nodo i
    prenum[prenum_ind++]=i;
    std::cout << "[DEBUG]3 " << L[i].size() << endl;
    for (unsigned j=0;j<L[i].size();j++) {
        std::cout << "[DEBUG]4\n";
        if (!visitado[L[i][j].j]) {
            std::cout << "[DEBUG]5\n";
            dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
        };
    }
    postnum[postnum_ind++]=i;//asignamos el orden de visita posnum que corresponde al nodo i
}

/**
 * @brief Hace un recorrido en profundidad de un grafo
 * 
 */
void GRAFO::RecorridoProfundidad() {
    //creación e inicialización de variables y vectores
    vector<LA_nodo> L{LS};
    vector<bool> visitado;
    vector<unsigned> prenum;
    unsigned prenum_ind{0};
    vector<unsigned> postnum;
    unsigned postnum_ind;
    visitado.resize(n);
    prenum.resize(n);
    postnum.resize(n);
    //solicitud al usuario del nodo inicial del recorrido en profundidad
    std::cout << "Construiremos un recorrido en profundidad\n";
    std::cout << "Elija un nodo de partida [1 - " << n << "] : ";
    unsigned i;
    std::cin >> i;  
    std::cout << "[DEBUG]Se crea todo\n";
    dfs_num(i - 1, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
    //mostrar en pantalla el preorden
    std::cout << "[DEBUG]se hace el dfs\n";
    std::cout << "Orden de visita de los nodos en preorden\n";
    std::cout << "[" << i << "]";
    for (int iterador{1}; iterador < prenum_ind; iterador++) {
        std::cout << " -> "<< prenum[iterador] << std::endl;
    }
    //mostrar en pantalla el postorden
    std::cout << "Orden de visita de los nodos en preorden\n";
    std::cout << "[" << postnum[postnum_ind] << "]";
    for (int iterador{1}; iterador < postnum_ind; iterador++) {
        std::cout << " -> "<< postnum[iterador] << std::endl;
    }
}

void GRAFO::bfs_num(	unsigned i, //nodo desde el que realizamos el recorrido en amplitud
				vector<LA_nodo>  L, //lista que recorremos, LS o LP; por defecto LS
				vector<unsigned> &pred, //vector de predecesores en el recorrido
				vector<unsigned> &d) //vector de distancias a nodo i+1
//Recorrido en amplitud con la construcci�n de pred y d: usamos la cola
{
    vector<bool> visitado; //creamos e iniciamos el vector visitado
    visitado.resize(n, false);
    visitado[i] = true;

    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[i] = i;
    d[i] = 0;

    queue<unsigned> cola; //creamos e inicializamos la cola
    cola.push(i);//iniciamos el recorrido desde el nodo i+1

    while (!cola.empty()) //al menos entra una vez al visitar el nodo i+1 y contin�a hasta que la cola se vac�e
    {   unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
        cola.pop(); //lo sacamos de la cola
        //Hacemos el recorrido sobre L desde el nodo k+1
        for (unsigned j=0;j<L[k].size();j++)
            //Recorremos todos los nodos u adyacentes al nodo k+1
            //Si el nodo u no est� visitado
            {
            //Lo visitamos
            //Lo metemos en la cola
            //le asignamos el predecesor
            //le calculamos su etiqueta distancia
            };
        //Hemos terminado pues la cola est� vac�a
    };
}

void RecorridoAmplitud() { //Construye un recorrido en amplitud desde un nodo inicial

}