# Laboratory Exercise No. 4

## Exercise 1: Greatest Common Divisor

### Skills:
- Mathematical recursion

### Description:
Given two positive integers `a` and `b`, their greatest common divisor (gcd(a, b)) is defined recursively.

Identify an appropriate termination condition and write a recursive function:
```c
int gcd(int a, int b);
```
that realizes the above definition.

## Exercise 2: Majority Element

### Skills:
- Mathematical recursion

### Description:
Given a vector `vet` of `N` natural numbers, a majority element, if it exists, is defined as a value that appears more than `N/2` times.

Example:
- If `N = 7` and `vet` contains `3, 3, 9, 4, 3, 5, 3`, the majority element is `3`.
- If `N = 8` and `vet` contains `0, 1, 0, 2, 3, 4, 0, 5`, there is no majority element.

Write a function `majority` that, given `N` and `vet`, prints the majority element if it exists, and `-1` if it does not. The prototype is:
```c
int majority(int *a, int N);
```

Constraints: Complexity O(n log n), in-place algorithm.

## Exercise 3: Regular Expression Evaluation

### Description:
String search problems often require compact representation of sets of strings, rather than exact matches. Regular expressions are commonly used for this purpose.

A regular expression (regexp) is a sequence of symbols that identifies a set of strings. Write a C function that finds occurrences of a given regexp within an input string. The function should have the following prototype:
```c
char *searchRegexp(char *src, char *regexp);
```
where:
- `src` represents the source string to search within.
- `regexp` represents the regular expression to search for.
- The return value is a pointer to the first occurrence of `regexp` in `src` (or `NULL` if not found).

For this exercise, consider only strings composed of alphabetic characters and regular expressions containing only alphabetic characters and the following metacharacters:
- `.` matches any single character.
- `[]` matches any single character contained within the brackets.
- `[^ ]` matches any single character not contained within the brackets.
- `\a` matches any lowercase letter.
- `\A` matches any uppercase letter.

Examples of regular expressions:
- `.oto` matches any four-character string ending with "oto", e.g., "voto", "noto", "foto", ...
- `[mn]oto` matches only "moto" and "noto".
- `[^f]oto` matches all strings ending with "oto" except "foto".
- `\aoto` matches any four-character string starting with a lowercase letter and ending with "oto".
- `\Aoto` matches any four-character string starting with an uppercase letter and ending with "oto".

## Exercise 4: Transport Company - Sorting

### Description:
Refer to the scenario introduced in Exercise 2 of Laboratory 2. Write a C program that, after acquiring the information into an appropriate data structure, provides the following operations:
- Print the contents of the log, either to the screen or to a file.
- Sort the vector by date, and by hour within the same date.
- Sort the vector by route code.
- Sort the vector by departure station.
- Search for a route by departure station (including partial matches).

For the searches, implement both a binary search function and a linear search function. For sorting, pay attention to the stability of the chosen algorithm when sorting by multiple keys. Choose the most appropriate search algorithm: if the data set is sorted according to the current search key, use binary search; otherwise, use linear search. It is suggested to maintain the current sorting state of the data set in the program.

## Exercise 5: Transport Company - Multi-sorting

### Description:
Extend the functionalities of the previous exercise to maintain multiple simultaneous orderings of the data set.

Suggestion: Read the original vector only once, keeping it in the exact order of reading throughout the execution. Use additional vectors of pointers to the structure for each required sorting order, managing the sortings accordingly.