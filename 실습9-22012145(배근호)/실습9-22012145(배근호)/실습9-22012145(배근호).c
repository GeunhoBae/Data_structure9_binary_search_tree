#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

typedef struct node tree;
struct node {
    int key;
    double value;
    struct node* lchild, * rchild;
};

//함수선언
tree* modified_search(tree*, int);
void insert_node(tree**, int, double);
void inorder(tree*);
void search(tree*, int, int);
tree* make_bst(int);
int count_node(tree*);
int count_depth(tree*);
int count_leaf(tree*);
void delete_tree(tree*);

//main 함수
void main() {
    //9.1
    printf("9.1\n");
    printf("12개의 (key, value)쌍을 생성하여 이진탐색트리 생성\n");
    tree* A = NULL;
    double A_key[12] = { 10, 6, 15, 8, 18, 12, 3, 14, 9, 20, 5, 2 };
    for (int i = 0; i < 12; i++) //value는 key로 설정
        insert_node(&A, A_key[i], A_key[i]);
    inorder(A);
    printf("노드 수: %d\n", count_node(A));
    printf("깊이: %d\n", count_depth(A)-1);
    printf("단말노드 수: %d\n", count_leaf(A));
    printf("\n\n");

    //9.2
    printf("9.2\n");
    printf("key를 이용한 검색\n");
    int key_num; int count;
    while (1) {
        printf("찾고자 하는 key입력(종료:-999): ");
        scanf("%d", &key_num);
        if (key_num == -999) break;
        count = 0;
        search(A, key_num, count);
        printf("\n");
    }
    printf("\n");

    //9.3
    printf("9.3\n");
    tree* B = NULL;
    int n;
    while (1) {
        printf("n개의 노드를 가진 이진검색 트리생성(n)-종료(-1): ");
        scanf("%d", &n);
        if (n == -1) break;

        clock_t before = clock();
        B = make_bst(n);
        clock_t after = clock();

        inorder(B);
        printf("생성시간: %f\n", (double) (after - before) / CLOCKS_PER_SEC);
        printf("노드 수: %d\n", count_node(B));
        printf("깊이: %d\n", count_depth(B)-1);
        printf("단말노드 수: %d\n", count_leaf(B));
    }

    //9.4
    printf("\n9.4\n");
    printf("트리삭제\n");
    delete_tree(A);
    delete_tree(B);
    inorder(A);
    inorder(B);
}

//함수구현
void delete_tree(tree* ptr) {
    delete_tree(ptr->lchild);
    delete_tree(ptr->rchild);
    free(ptr);
}

int count_leaf(tree* ptr) {
    if (ptr) {
        if (!ptr->lchild && !ptr->rchild)
            return 1;
        else
            return count_leaf(ptr->lchild) + count_leaf(ptr->rchild);
    }
    else return 0;
}

int count_depth(tree* ptr) {
    if (ptr) {
        int left_depth = count_depth(ptr->lchild);
        int right_depth = count_depth(ptr->rchild);
        if (left_depth < right_depth)
            return right_depth + 1;
        else
            return left_depth + 1;
    }
    else return 0;
}

int count_node(tree* ptr) {
    if (ptr) {
        return 1 + count_node(ptr->lchild) + count_node(ptr->rchild);
    }
    else return 0;
}

tree* make_bst(int n) {
    tree* B = NULL;
    for (int i = 0; i < n; i++) {
        int key = (rand() / (0x7fff * 1.0)) * 100000000;
        double value = 1.0 / key;
        insert_node(&B, key, value);
    }
    
    return B;
}

void search(tree* A, int key_num, int count) {
    count++;
    if (!A) return printf("없는 노드입니다.");
    if (key_num == A->key)
        return printf("count: %d, key: %d, value: %f", count, A->key, A->value);
    if (key_num < A->key)
        search(A->lchild, key_num, count);
    else search(A->rchild, key_num, count);
}

void inorder(tree* root) {
    if (root) {
        inorder(root->lchild);
        printf("(%d, %f) \n", root->key, root->value);
        inorder(root->rchild);
    }
}

void insert_node(tree** root, int key, double value) {
    tree* ptr, * parent = modified_search(*root, key);

    if (parent || !(*root)) {
        ptr = (tree*)malloc(sizeof(tree));
        ptr->value = value;
        ptr->key = key;
        ptr->lchild = ptr->rchild = NULL;

        if (*root) {
            if (key < parent->key) //key값이 작을때
                parent->lchild = ptr;
            else
                parent->rchild = ptr;
        }
        else *root = ptr;
    }
}

tree* modified_search(tree* root, int key) {
    for (tree* ptr = root; ptr; ) {
        if (key == ptr->key) //키 중복
            return NULL;
        if (key < ptr->key) {
            if (ptr->lchild == NULL)
                return ptr;
            else ptr = ptr->lchild;
        }
        else { //key > ptr->value
            if (ptr->rchild == NULL)
                return ptr;
            else ptr = ptr->rchild;
        }
    }
    return NULL;
}