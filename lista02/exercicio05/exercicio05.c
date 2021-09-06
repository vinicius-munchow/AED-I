//Vinicius Laguna Munchow
//Matricula: 20101860
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[30];
    int age;
    int height;
} Person;

void flush_stdin(){ //limpa quaisquer caracteres restantes do input pelo usuario
    int c;
    do {
        c = fgetc(stdin);
    } while (c != EOF && c != '\n');
}

Person *add_data(Person *pBuffer, int listSize){
    int oldListSize = listSize - 1;
    Person person;

    pBuffer = realloc(pBuffer, sizeof(Person) * listSize);
    if (!pBuffer){
        printf("\nErro ao alocar memoria!\n");
        return NULL;
    }

    printf("\n-- Prossiga com os dados que deseja incluir:\n\n");
	printf("\t Nome: ");
    scanf("%30s^\n", person.name);
    flush_stdin();
	printf("\t Idade: ");
    scanf("%i", &person.age);
	printf("\t Altura: ");
    scanf("%i", &person.height);

    if(listSize > 1){
        *(pBuffer + (sizeof(Person) * oldListSize)) = person;
    } else {
        *(pBuffer) = person;
    }

    
    return pBuffer;
}

int list_data(Person *pBuffer, int listSize){
    int i;
    Person person;

    if (listSize != 0){
        printf("\n-------------------------\n");
        printf("\nDADOS REGISTRADOS:\n");
        for(i = 0; i < listSize; i++){
            person = *(pBuffer + (sizeof(Person) * i));
            printf("\nREGISTRO %i: \n", i + 1);
            printf("\nNome: %s", person.name);
            printf("\nIdade: %i", person.age);
            printf("\nAltura: %i\n", person.height);
        }
    } else {
        printf("\nAgenda vazia!");
        return -1;
    }
    return 0;
}

int menu(void){
	int c = 0;

	do {
        printf("\n-- Deseja adicionar dados na agenda? \n\n");
        printf("\t1 - Sim\n");
        printf("\t2 - Nao\n");
		printf("\n-- Digite sua escolha: ");
		scanf("%d", &c);
	} while (c < 1 || c > 2);
	getchar();
	return c;
}

int main(int argc, char *argv[]){
    int op = 0;
    int listSize = 0;

    Person *pBuffer = malloc(sizeof(int));
    if (!pBuffer) {
        printf("\nErro ao alocar memoria!\n");
        return -1;
    }

    do {
		op = menu();
		switch (op) {
		case 1:
            listSize++;
			pBuffer = add_data(pBuffer, listSize);
			break;
		case 2:
			list_data(pBuffer, listSize);
			break;
        }
	} while(op != 2);

    free(pBuffer);
	return 0;
}