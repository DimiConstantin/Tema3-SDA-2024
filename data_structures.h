#pragma once
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define USR_MAX 521
#define DIE(assertion, call_description)  \
    do {                                  \
        if (assertion) {                  \
            fprintf(stderr, "(%s, %d): ", \
                __FILE__, __LINE__);      \
            perror(call_description);     \
            exit(errno);                  \
        }                                 \
    } while (0)

typedef struct ll_node_t {
    void* data;
    struct ll_node_t* next;
} ll_node_t;

typedef struct linked_list_t {
    ll_node_t* head;
    unsigned int data_size;
    unsigned int size;
} linked_list_t;

typedef struct
{
    linked_list_t** neighbors; /* Listele de adiacenta ale grafului */
    int nodes; /* Numarul de noduri din graf. */
} list_graph_t;

typedef struct queue_t queue_t;
struct queue_t {
    /* Dimensiunea maxima a cozii */
    unsigned int max_size;
    /* Dimensiunea cozii */
    unsigned int size;
    /* Dimensiunea in octeti a tipului de date stocat in coada */
    unsigned int data_size;
    /* Indexul de la care se vor efectua operatiile de front si dequeue */
    unsigned int read_idx;
    /* Indexul de la care se vor efectua operatiile de enqueue */
    unsigned int write_idx;
    /* Bufferul ce stocheaza elementele cozii */
    void** buff;
};

typedef struct post_t {
    int id, uid, nrlike;
    char* title;
    linked_list_t* likes;
    list_graph_t* tree;
    int father;
} post_t;

linked_list_t* ll_create(unsigned int data_size);
ll_node_t* get_nth_node(linked_list_t* list, unsigned int n);
void ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data);
ll_node_t* ll_remove_nth_node(linked_list_t* list, unsigned int n);
unsigned int ll_get_size(linked_list_t* list);
void ll_free(linked_list_t** pp_list);
void ll_print_int(linked_list_t* list);

list_graph_t* lg_create(int nodes);
int is_node_in_graph(int n, int nodes);
void lg_add_edge(list_graph_t* graph, int src, int dest);
int lg_has_edge(list_graph_t* graph, int src, int dest);
void lg_remove_edge(list_graph_t* graph, int src, int dest);
void lg_free(list_graph_t* graph);
void lg_print_graph(list_graph_t* graph);

queue_t* q_create(unsigned int data_size, unsigned int max_size);
unsigned int q_get_size(queue_t* q);
unsigned int q_is_empty(queue_t* q);
void* q_front(queue_t* q);
int q_dequeue(queue_t* q);
int q_enqueue(queue_t* q, void* new_data);
void q_clear(queue_t* q);
void q_free(queue_t* q);
int* bfs_list_graph(list_graph_t* lg, int node);
