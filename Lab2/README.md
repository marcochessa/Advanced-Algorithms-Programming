# Lab Exercise 2

## Exercise 1: Region Identification

- **Skills:** File reading/writing, matrix manipulations
- **Category:** Verification and selection problems (From problem to program: 4.5)

A text file contains a matrix of integers (0 or 1) in the following format:
- The first line of the file specifies the actual dimensions of the matrix (number of rows nr and number of columns nc). Assume both values are at most 50.
- Each of the nr subsequent rows contains the nc values corresponding to a row of the matrix, separated by one or more spaces.
- Each cell can contain only the value 0 (associated with the color white) or the value 1 (associated with the color black).
- Black cells are organized to form rectangular regions (each black region is surrounded by a frame of white cells, or by the edge/s of the matrix). For this purpose, consider that cell adjacency is considered only along the four main cardinal points (North, South, West, East), not diagonally.

Write a C program that:
- Reads the matrix from the input file (the file contains no errors, so there are only black rectangles that respect the constraints).
- Identifies the largest black regions by height, width, and total area.
- In case of a tie, one of the identified regions that satisfy a certain criterion is reported.
- For each of these regions, outputs the coordinates of the upper-left extreme and its characteristics (height, width, total area).

**Example:**
Corresponding Map:
```
5 6
1 1 0 0 0 0
0 0 1 1 0 0
0 0 1 1 0 1
0 0 0 0 0 1
1 0 1 0 0 1
```

Program Output:
```
Max Base: upper-left corner=<0,0> b=2, h=1, Area=2
Max Area: upper-left corner=<1,2> b=2, h=2, Area=4
Max Height: upper-left corner=<2,5> b=1, h=3, Area=3
```

---

## Exercise 2: Transport Company

- **Skills:** Data selection/filtering using table search, enumerative types
- **Category:** Selection problems (From problem to program: 3.4.2 and 4.5.2)

An urban transport company tracks its vehicles in a log file (text file named corse.txt).
The file is organized as follows:
- The first line contains a positive integer indicating the number of subsequent lines in the file itself (at most 1000).
- In the subsequent lines, information about the routes, one per line, is provided in the format: <route_code><departure><destination><date><departure_time><arrival_time><delay>.
All strings are at most 30 characters long. The delay is an integer, possibly zero, representing the minutes of delay accumulated by the run.

Write a C program capable of answering the following queries:
1. List all the runs starting in a certain date range.
2. List all the runs starting from a certain stop.
3. List all the runs terminating at a certain stop.
4. List all the runs that reached the destination late within a certain date range.
5. List the total accumulated delay of the runs identified by a certain route code.

The above queries should be handled through command menus (see section 4.4.1, From problem to program). Each command consists of a word among "date", "departure", "terminus", "delay", "total_delay", and "end", possibly followed on the same line by other information, for example two dates for "date", a departure stop for "departure", etc.

Use the command encoding strategy through the enum command_e type, containing the symbols r_date, r_departure, r_terminus, r_delay, r_total_delay, r_end, enabling switch-case based menus.

Suggestions:
- Implement a readCommand function that, properly acquiring the command, returns the corresponding value of type command_e.
- Implement a selectData function that, receiving as parameters the table, the table size, and the command type, manages through a menu the acquisition of the additional information necessary for that command and the call to an appropriate function for selecting and printing the selected data.

---

## Exercise 3: Word Occurrences

- **Skills:** File reading/writing, text manipulations, search in tables of names/strings
- **Category:** Text processing problems using strings (From problem to program: 4.4.3)

Write a program capable of locating, within a generic text, the occurrences of each word containing a certain character sequence. By word, we mean a sequence of contiguous alphanumeric characters (identified by the isalnum function), separated by spaces or punctuation marks (identified by the isspace and ispunct functions).

The program receives input:
- The sequenze.txt file: the first line contains the total number of sequences, at most 20, on the subsequent lines, one per line, the sequences to be searched. The length of each sequence is limited to a maximum of 5 characters. Case sensitivity is disregarded.
- The text.txt file: contains the text. The number of lines is not known in advance. Assume that the length of each line is at most 200 characters. Also assume that no word in the text is longer than 25 characters.

The program should display, for each of the sequences, which words contain it and where they are located in the file. The position of the words is given in terms of word count from the beginning of the text. For the purposes of the exercise, only the first 10 occurrences for each sequence should be identified and displayed.

**Example:**
sequences.txt file:
```
4
no
Al
per
s
```

text.txt file:
```
Non sempre si capisce un esercizio alla prima lettura, ma prestando attenzione al testo e all’esempio non dovrebbe essere impossibile scrivere codice funzionante nonostante i dubbi iniziali. Se ancora non si capisce, allora basta chiedere all’esercitatore di turno.
```

The sequence "no" is contained in "Non" (word at position 1 in the text), "non" (position 18), "nonostante" (position 25), "non" (position 31), and "turno" (position 40).

---

## Exercise 4: Sorting Algorithm Evaluation

- **Skills:** Iterative sorting algorithms, empirical complexity analysis

Consider the following sorting algorithms for sorting arrays of integers in ascending order:
- Selection Sort
- Insertion Sort
- Shell Sort

Introduce a counter variable for:

Write a C program that, for each numeric sequence acquired from the file (sort.txt), invokes all the above sorting algorithms and prints to the screen:
- the number of swaps
- the number of iterations of the outer loop
- for each step of the outer loop the number of iterations of the inner loop
- the total number of iterations.

The sort.txt file is characterized by the following format:
- The first line contains the number S of numeric sequences.
- Then follow S lines in the form <length><sequence> where <length> is a non-negative integer

 representing the length of the sequence reported on that line, and <sequence> are <length> numbers separated by a space.