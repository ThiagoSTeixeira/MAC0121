# EP4 121 Relatório

### Thiago Santos Teixeira nUSP 10736987

###### Testes de tempo:

​        Para testar o tempo foi usado um arquivo com terceiro livro da serie
​    Game of Thrones (2.4 Mb)  os dois primeiros livros da serie (3.4Mb) e o
​    ultimo teste foi os ultimos quatro livros da serie Harry Potter (5.1 Mb).
​            VD/A   VO/A   LD/A   LO/A   AB/A    VD/O   VO/O   LD/O   LO/O   AB/O
​    test1:  4s     4s     6.6s   27.7s  0.018s  3.9s   4s     6.6s   30.8s  0.02s
​    test2:  5.8s   5s     10s    48s    0.02s   6s     4s     10s    52s    0.02s
​    test3:  9s     7.5s   15s    1m18s  0.03s   9s     7.2s   14.7s  1m24s  0.04s



###### Complexidade do programa:

Vetor desodenado: 

​	-Inserção de um item: O(n) *busca linear*

​	-Destruição da tabela: O(n)

​	-Imprimir a tabela: O(NlogN)  *devido ao Merge*

Vetor Ordenado:

> ​	Similar ao desordenado, mas com inserção mais rapida, e a impressão com O(n), quando imprimindo em ordem de frequência terá um Merge O(NlogN)

Lista Ligada Desordenada:

​	-Inserção: O(n)

> Para imprimir a tabela é necessário um vetor auxiliar, mantendo a complexidade mas ocupando o dobro de memória.

Lista ligada ordenada: 

> Complexidade se mantém similar mas não é necessario percorrer a tabela inteira para saber se um item ja foi inserido

Arvore de busca binária:

​	-Complexidade média O(logN)

> Pior caso é linear e a chance de acontecer é muito baixa.



###### Outras Línguas:

Para textos em diferentes línguas, o funcionamento do programa se mantem similar, exceto para aquelas que utilizam muitos carácteres especiais.



