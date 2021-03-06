Chapter 8: Recursion and Dynamic Programming

1. A child is running up a staircase with n steps and can hop either 1, 2, or 3
   steps at a time.  Implement a method to count how many possible ways the
   child can run up the stairs.

2. Imagine a robot sitting on the upper left corner of a grid with r rows and
   c columns.  The robot can only move in two directions, right and down, but
   certain cells are "off limits" such that the robot cannot step on them.
   Design an algorithm to find a path for the robot from the top left to the
   bottom right.

3. A magic index in an array is defined to be an index such that array[i] == i.
   Given a sorted array of distinct integers, write a method to find a magic
   index, if one exists in an array.

4. Write a method to return all subsets of a set.

5. Write a function to multiply two positive integers without using the *
   operator.  You can use addition, subtraction and bit shifting, but you
   should minimize the number of those operations.

6. In the classic problem of Towers of Hanoi, you have 3 towes and N disks of
   different sizes which can slide on to any tower.  The puzzle starts with
   disks sorted in ascending order of size from top to bottom (i.e. the disks
   get smaller in size as you go up the tower).  You have the following
   constraints:
   1. Only one disk can be moved at a time.
   2. A disk is slide off of the top of one tower and onto another tower.
   3. A disk cannot be placed on top of a smaller disk.

7. Write a method to compute all permutations of a string of unique characters.

8. Write a method to compute all permutations of a string that may have
   duplicate characters.

9. Implement an algorithms to print all valid (e.g. properly opened and closed)
   combinations of n pairs of parentheses.
   ((())), (()()), (())(), ()(()), ()()()

10. Implement a paint fill function that one might see on many image editing
    programs.  That is, given a screen (represented by a two-dimensional array
    of colors), a point and a new color, fill in the surrounding area until the
    color changes from the original color.

11. Given an infinite number of quarters, dimes, nickels and pennies, write
    code to calculate the number of ways of representing n cents.

12. Write an algorithm to print all ways of arranging eight queens on an 8x8
    chess board so that none of them share the same row, column, or diagonal.

13. You have a stack of n boxes with widths wi, heights, hi, and depths di.
    The boxes cannot be rotated and can only be stacked on top of one another
    if each box in the stack is strictly larger than the box above it in width,
    height, and depth.  Implement a method to compute the height of the tallest
    possible stack.  The height of the stack is the height of the sum of the
    heights of each box.

14. Given a boolean expression consisting of the symbols 0 (false), 1 (true),
    & (AND), | (OR) and ^ (XOR) and a desired boolean result value, implement
    a function to count then umber of ways of parenthesizing the expression
    such that it evaluates to the desired result.
