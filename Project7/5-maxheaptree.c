#include <stdio.h>
#include <stdlib.h>

// 두 정수 값을 교환하는 헬퍼 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 최대 힙에 값을 삽입하고 그 과정 출력
void insertAndPrintMaxHeap(int heap[], int* size, int value) {
    // 힙의 끝에 새 값을 추가
    heap[*size] = value;
    int currentIndex = *size;
    (*size)++;

    // 초기 삽입 후 힙 상태 출력
    for (int i = 0; i < *size; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");

    // 최대 힙 속성을 유지하기 위해 힙 재배치
    int moveCount = 0; // 노드 이동 횟수
    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;
        if (heap[currentIndex] > heap[parentIndex]) {
            // 현재 노드를 부모와 교환
            swap(&heap[currentIndex], &heap[parentIndex]);
            moveCount++; // 이동된 횟수 증가

            // 교환 후 힙 상태 출력
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

    // 노드가 이동된 횟수 출력
    printf("노드가 이동된 횟수: %d\n", moveCount);
}

// 루트 노드를 삭제하고 그 과정 출력
void deleteRootAndPrintMaxHeap(int heap[], int* size) {
    if (*size <= 0) {
        printf("삭제할 노드가 없습니다.\n");
        return;
    }

    int moveCount = 0;  // 노드 이동 횟수

    // 삭제할 노드의 값을 출력
    printf("삭제된 값: %d\n", heap[0]);

    // 루트 노드를 마지막 요소로 대체
    heap[0] = heap[*size - 1];
    (*size)--;

    int currentIndex = 0;

    // 최대 힙 속성을 유지하기 위해 힙 재배치 (하향 조정)
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
            // 현재 노드를 가장 큰 자식과 교환
            swap(&heap[currentIndex], &heap[largest]);
            moveCount++;  // 노드가 이동한 횟수 증가

            // 교환 후 힙 상태 출력
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

    // 이동된 횟수 출력
    printf("노드가 이동된 횟수: %d\n", moveCount);
}

// 힙을 레벨 순서로 출력
void printLevelOrder(int heap[], int size) {
    printf("트리 레벨별 출력\n");
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

// 새로운 TreeNode 생성 함수
typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// TreeNode를 동적으로 생성하는 함수
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 오류\n");
        exit(1);  // 메모리 할당 실패 시 프로그램 종료
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Max Heap Tree에 노드를 삽입하는 함수
void InsertMaxHeapTree(TreeNode** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
    }
    else {
        // Max Heap Tree의 규칙에 따라 삽입
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

// 트리를 배열로 변환하여 힙을 생성하는 함수
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = NULL;  // 루트 초기화
    for (int i = 0; i < size; i++) {
        InsertMaxHeapTree(&root, inputData[i]);  // 트리에 값 삽입
    }
    return root;  // 루트 반환
}

// 힙을 채우기 위한 재귀 함수
void fillHeap(TreeNode* node, int heap[], int* size) {
    if (node == NULL) return;
    heap[(*size)++] = node->value;  // 현재 노드 값을 배열에 저장
    fillHeap(node->left, heap, size);  // 왼쪽 자식 순회
    fillHeap(node->right, heap, size); // 오른쪽 자식 순회
}

// 사용자 인터페이스를 실행하는 함수
void runUserInterface(TreeNode* root) {
    int heap[100];
    int size = 0;

    // 힙으로 변환
    fillHeap(root, heap, &size);

    char choice;
    // 메뉴와 항목 출력
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf("| i\t: 노드 추가     |\n");
    printf("| d\t: 루트 삭제     |\n");
    printf("| p\t: 레벨별 출력   |\n");
    printf("| c\t: 종료          |\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

    while (1) {
        printf("메뉴 입력: ");
        scanf_s(" %c", &choice);  // 입력 버퍼에서 공백을 무시하기 위해 ' ' 추가

        switch (choice) {
        case 'i':
            printf("추가할 값 입력: ");
            int value;
            scanf_s("%d", &value);
            insertAndPrintMaxHeap(heap, &size, value);  // 삽입 후 과정을 출력
            break;
        case 'd':
            deleteRootAndPrintMaxHeap(heap, &size);  // 루트 노드 삭제 후 과정을 출력
            break;
        case 'p':
            printLevelOrder(heap, size);  // 레벨별 트리 출력
            break;
        case 'c':
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("잘못된 명령어입니다.\n");
        }
    }
}

// main 함수
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root;
    root = generateMaxHeapTree(inputData, size);  // 최대 힙 트리 생성
    runUserInterface(root);  // 사용자 인터페이스 실행

    // 동적 메모리 해제 (트리 메모리 해제 부분을 추가해야 함)
    free(root);
    return 0;
}