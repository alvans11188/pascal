#include <iostream>
#include <omp.h>

using namespace std;

#define N 24

int main() {
    int tid, nthr;
    int A[N];

    
    for (int i = 0; i < N; i++) A[i] = 0;

    
    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        cout << "Thread " << tid << " en marcha (región 1)" << endl;
        A[tid] = tid + 10;
        cout << "El thread " << tid << " ha terminado (región 1)" << endl;
    }

    for (int i = 0; i < N; i++)
        cout << "A[" << i << "] = " << A[i] << endl;

    cout << "\n>> Fin de la primera región paralela\n\n";

    
    cout << "Introduce el número de threads ---> ";
    cin >> nthr;

    #ifdef _OPENMP
    omp_set_num_threads(nthr);
    #endif

    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        cout << "Thread " << tid << " en marcha (región 2)" << endl;
        A[tid] = tid + 100;
        cout << "El thread " << tid << " ha terminado (región 2)" << endl;
    }

    for (int i = 0; i < N; i++)
        cout << "A[" << i << "] = " << A[i] << endl;

    cout << "\n>> Fin de la segunda región paralela\n\n";

    
    #pragma omp parallel private(tid) num_threads(6)
    {
        tid = omp_get_thread_num();
        cout << "Thread " << tid << " en marcha (región 3)" << endl;
        A[tid] = tid + 1000;
        cout << "El thread " << tid << " ha terminado (región 3)" << endl;
    }

    for (int i = 0; i < N; i++)
        cout << "A[" << i << "] = " << A[i] << endl;

    cout << "\n>> Fin de la tercera región paralela\n";

    return 0;
}