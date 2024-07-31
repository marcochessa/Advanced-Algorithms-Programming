## Laboratory Exercise No. 10

#### Exercise 1: Floor Exercise

**Problem Statement:**

Floor exercise is a discipline in artistic gymnastics where the athlete must perform a series of elements without the use of apparatus, except for the competition mat. In a floor exercise routine, the gymnast is required to perform a series of acrobatic passes called diagonals. Each diagonal consists of one or more elements.

Each element is characterized by the following parameters:
- **Name**: The name of the element (a string of up to 100 characters without spaces)
- **Type**: The element can be a forward acrobatic element [2], a backward acrobatic element [1], or a transition element [0]
- **Entry Direction**: The gymnast can enter the element from the front [1] or from the back [0]
- **Exit Direction**: The gymnast can exit the element from the front [1] or from the back [0]
- **Precedence Requirement**: The element can be performed as the first in a sequence [0] or must be preceded by at least one other element [1]
- **Final**: The element cannot be followed by other elements [1] or can be followed [0]
- **Value**: The score achieved by the gymnast for the correct execution of the element (a real number)
- **Difficulty**: The difficulty of the element (an integer).

Elements are stored in a text file (`elements.txt`), with one element per line. The number of elements is listed on the first line of the file.

To perform a sequence of elements, the exit direction of the first element must match the entry direction of the second element. A gymnast always starts a diagonal facing forward. The difficulty of a diagonal is defined as the sum of the difficulties of the elements it contains. The difficulty of the competition program is the sum of the difficulties of the diagonals that compose it.

For this exercise, consider the following rules:
- The gymnast must present 3 diagonals.
- The gymnast must include at least one acrobatic element in each diagonal.
- The gymnast must include at least one forward acrobatic element and one backward acrobatic element in the entire routine, but not necessarily in the same diagonal.
- The gymnast must present at least one diagonal with at least two acrobatic elements in sequence.
- If the gymnast includes a final element with a difficulty of 8 or higher in the last diagonal, the total score of that diagonal is multiplied by 1.5.
- Each diagonal can contain a maximum of 5 elements.
- Each diagonal's difficulty cannot exceed a given value `DD`.
- The overall program difficulty cannot exceed a given value `DP`.

Write a C program to identify the sequence of diagonals that allows the gymnast to achieve the highest possible score, given a set of available elements and the values of `DD` and `DP`.

---

#### Exercise 2: Floor Exercise (Greedy Version)

Based on the scenario described in Exercise 1, solve the problem using one or more greedy algorithms. Define appropriate objective functions.

---

#### Exercise 3: Network of Computers

An undirected, weighted graph represents a network of computers, each belonging to a subnet. The weight associated with each edge represents the data flow between two computers of the same subnet or different subnets, as shown in the example below (see the next figure).

The graph is stored in a file, whose name is passed as a command-line argument. The file consists of an indefinite number of lines, each containing a quadruple of alphanumeric strings (up to 30 characters) and an integer:
```
<computer_id1> <subnet_id1> <computer_id2> <subnet_id2> <flow>
```

Additionally, make the following assumptions:
- The names of individual nodes are unique within the graph.
- No loops are allowed.
- There is at most one edge between two nodes (no multigraph).
- Subnets are subgraphs that are not necessarily connected.

Write a C program to load the graph into memory by reading the contents from the file and to perform some simple operations on it.

The data structure in memory should be implemented considering the following constraints:
- The graph should be implemented as a Class I ADT, capable of containing both an adjacency matrix and adjacency lists. During the data loading phase from the file, only the adjacency matrix is generated; upon explicit command, the adjacency list should also be generated.
- Use a symbol table to provide mappings "from name to index" and "from index to name".

Once the graph is loaded from the file, the following operations should be possible:
- List vertices in alphabetical order, and for each vertex, list the edges incident on it, also in alphabetical order.
- Given 3 vertices whose names are read from the keyboard, check if they are pairwise adjacent, i.e., if they form a complete subgraph. Implement this function for both the adjacency matrix representation and the adjacency list representation.
- Generate the adjacency list representation, WITHOUT reading the file again, from the adjacency matrix representation.

An example graph is provided in the attached file (`graph.txt`).