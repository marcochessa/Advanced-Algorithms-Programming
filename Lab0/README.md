# Lab Exercise 0

## Exercise 1: Numeric Sequences in Vector

- **Points:** 2
- **Simplified programming part, exam of September 13, 2018**

Let V be a vector of N integers (N ≤ 30). Write a C program that, once this vector is acquired from the keyboard, displays all the maximum size subvectors formed by contiguous cells containing non-null data.

**Example:**
Given the vector [1 3 4 0 1 0 9 4 2 0], the two maximum size subvectors (3) containing non-null data are [1 3 4] and [9 4 2].

---

## Exercise 2: String Manipulation

- **Points:** 2
- **Simplified programming part, exam of June 21, 2018**

A text file contains information in the following format:
- The first line of the file contains an integer N indicating the number of words.
- Each of the N subsequent lines contains one word per line (maximum 20 characters).

Write a C program that counts, among the words in the file, how many substrings of a given length have 2 vowels.

**Operations:**
- Read the data from an input file, whose name (maximum 20 characters) is read from the keyboard.
- Read an integer n from the keyboard representing the length of the substrings being searched.
- For each acquired word, call the count function that counts how many n-character substrings containing exactly two vowels appear in the string S passed as an argument.
- Print the total number of substrings found with exactly two vowels.

**Function prototype:**
```c
int count(char S[20], int n);
```

**Example:**
If S="forExample" and n=4, the substrings of S of length 4 with 2 vowels are 4 and they are "forE", "orEx", "rExa", and "Exam".

---

## Exercise 3: Vector Rotation

Write a C function that allows the user to rotate the contents of a vector of N integers to the right or left by a user-specified number of positions P. The vector is to be considered circular, meaning that the element to the right of the cell with index N-1 is the cell with index 0, and the element to the left of the cell with index 0 is the cell with index N-1.

**Function prototype:**
```c
void rotate(int v[maxN], int N, int P, int dir);
```

**Main:**
1. Acquire N from the keyboard (N ≤ maxN with maxN being 30).
2. Acquire the vector V from the keyboard.
3. Repeat rotations, acquiring P each time (P < N, P=0 to finish) and the direction (dir =-1 for right rotation, dir = 1 for left rotation), and print the resulting vector.

---

## Exercise 4: Iteration over Matrices

A text file contains a matrix of integers in the following format:
- The first line of the file specifies the dimensions of the matrix (number of rows nr and number of columns nc). Assume both values are at most 20.
- Each of the nr subsequent rows contains the nc values corresponding to a row of the matrix, separated by one or more spaces.

Write a C program that:
- Reads this matrix from the input file, whose name (maximum 20 characters) is read from the keyboard.
- Repeatedly asks the user for a value dim between 1 and the minimum of nr and nc, and prints all square submatrices of that size contained in the matrix.
- Terminates iteration if the user enters a value inconsistent with the dimensions of the matrix.
- Stores in an appropriate matrix and prints at the end the square submatrix, among those previously identified, whose sum of elements is maximum.