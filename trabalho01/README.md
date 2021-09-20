## Trabalho 01

**Nome: Vinícius Münchow** ---
**Email: vlmunchow@inf.ufpel.edu.br | viniciuslaguna.m@gmail.com**

Continuar a sua implementação da agenda (exercício 3) semana 1 dentro dos mesmo parâmetros, mas incluir o seguinte: Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer. Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer. Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro). Não pode usar struct em todo o programa. Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa. Implementar a base de dados da agenda usando lista duplamente ligada (somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo).

- Para rodar os programas, use o comando **make compile** e, então, **make run**
- Caso deseje rodar os programas com os testes predefinidos pelos arquivos **test.txt** dentro das pastas, use o comando **make run-test**
- Caso deseje testar memory leaks nos programas, use o comando **make run-memcheck** ou **make run-test-memcheck** (deve ter o Valgrind instalado)

- Estrutura de arquivos:

```
|───trabalho01
│   │   trabalho01.c
│   │   Makefile
|   |   test.txt
|   |   README.md

```

- Link para vídeo de demonstração: https://drive.google.com/drive/folders/1v0eofZQXVdCyzwcpyUvBZPDpgHM29kEG?usp=sharing
- Link para prints com teste de memory leak (feitos com **make run-test-memcheck**): https://drive.google.com/drive/folders/12emXJfOAhm2DWawnkiUjLIrWM0AIPv35?usp=sharing

- Dificuldades encontradas: não fui capaz de concretizar a parte da fila ordenada e tive alguns problemas descritos no video e nos prints em relação a memory leaks que não consegui consertar também.
