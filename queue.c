#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head =
        (struct list_head *) malloc(sizeof(struct list_head));
    if (!head)
        return NULL;
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;

    element_t *current, *safe = NULL;
    list_for_each_entry_safe (current, safe, l, list) {
        if (current->value)
            free(current->value);
        free(current);
    }

    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new_node_element = (element_t *) malloc(sizeof(element_t));
    if (!new_node_element)
        return false;

    new_node_element->value = malloc(strlen(s) + 1);
    strncpy(new_node_element->value, s, strlen(s) + 1);
    if (!new_node_element->value) {
        free(new_node_element);
        return false;
    }

    list_add(&new_node_element->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new_node_tail = (element_t *) malloc(sizeof(element_t));
    if (!new_node_tail) {
        return false;
    }
    new_node_tail->value = malloc(strlen(s) + 1);
    if (!new_node_tail->value) {
        free(new_node_tail);
        return false;
    }

    strncpy(new_node_tail->value, s, strlen(s) + 1);


    list_add_tail(&new_node_tail->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *temp = list_first_entry(head, element_t, list);

    if (sp && temp) {
        strncpy(sp, temp->value, bufsize);
        sp[bufsize - 1] = '\0';
    }

    list_del(&temp->list);
    return temp;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *temp = list_last_entry(head, element_t, list);
    if (temp && sp) {
        strncpy(sp, temp->value, bufsize);
        sp[bufsize - 1] = '\0';
    }

    list_del(&temp->list);
    return temp;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;
    int len = 0;
    struct list_head *count;
    list_for_each (count, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/

    if (!head || list_empty(head))
        return false;  // if queue is empty or NULL

    struct list_head *slow = head->next, *fast = head->next->next;
    // check queue until the very last entry
    // using Tortoise and Hare algo
    while (fast != head && fast->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    element_t *middle_node = list_entry(slow, element_t, list);
    list_del(slow);
    free(middle_node->value);
    free(middle_node);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (!head || list_empty(head))
        return false;


    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    if (!head || list_empty(head))
        return;
    for (struct list_head *tmp = head->next; tmp->next != head && tmp != head;
         tmp = tmp->next) {
        list_move(tmp, tmp->next);
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;

    struct list_head *current = head;
    struct list_head *prev = NULL;
    struct list_head *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
    if (!head || list_empty(head) || k == 1)
        return;

    int len = q_size(head);
    int swaps = len / k;
    if (swaps == 0)
        return;

    struct list_head *current = NULL, *tmp_head = head;
    int count = 0;
    while (swaps--) {
        for (current = tmp_head->next; ++count < k;) {
            list_move(current->next, tmp_head);
        }
        tmp_head = current;
        count = 0;
    }
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
