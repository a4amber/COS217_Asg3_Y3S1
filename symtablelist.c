  /*--------------------------------------------------------------------*/
/* symtablelist.c                                                     */
/* Author: Amber Chow                                                     */
/*--------------------------------------------------------------------*/
#include "symtable.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


/*----------------------------------------------*/


/*representation of the Symbol Table object*/
struct Node {char* key; const void * value; struct Node *next;}; //CONST VALUE
struct SymTable {struct Node *first; size_t length;} ;

/*----------------------------------------------*/

/*The SymTable_new() function returns a new SymTable object 
that contains no bindings, or NULL if insufficient memory is available.*/  

  SymTable_T SymTable_new(void)
  {
    SymTable_T *st;
    st = calloc(1, sizeof(*st)); 
    if (st == NULL) return NULL;
    return *st;
  }

/*----------------------------------------------*/

/*SymTable_free frees all memory occupied by oSymTable*/

  void SymTable_free(SymTable_T oSymTable)
  {
  assert(oSymTable != NULL); 

    /*free front to back key by node*/
  while (oSymTable->first != NULL)
  {
  struct Node* toFree = oSymTable->first ; 
  oSymTable->first = oSymTable->first->next;
  free(toFree->key);
  free(toFree);
  }
  free(oSymTable);
  }

/*----------------------------------------------*/

/*SymTable_getLength must return the number of bindings in oSymTable.*/

  size_t SymTable_getLength(SymTable_T oSymTable)
  {
    assert(oSymTable != NULL);
    return oSymTable->length; 
  }

/*----------------------------------------------*/

/*If oSymTable does not contain a binding with key pcKey,
 then SymTable_put adds a new binding to oSymTable consisting 
 of key pcKey and value pvValue and return 1 (TRUE). 
 Otherwise the function must leave oSymTable unchanged 
 and return 0 (FALSE). If insufficient memory is available,
  then the function must leave oSymTable unchanged and return 0 (FALSE).*/



  int SymTable_put(SymTable_T oSymTable,
     const char *pcKey, const void *pvValue)
     {
        assert(pcKey != NULL);
        assert(pvValue != NULL);

        /*return false if binding exists*/
        struct Node *current = oSymTable->first;
        while (strcmp(current->key, pcKey) != 0) 
        {
            current = current->next;
            if (current == NULL)
            return 0;
        }

        struct Node* newNode = calloc(1, sizeof(struct Node));
        if(newNode == NULL) return 0;
        newNode->key = calloc(strlen(pcKey)+1, sizeof(char));
        if(newNode == NULL) return 0;
        strcpy(newNode->key, pcKey);
        newNode->value = pvValue;
        oSymTable->first->next = oSymTable->first;
        oSymTable->first = newNode;
        oSymTable->length++;
        return 1;

     }

/*----------------------------------------------*/

/*If oSymTable contains a binding with key pcKey, 
then SymTable_replace must replace the binding's value 
with pvValue and return the old value. 
Otherwise it must leave oSymTable unchanged and return NULL.*/

  void *SymTable_replace(SymTable_T oSymTable,
     const char *pcKey, const void *pvValue) 
     {
        assert(pcKey != NULL);
        assert(pvValue != NULL);

        struct Node *current = oSymTable->first;
        while (strcmp(current->key, pcKey) != 0) 
        {
            current = current->next;
            if (current == NULL)
            return NULL;
        }
        struct Node* old = current->value;
        current->value = pvValue;
        return old;
     }

/*----------------------------------------------*/

/*SymTable_contains must return 1 (TRUE) if oSymTable 
contains a binding whose key is pcKey, and 0 (FALSE) otherwise.*/

  int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
  {
        assert(oSymTable != NULL);
        assert(pcKey != NULL);

        struct Node *current = oSymTable->first;
        while (strcmp(current->key, pcKey) != 0) 
        {
            current = current->next;
            if (current == NULL)
            return 0;
        }
        return 1;
  }

/*----------------------------------------------*/

/*SymTable_get must return the value of the binding within oSymTable
 whose key is pcKey, or NULL if no such binding exists.*/

  void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
  {
        assert(oSymTable != NULL);
        assert(pcKey != NULL);

        struct Node *current = oSymTable->first;
        while (strcmp(current->key, pcKey) != 0) 
        {
            current = current->next;
            if (current == NULL)
            return NULL;
        }
        return current->value;

  }

/*----------------------------------------------*/

/*If oSymTable contains a binding with key pcKey, 
then SymTable_remove must remove that binding from 
oSymTable and return the binding's value. 
Otherwise the function must not change oSymTable and return NULL.*/

  void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
  {
        assert(oSymTable != NULL);
        assert(pcKey != NULL);

        struct Node *current = oSymTable->first;
        while (strcmp(current->key, pcKey) != 0) 
        {
            current = current->next;
            if (current == NULL)
            return NULL;
        }
        struct Node * remove = current;
        current = current->next;
        free(remove->key);
        const void* removedVal = remove->value; 
        free(remove);
        oSymTable->length--;
        return removedVal;
  }

/*----------------------------------------------*/

/*SymTable_map must apply function *pfApply to each binding
in oSymTable, passing pvExtra as an extra parameter. 
That is, the function must call (*pfApply)(pcKey, pvValue, pvExtra)
 for each pcKey/pvValue binding in oSymTable.*/

  void SymTable_map(SymTable_T oSymTable,
     void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
     const void *pvExtra)
     {
        assert(oSymTable != NULL);
        assert(pfApply != NULL);

        struct Node *current = oSymTable->first;
        while (current != NULL)
        {
            current = current->next;
            (*pfApply) ((void*) current->key, (void*) current->value, (void*) pvExtra);
        }
        
     }