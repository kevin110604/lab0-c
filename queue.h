/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdbool.h>
#include <stddef.h> /* offsetof */

/************** Data structure declarations ****************/

/* Queue structure */
typedef struct list_node {
    struct list_node *head; /* Linked list of elements */
    struct list_node *tail;
} queue_t;


/* Linked list element (You shouldn't need to change this) */
typedef struct ELE {
    /* Pointer to array holding string.
       This array needs to be explicitly allocated and freed */
    char *value;
    queue_t list;
} list_ele_t;

#ifndef container_of
#ifdef __LIST_HAVE_TYPEOF
#define container_of(ptr, type, member)                            \
    __extension__({                                                \
        const __typeof__(((type *) 0)->member) *__pmember = (ptr); \
        (type *) ((char *) __pmember - offsetof(type, member));    \
    })
#else
#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) -offsetof(type, member)))
#endif
#endif


#define list_entry(node, type, member) container_of(node, type, member)

/************** Operations on queue ************************/

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new();

/*
  Free ALL storage used by queue.
  No effect if q is NULL
*/
void q_free(queue_t *q);

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s);

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s);

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize);

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q);

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q);
