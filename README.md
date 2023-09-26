# Homework #6

This was the sixth coding assignment for the Fall 2020 CS1575 (Data Structures) course.

# Information From Assignment README

Help Tank find Morpheus and the others in The Matrix by creating a **dictionary** to automate the deciphering of known symbols in code!

You will implement a dictionary (abstract data type) using a **binary search tree** (BST) data structure that will have similar functionality to std::map.
  - https://en.cppreference.com/w/cpp/container/map

Your tasks are:

1. to write the **MyMap** functions

2. to write a function, **get_letter_frequency()**, that accepts an arbitrary number of characters from standard input and builds a MyMap containing the number of occurrences for each character in the input, i.e., if the letter 'a' occurs 43 times in the input, map['a'] should return 43.
  - an example of the behavior of this function is at the end of pa06.cpp.

* We give you a working pa06.cpp and its output (pa06_output.txt)
* We also give you a similar file pa06_std.cpp with the std:: versions of the map functions
*
* Note: map/dictionary does NOT allow duplicates.
* If you insert an item already in the map, overwrite the old one.
