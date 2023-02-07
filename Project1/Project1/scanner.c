#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "scanner.h"
#include "core.h"

// Below are the values we want to persist as the scanner runs

// This maintains a pointer to the file
static FILE* fp;

// This is the string making up the current token
static char* tokenString;

// This is the enum value for the current token
static int token;



// Below are the functions that make up the scanner

// Opens the file, find the first token
int scanner_open(char* filename) {
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: File %s couldn't be opened!\n", filename);
    }
    tokenString = NULL;
    return nextToken();
}

// Frees memory allocated for the scanner
int scanner_close() {
    fclose(fp);
    free(tokenString);
}

// Returns the current token (enum value)
int currentToken() {
    return token;
}

// Finds the next token (or the first token when called by scanner_open)
int nextToken() {
    int c, i;

    /* Get the next character */
    c = fgetc(fp);

    if (c != EOF) {
        /* Read the next non-space character */
        while (isspace(c)) {
            c = fgetc(fp);
        }

        /* Symbols */
        if (c == '+') {
            token = ADD;
        }
        else if (c == '-') {
            token = SUBTRACT;
        }
        else if (c == '*') {
            token = MULTIPLY;
        }
        else if (c == '/') {
            token = DIVIDE;
        }
        else if (c == '=') {
            token = EQUAL;
        }
        else if (c == ':') {
            c = fgetc(fp);
            if (c == '=') {
                token = ASSIGN;
            }
            else {
                token = COLON;
                ungetc(c, fp);
            }
        }
        else if (c == '<') {
            token = LESS;
        }
        else if (c == ';') {
            token = SEMICOLON;
        }
        else if (c == '.') {
            token = PERIOD;
        }
        else if (c == ',') {
            token = COMMA;
        }
        else if (c == '(') {
            token = LPAREN;
        }
        else if (c == ')') {
            token = RPAREN;
        }
        else if (c == '[') {
            token = LBRACE;
        }
        else if (c == ']') {
            token = RBRACE;
        }
        else if (isalpha(c)) {  /* Keywords and ID */
            tokenString = (char*)malloc(sizeof(char) * 10);

            i = 0;
            do {
                tokenString[i] = (char)c;
                i++;
                c = fgetc(fp);
            } while (isalnum(c));

            tokenString[i] = '\0';
            ungetc(c, fp);

            if (strcmp(tokenString, "and") == 0) {
                token = AND;
            }
            else if (strcmp(tokenString, "begin") == 0) {
                token = BEGIN;
            }
            else if (strcmp(tokenString, "do") == 0) {
                token = DO;
            }
            else if (strcmp(tokenString, "else") == 0) {
                token = ELSE;
            }
            else if (strcmp(tokenString, "end") == 0) {
                token = END;
            }
            else if (strcmp(tokenString, "if") == 0) {
                token = IF;
            }
            else if (strcmp(tokenString, "in") == 0) {
                token = IN;
            }
            else if (strcmp(tokenString, "integer") == 0) {
                token = INTEGER;
            }
            else if (strcmp(tokenString, "is") == 0) {
                token = IS;
            }
            else if (strcmp(tokenString, "new") == 0) {
                token = NEW;
            }
            else if (strcmp(tokenString, "not") == 0) {
                token = NOT;
            }
            else if (strcmp(tokenString, "or") == 0) {
                token = OR;
            }
            else if (strcmp(tokenString, "out") == 0) {
                token = OUT;
            }
            else if (strcmp(tokenString, "procedure") == 0) {
                token = PROCEDURE;
            }
            else if (strcmp(tokenString, "record") == 0) {
                token = RECORD;
            }
            else if (strcmp(tokenString, "then") == 0) {
                token = THEN;
            }
            else if (strcmp(tokenString, "while") == 0) {
                token = WHILE;
            }
            else {
                token = ID;
            }
        }
        else if (isdigit(c)) {  /* Number(CONST) */
            tokenString = (char*)malloc(sizeof(char) * 10);

            i = 0;
            do {
                tokenString[i] = (char)c;
                i++;
                c = fgetc(fp);
            } while (isdigit(c));

            tokenString[i] = '\0';
            ungetc(c, fp);

            if (atoi(tokenString) > 1009) {
                fprintf(stderr, "ERROR: Number is larger than the MAX\n");
                token = ERROR;
                exit(0);
            }
            else {
                token = CONST;
            }
        }
        else {
            fprintf(stderr, "ERROR: Unexpected Character input\n");
            token = ERROR;
            exit(0);
        }
    }
    else {
        token = EOS;
    }

    return token;
}

// Passes back the string value, so the parse tree (project 2) will be able to store identifiers
void getId(char* identifier) {
    strcpy(identifier, tokenString);
}

// Passes back the constant value, so the parse tree (project 2) will be able to store const values
int getConst() {
    return atoi(tokenString);
}