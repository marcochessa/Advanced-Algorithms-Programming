## Laboratory Exercise No. 8

### Exercise 1: Sequenza di attività

#### Skills:
- Exploring the solution space with combinatorial models
- Optimization problems

#### Description:
An activity `i` is characterized by an open interval `(si, fi)`, where `si` is the start time, `fi` is the end time, and `di = fi - si` is the duration of the activity. An array `v` of structures represents a collection of activities with fields for start time and end time. Activities `i` and `j` are incompatible if and only if they intersect or overlap, which is determined by the condition:
```
si < fj && sj < fi
```
Write a wrapper function and a recursive function in C that determines and displays a subset of compatible activities that maximizes the sum of their durations:
```
max Σ dk, such that ∀(k1, k2) ∈ S, k1 ∩ k2 = ∅
```
The prototype of the wrapper function is:
```c
void attSel(int N, att *v);
```
**Example:** Given `S = ((1,2), (2,4), (2,5), (3,5), (5,7), (6,8))`, one of the subsets of `S` of compatible activities that maximizes the sum of durations is `(1,2), (2,5), (6,8)` with a total duration of 6.

### Exercise 2: Tessere e scacchiere

#### Skills:
- Exploring the solution space with combinatorial models
- Optimization problems

#### Description:
A game is played on a rectangular board of size `R x C`. Each cell must contain a tile with two segments of pipe, one horizontal and one vertical. The segments are characterized by a color and a score (positive integer). To earn points, pipes must be aligned along an entire row (for horizontal) or column (for vertical) with the same color. Tiles can be rotated by 90°. Each tile is available in a single copy. Assume there are enough tiles to complete the board.

The goal of the game is to achieve the maximum possible score by placing a tile in each cell of the board.

The details are provided in two files:
- `tiles.txt` with:
  - The first line containing the number `T` of tiles.
  - `T` quadruples each representing a tile with `<color1><value1><color2><value2>`.

- `board.txt` with:
  - The first line containing `R` and `C`, the number of rows and columns.
  - `R` lines with `C` elements each describing the configuration of the board. Each cell is represented by a pair `ti/r` where `ti` is the index of a tile and `r` is its rotation (e.g., `7/0` for no rotation). An empty cell is represented by `-1/-1`.

Write a C program that, once it has loaded the available tiles and initial board configuration into appropriate data structures, generates the solution with the maximum possible score starting from the initial configuration read from the file.

### Exercise 3: Gioco di ruolo (multifile)

#### Skills:
- Arrays of struct, dynamic data structures, dynamic arrays, dynamic reallocation
- Multifile programming

#### Description:
Consider the scenario from Exercise 3 of Laboratory 6 (Role-Playing Game). Organize the previously written code into multiple modules:
- A client module containing `main` and the user interface/menu.
- A module for managing characters.
- A module for managing inventory.

**Character Module** should provide functionalities for:
- Loading character information from a file while maintaining the list structure.
- Inserting/deleting a character.
- Searching for a character by code.
- Printing details of a character and their equipment, if present.
- Modifying a character's equipment by adding/removing items.

**Inventory Module** should provide functionalities for:
- Loading object information from a file into a dynamically allocated array of structures.
- Searching for an object by name.
- Printing details of an object.

**Note:** The character module is a client of the inventory module because each character has a collection of (references to) data in the inventory.