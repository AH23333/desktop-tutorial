#include <stdio.h>
#include <stdlib.h>

#define MAX INT_MAX - 1

//���������Ż�

//ԭ��
/*����ͼ
	  ��	A  B  C  D  E  F
	A	0, 1, 1, 1, 0, 0,
	B	0, 0, 0, 0, 0, 0,
	C	0, 1, 0, 0, 1, 0,
	D	0, 0, 0, 0, 1, 0,
	E	0, 0, 0, 0, 0, 0,
	F	0, 0, 0, 1, 1, 0
	*/
//�涨�ڽӾ�����б�ʾ����ĳ��ȣ��б�ʾ��������
//ÿ���ҳ����Ϊ0�Ķ��㣬ɾ���ö��㣬�����ڽӾ���ֱ�����ж��㶼��ɾ��
//�������ж���û�б�ɾ����˵���л�

//ɸ��һ��Ϊf
/*����ͼ
	  ��	A  B  C  D  E  F
	A	0, 1, 1, 1, 0,  ,
	B	0, 0, 0, 0, 0,  ,
	C	0, 1, 0, 0, 1,  ,
	D	0, 0, 0, 0, 1,  ,
	E	0, 0, 0, 0, 0,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//ɸ�ڶ���Ϊa
/*����ͼ
	  ��	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 , 0, 0, 0, 0,  ,
	C	 , 1, 0, 0, 1,  ,
	D	 , 0, 0, 0, 1,  ,
	E	 , 0, 0, 0, 0,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//ɸ������Ϊd
/*����ͼ
	  ��	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 , 0, 0,  , 0,  ,
	C	 , 1, 0,  , 1,  ,
	D	 ,  ,  ,  ,  ,  ,
	E	 , 0, 0,  , 0,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//ɸ���Ĵ�Ϊc
/*����ͼ
	  ��	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 , 0,  ,  , 0,  ,
	C	 ,  ,  ,  ,  ,  ,
	D	 ,  ,  ,  ,  ,  ,
	E	 , 0,  ,  , 0,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//ɸ�����Ϊe
/*����ͼ
	  ��	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 , 0,  ,  ,  ,  ,
	C	 ,  ,  ,  ,  ,  ,
	D	 ,  ,  ,  ,  ,  ,
	E	 ,  ,  ,  ,  ,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//ɸ������Ϊb
/*����ͼ
	  ��	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 ,  ,  ,  ,  ,  ,
	C	 ,  ,  ,  ,  ,  ,
	D	 ,  ,  ,  ,  ,  ,
	E	 ,  ,  ,  ,  ,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//Ȼ��û��ʣ�µ�����˵��û�л�

//����C�ﲻ�öԾ�����в��������Կ����ȰѾ�������������һ��Ȼ���ٽ��в���

//�ȰѾ�������������һ����һ˵һ�������ۻ���
/*����ͼ
	  ��	A  B  C  D  E  F
	A	1, 2, 2, 2, 1, 1,
	B	1, 1, 1, 1, 1, 1,
	C	1, 2, 1, 1, 2, 1,
	D	1, 1, 1, 1, 2, 1,
	E	1, 1, 1, 1, 1, 1,
	F	1, 1, 1, 2, 2, 1,
	*/

//����Ĳ�����ǰ��һ����ֻ������ɾ���������ɸ�ֵΪ0

typedef struct Graph {
	char* vexs;//����
	int** arcs;//��
	int vexNum;
	int arcNum;
} Graph;

Graph* init_graph(int vexNum);

void create_graph(Graph* graph, char* vexs, int* arcs);
void topological_sort(Graph* graph);
void DFS(Graph* graph, int* visited, int index);

int check_colume(Graph* graph, int index);

int main(void)
{
	Graph* G = init_graph(6);
	/*����ͼ
	  ��	A  B  C  D  E  F
	A	0, 1, 1, 1, 0, 0,
	B	0, 0, 0, 0, 0, 0,
	C	0, 1, 0, 0, 1, 0,
	D	0, 0, 0, 0, 1, 0,
	E	0, 0, 0, 0, 0, 0,
	F	0, 0, 0, 1, 1, 0
	*/

	//visitedһά�����ʼ��
	int* visited = (int*)malloc(sizeof(int) * G->vexNum);
	if (!visited) {
		puts("visited malloc failed\n");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < G->vexNum; i++) {
		visited[i] = 0;
	}

	//ͼ�ڽӾ�����Ϣ
	int arcs[6][6] = {
		1, 2, 2, 2, 1, 1,
		1, 1, 1, 1, 1, 1,
		1, 2, 1, 1, 2, 1,
		1, 1, 1, 1, 2, 1,
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 2, 2, 1
	};

	create_graph(G, "ABCDEF", (int*)arcs);
	DFS(G, visited, 0);
	printf("\n");
	topological_sort(G);

	return EXIT_SUCCESS;
}

// ��������
void topological_sort(Graph* graph) {
	int* visited = (int*)malloc(sizeof(int) * graph->vexNum);	// ��������Ƿ��Ѵ���
	if (!visited) {
		puts("visited malloc failed\n");
		return;
	}

	for (int i = 0; i < graph->vexNum; i++) {
		visited[i] = 0;
	}

	int count = 0;  // ��¼������Ķ�����

	while (count < graph->vexNum) {
		int found = 0;  // ����Ƿ��ҵ����Ϊ0�Ķ���
		for (int i = 0; i < graph->vexNum; i++) {
			if (!visited[i] && check_colume(graph, i)) {  // ����ö���δ���������Ϊ0
				printf("%c\t", graph->vexs[i]);  // �������
				visited[i] = 1;  // ���Ϊ�Ѵ���
				count++;

				// ɾ���ö�����к��У���ֵ��Ϊ0��
				for (int j = 0; j < graph->vexNum; j++) {
					graph->arcs[j][i] = 1;  // ɾ����
					graph->arcs[i][j] = 1;  // ɾ����
				}
				found = 1;
				break;  // �ҵ�һ�����˳���ǰѭ��
			}
		}
		if (!found) {  // ���û���ҵ����Ϊ0�Ķ���
			printf("ͼ�д��ڻ����޷�����������������\n");
			return;
		}
	}
	printf("\n");
}

// ���ĳһ���Ƿ�ȫΪ0�����Ϊ0��
int check_colume(Graph* graph, int index) {
	for (int i = 0; i < graph->vexNum; i++) {
		if (graph->arcs[i][index] > 1) {  // ���������ֵΪ2��ʾ�б�
			return 0;  // ��������з���ֵ������0
		}
	}
	return 1;  // �������ȫΪ0������1
}

Graph* init_graph(int vexNum) {
	//��ʼ��ͼ�ṹ��
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	if (!graph) {
		puts("init_graph graph malloc failed\n");
		exit(EXIT_FAILURE);
	}

	graph->vexs = (char*)malloc(sizeof(char) * vexNum);
	if (!graph->vexs) {
		puts("ini_graph graph->vexs malloc failed\n");
		exit(EXIT_FAILURE);
	}

	graph->arcs = (int**)malloc(sizeof(int*) * vexNum);
	if (!graph->arcs) {
		puts("init_graph graph->arcs malloc failed\n");
		exit(EXIT_FAILURE);
	}

	//��ʼ����������vexs���ڽӾ���arcs
	for (int i = 0; i < vexNum; i++) {
		graph->arcs[i] = (int*)malloc(sizeof(int) * vexNum);
		if (!graph->arcs[i]) {
			printf("init_graph graph->arcs[%d] malloc failed\n", i);
			exit(EXIT_FAILURE);
		}
	}

	graph->vexNum = vexNum;
	graph->arcNum = 0;

	return graph;
}

void create_graph(Graph* graph, char* vexs, int* arcs) {
	for (int i = 0; i < graph->vexNum; i++) {	//�����ά�ڽӾ���
		graph->vexs[i] = vexs[i];
		for (int j = 0; j < graph->vexNum; j++) {
			graph->arcs[i][j] = *(arcs + i * graph->vexNum + j);	//��һά����arcsת��Ϊgraph->arcs��ά����
			if (graph->arcs[i][j] && graph->arcs[i][j] != MAX - 1) graph->arcNum++;
		}
	}
	graph->arcNum /= 2;
}

void DFS(Graph* graph, int* visited, int index) {
	printf("%c\t", graph->vexs[index]);
	visited[index] = 1;
	for (int i = 0; i < graph->vexNum; i++) {
		if (graph->arcs[index][i] > 0 && graph->arcs[index][i] != MAX && !visited[i]) DFS(graph, visited, i);
	}
}