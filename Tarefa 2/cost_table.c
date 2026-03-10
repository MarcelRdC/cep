#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cost_table.h"

COST_NODE* create_neighbor_node(COST_DATA new_neighbor_data){

    COST_NODE *new_node;
    new_node = malloc(sizeof(COST_NODE));
    new_node->data = new_neighbor_data;
    new_node->next = NULL;

    return new_node;
}

COST_NODE_LIST* create_cost_list_node(COST_DATA new_neighbor_data){

    COST_NODE_LIST *new_node;
    new_node = malloc(sizeof(COST_NODE_LIST));

    COST_NODE* first_neighbor = create_neighbor_node(new_neighbor_data);  //O primeiro e o último nó dessa lista são iguais por existir somente 1 nó após a criação.

    strcpy(new_node->name, first_neighbor->data.vertex_a);
    new_node->first_neighbor = first_neighbor;
    new_node->last_neighbor = first_neighbor;
    new_node->next = NULL;

    return new_node;
}

COST_NODE_LIST* insert_neighbor_of(COST_NODE_LIST *this_node, COST_DATA new_node){

    if(this_node==NULL)
        return create_cost_list_node(new_node);

    if(strcmp(this_node->name, new_node.vertex_a))                              //strcmp() retorna 0 se as strings forem iguais.
        this_node->next = insert_neighbor_of(this_node->next, new_node);
    else{
        COST_NODE *new_last_neighbor = create_neighbor_node(new_node);
        this_node->last_neighbor->next = new_last_neighbor;
        this_node->last_neighbor = new_last_neighbor;
    };

    return this_node;
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
        COST_DATA new_neighbor;

        if(strcmp(buffer_line, end_of_input)){

            token = strtok(buffer_line, ",");
            strcpy(new.vertex_a, token);
            strcpy(new_neighbor.vertex_b, token);

            token = strtok(NULL, ",");
            strcpy(new.vertex_b, token);
            strcpy(new_neighbor.vertex_a, token);

            token = strtok(NULL, "\n");
            new.cost = atof(token);
            new_neighbor.cost = new.cost;

            //Insere o nó na tabela.
            table = insert_neighbor_of(table, new);
            table = insert_neighbor_of(table, new_neighbor);

        }else{
            is_end_of_input=1;
        };
    };
    return table;
}