# Exercise 1
Code balance for the following loops:
## a)
```C
for (j=0; j<N; j++)
  for (i=0; i<N; i++)
    y[j] += A[j][i]*B[i];
```
$2N^2$ flops, A, B is loaded every single iteration, y fits in the register:

$$
B_c = \frac{2N^2}{2N^2} = 1.
$$

## b)
```C
double s = 0.;
  for (i=0; i<N; i++)
    s += A[i]*A[i];
```
$2N$ flops, N loads of A (1 each iteration), s stays in the cache register:

$$
B_c = \frac{N}{2N} = 1/2.
$$

## c)
```C
double s = 0.;
for (i=0; i<N; i++)
  s += A[i]*B[i];
```
$2N$ flops, 2 loads each iteration, whereas s stays in the register:

$$
B_c = \frac{2N}{2N} = 1.
$$

## d)
```C
double s = 0.;
  for (i=0; i<N; i++)
    s += A[i]*B[K[i]];
```
$2N$ flops and N*(2.5 loads), only half a load for K, because int has half the amount of bytes than of a double:

$$
B_c = \frac{2.5N}{2N} = 5/4.
$$

Worst case, K[i] is a random integer of B array:
$$
B_c = \frac{9.5N}{2N} = 4.75.
$$
Best case, K[i] is constant resulting in maximum amount of cache hits:
$$
B_c = 1.5N/2N = 0.75.
$$
