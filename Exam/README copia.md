# Exam Exercise: Graphs and Directed Acyclic Graphs (DAGs)

## Objective

In this exercise, you will work with a weighted, directed, and connected graph. The goal is to:

1. **Identify Minimal Edge Sets**: Find all minimal sets of edges whose removal will convert the graph into a Directed Acyclic Graph (DAG).
2. **Construct a DAG**: From the identified edge sets, construct a DAG by removing the set with the maximum weight.
3. **Compute Maximum Distances**: Calculate the maximum distances from each node in the constructed DAG.

## Instructions

### 1. Understanding the Code

The code is divided into three main files:

- `main.c`: Contains the entry point of the program and manages high-level operations.
- `Graph.c`: Contains functions for graph operations, such as loading the graph, inserting edges, and finding kernel sets.
- `ST.c`: Implements the symbol table used for storing node identifiers.

### 2. Code Files

#### `main.c`

This file is responsible for:

1. **Loading the Graph**: Reads the graph data from a file (`file1.txt`), initializes the graph, and prints it.
2. **Verifying Kernel**: Reads a potential kernel from `file2.txt` and checks if it is a valid kernel.
3. **Finding Maximum Kernel**: Computes the maximum kernel and prints the results.
4. **Computing Maximum Path Length**: Determines the length of the longest simple path in the graph.

#### `Graph.c`

This file includes functions for:

1. **Graph Initialization**: Initializes the graph structure and adjacency lists.
2. **Loading Graph Data**: Reads and parses graph data from a file.
3. **Inserting Edges**: Adds edges to the graph.
4. **Finding and Verifying Kernels**: Generates and verifies kernel sets.

```c
#include <mem.h>
#include <malloc.h>
#include "Graph.h"

#define len 21

struct node {
    int v;
    link next;
};

struct G {
    link *ladj;
    int V;
    int E;
    ST tab;
    link z; // -> SENTINEL
};

// Function prototypes
static int cammino(Graph g, int ind, int *Ker, int N, int max, int *vCons, int *finalMax);
static Edge EDGEcreate(int v, int w);
static void insertE(Graph g, Edge e);
static link NEW(int v, link next);
static void genKernel(Graph g, int *sol, int *bestSol, int pos, int start, int car);
static void saveKernel(FILE *F3, int *ker, int N, Graph g);
static int BelongKer(int i, int *LVert, int N);

// Function implementations
```

#### `ST.c`

This file manages the symbol table for node identifiers:

1. **Initialization**: Creates and initializes the symbol table.
2. **Insertion and Search**: Adds and retrieves identifiers.
3. **Freeing Resources**: Cleans up the symbol table.

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct symbtab {
    char **a;
    int size;
    int maxN;
};

// Function prototypes
ST STinit(int N);
void STfree(ST st);
void STinsert(ST st, char *val);
int STsearch(ST st, char *k);
int STcount(ST st);
char* STsearchByIndex(ST st, int ind);

// Function implementations
```

### 4. Functions Overview

- **`GRAPHload`**: Loads graph data from a file and initializes the graph.
- **`GRAPHinsertE`**: Adds an edge to the graph.
- **`isKernel`**: Checks if a given set of nodes forms a kernel.
- **`findKernel`**: Finds the maximum kernel in the graph.
- **`camMaxVert`**: Computes the maximum length of a simple path in the graph.
- **`STinit`, `STinsert`, `STsearch`**: Manage the symbol table operations.