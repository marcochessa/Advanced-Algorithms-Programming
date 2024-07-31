# Laboratory Exercise No. 3

## Exercise 1: Region Identification

### Skills:
- File reading/writing
- Static matrix manipulation
- Pointers and parameter passing by reference

### Category:
- Verification and selection problems

### Description:
Revisit exercise 1 from Lab02 and make the following modifications:

1. **Matrix Reading Function**: 
   - Declare an integer matrix `M` and define `MAXR` as 50.
   - Implement a function `readMatrix` that reads the matrix and returns the actual number of rows and columns used as "by reference" parameters (using pointers by value). 
   - The function should be callable with a statement like:
     ```c
     readMatrix(M, MAXR, &nr, &nc);
     ```

2. **Region Recognition Function**:
   - Implement a function `recognizeRegion` that, given a cell in the matrix, determines if it is the top-left corner of a region.
   - The function should return the dimensions of the rectangle "by reference" and have a boolean return value (true: rectangle found, false: rectangle not found).
   - The function should be callable with a statement like:
     ```c
     if (recognizeRegion(M, nr, nc, r, c, &b, &h)) {
         // Print message for rectangle with
         // top-left corner at (r, c), width b, and height h
         ...
     }
     ```

## Exercise 2: Pointers and Data Representation

### Skills:
- Pointers
- Information encoding
- Numerical representations

### Category:
- Pointer data type

### Description:
Implement a function that displays the internal (binary) encoding of a real number, implemented in C as a `float`, `double`, or `long double`.

#### Background:
- The C types `float`, `double`, and `long double` adhere to the IEEE-754 specifications for single, double, and extended/triple/quadruple precision real data types. 
- For the `long double` type, the C standard does not have a unique choice, but all formats for `long double` have a 15-bit exponent.

#### Program Requirements:
- Use 3 variables for real numbers (`af`, `ad`, `ald`), of types `float`, `double`, and `long double`, respectively.
- Determine if the computer uses little-endian or big-endian encoding and assign the corresponding value (true or false as an integer) to a variable `bigEndian`.
- Display (using the C `sizeof` operator) the size (in bytes and bits) of the three variables `af`, `ad`, and `ald`.
- Read a decimal number (with optional exponent in base 10) from the keyboard and assign it to the three variables `af`, `ad`, `ald`.

#### Display Function:
- Implement the function `printEncoding` with the prototype:
  ```c
  void printEncoding(void *p, int size, int bigEndian);
  ```
- Call this function three times, passing as parameters the pointer to one of the three variables (converted to `void *`) and the size of the variable:
  ```c
  printEncoding((void *)&af, sizeof(af), bigEndian);
  printEncoding((void *)&ad, sizeof(ad), bigEndian);
  printEncoding((void *)&ald, sizeof(ald), bigEndian);
  ```

#### Function Details:
- `printEncoding` should print the sign bit, exponent bits, and mantissa bits of the number using pointer arithmetic, the encoding type, and the size received as parameters.
- Suggested strategy:
  - Read/recognize the received number as an array of `unsigned char` (e.g., a 32-bit float corresponds to an array of 4 `unsigned char`).
  - Decode each element of the array using an algorithm to convert it to binary.
  - Print the bits, separating the sign bit, exponent bits, and mantissa bits, starting from the most significant bit (MSB). The `bigEndian` parameter determines the direction to traverse the bytes of the number. Use pointer arithmetic to traverse all bytes of the data from the most significant to the least significant (or vice versa, depending on the decoding choice).