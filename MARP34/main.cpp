
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (MARPXX) de los autores de la solución.
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

void resuelveCaso() {
    int N, M, talla;
    cin >> N >> M;

    vector<int> tallasNecesarias(101, 0);
    vector<int> tallasDisponibles(101, 0);

    // Contar tallas necesarias
    for (int i = 0; i < N; ++i) {
        cin >> talla;
        tallasNecesarias[talla]++;
    }

    // Contar tallas disponibles
    for (int i = 0; i < M; ++i) {
        cin >> talla;
        tallasDisponibles[talla]++;
    }

    int equipacionesAComprar = 0;

    // Verificar tallas para cada jugador
    for (int i = 1; i <= 100; ++i) {
        // Si hay menos disponibles que necesarias, se deben comprar nuevas
        if (tallasNecesarias[i] > tallasDisponibles[i]) {
            equipacionesAComprar += tallasNecesarias[i] - tallasDisponibles[i];
        }
        // Pasar las sobrantes de la talla actual a la siguiente
        if (i < 100 && tallasDisponibles[i] > tallasNecesarias[i]) {
            tallasDisponibles[i + 1] += tallasDisponibles[i] - tallasNecesarias[i];
        }
    }

    // Escribir la solución
    cout << equipacionesAComprar << "\n";
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
