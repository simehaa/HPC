# Basic optimization techniques for serial code
Single-processor optimization are important.
## Scalar profiling
*profiling*: gathering info. about behavior, specifically its use of resources (**runtime** important resource).
*hot spots* parts of program that require a dominant fraction of the runtime. First, hot spots must be determined, then the cause of stalling: data access to main memory or pipeline stall limits.
### Function- and line-based runtime profiling
1. Code instrumentations: let compiler modify func. calls
2. Sampling: interupt program to record counts.
*gprof*: profiling tool (for GCC use -pg flag, produces a gmon.out file that is interpreted at runtime).
### Hardware performance counters
### Manual instrumentation

## Common sense optimizations
### Do less work!
### Avoid expensive operations!
### Shrink the working set!

## Simple measures, large impact
### Elimination of common subexpressions
### Avoiding branches
### Using SIMD instruction sets

## The role of compilers
### General optimization options
### Inlining
### Aliasing
### Computational accuracy
### Register optimizations
### Using compiler logs

## C++ optimizations
### Temporaries
### Dynamic memory management
### Loop kernels and iterators
