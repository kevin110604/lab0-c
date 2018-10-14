/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL)
        return q;
    q->head = q;
    q->tail = q;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;

    queue_t *node;
    queue_t *next;
    queue_t *prev;
    list_ele_t *item;

    while (q->head != q) {
        node = q->head;
        item = list_entry(node, list_ele_t, list);
        free(item->value);

        next = node->head;
        prev = node->tail;
        next->tail = prev;
        prev->head = next;
        free(item);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /*
    list_ele_t *newh;
    if (q == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
     newh->value = malloc(strlen(s) + 1);
     if (newh->value == NULL) {
         free(newh);
         return false;
     }
     strcpy(newh->value, s);

     queue_t *next = q->head;
     queue_t *node = &newh->list;

     next->tail = node;
     node->head = next;
     node->tail = q;
     q->head = node;
     q->size++;
     */
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /*
    list_ele_t *newh;
    if (q == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    newh->value = malloc(strlen(s) + 1);
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    queue_t *prev = q->tail;
    queue_t *node = &newh->list;

    prev->head = node;
    node->head = q;
    node->tail = prev;
    q->tail = node;
    q->size++;
    */
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == q)
        return false;
    queue_t *node = q->head;
    list_ele_t *item = list_entry(node, list_ele_t, list);
    if (sp != NULL) {
        strncpy(sp, item->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    free(item->value);

    queue_t *next = node->head;
    queue_t *prev = node->tail;

    next->tail = prev;
    prev->head = next;
    free(item);
    q->size--;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || q->head == q)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->size <= 1)
        return;
    queue_t *cur, *pre, *old_tail, *tmp;
    old_tail = q->tail;
    pre = q;
    q->tail = q->head;
    for (cur = q->head; cur != old_tail; cur = tmp) {
        tmp = cur->head;
        cur->head = pre;
        cur->tail = old_tail;
        pre->tail = cur;
        pre = cur;
        old_tail->head = cur;
    }
    q->head = old_tail;
    old_tail->tail = q;
}
