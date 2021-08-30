//Vinicius Laguna Munchow
//Matricula: 20101860
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[10];
    int age;
    int phone;
} Person;

void flush_stdin(){ //limpa quaisquer caracteres restantes do input pelo usuario
    int c;
    do {
        c = fgetc(stdin);
    } while (c != EOF && c != '\n');
}

int get_index(char *pBuffer, char *name){
    int index;
    int listSize = *(int *)pBuffer;
    Person person;

    for(index = 0; index < listSize; index++){
        person = *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * index));

        if((strcmp(person.name, name)) == 0){
            printf("\nOperacao realizada com sucesso!\n");
            return index;
        }
    }

    //caso não caia em nenhuma condicao do loop acima
    printf("\nNao foi possivel localizar o registro!\n");
    return -1;
}

char *remove_person(char *pBuffer){
    int index = -1;
    int nextIndex;
    int oldListSize = *(int *)pBuffer;
    int newListSize;
    char rmName[10];
    Person person;

    if(oldListSize == 0){
        newListSize = 0;
    } else {
        newListSize = oldListSize - 1;
    }

    printf("\n-- Digite o nome da pessoa que deseja apagar da agenda: ");
    scanf("%10s^\n", rmName);
    flush_stdin();
    
    index = get_index(pBuffer, rmName);
    if(index == -1){
        return NULL;
    }

    nextIndex = index + 1;

    //a partir do index, traz as informações um indice para trás, para poder diminuir o tamanho do buffer no final
    while(nextIndex < oldListSize){
        person = *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * nextIndex));
        *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * index)) = person;
        index++;
        nextIndex++;
    }
 
    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(Person) * newListSize));
    *(int *)pBuffer = newListSize;
    
    return pBuffer;
}

char *add_person(char *pBuffer){
    int oldListSize = *(int *)pBuffer;
    int newListSize = oldListSize + 1;
    Person person;

    printf("\n-- Prossiga com as informacoes da pessoa que deseja incluir:\n\n");
	printf("\t Nome: ");
    scanf("%10s^\n", person.name);
    flush_stdin();
	printf("\t Idade: ");
    scanf("%i", &person.age);
	printf("\t Telefone: ");
    scanf("%i", &person.phone);
    
    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(Person) * newListSize));
    if (!pBuffer){
        printf("\nErro ao alocar memoria!\n");
        return NULL;
    }

    *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * oldListSize)) = person;
    *(int *)pBuffer = newListSize;
    return pBuffer;
}

int search_person(char *pBuffer){
    int index = -1;
    int listSize = *(int *)pBuffer;
    char name[10];
    Person person;

    printf("\n-- Digite o nome da pessoa que deseja buscar: ");
    scanf("%10s^\n", name);
    flush_stdin();

    index = get_index(pBuffer, name);
    if(index == -1){
        return -1;
    } else {
        person = *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * index));
        printf("\nREGISTRO %i: \n", index + 1);
        printf("\nNome: %s", person.name);
        printf("\nIdade: %i", person.age);
        printf("\nTelefone: %i\n", person.phone);
    }

    return 0;
}

int list_all(char *pBuffer){
    int i = 0;
    int listSize = *(int *)pBuffer;
    Person person;

    if (listSize != 0){
        printf("\n-- LISTA DE PESSOAS REGISTRADAS:\n");
        for(i = 0; i < listSize; i++){
            person = *(Person *)(pBuffer + sizeof(int) + (sizeof(Person) * i));
            printf("\nREGISTRO %i: \n", i + 1);
            printf("\nNome: %s", person.name);
            printf("\nIdade: %i", person.age);
            printf("\nTelefone: %i\n", person.phone);
        }
    } else {
        printf("\nAgenda vazia! Preencha-a com alguns registros antes e tente novamente!\n");
        return -1;
    }
    return 0;
}


int menu(void){
	int c = 0;

	do {
		printf("\n-- AGENDA DE PESSOAS:\n\n");
		printf("\t 1. Incluir registro\n");
		printf("\t 2. Apagar registro\n");
		printf("\t 3. Buscar por nome\n");
		printf("\t 4. Listar registros\n");
		printf("\t 5. Sair\n");
		printf("\n-- Digite sua escolha: ");
		scanf("%d", &c);
	} while (c <= 0 || c > 5);
	getchar();
	return c;
}

int main(int argc, char *argv[]){
    int op;

    void *pBuffer = malloc(sizeof(int));
    if (!pBuffer) {
        printf("\nErro ao alocar memoria!\n");
        return -1;
    }
    /* (int *) faz o type casting do buffer (por ele ser void) e o asterisco que precede o parenteses
    indica que se deseja acessar o valor do endereço, para que o mesmo receba 0 nesse caso */
    *(int *)pBuffer = 0;
    

    while(op != 5) {
		op = menu();
		switch (op) {
		case 1:
			pBuffer = add_person(pBuffer);
			break;
		case 2:
			pBuffer = remove_person(pBuffer);
			break;
		case 3:
            search_person(pBuffer);
            break;
        case 4:
			list_all(pBuffer);
			break;
		case 5:
			break;
		}
	}

    free(pBuffer);
	return 0;
}