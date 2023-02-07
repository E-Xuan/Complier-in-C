Name: Yixuan Huang

Files: main.c, core.h, scanner.c, scanner.h, and README.txt

main.c: This class contains a main function and it is provided by downloading file lab1.zip. I do not add or delete any code in this file.

core.h: This is a definition class which contins all possibile labels. It is provided by lab1.zip, and I do not add or delete any code in this file.

scanner.c: This class has several functions:
          scanner_open function is used to open the file, and find the first token;
          scanner_close function is used to close the file and frees memory allocated for the scanner;
          currentToken function returns the current token (enum value);
          nextToken function finds the next token or the first token when called by scanner_open and return its enum value to main function;
          getId function passes back the string value, so the parse tree will be able to store identifiers;
          getConst function passes back the constant value, so the parse tree will be able to store const values.
I have added code for currentToken function and nextToken function. The rest function's code has already provided by lab1.zip. 

scanner.h: This is a function prototype file for scanner.c. I do not add or delete any code in this file.

I have used ChatGPT to get some basic ideas on how to form the structure. ChatGPT will only provide a sample solution for nextToken function and I have to
do all the works by my own. Actually, I finally do this project more rely on the ScannerOutline.pdf and write my code.

One known bug during I worte my scanner.c file is that when I wrote the condition to check the input string, I wrote strcmp(tokenString, keywords) 
and forget to add == 0 which caused all input string will return random keywords enum value, for example, input string while may return a token ADD. 
But I have already fixed this bug.

Another small bug which is still in my project is that sometimes, it will return an error message when reading 
the end of the input file. However, This bug only appears in one of correct code test, but I can not remember 
which correct test makes this bug. After printing all correct answer, my programm will add ERROR: Something meaningful here in the end. Even if my
code does not have this sentence. After I debug my code, I find that some correct test case will end with a space line after the last word, and it 
does not allowed in my code, so it will print the error message. However, I really have no ideas on how to fix this bug. My code will provide the correct
answer/ expected answer, but will add one more line in the end.