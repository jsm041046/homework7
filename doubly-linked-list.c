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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node { //��� ����ü ����
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head { //����� �� ���κ��� ����Ű�� ��� ����
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�ʹ� �ٸ��� �����͸� �Ҵ��ؼ� ��ȯ�ϴ� ���� �ƴ� �ּҸ� ���� ó������ �� HeadNode�� �Ҵ��� �ϴ� ����̴�.*/
int initialize(headNode** h); //���� ����Ʈ�� �� �պκ��� �ʱ�ȭ

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� �������ڸ�, initialize�Լ��� ���ʿ� ���� ��Ŀ� ���̰� ���� �� ����� ���� ������ �Ȱ��� ������� �Ҵ� ������ �����ϴ�.
        - ����, ���������͸� ���� �����Ѵٸ�, �׳� �ѹ� ������ ���� HeadNode�� �����ϸ� �ȴ�. */
int freeList(headNode* h);

int insertNode(headNode* h, int key); //���� ����Ʈ�� �߰��� key�� ������ 
int insertLast(headNode* h, int key); //���� ����Ʈ�� �� �ڿ� key�� ������
int insertFirst(headNode* h, int key);//���� ����Ʈ�� ù��°�� key�� ������
int deleteNode(headNode* h, int key); //���� ����Ʈ�� key���Ҹ� ������
int deleteLast(headNode* h); //���� ����Ʈ�� �������� ��ġ�� ���Ҹ� ������
int deleteFirst(headNode* h); //���� ����Ʈ�� ù��° ���Ҹ� ������
int invertList(headNode* h); //���� ����Ʈ�� ������ ������ �ٲ�

void printList(headNode* h); //���� ����Ʈ�� ���


int main()
{
	char command; //����� ���� ���ں��� ����
	int key; //�ӽ÷� ���Ұ��� ������ ����
	headNode* headnode=NULL; //���� ����Ʈ�� �� ���� ����ų ����
    printf("[----- 2021041046 ������ -----]\n"); //�й�, �̸� ���
	do{
		printf("----------------------------------------------------------------\n"); //�ȳ�
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //��ɾ� �Է� ����

		switch(command) { //�Էµ� ��ɾ ���� �б�
		case 'z': case 'Z':
			initialize(&headnode); //���� ����Ʈ �ʱ�ȭ
			break;
		case 'p': case 'P':
			printList(headnode); //���� ����Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			insertNode(headnode, key); //���� ����Ʈ �߰��� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			deleteNode(headnode, key); //���� ����Ʈ���� ���ϴ� ���� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			insertLast(headnode, key); //���� ����Ʈ�� �������� ���� �Է�
			break;
		case 'e': case 'E':
			deleteLast(headnode); //���� ����Ʈ�� ������ ���� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			insertFirst(headnode, key); //���� ����Ʈ�� ù��°�� ���� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode); //���� ����Ʈ�� ù��° ���� ����
			break;
		case 'r': case 'R':
			invertList(headnode); //���� ����Ʈ�� ������ ������ ��ȯ
			break;
		case 'q': case 'Q':
			freeList(headnode); //���� ����Ʈ�� �޸� �Ҵ� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //�Է¿� Q ���� ������ ������ ��������

	return 1;
}


int initialize(headNode** h) {
    /*  singly-linked-list�� initialize�ʹ� �ٸ��� �����͸� �Ҵ��ؼ� ��ȯ�ϴ� ���� �ƴ� �ּҸ� ���� ó������ �� HeadNode�� �Ҵ��� �ϴ� ����̴�.*/
    //���޹��� �����Ͱ� NULL�� �ƴϸ� freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ����
    if(*h != NULL)
        freeList(*h);
    //�ּҰ��� ���� ���޹��� headNode�� �޸𸮸� �Ҵ���
    *h = (headNode*)malloc(sizeof(headNode));
    (*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
    /* - initialize�� �� �ٸ��� �̱������ͷ� �ϴ��� �������ڸ�, initialize�Լ��� ���ʿ� ���� ��Ŀ� ���̰� ���� �� ����� ���� ������ �Ȱ��� ������� �Ҵ� ������ �����ϴ�.
       - ����, ���������͸� ���� �����Ѵٸ�, �׳� �ѹ� ������ ���� HeadNode�� �����ϸ� �ȴ�. */
	listNode* p = h->first;

    //�ӽ÷� prev�����͸� ���� �� �ΰ��� �����͸� �̿��� p�� ���� ��ũ�� �����ϰ� prev�� ������ ������ �޸𸮸� �����ϴ� ���� p�� ���� ����Ű�� ���� �� ���� �ݺ���
	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
    //������ ���ԵǴ� ���Ҹ� ����
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
    //�ӽ÷� ���� �ִ� node���� ���� �� �Ҵ��ϰ�, ���Ұ��� ������
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
    //���� ���� ������ ����Ű�� p�����ͺ����� ����
    listNode* p = h->first;
    if(p != NULL) //���Ұ� ���� ���
    {
        while (p->rlink != NULL) //p�� ���� ���Ұ� NULL�� ���� �� ���� �ݺ�
        {
            p = p->rlink; //p�� ���� ��ġ�� �̵���Ŵ
        } 
    }
    
    if(p != NULL) //��ġ�� �� ���� �ƴ� ���
    {
        //������ ��ġ�� ���� �߰�
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
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
    //���� ���� ������ ����Ű�� p�����ͺ����� ����
    listNode* p = h->first;
    if(p != NULL) //���Ұ� ���� ���
    {
        while (p->rlink != NULL) //p�� ���� ���Ұ� NULL�� ���� �� ���� �ݺ�
        {
            p = p->rlink; //p�� ���� ��ġ�� �̵���Ŵ
        } 
    }
    if(p != NULL) //���� p�� ������ ���
    {
        if(p->llink != NULL) //���� ���Ұ� ������ ���
            p->llink->rlink = NULL; //���� ������ ��ũ�� ����
        else
            h->first = NULL; //���� ���Ұ� ���� ��� ��带 �ʱ�ȭ
        free(p); //���� p�� �޸� �Ҵ� ����
    }

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
    //�ӽ÷� ���� �ִ� node���� ���� �� �Ҵ��ϰ�, ���Ұ��� ������
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
    //�Ҵ�� ��带 ��忡 ���� ��ũ�� �����ϰ�, ����� ���� ����� ���� ��ũ�� ���ο��� �����ϰ�, ����� ��ũ�� �ش� ��忡 ������
    node->rlink = h->first;
    node->llink = NULL;
    if(node->rlink != NULL) //���� ���Ұ� ������ ���
        node->rlink->llink = node; //���� ������ ���� ��ũ�� �ش� ��忡 ����
	h->first = node;

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
    //�ӽ� ������ p����
    listNode* p = h->first;
    if(h->first != NULL) //���� ����Ʈ�� ��尡 ������ ���(��尡 �ִ� = ���� ����Ʈ�� ���� �����Ѵ�)
    {
        h->first = h->first->rlink; //�� �� ���Ҹ� ���� ���ҷ� ����
        if(h->first != NULL) //���� �� ���� ��尡 ���� ���� ���
            h->first->llink = NULL; //���� �� �տ� ���� ������ ���� ��ũ�� ���� ����
        free(p); //������ �� �� ���Ҵ� �Ҵ� ����
    }
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
    //���� ���� ������ ����Ű�� p�����ͺ����� ����
    listNode* p = h->first;
    listNode* temp;
    while (p != NULL) //p�� NULL�� ���� �� ���� �ݺ�
    {
        //p�� ��ũ ������ ��ȯ �� p�� ���� ���ҷ� �̵�
        temp = p->rlink;
        p->rlink = p->llink;
        p->llink = temp;
        if(p->llink == NULL) //���� ���Ұ� ���� ��� (p�� ��ũ�� �ٲ�����Ƿ� p�� �������Ҵ� ���ʿ� �޷��ִ�)
            h->first = p; //��带 �� ������ �ű��
        p = p->llink; //���� ���ҷ� p�� �̵�
    }
    
	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
    //�ӽ÷� ���� �ִ� node���� ���� �� �Ҵ��ϰ�, ���Ұ��� ������
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
    //���� ���� ������ ����Ű�� p�����ͺ����� ����, NULL�� ����Ű�� prev�����ͺ��� ����
    listNode* p = h->first;
    listNode* prev = NULL;
    while (p != NULL && p->key <= node->key) //p�� NULL�� �����ų� p�� ���Ұ��� node���� Ŀ�� �� ���� �ݺ�
    {
        prev = p;
        p = p->rlink; //prev���� p�� ���ϰ� �ϰ�, p�� ���� ��ġ�� �̵���Ŵ
    } 
    if(prev != NULL) //��ġ�� �� ���� �ƴ� ���
    {
        //������ ��ġ�� ���� �߰�
        node->rlink = prev->rlink;
        if(node->rlink != NULL) //���� ��ũ�� ���� ���
            node->rlink->llink = node; //���� ��ũ�� ���� ��ũ�� �ش� ��带 ����Ű�� ��
        node->llink = prev;
        prev->rlink = node;
    } else {
        node->rlink = h->first;
        node->llink = NULL;
        if(h->first != NULL) //ù��° ���Ұ� ���� ���
            h->first->llink = node;
        h->first = node;
    }
    
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
    //���� ���� ������ ����Ű�� p�����ͺ����� ����, NULL�� ����Ű�� prev�����ͺ��� ����
    listNode* p = h->first;
    listNode* prev = NULL;
    while (p != NULL && p->key != key) //p�� NULL�� �����ų� p�� ���Ұ��� key�� ������ �� ���� �ݺ�
    {
        prev = p;
        p = p->rlink; //prev���� p�� ���ϰ� �ϰ�, p�� ���� ��ġ�� �̵���Ŵ
    } 
    if(p ==  NULL)
    {
        printf("List don't have that element!\n"); //�ش� ���Ұ� ������ �ȳ�
        return -1; //������ ���� ����
    }
    if(prev != NULL) { //���� ���Ұ� ���� ���
    //���� ������ ��ũ�� ���� ���ҷ� �ΰ�����
        prev->rlink = p->rlink;
        if(p->rlink != NULL) //���� ���Ұ� ������ ���
            p->rlink->llink = prev;
    } else {
        h->first = p->rlink; //ù��° ��ũ�� ���� ���ҷ� �ΰ�����
        p->llink = NULL; //���� ������ ������ ����
    }
    free(p); //���� p�� �޸� �Ҵ� ����

	return 1;
}