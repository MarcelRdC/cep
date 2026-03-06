typedef struct cost_data{
    char self_name[35];
    char neighbor_name[35];
    double cost;
} COST_DATA;

typedef struct cost_node{
    COST_DATA data;
    struct cost_node *next;
} COST_NODE;

typedef struct cost_node_list{
    char name[35];
    struct cost_node *first_neighbor;
    struct cost_node *last_neighbor;
    struct cost_node_list *next;
} COST_NODE_LIST;


//Cria um novo nó em uma lista de custos.
//
COST_NODE* create_neighbor_node(COST_DATA new_neighbor_data);

// Cria um novo nó que aponta para uma nova lista de custos. O primeiro e o último nó dessa lista são iguais por existir somente 1 nó após a criação.
//
COST_NODE_LIST* create_cost_list_node(COST_DATA new_neighbor_data);

// Insere um nó de vizinho na lista apropriada. Caso a lista não exista, cria a lista com o primeiro vizinho e cria um nó que aponta para o
// primeiro (e último) da lista. Caso a lista exista, o novo vizinho é adicionado ao final da mesma.
//
COST_NODE_LIST* insert_neighbor_of(COST_NODE_LIST *this_node, COST_DATA new_node);

void free_list(COST_NODE *this_node);

void free_table(COST_NODE_LIST *this_node);

COST_NODE_LIST* make_cost_table(FILE *file);