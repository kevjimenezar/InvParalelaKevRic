#include <iostream>
#include <vector>
#include <random>
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

int main() {

    int m = 1000; // Tamaño del vector
    int n = 1000; // Rango de números aleatorios

    vector<int> randomVector = genVector(m, n);

    for (int num : randomVector) {
        cout << num << " ";
    }
    return 0;
}
