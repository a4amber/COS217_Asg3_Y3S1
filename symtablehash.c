  /*--------------------------------------------------------------------*/
/* symtablehash.c                                                     */
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
    /*the hash table: an array of pointers to Nodes*/
    struct Node** hash;
    /*number of elements in symbol table*/
     size_t length;
     /*the number of buckets the hashtable contains*/
     size_t buckets;
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
    symtab->buckets = 509;
    symtab->hash = (struct Node**) calloc(symtab->buckets,sizeof(struct Node*));
    symtab-> length = 0;
    return symtab;
  }

/*----------------------------------------------*/

/*SymTable_free frees all memory occupied by oSymTable*/

  void SymTable_free(SymTable_T oSymTable)
  {
    struct Node* toFree;
    size_t i = 0;
    assert(oSymTable != NULL); 

    /*free front to back key by node*/
  while (oSymTable->length > 0)
  {
  while(oSymTable->table[i] != NULL){
    toFree = table[i];
    table[i] = table[i]->next;
    free(toFree->key);
    free(toFree);
  } 
  i++;
  }
  free(hash);
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
        size_t bin;

        assert(pcKey != NULL);
        assert(oSymTable!= NULL);
        

        /*return false if binding exists*/
        bin = SymTable_hash(pcKey,oSymTable->buckets);
        current = oSymTable->hash[bin];
        while (current != NULL) 
        {
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
        if(oSymTable->hash[bin] != NULL)
        {
        temp = oSymTable->hash[bin];
        newNode->next = temp;
        }
        oSymTable->hash[bin] = newNode;
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
        size_t bin;

        assert(pcKey != NULL);
        assert(oSymTable != NULL);

        bin = SymTable_hash(pcKey,oSymTable->buckets);

        current = oSymTable->hash[bin];
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
        size_t bin;

        assert(oSymTable != NULL);
        assert(pcKey != NULL);

        bin = SymTable_hash(pcKey,oSymTable->buckets);

        current = oSymTable->hash[bin];
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
        size_t bin;

        assert(oSymTable != NULL);
        assert(pcKey != NULL);

        bin = SymTable_hash(pcKey,oSymTable->buckets);
        current = oSymTable->hash[bin];
        
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
        size_t bin;

        assert(oSymTable != NULL);
        assert(pcKey != NULL);

        bin = SymTable_hash(pcKey,oSymTable->buckets);
        current = oSymTable->hash[bin];

        if (current == NULL) return NULL;

        while (strcmp(current->key, pcKey) != 0) 
        {
            prior = current;
            current = current->next;
            if (current == NULL)
            return NULL;
        }
        remove = current;

        if(current != oSymTable->hash[bin])
        prior->next = current->next;
        else
        oSymTable->hash[bin] = current->next;

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
        size_t i = 0;
        size_t proc = 0;

        assert(oSymTable != NULL);
        assert(pfApply != NULL);


        current = oSymTable->hash[i];
        while (proc < oSymTable->length){
            while(current != NULL)
            {
                (*pfApply) ((void*) current->key, (void*) current->value, (void*) pvExtra);
                proc++;
                current = current->next;
            }
            i++;
            current = current[i];
        }
        
     }