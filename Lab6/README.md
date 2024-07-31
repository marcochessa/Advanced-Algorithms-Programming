# Laboratory Exercise No. 6

## Exercise 1: Vertex Cover

### Skills:
- Exploring the solution space with combinatorial models

### Description:
Given an undirected graph \( G \) with \( N \) vertices, identified by integers in the range 0..N-1, and \( E \) edges, identified as pairs of vertices. The graph is stored in a file, with \( N \) and \( E \) on the first line, followed by \( E \) lines each containing an edge in the form `u v`.

A vertex cover is a subset \( W \) of the vertices such that for every edge \((u,v) \in E\), either \( u \in W \) or \( v \in W \).

After reading the graph \( G \) from the file and storing the relevant information in appropriate data structures, list all the vertex covers.

Example: For the following graph,
```
N = 4
E = 4
0 1
1 2
2 3
3 0
```
the vertex covers are: (0, 1), (1, 2), (0, 1, 2), (0, 1, 3), (0, 2, 3), (1, 2, 3), (0, 1, 2, 3).

Note: This exercise does not require knowledge of Graph Theory.

## Exercise 2: Anagrafica with Lists

### Skills:
- Creating and managing linked lists

### Description:
The details of an anagrafica are stored in a text file composed of an indefinite number of lines in the following format:
```
<code> <name> <surname> <date_of_birth> <street> <city> <postal_code>
```
The field `<date_of_birth>` is in the format `dd/mm/yyyy`, `<postal_code>` is an integer, while all other fields are strings without spaces of maximum 50 characters. `<code>` is in the form `AXXXX`, where `X` represents a digit in the range 0-9, and is unique across the entire anagrafica. The details of the anagrafica should be enclosed in an appropriate data type `Item`.

The anagrafica should be stored in a list ordered by date of birth (the youngest people appear first in the list).

Write a C program that, after initializing an empty list, offers the following functionalities:
- Acquisition and ordered insertion of a new element into the list (from the keyboard)
- Acquisition and ordered insertion of new elements into the list (from a file)
- Searching for an element by code
- Deletion (with data extraction) of an element from the list, after searching by code
- Deletion (with data extraction) of all elements with dates between 2 dates read from the keyboard. Instead of implementing a function that deletes these elements from the list and returns them stored in a list or dynamic array, it is advised to implement a function that extracts and returns to the calling program the first element belonging to the interval. The calling program will iterate the call of this function, printing the result, for all elements of the interval.
- Printing the list to a file.

For the search and delete functions, it is required that the function operating on the lists returns the found or deleted element to the calling program, which handles the printing.