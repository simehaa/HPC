# Chapter 3, Data access optimization
Most limiting performance factor: **data access**. On chip resources tend to be underutilized.
## 3.1 Balance analysis and lightspeed estimates
### Bandwidth-based performance modeling
*Balance*: i.e. *machine balance* is the ratio of possible memory Bandwidth [GWords/sec] to peak performance [GFlops/sec]. Balance examples [Words/Flops]:
* Cache: 0.5-1.0.
* Machine (memory): 0.03-0.5.
* Interconnect (high speed): 0.001-0.02.
* Interconnect (GBit ethernet): 0.0001-0.0007.
* Disk (or disk subsystem): 0.0001-0.01.

*Code balance*: data traffic/floating point ops [Words/Flops].
Peak performance, *lightspeed*, l=min(1,Bm/Bc). Hence, *performance*, P=min(Pmax,bm/B_C). Assumptions for this performance model:

* Arithmetic units are used (MULT, ADD) optimally.
* Double precision floating-point arithmetic.
* Data transfer and arithmetic overlap perfectly.
* Slowest data path determines the loop code's performance.
* System is in throughput mode.
* Memory Bandwidth that goes into the calculation of machine balance is possible to saturate to its full extent.

### The STREAM benchmarks
Four simple synthetic kernel loops which are supposed to fathom the capabilities of a processor's or a system's memory interface. Performance is usually reported as Bandwidth [GBytes/sec].

## 3.2 Storage order
Multidimensional arrays are important in scientific computing. How effectively these are saved in memory affects performance. *Strided* access to a 1D array: reduces spatial locality. leading to low utilization of available bandwidth. C implements *row major order* for multidim. arrays.

## 3.3 Case study: The Jacobi algorithm
An iterative method in numerical analysis and simulation, which can be used for i.e. solving the diffusion equation. It updates an array element according to the old values of the four neighbor points (and has a convergence critetion: not so important here).
* Assume Intel Xeon 5160.
* One update: 4 loads (only 3 counts due to cache), 1 store.
* Code Balance, Bc = 1.0 W/F.
* Theoretical machine balance, Bm = 0.111 W/F, but we use one MULT and 3 ADD ops, => Bm /= 4/6, Bm = 0.167 W/F.
* lightspeed, lbest = 0.222.
* Peak performance = 12 GFlops/sec * 4/6 (due to three ADD ops) = 8GFlops/sec.
* Predicted performance = 8 GFlops/sec * 0.222 = 1.78 GFlops/sec. Must be scaled down (STREAM copy), expected performance ~675 MFlops/sec.

## 3.4 Case study: Dense matrix transpose
Unfavorable way:
```
do i=1,N
  do j=1,N
    A(i,j) = B(j,i)
  enddo
enddo
```
Write access to A is strided. Assume cache size C and cache line size Lc. Performance regimes:
1. Effective bandwidth of the order of cache speeds. Spatial locality is of importance only between different cache levels; optimization potential is limited.
2. If the matrix is too large for cache but NLc <~ C, then the strided access to A is insignificant.
3. If N is even larger, NLc >~ C, then each store to A causes a cache miss and a subsequent write allocate: sharp drop in performance. Only 1/Lc cache line entries is actually used.
Better way:
```c
for (j=0; j<N; j+=m) {
  for (i=0; i<N; i++) {
    A[j+0,i] = B[i,j+0];
    A[j+1,i] = B[i,j+1];
    // ...
    A[j+m-1,i] = B[i,j+m-1];
  }
}
```
m must be chosen optimally! (balance read of B and write of A).
**TLB**: *translation lookaside buffer*, a factor that reduces bandwidth, it caches the mapping between logical and physical memory pages. Direct mapped cache of size C, every C/N iteration hits the same cache line. With a line length of Lc, the effective cache size is Ceff = Lc max(1, C/N).


## 3.5 Algorithm classification and access optimizations
Assumption for following optimization techniques: register pressure is not too large, otherwise the compiler will spill register data to cache: slow. Some terminology:
* MMM: matrix-matrix multiplication
* MVM: matrix-vector multiplication
* sMVM: sparse MVM
* JDS and CRS: schemes for sMVM
### O(N) / O(N)
Arithmetic operations and no. of data transfers of order N. Optimization is limited. However, *loop fusion* often has room for improvement.
### O(N^2) / O(N^2)
Typical in two-level loop nests: ex. dense matrix-vector multiplication, matrix transpose or matrix addition. *loop unrolling* can often be applied: outer loop is traversed with a stride **m** and inner loop is replicated **m** times (might need a remainder loop).
Combination of loop unrolling and fusion: *unroll and jam*. Performance gain can get close to **a factor of two**.
*loop blocking*: chunk up the size of the inner loops: increases cache hits.
### O(N^3) / O(N^2)
No. of ops > no. of data items (ex. dens matrix-matrix multiplication and dense diagonalization): optimization potential is large. If main memory bandwidth and latency are **not** the limiting factors for performance, then the code is cache-bound. Linear algebra and matrix operations should be used from optimized libraries.

## 3.6 Case study: Sparse matrix-vector multiply
Key ingredient in most iterative matrix diagonalization algorithms. *sparse matrix*: no. of non-zero entries grows linearly with the no. of rows.
### Sparse matrix storage schemes
Most important schemes:
* CRS (compressed row storage), well-suited for cache-based microprocessors. Has one array with the column indices and one array which point to the first index in each row.
* JDS (jagged diagonals storage), supports dependency and loop structures that are favorable on vector systems. All zeros are removed and all nonzeros are shifted left. Columns are stored in val and col_idx keeps the indices. jd_ptr holds start indices of the Nj jagged diagonals. perm stores the permutation map.
### Optimizing JDS sparse MVM
Unroll and jam should be applied, but usually requires length of inner loop to be independent of the outer loop index (violated if jagged diagonals are generally not all of the same length). *loop peeling*, for m-way unrolling, cuts (m X x) chinks and leaves m-1 partial diagonals over for separate treatment.


# Lecture notes
We need to know 2 hardware characteristics:
1. **Machine balance**, Bm = bmax [Words/sec]/ pmax [Flops/sec].
2. **Code balance**, Bc = #Words / #Flops.
Then we can hope for (ideally) performance of P=min(Pmax, bmax/Bc).
