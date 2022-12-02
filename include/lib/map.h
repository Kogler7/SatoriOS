#ifndef _SYSTEM_LIB_MAP_H_
#define _SYSTEM_LIB_MAP_H_

typedef struct map
{
    void *key;
    void *value;
} map;

int map_init(map *m, void *key, void *value);

int map_set(map *m, void *key, void *value);

int map_get(map *m, void *key, void **value);

#endif /* !_SYSTEM_LIB_MAP_H_ */