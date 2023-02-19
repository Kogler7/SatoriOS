#ifndef _SIMPLE_DYNAMIC_STR_H_
#define _SIMPLE_DYNAMIC_STR_H_

typedef char *sds;

struct sdshdr {
    int len;
    int free;
    char buf[];
};

#endif /* !_SIMPLE_DYNAMIC_STR_H_ */