# Chapter 6, Shared-memory parallel programming with OpenMP
Price vs. performance sweet spot is mostly in the *two-socket* regime and possibly multiple cores and chips on a socket. Two concepts:
* **Shared-memory** pp: multiple processing elements with access to the same memory.
* **Distributed-memory** pp: Processing units needs to communicatewith specific commands (interconnection network and I/O devices).

OpenMP bindings are defined for C, C++ and Fortran.
## 6.1 Short introduction to OpenMP
**Shared memory**: all processors can immediate access all data from all other processors. OpenMP is a set of *compiler directives* which would otherwise (non-OpenMP-capable compiler) be regarded as comments. Central entity in an OpenMp program: it is a *thread* and NOT a process. Each thread can however have "private" data, but the others can access it if it knows the address location. However, OpenMP *forbids* access of private data between threads.
### Parallel execution
*Master thread* runs after startup of any OpenMP program. *Fork Join model*: the execution consists of parallel regions (with any no. of threads) and between parallel regions, only the master thread executes.
In C/C++: a parallel region is started with a *sentinel*:
```C
#pragma omp
```
Inside the parallel region each thread has its *thread ID* $$[0,1,...,N-1]$$. In C++:
```C
#include <omp.h>
#pragma omp parallel
{
  do_work_package(omp_get_thread_num(),omp_get_num_threads());
}
```
An OpenMP program should be written so that it does not assume a specific number of threads.
### Data scoping
All global variables is accesible inside a parallel region. How to make private variables:
1. By a PRIVATE clause to the OMP PARALLEL directive, which extends until the end of the parallel construct.
2. The index variable of a worksharing loop is automatically made private.
3. Local variables in a subroutine called from a parallel region are private to each calling thread (by copying). However variables carrying the static storage class in C/C++ will be shared.

In C/C++ one can simply declare local variables (less need for using the private clause).
### OpenMP worksharing for loops
Loops are natural candidates for parallelization (if iterations are independent). In a parallel loop each thread can execute its share of the loop's iteration space. *race condition* result depend on order of which the result is added up after a parallel execution.
### Synchronization
#### Critical regions
Concurrent write access to a shared variable (a shared resource) must be avoided to circumvent race conditions. This is solved by critical regions: wiar blocks for threads so that if thread 1 finished before thread 0, then 1 must wait. Critical regions hold the danger of *deadlocks* when used inappropriately: if one thread wait for a resource that will never become available. OpenMP solution: Critical region may be given a name in parantheses. Disadvantage: critical regions are named with unique identifiers: it is not possible to have the indexed.
#### Barriers
If it is necessary to synchronize all threads: barriers come in handy.
These synchronization points guarantees that all threads have reached it before any thread continues. NB: every thread must hit the barrier, otherwise a deadlock may occur. Barriers also have a performance impact.
### Reductions
Elegant OpenMP solution to accumulate the final result after a parallel construct (for addition, subtraction, multiplication, logical etc).
### Loop scheduling
Static: divides a loop into contiguous chinks of roughly equal size.
Chunk size can be varied with integers (i.e. Static, 3). Dynamic: assign chunks of work whose size is defined by the chunksize, to the next thread which has finished its current chunk. (Analogy: workers which finishes a task first go and get assignet a new task): load imbalance s greatly reduced. Downside: dynamic scheduling generates significant overhead if chunks are to small in terms of execution time. If applications are limited by memory bandwidth it may suffer access locality on ccNUMA systems: and static is the only choice.
### Tasking
Parallelization of "not" loops, but some other tasks that can be split up (i.e. working with a list of objects). This can be done by using `!$OMP TASK` and `!$OMP SINGLE`. OpenMP standard provides examples.
### Miscellaneous
#### Conditional compilation
C/C++: preprocessor symbol `_OPENMP` makes functions only defined if OpenMP is available.
#### Memory consistency
```c
SINGLE
// ...
END SINGLE
```
acts as an implicit barrier: no thread can continue before all threads have reached the same point: this enforces memory consistency.
#### Thread safety
As a general rule, I/O operations and general OS functionality (also common library functions) should be serialized because they may not be thread safe.
#### Affinity
The OpenMP standard gives no hints as to to how threads are to be bound by the cores of a system. Don't rely on the OS to make  a good choice regarding placement of threads.
#### Environment variables
Some aspects of OpenMP program execution can be influenced by environment variables. There may be a limit on each thread's stack size, can be adjusted by `OMP_STACKSIZE`. `OMP_DYNAMIC` can be set to `true` or `false`, which can allow the number of active threads to dynamically change between parallel regions.
## 6.2 Case study: OpenMP-parallel Jacobi algorithm
Convergence is satisfied when som value maxdelta (max abs difference over all matrix elems.) is below some epsilon.
* Working set $16N^2$ bytes, performance breakdown when working set does not fit into cache anymore. Second breakdown when N is very large: two successive lattice rows exceed L2 cache size.
* A single thread can saturate a socket's FSB for a memory-bound situation.
* With two threads, the maximum in-cache performance is the same. L2 can saturate the bandwidth demands of both cores in its group
* For $N<50$, location of threads is more important than their number.
## 6.3 Advanced OpenMP: Wavefront parallelization
*Gauss-Seidel* algorithm, can be used for solving systems of linear equations. It is also widely employed as a smoother component of multigrid methods. Consider a 3D representation of space, a sweep of the tensor will update an element according to its six closest neighbors. This can be parallelized by splitting up the tensor along one dimension.
