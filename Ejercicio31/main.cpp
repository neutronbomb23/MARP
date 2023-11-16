
/*@ <authors>
 *
 * Dorjee Khampa Herrezuelo Blasco MARP13
 *
 *@ </authors> */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <queue>
using namespace std;


/*@ <answer>

La solución implementada busca determinar cuántos nodos son alcanzables desde ciertos puntos de inicio dados, considerando un límite de distancia.
PARA ESTOs, se utiliza el algoritmo de Dijkstra.



1. Se inicia la distancia de cada nodo a "INFINITO", excepto los nodos de inicio que tienen distancia 0.
2. Se utiliza cola de prioridad para gestionar los nodos pendientes de procesar empezando por los del inicio.
3. En cada iteración, se toma el nodo con la menor distancia conocida y se actualiza la distancia a sus
vecinos si se encuentra una ruta más corta a través del nodo actual.
4. Se contabilizan aquellos nodos cuya distancia final es menor o igual al límite dado.

El coste de esta solución es principalmente el del algoritmo de Dijkstra, que es O((V+E) log V), siendo V el número de nodos y E el número de aristas en el grafo.

@ </answer> */


class CaminoOptimo {
protected:
    const int INFINITO = numeric_limits<int>::max();
    vector<int> puntosInicio;
    vector<int> distancia;
    IndexPQ<int> colaPrioridad;
    int puntosAlcanzables;

    void optimizarRuta(AristaDirigida<int> arista) {
        int inicio = arista.desde();
        int fin = arista.hasta();
        if (distancia[fin] > distancia[inicio] + arista.valor()) {
            distancia[fin] = distancia[inicio] + arista.valor();
            colaPrioridad.update(fin, distancia[fin]);
        }
    };

public:
    CaminoOptimo(DigrafoValorado<int> const& grafo, vector<int>& puntosDeInicio, int limite, vector<bool>& alcanzado)
        : distancia(grafo.V(), INFINITO), colaPrioridad(grafo.V()), puntosAlcanzables(0) {

        for (int inicio : puntosDeInicio) {
            distancia[inicio] = 0;
            colaPrioridad.push(inicio, 0);
        }

        while (!colaPrioridad.empty()) {
            int actual = colaPrioridad.top().elem; colaPrioridad.pop();
            for (AristaDirigida<int> a : grafo.ady(actual)) {
                optimizarRuta(a);
            }

            if (distancia[actual] <= limite && !alcanzado[actual]) {
                puntosAlcanzables++;
                alcanzado[actual] = true;
            }
        }
    }

    int totalAlcanzables() const { return puntosAlcanzables; }
};

bool resuelveCaso() {
    int limite, nodos, conexiones;
    cin >> limite >> nodos >> conexiones;

    if (!cin) return false;

    DigrafoValorado<int> grafo = DigrafoValorado<int>(nodos);

    int inicio, fin, peso;
    for (int i = 0; i < conexiones; ++i) {
        cin >> inicio >> fin >> peso;
        grafo.ponArista(AristaDirigida<int>(inicio - 1, fin - 1, peso));
        grafo.ponArista(AristaDirigida<int>(fin - 1, inicio - 1, peso));
    }

    int numeroDeInicios;
    cin >> numeroDeInicios;
    vector<bool> visitados(nodos, false);
    vector<int> inicios(numeroDeInicios);

    for (int i = 0; i < numeroDeInicios; ++i) {
        cin >> inicio;
        inicios[i] = inicio - 1;
    }

    CaminoOptimo camino(grafo, inicios, limite, visitados);
    cout << camino.totalAlcanzables() << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}