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


## Tarefa 2 (incompleta): Encontrar o caminho de custo mínimo entre duas cidades, dados seus respectivos CEPs e custos em um grafo.

### Metotolodia

Utilizei uma lista de cidades em que cada nó aponta para uma lista com todos os vizinhos desta mesma cidade.
Posteriormente foram criadas estruturas para armazenar a lista de nós visitados e lista de nós candidatos,
que seriam utilizadas em uma implementação do Algoritmo de Dijkstra.

### O que poderia ter sido feito

- Eu poderia ter utilizado outra linguagem ao invés de C. O desconhecimento da quantidade de entradas me fez
optar listas encadeadas, mas a dificuldade da conversão e comparação dos dados entre as diferentes estruturas
foi o que me impossibilitou de concluir o desafio.
- Implementar o algoritmo certamente seria mais fácil com vetores e uma matriz de adjacência, mas a matriz
pode ou não ficar com muitos endereços não preenchidos e isso implicaria na necessidade de um mapeamento de
nomes de cidades em índices numéricos.
- Eu posso ter usado mais recursão do que deveria. Se fosse refatorar esse código, eu procuraria por
oportunidades de trocar recursões por loops.