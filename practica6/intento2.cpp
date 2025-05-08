#include <iostream>
#include <omp.h>

using namespace std;

#define N 24

int main() {
    int tid, nthr;
    int A[N];

   
    for (int i = 0; i < N; i++) {
        A[i] = 0;
    }

    
    cout << "\nIntroduce el número de threads ---> ";
    cin >> nthr;

   
    #ifdef _OPENMP
    omp_set_num_threads(nthr);
    #endif

    
    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        cout << "Thread " << tid << " en marcha" << endl;

        A[tid] = tid + 10;

        cout << "El thread " << tid << " ha terminado" << endl;
    }

    
    for (int i = 0; i < N; i++) {
        cout << "A[" << i << "] = " << A[i] << endl;
    }
    return 0;
}