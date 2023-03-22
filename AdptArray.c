#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

// AdptArray struct definition
typedef struct AdptArray_
{
    PElement *array;
    int size;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
} AdptArray, *PAdptArray;
#define INITIAL_SIZE 1

// create a new adaptive array with the given functions and return a pointer to it
// if allocation fails, free all the allocations and return NULL
PAdptArray CreateAdptArray(COPY_FUNC CF, DEL_FUNC DF, PRINT_FUNC PF)
{
    PAdptArray p = (PAdptArray)malloc(sizeof(AdptArray));
    if (!p)
        return NULL;
    p->array = (PElement *)malloc(sizeof(PElement) * INITIAL_SIZE);
    if (!p->array)
    {
        free(p);
        return NULL;
    }
    p->array[0] = NULL;
    p->size = INITIAL_SIZE;
    p->copy_func = CF;
    p->del_func = DF;
    p->print_func = PF;
    return p;
}

// if p is NULL, do nothing
//  if p is not NULL, free all the elements in the array and then free the array and the struct
//  if p is not NULL, free the array and the struct
void DeleteAdptArray(PAdptArray p)
{
    if (!p)
        return;
    for (int i = 0; i < p->size; i++)
    {
        if (p->array[i])
            p->del_func(p->array[i]);
    }
    free(p->array);
    free(p);
}

// if index is negative, return FAIL
// SetAdtArrayAt(p, 0, element) - if the array is empty, create a new array with size 1 and put the element in the first place
// Result set atp array at p 0 element if the array is empty create a new array with size 1 and put the element in the first place
// if index is bigger than the size of the array, create a new array with size index+1 and copy all the elements from the old array to the new array.
// this function should not change the size of the array if the index is smaller than the size of the array and there is already an element in the index
// if index is smaller than the size of the array and there is no element in the index, put the element in the index and return SUCCESS

Result SetAdptArrayAt(PAdptArray p, int index, PElement pe)
{
    if (!p)
        return FAIL;
    if (index < 0)
        return FAIL;
    if (index >= p->size)
    {
        int tmpsize = p->size;
        p->size = index + 1;
        // printf("size: %d index: %d tmpsize: %d p->size: %d p->array: %p p->array[0]: %p )
        // ", p->size, index, tmpsize, p->size, p->array, p->array[0]);
        p->array = (PElement *)realloc(p->array, sizeof(PElement) * p->size);
        if (!p->array)
            return FAIL;
        for (int i = tmpsize; i < p->size; i++)
        {
            p->array[i] = NULL;
        }
    }
    if (p->array[index])
    {
        p->del_func(p->array[index]);
        p->array[index] = NULL;
    }
    p->array[index] = p->copy_func(pe);
    if(!p->array[index]){
        return FAIL;
    }
    return SUCCESS;
}

// if index is negative or index is bigger than the size of the array, return NULL
// if index is in the array but there is no element in this index, return NULL
PElement GetAdptArrayAt(PAdptArray p, int index)
{
    if (!p)
        return NULL;
    if (index < 0)
        return NULL;
    if (index >= p->size)
        return NULL;
    if (p->array[index])
    {
        return p->copy_func(p->array[index]);
    } // else
    return NULL;
}

// if p is NULL, return -1
//  if p is not NULL, return the size of the array
int GetAdptArraySize(PAdptArray p)
{
    if (!p)
        return -1;
    return p->size;
}

// Print all the elements in the array
void PrintDB(PAdptArray p)
{
    if (!p)
        return;
    for (int i = 0; i < p->size; i++)
    {
        if (p->array[i])
            p->print_func(p->array[i]);
    }
}

// AdptArray.h - the header file of the adaptive array
// AdptArray.c - the implementation file of the adaptive array
// book.h - the header file of the book struct
// book.c - the implementation file of the book struct
// Person.h - the header file of the person struct
// Person.c - the implementation file of the person struct
// main.c - the main file of the program
// Makefile - the makefile of the program


