#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <omp.h>
#include <thread>
#include <chrono>
using namespace std;

// Ejemplo 1: Elementos de la Sucesión de Fibonacci en una lista aleatoria

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
vector<int> findCoincidences(const vector<int>& vec, const vector<int>& fib,const int& limit) {
    vector<int> result;
    #pragma omp parallel default(none) shared(vec, fib, result, limit) // Inicio del proceso en paralelo
    {
        #pragma omp for // Se procesa ya en paralelo el bucle for
        for (int num: vec) {
            if (find(fib.begin(), fib.end(), num) != fib.end() && num <= limit) { // Verificacion ya que si no se encuentra devuelve el final de fib y limite
                #pragma omp critical // Proporciona seguridad de acceso al vector con varios hilos
                {
                    result.push_back(num);
                }
            }
        }
    }
    return deleteDup(result);
}

// Ejemplo 2: Aproximaciones a la Proporción Áurea usando Fibonacci
vector<double> calcGoldenRatio(const vector<int>& fib) {
    vector<double> aproxs;
    int size = fib.size();
    
    #pragma omp parallel for // Procesar en paralelo
    for (int i = 2; i < size; i++) {
        double ratio = static_cast<double>(fib[i]) / fib[i - 1];
        #pragma omp critical // Sección crítica para evitar condiciones de carrera
        {
            aproxs.push_back(ratio);
        }
    }
    return aproxs;
}

//Ejemplo Complementario
class Flower {
    public:
        std::string name;
        int petals;
    };
    
    std::vector<Flower> defineFlowers() {
    return {
        {"Margarita comun", 13},
        {"Margarita gigante", 34},
        {"Girasol", 55},
        {"Rosa", 5},
        {"Lirio", 3},
        {"Jacinto", 8},
        {"Flor de loto", 13},
        {"Tulipan", 3},
        {"Amapola", 4},
        {"Dalia", 13},
        {"Crisantemo", 13},
        {"Orquidea", 3},
        {"Azucena", 6},
        {"Clavel", 5},
        {"Campanilla", 5},
        {"Pensamiento", 5},
        {"Geranio", 5},
        {"Girasol gigante", 89},
        {"Violeta", 5}
    };
}
    
    // Función para comprobar si la cantidad de pétalos de una flor se encuentran en la suceción
    bool isFibonacci(int petals, const vector<int>& coinc) {
    bool found = false;
    #pragma omp parallel for shared(coinc, petals) // Clausula de datos: TODOS LOS HILOS TIENEN ACCESO ya que no modifican
    for (size_t i = 0; i < coinc.size(); i++) {
        if (coinc[i] == petals) {
            #pragma omp critical
            {
                found = true;
            }
        }
    }
    return found;
}

//Revisa el vector de Flores y resuelve si su cantidad de pétalos pertenece a la sucesión de Fibonacci
void checkPetalsInFibonacci(const std::vector<Flower>& flowers, const std::vector<int>& coinc) {
    #pragma omp parallel for
    for (size_t i = 0; i < flowers.size(); i++) {
        const auto& flower = flowers[i];
        if (isFibonacci(flower.petals, coinc)) {
            #pragma omp critical // Evita interferencias en la salida
            {
                cout << "La flor " << flower.name << " con " << flower.petals << " petalos esta en la sucesion de Fibonacci." << endl;
            }
        } else {
            #pragma omp critical
            {
                cout << "La flor " << flower.name << " con " << flower.petals << " petalos NO esta en la sucesion de Fibonacci." << endl;
            }
        }
    }
}

int main() {
    int m = 1000000; // Tamaño del vector
    int n = 100000; // Rango de números aleatorios
    int limit = 89;

    vector<int> randomVector = genVector(m, n);
    vector<int> fib = genFibonacci(n);
    vector<int> coinc = findCoincidences(randomVector, fib, limit);
    
    cout << "Ejemplo 1:" << endl;
    cout << "Los numeros originales de la sucesion de Fibonacci son:" << endl;
    for (int num : fib) {
        cout << num << " ";
    }

    cout << endl << endl;
    cout << "Los numeros que contrastados coinciden con la sucecion de Fibonacci son:" << endl;
    for (int num : coinc) {
        cout << num << " ";
    }
    cout << endl << endl;
    
    
    
     // Para el ejemplo número 2, calculamos las aproximaciones de la proporción áurea usando toda la secuencia de Fibonacci
    vector<double> goldenRatioAprox = calcGoldenRatio(coinc);
    cout << "Ejemplo 2:" << endl;
    cout << "Las aproximaciones obtenidas de la Proporción Aurea son:" << endl;
    for (double num : goldenRatioAprox) {
        cout << num << " - ";
    }
    cout << endl << endl;
    
    
    
    
    // Definición de flores
    vector<Flower> flowers = defineFlowers();
    checkPetalsInFibonacci(flowers, coinc);
     
    return 0;
}