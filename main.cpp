#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

// Función para generar un vector de números aleatorios
vector<int> genVector(int m, int n) {
    vector<int> vec(m); // Creacion del vector
    random_device rd; // Semilla aleatoria
    mt19937 gen(rd()); // Generador de números aleatorios
    uniform_int_distribution<> dist(0, n); // Distribución uniforme entre 0 y n

    for (int i = 0; i < m; i++) {
        vec[i] = dist(gen);
    }
    return vec;
}
vector<int> genFibonacci(int limit) {
    vector<int> fib = {0, 1};
    while (true) {
        int next = fib[fib.size() - 2] + fib[fib.size() - 1]; //Fn = Fn–2 + Fn–1
        if (next > limit) break; // Verificacion del limite
        fib.push_back(next);
    }
    return fib;
}

int main() {

    int m = 1000; // Tamaño del vector
    int n = 1000; // Rango de números aleatorios

    vector<int> randomVector = genVector(m, n);
    vector<int> fib = genFibonacci(n);

    for (int num : randomVector) {
        cout << num << " ";
    }
    cout<<endl<<endl;
    for (int num : fib) {
        cout << num << " ";
    }
    return 0;
}
