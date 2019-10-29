# Lecture notes
Two reasons:
1. Solve problems faster.
2. Solve larger problems
Identify parallelism: how can multiple compute elements collaborate to solve the computational problem?
*SPMD*: single program multiple data.
# OpenMP
Standardized method for shared memory parallelization.
For-loops: sentral in scientific computing.

Example: $s = a_0^2 + a_1^2 + ... + a_N^2$:
```C
#pragma omp parallel
{
  int num_threads, thread_id;
  num_threads = omp_get_num_threads();
  thread_id = omp_get_thread_num();
}

#pragma omp parallel for reduction(+:s)
  for (int i=0; i<N; i++) {
    s = s + a[i]*a[i]; //*
  }

#pragma omp parallel for
  for (int i=0; i<N; i++) {
    a[i] = b[i] + c[i];
  }

#pragma omp parallel for schedule(static|dynamic|guided [,chunk])

# pragma omp parallel private (r, i)
{
  #pragma single
  {
    for (i=0; i<N; i++) {
      r = rand();
      if (p[i] > r) {

        #pragma task
        {
          do_some_work(p[i]);
        }

      } // end if
    } // end for
  } // end single
} // end parallel
```
