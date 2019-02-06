#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 40

typedef enum { false, true } bool;
 
struct node{
    char name[50];
    double degreeCentrality;
    double stdDegreeCentrality;
    double closenessCentrality;
    double stdClosenessCentrality;
    double betweennesCentrality;
    double stdBetweennesCentrality;
    struct node* next;
};


struct adjGraph{
	int numberOfVertices;
    struct node** adjLists;
};


struct node* createNode(char* name){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
   	snprintf(newNode->name, sizeof(newNode->name), "%s", name);
    newNode->next = NULL;
    return newNode;
}
 

struct adjGraph* createGraph(int vertices){
    struct adjGraph* graph = (struct adjGraph*)malloc(sizeof(struct adjGraph));
 	graph->numberOfVertices = vertices;
    graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));
 
    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
 
    return graph;
}

int search(char* name, struct adjGraph* graph){
	int i, j=0;
	for(i=0;i<currentPopulation(graph);i++){
		if(strcmp(graph->adjLists[i]->name,name)==0)
			return i;
	}
    return -1;
}

int currentPopulation(struct adjGraph* graph){
	int i,j=0;
	for(i=0;i<graph->numberOfVertices;i++){
		if(graph->adjLists[i]!=NULL)
			j++;
	}
    return j;
}
 
void addConnection(struct adjGraph* graph, char* person, char* friend){
	struct node* newPerson = createNode(person);
	struct node* newFriend = createNode(friend);
    int p = search(person, graph);
    int n=currentPopulation(graph);
    if(n==0){
    	newPerson->next=newFriend;
		graph->adjLists[0]=newPerson;
	}
    else if(p>=0){
    	struct node* temp = graph->adjLists[p];
		if(temp->next==NULL)
			temp->next=newFriend;
		else{
			while(temp->next){
	    		temp=temp->next;
			}
	    	temp->next=newFriend;
		} 
	    
	}
	else{
		newPerson->next=newFriend;
		graph->adjLists[n]=newPerson;
	}
	
}
 
void printGraph(struct adjGraph* graph){
    int i;
    for (i = 0; i<graph->numberOfVertices;i++){
        struct node* temp = graph->adjLists[i];
        printf("\n%s; ",graph->adjLists[i]->name );
        do{
            printf("%s, ", temp->next->name);
            temp = temp->next;
        }while (temp->next);
        printf("\n");
    }
}

//
//
// STACK CODES
//
//
struct Stack 
{ 
    int top; 
    unsigned capacity; 
    int* array; 
}; 
  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* createStack(unsigned capacity) 
{ 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*) malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 
  
// Stack is full when top is equal to the last index 
int isFull(struct Stack* stack) 
{   return stack->top == stack->capacity - 1; } 
  
// Stack is empty when top is equal to -1 
int isEmpty(struct Stack* stack) 
{   return stack->top == -1;  } 
  
// Function to add an item to stack.  It increases top by 1 
void push(struct Stack* stack, int item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    printf("%d pushed to stack\n", item); 
} 
  
// Function to remove an item from stack.  It decreases top by 1 
int pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
} 


//
//
//CALCULATIONS WITH DIJKSTRA
//
//
int minDistance(int dist[], bool sptSet[], int V){ 
   // Initialize min value 
   int min = INT_MAX, min_index; 
   int v;
   for(v= 0; v < V; v++) 
     if(sptSet[v] == false && dist[v] <= min) 
         min = dist[v], min_index = v; 
   
   return min_index; 
} 

void savePath(int parent[], int j, struct Stack* path){ 
      
    // Base Case : If j is source 
    if (parent[j] == - 1) 
        return; 
  
    savePath(parent, parent[j], path); 
  
    push(path, j);
	 
} 

void saveParent(int V, int N, int parent[], struct Stack** paths) {    
   int i;
   for (i = 0; i < V; i++) {
   	struct Stack* tempPath=createStack(V);
   	savePath(parent, i, tempPath); 
   	paths[i]=tempPath;
   }
      
} 


// Function that implements Dijkstra's single source shortest path algorithm 
// for a graph represented using adjacency matrix representation 
void dijkstra(int** matrix, int src, int V,int dist[],int parent[], struct Stack** paths) 
{  
	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest 
                     // path tree or shortest distance from src to i is finalized 
     // Initialize all distances as INFINITE and stpSet[] as false 
     int i;
     for (i = 0; i < V; i++){
     	dist[i] = INT_MAX;
     	sptSet[i] = false;
     	parent[0]=-1;
	 } 
   
     // Distance of source vertex from itself is always 0 
     dist[src] = 0; 
   
     // Find shortest path for all vertices 
     int count;
     for (count = 0; count < V-1; count++) 
     { 
       // Pick the minimum distance vertex from the set of vertices not 
       // yet processed. u is always equal to src in the first iteration. 
       int u = minDistance(dist, sptSet, V); 
   
       // Mark the picked vertex as processed 
       sptSet[u] = true;
   
       // Update dist value of the adjacent vertices of the picked vertex. 
       int v;
       for (v = 0; v < V; v++) 
   
         // Update dist[v] only if is not in sptSet, there is an edge from  
         // u to v, and total weight of path from src to  v through u is  
         // smaller than current value of dist[v] 
         if (!sptSet[v] && matrix[u][v] && dist[u] != INT_MAX  && dist[u]+matrix[u][v] < dist[v]) 
            dist[v] = dist[u] + matrix[u][v];
			parent[v]=u;
     } 
   	saveParent(V, V, parent, paths);
     // print the constructed distance array 
     //printSolution(dist, V, V);
} 

void setDegreeCentralities(struct adjGraph* graph){
	int i, N=graph->numberOfVertices;
	for (i = 0; i<N;i++){
		struct node* temp = graph->adjLists[i];
		int numAdjacents=0;
		while (temp){
            numAdjacents++;
            temp = temp->next;
        }
		graph->adjLists[i]->degreeCentrality=numAdjacents-1;
		graph->adjLists[i]->stdDegreeCentrality=graph->adjLists[i]->degreeCentrality/N;				
	}
}

void setClosenessCentralities(struct adjGraph* graph, int** matrix){
	int N= graph->numberOfVertices;
	struct Stack** paths = (struct Stack** ) malloc (N* sizeof(struct Stack* ));
	int k;
    for (k=0; k<N; k++){
        paths[k]=createStack(N);
	}
	
	int i;
	for (i = 0; i<N;i++){
		int dist[N];
 	    int parent[N];
		dijkstra(matrix,i,N,dist,parent, paths);
		
		int j, counter=0,numThreePaths=0;
		double total=0.0;
		for (j = 0; j<N;j++){
			total+=dist[j];
			if(isInArray(i, paths[j]->array, N))
				counter++;
			if(sizeof(paths[j]->array)>2)
				numThreePaths++;
		}
		
		graph->adjLists[i]->closenessCentrality=1/total;
		graph->adjLists[i]->stdClosenessCentrality=(1/total)*(N-1);
		graph->adjLists[i]->betweennesCentrality=counter/numThreePaths;
		graph->adjLists[i]->stdBetweennesCentrality=(counter/numThreePaths)/((N-1)*(N-2)/2);
		
	}
}

bool isInArray(int key, int array[], int N){
	int t;
	for(t=0;t<N;t++){
		if(array[t]==key)
			return true;
	}
	return false;
}

//
//
//	CONVERSION TO MATRIX
//
//
int getIndex(struct adjGraph* graph, char* name){
	int N = graph->numberOfVertices;
	int i,j=0;
	for (i = 0; i<N && strcmp(name,graph->adjLists[i]->name)!=0;i++){
		j++;
	}
	return j;
}

void convertList2Matrix(struct adjGraph* graph, int** emptyMatrix,int N){
	int i,j;
    for (i = 0; i<N;i++){        
        struct node* temp = graph->adjLists[i]->next;
		while (temp){
			j = getIndex(graph, temp->name);			
        	emptyMatrix[i][j]=1;     
			temp = temp->next;  
		}
    }
}

void printMatrix(int** matrix, struct adjGraph* graph){
	int r,c,nodes=graph->numberOfVertices;
	
	printf("\nADJACENCY MATRIX:\n");
  	    printf("        ");
 	    for (c = 0; c < nodes; c++) {
  	    	printf("%6s ", graph->adjLists[c]->name);
  	    }
  	    printf("\n");
  	    
  	    for (c = 0; c < nodes*2.5; c++) {
  	    	printf("---");
  	    }
  	    printf("\n");
  	    
  	    for (r = 0; r < nodes; r++) {
  	    	printf("%7s| ", graph->adjLists[r]->name);
  	    	for (c = 0; c < nodes; c++) {
  	        	printf("  %d    ", matrix[r][c]);
  	      	}
  	     printf("\n");
  	    }
}

	void printValues(struct adjGraph* graph){
		int N=graph->numberOfVertices;
		int i;
   		for (i = 0; i<N;i++){        
        	printf("degree centrality of %s: %.1f\n",graph->adjLists[i]->name, graph->adjLists[i]->degreeCentrality );
        	printf("standart degree centrality of %s: %.4f\n",graph->adjLists[i]->name, graph->adjLists[i]->stdDegreeCentrality );
        	printf("closeness centrality of %s: %.4f\n",graph->adjLists[i]->name, graph->adjLists[i]->closenessCentrality );
        	printf("standart closeness centrality of %s: %.4f\n",graph->adjLists[i]->name, graph->adjLists[i]->stdClosenessCentrality ); 
        	printf("betweennes centrality of %s: %.4f\n",graph->adjLists[i]->name, graph->adjLists[i]->betweennesCentrality );
        	printf("standart betweennes centrality of %s: %.4f\n",graph->adjLists[i]->name, graph->adjLists[i]->stdBetweennesCentrality );
        	printf("\n");
			}
    	}
		
	

int main(){
	
	FILE *fp=fopen("input.txt","r");
	
	int ch=0;
	int lineNum=0;
  	while ((ch = fgetc(fp)) != EOF){
      	if (ch == '\n')
    	lineNum++;
	}
	struct adjGraph* graph = createGraph(lineNum);
	fclose(fp);
	
	FILE *fp2=fopen("input.txt","r");
	char str[50];
  	while(fscanf(fp2, "%s", str)==1){
	    char* where = strchr( str, ';');
	    char person[50];
	    char cleanPerson[50];
		char friend[50];
	    if(where != NULL ){
	      sscanf(str, "%[^;];",person);
	      //printf("%s", person);  
	    }
		else{
	      sscanf(str, "%[^,],",friend);
	      addConnection(graph, person, friend);
	      //printf("%s ", friend);     
	    }
  	}
	fclose(fp);
 
    printGraph(graph);
    setDegreeCentralities(graph);
    
    int N = graph->numberOfVertices, i,j;
    /* Dynamic allocation of matrix array */
    int **adj_matrix = (int **) malloc (N* sizeof(int *));
    for (i = 0; i < N; i++) 
 	     adj_matrix[i] = (int *) malloc(N* sizeof(int));
 	     
    // Fill matrix with zeo  	
    for (i = 0; i<N;i++){        
        for (j= 0; j<N;j++){
        	adj_matrix[i][j]=0;
		}
    }
 	
 	convertList2Matrix(graph, adj_matrix, N);
	  	
 	printMatrix(adj_matrix, graph);
 	
 	setClosenessCentralities(graph, adj_matrix);
 	
 	printValues(graph);
 	
 	
 	
 	
    return 0;
}

 
 

