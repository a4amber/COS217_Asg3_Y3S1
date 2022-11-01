  /*--------------------------------------------------------------------*/
/* symtablehash.c                                                    */
/* Author: Amber Chow                                                     */
/*--------------------------------------------------------------------*/
#include "symtable.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


/*----------------------------------------------*/


/*representation of the nodes used to implement symbol table*/
struct Node {
    /*string key*/
    char* key;
    /*value provided by client*/
     void * value;
     /*next node in linked list implementation*/
     struct Node *next;}; 

/*a represenation of the Symbol Table object*/
struct SymTable {
    /*location of hash array*/
    void *hash;
    /*number of elements in symbol table*/
     size_t length;
     /*number of bucket counts*/
     size_t numBuck;
     } ;


/*----------------------------------------------*/

/* Return a hash code for pcKey that is between 0 and uBucketCount-1,
   inclusive. */

static size_t SymTable_hash(const char *pcKey, size_t uBucketCount)
{
   const size_t HASH_MULTIPLIER = 65599;
   size_t u;
   size_t uHash = 0;

   assert(pcKey != NULL);

   for (u = 0; pcKey[u] != '\0'; u++)
      uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];

   return uHash % uBucketCount;
}

/*----------------------------------------------*/
/*The SymTable_new() function returns a new SymTable object 
that contains no bindings, or NULL if insufficient memory is available.*/  

  SymTable_T SymTable_new(void)
  {
    SymTable_T symtab;
    symtab = (SymTable_T) malloc(sizeof(struct SymTable)); 
    if (symtab == NULL) return NULL;
    symtab->length = 0;
    symtab->numBuck = 509;
    symtab->hash = calloc(symtab->numBuck, sizeof(void*));
    if(symtab->hash == NULL) return NULL;
    return symtab;
  }

/*----------------------------------------------*/

/*SymTable_free frees all memory occupied by oSymTable*/

  void SymTable_free(SymTable_T oSymTable)
  {
    struct Node* toFree;
    void* current;
    
    size_t elementsProc;
    size_t i;

    assert(oSymTable != NULL); 

    /*free front to back key by node*/
       
        current = oSymTable->hash;
        while (elementsProc != oSymTable->length)
        {
            while (current == NULL){
                 current++;
                 i++;
            }

            toFree = *current;
            current = current->next;
            free(toFree->key);
            free(toFree);
            elementsProc++;

            if(current == NULL)
            i++;
            current = oSymTable->hash[i];
        }

  free(oSymTable->hash);
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
        struct Node *current;
        struct Node* newNode;
        struct Node* temp;
        size_t bucket;

        assert(pcKey != NULL);
        assert(oSymTable!= NULL);
        
        bucket = SymTable_hash(pcKey, oSymTable->numBuck);

        while (oSymTable->hash[bucket] != NULL) 
        {
            current = *oSymTable->hash[bucket];
            if( strcmp(current->key, pcKey) ==0)
            return 0;
            current = current->next;
        }

        newNode = calloc(1, sizeof(struct Node));
        if(newNode == NULL) return 0;
        newNode->key = calloc(strlen(pcKey)+1, sizeof(char));
        if(newNode == NULL) return 0;
        strcpy(newNode->key, pcKey);
        newNode->value = (void*) pvValue;
        if(oSymTable->hash[bucket] != NULL)
        {
        temp = oSymTable->hash[bucket]->next;
        newNode->next = temp;
        }
        oSymTable->hash[bucket] = newNode;
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
        struct Node *current;
        struct Node* old;
        size_t bucket;

        assert(pcKey != NULL);
        assert(oSymTable != NULL);

        bucket = SymTable_hash(*pcKey, oSymTabl->numBuck);
        
        current = oSymTable->hash[bucket];
        if(current == NULL) return NULL;

        while (strcmp(current->key, pcKey) != 0) 
        {
            current = current->next;
            if (current == NULL)
            return NULL;
        }
        old = current->value;
        current->value = (void*) pvValue;
        return old;
     }

/*----------------------------------------------*/

/*SymTable_contains must return 1 (TRUE) if oSymTable 
contains a binding whose key is pcKey, and 0 (FALSE) otherwise.*/

  int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
  { 
        struct Node *current;
        size_t bucket;

        assert(oSymTable != NULL);
        assert(pcKey != NULL);

        bucket = SymTable_hash(*pcKey, oSymTable->numBuck);
        
        current = oSymTable->hash[bucket];
        if (current == NULL) return 0;

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
        struct Node *current;
        size_t bucket;

        assert(oSymTable != NULL);
        assert(pcKey != NULL);

        bucket = SymTable_hash(*pcKey, oSymTable->numBuck);
        
        current = oSymTable->hash[bucket];
        
        if (current == NULL) return NULL;

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
        struct Node *current;
        struct Node *prior;
        struct Node * remove;
        void* removedVal;
        size_t bucket;

        assert(oSymTable != NULL);
        assert(pcKey != NULL);

        bucket = SymTable_hash(*pcKey, oSymTable.numBuck);
        
        current = oSymTable->hash[bucket];
        if (current == NULL) return NULL;

        while (strcmp(current->key, pcKey) != 0) 
        {
            prior = current;
            current = current->next;
            if (current == NULL)
            return NULL;
        }
        remove = current;

        if(current != oSymTable->first)
        prior->next = current->next;
        else
        oSymTable->first = current->next;

        removedVal = remove->value; 
        free(remove->key);
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
        struct Node *current;
        size_t elementsProc;
        size_t i;

        assert(oSymTable != NULL);
        assert(pfApply != NULL);
        
        current = oSymTable->hash;
        while (elementsProc != oSymTable.length)
        {
            while (current == NULL){
                 current++;
                 i++;
            }

            (*pfApply) ((void*) current->key, (void*) current->value, (void*) pvExtra);
            current = current->next;
            elementsProc ++;
            if(current == NULL)
            i++;
            current = oSymTable->hash[i];
        }
        
     }
     
