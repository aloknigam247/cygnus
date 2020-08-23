#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

struct GenericList {
    struct GenericList *next;
};

#define FOREACH_GLIST(type, iter, incr) for(type iter; iter; incr)

struct GenericList* reverseGenericList(struct GenericList *head);

#endif
