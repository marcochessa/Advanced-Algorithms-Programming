# Laboratory Exercise No. 9

## Exercise No. 0: Mobile Network Antennas

### Problem Description
You are given a set of `n` cities arranged on a straight road, identified by integers from 1 to `n`, each characterized by its population (in thousands, integer). An antenna for the mobile network can be installed in a city only if its adjacent cities do not have antennas. Each antenna covers only the population of the city where it is installed.

For example:
- Cities: 1 2 3 4 5 6 7
- Populations: 14 22 13 25 30 11 90

Using the bottom-up dynamic programming paradigm, determine the maximum number of inhabitants that can be covered while respecting the installation rule, and the corresponding antenna placement.

### Solution

This is an optimization problem that could be solved by identifying all subsets of antennas, evaluating those that satisfy the rule, and among these, finding the optimal one. The model used is the powerset.

Alternatively, a dynamic programming approach can be used. The data is stored in an integer array `val` of `n+1` cells. The cell at index 0 corresponds to a fictitious city with no inhabitants.

**Step 1: Applicability of Dynamic Programming**

The following statement holds:
- The optimal solution for city index `k` corresponds to one of the following two cases:
  1. No antenna in city `k`: The optimal solution is the same as for the first `k-1` cities.
  2. An antenna in city `k`: The optimal solution is obtained from the optimal solution for the first `k-2` cities plus the antenna in city `k`.

We store the optimal solution in an integer array `opt` of `n+1` cells. `opt[0]` is 0 (no cities, no inhabitants, no antennas), and `opt[1]` is `val[1]` (only the city at index 1 with its population).

For other cases where `1 < k <= n`:
- If an antenna can be placed in city `k`, then it cannot be placed in city `k-1`, but rather in city `k-2`: `opt[k] = opt[k-2] + val[k]`.
- If an antenna cannot be placed in city `k`, then it can be placed in city `k-1`: `opt[k] = opt[k-1]`.

**Step 2: Recursive Solution**

The recursive formulation is:
\[ \text{opt}(k) = 
\begin{cases} 
0 & \text{if } k = 0 \\
\text{val}[1] & \text{if } k = 1 \\
\max(\text{opt}(k-1), \text{val}(k) + \text{opt}(k-2)) & \text{if } 1 < k \leq n 
\end{cases} \]

This can be easily coded in C as:
```c
int solveR(int *val, int *opt, int n, int k) {
    if (k == 0)
        return 0;
    if (k == 1)
        return val[1];
    return max(solveR(val, opt, n, k-1), solveR(val, opt, n, k-2) + val[k]);
}

void solve(int *val, int n) {
    int *opt = calloc((n + 1), sizeof(int));
    printf("Recursive solution: ");
    printf("maximum population covered %d\n", solveR(val, opt, n, n));
}
```

This solution results in the following recurrence relation:
\[ T(n) = 
\begin{cases} 
1 & \text{if } n = 0 \\
1 & \text{if } n = 1 \\
T(n-1) + T(n-2) + 1 & \text{if } n > 1 
\end{cases} \]

This is identical to the recurrence relation for Fibonacci numbers, so the recursive solution has exponential complexity.

**Step 3: Bottom-Up Dynamic Programming Solution**

Transforming the recursive solution into an iterative form:
- `opt[0]` and `opt[1]` are known a priori.
- For `2 ≤ i ≤ n`, `opt[i] = max(opt[i-1], opt[i-2] + val[i])`.

```c
void solveDP(int *val, int n) {
    int i, *opt = calloc((n + 1), sizeof(int));
    opt[1] = val[1];
    for (i = 2; i <= n; i++) {
        if (opt[i-1] > opt[i-2] + val[i])
            opt[i] = opt[i-1];
        else
            opt[i] = opt[i-2] + val[i];
    }
    printf("Dynamic programming solution: ");
    printf("maximum population covered %d\n", opt[n]);
    displaySol(opt, val, n);
}
```

**Step 4: Constructing the Optimal Solution**

The `displaySol` function constructs and displays the solution (cities where antennas are installed). It uses an integer array `sol` of `n+1` elements to record whether the `i`-th element is part of the solution. The decision is based on the content of the `opt` array and is constructed by scanning from right to left:

- `sol[1]` is assumed to be 1, unless modified during the next iteration.
- If `opt[i] == opt[i-1]`, it is certain that no antenna was placed in city `i`, so `sol[i] = 0`, and the iteration proceeds to city `(i-1)`.
- If `opt[i] == opt[i-2] + val[i]`, it is certain that:
  - An antenna was placed in city `i`, so `sol[i] = 1`.
  - No antenna was placed in city `(i-1)`, so `sol[i-1] = 0`.
  - The iteration proceeds to city `(i-2)`.

```c
void displaySol(int *opt, int *val, int n) {
    int i, *sol = calloc((n + 1), sizeof(int));
    sol[1] = 1;
    i = n;
    while (i >= 2) {
        if (opt[i] == opt[i-1]) {
            sol[i] = 0;
            i--;
        } else if (opt[i] == opt[i-2] + val[i]) {
            sol[i] = 1;
            sol[i-1] = 0;
            i -= 2;
        }
    }
    for (i = 1; i <= n; i++)
        if (sol[i])
            printf("%d ", val[i]);
    printf("\n");
}
```

## Exercise No. 1: Activity Sequence (Version 2)

Consider the situation introduced in Exercise No. 1 from Laboratory 8. Propose a solution to the same problem using the dynamic programming paradigm.

**Hint:**
- Sort the activities along a timeline. Define the sorting criterion based on the problem constraint (the intervals of the solution should not intersect).
- Inspired by the dynamic programming solution for the Longest Increasing Subsequence problem, build partial solutions considering only the activities up to the `i`-th in the sorted order, defining appropriately how to consider the activities. Extending partial solutions with the addition of a new `i`-th activity can be based on the compatibility between the "new" `i`-th activity and the previously considered solutions for `i-1`.
- Follow the steps performed in the previous exercise: applicability proof, recursive calculation of the optimal value, bottom-up dynamic programming calculation of the optimal value and solution.

## Exercise No. 2: Necklaces and Precious Stones (Version 3)

Solve Exercise No. 1 from Laboratory 7 using the memoization paradigm. Only calculate the maximum length of the necklace compatible with the available gems and composition rules.

**Hint:**
- Address the problem with the divide and conquer technique, noting that a necklace of length `P` can be recursively defined as:
  - The empty necklace, with `P=0` gems.
  - A gem followed by a necklace of `P-1` gems.

Since there are 4 types of gems (Z, R, T, S), write 4 functions `fZ`, `fR`, `fT`, `fS` to calculate the length of the longest necklace starting with a sapphire, ruby, topaz, and emerald, respectively, given `z` sapphires, `r` rubies, `t` topazes, and `s` emeralds. The composition rules for necklaces can be expressed recursively based on the values of the other functions.

Ensure to define the base cases for these functions to avoid entering inadmissible portions of the state space.

Memoization requires storing the solutions of solved subproblems in appropriate data structures, to reuse these solutions when the same subproblems reappear, limiting recursion to unsolved subproblems.

## Exercise No. 3: Role-Playing Game (Multi-file, with ADT)

Based on the code produced for Exercise No. 3 from Laboratory 8, adapt the code so that both the character module and the inventory module are first-class ADTs.

**Consider:**
- A data type for an item and a data type for an array of items (inventory).
- A data type for a character