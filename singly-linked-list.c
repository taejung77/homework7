#include<stdio.h>
#include<stdlib.h>  

typedef struct Node { // 노드 구조체
    int key;
    struct Node* link;
} listNode;

typedef struct Head { // 헤드 구조체
    int key;
    struct Node* first;
} headNode;

headNode* initialize(headNode* h); //   초기화 함수
int freeList(headNode* h);      //   리스트 해제 함수

void printList(headNode* h);    //   리스트 출력 함수

int insertNode(headNode* h, int key);   ///   노드 삽입 함수
int insertLast(headNode* h, int key);   //   마지막에 노드 삽입 함수
int insertFirst(headNode* h, int key);  //  처음에 노드 삽입 함수

int deleteFirst(headNode* h);           //   처음 노드 삭제 함수
int deleteNode(headNode* h, int key);   //   노드 삭제 함수
int deleteLast(headNode* h);            //   마지막 노드 삭제 함수
int invertList(headNode* h);            //   리스트 뒤집기 함수

int main(){
    char command;
    int key;
    headNode* headnode = NULL;  // 헤드 노드 생성

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p\n");
        printf(" Insert Node   = i           Delete Node   = d\n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command){
            case 'z': case 'Z':
                headnode = initialize(headnode);
                break;
            case 'p': case 'P':
                printList(headnode);
                break;
            case 'i': case 'I':
                printf("Your Key = ");
                scanf("%d", &key);
                insertNode(headnode, key);
                break;
            case 'n': case 'N':
                printf("Your Key = ");
                scanf("%d", &key);
                insertLast(headnode, key);
                break;
            case 'd': case 'D':
                printf("Your Key = ");
                scanf("%d", &key);
                deleteFirst(headnode);
                break;
            case 'e': case 'E':
                deleteLast(headnode);
                break;
            case 'f': case 'F':
                printf("Your Key = ");
                scanf("%d", &key);
                insertFirst(headnode, key);
                break;
            case 't': case 'T':
                deleteFirst(headnode);
                break;
            case 'r': case 'R':
                invertList(headnode);
                break;
            case 'q': case 'Q':
                freeList(headnode);
                break;
            default:
                printf("\n       >>>>>   Concentration!!   <<<<<     \n");
                break;
        }
    }while(command != 'q' && command != 'Q');
    printf("[----- [Your Name] [Student ID] -----]");
    return 1;
}

headNode* initialize(headNode* h){  // 초기화 함수
    if(h != NULL){
        freeList(h);    // 리스트가 비어있지 않으면 해제
    }
    headNode* temp = (headNode*)malloc(sizeof(headNode));   // 헤드 노드 생성
    temp->first = NULL;                                     // 헤드 노드의 링크를 NULL로 초기화                
    return temp;            
}
int freeList(headNode* h){          // 리스트 해제 함수
    listNode* p= h->first;          // 리스트의 첫 번째 노드를 가리키는 포인터 p
    listNode* prev = NULL;          // 이전 노드를 가리키는 포인터 prev
    while(p != NULL){               // p가 NULL이 아닐 때까지 반복
        prev = p;                   // prev에 p를 대입
        p = p->link;                // p에 p의 다음 노드를 대입
        free(prev);                 // prev 해제
    }
    free(h);                        // 헤드 노드 해제
    return 0 ;
}
int insertNode(headNode* h, int key) {  // 노드 삽입 함수
    listNode* node = (listNode*)malloc(sizeof(listNode));   // 삽입할 노드 생성
    node->key = key;                                        // 노드의 key에 key 대입
    node->link = NULL;                                      // 노드의 링크를 NULL로 초기화

    if (h->first == NULL || key < h->first->key) {  // 첫 번째 노드보다 작은 값인 경우
        node->link = h->first;                      // 삽입할 노드의 링크에 첫 번째 노드 대입
        h->first = node;                            // 헤드 노드에 삽입할 노드 대입
        return 0;
    }

    listNode* prev = h->first;          // 이전 노드를 가리키는 포인터 prev
    listNode* temp = h->first->link;    // 다음 노드를 가리키는 포인터 temp

    while (temp != NULL) {
        if (key < temp->key) {  // 이전 노드와 다음 노드 사이에 삽입해야 하는 경우
            prev->link = node;  // 이전 노드의 링크에 삽입할 노드 대입
            node->link = temp;  // 삽입할 노드의 링크에 다음 노드 대입
            return 0;   
        }
        prev = temp;          // prev에 temp 대입
        temp = temp->link;    // temp에 temp의 다음 노드 대입
    }

    // 마지막에 삽입하는 경우
    prev->link = node;
    return 0;
}

int insertFirst(headNode* h, int key){  // 처음에 노드 삽입 함수
    listNode* node=(listNode*)malloc(sizeof(listNode)); // 삽입할 노드 생성
    node->key = key;       // 노드의 key에 key 대입

    node->link = h->first;                   // 삽입할 노드의 링크에 첫 번째 노드 대입
    h->first = node;                         // 헤드 노드에 삽입할 노드 대입
    return 0;
}
int insertLast(headNode* h, int key){   // 마지막에 노드 삽입 함수
    listNode* node=(listNode*)malloc(sizeof(listNode)); // 삽입할 노드 생성
    listNode* p;                    // 노드를 탐색할 포인터 p
    node->key = key;                // 노드의 key에 key 대입
    node->link = NULL;              // 노드의 링크를 NULL로 초기화
    if(h->first == NULL){           // 리스트가 비어있는 경우
        h->first = node;            // 헤드 노드에 삽입할 노드 대입
        return 0;
    }
    p = h->first;     // p에 첫 번째 노드 대입
    while(p->link != NULL){ // p의 링크가 NULL이 아닐 때까지 반복
        p = p->link;    // p에 p의 다음 노드 대입
    }
    p->link = node;     // p의 링크에 삽입할 노드 대입
    return 0;   
}
int deleteFirst(headNode* h){   // 처음 노드 삭제 함수
    listNode* temp;         // 삭제할 노드를 가리키는 포인터 temp
    if(h->first == NULL){   // 리스트가 비어있는 경우
        printf("List is empty\n");  
        return 0;
    }
    temp = h->first;        // temp에 첫 번째 노드 대입
    h->first = temp->link;  // 헤드 노드에 temp의 다음 노드 대입
    free(temp);             // temp 해제
    return 0;
}
int deleteNode(headNode* h, int key){   // 노드 삭제 함수
    listNode* temp;  
    listNode* prev; 
    if(h->first == NULL){   // 리스트가 비어있는 경우
        printf("List is empty\n");  
        return 0;
    }
    if(h->first->key == key){   // 첫 번째 노드가 삭제할 노드인 경우
        temp = h->first;        // temp에 첫 번째 노드 대입
        h->first = temp->link;  // 헤드 노드에 temp의 다음 노드 대입
        free(temp);
        return 0;
    }
    prev = h->first;
    temp = h->first->link;
    while(temp != NULL){        // temp가 NULL이 아닐 때까지 반복
        if(temp->key == key){
            prev->link = temp->link;
            free(temp);
            return 0;
        }
        prev = temp;
        temp = temp->link;
    }
    printf("There is no %d in list\n", key);
    return 0;
}
int deleteLast(headNode* h){    // 마지막 노드 삭제 함수
    listNode* temp;
    listNode* prev;
    if(h->first == NULL){   
        printf("List is empty\n");
        return 0;
    }
    if(h->first->link == NULL){ // 리스트에 노드가 하나만 있는 경우
        free(h->first);         // 첫 번째 노드 해제
        h->first = NULL;
        return 0;
    }
    prev = h->first;
    temp = h->first->link;
    while(temp->link != NULL){  
        prev = temp;    
        temp = temp->link;
    }
    free(temp);
    prev->link = NULL;
    return 0;
}
int invertList(headNode* h){    // 리스트 뒤집기 함수
    listNode* p;
    listNode* q;
    listNode* r;
    p = h->first;               
    q = NULL;
    while(p != NULL){
        r = q;
        q = p;
        p = p->link;
        q->link = r;
    }
    h->first = q;
    return 0;
}
void printList(headNode* h){    // 리스트 출력 함수
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if(h == NULL) {
        printf("Nothing to print....\n");
        return;
    }
    p = h->first;

    while(p != NULL){
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->link;
        i++;
    }
    printf("  items = %d\n", i);
}
