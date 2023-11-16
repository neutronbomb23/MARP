#ifndef INDEXPQ_H
#define INDEXPQ_H

#include <vector>
#include <functional>

template <typename T, typename Comparator = std::less<T>>
class IndexPQ {
private:
    std::vector<int> pq, qp;
    std::vector<T> elements;
    int n;

    bool greater(int i, int j) {
        return Comparator()(elements[pq[i]], elements[pq[j]]);
    }

    void exch(int i, int j) {
        int swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }

public:
    IndexPQ(int maxN) : n(0), pq(maxN + 1), qp(maxN + 1, -1), elements(maxN + 1) {}

    bool isEmpty() {
        return n == 0;
    }

    bool contains(int i) {
        return qp[i] != -1;
    }

    void insert(int i, T element) {
        n++;
        qp[i] = n;
        pq[n] = i;
        elements[i] = element;
        swim(n);
    }

    T maxElement() {
        return elements[pq[1]];
    }

    int maxIndex() {
        return pq[1];
    }

    T elementOf(int i) {
        return elements[i];
    }

    int delMax() {
        int indexOfMax = pq[1];
        exch(1, n--);
        sink(1);
        qp[indexOfMax] = -1;
        // Optional: Not needed for correctness
        // elements[pq[n + 1]] = null;
        pq[n + 1] = -1;
        return indexOfMax;
    }

    void change(int i, T element) {
        elements[i] = element;
        swim(qp[i]);
        sink(qp[i]);
    }

    void swim(int k) {
        while (k > 1 && greater(k / 2, k)) {
            exch(k, k / 2);
            k = k / 2;
        }
    }

    void sink(int k) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && greater(j, j + 1)) j++;
            if (!greater(k, j)) break;
            exch(k, j);
            k = j;
        }
    }
};

#endif // INDEXPQ_H
