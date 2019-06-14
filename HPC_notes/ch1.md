# Chapter 1, Modern processors
## 1.2 General-purpose cache-based microprocessor architecture
### Pipelining
Wind-up phase, *throughput* (finished instructions per clock cycle), wind-down phase.
A pipeline typically contains 10 - 35 stages (e.g. load, store, address calculation, instruction fetch, decode, ...).
**Avoid division, square-root and trigonometric functions** for HPC, as these typically require several tens or up to 100 cycles: *pipeline bubbles*.
**Avoid loop dependency** which is that step i depend on step i-1, as this causes a huge drop in performance.
### Superscalarity
More than on "result" per cycle. Requires proper out-of-order execution and compiler optimization for full potential. It is hard to achieve more than 2-3 instructions/cycle.
### SIMD
Single instruction multiple data. A CPU architecture which allows true parallelization for arithmetic operations.
## 1.3 Memory Hierarchies
CPU's have registers which can be accessed without delay and caches which holds copies of recently used data items. Main memory is slower and larger.
### Cache
Are used because obtaining data from main memory is painfully slow.
*latency*: the time it takes to transfer a zero-byte message.
Usually two layers of cache:
* L1: also split in two: L1I - instruction cache and L1D - data cache.
* L2: unified cache.
*temporal locality*: using data in cache again soon enough.
*load*: read request, if it's satisfied immediately it's a cache hit (low latency), else cache miss.
*reuse ratio* (beta): percentage of data items that is reused. It is zero for streaming, performance advantage is only significant if reuse ratio is close to one.
Cache lines is used for streaming.
*write miss*: cache memory consistency dictates that the cache line must be transferred from memory to cache before an entry can be modified: which is called *write allocate*. Strategies to avoid write allocate (can be applied by the compiler):
* Nontemporal stores: store instructions which bypasses cache (avoid cache "pollution")
* Cache line zero: instructions that zero out a cache line (must be used with care). Elements are evicted to memory.
### Cache mapping
*fully associative*: no restriction on which cache line can be associated with which memory locations (but cache logic must store addresses).
*m-way associative*: between fully as. and direct mapping. Each "color" has m possible places.
*direct mapping*: entire cache is mapped in memory.
### Prefetch
Cache lining, the first miss still causes latency. Line lengths ~ 64-128 bytes. Latency is still a problem. Prefetching supplies cache with data ahead of requirements
## 1.4 Multicore processors
Moore's law is still valid, but microprocessors start to hit the heat barrier. Multicore is popular among manufacturers (it is over-optimistic to assume that m cores causes m times the performance). *core* - *CPU* - *processor*. *socket* - physical package of cores. PCs typically have one socket, servers typically have 2-4 sockets.
Arrangement of cores:
* The cores can have separate caches or share certain levels (cache group), enables communication between cores.
* Integrated memory controller: which memory can be attached directly without separate logic ("chipset").
* Fast paths between caches: efficient cache coherent communication.
*parallell programming* is an absolute necessity for efficiency.
## 1.5 Multithreaded processors
Multi-pipelines microprocessors. (arithmetic units, caches, queues, memory interfaces etc. are not duplicated). Multiple instruction streams (threads) can be executed in parallel. The hardware must keep track of threads. This opens up for filling the pipeline bubbles. The performance of a single thread is not improved, but a stream of thread may cause overall better performance.
## 1.6 Vector processors
Massive parallelism built into execution units and (more importantly) the memory subsystem.
### Design principles
A vector CPU can issue a single instruction for a whole array if it is shorter than the vector length, otherwise the array is divided in chunks. Performance is drawn by a combination of massive pipeline parallelism with high-bandwidth memory access. **vectorization is vital**, otherwise is does not make sense to use a vector computer at all.
### Programming for vector architectures
*Mask registers*: boolean registers with vector length (loops with if else within).
Single branches (loops with only if) with expensive methods (divide, sqrt, etc.) can use the gather/scatter method.
