/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * MARP13 Dorjee Khampa Herrezuelo Blasco
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Digrafo.h"
using namespace std;

/*@ <answer>

El problema es una variación de detectar ciclos en un grafo dirigido.
Mapeamos las instrucciones en el programa oscuro a un grafo dirigido donde los vértices representan instrucciones y las aristas representan el flujo de control entre instrucciones.
Usando DFS, verificamos la presencia de ciclos. Si hay un ciclo, el programa podría no terminar.
Si llegamos al último vértice, el programa siempre terminará.

El coste de la solución es O(L), siendo L el número de instrucciones del programa oscuro, ya que cada instrucción es visitada una vez.

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)


bool esCiclico(Digrafo const& grafo, int v, vector<bool>& visitados, vector<bool>& pilaRecursion, bool& tieneCondicional) {
    visitados[v] = true;
    pilaRecursion[v] = true;

    for (int w : grafo.ady(v)) {
        if (!visitados[w] && esCiclico(grafo, w, visitados, pilaRecursion, tieneCondicional)) {
            return true;
        }
        else if (pilaRecursion[w]) {
            if (grafo.ady(v).size() > 1) {
                tieneCondicional = true;
            }
            return true;
        }
    }
    pilaRecursion[v] = false;
    return false;
}

bool resuelveCaso() {
    int L;
    cin >> L;
    if (!cin) return false;

    Digrafo grafo(L + 2);

    for (int i = 1; i <= L; ++i) {
        char tipo;
        int destino;
        cin >> tipo;

        if (tipo == 'J') {
            cin >> destino;
            grafo.ponArista(i, destino);
        }
        else if (tipo == 'C') {
            cin >> destino;
            grafo.ponArista(i, destino);
            grafo.ponArista(i, i + 1);
        }
        else {  // instrucción aritmética
            grafo.ponArista(i, i + 1);
        }
    }

    vector<bool> visitados(L + 2, false);
    vector<bool> pilaRecursion(L + 2, false);
    bool tieneCondicional = false;

    if (esCiclico(grafo, 1, visitados, pilaRecursion, tieneCondicional)) {
        if (tieneCondicional) {
            cout << "A VECES\n";
        }
        else {
            cout << "NUNCA\n";
        }
    }
    else {
        cout << "SIEMPRE\n";
    }

    return true;
}

//@ <answer>

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
