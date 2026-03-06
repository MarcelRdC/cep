#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city_tree.h"
#include "cost_table.h"

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
    char *token;
    char buffer_line[100]={'\0'};
    fgets(buffer_line, 255, file);

    token = strtok(buffer_line, ",");
    int target_cep1 = atoi(token);

    token = strtok(NULL, "\n");
    int target_cep2 = atoi(token);

    CITY city_1 = get_city_from_cep(tree, target_cep1);
    CITY city_2 = get_city_from_cep(tree, target_cep2);
    printf("\nO CEP (%d) pertence a cidade %s.", target_cep1, city_1.nome);
    printf("\nO CEP (%d) pertence a cidade %s.\n\n", target_cep2, city_2.nome);
    //get_cost_from_table(table, city_1, city_2);

    //Bloco de liberação de memória.
    fclose(file);
    free_tree(tree);
    free_table(table);

    return 0;
}