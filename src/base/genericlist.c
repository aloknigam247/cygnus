#include "genericlist.h"
#include <stddef.h>

struct GenericList *reverseGenericList(struct GenericList *curr) {
    if (!curr)
        return NULL;

    struct GenericList *prev = NULL, *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}
