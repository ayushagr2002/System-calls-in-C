# System-calls-in-C
Manipulating files using system calls in C programming language

- Q1: Reverse a file using system calls.
- Q2: Reverse a specific part of a file using system calls.
- Q3: Check permissions of the output file of the above two programs using system calls.

# Assumptions Made:

- A single call of `malloc` can allocate upto 1 MB of memory on heap.
- File name for all the questions are given as absolute or relative.
- The files provided in input are text files(.txt).
- If directory is already present, then we change its permissions to 0700 else if directory is not present then we create the directory for the required permissions.

### Specific for Q2:

- The file size(in B) is exactly divisible by No_of_Parts given in input.
- No_of_Parts and Part_to_be_Reversed are single digit integers.
