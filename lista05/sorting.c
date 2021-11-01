//Vinicius Laguna Munchow
//Matricula: 20101860
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int is_ordered(int *data, int size) {
    int i;

    for(i = 0; i < size; i++) {
        if(data[i] > data[i + 1]) {
            printf("\nERRO! VETOR NÃO ORDENADO\n");
            return -1;
        }
    }

    return 0;
}

int insertion_sort(int *data, int size) {
    int i, j, temp;

    for(i = 1; i < size; i++) {
        temp = data[i];
        for(j = i; (j > 0) && (temp < data[j - 1]); j--) {
            data[j] = data[j - 1];
        }
        data[j] = temp;
    }

    return 0;
}

int selection_sort(int *data, int size) {
    int i, j,temp, min, min_id = 0;

    for(i = 0; i < size - 1; i++) {
        min = data[i];
        for(j = i + 1; j < size; j++) {
            if(data[j] < min) {
                min = data[j];
                min_id = j;
            }
        }

        if (i != min_id) {
            temp = data[i];
            data[i] = data[min_id];
            data[min_id] = temp;
            min_id = i + 1;
        }
    }

    return 0;
}

int quick_sort(int *data, int left, int right) {
    int mid, temp, leftHandler, rightHandler;
    leftHandler = left;
    rightHandler = right;
    mid = data[(leftHandler + rightHandler)/2];

    do {
        while(data[leftHandler] < mid) {
            leftHandler++; 
        }
        while(mid < data[rightHandler]) {
            rightHandler--;
        }
        if(leftHandler <= rightHandler) {
            temp = data[leftHandler];
            data[leftHandler] = data[rightHandler];
            data[rightHandler] = temp;
            leftHandler++;
            rightHandler--;
        }
    } while(leftHandler <= rightHandler);

    if(left < rightHandler) {
        quick_sort(data, left, rightHandler);
    }
    if(leftHandler < right) {
        quick_sort(data, leftHandler, right);
    }

    return 0;
}

int merge (int * data, int left, int mid, int right) {
    int i, j, k, size, *temp, v1, v2, end1=0, end2=0;
    
    //tamanho do vetor temp
    size = right - left + 1;
    //vetores divididos
    v1 = left;
    v2 = mid + 1;
    temp = (int *)malloc(sizeof(int) * size);

    if(temp != NULL) {
    //para cada posição do vetor temp, testa qual o elemento maior entre os vetores divididos
        for(i = 0; i < size; i++) {
            //roda o seguinte bloco caso nenhum dos vetores divididos tenha chegado ao final
            if(!end1 && !end2) {
                if(data[v1] < data[v2]) {
                    temp[i] = data[v1++];
                } else {
                    temp[i] = data[v2++];
                }
                //testa se algum dos vetores divididos acabou de chegar ao final
                if(v1 > mid) {
                    end1 = 1;
                }
                if(v2 > right) {
                    end2 = 1;
                }
            } else { 
                //copia para o final o que sobrou
                if(!end1) {
                    temp[i] = data[v1++];
                } else {
                    temp[i] = data[v2++];
                }
            }
        }
        //copia do vetor temp para o original, ja de forma ordenada
        for(j = 0, k = left; j < size; j++, k++) {
            data[k] = temp[j];
        }
    }
    
    free(temp);
    return 0;
}

int merge_sort (int *data, int left, int right) {
    int mid;

    if (left < right) {
        mid = (left + right) / 2;
        merge_sort(data, left, mid);
        merge_sort(data, mid + 1, right);
        merge(data, left, mid, right);
    }
    
    return 0;
}

int print_vector(int *data, int size) {
    int i;
    
    for(i = 0; i < size; i++) {
        printf("%i ", data[i]);
    }
    
    return 0;
}

int menu(void) {
	int i = 0;

	do {
		printf("\n-- ALGORITMOS DE ORDENACAO:\n\n");
		printf("\t 1. Insertion Sort\n");
		printf("\t 2. Selection Sort\n");
		printf("\t 3. Quick Sort\n");
		printf("\t 4. Merge Sort\n");
		printf("\n-- Digite sua escolha: ");
		scanf("%i", &i);
	} while(i <= 0 || i > 4);
	getchar();
	return i;
}

int main () {
    struct timeval begin, end;
    float elapsed;
    int size = 0, i = 0, op = 1;
    int *data = malloc(sizeof(int));

    srand(time(NULL));

    while(op != 0) {
       
        op = menu();

        printf("\n--------------------------------------------------------------------\n");

        printf("\n-- Digite o tamanho do vetor de numeros a ser ordenado: ");
        scanf("%i", &size);
        data = realloc(data, sizeof(int) * size);

        for(i = 0; i < size; i++) {
            data[i] = rand()%1000;
        }

        printf("\nVetor de numeros aleatorios: ");
        print_vector(data, size);

        printf("\n\n--------------------------------------------------------------------\n");

        switch (op) {
        case 1:
            gettimeofday(&begin, 0);
            insertion_sort(data, size);
            gettimeofday(&end, 0);

            elapsed = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)*1e-6;

            is_ordered(data, size - 1);

            printf("\nVetor ordenado pelo algoritmo Insertion Sort: ");
            print_vector(data, size);
            printf("\n\nO algoritmo Insertion Sort levou %.8f segundos para ordenar o vetor.\n", elapsed);
            break;
        case 2:
            gettimeofday(&begin, 0);
            selection_sort(data, size);
            gettimeofday(&end, 0);

            elapsed = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)*1e-6;

            is_ordered(data, size - 1);

            printf("\nVetor ordenado pelo algoritmo Selection Sort: ");
            print_vector(data, size);
            printf("\n\nO algoritmo Selection Sort levou %.8f segundos para ordenar o vetor.\n", elapsed);
            break;
        case 3:
            gettimeofday(&begin, 0);
            quick_sort(data, 0, size - 1);
            gettimeofday(&end, 0);

            elapsed = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)*1e-6;

            is_ordered(data, size - 1);

            printf("\nVetor ordenado pelo algoritmo Quick Sort: ");
            print_vector(data, size);

            printf("\n\nO algoritmo Quick Sort levou %.8f segundos para ordenar o vetor.\n", elapsed);
            break;
        case 4:
            gettimeofday(&begin, 0);
            merge_sort(data, 0, size - 1);
            gettimeofday(&end, 0);

            elapsed = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)*1e-6;

            is_ordered(data, size - 1);

            printf("\nVetor ordenado pelo algoritmo Merge Sort: ");
            print_vector(data, size);

            printf("\n\nO algoritmo Merge Sort levou %.8f segundos para ordenar o vetor.\n", elapsed);
            break;
        }

        printf("\n--------------------------------------------------------------------\n");

        do {
            printf("\n-- Deseja realizar outra operacao:\n\n");
            printf("\t 1. Sim\n");
            printf("\t 0. Nao (sair do programa)\n");
            printf("\n-- Digite sua escolha: ");
            scanf("%i", &op);
        } while(op != 0 && op != 1);
    }

    free(data);
    return 0;
}