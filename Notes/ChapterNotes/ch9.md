# Chapter 9, Distributed-memory parallel programming with MPI
Message passing (MP) is the most tedious and complicated communication, but also the most flexible parallelization method. *MPI = Message Passing Interface*. Efficient parallel I/O: necessary ingredient in HPC. MPI 2.2 defines more than 500 functions.
## 9.1 Message passing
Required if the computer is of the distributed-memory type (there exists some other paradigms such as HPF, CAF and UPC, but MPI is dominant). MPI conforms on these rules:
* SIMD: single program multiple data. The same program runs on all processes, this is no restriction for MPMD (rank can be used uniquely).
* Program is written in a sequential language: Fortran, C, C++. Data exchange is done via calls to an appropriate library.
* All variables in a process are local to this process. There is no concept of shared memory.

## 9.2 A short introduction to MPI
### A simple example
Most MPI implementations provide compiler wrapper scripts (mpicc etc.)
```
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  printf("Hello World, I am %d of %d\n", rank, size);
  MPI_Finalize();
  return 0;
}
```
`MPI_COMM_WORLD` is created upon initialization and describes all processes that have been started as part of the parallel program. Only rank 0 is guaranteed to execute code beyond `MPI_Finalize()`. MPI programs are typically run `$ mpirun -np 4 ./test.exe` (example with four processes).

### Messages and point-to-point communication
For a message to successfully pass, the data type must mach for the sender and the reciever. *One* sender to *One* reciever: point-to-point communication.
```
MPI_Send(buf,      # message buffer
         count,    # No. of items
         datatype, # MPI data type
         dest,     # destination rank
         tag,      # message tag
         comm,     # communicator
         ierror    # return value
    )
```

```
MPI_Recv(buf,      # message buffer
         count,    # No. of items
         datatype, # MPI data type
         source,   # source rank
         tag,      # message tag
         comm,     # communicator
         status,   # status object
         ierror    # return value
    )
```
Explanation to some of the arguments:
* Status: can be used to determine parameters that have not been fixed eby the call's arguments.
* Count: the max no. of elements to be sent. Less elements may be sent: `MPI_Get_count()` can retrieve the real number.
* Source: normally source rank: may also be `MPI_ANY_SOURCE`: message may be sent by anyone.
* Tag: message tag: may also be `MPI_ANY_TAG`, tag should not matter.
* `status(MPI_TAG)` and `status(MPI_SOURCE)` contain the sender's message tag and rank, respectively.

```
MPI_Get_count(status,   # status object from MPI_Recv()
              datatype, # MPI data type recieved
              count,    # count (output argument)
              ierror)   # return value
```

Synchonousness of `MPI_Send()` is important: deadlocks may occur. If it works completely synchonously, the call cannot return to the user code before a msg transfer has at least started after a handshake (recv/send). However, the message may be copied to an *intermediate buffer* and return right away.
`MPI_Sendrecv()` and `MPI_Sendrecv_replace()` are handy, they combine the standard send and recieve in ONE call, and they **guarantee** to not be subject to the deadlock effects that occur with separate send and recieve.

### Collective communication
*Reduction operation*: accumulation of partial results performed on all processes in the communicator.
*Collective communication*: requires that every rank calls the same routine (impossible for a p2p message to match a recieve that was initiated using a collective call).
Simplest collective: barrier:
```
MPI_Barrier(comm,   # communicator
            ierror) # return value
```
The barrier enforces synchronization: all processes must call it before they are allowed to return to the user code. Barrier is overrated: other MPI routines allow for implicit/explicit sync. with finer control, but the barrier can be used for debugging/profiling.

**Useful** collective: *broadcast*:
```
MPI_Bcast(buffer,   # send/recieve buffer
          count,    # message length
          datatype, # MPI datatype
          root,     # rank of root process
          comm,     # communicator
          ierror)   # return value
```
A root rank (i.e rank 0) sends the same message to every rank, NB: every rank must actually call `MPI_Bcast()`. This is a very useful method when information must be shared across all ranks.

More advanced collective calls:
* `MPI_Gather()`: collects the send buffer contents of all processes and concatenates them in rank order into the recieve buffer of the root process.
* `MPI_Scatter()`: reverse of `MPI_Gather()`, distributing equal chunks of the root's send buffer.
* `MPI_Allgather()`: a combo of `MPI_Gather()` and `MPI_Bcast()`.

```
MPI_Reduce(sendbuf,  # send buffer
           recvbuf,  # recieve buffer
           count     # number of elems
           datatype, # MPI datatype
           op,       # MPI reduction operator
           root,     # root rank
           comm,     # communicator
           ierror)   # return value
```
`MPI_Reduce()` combines the contents of the sendbuf array on all processes, element-wise, using an operator encoded by the op argument, and stores the result in the recvbuf on root. Operators (op): i.e MPI_MAX, MPI_MIN, MPI_SUM and MPI_PROD.

* `MPI_Allreduce()` is a fusion of a reduction with a broadcast.
* `MPI_Reduce_scatter()` combines reduce/scatter.

Collectives > point-to-point contructs or combinations of simpler collectives that "emulate"
 the same semantics.

### Nonblocking point-to-point communication
All MPI functionalities: a call returns to the user program only after the msg transfer has progressed far enough (no problems with send/recv buffer).
* buffer can safely be modified: in MPI this is called  *blocking communication*.
* p2p communication can also be performed with nonblocking semantics: synchronization is ruled out (i.e. `MPI_Isend()`). This way communication and computation can be overlapped. The message buffer must **not** be used as long as the user program has not been notified that this is safe.

`MPI_Isend()` handy `MPI_Irecv()` have an extra argument `request`, which serves as an identifier by which the program can later refer to the pending communication request: `MPI_Request*` in C.
```
MPI_Test(request,   # pending request handle
         flag,      # true if request complete (int* in C)
         status,    # status object
         ierror)    # return value
MPI_Test(request,   # pending request handle
        status,     # status object
        ierror)     # return value
```
Potential problem: compiler has no way to know that `MPI_Wait()` can and usually will modify the contents of `buf`:
Fix:
Put the variable into a `COMMON` block.

Multiple requests at a time (which is an advantage of nonblocking communication):
```
MPI_Waitall(count,    # no. of requests
            requests, # request handle array
            statuses, # statuses array
            ierror)   # return value
```
|             | Point-to-point | Collective |
|-------------|:---------------|:-----------|
| Blocking    | MPI_Send()     | MPI_Barrier()
|             | MPI_Ssend()    | MPI_Bcast()
|             | MPI_Bsend()    | MPI_Scatter()/MPI_Gather()
|             | MPI_Recv()    | MPI_Reduce()
|             |               | MPI_Reduce_scatter()
|             |               | MPI_Allreduce()
| Nonblocking | MPI_Isend() | |
|  | MPI_Irecv() | |
|  | MPI_Wait()/MPI_Test() | |
|  | MPI_Waitany()/MPI_Testany() | |
|  | MPI_Waitsome()/MPI_Testsome() | |
|  | MPI_Waitall()/MPI_Testall() | |

### Virtual topologies
Setting up process grid and keeping track of which ranks have to exchange halo data is nontrivial. MPI support this recurring task in the form of *virtual topologies*. Moreover, they potentially allow the MPI library to optimize communications by employing knowledge about network topology:

A silly analogy: this is like hiring an experienced post officer which knows the neighborhood.

A computation example: consider a 3000 x 4000 array of double precision elements. A simulation runs on 3 x 4 = 12 processes (each process holds a chunk of 1000 x 1000). Each process has at most four neighbors.
```
MPI_Cart_create(comm_old,  # input communicator
                ndims,     # number of dims.
                dims,      # no. of processes in each dim.
                periods,   # periodicity per dimension
                reorder,   # true = allow rank reordering
                comm_cart, # new cartesian communicator
                ierror)    # return value
```
A handy function which generates a "Cartesian" communicator which can be used later to refer to the topology. Example (from above): (Fortran, I think)
```
MPI_Cart_create(MPI_COMM_WORLD,
                2,
                (/ 4, 3 /),
                (/ .false., .true. /), # open/periodic
                .false., # no rank reordering
                comm_cart,
                ierror)
```
If no. of MPI procs is given, finding an optimal extension of the grid in each direction requires some arithmetic:
```
MPI_Dims_create(nnodes, # no. of nodes in grid
                ndims,  # no. of cartesian dims.
                dims,   # input != 0: nodes fixed in this dir. input == 0: calculate nodes, output: no. of nodes in each dir
                ierror)
```
Notice, dims is both input and output, where each entry corresponds to a cartesian dim. A zero entry denotes a dim for which `MPI_Dims_create()` should calculate the no. of procs, a nonzero entry specifies a fixed no. of procs.

Reverse mapping, from cartesian coor to an MPI rank:
```
MPI_Cart_rank(comm_cart,   # cartesian communicator
              coors,       # cartesian process coordinates
              rank,        # return process rank in comm_cart
              ierror)
```

Lastly the `MPI_Cart_shift()` does it all in one step:
```
MPI_Cart_shift(comm_cart,    # cartesian communicator
               direction,    # direction of shift (0..ndims-1)
               disp,         # displacement
               rank_source,  # return source rank
               rank_dest,    # return destination rank
               ierror)
```
For source and destination rank, which returns the neighboring ranks, if a neighbor does not exist (beyond boundaries), the return will be `MPI_PROC_NULL`. This can also be a dummy argument for source/destination.

## 9.3 Example: MPI parallelization of a Jacobi solver
The following chapter is a thorough example of a Jacobi solver in 3D. MPI parallelization is much more complex than OpenMP in this case.
### MPI implementation
Two difficulties:
1. Convergence criterion: a reduction is required to get a global maximum. Solution: `MPI_Allreduce()`.
2. In order for a sweep to yield correct results, appropriate BCs must be implemented. Problem only for adjacent cells. Solution: *ghost* / *halo layers* are used to store copies of the boundary info.

Data flow:
1. Initialize grid and boundaries
2. Communicate halo layers
3. Sweep subdomains
4. Calculate global max deviation
5. Is convergence criterion satisfied
   * Yes: end
   * No: exchange grids and return to point 2

The hardest task is perhaps the communication required between two subdomains: the halo layers:
* Sending each chunk as a separate message is out of the question: network would be flooded with short messages.
* Solution: create two intermediate buffers per process: for sending and recieving. The size of all buffer should be large enough for the largest buffer!

Halo communication:
* `CopySendBuf()`/`CopyRecvBuf()`: useful routines.
* Six steps: send information each positive and negative cartesian direction

### Performance properties
We extinguish between weak and strong scaling scenarios.
#### Weak scaling
(This chapter is mainly about a theory for performance: weak scaling, which is tested. The experiments were consistent with the theory).

Weak scaling is about keeping the problem fixed (i.e. a 3D domain of $120^3$) and changing the no. of nodes.

Due to synchronization between subdomains, the overall runtime is dominated by the slowest process: which is the one with the largest no. of halo faces. We can expect reasonably linear scaling behavior even on slow networks.

#### Strong scaling
Strong scaling is about keeping the no. of nodes fixed and rather observing the effects of varying the problem size (i.e. $120^3$ vs $480^3$). Results show that the $120^3$ domain has a larger penalty ($10\% $) than the $480^3$ domain.
