#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "core.h"
#include "memory.h"

/*
*
* Data Structs
*
*/

static char** iLookup;
static int* iValues;
static int iLen;

static char** rLookup;
static int** rValues;
static int rLen;


/*
*
* Helper functions
*
*/

// If iden is an integer, return the index. Otherwise, return -1
static int searchInteger(char* iden) {
	int location = -1;
	for (int i=0; i<iLen; i++) {
		if (strcmp(iLookup[i], iden)==0) {
			location = i;
		}
	}
	return location;
}

// If iden is a record, return the index. Otherwise, return -1
static int searchRecord(char* iden) {
	int location = -1;
	for (int i=0; i<rLen; i++) {
		if (strcmp(rLookup[i], iden)==0) {
			location = i;
		}
	}
	return location;
}


/*
*
* Memory functions
*
*/

// Initialize data structures
// Don't worry about freeing memory, will do that in project 5
void memory_init() {
	iLookup = malloc(0);
	iValues = malloc(0);
	iLen = 0;
	
	rLookup = malloc(0);
	rValues = malloc(0);
	rLen = 0;
}

// Handle an integer or record declaration
void declare(char* iden, int type) {
	if (type == INTEGER) {
		iLen++;
		iLookup = realloc(iLookup, iLen*sizeof(char*));
		iLookup[iLen-1] = iden;
		iValues = realloc(iValues, iLen*sizeof(int));
		iValues[iLen-1] = 0;
	} else {
		rLen++;
		rLookup = realloc(rLookup, rLen*sizeof(char*));
		rLookup[rLen-1] = iden;
		rValues = realloc(rValues, rLen*sizeof(int*));
		rValues[rLen-1] = calloc(1, sizeof(int));
	}
}

// Store a value to a variable. Remember, unindexed stores to a record go to index 0
void store(char* iden, int value) {
	int location = searchInteger(iden);
	if (location == -1) {
		storeRec(iden, 0, value);
	} else {
		iValues[location] = value;
	}
}

// Read a value from a variable. Remember, unindexed reads from a record read index 0
int recall(char* iden) {
	int location = searchInteger(iden);
	if (location == -1) {
		return recallRec(iden, 0);
	} else {
		return iValues[location];
	}
}

// Store a value to a record variable, at the given index
void storeRec(char* iden, int index, int value) {
	int location = searchRecord(iden);
	if (index+1 <= rValues[location][0]) {
		rValues[location][index+1] = value;
	} else {
		printf("Runtime Error: write to index %d outside of array %s bounds!\n", index, iden);
		exit(0);
	}
}

// Read a value from a record variable, from the given index
int recallRec(char* iden, int index) {
	int location = searchRecord(iden);
	if (index+1 <= rValues[location][0]) {
		return rValues[location][index+1];
	} else {
		printf("Runtime Error: read from index %d outside of array %s bounds!\n", index, iden);
		exit(0);
	}
	return 0;
}

// Handle "id := record id" type assignment
void record(char* lhs, char* rhs) {
	int locLhs = searchRecord(lhs);
	int locRhs = searchRecord(rhs);
	rValues[locLhs] = rValues[locRhs];
}

// Handle "id := new record[<expr>]" type assignment
void allocateRecord(char* iden, int size) {
	int location = searchRecord(iden);
	rValues[location] = calloc(size+1, sizeof(int));
	rValues[location][0] = size;
}