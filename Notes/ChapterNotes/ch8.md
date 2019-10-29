# Chapter 8, Loacality optimizations on ccNUMA architectures
Applications bound by memory bandwidth, locality and contention problems tend to turn up when threads and their data are not carefully placed across the locality domains of a ccNUMA system.
## 8.1 Locality of access on ccNUMA
Placement problems:
1. Make sure memory gets mapped into the locality domains of processors that actually access them.
2. Threads/processes must be *pinned* to those CPUs which had originally mapped their memory regions in order not to lose locality of access.

Even with an extremely fast NUMA interconnect, the contention problem cannot be eliminated. No interconnect, can turn ccNUMA into UMA.
### Page placement by first touch
First touch policy: a page gets mapped into the locality domain of the processor that first writes to it (allocating is not sufficient). Considerations:
* write memory in parallel, and then program so that the same length loop is used.
* the hardware must be capable of scaling memory bandwidth across locality domains.

It is not always at the programmer's discretion how and when data is touched first: in C/C++ global data is initialized before main() starts.
In case of doubt: the system documentation should be consulted.

### Access locality by other means
OSs often feature advanced tols for explicit page placement and diagnostics. Typical capabilities:
* Setting policies or preferences to restrict mapping of memory pages to specific locality domains (irrespective of allocation).
* Setting policies for distributing the mapping of successively touched pages across locality domains in a "round-robin" or even random fashion.
* diagnosing the current distribution of pages over LDs, probably on a per-process basis. (Linux: see numatools package).

## 8.2 Case study: ccNUMA optimizations of sparse MVM
See book. (p. 191)

## 8.2 Placement pitfalls
Data placement is important on ccNUMA. In principle ccNUMA is superior when it comes to scalability of memory-bound codes, however, UMA are much easier to handle.

Inadequate statement: placement problems are restricted to shared-memory programming (NOT true).
### NUMA-unfriendly OpenMP scheduling
Dynamic scheduling will necessarily lead to scalability problems if the thread team is spread across several LDs. May be best to distribute the working set's memory pages round-robin across the domains and hope for a statistically even distribution of accesses.

### File system cache
Cache can be helpful for good I/O performance. Buffer cache can be a problem: if a parallel runs on clusters of ccNUMA, performance may have strong fluctuations: if a large buffer cache is on ONE node, the performance of the whole parallel region can be affected.

## 8.4 ccNUMA issues with C++
### Arrays of objects
An array of objects can be allocated with `new[]`. Constructor is called for each array member. `new` knows nothing about NUMA, therefore all calls are done by the thread executing `new`, hence the problem: all data ends up in that thread's local memory.
First: map the memory pages to the correct nodes so that access becomas local for each thread, then call constructors (see *placement new*, which does not call any constructor). Avoiding this situation is hardly possible with C++ if one insists on constructing arrays of objects with new[]. Best advice: call object constructors explicitly in a loop and use a vector for holding pointers only (the class constructor is called from different threads concurrently and must be thread safe).

### Standard Template Library
C-style array handling is discouraged in C++: use `std::vector<>` instead. See book: C++ must be used with some ccNUMA awareness without to much hassle.

# Lecture notes
* *Cache coherence* protocols guarantee consistency between cached data in the shared memory at all times.
* A *locality domain* (LD) is a set of processor cores together with locally connected memory.
* Each LD is a UMA building block, and multiple LDs are linked via a coherent interconnect.
* Placement problem.  First touch: a page gets mapped into the locality domain of the processor that first writes to it. (**malloc** not sufficient and calloc is counterproductive: use *malloc* and initialize in a parallel).

## Some requirements
* Identical and reproducible loop scheduling: *static* and *identical chunksize*.
* For succesive parallel loops (same no. of iter and parallel threads): each thread should get the same part of iteration space in all loops: use *static* and *identical chunksize*.
* Beware of cache-coherence traffic: can destroy achievable aggregate memory bandwidth.
* Beware of global data (initialized before `main()`).
* `dynamic` scheduling could be preferable over `static` with poorly load-balanced situations. On the other hand, dynamic will lead to scalability problems if the thread team is spread across several locality domains.
* Disk I/O operations cause OSs to set up buffer caches which store recently read or written file data for efficient re-use.
