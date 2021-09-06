## Exercicio 07

Modificação do Exercício 03 (lista01). O programa deve armazenar no máximo 10 pessoas. Todas as variáveis que forem usadas no programa deve ser ponteiros. A única exceção é o item 1 que deve ser uma variável global **Pessoa pessoas[10]**. Os ponteiros devem apontar para um buffer chamado pBuffer onde os dados devem ser armazenados (por exemplo, um contador para um for deve ser um ponteiro para int e o int vai ficar armazenado dentro de pBuffer) e não pode usar struct dentro do pBuffer.

- Para rodar os programas, use o comando **make compile** e, então, **make run**
- Caso deseje rodar os programas com os testes predefinidos pelos arquivos **test.txt** dentro das pastas, use o comando **make run-test**
- Caso deseje testar memory leaks nos programas, use o comando **make run-memcheck** ou **make run-test-memcheck** (deve ter o Valgrind instalado)

- Estrutura de arquivos:

```
|───exercicio07
│   │   exercicio07.c
│   │   Makefile
|   |   test.txt
|   |   README.md

```

- Link para vídeo de demonstração: https://drive.google.com/file/d/1vKwPwNzH5e_AqJMfReFJz4Ua769PirBC/view?usp=sharing
- Link para print com teste de memory leak (feitos com **make run-test-memcheck**): https://drive.google.com/file/d/1ViHh5d1gNju4lUGA8J5i3rdBvmOX9ClV/view?usp=sharing
