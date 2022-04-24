/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node { //노드 구조체 정의
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head { //노드의 맨 끝부분을 가르키는 헤더 정의
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와는 다르게 포인터를 할당해서 반환하는 것이 아닌 주소를 통해 처음부터 원 HeadNode에 할당을 하는 방식이다.*/
int initialize(headNode** h); //연결 리스트의 맨 앞부분을 초기화

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 설명하자면, initialize함수가 애초에 전달 방식에 차이가 있을 뿐 결과는 같기 때문에 똑같은 방식으로 할당 해제가 가능하다.
        - 또한, 이중포인터를 통해 전달한다면, 그냥 한번 참조를 통해 HeadNode에 접근하면 된다. */
int freeList(headNode* h);

int insertNode(headNode* h, int key); //연결 리스트의 중간에 key를 삽입함 
int insertLast(headNode* h, int key); //연결 리스트의 맨 뒤에 key를 삽입함
int insertFirst(headNode* h, int key);//연결 리스트에 첫번째에 key를 삽입함
int deleteNode(headNode* h, int key); //연결 리스트의 key원소를 제거함
int deleteLast(headNode* h); //연결 리스트의 마지막에 위치한 원소를 제거함
int deleteFirst(headNode* h); //연결 리스트의 첫번째 원소를 제거함
int invertList(headNode* h); //연결 리스트의 순서를 역으로 바꿈

void printList(headNode* h); //연결 리스트의 출력


int main()
{
	char command; //명령을 받을 문자변수 선언
	int key; //임시로 원소값을 저장할 변수
	headNode* headnode=NULL; //연결 리스트의 맨 앞을 가르킬 변수
    printf("[----- 2021041046 전설민 -----]\n"); //학번, 이름 출력
	do{
		printf("----------------------------------------------------------------\n"); //안내
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어 입력 받음

		switch(command) { //입력된 명령어에 따른 분기
		case 'z': case 'Z':
			initialize(&headnode); //연결 리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode); //연결 리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); //원소값 입력
			insertNode(headnode, key); //연결 리스트 중간에 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //원소값 입력
			deleteNode(headnode, key); //연결 리스트에서 원하는 원소 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); //원소값 입력
			insertLast(headnode, key); //연결 리스트의 마지막에 원소 입력
			break;
		case 'e': case 'E':
			deleteLast(headnode); //연결 리스트의 마지막 원소 제거
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); //원소값 입력
			insertFirst(headnode, key); //연결 리스트의 첫번째에 원소 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); //연결 리스트의 첫번째 원소 제거
			break;
		case 'r': case 'R':
			invertList(headnode); //연결 리스트의 순서를 역으로 전환
			break;
		case 'q': case 'Q':
			freeList(headnode); //연결 리스트의 메모리 할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //입력에 Q 값이 들어오면 루프를 빠져나옴

	return 1;
}


int initialize(headNode** h) {
    /*  singly-linked-list의 initialize와는 다르게 포인터를 할당해서 반환하는 것이 아닌 주소를 통해 처음부터 원 HeadNode에 할당을 하는 방식이다.*/
    //전달받은 포인터가 NULL이 아니면 freeNode를 호출하여 할당된 메모리 해제
    if(*h != NULL)
        freeList(*h);
    //주소값을 통해 전달받은 headNode에 메모리를 할당함
    *h = (headNode*)malloc(sizeof(headNode));
    (*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
    /* - initialize와 왜 다르게 싱글포인터로 하는지 설명하자면, initialize함수가 애초에 전달 방식에 차이가 있을 뿐 결과는 같기 때문에 똑같은 방식으로 할당 해제가 가능하다.
       - 또한, 이중포인터를 통해 전달한다면, 그냥 한번 참조를 통해 HeadNode에 접근하면 된다. */
	listNode* p = h->first;

    //임시로 prev포인터를 선언 후 두개의 포인터를 이용해 p는 다음 링크를 참조하고 prev는 지나온 원소의 메모리를 해제하는 것을 p가 값을 가르키지 않을 때 까지 반복함
	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
    //마지막 남게되는 원소를 해제
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    //임시로 값을 넣는 node변수 선언 후 할당하고, 원소값을 대입함
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
    //헤드와 같은 내용을 가르키는 p포인터변수를 선언
    listNode* p = h->first;
    if(p != NULL) //원소가 있을 경우
    {
        while (p->rlink != NULL) //p의 다음 원소가 NULL이 나올 때 까지 반복
        {
            p = p->rlink; //p를 다음 위치로 이동시킴
        } 
    }
    
    if(p != NULL) //위치가 맨 앞이 아닐 경우
    {
        //지정된 위치에 원소 추가
        p->rlink = node;
        node->llink = p;
        node->rlink = NULL;
    } else {
        h->first = node;
        node->rlink = NULL;
    }

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    //헤드와 같은 내용을 가르키는 p포인터변수를 선언
    listNode* p = h->first;
    if(p != NULL) //원소가 있을 경우
    {
        while (p->rlink != NULL) //p의 다음 원소가 NULL이 나올 때 까지 반복
        {
            p = p->rlink; //p를 다음 위치로 이동시킴
        } 
    }
    if(p != NULL) //원소 p가 존재할 경우
    {
        if(p->llink != NULL) //이전 원소가 존재할 경우
            p->llink->rlink = NULL; //이전 원소의 링크를 끊음
        else
            h->first = NULL; //이전 원소가 없을 경우 헤드를 초기화
        free(p); //원소 p는 메모리 할당 해제
    }

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
    //임시로 값을 넣는 node변수 선언 후 할당하고, 원소값을 대입함
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
    //할당된 노드를 헤드에 우측 링크로 연결하고, 연결된 우측 노드의 좌측 링크를 본인에게 연결하고, 헤드의 링크를 해당 노드에 연결함
    node->rlink = h->first;
    node->llink = NULL;
    if(node->rlink != NULL) //다음 원소가 존재할 경우
        node->rlink->llink = node; //다음 원소의 좌측 링크를 해당 노드에 연결
	h->first = node;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    //임시 포인터 p선언
    listNode* p = h->first;
    if(h->first != NULL) //연결 리스트의 헤드가 존재할 경우(헤드가 있다 = 연결 리스트에 값이 존재한다)
    {
        h->first = h->first->rlink; //맨 앞 원소를 다음 원소로 이전
        if(h->first != NULL) //이전 한 후의 헤드가 값이 있을 경우
            h->first->llink = NULL; //새로 맨 앞에 있을 원소의 좌측 링크를 연결 해제
        free(p); //기존의 맨 앞 원소는 할당 해제
    }
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    //헤드와 같은 내용을 가르키는 p포인터변수를 선언
    listNode* p = h->first;
    listNode* temp;
    while (p != NULL) //p가 NULL이 나올 때 까지 반복
    {
        //p의 링크 방향을 교환 후 p를 다음 원소로 이동
        temp = p->rlink;
        p->rlink = p->llink;
        p->llink = temp;
        if(p->llink == NULL) //다음 원소가 없을 경우 (p의 링크가 바뀌었으므로 p의 다음원소는 왼쪽에 달려있다)
            h->first = p; //헤드를 맨 끝으로 옮긴다
        p = p->llink; //다음 원소로 p를 이동
    }
    
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    //임시로 값을 넣는 node변수 선언 후 할당하고, 원소값을 대입함
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
    //헤드와 같은 내용을 가르키는 p포인터변수를 선언, NULL을 가르키는 prev포인터변수 선언
    listNode* p = h->first;
    listNode* prev = NULL;
    while (p != NULL && p->key <= node->key) //p가 NULL이 나오거나 p의 원소값이 node보다 커질 때 까지 반복
    {
        prev = p;
        p = p->rlink; //prev값을 p를 향하게 하고, p를 다음 위치로 이동시킴
    } 
    if(prev != NULL) //위치가 맨 앞이 아닐 경우
    {
        //지정된 위치에 원소 추가
        node->rlink = prev->rlink;
        if(node->rlink != NULL) //우측 링크가 있을 경우
            node->rlink->llink = node; //우측 링크의 좌측 링크가 해당 노드를 가르키게 함
        node->llink = prev;
        prev->rlink = node;
    } else {
        node->rlink = h->first;
        node->llink = NULL;
        if(h->first != NULL) //첫번째 원소가 있을 경우
            h->first->llink = node;
        h->first = node;
    }
    
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    //헤드와 같은 내용을 가르키는 p포인터변수를 선언, NULL을 가르키는 prev포인터변수 선언
    listNode* p = h->first;
    listNode* prev = NULL;
    while (p != NULL && p->key != key) //p가 NULL이 나오거나 p의 원소값이 key와 같아질 때 까지 반복
    {
        prev = p;
        p = p->rlink; //prev값을 p를 향하게 하고, p를 다음 위치로 이동시킴
    } 
    if(p ==  NULL)
    {
        printf("List don't have that element!\n"); //해당 원소가 없음을 안내
        return -1; //비정상 종료 리턴
    }
    if(prev != NULL) { //이전 원소가 있을 경우
    //이전 원소의 링크를 다음 원소로 인가해줌
        prev->rlink = p->rlink;
        if(p->rlink != NULL) //다음 원소가 존재할 경우
            p->rlink->llink = prev;
    } else {
        h->first = p->rlink; //첫번째 링크를 다음 원소로 인가해줌
        p->llink = NULL; //이전 원소의 연결을 끊음
    }
    free(p); //원소 p는 메모리 할당 해제

	return 1;
}