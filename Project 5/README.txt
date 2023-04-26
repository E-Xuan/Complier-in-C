This is a README file for CSE3341 Project 5

Author Name: Yixuan Huang

This project contains
C source files: main.c, execute.c, memory.c, parser.c, scanner.c
Header files: core.h, execute.h, memory.h, parser.h, scanner.h, tree.h
README file

main.c : it has a main function which is used for opening the file, read and build the parse tree, execute the parse tree, and close the file scanner.

execute.c : it has several functions which are used to execute the parse tree and print the outcome value.

memory.c : it contains several helper function for execute.c to store the integer const values or record values in specific position based on the variable declare sequence.

parser.c : it has functions which are used to read the file and build the parse tree, afte this file, the parse tree will be updated with important information.

scanner.c : this file is written in project 1 and does not have any change. It is used for read the char and return the tokens. 

In this lab, I have fixed the memory.c so that we running the code, it will also print the number of reachable variables at current time. Every time when the number of reachable variable changes, it will print "gc: number of reachable". To achieve, this I use the callStack[fp]->rValues[location][1] to store the reference count for each record variable. If the value changes to 0, which means it is thrown to the gabage collection. Then the number of reachable will decrease. And everytime when we create new record variable, the number of reachable will increase. Also, when a function call is done (including main function), all record valriables in this function will become unreachable, and we need to free all variables in this function.

In order to test the project, I have used the correcct file folder and error file folder which provided by professor. I first used command ./main Correct/#.code Correct/#.data to test signle code, and then I used command ./tester.sh to run all the correct test cases and error test cases. The outcome is: 
Correct cases score out of 10:
10
Done!