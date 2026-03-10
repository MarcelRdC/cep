/* Implementação do Algoritmo de Dijkstra (busca de caminho de custo mínimo de A a B).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cost_table.h"
#include "dijkstra.h"
#include <unistd.h>

//dijkstra |-> choose_candidate -> update_candidate_list -> update_candidates -> create_candidate
//         | add_to_visited_list
//         | remove_from_candidate

//Adiciona um candidato (aresta/vertex_b) à lista de candidatos.
CANDIDATE_NODE* create_candidate(COST_DATA data, CANDIDATE_NODE *best_candidate, CANDIDATE_NODE *next){

    CANDIDATE_NODE *new_candidate;
    new_candidate = malloc(sizeof(CANDIDATE_NODE));
    new_candidate->data = data;
    new_candidate->previous_in_path = best_candidate;
    new_candidate->cum_cost = best_candidate->cum_cost + data.cost; //Inicializa cum_cost considerando a soma do previous (melhor candidato escolhido) com o custo da nova aresta.
    new_candidate->next = next;

    return new_candidate;
}

//Verifica se um candidato (aresta/vertex_b) já foi visitado.
int is_visited(CANDIDATE_NODE *this_node, COST_DATA this_candidate){

    int output=0;

    while(this_node!=NULL)
        if(!strcmp(this_node->data.vertex_b, this_candidate.vertex_b)){
            output =1;
            break;
        }else
            this_node = this_node->next;

    return output;
}

//Busca candidato atual (vertex_b) da lista de vizinhos na lista de candidatos para atualizar. Caso o candidato não exista, cria um novo nó de candidato (aresta/vertex_b). 
CANDIDATE_NODE* update_candidates(CANDIDATE_NODE *candidate_list, CANDIDATE_NODE *best_candidate, COST_DATA new_candidate_data, CANDIDATE_NODE *visited_list){


    CANDIDATE_NODE *this_node;
    CANDIDATE_NODE *new_candidate = NULL;

    this_node = candidate_list;    
   
    //Percorre a lista de candidatos
    while(this_node!=NULL){

        if(strcmp(this_node->data.vertex_b, new_candidate_data.vertex_b)){ //Enquanto não achar, continua percorrendo.
            this_node = this_node->next;
        }else{

            if(this_node->data.cost > new_candidate_data.cost){ //Se achar, e se o custo anterior for superior ao da nova aresta encontrada...
                this_node->data = new_candidate_data;           //...substitui pelos dados da nova melhor aresta...
                this_node->previous_in_path = best_candidate;   //...e marca como previous o melhor nó selecionado (outro lado dessa aresta).
            }
            return candidate_list;
        };  
    };
    //Se o candidato (aresta) não existe ainda, cria o candidato e adiciona ele no começo da lista.
    new_candidate = create_candidate(new_candidate_data, best_candidate, candidate_list);

    return new_candidate;
}

//Busca na table a lista de vizinhos do melhor candidato (lista de COST_NODE). Atualiza uma aresta (se necessário) se ela já for um candidato ou insere ela na lista de candidatos se ele ainda não for.
CANDIDATE_NODE* update_candidate_list(CANDIDATE_NODE *candidate_list, CANDIDATE_NODE *best_candidate, COST_NODE_LIST *table, CANDIDATE_NODE *visited_list){

    CANDIDATE_NODE *updated_list = candidate_list;

    if(candidate_list==NULL)      //Redundante?
        return candidate_list;
    if(table==NULL)
        return candidate_list;

    COST_NODE_LIST *this_table_node;
    COST_NODE *this_neighbor_node;
    this_table_node = table;

    while(this_table_node!=NULL){

        if(strcmp(best_candidate->data.vertex_b, this_table_node->name)){ //Enquanto não alcançar o nó de vizinho do melhor candidato, percorre a table.
            this_table_node = this_table_node->next;
        }else{
            this_neighbor_node = this_table_node->first_neighbor;        //Após alcançar o nó do melhor candidato, percorre a lista de vizinhos adicionando-os como candidatos.
            while(this_neighbor_node!=NULL){
                //Busca vizinho atual da lista de candidatos para atualizar e/ou inserir como candidato. 
                updated_list =  update_candidates(updated_list, best_candidate, this_neighbor_node->data, visited_list);
                this_neighbor_node = this_neighbor_node->next;
            };
            break;
        };
    };

    return updated_list;
}

//Escolhe o melhor candidato (vertex_b com a aresta menos custosa).
CANDIDATE_NODE* choose_candidate(CANDIDATE_NODE *candidate_list, CANDIDATE_NODE *visited_list){

    CANDIDATE_NODE *this_candidate = candidate_list;
    CANDIDATE_NODE *best_candidate = NULL;

    while(this_candidate!=NULL){ //Enquanto não há um melhor candidato, escolhe a primeira aresta que ainda não foi visitada. Quando já houver, substitui quando achar uma de custo menor.
        if(!is_visited(visited_list, this_candidate->data) && (best_candidate == NULL || this_candidate->cum_cost + this_candidate->data.cost < best_candidate->cum_cost + best_candidate->data.cost))
            best_candidate = this_candidate;
        this_candidate = this_candidate->next;
    };

    return best_candidate;
}

//Recebe a lista de visitados e um nó a inserir na lista.
CANDIDATE_NODE* add_to_visited_list(CANDIDATE_NODE *this_node, CANDIDATE_NODE *new_node){

    CANDIDATE_NODE *updated_list = this_node;
    if(this_node==NULL){
        updated_list = new_node;
        updated_list->next = NULL;
    }else{
        while(this_node->next!=NULL){
            this_node = this_node->next;
        };
    this_node->next = new_node;
    new_node->next = NULL;
    };

    return updated_list;
}

//Recebe a lista de candidatos e um nó a remover da lista.
CANDIDATE_NODE* remove_from_candidate(CANDIDATE_NODE *this_node, CANDIDATE_NODE *best_candidate){
    
    CANDIDATE_NODE *updated_list = this_node;

    if(this_node==NULL){
        printf("\nErro: não é possível remover candidato de lista vazia.\n");
        updated_list = NULL;
    }
    else if(this_node == best_candidate){
                updated_list = this_node->next; 
    }else{      
        while(this_node->next!=NULL){
            if(this_node->next == best_candidate){
                this_node->next = this_node->next->next;
                break;
            };
            this_node = this_node->next;
        }
    }

    return updated_list;
}

//Bloco de funções que liberam a memória alocada durante a execução.
void free_candidate_list(CANDIDATE_NODE *candidate_list){
    if(candidate_list!=NULL){
        free_candidate_list(candidate_list->next);
        free(candidate_list);
    };
    return;
}

void free_visited_list(CANDIDATE_NODE *visited_list){
    
    if(visited_list!=NULL){
        free_visited_list(visited_list->next);
        free(visited_list);
    };
    return;
}

void free_dijkstra(CANDIDATE_NODE *candidate_list, CANDIDATE_NODE *visited_list){

    free_candidate_list(candidate_list);
    free_visited_list(visited_list);

    return;
}

// Recebe dados da source e do target, e recebe o ponteiro da table para buscar os vizinhos.
void dijkstra(COST_DATA source, COST_DATA target, COST_NODE_LIST *table){

    //Cria o primeiro candidato, que é a source/origin.
    CANDIDATE_NODE *candidate_list=NULL;
    candidate_list=malloc(sizeof(CANDIDATE_NODE));
    candidate_list->data = source;
    candidate_list->cum_cost = 0;
    candidate_list->previous_in_path = candidate_list;
    candidate_list->next = NULL;

    //Inicializa a lista de nós visitados e melhor candidato a ser adicionado à "malha", que por hora é a source/origem.
    CANDIDATE_NODE *visited_list = NULL;
    CANDIDATE_NODE *best_candidate = candidate_list;
    CANDIDATE_NODE *updated_list = NULL;
    
    //Enquanto o melhor nó não for o destino alvo, executa Dijkstra.
    while(strcmp(best_candidate->data.vertex_b, target.vertex_a)){               //strcmp() retorna 0 para string iguais.
        best_candidate = choose_candidate(candidate_list, visited_list);
        updated_list = update_candidate_list(candidate_list, best_candidate, table, visited_list);
        visited_list = add_to_visited_list(visited_list, best_candidate);
        candidate_list = remove_from_candidate(updated_list, best_candidate);
    };

    //Resultados
    printf("\nO custo de %s ate %s e %.2f\n", source.vertex_a, target.vertex_a, best_candidate->cum_cost);

    printf("\nCaminho: (destino) ", best_candidate->data.vertex_b, best_candidate->previous_in_path->data.vertex_b);
    while(best_candidate->previous_in_path!=best_candidate){
        printf("%s < ", best_candidate->data.vertex_b);
        best_candidate = best_candidate->previous_in_path;
    };
    printf("%s (origem)\n\n", best_candidate->data.vertex_b);

    free_dijkstra(candidate_list, visited_list);

    return;
}