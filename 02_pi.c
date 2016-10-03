#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2

static long num_steps = 100000000;
double step, pi = 0.0;

int main(void)
{
  step = 1.0 / num_steps;
  double t = omp_get_wtime();
  omp_set_num_threads(NUM_THREADS);
  
  #pragma omp parallel 
  {  
    int id = omp_get_thread_num();
    int _nthreads = omp_get_num_threads();
    double x, sum = 0.0;

    for (int i = id; i < num_steps; i += _nthreads)
    {
      x = (i + 0.5) * step;
      sum += (4.0 / (1.0 + (x * x)));
    }
    sum *= step;
    
    #pragma omp atomic
    pi += sum;
  }

  t = omp_get_wtime() - t;
 
  printf("PI=%f Time elapsed=%f\n", pi, t);
}

