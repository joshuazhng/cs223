/*
 * NodeType.h
 * Joshua Zhang
 * CPSC 223 PSET 4
 * 4/6/23
 * Small struct that is part of a Linked List class
 */

#include "Station.h"
using namespace std;

#ifndef NODETYPE
#define NODETYPE

struct NodeType
{
    Station info;
    NodeType *next;
};

#endif
