#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct city{
    char nome[30];
    int cep_min;
    int cep_max;
} CITY;

typedef struct city_node{
    CITY data;
    struct city_node *left;
    struct city_node *right;
    struct city_node *middle;
} CITY_NODE;

typedef struct cost_data{
    char self_name[30];
    char neighbor_name[30];
    double cost;
} COST_DATA;

typedef struct cost_node{
    COST_DATA data;
    struct cost_node *next;
} COST_NODE;

typedef struct cost_node_list{
    char name[30];
    struct cost_node *first_neighbor;
    struct cost_node *last_neighbor;
    struct cost_node_list *next;
} COST_NODE_LIST;

//Cria um novo nó em uma lista de custos.
//
COST_NODE* create_neighbor_node(COST_DATA new_neighbor_data){

    COST_NODE *new_node;
    new_node = malloc(sizeof(COST_NODE));
    new_node->data = new_neighbor_data;
    new_node->next = NULL;

    printf("\nInserindo o vizinho %s de %s de custo %f.", new_neighbor_data.neighbor_name, new_neighbor_data.self_name, new_neighbor_data.cost);

    return new_node;
}

// Cria um novo nó que aponta para uma nova lista de custos. O primeiro e o último nó dessa lista são iguais por existir somente 1 nó após a criação.
//
COST_NODE_LIST* create_cost_list_node(COST_DATA new_neighbor_data){

    COST_NODE_LIST *new_node;
    new_node = malloc(sizeof(COST_NODE_LIST));

    COST_NODE* first_neighbor = create_neighbor_node(new_neighbor_data);

    strcpy(new_node->name, first_neighbor->data.self_name);
    new_node->first_neighbor = first_neighbor;
    new_node->last_neighbor = first_neighbor;
    new_node->next = NULL;

    printf("\nInserindo a lista de vizinhos de %s.\n", new_node->name);

    return new_node;
}

// Insere um nó de vizinho na lista apropriada. Caso a lista não exista, cria a lista com o primeiro vizinho e cria um nó que aponta para o
// primeiro (e último) da lista. Caso a lista exista, o novo vizinho é adicionado ao final da mesma.
//
COST_NODE_LIST* insert_neighbor_of(COST_NODE_LIST *this_node, COST_DATA new_node){

    if(this_node==NULL)
        return create_cost_list_node(new_node);

    if(strcmp(this_node->name, new_node.self_name))                              //strcmp() retorna 0 se as strings forem iguais.
        this_node->next = insert_neighbor_of(this_node->next, new_node);
    else{
        COST_NODE *new_last_neighbor = create_neighbor_node(new_node);
        this_node->last_neighbor->next = new_last_neighbor;
        this_node->last_neighbor = new_last_neighbor;
    };

    return this_node;
}

//Cria um novo nó (com alocação na memória) e retorna seu endereço.
//
CITY_NODE *create_node(CITY new_node_data, CITY_NODE *left, CITY_NODE *right, CITY_NODE *middle){

    CITY_NODE *new_node;

    new_node = malloc(sizeof(CITY_NODE));
    new_node->data = new_node_data;
    new_node->left = left;
    new_node->right = right;
    new_node->middle = middle;

    return new_node;
}

//Cria e insere um novo no acima de outro, fazendo a transferencia de filhos caso necessaria.
//Retorna o endereço para o nó criado.
//
// CITY_NODE *this_node: nó de referencia.
// CITY    new_node_data: campo data a ser usado na criacao do novo nó.
//
CITY_NODE* insert_new_in_between(CITY_NODE *this_node, CITY new_node_data){
    
    CITY_NODE *new_node_left = NULL;
    CITY_NODE *new_node_right = NULL;

    if(this_node->left!=NULL && this_node->left->data.cep_max < new_node_data.cep_min){
        new_node_left = this_node->left;
        this_node->left = NULL;
    };
    if(this_node->right!=NULL && this_node->right->data.cep_min > new_node_data.cep_max){
        new_node_right = this_node->right;
        this_node->right = NULL;
    };

    return create_node(new_node_data, new_node_left, new_node_right, this_node);
}

//Dado o ponteiro para uma árvore e um campo data de um nó, insere o nó na árvore
//na posição adequada.
//
// CITY_NODE *this_node = endereço do nó de referência (ou raíz da árvore).
// CITY   new_node_data = campo data usado para criar o novo nó.
//
CITY_NODE* insert_node(CITY_NODE *this_node, CITY new_node_data){
    
    if(this_node==NULL){                                                                          // A faixa de CEP da nova cidade corresponde a esse no folha.
        this_node = create_node(new_node_data, NULL, NULL, NULL);
    }else if(this_node->data.cep_max <= new_node_data.cep_max && this_node->data.cep_min >= new_node_data.cep_min){  //Se o nó a ser inserido possui uma faixa mais abrangente que o nó atual, inverte a posição dos nós.
            this_node = insert_new_in_between(this_node, new_node_data); //create_node(new_node_data, this_node->left, this_node->right, this_node);
    }else if(this_node->data.cep_max > new_node_data.cep_max && this_node->data.cep_min < new_node_data.cep_min){
            this_node->middle = insert_node(this_node->middle, new_node_data);  
    }else if(this_node->data.cep_min > new_node_data.cep_max){                                    // A faixa de CEP da nova cidade é menor que a deste no.
            this_node->left = insert_node(this_node->left, new_node_data);
    }else if(this_node->data.cep_max < new_node_data.cep_min){                                          // A faixa de CEP da nova cidade é maior que a deste no.
            this_node->right = insert_node(this_node->right, new_node_data);
    }else printf("Internal Error.");
    

    return this_node;
}

//Dado o ponteiro para uma árvore e um int referente a um CEP, retorna o campo data
// de um nó contendo o nome do nó da árvore com o intervalo de CEP mais restrito ao
// qual o CEP da entrada pertence, com todos os outros campos valendo NULL.
//
// CITY_NODE *this_node: endereço do nó de referência (ou raíz da árvore).
// int       target_cep: CEP usado na busca.
//
CITY get_city_from_cep(CITY_NODE* this_node, int target_cep){
    
    CITY output;

    if(this_node==NULL){
        output.nome[0] = '\0';
        output.cep_min = -1;
        output.cep_max = -1;
    }else if(target_cep < this_node->data.cep_min){
            output = get_city_from_cep(this_node->left, target_cep);       //Esta em uma faixa a esquerda?
    }else if(target_cep > this_node->data.cep_max){
            output = get_city_from_cep(this_node->right, target_cep);  //Esta em uma a faixa direita?
    }else{
            output = get_city_from_cep(this_node->middle, target_cep); //Esta em uma subfaixa?
            if(output.cep_min==-1)
                output = this_node->data;
    };
                        //Retorna a cidade da subfaixa a qual o CEP pertence.

    return output;
} 

//Dado o ponteiro para uma árvore, desaloca da memória todos os nós da árvore.
//
// CITY_NODE *this_node: nó de referência (ou raíz da árvore).
//
void free_tree(CITY_NODE *this_node){

    if(this_node->left!=NULL)
        free_tree(this_node->left);
    if(this_node->right!=NULL)
        free_tree(this_node->right);
    if(this_node->middle!=NULL)
        free_tree(this_node->middle);

    free(this_node);
    
    return;
}

void free_list(COST_NODE *this_node){

    if(this_node->next!=NULL)
        free_list(this_node->next);

    free(this_node);

    return;
}

void free_table(COST_NODE_LIST *this_node){
    
    if(this_node->first_neighbor!=NULL)
        free_list(this_node->first_neighbor);
    if(this_node->next!=NULL)
        free_table(this_node->next);

    free(this_node);

    return;
}

COST_NODE_LIST* make_cost_table(FILE *file){

    COST_NODE_LIST *table=NULL;

    //Verifica se todas as cidades foram lidas.
    char end_of_input[4] = {'-', '-', '\n'};
    int is_end_of_input=0;

    while(!feof(file)&&is_end_of_input==0){
        
        //Cria o ponteiro para o strtok() e o buffer para o fgets().
        char *token;
        char buffer_line[100]={'\0'};

        //Leitura do arquivo e atribuição dos atributos;
        fgets(buffer_line, 255, file);

        //Cria um novo nó para a árvore com dados provenientes da entrada.
        COST_DATA new;

        if(strcmp(buffer_line, end_of_input)){

            token = strtok(buffer_line, ",");
            strcpy(new.self_name, token);

            token = strtok(NULL, ",");
            strcpy(new.neighbor_name, token);

            token = strtok(NULL, "\n");
            printf("\ntoken: %s .", token);
            new.cost = atof(token);
            printf("\natof: %f .\n", new.cost);
            //Insere o nó na tabela.
            table = insert_neighbor_of(table, new);

        }else{
            is_end_of_input=1;

            //fgets(buffer_line, 255, file);
            //token = strtok(buffer_line, "\n");
            //int target_cep = atoi(token);      <------ Mudança de responsabilidade

            //printf("\nO CEP (%d) pertence a cidade %s.\n\n", target_cep, get_city_from_cep(tree, target_cep).nome);
        };
    };
    return table;
}

//Cria uma árvore com as cidades da entrada, ordenando pelo intervalo de CEP,
// e retorna o ponteiro da raíz da árvore.
//
// FILE      *file: ponteiro da leitura do arquivo de entrada.
// CITY_NODE *tree: ponteiro da raíz da árvore (por padrão deve ser NULL).
//
CITY_NODE* make_city_tree(FILE *file){
    
    CITY_NODE *tree=NULL;
    //Verifica se todas as cidades foram lidas.
    char end_of_input[4] = {'-', '-', '\n'};
    int is_end_of_input=0;

    while(!feof(file)&&is_end_of_input==0){
        
        //Cria o ponteiro para o strtok() e o buffer para o fgets().
        char *token;
        char buffer_line[100]={'\0'};

        //Leitura do arquivo e atribuição dos atributos;
        fgets(buffer_line, 255, file);

        //Cria um novo nó para a árvore com dados provenientes da entrada.
        CITY new;

        if(strcmp(buffer_line, end_of_input)){

            token = strtok(buffer_line, ",");
            strcpy(new.nome, token);

            token = strtok(NULL, ",");
            new.cep_min = atoi(token);

            token = strtok(NULL, "\n");
            new.cep_max = atoi(token);

            //Insere o nó na árvore.
            tree = insert_node(tree, new);

        }else{
            is_end_of_input=1;

            //fgets(buffer_line, 255, file);
            //token = strtok(buffer_line, "\n");
            //int target_cep = atoi(token);      <------ Mudança de responsabilidade

            //printf("\nO CEP (%d) pertence a cidade %s.\n\n", target_cep, get_city_from_cep(tree, target_cep).nome);
        };
    };
    return tree;
}

// DEBUG //
// Conta a quantidade de cidades na árvore e retorna em valor inteiro. 
//
int count_city_nodes(CITY_NODE *this_node){

    if(this_node==NULL)
        return 0;

    int sum_of_nodes=1;

    sum_of_nodes = sum_of_nodes + count_city_nodes(this_node->left);

    sum_of_nodes = sum_of_nodes + count_city_nodes(this_node->right);

    sum_of_nodes = sum_of_nodes + count_city_nodes(this_node->middle);
    
    return sum_of_nodes;
}

//float get_cost_from_table(TABLE_NODE *table, CITY city_1, CITY city_2){};

int main(int argc, char *argv[]){

    //Abre o arquivo de entrada.
    FILE *file = fopen(argv[1], "r");
    if(!file){
        printf("\nErro na leitura do arquivo.\n");
        return 1;
    };
    
    CITY_NODE *tree=NULL;
    COST_NODE_LIST *table=NULL;

    tree = make_city_tree(file);
    //count_city_nodes(tree);
    table = make_cost_table(file);
    
    //Leitura das cidades alvo.
    //something = something(file);

    //Leitura 
    //CITY city_1 = get_city_from_cep();
    //CITY city_2 = get_city_from_cep();
    //get_cost_from_table(table, city_1, city_2);

    //Bloco de liberação de memória.
    fclose(file);
    free_tree(tree);
    free_table(table);
    printf("\n PERFEITO!\n");

    return 0;
}