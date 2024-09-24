#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <omp.h>
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

// Función para generar un vector con la secuencia de Fibonacci
vector<int> genFibonacci(int limit) {
    vector<int> fib = {0, 1};
    while (true) {
        int next = fib[fib.size() - 2] + fib[fib.size() - 1]; //Fn = Fn–2 + Fn–1
        if (next > limit) break; // Verificacion del limite
        fib.push_back(next);
    }
    return fib;
}

// Función para eliminar duplicados y ordenar
vector<int> deleteDup(vector<int>& result) {
    auto it = unique(result.begin(), result.end()); // Eliminar de duplicados
    result.resize(distance(result.begin(), it));
    result.insert(result.begin() + 1, 1); // Se agrega el 1 ya que se repite en la secuencia
    sort(result.begin(), result.end());
    return result;
}

// Función para encontrar los numeros de fibonacci en el vector random
vector<int> findCoincidences(const vector<int>& vec, const vector<int>& fib) {
    vector<int> result;
    #pragma omp parallel default(none) shared(vec, fib, result) // Inicio del proceso en paralelo
    {
        #pragma omp for // Se procesa ya en paralelo el bucle for
        for (int num: vec) {
            if (find(fib.begin(), fib.end(), num) != fib.end()) { // Verificacion ya que si no se encuentra devuelve el final de fib
                #pragma omp critical // Proporciona seguridad de acceso al vector con varios hilos
                {
                    result.push_back(num);
                }
            }
        }
    }
    return deleteDup(result);
}


int main() {

    int m = 1000000; // Tamaño del vector
    int n = 100000; // Rango de números aleatorios

    vector<int> randomVector = genVector(m, n);
    vector<int> fib = genFibonacci(n);
    vector<int> coinc = findCoincidences(randomVector,fib);

    cout<<"Los números originales de la sucesión de Fibonacci son:"<<endl;
    for (int num : fib) {
        cout << num << " ";
    }

    cout<<endl<<endl;
    cout<<"Los números que contrastados coinciden con la suceción de Fibonacci son:"<<endl;
    for (int num : coinc) {
        cout << num << " ";
    }
    return 0;
}
