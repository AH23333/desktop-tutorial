#include <stdio.h>
#include <stdlib.h>

#define MAX INT_MAX - 1

//拓扑排序优化
//optimization of topology sort

//原理 theory
/*有向图 digraph
	  →	A  B  C  D  E  F
	A	0, 1, 1, 1, 0, 0,
	B	0, 0, 0, 0, 0, 0,
	C	0, 1, 0, 0, 1, 0,
	D	0, 0, 0, 0, 1, 0,
	E	0, 0, 0, 0, 0, 0,
	F	0, 0, 0, 1, 1, 0
	*/
//规定邻接矩阵的行表示顶点的出度，列表示顶点的入度
//We specify that the rows of the adjacency matrix represent the outgoing degree and the columms represent the incoming degree of vertices
//每次找出入度为0的顶点，删除该顶点，更新邻接矩阵，直到所有顶点都被删除
//Each time we find a vertex with zero variance, and delete that vertex and update the adjacency matrix until all vertices are removed
//如果最后还有顶点没有被删除，说明有环
//If there are still vertices left undeleted at the end there is a ring

//筛第一次为f
//Filter out the first time is F
/*有向图 digraph
	  →	A  B  C  D  E  F
	A	0, 1, 1, 1, 0,  ,
	B	0, 0, 0, 0, 0,  ,
	C	0, 1, 0, 0, 1,  ,
	D	0, 0, 0, 0, 1,  ,
	E	0, 0, 0, 0, 0,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//筛第二次为a
// The second time is an a
/*有向图 digraph
	  →	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 , 0, 0, 0, 0,  ,
	C	 , 1, 0, 0, 1,  ,
	D	 , 0, 0, 0, 1,  ,
	E	 , 0, 0, 0, 0,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//筛第三次为d
//d
/*有向图 digraph
	  →	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 , 0, 0,  , 0,  ,
	C	 , 1, 0,  , 1,  ,
	D	 ,  ,  ,  ,  ,  ,
	E	 , 0, 0,  , 0,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//筛第四次为c
//c
/*有向图 digraph
	  →	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 , 0,  ,  , 0,  ,
	C	 ,  ,  ,  ,  ,  ,
	D	 ,  ,  ,  ,  ,  ,
	E	 , 0,  ,  , 0,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//筛第五次为e
//e
/*有向图 digraph
	  →	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 , 0,  ,  ,  ,  ,
	C	 ,  ,  ,  ,  ,  ,
	D	 ,  ,  ,  ,  ,  ,
	E	 ,  ,  ,  ,  ,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//筛第六次为b
//b
/*有向图 digraph
	  →	A  B  C  D  E  F
	A	 ,  ,  ,  ,  ,  ,
	B	 ,  ,  ,  ,  ,  ,
	C	 ,  ,  ,  ,  ,  ,
	D	 ,  ,  ,  ,  ,  ,
	E	 ,  ,  ,  ,  ,  ,
	F	 ,  ,  ,  ,  ,  ,
	*/

//然后没有剩下的数，说明没有环
// And then there is not number left，which means there is not ring

//但在C语言中不好直接对矩阵进行动态操作，所以可以先把矩阵里所有数加一，然后再进行操作
// However，in C，it is not good to directly perform dynamic operations on the matrix, so you can first add 1 to all the numbers in the matrix and then operate

//先把矩阵里所有数加一（有一说一看的我眼花）
//add 1 to all the numbers in the matrix(To be honest, this is making my eyes spin)
/*有向图 digraph
	  →	A  B  C  D  E  F
	A	1, 2, 2, 2, 1, 1,
	B	1, 1, 1, 1, 1, 1,
	C	1, 2, 1, 1, 2, 1,
	D	1, 1, 1, 1, 2, 1,
	E	1, 1, 1, 1, 1, 1,
	F	1, 1, 1, 2, 2, 1,
	*/

//后面的操作和前面一样，只不过把删除操作换成赋值为0
// The subsequent operations are the same as the previous ones, expect that the deletion operation is replace with assigning a value of 0

typedef struct Graph {
	char* vexs;//顶点
	int** arcs;//边
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
	/*有向图
	  →	A  B  C  D  E  F
	A	0, 1, 1, 1, 0, 0,
	B	0, 0, 0, 0, 0, 0,
	C	0, 1, 0, 0, 1, 0,
	D	0, 0, 0, 0, 1, 0,
	E	0, 0, 0, 0, 0, 0,
	F	0, 0, 0, 1, 1, 0
	*/

	//visited一维数组初始化
	int* visited = (int*)malloc(sizeof(int) * G->vexNum);
	if (!visited) {
		puts("visited malloc failed\n");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < G->vexNum; i++) {
		visited[i] = 0;
	}

	//图邻接矩阵信息
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

// 拓扑排序
void topological_sort(Graph* graph) {
	int* visited = (int*)malloc(sizeof(int) * graph->vexNum);	// 用来标记是否已处理
	if (!visited) {
		puts("visited malloc failed\n");
		return;
	}

	for (int i = 0; i < graph->vexNum; i++) {
		visited[i] = 0;
	}

	int count = 0;  // 记录已排序的顶点数

	while (count < graph->vexNum) {
		int found = 0;  // 标记是否找到入度为0的顶点
		for (int i = 0; i < graph->vexNum; i++) {
			if (!visited[i] && check_colume(graph, i)) {  // 如果该顶点未处理且入度为0
				printf("%c\t", graph->vexs[i]);  // 输出顶点
				visited[i] = 1;  // 标记为已处理
				count++;

				// 删除该顶点的行和列（将值置为0）
				for (int j = 0; j < graph->vexNum; j++) {
					graph->arcs[j][i] = 1;  // 删除列
					graph->arcs[i][j] = 1;  // 删除行
				}
				found = 1;
				break;  // 找到一个就退出当前循环
			}
		}
		if (!found) {  // 如果没有找到入度为0的顶点
			printf("图中存在环，无法继续进行拓扑排序。\n");
			return;
		}
	}
	printf("\n");
}

// 检查某一列是否全为0（入度为0）
int check_colume(Graph* graph, int index) {
	for (int i = 0; i < graph->vexNum; i++) {
		if (graph->arcs[i][index] > 1) {  // 假设矩阵中值为2表示有边
			return 0;  // 如果该列有非零值，返回0
		}
	}
	return 1;  // 如果该列全为0，返回1
}

Graph* init_graph(int vexNum) {
	//初始化图结构体
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

	//初始化顶点数组vexs和邻接矩阵arcs
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
	for (int i = 0; i < graph->vexNum; i++) {	//导入二维邻接矩阵
		graph->vexs[i] = vexs[i];
		for (int j = 0; j < graph->vexNum; j++) {
			graph->arcs[i][j] = *(arcs + i * graph->vexNum + j);	//将一维数组arcs转换为graph->arcs二维数组
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
