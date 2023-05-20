/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 

typedef struct Node {                              
	int key;
	struct Node* llink;                           //���� ����� �ּ�
	struct Node* rlink;                           //������ ����� �ּ�
	
 } listNode;

int initialize(listNode** h);                     // ����Ʈ �ʱ�ȭ
int freeList(listNode* h);                        // ����Ʈ �Ҵ�����
int insertLast(listNode* h, int key);             // �ǵڿ� ��� ����
int deleteLast(listNode* h);                      // �ǵھ� ��� ���� 
int insertFirst(listNode* h, int key);            // �Ǿտ� ��� ����
int deleteFirst(listNode* h);                     // �Ǿտ� ��� ����
int invertList(listNode* h);                      // ����Ʈ ���� �Ųٷ�

int insertNode(listNode* h, int key);             // key�� ������������ ��� ����
int deleteNode(listNode* h, int key);             // key���� ���� ��� ����

void printList(listNode* h);                      // ����Ʈ ���



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;//�����
	printf("[-----------2022041047 ������------------]\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
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

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) //����Ʈ �ʱ�ȭ
{    

		if (*h != NULL)
		freeList(*h);             //����尡 ������� �ʴٸ� ���� ����Ʈ ����

	*h = (listNode*)malloc(sizeof(listNode));//��� ����Ҵ�
	
	//����� ��ũ�� ���� �ڽ��� ���� ����Ŵ
	(*h)->llink = *h;
	(*h)->rlink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h) //����Ʈ �Ҵ� ����
{   
	if (h == NULL) //�Ҵ������� ����Ʈ�� ���ٸ�  ����
	{
		printf("nothing to free.....\n");
		return 0;
	}

	while (h->llink != h) //�����ʿ��� ���� �Ҵ�����
	{
		deleteFirst(h);     
	}
	free(h);//������ �Ҵ�����

	return 0;
}



void printList(listNode* h) //����Ʈ ���
{
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {//����Ʈ�� ���������
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//ù��° ���� �̵�

	while (p != NULL && p != h) //p�� ����� ���̰ų�, ������� ���� ����
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;			//���������� �̵�
		i++;
	}
	printf("  items = %d\n", i);


	/*�ּ� ���*/
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);//��� ��� �� ���� ������ ��� �ּ� ���

	i = 0;
	p = h->rlink;//����� ������ ��� 
	while (p != NULL && p != h) {	//p�� ����� ���̰ų�, ������� ���� ����
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);//p�� ����Ű�� ����� �ּҿ� ���ʳ��, �����ʳ�� �ּ�
		p = p->rlink;//�������� �̵�
		i++;
	}

}


int insertLast(listNode* h, int key) {//�������� ��� ����
	if (h == NULL) {//����尡 ���������
		printf("you should initialize first \n"); 
		return 0;
	}
	if (h->llink == h) {//ù ��尡 ������
		insertFirst(h, key);//ù��� ����
		return 1;
	}
	listNode* p = (listNode*)malloc(sizeof(listNode));//p�� ��� �Ҵ�
	p->key = key;
	p->llink = h->llink; // p�� ���ʿ� ������ ���
	p->rlink = h; // p�� �����ʿ� ��� ���
	h->llink->rlink = p; // ����������� �����ʿ� p����
	h->llink = p;//����� ���ʿ� p����
	return 1;
}

int deleteLast(listNode* h) {// ������ ��� ����
		if (h == NULL || h->llink == h) {   //��尡 ����ְų� ��尡 ���������
		printf("nothing to delete\n");
		return 0;
	}

	if (h->rlink->rlink == h) {//ù��° ��� �ۿ� ������
		deleteFirst(h); //ù��� ����
		return 1;
	}
	listNode* p = h->llink; //p�� ����� ���ʳ�� �ֱ�              
	p->llink->rlink = p->rlink;  // p�� ���ʳ�忡 p�� �����ʳ�� ���� 
	h->llink = p->llink; //����� ���ʿ� p���ʳ�� �ֱ�
	p->rlink = p;// p������ ��忡 p
	p->llink = p; //p���� ��忡 p
	printf("Delete %d\n", p->key);
	free(p);//p����
	return 1;
}


int insertFirst(listNode* h, int key) { //�Ǿտ� ��� ����   
	if (h == NULL) {                       //��尡 �������� �ʾҴٸ�
		printf("initialize first\n");      
		return 0;
	}
	listNode *p = (listNode *)malloc(sizeof(listNode));//p�� ����Ҵ�
	p->key = key;
	p->llink = h;//p�� ���� ��� ��� �Ҵ�
	if (h->llink == h) {                   //p�� ù����
		h->llink = p;                     //����� ���ʿ� p���� 
	}
	else {                             //h�� �����ʳ�嵵 h���� 
		h->rlink->llink = p;           
	}
	p->rlink = h->rlink;               //���� ù��带 p�� �޳��� ����
	h->rlink = p;                      
	return 1;
}


int deleteFirst(listNode* h) {                       //ù��� ����
		if (h == NULL || h->llink == h) {                //��尡 ����ְų�, ù��尡 ������
		printf("nothing to delete\n");
		return 0;
	}

	listNode * temp = h->rlink;//ù��带 temp�� �Űܵ�
	h->rlink = temp->rlink; //�ι�°��带 ���Ϳ���
	if (temp->rlink == h) { //��尡 �Ѱ��ۿ� �����ٸ�
		h->llink = temp->llink;
	}
	else {                                         
		temp->rlink->llink = temp->llink;          //�ι�° ��带 ���Ϳ���
	}
	temp->rlink = temp;//�����Ϸ��� ��带 ��ͳ��� ����
	temp->llink = temp;
	printf("Delet %d\n", temp->key);
	free(temp);//��� ����
	return 1;

}


int invertList(listNode* h) {        //��� ������               
	if (h == NULL || h->llink == h) {             //��尡 ����ְų�, ù��尡 ������  
		printf("Empty List\n");
		return 0;
	}

	listNode *p = h->rlink;//p�� ù��� �ֱ�
	listNode *tail = NULL;
	listNode *middle = NULL;
	while (p != h) {        // middle->tail �� tail->middle �� �ٲٴ� ����                  
		tail = middle;
		middle = p;//��������ּ� middle�� �ֱ�
		p = p->rlink;//p�� ������� �ֱ�
		if (tail != NULL) {                   
			tail->llink = middle;//tail�� ���� ��忡 middle
			middle->rlink = tail;//middle�� ������ ��忡 tail
		}
		if (middle->llink == h) { //ù�����            
			middle->rlink = h;//ù����� ������ ��ũ�� h�� ����
		}
	}
	h->llink = h->rlink;//����带 h�� ����Ű�� ù���� �ֱ�                 
	h->rlink = middle;//middle
	middle->llink = h;
	return 1;
}




int insertNode(listNode* h, int key) {//�������� ������
	if (h == NULL) {                  
		printf("initialize first\n"); 
		return 0;
	}
	listNode *node = h->rlink;//rlink�� ���� ��ũ
	listNode *prev = NULL;//llink�� ���� ��ũ
	listNode *p = NULL;//������ ���
	while (node->key < key && node != h) {//������ ����� �ڸ��� ã�� ������
		prev = node;//prev�� ���� ��� �ּҸ� �ְ�
		node = node->rlink;//�������� �̵�
	}
	if (prev == NULL) {     //���̸� ��� �ڿ� ����
		insertFirst(h, key);
		return 1;
	}
	if (node == h) {        //��常 �����Ǿ��ִٸ�
		insertLast(h, key);
		return 1;
	}
	p = (listNode*)malloc(sizeof(listNode));//p�� ��� �Ҵ�
	p->key = key;//p�� Ű�� �ֱ�
	prev->rlink = p;            //������忡 p����           
	node->llink = p;//���ĳ�忡 p����
	p->llink = prev;//p���ʿ� ������忬��
	p->rlink = node;//p�����ʿ� ���ĳ�忬��

	return 1;
}


int deleteNode(listNode* h, int key) {	//Ű ���� �ش��ϴ� ������
	if (h == NULL || h->llink == h) { //������ ��尡 ������
		printf("Empty List\n");
		return 0;
	}

	listNode*node = h->rlink;//���� �����
	listNode*prev = NULL;//������� ��ũ
	while (node->key != key && node != h) {//������ ��� ã�������� �̵�
		prev = node;
		node = node->rlink;
	}
	if (prev == NULL) { //ù��尡 �������
		deleteFirst(h);
		return 1;
	}
	if (node == h) {    //��尡 �������� �ʴٸ�
		printf("%d is not Exist\n", key);
		return 0;
	}
	prev->rlink = node->rlink;//��������� �����ʿ� ������� ����� ������ ��� ����
	node->rlink->llink = prev;//������� ����� ������ ��� ������ ������带 ����Ű�� ����
	node->rlink = node;       //������� ��尡 ��ͳ�尡 �ǰԲ� ����
	node->llink = node;
	printf("Delet %d\n", key);
	free(node);//node ����
	return 1;
}