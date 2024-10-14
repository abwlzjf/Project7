#include <stdio.h>
#include <stdlib.h>

// �� ���� ���� ��ȯ�ϴ� ���� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �ִ� ���� ���� �����ϰ� �� ���� ���
void insertAndPrintMaxHeap(int heap[], int* size, int value) {
    // ���� ���� �� ���� �߰�
    heap[*size] = value;
    int currentIndex = *size;
    (*size)++;

    // �ʱ� ���� �� �� ���� ���
    for (int i = 0; i < *size; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");

    // �ִ� �� �Ӽ��� �����ϱ� ���� �� ���ġ
    int moveCount = 0; // ��� �̵� Ƚ��
    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;
        if (heap[currentIndex] > heap[parentIndex]) {
            // ���� ��带 �θ�� ��ȯ
            swap(&heap[currentIndex], &heap[parentIndex]);
            moveCount++; // �̵��� Ƚ�� ����

            // ��ȯ �� �� ���� ���
            for (int i = 0; i < *size; i++) {
                printf("%d ", heap[i]);
            }
            printf("\n");

            currentIndex = parentIndex;
        }
        else {
            break;
        }
    }

    // ��尡 �̵��� Ƚ�� ���
    printf("��尡 �̵��� Ƚ��: %d\n", moveCount);
}

// ��Ʈ ��带 �����ϰ� �� ���� ���
void deleteRootAndPrintMaxHeap(int heap[], int* size) {
    if (*size <= 0) {
        printf("������ ��尡 �����ϴ�.\n");
        return;
    }

    int moveCount = 0;  // ��� �̵� Ƚ��

    // ������ ����� ���� ���
    printf("������ ��: %d\n", heap[0]);

    // ��Ʈ ��带 ������ ��ҷ� ��ü
    heap[0] = heap[*size - 1];
    (*size)--;

    int currentIndex = 0;

    // �ִ� �� �Ӽ��� �����ϱ� ���� �� ���ġ (���� ����)
    while (1) {
        int leftChild = 2 * currentIndex + 1;
        int rightChild = 2 * currentIndex + 2;
        int largest = currentIndex;

        if (leftChild < *size && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }
        if (rightChild < *size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != currentIndex) {
            // ���� ��带 ���� ū �ڽİ� ��ȯ
            swap(&heap[currentIndex], &heap[largest]);
            moveCount++;  // ��尡 �̵��� Ƚ�� ����

            // ��ȯ �� �� ���� ���
            for (int i = 0; i < *size; i++) {
                printf("%d ", heap[i]);
            }
            printf("\n");

            currentIndex = largest;
        }
        else {
            break;
        }
    }

    // �̵��� Ƚ�� ���
    printf("��尡 �̵��� Ƚ��: %d\n", moveCount);
}

// ���� ���� ������ ���
void printLevelOrder(int heap[], int size) {
    printf("Ʈ�� ������ ���\n");
    int level = 0;
    int count = 1;
    for (int i = 0; i < size; i++) {
        if (i == count - 1) {
            printf("\n[%d] ", level + 1);
            level++;
            count *= 2;
        }
        printf("%d ", heap[i]);
    }
    printf("\n");
}

// ���ο� TreeNode ���� �Լ�
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// TreeNode�� �������� �����ϴ� �Լ�
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1);  // �޸� �Ҵ� ���� �� ���α׷� ����
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Max Heap Tree�� ��带 �����ϴ� �Լ�
void InsertMaxHeapTree(TreeNode** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
    }
    else {
        // Max Heap Tree�� ��Ģ�� ���� ����
        if (value > (*root)->value) {
            int temp = (*root)->value;
            (*root)->value = value;
            value = temp;
        }
        if ((*root)->left == NULL) {
            InsertMaxHeapTree(&(*root)->left, value);
        }
        else if ((*root)->right == NULL) {
            InsertMaxHeapTree(&(*root)->right, value);
        }
        else {
            if (rand() % 2 == 0) {
                InsertMaxHeapTree(&(*root)->left, value);
            }
            else {
                InsertMaxHeapTree(&(*root)->right, value);
            }
        }
    }
}

// Ʈ���� �迭�� ��ȯ�Ͽ� ���� �����ϴ� �Լ�
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = NULL;  // ��Ʈ �ʱ�ȭ
    for (int i = 0; i < size; i++) {
        InsertMaxHeapTree(&root, inputData[i]);  // Ʈ���� �� ����
    }
    return root;  // ��Ʈ ��ȯ
}

// ���� ä��� ���� ��� �Լ�
void fillHeap(TreeNode* node, int heap[], int* size) {
    if (node == NULL) return;
    heap[(*size)++] = node->value;  // ���� ��� ���� �迭�� ����
    fillHeap(node->left, heap, size);  // ���� �ڽ� ��ȸ
    fillHeap(node->right, heap, size); // ������ �ڽ� ��ȸ
}

// ����� �������̽��� �����ϴ� �Լ�
void runUserInterface(TreeNode* root) {
    int heap[100];
    int size = 0;

    // ������ ��ȯ
    fillHeap(root, heap, &size);

    char choice;
    // �޴��� �׸� ���
    printf("�ѤѤѤѤѤѤѤѤѤѤѤ�\n");
    printf("| i\t: ��� �߰�     |\n");
    printf("| d\t: ��Ʈ ����     |\n");
    printf("| p\t: ������ ���   |\n");
    printf("| c\t: ����          |\n");
    printf("�ѤѤѤѤѤѤѤѤѤѤѤ�\n");

    while (1) {
        printf("�޴� �Է�: ");
        scanf_s(" %c", &choice);  // �Է� ���ۿ��� ������ �����ϱ� ���� ' ' �߰�

        switch (choice) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            int value;
            scanf_s("%d", &value);
            insertAndPrintMaxHeap(heap, &size, value);  // ���� �� ������ ���
            break;
        case 'd':
            deleteRootAndPrintMaxHeap(heap, &size);  // ��Ʈ ��� ���� �� ������ ���
            break;
        case 'p':
            printLevelOrder(heap, size);  // ������ Ʈ�� ���
            break;
        case 'c':
            printf("���α׷��� �����մϴ�.\n");
            return;
        default:
            printf("�߸��� ��ɾ��Դϴ�.\n");
        }
    }
}

// main �Լ�
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root;
    root = generateMaxHeapTree(inputData, size);  // �ִ� �� Ʈ�� ����
    runUserInterface(root);  // ����� �������̽� ����

    // ���� �޸� ���� (Ʈ�� �޸� ���� �κ��� �߰��ؾ� ��)
    free(root);
    return 0;
}