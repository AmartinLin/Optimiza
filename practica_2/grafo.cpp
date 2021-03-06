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
            if (dirigido == 0 && i != j) {
                dummy.j = i -1;
                LS[j-1].push_back(dummy);
            } else { //pendiente la construcción de LP, si es dirigido
                LP.resize(n);
                dummy.j = i - 1;
                LP[j-1].push_back(dummy);
            };
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
        std::cout << "Nodo " << i + 1 << ": ";
        if (L[i].size() == 0) {
            std::cout << "Vacío";
        }
        for (int j{0}; j < L[i].size(); j++) {
            std::cout << "(" << L[i][j].j + 1 << ", " << L[i][j].c << ") ";
        }
        std::cout << std::endl;
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
 * @param L [VECTOR] lista que recorremos, LS o LP; por defecto LS
 * @param visitado [VECTOR] informa de si un nodo ha sido visitado
 * @param prenum [VECTOR] almacenamos en la posición i el preorden del nodo i+1
 * @param prenum_ind contador del preorden
 * @param postnum [VECTOR] almacenamos en la posición i el postorden del nodo i+1
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
	visitado[i] = true;
    //asignamos el orden de visita prenum que corresponde el nodo i
    prenum[prenum_ind++]=i;
    for (unsigned j=0;j<L[i].size();j++) {
        if (!visitado[L[i][j].j]) {
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
    unsigned i;
    vector<bool> visitado;
    vector<unsigned> prenum;
    unsigned prenum_ind{0};
    vector<unsigned> postnum;
    unsigned postnum_ind;
    visitado.resize(n);
    prenum.resize(n);
    postnum.resize(n);
    //solicitud al usuario del nodo inicial del recorrido en profundidad
    std::cout << "Elija un nodo de partida [1 - " << n << "] : ";
    std::cin >> i;  
    dfs_num(i - 1, LS, visitado, prenum, prenum_ind, postnum, postnum_ind);
    //mostrar en pantalla el preorden
    std::cout << "Orden de visita de los nodos en preorden\n";
    std::cout << "[" << i << "]";
    for (int iterador{1}; iterador < prenum_ind; iterador++) {
        std::cout << " -> " << "[" << prenum[iterador] + 1 << "]";
    }
    //mostrar en pantalla el postorden
    std::cout << "\nOrden de visita de los nodos en postorden\n";
    std::cout << "[" << postnum[0] + 1 << "]";
    for (int iterador{1}; iterador < postnum_ind; iterador++) {
        std::cout << " -> " << "[" << postnum[iterador] + 1 << "]";
    }
    std::cout << std::endl;
}

/**
 * @brief Recorrido en amplitud con la construcción de pred y d: usamos la cola
 * 
 * @param i nodo desde el que realizamos el recorrido en amplitud
 * @param L lista que recorremos, LS o LP; por defecto LS
 * @param pred vector de predecesores en el recorrido
 * @param d vector de distancias a nodo i+1
 */
void GRAFO::bfs_num(	unsigned i, 
				        vector<LA_nodo>  L, 
				        vector<unsigned> &pred, 
				        vector<unsigned> &d) {
    //creamos e iniciamos el vector visitado
    vector<bool> visitado; 
    visitado.resize(n, false);
    visitado[i] = true;

    pred.resize(n, 0); //creamos e inicializamos pred y d
    d.resize(n, 0);
    pred[i] = i;
    d[i] = 0;

    queue<unsigned> cola; //creamos e inicializamos la cola
    cola.push(i);//iniciamos el recorrido desde el nodo i+1

    while (!cola.empty()) { //al menos entra una vez al visitar el nodo i+1 y contin�a hasta que la cola se vac�e
        unsigned k = cola.front(); //cogemos el nodo k+1 de la cola
        cola.pop(); //lo sacamos de la cola
        //Hacemos el recorrido sobre L desde el nodo k+1
        for (unsigned j=0;j<L[k].size();j++) { //Recorremos todos los nodos u adyacentes al nodo k+1
            std::cout << "[DEBUG] ENTRA AL FOR\n";
            unsigned u = L[k][j].j; 
            //Si el nodo u no está visitado 
            if (visitado[u] == false) { 
            //Lo visitamos
            //Lo metemos en la cola
            //le asignamos el predecesor
            //le calculamos su etiqueta distancia
            visitado[u] = true;
            cola.push(u);
            pred[u] = k + 1;
            d[u] = d[k] + 1;
            };
        }
        //Hemos terminado pues la cola est� vac�a
    };
}

/**
 * @brief Construye un recorrido en amplitud desde un nodo inicial
 * 
 */
void GRAFO::RecorridoAmplitud() {  
    unsigned i;
    vector<unsigned> pred;
    vector<unsigned> d;
    std::cout << "Elija un nodo de partida [1 - " << n << "]: ";
    std::cin >> i;
    bfs_num(i - 1, LS, pred, d);

    int max_dist{0};
    for (int i{0}; i < d.size(); i++) {
        if (max_dist < d[i])
            max_dist = d[i];
    }
    
    std::cout << "Nodo inicial: " << i << std::endl;
    std::cout << "\nNodos según la distancia al nodo inicial en numero de aristas: \n";
    std::cout << "Distancia a 0 aristas : " << i << std::endl;
    for (int i{1}; i <= max_dist; i++) {
        std::cout << "Distancia a " << i << " aristas";
        for (int j{0}; j < d.size(); j++) {
            if (d[j] == i) {
                std::cout << " : " << j + 1; 
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\nRamas de conexión en el recorrido (predecesores)\n";
    for (int i{0}; i < n; i++) {
        if (pred[i] == 0) {
            std::cout << "Predecesor de " << i + 1 << ":  " << std::endl;
        } else {
            std::cout << "Predecesor de " << i + 1 << ": " << pred[i] << std::endl;
        }
    } 
}

/**
 * @brief reorganiza los parametros pasados
 * 
 * @param[in] aristas vector de aristas que se ha de pasar por parámetros 
 * @param[in] inicio punto de inicio del vector anterior donde se empezará a organizar
 * @param[in] final punto donde se termina el vector a organizar
 */
template <class T> 
int particion(vector<T> &aristas, int inicio, int final) {
    int pivote = aristas[inicio].peso; // seleccionamos como elementos pivote la primera arista
    int i = inicio + 1;
    for (int j = i; j <= final; j++) {
        if (aristas[j].peso < pivote) {
            swap(aristas[i], aristas[j]);
            i++;
        }
    }
    swap(aristas[inicio], aristas[i - 1]);
    return i - 1;
}

/**
 * @brief Función quicksort desarroyada para el pleno funcionamiento
 *        del método kruskal (ordena de menor a mayor las aristas)
 * 
 * @param[in] aristas vector de aristas que se ha de pasar por parámetros 
 * @param[in] inicio punto de inicio del vector anterior donde se empezará a organizar
 * @param[in] final punto donde se termina el vector a organizar
 */
template <class T> 
void quickSort(vector<T> &aristas, int inicio, int final) {
    if (inicio >= final) { 
        return;
    }
    int pivote = particion(aristas, inicio, final);
    quickSort(aristas, inicio, pivote - 1); 
    quickSort(aristas, pivote + 1, final);
}

/**
 * @brief Realiza el algoritmo de kruskal para grafos no dirigidos
 * 
 */
void GRAFO::kruskal() {
    vector<AristaPesada> Aristas;
    /*Cargamos todas las aristas de la lista de adyacencia*/
    Aristas.resize(m);
    unsigned k = 0;
    for (unsigned i{0}; i < n; i++) {
        for (unsigned j{0}; j < LS[i].size(); j++) {
            if (i < LS[i][j].j) {
                Aristas[k].extremo1 = i;
                Aristas[k].extremo2 = LS[i][j].j;
                Aristas[k++].peso = LS[i][j].c;
            }
        }
    };
    // necesito ordenar las aristas por coste, para ello se ha desarroyado 
    // la función quicksort
    quickSort(Aristas, 0, Aristas.size() - 1);
    /*Inicializamos el registro de componentes conexas: cada nodo está en su componente conexa*/
    vector <unsigned> Raiz;
    Raiz.resize(n);
    for (unsigned q = 0;q < n; q++) {
        Raiz[q]=q;
    };
    vector<AristaPesada> arbol;
    double coste_total{0};
    for (int aristas_realiza{0}; arbol.size() < n - 1; aristas_realiza++) {
        AristaPesada e = Aristas[aristas_realiza]; // e -> siguiente arista
        if (Raiz[e.extremo1] != Raiz[e.extremo2]) {
            arbol.push_back(e); // T = T U e
            std::cout << "Arista numero " << aristas_realiza << " incorporada (" 
                      <<  e.extremo1 + 1 << ", " << e.extremo2 + 1 << "), con peso " << e.peso << std::endl;
            coste_total += e.peso;
            // Clasificamos los elementos conexos con la misma raíz
            unsigned kill = Raiz[e.extremo1];
            for (int k{0}; k < n; k++) {
                if (Raiz[k] == kill) {
                    Raiz[k] = Raiz[e.extremo2];
                }
            }
        }
    }
    std::cout << "Coste total del arbol: " << coste_total << std::endl;
}