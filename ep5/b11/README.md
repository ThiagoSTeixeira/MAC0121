# Como usar
Escreva sua AI, nela inclua `robot_fight.h` e implemente as funções restantes. \\
Use `./make_ai nome-da-ai.c NUMERO_DO_JOGADOR` para compilar a AI para cada jogador \\
Rode love na pasta local ('love .')

# Observações
Só funciona com LOVE 0.9+, depois posso fazer ser compatével com 0.8 \\
Inclui o código fonte de lua para deixar tudo mais simples... 

# Exemplo
Para testar, execute esses comandos (Todos os jogadores terão a mesma AI) \\
```
./make_ai ai/stupid.c 1
./make_ai ai/stupid.c 2
./make_ai ai/stupid.c 3
./make_ai ai/stupid.c 4
love .
```
