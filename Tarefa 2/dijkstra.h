/* Esta é a parte do código que ficou incompleta. */
#include <stdio.h>
#include <stdlib.h>

typedef struct candidate_node{
    COST_DATA data;
    struct candidate_node *previous_in_path;
    double cum_cost;
    struct candidate_node *next;
}CANDIDATE_NODE;

//dijkstra |-> choose_candidate -> update_candidate_list -> update_candidates -> create_candidate
//         | add_to_visited_list
//         | remove_from_candidate

//Verifica se um candidato (aresta/vertex_b) já foi visitado.
int is_visited(CANDIDATE_NODE *this_node, COST_DATA this_candidate);

//Adiciona um candidato à lista de candidatos.
CANDIDATE_NODE* create_candidate(COST_DATA data, CANDIDATE_NODE *best_candidate, CANDIDATE_NODE *next);

//Busca candidato atual (vertex_b) da lista de vizinhos na lista de candidatos para atualizar. Caso o candidato não exista, cria um novo nó de candidato (aresta/vertex_b).  
CANDIDATE_NODE* update_candidates(CANDIDATE_NODE *candidate_list, CANDIDATE_NODE *best_candidate, COST_DATA new_candidate_data, CANDIDATE_NODE *visited_list);

//Busca na table a lista de vizinhos do melhor candidato (lista de COST_NODE). Atualiza uma aresta (se necessário) se ela já for um candidato ou insere ela na lista de candidatos se ele ainda não for.
CANDIDATE_NODE* update_candidate_list(CANDIDATE_NODE *candidate_list, CANDIDATE_NODE *best_candidate, COST_NODE_LIST *table, CANDIDATE_NODE *visited_list);

//Escolhe o melhor candidato (vertex_b com a aresta menos custosa).
CANDIDATE_NODE* choose_candidate(CANDIDATE_NODE *candidate_list, CANDIDATE_NODE *visited_list);

//Recebe a lista de visitados e um nó a inserir na lista.
CANDIDATE_NODE* add_to_visited_list(CANDIDATE_NODE *this_node, CANDIDATE_NODE *new_node);

//Recebe a lista de candidatos e um nó a remover da lista.
CANDIDATE_NODE* remove_from_candidate(CANDIDATE_NODE *this_node, CANDIDATE_NODE *best_candidate);

// Recebe dados da source e do target, e recebe o ponteiro da table para buscar os vizinhos.
void dijkstra(COST_DATA source, COST_DATA target, COST_NODE_LIST *table);