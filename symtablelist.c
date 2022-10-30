  /*--------------------------------------------------------------------*/
/* symtablelist.c                                                     */
/* Author: Amber Chow                                                     */
/*--------------------------------------------------------------------*/
#include "symtable.h"
#include <assert.h>

/*----------------------------------------------*/

//  GENERALLY AM I ON THE RIGHT TRACK
//  USAGE OF STRUCT (CHANGE THE INPUT)
//

/*representation of the Symbol Table object*/
struct Node {const char* key; void * value; struct Node *next}
struct List {struct Node *first; size_t length;}
struct SymTable {const struct List *list}

/*----------------------------------------------*/

/*The SymTable_new() function returns a new SymTable object 
that contains no bindings, or NULL if insufficient memory is available.*/  

  struct SymTable SymTable_new(void)
  {
    struct SymTable *st;
    st = calloc(1, sizeof(*st));
    if(st == NULL) return NULL;
  }

/*----------------------------------------------*/

/*SymTable_free frees all memory occupied by oSymTable*/

  void SymTable_free( struct SymTable oSymTable)
  {
  assert(oSymTable != NULL);  //WHY DOES THIS NOT COLOR CORRECTLY

    /*free front to back key by node*/
  while (oSymTable->first != NULL)
  {
  struct Node* toFree = oSymTable->first ; 
  oSymTable->first = oSymTable->next;
  free(toFree->key);
  free(toFree);
  }
  free(oSymTable->list);
  free(oSymTable);
  }

/*----------------------------------------------*/

/*SymTable_getLength must return the number of bindings in oSymTable.*/

  size_t SymTable_getLength(struct SymTable oSymTable)
  {
    assert(oSymTable != NULL);
    return oSymTable->length; //NEED TO INCLUDE LIST?
  }

/*----------------------------------------------*/
// I NEED TO UNCOMMENT THESE EVENTUALLY RIGHT?

/*If oSymTable does not contain a binding with key pcKey,
 then SymTable_put adds a new binding to oSymTable consisting 
 of key pcKey and value pvValue and return 1 (TRUE). 
 Otherwise the function must leave oSymTable unchanged 
 and return 0 (FALSE). If insufficient memory is available,
  then the function must leave oSymTable unchanged and return 0 (FALSE).*/

  int SymTable_put(struct SymTable oSymTable,
     const char *pcKey, const void *pvValue)
     {
        assert(*pcKey != NULL);
        assert(*pvValue != NULL);

        /*return false if binding exists*/
        struct Node *current = oSymtable->first;
        while (&current->key != &pcKey)
        {
            current = current.next;
            if (current = NULL)
            return FALSE;
        }

        struct Node* newNode = calloc(1, sizeof(struct Node));
        newNode.key = calloc(strlen(pcKey)+1, sizeof(char));
        newNode->key = pcKey;
        newNode.value = pvValue;
        oSymTable->next = oSymTable->first;
        oSymTable->next = newNode;
        oSymTable->length++;
        return TRUE;

     }

/*----------------------------------------------*/

/*If oSymTable contains a binding with key pcKey, 
then SymTable_replace must replace the binding's value 
with pvValue and return the old value. 
Otherwise it must leave oSymTable unchanged and return NULL.*/

  void *SymTable_replace(struct SymTable oSymTable,
     const char *pcKey, const void *pvValue)
     {
        assert(*pcKey != NULL);
        assert(*pvValue != NULL);

        struct Node *current = oSymtable->first;
        while (&current->key != &pcKey)
        {
            current = current->next;
            if (current = NULL)
            return NULL;
        }
        struct Node* old = current->value;
        current->value = pvValue;
        return &old;
     }

/*----------------------------------------------*/

/*SymTable_contains must return 1 (TRUE) if oSymTable 
contains a binding whose key is pcKey, and 0 (FALSE) otherwise.*/

  int SymTable_contains(struct SymTable oSymTable, const char *pcKey)
  {
        assert(oSymTable != NULL);
        assert(*pcKey != NULL);

        struct Node *current = oSymtable->first;
        while (&current->key != &pcKey)
        {
            current = current->next;
            if (current = NULL)
            return FALSE;
        }
        return TRUE;
  }

/*----------------------------------------------*/

/*SymTable_get must return the value of the binding within oSymTable
 whose key is pcKey, or NULL if no such binding exists.*/

  void *SymTable_get(struct SymTable oSymTable, const char *pcKey)
  {
        assert(oSymTable != NULL);
        assert(*pcKey != NULL);

        struct Node *current = oSymtable->first;
        while (&current->key != &pcKey)
        {
            current = current.next;
            if (current = NULL)
            return NULL;
        }
        return current->value;

  }

/*----------------------------------------------*/

/*If oSymTable contains a binding with key pcKey, 
then SymTable_remove must remove that binding from 
oSymTable and return the binding's value. 
Otherwise the function must not change oSymTable and return NULL.*/

  void *SymTable_remove(struct SymTable oSymTable, const char *pcKey)
  {
        assert(oSymTable != NULL);
        assert(*pcKey != NULL);

        struct Node *current = oSymtable->first;
        while (&current->key != &pcKey)
        {
            current = current.next;
            if (current = NULL)
            return NULL;
        }
        struct Node * remove = current;
        current = current.next
        free(remove.key);
        void* removedVal = remove.value;
        free(remove);
        oSymTable->length--;
        return &removedVal;
  }

/*----------------------------------------------*/

/*SymTable_map must apply function *pfApply to each binding
in oSymTable, passing pvExtra as an extra parameter. 
That is, the function must call (*pfApply)(pcKey, pvValue, pvExtra)
 for each pcKey/pvValue binding in oSymTable.*/

  void SymTable_map(struct SymTable oSymTable,
     void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
     const void *pvExtra)
     {
        assert(oSymTable != NULL);
        assert(pfApply != NULL);

        struct Node *current = oSymtable->first;
        while (current != NULL)
        {
            current = current->next;
            (*pfApply) ((void*) current->key, (void*) pvExtra;
        }
        
     }