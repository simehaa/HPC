# Chapter 4, Parallel computers
Multiple cores ("compute elements") solve a problem in a cooperative way. Twice a year, parallel computers are ranked and published using the *LINPACK* benchmark. This chapter:
* Introduction to fundamental variants of parallel computers (*shared-memory* and *distributed memory*).
* Basic design rules and performance characteristics for the common types of networks.

## 4.1 Taxonomy of parallel computing paradigms
Dominating concepts: SIMD and MIMD.
* *Single Instruction, Multiple Data*, single or multiple cores. Examples: vector processors, GPUs.
* *Multiple Instruction, Multiple Data*, multiple cores operate on different data items concurrently.
There are more categories:
* SISD: conventional, nonparallel, single-processor.
* MISD: not a useful paradigm.

## 4.2 Shared-memory computers
CPUs work on a common, shared physical address space. Two varieties (different performance characteristics in terms of memory access):
 * Uniform memory access (UMA). Flat memory model: latenc and bandwidth are the same for all processors and memory locations (symmetric multiprocessing - SMP).
 * cache-coherent Nonuniform Memory Access (ccNUMA). Memory is physically distributed but logically shared.
### Cache coherence
Cache coherence mechanism are required for UMA/ccNUMA. CC protocols ensures  a consistent view of memory under all circumstances. Under control of cc logic discrepancy can be avoided: ex. MESI protocol:
  * Modified: cache line has been modified in THIS cache. Only upon eviction will memory reflect the most current state.
  * Exclusive: cache line has been read from memory but not (yet) modified (resides in no other cache).
  * Shared: cache line has been read from memory, not yet modified and there may be other copies of other caches.
  * Invalid: cache line does not reflect any sensible data. (normally because cache line was shared and another processor has requested ownership).
*bus snoops* is used: whenever notification of other caches seems in order, the originating cache broadcasts the corresponding cache line address through the system: all caches "snoop" the bus and react accordingly (drawback: reduce available bandwidth).
### UMA
Simplest implementation: dual-core processor (one path two memory is shared, through a *fronside bus*, FSB). General problem: bottlenecks are bound to occur when no. of socket or FSBs is larger than a certain limit.
### ccNUMA
*Locality domain* (LD) is a set of cores together with locally connected memory. Multiple LDs are linked via a coherent interconnect. One could think of each LD as a UMA builing block. Programmer's POV: transparent as all protocols are hardware handled.
Large supercomputers and cost-effective smaller clusters are always made from shared-memory builing blocks (usually ccNUMA). Two problems:
* Locality problem: network connections must have bandwidth and latency at least same order of magnitude as for local memory.
* Contention: two processors from different locality fights for memory bandwidth.

## 4.3 Distributed-memory computers
Each processor P connected to a local memory (no other CPU has direct access), this is outdated layout. This is typically handled by several nodes with 2+ CPUs with each network interface (NI) which is connected to a communication network. *NORMA - No remote memory access*: name of this architecture. Simplest interconnection: ethernet, however technologies with 10x the performance exists.

## 4.4 Hierarchical (hybrid) systems
Large-scale parallel computers are a mix of *shared memory* and *distributed memory*. The sweet spot for inexpensive commodity clusters are two-socket building blocks. **The optimal programming model is highly application- and system-dependent**.
Examples of hybrids:
Clusters with multicore processors with additional accelerator harware such as:
* applications-specific add-on cards
* GPUs
* FPGAs (field-prgrammable gate arrays)
* ASICs (application specific integrated circuits)
* co-processors
* etc.

## 4.5 Networks
Characteristics of the network that connects "execution units", "processors" and "compute nodes" play a **dominant role**.
### Basic performance characteristics of networks
The dominating distributed-memory interconnect is *InfiniBand*.
#### Point-to-point connections
Total transfer time for a message of size N bytes can be assumed as T=Tl + N/B, Tl latency, B is max network bandwidth. Time for various N can be measured by i.e. the standard Intel MPI benchmarks (IMB) suite.
N_{1/2} value is often reported (N when B = B_eff/2). It is desireable to improve both latency and bandwidth.
#### Bisection bandwidth
Another way to report bandwidth. Bb = sum(bandwidths of min no. of connections), when dividing the system in two equal parts.
### Buses
Common communication method in systems. Example: PCI (Peripheral Component Interconnect) bus. Drawback: *blocking*. The more devices connected, the lower average available bandwidth per device. In HPC, communication is limited to the processor, the socket level or to diagnostic networks.
### Switched and fat-tree networks
Communication devices are split in groups which are connected through a switch. Switches are connected with switch layers.
### Mesh networks
Compute elements located at a Cartesian grid intersection (as a multidim. hypercube), usually in a torus topology (makes "periodic boundaries": easier to communicate with neighbor devices).
### Hybrids
Combination of at least 2 topologies.
