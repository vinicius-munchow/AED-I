## Lista 05

Implementar os algoritmos de ordenação *Insertion Sort*, *Selection Sort*, *Quick Sort* e *Merge Sort*. O programa deve solicitar o tamanho do vetor de números (n) que será ordenado. O programa deve preencher um vetor de tamanho n com números aleatórios. Usar **srand(time(NULL))**; no inicio do programa. Faça um código que verifica se o resultado dado por cada algoritmo de ordenação está correto. Use a melhor lib para calcular quanto tempo cada algoritmo de ordenação levou para terminar.

- Para rodar o programa, use o comando **make compile** e, então, **make run**
- Caso deseje rodar o programa com os testes predefinidos pelo arquivo **test.txt** dentro da pasta, use o comando **make run-test**
- Caso deseje testar memory leaks no programa, use o comando **make run-memcheck** ou **make run-test-memcheck** (deve ter o Valgrind instalado)

- Estrutura de arquivos:

```
|───lista05
│   │   sorting.c
│   │   Makefile
|   |   test.txt
|   |   README.md

```

- Link para vídeo de demonstração: https://drive.google.com/file/d/1ZNaPM_TLYyzH_9OKHSsISo70qjOvQ9us/view?usp=sharing
- Link para print com teste de memory leak (feitos com **make run-test-memcheck**): https://drive.google.com/drive/folders/17ZM55u5E3noMabreN5HSv5cpv-WC6Kec?usp=sharing
