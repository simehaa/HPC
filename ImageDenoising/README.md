# Image Denoising
A project in the IN3200 course at University of Oslo, spring 2019. This readme file will only provide information about how to run the codes. For additional information about the algorithm and performance, see *report.pdf*.

There are three folders:
* parallel_code: containing the MPI parallelized code.
* serial_code: containing the serial code.
* simple-jpeg: containing various files that can handle .jpg files for C.

To compile and run, go in either directory *serial_code* OR *parallel_code*. Use:
```
$ make -j
$ make
```
(the `-j` is unnecessary but will compile all files parallelized).

1. Go to the desired folder: serial_code or parallel_code
2. put a grayscale .jpg image in the folder.
3. The codes are run with 4 additional command line arguments:
The serial code:
```
$ ./serial.x kappa maxiter infilename outfilename
```
The parallelized code:
```
$ mpirun -np num_procs ./parallel.x kappa maxiter infilename outfilename
```
where
* `float kappa`, typically $\leq 0.2$.
* `int maxiter`, typically 100-1000.
* `char* infilename`, filename for image (i.e. mona_lisa_noisy.jpg)
* `char* outfilename`, filename for output image
* `int num_procs`, the number of processes for the MPI code.

**Note**: the code is set up to read *.jpg* files, other file types will require additional libraries.
To remove object files and executable files:
```
$ make clean
```
