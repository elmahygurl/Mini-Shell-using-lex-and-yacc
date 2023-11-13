# Mini-Shell-using-lex-and-yacc
## Project Overview & Background
The mini shell program created using lex and yacc offers a straightforward implementation of a shell, which serves as a command-line interface for interacting with an operating system. This program utilizes two essential tools: lex and yacc.

Lex plays a role in defining the lexical structure of the shell, encompassing keywords, operators, and special symbols. It transforms these components into tokens that yacc can process effectively.
Yacc, on the other hand, is responsible for outlining the grammar and syntax of the shell. It takes the tokens produced by lex, using them to construct the structure of shell commands. Additionally, yacc implements the necessary actions for executing these commands, such as invoking system functions or running external programs.

The collaboration between lex and yacc provides a simple yet robust framework for developing a shell program. This makes it an excellent choice for gaining insights into shell programming and understanding the fundamentals of parsing.

## Prerequisites 
Before running the mini shell program, ensure that you have the following:
1. **Operating System:**
   - Linux (Ubuntu)
2. **Required Software:**
   - C Compiler
   - Make
3. **Additional Tools:**
   - Bison
   - Flex

## Installation 
You can install the required tools on a Debian-based system (Ubuntu) using the following commands:

   ### For C Compiler and Make
   
   sudo apt-get update
   
   sudo apt-get install build-essential
   
   ### For Bison and Flex
   
   sudo apt-get install bison flex

## Run 
- Navigate to directory
- Run make
  ```bash
  make
  
## Authors 
- [Youssef Elkady](https://github.com/Youssef-Elkady)
- [Salma ElMahy](https://github.com/elmahygurl)
