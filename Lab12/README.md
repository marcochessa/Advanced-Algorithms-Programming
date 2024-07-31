## Laboratory Exercise No. 12

#### Exercise 1: Graphs and DAGs

You have a weighted, directed, and connected graph stored in a file named `grafo.txt` with the following format:

- The first line contains an integer \( N \), representing the number of vertices in the graph.
- The next \( N \) lines each contain a string of up to 30 alphanumeric characters representing the unique identifier of each node.
- This is followed by an indefinite number of triples `<id_1> <id_2> <arc_weight>` representing the directed edges of the graph. The weight is a non-negative integer.

**Write a C program to perform the following operations:**

1. **Identify all sets of edges of minimum cardinality whose removal makes the original graph a Directed Acyclic Graph (DAG).**
   
   - To achieve this, you will need to:
     - Detect cycles in the graph.
     - Find the minimum set of edges whose removal will break all cycles.
     - Use graph algorithms such as Depth-First Search (DFS) and cycle detection techniques to determine the minimal edge sets.

2. **Construct a DAG by removing, among all the edge sets identified in the previous step, the one with the maximum weight.** 
   
   - Define the weight of a set of edges as the sum of the weights of the edges in that set.
   - To construct the DAG:
     - Calculate the weight of each edge set.
     - Remove the set with the maximum weight from the original graph to form a DAG.

3. **Compute the maximum distances from each node in the constructed DAG.**
   
   - This involves:
     - Performing a topological sort of the DAG.
     - Using dynamic programming or other shortest path algorithms to compute the longest path from each node.

**Steps to Implement the Solution:**

1. **Read and Parse Input:**
   - Read the number of vertices and their identifiers.
   - Read the edges and their weights, and construct the graph.

2. **Cycle Detection:**
   - Implement a cycle detection algorithm to identify cycles in the graph.
   - Find minimal edge sets that can break these cycles.

3. **Determine Edge Sets:**
   - For each set of edges that can break cycles, calculate its weight.
   - Identify the set with the maximum weight.

4. **Construct the DAG:**
   - Remove the edges from the original graph to form a DAG based on the identified set.

5. **Compute Maximum Distances:**
   - Use algorithms suited for DAGs to compute maximum distances from each node.

**Note:**
- Ensure that you handle the graph representation efficiently and use appropriate algorithms for cycle detection, topological sorting, and longest path calculations in DAGs.
