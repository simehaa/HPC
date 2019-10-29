# PageRank
The code reads a .txt file which must be formatted in this manner:
```
# Directed graph (each unordered pair of nodes is saved once): web-NotreDame.txt
# University of Notre Dame web graph from 1999 by Albert, Jeong and Barabasi
# Nodes: 325729 Edges: 1497134
# FromNodeId	ToNodeId
0	0
0	1
0	2
```
* Four lines with information of which the third line is important: number of nodes and edges.
* Following with an arbitrary amount of lines with to numbers. Each of these lines corresponds to a link to one webpage ID from a webpage ID (these numbers can be the same: self linkage)

This repository includes a data file from the University of Notre Dame with roughly 1.5 million links on roughly 325 000 webpages.

## Run the code
Compile by using
```
$ make
```
And run by using
```
$ ./pagerank.exe web-NotreDame.txt 0.5 0.001 10
```
The three last command line arguments are
1. Damping constant (must be 0 < d < 1)
2. Convergence threshold (typically a small number)
3. The number of top webpages to be printed (similar to the top search results in a search engine)
