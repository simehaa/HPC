# Chapter 7, Efficient OpenMP programming
OpenMP is seemingly a very simple way to parallelize code.

# 7.1 Profiling OpenMP programs
Profiling tools can hint to the root problems (also with OpenMP). Thread profilers can usually summarize fraction of walltime spent in barriers, spin loops, critical section or locks, all of which might reveal performance problems.

# 7.2 Performance pitfalls
*Practical advice for avoiding typical OpenMP performance traps*.
### Ameliorating the impact of OpenMP worksharing constructs
Parallel region started OR parallel loop initiated/ended: overhead involved.
N threads, speedup:
$$
S_{omp}(N) = \frac{1}{s+\frac{1-s}{N} + \kappa N + \lambda}
$$.
Perfomance depends on the values of $\kappa$ and $\lambda$.
#### Run serial code if parallelism does not pay off
OpenMP `IF` clause helps with this. Another option is to reduce the number of threads by the `NUM_THREADS` clause.
#### Avoid implicit barriers
Most OpenMP worksharing (inc. `OM DO/END DO`) constructs insert automatic barriers at the end. `NOWAIT` (still in parallel region, do more work after this line) clause removes implicit barrier. NB: check if `NOWAIT` is really safe.
#### Try to minimize the number of parallel regions
The less often the team of threads needs to be forked or restarted, the less overhead is incurred.
#### Avoid "trivial" load imbalance
If the trip count is a small noninteger multiple of the number of threads, som threads end up doing significantly less work than others: load imbalance.
#### Avoid dynamic/guided loop scheduling or tasking unless necessary
Scheduling options (except `STATIC`) require computation or bookkeeping in order to figure out which thread is to compute the next chunk or task.
### Determining OpenMP overhead for short loops
How to estimate overheads? (Usually ~ 100-1000). General result: implicit and explicit barriers are the largest contributors to OpenMP-specific parallel overhead.
### Serialization
Most straightforward way to coordinate access to shared resources: critical region. Unless used with caution, these bear the potential of serializing the code.

With (big fat lock) protected access to each column,  serialization can then only occur if two threads try to update the same column at the same time.

C/C++: privatization insede the parallel region, and do the reduction manually. Should be prioritized over synchronization when possible.

### False sharing
What if cache coherence logic is forced to evict and reload in rapid succession: bad performance. If this is parallelized: performance will suffer due to a lot of cache misses and subsequent coherence traffic.

Solution: privatization in the form of reduction.

## 7.3 Case study: Parallel sparse matrix-vector multiply (sMVM)
Scheduling strategy: `DYNAMIC` or `GUIDED`. Result: performance gain from using two threads is far from a factor of 2. Extremely unsuitable for ccNUMA: poor scalability.
