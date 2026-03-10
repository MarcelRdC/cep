#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city_tree.h"
#include "cost_table.h"
#include "dijkstra.h"

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
    table = make_cost_table(file);
    
    //Leitura das cidades alvo.
    char *token;
    char buffer_line[100]={'\0'};
    fgets(buffer_line, 255, file);

    token = strtok(buffer_line, ",");
    int target_cep1 = atoi(token);

    token = strtok(NULL, "\n");
    int target_cep2 = atoi(token);

    //Busca pelas cidades alvo na árvore.
    COST_DATA city_1 = {0};
    strcpy(city_1.vertex_a, get_city_from_cep(tree, target_cep1).nome);
    strcpy(city_1.vertex_b, city_1.vertex_a);

    COST_DATA city_2 = {0};
    strcpy(city_2.vertex_a, get_city_from_cep(tree, target_cep2).nome);

    printf("\nO CEP (%d) pertence a cidade %s.\n", target_cep1, city_1.vertex_a);
    printf("\nO CEP (%d) pertence a cidade %s.\n", target_cep2, city_2.vertex_a);

    dijkstra(city_1, city_2, table);

    //Bloco de liberação de memória.
    fclose(file);
    free_tree(tree);
    free_table(table);

    return 0;
}