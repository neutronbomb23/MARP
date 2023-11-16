
/*@ <authors>
 *
 * Dorjee Khampa Herrezuelo Blasco MARP 13
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int calcularParches(vector<int>& agujeros, int L) {
    sort(agujeros.begin(), agujeros.end()); // Asegúrate de que los agujeros estén ordenados
    int parches = 0;
    int alcance = 0;
    for (int i = 0; i < agujeros.size();) {
        ++parches;
        alcance = agujeros[i] + L;
        while (i < agujeros.size() && agujeros[i] <= alcance) {
            ++i;
        }
    }
    return parches;
}

void resuelveCaso() {
    int N, L;
    cin >> N >> L;
    vector<int> agujeros(N);
    for (int i = 0; i < N; ++i) {
        cin >> agujeros[i];
    }
    cout << calcularParches(agujeros, L) << '\n';
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);;
#endif
    return 0;
}
