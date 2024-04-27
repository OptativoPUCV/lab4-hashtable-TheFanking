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


void insertMap(HashMap * map, char * key, void * value) 
{
  long posicion = hash(key,map->capacity);
  if (posicion == -1)
  {
    exit(EXIT_FAILURE);
  }
  if (posicion < 0 || posicion > map->capacity)
  {
    exit(EXIT_FAILURE);
  }
  Pair *mapAux = createPair(key,value);
  if (mapAux == NULL)
    {
      exit(EXIT_FAILURE);
    }
  if (mapAux[posicion] == NULL)
  {
    map->buckets[posicion] = createPair(key, value);
    map->current++;
    map->size++;
  }
  else
  {
    for (long i = posicion ; i < map->capacity ; i++)
    {
      if (map->buckets[i] == NULL)
        {
          map->buckets[i] = createPair(key,value); 
          map->current++;
          map->size++;
          return;
        }
    }
    for (long j = 0 ; j < posicion ; j++)
    {
        if(map->buckets[j] == NULL)
        {
          map->buckets[j] = createPair(key,value);
          map->current++;
          map->size++;
          return;
        }  
    }
}
void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
    HashMap *map = malloc(sizeof(HashMap));
    if (map == NULL)
    {
      exit(EXIT_FAILURE); 
    }
    map->capacity = capacity;
    map->buckets = malloc(capacity * sizeof(HashMap *));
    if (map->buckets == NULL)
    {
      exit(EXIT_FAILURE);
    }
    for (int i = 0 ; i < map->capacity ; i++)
      {
        map->buckets[i] = NULL;
          
      }
    map->size = 0;
    map->current = -1;

    return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
