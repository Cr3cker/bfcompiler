# Brainfuck Compiler (currently interpreter) in C

This project is a simple Brainfuck interpreter written in C. It reads Brainfuck code from a file, builds an Abstract Syntax Tree (AST) representing the code, and then executes the code by traversing the AST and performing the operations specified by each node.

## Code Structure

The code is structured around the `Node` struct, which represents a node in the AST. Each node has a `type` (which specifies the Brainfuck command that the node represents), a `next` pointer (which points to the next node in the AST), and a `child` pointer (which is currently unused).

The `main` function starts by opening a file named "source.bf" and reading its contents into a buffer, ignoring spaces and newline characters. It then iterates over the buffer, creating a new node for each Brainfuck command it encounters (`+`, `-`, `>`, `<`). These nodes are linked together in the order they appear in the file to form the AST.

Once the AST is built, the function initializes an array of 1024 integers to serve as the memory for the Brainfuck program, and a pointer to represent the memory pointer of the program. It then traverses the AST, executing the operation specified by each node. The `BF_INCREMENT` and `BF_DECREMENT` operations increment and decrement the value in the current memory cell, while the `BF_MOVE_RIGHT` and `BF_MOVE_LEFT` operations move the memory pointer to the right and left, respectively.

After all the nodes have been processed, the function prints the final state of the memory and frees the buffer.

## Usage

To use this interpreter, you need to have a C compiler installed on your system. You can compile the code with a command like `gcc main.c -o bf`, and then run it with `./bf`. The interpreter will read Brainfuck code from a file named "source.bf" in the same directory.

## Limitations

This interpreter doesn't support the `[` and `]` commands, which are used in Brainfuck to create loops. Implementing these commands would require a more complex execution algorithm. Also, there's no bounds checking on the memory pointer, so moving the pointer too far to the left or right could cause a segmentation fault.