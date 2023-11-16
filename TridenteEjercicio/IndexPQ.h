#ifndef INDEXPQ_H_
#define INDEXPQ_H_

#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_map>

// E es el tipo de los elementos y T es el tipo de las prioridades
// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename E, typename T, typename Comparator = std::less<T>>
class IndexPQ {
public:
    // registro para las parejas < elem, prioridad >
    struct Par {
        E elem;
        T prioridad;
    };

private:
    // vector que contiene los datos (pares < elem, prio >)
    std::vector<Par> array;     // primer elemento en la posición 1

    // map que contiene las posiciones en array de los elementos
    std::unordered_map<E, int> posiciones;

    // Objeto función que sabe comparar prioridades.
    Comparator antes;

public:
    IndexPQ(Comparator c = Comparator()) : array(1), antes(c) {}

    void push(E const& e, T const& p) {
        if (posiciones.find(e) != posiciones.end())
            throw std::invalid_argument("No se pueden insertar elementos repetidos.");
        else {
            array.push_back({ e, p });
            posiciones[e] = size();
            flotar(size());
        }
    }

    void update(E const& e, T const& p) {
        int i = posiciones[e];
        if (i == 0) // el elemento e se inserta por primera vez
            push(e, p);
        else {
            array[i].prioridad = p;
            if (i != 1 && antes(array[i].prioridad, array[i / 2].prioridad))
                flotar(i);
            else // puede hacer falta hundir a e
                hundir(i);
        }
    }

    int size() const {
        return int(array.size()) - 1;
    }

    bool empty() const {
        return size() == 0;
    }

    Par const& top() const {
        if (size() == 0)
            throw std::domain_error("No se puede consultar el primero de una cola vacia");
        else return array[1];
    }

    void pop() {
        if (size() == 0) throw std::domain_error("No se puede eliminar el primero de una cola vacía.");
        else {
            posiciones.erase(array[1].elem);
            if (size() > 1) {
                array[1] = std::move(array.back());
                posiciones[array[1].elem] = 1;
                array.pop_back();
                hundir(1);
            }
            else
                array.pop_back();
        }
    }

private:
    void flotar(int i) {
        Par parmov = std::move(array[i]);
        int hueco = i;
        while (hueco != 1 && antes(parmov.prioridad, array[hueco / 2].prioridad)) {
            array[hueco] = std::move(array[hueco / 2]);
            posiciones[array[hueco].elem] = hueco;
            hueco /= 2;
        }
        array[hueco] = std::move(parmov);
        posiciones[array[hueco].elem] = hueco;
    }

    void hundir(int i) {
        Par parmov = std::move(array[i]);
        int hueco = i;
        int hijo = 2 * hueco;
        while (hijo <= size()) {
            if (hijo < size() && antes(array[hijo + 1].prioridad, array[hijo].prioridad))
                ++hijo;
            if (antes(array[hijo].prioridad, parmov.prioridad)) {
                array[hueco] = std::move(array[hijo]);
                posiciones[array[hueco].elem] = hueco;
                hueco = hijo; hijo = 2 * hueco;
            }
            else break;
        }
        array[hueco] = std::move(parmov);
        posiciones[array[hueco].elem] = hueco;
    }
};

#endif /* INDEXPQ_H_ */

