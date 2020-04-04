#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 
 * Generic Node for a Linked List
 */
typedef struct node
{
    void *data;
    struct node *link;
} node;

/**
 * Makes a node
 * key -> Element of any type to be inserted
 * size -> Sizeof the element getting inserted
 */
node *create_node(void *key, int size)
{
    node *temp;
    temp = (node *)calloc(1, sizeof(node));
    if (temp == NULL)
    {
        printf("[OUT_OF_MEM] Memory Error\n");
        exit(0);
    }
    void *data_at = calloc(1, size);
    memcpy(data_at, key, size);

    temp->data = data_at;
    temp->link = NULL;
    return temp;
}

/**
 * Frees a complete list
 * head -> Start to the List
 */
void free_list(node *head)
{
    node *p = head, *q;
    while (p != NULL)
    {
        q = p->link;
        free(p->data);
        free(p);
        p = q;
    }
}

/**
 * Displays a complete list based on a printer function
 * head -> Start to the List
 * printer -> Function for displaying individual void * elements inside the list
 */
void display_list(node *head, void (*printer)(void *))
{
    if (head == NULL)
        printf("[ ");
    else
        printf("[");
    while (head != NULL)
    {
        (*printer)(head->data);
        head = head->link;
        printf(" ,");
    }
    printf("\b]\n");
}

/**
 * Displays a complete list with memory based on a printer function
 * head -> Start to the List
 * printer -> Function for displaying individual void * elements inside the list
 */
void display_list_with_mem(node *head, void (*printer)(void *))
{
    if (head == NULL)
        printf("[ ");
    else
        printf("[");
    while (head != NULL)
    {
        printf(" <%u> -> ", head);
        (*printer)(head->data);
        printf(" ,");
        head = head->link;
    }
    printf("\b]\n");
}

/**
 * Inserts an element at the beginning of the list
 * head -> Start to the List
 * key -> Element to be inserted
 * size -> Sizeof the key element
 */
node *insert_first(node *head, void *key, int size)
{
    node *temp;
    temp = create_node(key, size);
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        temp->link = head;
        head = temp;
    }
    return head;
}

/**
 * Inserts an element at the ending of the list
 * head -> Start to the List
 * key -> Element to be inserted
 * size -> Sizeof the key element
 */
node *insert_last(node *head, void *key, int size)
{
    node *temp, *p = head;
    temp = create_node(key, size);
    if (head == NULL)
    {
        head = temp;
        return head;
    }
    else
    {
        while ((head->link) != NULL)
        {
            head = head->link;
        }
        head->link = temp;
    }
    return p;
}

/**
 * Inserts an element before something in the list
 * head -> Start to the List
 * data -> Function that returns 1 if this is the element to insert before, else 0
 * key -> Element to be inserted
 * size -> Sizeof the key element
 */
node *insert_before(node *head, int (*data)(void *), void *key, int size)
{
    node *temp, *p;
    if (head == NULL)
    {
        printf("[!] Empty List.\n");
        return head;
    }
    p = head;
    while (p->link != NULL)
    {
        if ((*data)((p->link)->data))
            break;
        p = p->link;
    }
    if (p->link == NULL)
        printf("[X] Data Not Found.\n");
    else
    {
        temp = create_node(key, size);
        temp->link = p->link;
        p->link = temp;
    }
    return head;
}

/**
 * Inserts an element before something in the list
 * head -> Start to the List
 * data -> Function that returns 1 if this is the element to insert before, else 0
 * key -> Element to be inserted
 * size -> Sizeof the key element
 */
node *insert_after(node *head, int (*data)(void *), void *key, int size)
{
    node *temp, *p;
    if (head == NULL)
    {
        printf("[!] Empty List. \n");
        return head;
    }
    p = head;
    while (p != NULL)
    {
        if ((*data)((p->link)->data))
            break;
        p = p->link;
    }
    if (p == NULL)
    {
        printf("[X] Data Not Found.\n");
    }
    else
    {
        temp = create_node(key, size);
        temp->link = p->link;
        p->link = temp;
    }
    return head;
}

/**
 * Deletes the first element in a list
 * head -> Start to the List
 */
node *delete_first(node *head)
{
    if (head == NULL)
    {
        printf("[LLIST_UFLOW] Linked List was Underflow!\n");
        return head;
    }
    node *temp = head;
    head = head->link;
    free(temp->data);
    free(temp);
    return head;
}

/**
 * Deletes the last element in the list
 * head -> Start to the List
 */
node *delete_last(node *head)
{
    if (head == NULL)
    {
        printf("[LLIST_UFLOW] Linked List was Underflow!\n");
        return head;
    }
    // If one element
    if (head->link == NULL)
    {
        free(head->data);
        free(head);
        return NULL;
    }
    node *temp = head, *p = head;
    head = head->link;
    while (head->link != NULL)
    {
        temp = head;
        head = head->link;
    }
    temp->link = NULL;
    free(head->data);
    free(head);
    return p;
}

/**
 * Deletes any element from the list
 * head -> Head Pointer of the List
 * key -> Function that returns 1 or 0 based on if the element is to be deleted
 * */
node *delete_any(node *head, int (*key)(void *))
{
    node *p, *q;
    if (head == NULL)
    {
        printf("[!] Empty List. \n");
        return head;
    }
    if ((*key)(head->data))
    {
        p = head;
        head = head->link;
        free(p->data);
        free(p);
    }
    else
    {
        p = head;
        while (p != NULL && !(*key)(p->data))
        {
            q = p;
            p = p->link;
        }
        if (p == NULL)
            printf("[X] Key Not Found.\n");
        else
        {
            q->link = p->link;
            free(q->data);
            free(p);
        }
    }
    return head;
}

/**
 * Inserts an element in the list in a sorted manner
 * head -> Start to the List
 * elem -> Element to be inserted
 * size -> Sizeof the elem element
 * key -> Function that returns an integer to compare between two elements
 */
node *insert_elem_sorted(node *head, void *elem, int size, int (*key)(void *))
{
    node *p, *q, *temp = create_node(elem, size);
    if (head == NULL)
    {
        head = temp;
        return head;
    }
    if ((*key)(head->data) >= (*key)(elem))
    {
        temp->link = head;
        head = temp;
    }
    else
    {
        p = head;
        while (p != NULL && (*key)(p->data) <= (*key)(elem))
        {
            q = p;
            p = p->link;
        }
        q->link = temp;
        temp->link = p;
    }
    return head;
}

/**
 * Reverses the linked list
 * head -> Start to the List
 */
node *reverse(node *head)
{
    node *prev = NULL, *curr = head, *next = NULL;

    while (curr != NULL)
    {
        next = curr->link;
        curr->link = prev;

        prev = curr;
        curr = next;
    }

    return head;
}

/**
 * Sorts the entire linked list
 * head -> Start to the List
 * key -> Function that returns an integer to compare between two elements
 */
node *sort(node *head, int (*key)(void *))
{

    // empty or only one element is already sorted
    if (head == NULL || head->link == NULL)
    {
        return head;
    }

    node *i = head, *j, *min;
    while (i->link != NULL)
    { // will run till second last element
        min = i;
        j = i->link;
        while (j != NULL)
        {
            if ((*key)(min->data) > (*key)(j->data))
            {
                min = j;
            }
            // updation
            j = j->link;
        }
        if (min != i)
        {
            // interchange min and i
            void *temp = min->data;
            min->data = i->data;
            i->data = temp;
        }

        // updation
        i = i->link;
    }

    return head;
}
