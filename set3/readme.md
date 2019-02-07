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
Peak performance, *lightspeed*, $$l=min(1,B_m/B_c)$$. Hence, *performance*, $$P=min(P_{max},b_{max}/B_C)$$. Assumptions for this performance model:
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
One update: 4 loads (only 3 counts due to cache), 1 store. Code Balance, $B_C = 1.0 W/F$
