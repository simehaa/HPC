# Chapter 5, Basics of parallelization
Billions of CPU hours are wasted every year because supercomputer users have no idea about the limitations of parallel execution.

## 5.1 Why parallelize?
A single core might be sufficient, however at one point they might need more juice due to:
* program executes to slow in a tolerable amount of time (typically more than "overnight").
* memory requirements are more than available (i.e. slightly large 3D arrays).

## 5.2 Parallelism
Identify the parallelism inherent in the algorithm at hand.
### Data parallelism
Assume the program will process large quantities of data stored on a computer. If this can be performed in parallel: we have *data parallelism* (MIMD and SPMD) not to be confused with SIMD parallelism.
Example (medium-grained loop parallelism): assume an array A = s*B:
P1:
  A[0:N/2] = s*B[0:N/2]
P2:
  A[N/2:N] = s*B[N/2:N]
Example (Coarse-grained parallelism by domain decomposition):
Assume a large domain of i.e. mechanical stress: each worker (processor) can be assigned a part of the grid. (However communication along borders between parts is often needed): ghost layers are added. Focus:
* obtain load balance (might need som trial and error)
* reduce communication overhead (for example Jacobi method on 2d grid: should be split in squares like a cross, not in rectangles of columns etc.).
### Functional parallelism
MPMD. Different parts have different performance properties and harware requirements.
* Example (master-worker scheme): One compute element for administrative tasks while all others solve the actual problem. Master distributes work and collect results. (i.e. ray tracing)
* Example (Functional decomposition): Multiphysics simulations, for instance airflow around a race car and parallel CFD (computational fluid dynamics).

## 5.3 Parallel scalability
### Factors that limit parallel execution
*Parallelism* is a common problem in computing, manufacturing, traffic flow, business processed, etc. If N workers does the exact same amount of work, the total time takes T/N, which is a speedup of N.
Load imbalance => total time > T/N.
Overhead communication => total time > T/N. Questions to ask:
* How much faster can N workers perform the task?
* How much work can be done with N workers instead of one?
* What impact do the communication requirements of the parallel application have on performance and scalability?
* What fraction of the resources is actually used productively for solving the problem?
### Scalability metrics
Amount of work: s + p = 1 (s is the serial part and p is the perfectly parallelizable fraction). Reasons for nonvanishing serial part:
* Algorithmic limitations.
* Bottlenecks (shared resources).
* Startup overhead.
* Communication.
Single worker: $T_f^s = s + p$.
N workers: $T_f^p = s + p/N$.
Total amount of work: $s + pN^a$ ($a > 0$ is a free parameter).
Serial runtime: $T_v^s = s + pN^a$.
Parallel runtime: $T_v^p = s + pN^{a-1}$.
### Simple scalability laws
Serial performance: $P_f^s = (s+p)/T_f^s = 1$.
Parallel performance: $P_f^p = (s+p)/T_f^p(N) = (s + (1-s)/N)^{-1}$.
Application speedup (scalability): $S_f = P_f^p/P_f^s = (s + (1-s)/N)^{-1}$. (**Amdahl's Law**)
Ideal case ($a = 1$): unlimited performance: $S_v = s + (1-s)N$ (**Gustafson's law**).
### Parallel efficiency
Usually defined as: $\epsilon$ = (performance on N CPUs) / (N x performance on one CPU) = speedup/N.
### Serial performance vs. strong scalability
One should measure scalability for some processor numbers and fix the model parameters by *least squares fitting*. One question to ask: invest scalar optimization effort into the serial or the parallel part of an application: performance is the relevant metric. Assume that the serial part can be accelerated by a factor $\xi$. $N \geq 1/s - 1$. If $s \ll 1$, parallel efficiency $\epsilon \sim 0.5$: enlarge N does not make sense, and one should focus on the parallel part. It is not possible to achieve the same speedup $\xi$ in both the serial and parallel part.
### Refined performance models
Further analysis (Amdahl's and Gustafson's law are not appropriate) with additional communication factors, load imbalance, parallel startup overhead etc.
### Choosing the right scaling baseline
HPC computers are all massively parallel: multicore chips in multisocket shared-memory nodes connected by multilevel networks. *Hierarchy levels*. Two cores on one socket may lead to a bandwidth bottleneck. Scalability on a given parallel architecture should always be reported in relation to a relevant scaling baseline. ON HPC clusters (and multisocket multicore shared memory systems) intranode and internode scaling behaviour should be strictly separated.
### Case study: can slower processors compute faster?
A "truly scalable" computer may be built from slow CPUs and a reasonable network (by slow: baseline serial execution time $\mu \geq 1$). Interesting questions:
1. Does it make sense to use $\mu N$ slow processors instead of N standard CPUs?
2. What conditions must be fulfilled by communication overhead to achieve better performance with slow processors?
3. Does the concept work in strong and weak scaling scenarios alike?
4. What is the expected performance gain?
5. Can a slow machine deliver more performance than a machine with standard processors within the same power envelope?
#### Strong scaling
Scalability alone is no appropriate measure for application performance (it relates p performance to s performance on one CPU of the same speed). A lot of approximation theories for performance with different cases of communication, latency, bandwidth etc.
#### Strictly weak scaling
Gustafson scaling (work prop. to N), speedup function for slow computer = ...
#### Modified weak scaling
Scale work with N instead of $\mu N$. Communication bandwidth overhead dominates the gain.
### Load imbalance
Possible reasons for bad scalability:
* Communication overhead
* Synchronization loss
* False sharing
* NUMA locality
* bandwidth bottlenecks
* ...
However, *Load imbalance* is often overlooked. May occur when:
* Synchronization points are not reached at the same time by different workers => some workers will be idle for some time..
* Algorithmic issues.
* Optimization problems: might be hard to foresee how much time 1/Nth chunk takes (might be different for different chunks).
* Coarse granularity, limiting the available parallelism.
* Waiting for resources such as I/O or communication devices.
#### OS jitter
Source of load imbalance with surprising consequences. Has been identified in large-scale parallel systems built from commodity components. High number of workers, there is OS noise of a statistical nature: larger probability that a delay will occur between two synchronization points => load imbalance occurs more frequently
