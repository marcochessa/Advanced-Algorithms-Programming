## Laboratory Exercise No. 7

### Exercise 1: Collane e pietre preziose

#### Skills:
- Exploring the solution space with combinatorial models
- Optimization problems

#### Description:
A jeweler has z sapphires, s emeralds, r rubies, and t topazes to create a necklace by stringing one stone after another. The necklace must follow these rules:
- A sapphire must be immediately followed by another sapphire or a ruby
- An emerald must be immediately followed by another emerald or a topaz
- A ruby must be immediately followed by an emerald or a topaz
- A topaz must be immediately followed by a sapphire or a ruby

Write a C function that calculates the length and displays the composition of a necklace of maximum length that adheres to the above rules. The length of the necklace is the number of precious stones that compose it.

Observation: The length of the solution is not known a priori and can vary between 1 and (z+r+s+t).

**Hint:** This exercise can be solved by adopting an approach similar to the arrangements with repetition seen in the lesson, appropriately adjusted to the requirements of the problem. Once the recursive model is set, write the filter (acceptability check) and optimization function. Finally, consider the possibility of introducing pruning criteria.

**Note:** Pay attention to the increase in execution time required to identify the solution as the input parameters for the problem (number of available precious stones) increase.

### Exercise 2: Collane e pietre preziose (version 2)

Consider the context introduced in the previous exercise. Each type of stone is characterized by its value (non-negative integer) (`val_z`, `val_s`, `val_r`, `val_t`). The value of the necklace is the sum of the values of the individual stones that compose it. Indicating with `n_z`, `n_s`, `n_r`, and `n_t` the number of sapphires, emeralds, rubies, and topazes, the value of the necklace is:
```
val = val_z * n_z + val_s * n_s + val_r * n_r + val_t * n_t
```
The composition of the necklace must respect all the rules introduced in the previous exercise. Additionally, the following criteria must be met:
- No type of stone can repeat more than `max_rip` times consecutively
- In the necklace, the number of sapphires cannot exceed the number of emeralds

Write a C function that calculates the composition of a necklace with the maximum value that adheres to the above rules.

### Exercise 3: Gioco di ruolo

#### Skills:
- Arrays of struct, dynamic data structures, dynamic arrays, dynamic reallocation

#### Description:
A text file (`pg.txt`) contains the details of some characters from a role-playing game, organized as follows:
- The number of characters in the file is not known a priori
- The details of each character are reported one per line. Each line contains three strings such as a unique identifier code, the character's name, and its class. Followed on the same line by a sextuple representing the character's base stats, in the form `<hp> <mp> <atk> <def> <mag> <spr>`. The meanings of the sextuple fields are not relevant for the exercise.
- The code is in the form `PGXXXX`, where `X` represents a digit in the range 0-9
- The name and class of each character are represented by a string, without spaces, of a maximum of 50 alphabetical characters (uppercase or lowercase)
- The stats are positive or zero integers
- All fields are separated by one or more spaces.

A second text file (`inventario.txt`) stores the details of a series of objects accessible to the characters in the game. The file is organized as follows:
- The first line contains the number `O` of objects
- The `O` subsequent lines contain the details of each available object
- Each object is characterized by a name, a type, and a sextuple representing the modifiers to the base stats of a character
- The name and type are represented by a string, without spaces, of a maximum of 50 alphabetical characters (uppercase or lowercase)
- The modifiers to the stats are integers (potentially negative), so they can be seen as bonuses (if positive) or maluses (if negative).

Each character can use the available objects in the inventory and freely compose their equipment, up to a maximum of eight items.

Set up the data structure so that it is consistent with the proposed graphical representation (the names of types and fields are only examples). If necessary, add all additional fields deemed appropriate. Pay particular attention to using wrapper structures for storing collections (for characters, objects, and equipment).

Write a C program that allows:
- Loading a list of characters
- Loading a dynamically allocated array of structures containing the list of objects
- Adding a new character
- Deleting a character
- Adding/removing an object from a character's equipment
- Calculating a character's stats considering their base parameters and current equipment. Ensure that no stat can be less than 1, regardless of the cumulative maluses due to the choice of equipment.