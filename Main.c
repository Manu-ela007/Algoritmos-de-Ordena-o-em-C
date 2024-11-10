#include <stdio.h>   // Biblioteca padrão de C, utilizada para entrada e saída
#include <stdlib.h>  // Biblioteca que fornece funções como rand() e malloc()
#include <time.h>    // Biblioteca usada para medir o tempo de execução com clock()

// Funções de ordenação

// Função de ordenação por seleção (Selection Sort)
void selectionSort(int arr[], int n) {
    // Percorre o array até o penúltimo elemento
    for (int i = 0; i < n - 1; i++) {
        int menor = i; // Assume que o primeiro elemento não ordenado é o menor
        // Percorre o restante do array para encontrar o menor elemento
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[menor]) { // Se encontrar um menor
                menor = j; // Atualiza o índice do menor elemento
            }
        }
        // Troca o elemento atual pelo menor encontrado
        int temp = arr[menor];
        arr[menor] = arr[i];
        arr[i] = temp;
    }
}

// Função de ordenação por inserção (Insertion Sort)
void insertionSort(int arr[], int n) {
    // Começa a partir do segundo elemento, considerando que o primeiro já está ordenado
    for (int i = 1; i < n; i++) {
        int elemento_atual = arr[i]; // Guarda o valor do elemento atual
        int j = i - 1; // Inicia a comparação com o elemento anterior
        // Move os elementos maiores para a direita para abrir espaço
        while (j >= 0 && arr[j] > elemento_atual) {
            arr[j + 1] = arr[j]; // Desloca o elemento maior para a direita
            j--; // Passa para o próximo elemento à esquerda
        }
        // Coloca o elemento atual na posição correta
        arr[j + 1] = elemento_atual;
    }
}

// Função de ordenação por bolha (Bubble Sort)
void bubbleSort(int arr[], int n) {
    // Percorre o array, onde o maior elemento "flutua" para o final a cada iteração
    for (int i = 0; i < n - 1; i++) {
        // Compara elementos adjacentes
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // Se o elemento atual for maior que o próximo
                // Troca os elementos de posição
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função auxiliar para mesclar duas metades do array (Merge Sort)
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1; // Tamanho da subarray esquerda
    int n2 = r - m; // Tamanho da subarray direita
    int L[n1], R[n2]; // Arrays temporários para armazenar as subarrays

    // Copia os elementos da subarray esquerda para L[]
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    // Copia os elementos da subarray direita para R[]
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    // Mescla os elementos de L[] e R[] de volta para arr[]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) { // Enquanto houver elementos nas duas arrays
        if (L[i] <= R[j]) { // Se o elemento atual de L[] for menor ou igual ao de R[]
            arr[k++] = L[i++]; // Copia L[i] para arr[k]
        } else {
            arr[k++] = R[j++]; // Caso contrário, copia R[j]
        }
    }
    // Copia os elementos restantes de L[]
    while (i < n1) arr[k++] = L[i++];
    // Copia os elementos restantes de R[]
    while (j < n2) arr[k++] = R[j++];
}

// Função recursiva para dividir e ordenar o array (Merge Sort)
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; // Calcula o ponto médio do array
        mergeSort(arr, l, m); // Ordena a metade esquerda
        mergeSort(arr, m + 1, r); // Ordena a metade direita
        merge(arr, l, m, r); // Mescla as metades
    }
}

// Função "wrapper" para chamar o Merge Sort
void mergeSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n - 1); // Chama a função mergeSort com os índices do array
}

// Função auxiliar para particionar o array em duas partes (Quick Sort)
int particionar(int arr[], int primeiro, int ultimo) {
    int elemento_central = arr[ultimo]; // Escolhe o último elemento como pivô
    int i = primeiro - 1; // Inicializa o índice do menor elemento

    // Coloca os elementos menores que o pivô à esquerda
    for (int j = primeiro; j < ultimo; j++) {
        if (arr[j] < elemento_central) {
            i++; // Encontra um elemento menor
            // Troca arr[i] e arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Coloca o pivô na sua posição correta
    int temp = arr[i + 1];
    arr[i + 1] = arr[ultimo];
    arr[ultimo] = temp;

    return i + 1; // Retorna o índice do pivô
}

// Função recursiva de ordenação rápida (Quick Sort)
void quickSort(int arr[], int primeiro, int ultimo) {
    if (primeiro < ultimo) {
        int pi = particionar(arr, primeiro, ultimo); // Particiona o array e obtém a posição do pivô
        quickSort(arr, primeiro, pi - 1); // Ordena a parte esquerda
        quickSort(arr, pi + 1, ultimo); // Ordena a parte direita
    }
}

// Função "wrapper" para chamar o Quick Sort
void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1); // Chama o Quick Sort para o array completo
}

// Função auxiliar para manter a propriedade da Heap em um nó
void heapify(int arr[], int n, int i) {
    int maior = i; // Supondo que o nó atual é o maior
    int esquerda = 2 * i + 1; // Índice do filho à esquerda
    int direita = 2 * i + 2; // Índice do filho à direita

    // Verifica se o filho à esquerda existe e é maior
    if (esquerda < n && arr[esquerda] > arr[maior])
        maior = esquerda;

    // Verifica se o filho à direita existe e é maior que o nó atual
    if (direita < n && arr[direita] > arr[maior])
        maior = direita;

    // Se o maior não for mais o nó atual, ocorre a troca
    if (maior != i) {
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;

        // Aplica heapify recursivamente no sub-árvore
        heapify(arr, n, maior);
    }
}

// Função de ordenação por Heap (Heap Sort)
void heapSort(int arr[], int n) {
    // Constrói a heap max
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrai o maior elemento e o coloca no final do array
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Chama heapify para restaurar a propriedade da heap
        heapify(arr, i, 0);
    }
}

// Função para medir o tempo de execução de uma função de ordenação
void medirTempo(void (*sortFunction)(int[], int), int arr[], int n) {
    // Cria uma cópia do array para não alterar o original
    int* tempArray = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempArray[i] = arr[i]; // Copia os elementos do array original
    }

    clock_t inicio = clock(); // Marca o início do tempo
    sortFunction(tempArray, n); // Chama a função de ordenação
    clock_t fim = clock(); // Marca o fim do tempo
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC; // Calcula o tempo de execução

    printf("Tempo de execução: %f segundos\n", tempo_execucao); // Exibe o tempo de execução

    free(tempArray); // Libera a memória alocada
}

// Função para gerar um array de inteiros aleatórios
void gerarArrayAleatorio(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Gera números aleatórios entre 0 e 9999
    }
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual

    int tamanhos[] = {100, 1000, 10000, 50000, 100000}; // Tamanhos de array a serem testados
    int n_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]); // Calcula o número de tamanhos

    // Loop através dos tamanhos definidos
    for (int i = 0; i < n_tamanhos; i++) {
        int n = tamanhos[i]; // Tamanho atual do array
        int arr[n]; // Declara um array do tamanho n
        gerarArrayAleatorio(arr, n); // Gera um array aleatório

        printf("\nTeste para tamanho %d:\n", n); // Indica o tamanho do teste

        printf("Selection Sort: ");
        medirTempo(selectionSort, arr, n); // Mede e exibe o tempo de execução do Selection Sort

        printf("Insertion Sort: ");
        medirTempo(insertionSort, arr, n); // Mede e exibe o tempo de execução do Insertion Sort

        printf("Bubble Sort: ");
        medirTempo(bubbleSort, arr, n); // Mede e exibe o tempo de execução do Bubble Sort

        printf("Merge Sort: ");
        medirTempo(mergeSortWrapper, arr, n); // Mede e exibe o tempo de execução do Merge Sort

        printf("Quick Sort: ");
        medirTempo(quickSortWrapper, arr, n); // Mede e exibe o tempo de execução do Quick Sort

        printf("Heap Sort: ");
        medirTempo(heapSort, arr, n); // Mede e exibe o tempo de execução do Heap Sort
    }

    return 0; // Finaliza a execução do programa
}
