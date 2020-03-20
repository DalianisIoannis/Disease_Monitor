#pragma once
#define GNU_SOURCE

#include "../headers/linkedList.h"
#include "../headers/HashTable.h"
#include "../headers/generalFuncs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool disMonitor(char*, int, int, int);
bool initMonitor(FILE**, Linked_List*, char*);
void emptyMonitor(FILE**, Linked_List*, char**, HashTable*, HashTable*, AVLTreePtr*);
bool inputLLtoHT(Linked_List, HashTable, int);
void Querries(HashTable, HashTable, Linked_List, AVLTreePtr*);