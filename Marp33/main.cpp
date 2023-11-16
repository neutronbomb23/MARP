
/*@ <authors>
 *
 * Dorjee Khampa Herrezuelo Blasco MARP13
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using PQ = priority_queue<int, std::vector<int>, std::greater<int>>;
/*@ <answer>

La solución utiliza un algoritmo voraz para maximizar las victorias asignando 
defensas contra ataques ordenados de menor a mayor. El coste es de 
\( O(N \log N) \) debido a la ordenación de los datos de entrada.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
// Función para calcular el número máximo de victorias
int calcularVictorias(vector<int>& defensa, vector<int>& ataque) {
    sort(defensa.begin(), defensa.end());
    sort(ataque.begin(), ataque.end());

    int victorias = 0;
    size_t indice_defensa = 0;

    // Recorremos el vector de ataque
    for (size_t i = 0; i < ataque.size(); ++i) {
        // Buscamos el primer equipo de defensa que pueda ganar
        while (indice_defensa < defensa.size() && defensa[indice_defensa] < ataque[i]) {
            ++indice_defensa;
        }
        // Si encontramos un equipo, contamos la victoria
        if (indice_defensa < defensa.size()) {
            ++victorias;
            ++indice_defensa; // Pasamos al siguiente equipo de defensa
        }
        else {
            // No hay más equipos que puedan ganar
            break;
        }
    }

    return victorias;
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin) return false;

    vector<int> ataque(N), defensa(N);

    for (int i = 0; i < N; ++i) {
        cin >> ataque[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> defensa[i];
    }

    cout << calcularVictorias(defensa, ataque) << endl;

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
