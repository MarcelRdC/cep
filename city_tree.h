typedef struct city{
    char nome[35];
    int cep_min;
    int cep_max;
} CITY;

typedef struct city_node{
    CITY data;
    struct city_node *left;
    struct city_node *right;
    struct city_node *middle;
} CITY_NODE;

//Cria um novo nó (com alocação na memória) e retorna seu endereço.
//
CITY_NODE *create_node(CITY new_node_data, CITY_NODE *left, CITY_NODE *right, CITY_NODE *middle);

//Cria e insere um novo no acima de outro, fazendo a transferencia de filhos caso necessaria.
//Retorna o endereço para o nó criado.
//
// CITY_NODE *this_node: nó de referencia.
// CITY    new_node_data: campo data a ser usado na criacao do novo nó.
//
CITY_NODE* insert_new_in_between(CITY_NODE *this_node, CITY new_node_data);

//Dado o ponteiro para uma árvore e um campo data de um nó, insere o nó na árvore
//na posição adequada.
//
// CITY_NODE *this_node = endereço do nó de referência (ou raíz da árvore).
// CITY   new_node_data = campo data usado para criar o novo nó.
//
CITY_NODE* insert_node(CITY_NODE *this_node, CITY new_node_data);

//Dado o ponteiro para uma árvore e um int referente a um CEP, retorna o campo data
// de um nó contendo o nome do nó da árvore com o intervalo de CEP mais restrito ao
// qual o CEP da entrada pertence, com todos os outros campos valendo NULL.
//
// CITY_NODE *this_node: endereço do nó de referência (ou raíz da árvore).
// int       target_cep: CEP usado na busca.
//
CITY get_city_from_cep(CITY_NODE* this_node, int target_cep);

//Dado o ponteiro para uma árvore, desaloca da memória todos os nós da árvore.
//
// CITY_NODE *this_node: nó de referência (ou raíz da árvore).
//
void free_tree(CITY_NODE *this_node);

// DEBUG //
// Conta a quantidade de cidades na árvore e retorna em valor inteiro. 
int count_city_nodes(CITY_NODE *this_node);

//Cria uma árvore com as cidades da entrada, ordenando pelo intervalo de CEP,
// e retorna o ponteiro da raíz da árvore.
//
// FILE      *file: ponteiro da leitura do arquivo de entrada.
// CITY_NODE *tree: ponteiro da raíz da árvore (por padrão deve ser NULL).
//
CITY_NODE* make_city_tree(FILE *file);