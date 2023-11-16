#include <iostream>
#include "indexpq.h"

struct Par {
    int prioridad;
    int order;

    Par(int p, int o) : prioridad(p), order(o) {}

    bool operator<(const Par& otro) const {
        if (prioridad != otro.prioridad) return prioridad < otro.prioridad;
        return order > otro.order;
    }

    bool operator>(const Par& otro) const {
        if (prioridad != otro.prioridad) return prioridad > otro.prioridad;
        return order < otro.order;
    }
};

int main() {
    IndexPQ<Par, std::greater<Par>> cola(10);

    cola.insert(1, Par(3, 1));
    cola.insert(2, Par(5, 2));
    cola.insert(3, Par(1, 3));

    std::cout << "Elemento con mayor prioridad: " << cola.maxElement().prioridad << std::endl;

    return 0;
}
