## Tarefa 1: Recuperação de nome de cidade a partir de CEP.

### Metodologia

Escolhi uma árvore para representar as faixas de CEP correspondentes a cada cidade. Porém, logo percebi
que existem faixas menores dentro de faixas maiores, e a árvore inicialmente binária virou ternária. A
inserção se manteria trivial caso os intervalos mais largos fossem sempre inseridos primeiro, mas como
a entrada não é ordenada, houveram inserções entre nós já inseridos.

### O que poderia ter sido feito

Considerando o volume da entrada, seria útil ter feito um balanceamento da árvore. Mesmo que não seja
possível alterar a posição de nós filhos do meio, ainda seria possível realizar movimentos com os filhos
da esquerda e da direita, e imagino que um balanceamento por altura com uma certa folga seria o ideal.


## Tarefa 2: Encontrar o caminho de custo mínimo entre duas cidades, dados seus respectivos CEPs e custos em um grafo.

### Metotolodia

Utilizei uma lista de cidades em que cada nó aponta para uma lista com todos os vizinhos desta mesma cidade.
Posteriormente foram criadas estruturas para armazenar a lista de nós visitados e lista de nós candidatos,
de acordo com o Algoritmo de Dijkstra.