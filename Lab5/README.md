# Laboratory Exercise No. 5

## Exercise 1: Playlist

### Skills:
- Exploring the solution space with combinatorial models

### Description:
A group of friends wants to create a playlist for a trip. To satisfy everyone, each friend can propose up to five songs to choose from. The playlist is created by selecting as many songs as there are friends, with each friend selecting one and only one song from their proposed list. All songs are distinct.

The information about the proposed songs is stored in a text file (`brani.txt`) organized as follows:
- The first line contains the number `A` of friends.
- Followed by `A` blocks of lines, one for each `i-th` friend, where:
  - The first line of the block contains the number `Ci` of songs proposed by the friend.
  - Followed by `Ci` strings, one per line, containing the titles of the proposed songs.

Assume that all song titles contain no spaces and are at most 255 characters long.

Write a C program that reads the input file and generates all possible playlists according to the above rules.

**Note**: The contents of the sample input file are indented to make it easier to distinguish the portions dedicated to each friend.

It is recommended to first identify which combinatorial model, among those covered in class, the problem refers to, and then adapt the code presented in class accordingly.

## Exercise 2: Matrix Allocation

### Skills:
- Dynamic data structures, dynamically created matrices

### Description:
A text file contains a matrix of integers with the following format:
- The first line of the file specifies the dimensions of the matrix (number of rows `nr` and number of columns `nc`).
- Each of the following `nr` lines contains the `nc` values corresponding to a row of the matrix, separated by one or more spaces.

Write a program that dynamically allocates the matrix and reads the file. The matrix allocation function can:
- Use the return value to return the pointer to the matrix to the main function
  ```c
  int **malloc2dR(...);
  ```
- Return the pointer to the matrix among the parameters passed by reference
  ```c
  void malloc2dP(int***,...);
  ```

Once the matrix is acquired, the program should invoke a function
```c
void separa(int **mat, int nr, int nc, ...);
```
that:
- Interprets the matrix as a checkerboard (with alternating white and black cells on each row and column).
- Separates the data of the black cells from the white cells, copying them (in arbitrary order) into two dynamic vectors, which are returned to the calling program.
- The two integer vectors, of appropriate length to contain the elements of the "white cells" and "black cells" separately, should be dynamically allocated.
- The two vectors and their contents must be visible to the caller of the `separa()` function (so they should be declared appropriately, in place of the ellipsis ...), which prints and deallocates them.

## Exercise 3: Transport Company - Multi-sorting

### Skills:
- Arrays of structs, dynamic data structures, dynamic arrays

### Description:
Repeat exercise 5 from Laboratory 4 using dynamically allocated arrays. Specifically, the arrays should be allocated based on the number of data entries actually present in the acquired file.

In addition to the previously provided commands, add one for acquiring (reading) a new file (given its name). This means the program should be able to acquire data from a file not only at the start but every time the user requests it. The read command generally involves acquiring new data from a different file than the previous one. Therefore, it is necessary to free (using the `free` function) the previously allocated arrays and allocate new ones for the new data to be read. Note that the task of acquiring data can be performed by a single function, called both (the first time) at the program's start and at each activation of the read command.