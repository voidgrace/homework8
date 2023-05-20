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
	struct Node* llink;                           //왼쪽 노드의 주소
	struct Node* rlink;                           //오른쪽 노드의 주소
	
 } listNode;

int initialize(listNode** h);                     // 리스트 초기화
int freeList(listNode* h);                        // 리스트 할당해제
int insertLast(listNode* h, int key);             // 맨뒤에 노드 삽입
int deleteLast(listNode* h);                      // 맨뒤애 노드 삭제 
int insertFirst(listNode* h, int key);            // 맨앞에 노드 삽입
int deleteFirst(listNode* h);                     // 맨앞에 노드 삭제
int invertList(listNode* h);                      // 리스트 순서 거꾸로

int insertNode(listNode* h, int key);             // key값 오름차순으로 노드 삽입
int deleteNode(listNode* h, int key);             // key값과 같은 노드 삭제

void printList(listNode* h);                      // 리스트 출력



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;//헤드노드
	printf("[-----------2022041047 강은혜------------]\n");
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


int initialize(listNode** h) //리스트 초기화
{    

		if (*h != NULL)
		freeList(*h);             //헤드노드가 비어있지 않다면 기존 리스트 해제

	*h = (listNode*)malloc(sizeof(listNode));//헤드 노드할당
	
	//헤드의 링크를 전부 자신을 향해 가리킴
	(*h)->llink = *h;
	(*h)->rlink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h) //리스트 할당 해제
{   
	if (h == NULL) //할당해제할 리스트가 없다면  리턴
	{
		printf("nothing to free.....\n");
		return 0;
	}

	while (h->llink != h) //오른쪽에서 부터 할당해제
	{
		deleteFirst(h);     
	}
	free(h);//헤더노드 할당해제

	return 0;
}



void printList(listNode* h) //리스트 출력
{
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {//리스트가 비어있을때
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;//첫번째 노드로 이동

	while (p != NULL && p != h) //p가 노드의 끝이거나, 비어있지 않을 동안
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;			//오른쪽으로 이동
		i++;
	}
	printf("  items = %d\n", i);


	/*주소 출력*/
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);//헤드 노드 및 왼쪽 오른쪽 노드 주소 출력

	i = 0;
	p = h->rlink;//헤드의 오른쪽 노드 
	while (p != NULL && p != h) {	//p가 노드의 끝이거나, 비어있지 않을 동안
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);//p가 가리키는 노드의 주소와 왼쪽노드, 오른쪽노드 주소
		p = p->rlink;//다음노드로 이동
		i++;
	}

}


int insertLast(listNode* h, int key) {//마지막에 노드 연결
	if (h == NULL) {//헤드노드가 비어있을때
		printf("you should initialize first \n"); 
		return 0;
	}
	if (h->llink == h) {//첫 노드가 없을때
		insertFirst(h, key);//첫노드 삽입
		return 1;
	}
	listNode* p = (listNode*)malloc(sizeof(listNode));//p에 노드 할당
	p->key = key;
	p->llink = h->llink; // p의 왼쪽에 마지막 노드
	p->rlink = h; // p의 오른쪽에 헤드 노드
	h->llink->rlink = p; // 마지막노드의 오른쪽에 p연결
	h->llink = p;//헤드의 왼쪽에 p연결
	return 1;
}

int deleteLast(listNode* h) {// 마지막 노드 삭제
		if (h == NULL || h->llink == h) {   //헤드가 비어있거나 노드가 비어있으면
		printf("nothing to delete\n");
		return 0;
	}

	if (h->rlink->rlink == h) {//첫번째 노드 밖에 없을때
		deleteFirst(h); //첫노드 삭제
		return 1;
	}
	listNode* p = h->llink; //p에 헤드의 왼쪽노드 넣기              
	p->llink->rlink = p->rlink;  // p의 왼쪽노드에 p의 오른쪽노드 연결 
	h->llink = p->llink; //헤드의 왼쪽에 p왼쪽노드 넣기
	p->rlink = p;// p오른쪽 노드에 p
	p->llink = p; //p왼쪽 노드에 p
	printf("Delete %d\n", p->key);
	free(p);//p해제
	return 1;
}


int insertFirst(listNode* h, int key) { //맨앞에 노드 삽입   
	if (h == NULL) {                       //헤드가 생성되지 않았다면
		printf("initialize first\n");      
		return 0;
	}
	listNode *p = (listNode *)malloc(sizeof(listNode));//p에 노드할당
	p->key = key;
	p->llink = h;//p의 왼쪽 노드 헤드 할당
	if (h->llink == h) {                   //p가 첫노드면
		h->llink = p;                     //헤드의 왼쪽에 p연결 
	}
	else {                             //h의 오른쪽노드도 h연결 
		h->rlink->llink = p;           
	}
	p->rlink = h->rlink;               //원래 첫노드를 p의 뒷노드로 연결
	h->rlink = p;                      
	return 1;
}


int deleteFirst(listNode* h) {                       //첫노드 삭제
		if (h == NULL || h->llink == h) {                //헤드가 비어있거나, 첫노드가 없으면
		printf("nothing to delete\n");
		return 0;
	}

	listNode * temp = h->rlink;//첫노드를 temp에 옮겨둠
	h->rlink = temp->rlink; //두번째노드를 헤드와연결
	if (temp->rlink == h) { //노드가 한개밖에 없었다면
		h->llink = temp->llink;
	}
	else {                                         
		temp->rlink->llink = temp->llink;          //두번째 노드를 헤드와연결
	}
	temp->rlink = temp;//삭제하려는 노드를 재귀노드로 변경
	temp->llink = temp;
	printf("Delet %d\n", temp->key);
	free(temp);//노드 삭제
	return 1;

}


int invertList(listNode* h) {        //노드 뒤집기               
	if (h == NULL || h->llink == h) {             //헤드가 비어있거나, 첫노드가 없으면  
		printf("Empty List\n");
		return 0;
	}

	listNode *p = h->rlink;//p에 첫노드 넣기
	listNode *tail = NULL;
	listNode *middle = NULL;
	while (p != h) {        // middle->tail 을 tail->middle 로 바꾸는 느낌                  
		tail = middle;
		middle = p;//이전노드주소 middle에 넣기
		p = p->rlink;//p에 다음노드 넣기
		if (tail != NULL) {                   
			tail->llink = middle;//tail의 왼쪽 노드에 middle
			middle->rlink = tail;//middle의 오른쪽 노드에 tail
		}
		if (middle->llink == h) { //첫노드라면            
			middle->rlink = h;//첫노드의 오른쪽 링크를 h로 연결
		}
	}
	h->llink = h->rlink;//끝노드를 h가 가리키는 첫노드로 넣기                 
	h->rlink = middle;//middle
	middle->llink = h;
	return 1;
}




int insertNode(listNode* h, int key) {//오름차순 노드삽입
	if (h == NULL) {                  
		printf("initialize first\n"); 
		return 0;
	}
	listNode *node = h->rlink;//rlink에 넣을 링크
	listNode *prev = NULL;//llink에 넣을 링크
	listNode *p = NULL;//삽입할 노드
	while (node->key < key && node != h) {//삽입할 노드의 자리를 찾을 때까지
		prev = node;//prev에 현재 노드 주소를 넣고
		node = node->rlink;//다음노드로 이동
	}
	if (prev == NULL) {     //끝이면 노드 뒤에 삽입
		insertFirst(h, key);
		return 1;
	}
	if (node == h) {        //헤드만 생성되어있다면
		insertLast(h, key);
		return 1;
	}
	p = (listNode*)malloc(sizeof(listNode));//p에 노드 할당
	p->key = key;//p에 키값 넣기
	prev->rlink = p;            //이전노드에 p연결           
	node->llink = p;//이후노드에 p연결
	p->llink = prev;//p왼쪽에 이전노드연결
	p->rlink = node;//p오른쪽에 이후노드연결

	return 1;
}


int deleteNode(listNode* h, int key) {	//키 값에 해당하는 노드삭제
	if (h == NULL || h->llink == h) { //삭제할 노드가 없으면
		printf("Empty List\n");
		return 0;
	}

	listNode*node = h->rlink;//삭제 대상노드
	listNode*prev = NULL;//이전노드 링크
	while (node->key != key && node != h) {//삭제할 노드 찾을때까지 이동
		prev = node;
		node = node->rlink;
	}
	if (prev == NULL) { //첫노드가 대상노드라면
		deleteFirst(h);
		return 1;
	}
	if (node == h) {    //노드가 존재하지 않다면
		printf("%d is not Exist\n", key);
		return 0;
	}
	prev->rlink = node->rlink;//이전노드의 오른쪽에 삭제대상 노드의 오른쪽 노드 연결
	node->rlink->llink = prev;//삭제대상 노드의 오른쪽 노드 왼쪽이 이전노드를 가리키게 연결
	node->rlink = node;       //삭제대상 노드가 재귀노드가 되게끔 연결
	node->llink = node;
	printf("Delet %d\n", key);
	free(node);//node 삭제
	return 1;
}