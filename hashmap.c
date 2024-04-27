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
  Pair *mapAux = createPair(key,value);
  if (map->buckets[posicion] == NULL)
  {
    map->buckets[posicion] = mapAux;
    map->current = posicion;
    map->size++;
    return;
  }
  else
  {
    for (long i = posicion + 1 ; i < map->capacity ; i++)
    {
      if (map->buckets[i] == NULL)
        {
          map->buckets[i] = mapAux; 
          map->current = i;
          map->size++;
          return;
        }
    }
    for (long j = 0 ; j < posicion ; j++)
    {
        if(map->buckets[j] == NULL)
        {
          map->buckets[j] = mapAux;
          map->current = j;
          map->size++;
          return;
        }
    }
  }
    
}
void enlarge(HashMap * map) 
{
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

  printf("HOLa");
}

Pair * searchMap(HashMap * map,  char * key) 
{
  if (map == NULL)
  {
    return NULL;
  }
  long posicion = hash(key,map->capacity);
  if (posicion == -1)
  {
    return NULL;
  }
  else if (posicion < 0 || posicion >= map->capacity)
  {
    return NULL;
  }

  if (strcmp(map->buckets[posicion]->key,key) == 0)
  {
    map->current = posicion;
    return map->buckets[posicion];
  }
  else
  {
    for (long i = posicion +1 ; i < map->capacity && 
         map->buckets[i] != NULL ; i++)
      {
        if (map->buckets[i] != NULL && 
            strcmp(map->buckets[i]->key,key) == 0)
        {
          map->current = i;
          return map->buckets[i];
        }
      }

    for (long j = 0 ; j < posicion && map->buckets[j] 
         != NULL ; j++)
      {
        if (map->buckets[j] != NULL &&
            strcmp(map->buckets[j]->key,key) == 0)
        {
          map->current = j;
          return map->buckets[j];
        }
      }
  }
  return NULL;
}

Pair * firstMap(HashMap * map) 
{
  if (map == NULL)
  {
    return NULL;
  }
  for (long i = 0 ; i < map->capacity ; i++)
    {
      if (map->buckets[i] != NULL && map->buckets[i]->key != NULL)
      {
        map->current = i;
        return map->buckets[i];
      }
    }
  return NULL;
  
}

Pair * nextMap(HashMap * map) 
{
  if (map == NULL || firstMap(map) == NULL)
  {
    return NULL;
  }
  Pair *aux = firstMap(map);
  long posicion = hash(aux->value,map->capacity);

  for (long i = posicion + 1 ; i < map->capacity ; i++)
    {
      if (map->buckets[i] != NULL && map->buckets[i]->key != NULL)
      {
        map->current = i;
        return map->buckets[i];
      }
    }

    return NULL;
}
