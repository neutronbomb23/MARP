
/*@ <authors>
 *
 * Dorjee Khampa Herrezuelo Blasco
 * Marp13
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
using namespace std;
const int INF = 1e9 + 7; // Un valor grande para representar infinito


/*@ <answer>

La solución utiliza el algoritmo de Kruskal para encontrar 
el árbol de expansión mínima del grafo. En este contexto,
estamos interesados en la arista con el mayor peso en el MST
. Esta arista representa la autonomía mínima necesaria para viajar 
entre cualquier par de ciudades en la red, porque en el peor de los casos,
necesitaremos cruzar esta arista para moverse de una ciudad a otra.

La lógica detrás de esto es que, en un MST, cualquier ruta entre dos
nodos pasa por las aristas de menor peso primero, y la arista de mayor 
peso en ese árbol sería la "limitante" en términos de autonomía requerida.

El coste del algoritmo es O(M log M), donde M es el número de aristas,
debido principalmente a la ordenación de las aristas y la construcción del MST.

@ </answer> */


int autonomiaMinimaKruskal(GrafoValorado<int>& grafo) {
    vector<Arista<int>> aristas = grafo.aristas();
    sort(aristas.begin(), aristas.end());  // Ordenamos las aristas por peso
    ConjuntosDisjuntos cjtos(grafo.V());

    int aristaMax = 0;  // Esta variable contendrá el valor de la arista más grande en el MST
    for (const Arista<int>& arista : aristas) {
        int v = arista.uno();
        int w = arista.otro(v);
        if (!cjtos.unidos(v, w)) {
            cjtos.unir(v, w);
            aristaMax = max(aristaMax, arista.valor());
        }
    }

    return aristaMax;
}

bool resuelveCaso() {
    int N, M;
    cin >> N >> M;

    if (!cin)
        return false;

    GrafoValorado<int> grafo(N);
    ConjuntosDisjuntos cjtos(N);

    for (int i = 0; i < M; ++i) {
        int v, w, valor;
        cin >> v >> w >> valor;
        grafo.ponArista({ v - 1, w - 1, valor });
        cjtos.unir(v - 1, w - 1);
    }

    if (cjtos.num_cjtos() > 1) {
        cout << "Imposible" << "\n";
    }
    else {
        cout << autonomiaMinimaKruskal(grafo) << "\n";
    }

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
