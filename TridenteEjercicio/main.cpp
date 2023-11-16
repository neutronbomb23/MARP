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

  /*@ <answer>
  *
  * El problema plantea determinar el ranking de las palabras más citadas
  * a lo largo del tiempo. Para resolver este problema, se hace uso de una
  * estructura de datos de cola de prioridad indexada, que permite actualizar
  * las prioridades de los elementos y recuperar el elemento con la mayor
  * prioridad en tiempo constante. Las prioridades se basan tanto en el número
  * de menciones como en el tiempo de la última actualización.
  *
  * Coste: O(n log n), siendo n el número de eventos, debido a las operaciones
  * sobre la cola de prioridad indexada.
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "IndexPQ.h"
using namespace std;

struct Tema {
    int menciones;
    int horaUltimaActualizacion;
};

struct TemaComparator {
    bool operator()(Tema const& a, Tema const& b) const {
        if (a.menciones != b.menciones)
            return a.menciones > b.menciones;
        return a.horaUltimaActualizacion > b.horaUltimaActualizacion;
    }
};

bool resuelveCaso() {
    int numEventos;
    cin >> numEventos;

    if (!cin)
        return false;

    unordered_map<string, Tema> temas;
    IndexPQ<string, Tema, TemaComparator> cola;
    int tiempoActual = 0;

    for (int i = 0; i < numEventos; ++i) {
        string tipo;
        cin >> tipo;

        if (tipo == "C") {
            string tema;
            int n;
            cin >> tema >> n;

            temas[tema].menciones += n;
            temas[tema].horaUltimaActualizacion = tiempoActual;
            cola.update(tema, temas[tema]);

        }
        else if (tipo == "E") {
            string tema;
            int n;
            cin >> tema >> n;

            temas[tema].menciones -= n;
            temas[tema].horaUltimaActualizacion = tiempoActual;
            cola.update(tema, temas[tema]);

        }
        else { // TC
            for (int j = 1; j <= 3 && !cola.empty(); ++j) {
                cout << j << " " << cola.top().elem << "\n";
                cola.pop();
            }
        }
        tiempoActual++;
    }

    cout << "---\n";
    return true;
}

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
