# General-purpose cache-based microprocessor architecture
## Pipelining
Wind-up phase, throughput, wind-down phase.
A pipeline typically contains 10 - 35 stages (e.g. load, store, address calculation, instruction fetch, decode, ...).
**Avoid division, square-root and trigonometric functions** for HPS, as these typically require several tens or up to 100 cycles: *pipeline bubbles*.
**Avoid loop dependency** which is that step i depend on step i-1, as this causes a huge drop in performance.
## Superscalarity
More than on "result" per cycle. Requires proper out-of-order execution and compiler optimization for full potential. It is hard to achieve more than 2-3 instructions/cycle.
## SIMD
Single instruction multiple data. A CPU architecture which allows true parallelization for arithmetic operations.
# Memory Hierarchies
