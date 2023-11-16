/*
 * MUY IMPORTANTE: Solo se corregir�n los comentarios y el c�digo
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificaci�n fuera de esas etiquetas no ser� corregida.
 */

 /*@ <answer>
   *
   * MARP13 Dorjee Khampa Herrezuelo Blasco
   *
   *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

/*@ <answer>

Para resolver el problema se utiliza una cola de prioridad para almacenar a los partidos, como la vista en clase.
Se extrae siempre el partido con el mayor coeficiente.
El struct partido contiene los votos, los escanos asignados y el �ndice original de cada partido.
Para calcular el n� de escanos que se le asigna a cada partido, se insertan todos los partidos en la cola de prioridad.
Se repite 'N' veces el n� de escanos a asignar. Se saca el partido con el maayor coeficiente, se le asigna un escano en cuesti�n
Se vuelve a insertar en la cola, con el escano ya sumado. Despu�s se sacan los escano en orden.

El coste de esta soluci�n es O(N log C), donde C es el n�mero de Partidos. Se hacen operaciones de costes logar�tmico, son las operaciones
push y pop. 

 @ </answer> */



struct Partido {
    int votos;    
    int escanos; 
    int indice;  

    Partido(int v, int i) : votos(v), escanos(0), indice(i) {}

    //calcular coeficiente
    double coeficiente() const {
        return (double)votos / (1 + escanos);
    }

    //ooperador para comparar partidos en la cola de prioridad
    bool operator<(const Partido& other) const {
        if (coeficiente() == other.coeficiente()) {
            if (votos == other.votos) {
                return indice > other.indice;
            }
            return votos < other.votos;
        }
        return coeficiente() < other.coeficiente();
    } //compara por coeficiente, votos y despu�s por el �ndice.
};

bool resuelveCaso() {
    int C, N;
    cin >> C >> N;

    if (C == 0) //Sale
        return false;

    //nueva cola de prioridad para 
    priority_queue<Partido> cola;

    //leer votos de cada partido y anadirlo a la cola de prioridad
    for (int i = 0; i < C; ++i) {
        int votos;
        cin >> votos;
        cola.push(Partido(votos, i));
    }

    vector<int> escanos(C, 0);  //vector para almacenar los escanos de cada partido.

    // Asignar los N escanos
    for (int i = 0; i < N; ++i) {
        Partido top = cola.top();  //extrae el partido con el m�ximo coeoficiente
        cola.pop();

        escanos[top.indice] = ++top.escanos;  //meter el escano, m�ximo
        cola.push(top);  // meto el partido de nuevo con el escano que se acaba de asignar.
    }

    // Imprime todos los resultados

    for (int i = 0; i < C; ++i) {
        cout << escanos[i] << " ";
    }
    cout << '\n';

    return true;
}

int main() {
//#ifndef DOMJUDGE
//    ifstream in("casos.txt");
//    auto cinbuf = cin.rdbuf(in.rdbuf());
//#endif

    // Para cada caso
    while (resuelveCaso());

//#ifndef DOMJUDGE
//    cin.rdbuf(cinbuf);
//    system("PAUSE");
//#endif
    return 0;
}
