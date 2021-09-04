#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    int key;
    struct tree* left;
    struct tree* right;
} tree_t;

typedef struct node_of_list
{
    tree_t* p_tr;
    struct node_of_list* next;
} node_t;

typedef struct
{
    int size;
    node_t* head;
    node_t* tail;
} queue_t;

tree_t* input_data(tree_t*);
tree_t* tree_insert(tree_t**, int);
void bfs_level_tree(tree_t*);
void tree_clear(tree_t*);
void queue_initialization(queue_t*);
void queue_push(queue_t*, tree_t*);
void queue_pop(queue_t*);
tree_t* queue_front(queue_t*);
int queue_empty(queue_t*);

int main()
{
    tree_t* tr = NULL;
    tr = input_data(tr);
    bfs_level_tree(tr);
    tree_clear(tr);
    printf("\n\n\n\n");
    system("pause");
    return 0;
}

tree_t* input_data(tree_t* root)
{
    int temp, count;
    printf(" input count of tree's nodes : ");
    scanf_s("%d", &count);
    printf(" input nodes: \n");
    for (int i = 0; i < count; i++)
    {
        scanf_s("%d", &temp);
        tree_insert(&root, temp);
    }
    printf("\n");
    return root;
}

void bfs_level_tree(tree_t* root)
{
    if (root == NULL)
    {
        return;
    }
    tree_t* temp = root;
    queue_t q;
    int input_lvl, current_lvl = 1;
    queue_initialization(&q);
    queue_push(&q, temp);
    printf(" input level from which you want to print nodes : ");
    scanf_s("%d", &input_lvl);
    printf("\n\n");
    while (!queue_empty(&q))
    {
        int size = q.size;
        while (size--)
        {
            temp = (tree_t*)queue_front(&q);
            queue_pop(&q);

            if (input_lvl == current_lvl)
            {
                printf(" %d ", temp->key);
            }

            if (temp->left != NULL)
            {
                queue_push(&q, temp->left);
            }

            if (temp->right != NULL)
            {
                queue_push(&q, temp->right);
            }
        }
        current_lvl++;
    }
    return;
}

tree_t* tree_insert(tree_t** tr, int key)
{
    tree_t* p = *tr;
    while (p != NULL)
    {
        if (key == p->key)
        {
            return p;
        }
        else if (key < p->key)
        {
            tr = &p->left;
            p = p->left;
        }
        else
        {
            tr = &p->right;
            p = p->right;
        }
    }

    p = (tree_t*)malloc(sizeof(tree_t));
    if (p != NULL)
    {
        p->key = key;
        p->left = p->right = NULL;
        *tr = p;
    }
    return p;
}

void tree_clear(tree_t* tr)
{
    if (tr != NULL)
    {
        if (tr->left != NULL)
        {
            tree_clear(tr->left);
        }
        if (tr->right != NULL)
        {
            tree_clear(tr->right);
        }
        free(tr);
    }
    return;
}

void queue_initialization(queue_t* q)
{
    q->head = q->tail = NULL;
    q->size = 0;
    return;
}

int queue_empty(queue_t* q)
{
    return (q->head == NULL);
}

tree_t* queue_front(queue_t* q)
{
    if (q->head != NULL)
    {
        return q->head->p_tr;
    }
}

void queue_push(queue_t* q, tree_t* p_tr)
{
    node_t* p = (node_t*)malloc(sizeof(node_t));
    if (p != NULL)
    {
        p->p_tr = p_tr;
        p->next = NULL;
        if (q->head == NULL)
        {
            q->head = q->tail = p;
            q->size = 1;
        }
        else
        {
            q->tail->next = p;
            q->tail = p;
            q->size++;
        }
    }
    return;
}

void queue_pop(queue_t* q)
{
    node_t* t;
    if (q->head != NULL)
    {
        t = q->head;
        q->head = q->head->next;
        free(t);
        if (q->head == NULL)
        {
            q->tail = NULL;
        }
        q->size--;
    }
    return;
}