
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

int calcularParches(vector<int>& agujeros, int L) {
    sort(agujeros.begin(), agujeros.end()); // Aseg�rate de que los agujeros est�n ordenados
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
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
