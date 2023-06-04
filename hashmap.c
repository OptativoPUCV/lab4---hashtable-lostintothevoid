#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
 long cont = hash(key, map->capacity);
  
  while(map->buckets[cont] != NULL && map->buckets[cont]->key != NULL){
    cont = (cont + 1) % map->capacity;
  }

  map->buckets[cont] = createPair(key, value);
  map->current = cont;
  map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap* temp= (HashMap*) malloc(sizeof( HashMap*)*capacity);
  temp->buckets=(Pair **)malloc(sizeof(Pair *) * capacity);
  temp->capacity=capacity;
  temp->size=0;
  temp->current=-1;
  for (long i = 0; i < capacity; i++) {
    temp->buckets[i] = NULL;
  }
  return temp;
}

void eraseMap(HashMap * map,  char * key) {    
  Pair *par=searchMap(map, key);
  if(par!=NULL){
    par->key=NULL;
    map->size--;
  }

}

Pair * searchMap(HashMap * map,  char * key) {   
  long poss=hash(key, map->capacity);
  while(map->buckets[poss] != NULL){
    if (is_equal(map->buckets[poss]->key, key)){
      
          map->current = poss;

          return map->buckets[poss];
      }
      poss = (poss + 1) % map->capacity;
  }

  return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
