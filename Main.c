#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[menor]) {
                menor = j;
            }
        }
        int temp = arr[menor];
        arr[menor] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int elemento_atual = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > elemento_atual) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = elemento_atual;
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

int particionar(int arr[], int primeiro, int ultimo) {
    int elemento_central = arr[ultimo];
    int i = primeiro - 1;

    for (int j = primeiro; j < ultimo; j++) {
        if (arr[j] < elemento_central) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[ultimo];
    arr[ultimo] = temp;

    return i + 1;
}

void quickSort(int arr[], int primeiro, int ultimo) {
    if (primeiro < ultimo) {
        int pi = particionar(arr, primeiro, ultimo);
        quickSort(arr, primeiro, pi - 1);
        quickSort(arr, pi + 1, ultimo);
    }
}

void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

void heapify(int arr[], int n, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && arr[esquerda] > arr[maior])
        maior = esquerda;

    if (direita < n && arr[direita] > arr[maior])
        maior = direita;

    if (maior != i) {
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        heapify(arr, n, maior);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void medirTempo(void (*sortFunction)(int[], int), int arr[], int n) {
    int* tempArray = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempArray[i] = arr[i];
    }

    clock_t inicio = clock();
    sortFunction(tempArray, n);
    clock_t fim = clock();
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f segundos\n", tempo_execucao);

    free(tempArray);
}

void gerarArrayAleatorio(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

int main() {
    srand(time(NULL));

    int tamanhos[] = {100, 1000, 10000, 50000, 100000};
    int n_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    for (int i = 0; i < n_tamanhos; i++) {
        int n = tamanhos[i];
        int arr[n];
        gerarArrayAleatorio(arr, n);

        printf("\nTeste para tamanho %d:\n", n);

        printf("Selection Sort: ");
        medirTempo(selectionSort, arr, n);

        printf("Insertion Sort: ");
        medirTempo(insertionSort, arr, n);

        printf("Bubble Sort: ");
        medirTempo(bubbleSort, arr, n);

        printf("Merge Sort: ");
        medirTempo(mergeSortWrapper, arr, n);

        printf("Quick Sort: ");
        medirTempo(quickSortWrapper, arr, n);

        printf("Heap Sort: ");
        medirTempo(heapSort, arr, n);
    }

    return 0;
}
