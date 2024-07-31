# Advanced Algorithms and Programming

## Lab 1

### Exercise 1: Championship Days

**Description:**

In a championship, n (max 20) teams play for m (max 20) days. Let's consider a matrix of n×m integers, each of which can only be 0, 1, or 3. Each row of the matrix represents the points acquired by the n teams in the matches played on the m days of the championship: 3 points for winning matches, 1 point for drawn matches, and 0 points for defeats. The results of the k-th day are contained in the rows of the column with index k. Write a C program that reads the contents of this matrix from a file and, for each day of the championship, prints the index (the corresponding row number) of the leading team. Define an appropriate format for the file.

### Exercise 2: Text Recoding with Dictionary

**Description:**

A file (source.txt) contains a text composed of an indefinite number of lines, each with a maximum length of 200 characters. A second file (dictionary.txt) contains a list of pairs of strings. The dictionary file is organized as follows:

- The first line contains a positive integer S (≤ 30), indicating the number of possible recodings (substitutions) present in the dictionary.
- Then follow S pairs <compressed><original> to represent possible substitutions. Each substitution <compressed> is in the form $<integer>$.

The purpose of the program is to recode the first text file by replacing character sequences based on the contents of the second file. If there are multiple possible substitutions for a certain substring, the program chooses the first substitution found. Save the result of the recoding in a third file (encoded.txt).

### Exercise 3: Matrix Rotation

**Description:**

Write a C program that allows the user to sequentially perform rotation operations of P positions on specified rows and/or columns of a matrix of integers. The rotations are to be understood as circular both on the rows and on the columns.

The program:

- reads from file, whose name is acquired from the keyboard, the matrix (max 30 x N).
- the format of the file provides on the first line 2 integers indicating the number of rows nr and columns nc, followed by nr rows each containing nc integers.
- repeatedly acquires from the keyboard a string (at most 100 characters, containing any spaces), in the form

```txt
<selector> <index> <direction> <positions>
```

The selector indicates whether to operate on a row ("row"), a column ("column"), or terminate ("end"). Then follow the index of the selected row (column), the direction ("right" or "left", or "up" or "down") and the number of positions.
