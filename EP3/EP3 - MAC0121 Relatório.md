# **EP3 - MAC0121 Relatório**

###### Thiago Santos Teixeira nUSP- 10736987

Perguntas:

1. Como funciona seu algoritmo? Qual a ideia geral?
2. Qual sua estimativa de complexidade de tempo de seu algoritmo para ordenar n panquecas?
3. Qual o número mı́nimo e máximo de flips seu algoritmo faz para ordenar uma sequência?
4. Mostre sequências em que seu algoritmo realiza o número máximo e mı́nimo de flips.
5. Mostre sequências em que seu algoritmo não realiza o número mı́nimo possı́vel de flips para
  ordenar uma sequência.
6. Você consegue alguma estimativa para a qualidade do seu algoritmo, ou seja, por exemplo, o
  número de flips dado por seu algoritmo é limitado por uma constante vezes o número ótimo
  de flips? Ou, o número de flips do seu algoritmo é limitado por n (número de panquecas)
  vezes o ótimo?
7. Imagine uma versão do problema em que as panquecas tenham um lado mais queimado que
  deva ficar voltado para baixo. Seu algoritmo funciona neste caso?



### 1.

​	A ideia geral de meu algoritmo é basicamente percorrer o vetor dado por inteiro e encontrar seu maior elemento e assim realizar um flip em sua posição de modo que ele seja colocado na ultima posição do array, assim, um segundo flip é realizado no inicio da pilha, fazendo com que o maior elemento seja colocado na primeira posição. Assim, esse processo vai se repetindo e colocando as maiores panquecas embaixo e deixando as maiores para o final.

### 2.

​	A estimativa de complexidade de tempo é O(n^2).

### 3.

​	O mínimo de flips que meu algorítmo realiza, ou seja, a quantidade de flips no melhor caso (uma sequência já ordenada, 5 4 3 2 1 0, por exemplo) é zero. Já o máximo de flips que meu algorítmo realiza, ou seja, a quantidade de flips no pior caso (1 3 4 2, por exemplo) é 2n-3.

### 4.

Máximo: (1 3 4 2), (2 4 5 1 3), (3 1 5 6 2 4).

Mínimo: Qualquer sequência já ordenada de maneira decrescente;  (4 3 2 1) (5 4 3 2 1) (6 5 4 3 2 1).

### 5.

​	Qualquer sequencia que não tenha seus números em ordem decrescente não será ordenada com o mínimo de flips.

(1 3 2 4), (1 2 4 5 ), (43 2 45 4), (45 65 324 2 3 5).

### 6.

### 7.

​	Num caso como esse, meu algorítmo não seria adequado, já que em seu funcionamento, os lados das panquecas não são levados em consideração, e assim elas são dispostas conforme mais conveniente, fazendo assim com que algumas panquecas fiquem com o lado queimado para cima e outras para baixo.



