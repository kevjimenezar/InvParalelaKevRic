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
    sort(vec.begin(),vec.end());
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

vector<int> findCoincidences(const vector<int>& vec, const vector<int>& fib) {
    vector<int> result;
    for (int num : vec) {
        auto n = find(fib.begin(), fib.end(), num);
        if (n != fib.end()) {
            result.push_back(num);
        }
    }
    auto it = unique(result.begin(), result.end()); // Eliminacion de duplicados
    result.resize(distance(result.begin(), it));
    result.insert(result.begin() + 1,1);
    return result;
}


int main() {

    int m = 1000000; // Tamaño del vector
    int n = 100000; // Rango de números aleatorios

    vector<int> randomVector = genVector(m, n);
    vector<int> fib = genFibonacci(n);
    vector<int> coinc = findCoincidences(randomVector,fib);

    cout<<endl<<endl;
    for (int num : fib) {
        cout << num << " ";
    }

    cout<<endl<<endl;
    cout<<endl<<endl;
    cout<<endl<<endl;
    for (int num : coinc) {
        cout << num << " ";
    }
    return 0;
}
