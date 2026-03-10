#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city_tree.h"

CITY_NODE *create_node(CITY new_node_data, CITY_NODE *left, CITY_NODE *right, CITY_NODE *middle){

    CITY_NODE *new_node;

    new_node = malloc(sizeof(CITY_NODE));
    new_node->data = new_node_data;
    new_node->left = left;
    new_node->right = right;
    new_node->middle = middle;

    return new_node;
}

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

CITY_NODE* insert_node(CITY_NODE *this_node, CITY new_node_data){
    
    if(this_node==NULL){                                                                          // A faixa de CEP da nova cidade corresponde a esse no folha.
        this_node = create_node(new_node_data, NULL, NULL, NULL);
    }else if(this_node->data.cep_max <= new_node_data.cep_max && this_node->data.cep_min >= new_node_data.cep_min){  //Se o nó a ser inserido possui uma faixa mais abrangente que o nó atual, inverte a posição dos nós.
            this_node = insert_new_in_between(this_node, new_node_data); //create_node(new_node_data, this_node->left, this_node->right, this_node);
    }else if(this_node->data.cep_max > new_node_data.cep_max && this_node->data.cep_min < new_node_data.cep_min){
            this_node->middle = insert_node(this_node->middle, new_node_data);  
    }else if(this_node->data.cep_min > new_node_data.cep_max){                                    // A faixa de CEP da nova cidade é menor que a deste no.
            this_node->left = insert_node(this_node->left, new_node_data);
    }else if(this_node->data.cep_max < new_node_data.cep_min){                                    // A faixa de CEP da nova cidade é maior que a deste no.
            this_node->right = insert_node(this_node->right, new_node_data);
    }else printf("Internal Error.");
    

    return this_node;
}

CITY get_city_from_cep(CITY_NODE* this_node, int target_cep){
    
    CITY output;

    if(this_node==NULL){
        output.nome[0] = '\0';
        output.cep_min = -1;
        output.cep_max = -1;
    }else if(target_cep < this_node->data.cep_min){
            output = get_city_from_cep(this_node->left, target_cep);   //Esta em uma faixa a esquerda?
    }else if(target_cep > this_node->data.cep_max){
            output = get_city_from_cep(this_node->right, target_cep);  //Esta em uma a faixa direita?
    }else{
            output = get_city_from_cep(this_node->middle, target_cep); //Esta em uma subfaixa?
            if(output.cep_min==-1)
                output = this_node->data;                              //Retorna a cidade da subfaixa a qual o CEP pertence.
    };

    return output;
}

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

int count_city_nodes(CITY_NODE *this_node){

    if(this_node==NULL)
        return 0;

    int sum_of_nodes=1;

    sum_of_nodes = sum_of_nodes + count_city_nodes(this_node->left);

    sum_of_nodes = sum_of_nodes + count_city_nodes(this_node->right);

    sum_of_nodes = sum_of_nodes + count_city_nodes(this_node->middle);
    
    return sum_of_nodes;
}

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
        };
    };
    return tree;
}