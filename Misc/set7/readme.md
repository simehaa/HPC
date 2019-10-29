# Week 7
## Exercise 1
### a)
Not suitable for parallelism, because the loop has to iterate sequentially.
```C
for (i=0; i < (int) sqrt(x); i++) {
  a[i] = 2.3 * x;
  if (i < 10) b[i] = a[i];
}
```
### b)
Not suitable for parallelism, because the loop has to iterate sequentially.
```C
flag = 0;
for (i = 0; (i<n) & (!flag); i++) {
  a[i] = 2.3 * i;
  if (a[i] < b[i]) flag = 1;
}
```
### c)
```C
#pragma omp parallel for
for (i = 0; i < n; i++) a[i] = foo(i);
```
### d)
```C
#pragma omp parallel for
for (i = 0; i < n; i++) {
  a[i] = foo(i);
  if (a[i] < b[i]) a[i] = b[i];
}
```
### e)
Not suitable for parallelism, because after the `break`-statement, no `a[i]` is supposed to be updated.
```C
for (i = 0; i < n; i++) {
  a[i] = foo(i);
  if (a[i] < b[i]) break;
}
```
### f)
```C
dotp = 0;
#pragma omp parallel for reduction(+:dotp)
for (i = 0; i < n; i++) dotp += a[i] * b[i];
```
### g)
```C
#pragma omp parallel for
for (i = k; i < 2*k; i++) a[i] = a[i] + a[i-k];
```
`a[i-k]` is actually independent due to the interval $i \in[k,2k-1]$.
### h)
Not suitable, because `a[i-k]` might not be independent if $n>2k-1$.
```C
for (i = k; i < n; i++) a[i] = b * a[i-k];
```
## Exercise 2
