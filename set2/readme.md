# Basic optimization techniques for serial code
Single-processor optimization are important.

## Scalar profiling
*profiling*: gathering info. about behavior, specifically its use of resources (**runtime** important resource).
*hot spots* parts of program that require a dominant fraction of the runtime. First, hot spots must be determined, then the cause of stalling: data access to main memory or pipeline stall limits.
### Function- and line-based runtime profiling
1. Code instrumentations: let compiler modify func. calls
2. Sampling: interupt program to record counts.
*gprof*: profiling tool (for GCC use -pg flag, produces a gmon.out file that is interpreted at runtime).
https://sourceware.org/binutils/docs/gprof/.
### Hardware performance counters
Performance counters (often < 10) are on-chip registers. Useful for profiling:
* Cache line transfers. Cache misses.
* No. of loads/stores.
* No. of FLOPS.
* Mispredicted branches.
* Pipeline stalls (bubbles).
* No. of instructions executed.
Interpreting the results requires experience!
### Manual instrumentation
Manual timing done by user with care: execution time should be larger than resolution of timer.

## Common sense optimizations
### Do less work!
Program should contain the least amount of operations necessary. I.e. if a loop with an if statement within runs, user might insert a break statement within the if test.
### Avoid expensive operations!
Expensive operations include trigonometric functions, exponentiation, etc.
**Replace expensive with simpler alternatives**. Ex.
* Integer pow: (((ax[i]+b)x[i]+c)x[i]+d)+e >> pow function.
* Float pow: try to pre-compute before loop.
* Pre-computed look-up tables. I.e. make a trigonometric table if the inputs are known (sin_list = [sin(pi), sin(2pi), ...]).
### Shrink the working set!
*working set*: memory the code uses (touches). More cache hits, fewer misses. This includes using the smaller byte data types (float etc.).

## Simple measures, large impact
### Elimination of common subexpressions
Considered a task for compilers. *loop incariant code motion*: pre-calculate complex expressions -> temporary variables.
### Avoiding branches
*tight loops*: few operations within: typical candidate for pipelining, loop unrolling, etc. BUT, compiler will find it difficult if the loop contains **condition branches**. Avoid these within loops if possible.
### Using SIMD instruction sets
*vectorizations*, and a vectorizable loop is generally faster with a single instruction.
Ideal scenario:
* independent iterations.
* no branches in the loop body.
* the arrays are accessed with a stride of one.
```
for (i=0; i<N; i++)
  r[i] = x[i] + y[i];
```
Assuming that the register can store 4 values, (intel may have 512 bits):
```
int i,rest=N%4;
for (i=0; i<N-rest; i+=4) {
  load R1 = [x[i],x[i+1],x[i+2],x[i+3]];
  load R2 = [y[i],y[i+1],y[i+2],y[i+3]];
  R3 = ADD(R1,R2);
  store [r[i],r[i+1],r[i+2],r[i+3]] = R3;
}
for (i=N-rest; i<N; i++) {
  r[i] = x[i] + y[i];
}
```
Beware of loop dependencies! RISC systems will not always benefit from vectorization.

## The role of compilers
Can be surprisingly smart and stupid simultaneously.
### General optimization options
Compiler offers optimization options (-O0, -O1, ...).
### Inlining
Function call uses resources: arguments are passed in registers or stack. Inlining reduce *register pressure*: CPU does not have enough registers required inside a complex computation. **Never rely on the compiler to optimize inlined code**. C++ inline is only a hint to the compiler (consult a compiler log to see if the function really was inlined).
Downside: may lead to problems with L1I cache capacity
### Aliasing

### Computational accuracy
### Register optimizations
### Using compiler logs

## C++ optimizations
### Temporaries
### Dynamic memory management
### Loop kernels and iterators
