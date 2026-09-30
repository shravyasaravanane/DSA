#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100
double A[MAX][MAX];
double mean[MAX];
double centered[MAX][MAX];
double variance[MAX];
double sd[MAX];
double norm[MAX][MAX];
double corr[MAX][MAX];

typedef struct Node {
    char word[20];
    struct Node *next;
} Node;

// Function to create a new node
Node* createNode(char str[]) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, str);
    newNode->next = NULL;
    return newNode;
}

// Function to create a circular linked list
Node* createCircularList(char* arr[], int n) {
    Node *head = NULL, *temp = NULL, *newNode;

    for (int i = 0; i < n; i++) {
        newNode = createNode(arr[i]);

        if (head == NULL) {
            head = newNode;
            temp = head;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }

    // Make the list circular
    temp->next = head;

    return head;
}

// Function to create a circular linked list
Node* createCircularShift(Node* head, int n) {
    if (head == NULL) 
        return head;

    for(int i = 0; i < n; i++)
        head = head->next;
    return head;
}

// Function to display the circular linked list
void display(Node *head, int n) {
    Node *temp = head;
    printf("Circular Linked List:\n");
    for (int i = 0; i < n; i++) {
        printf("%s -> ", temp->word);
        temp = temp->next;
    }
    printf("(Back to Head)\n");
}

// Queue structure
typedef struct {
    char data[MAX][20];
    int front, rear;
} Queue;

// Initialize queue
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

// Check empty
int isEmpty(Queue *q) {
    return (q->front > q->rear);
}

// Enqueue
void enqueue(Queue *q, char word[]) {
    q->rear++;
    strcpy(q->data[q->rear], word);
}

// Dequeue
char* dequeue(Queue *q) {
    return q->data[q->front++];
}
void displayQ(Queue *head, int n) {
    Queue *temp = head;
    printf("Queue:\n");
    for (int i = 0; i < n; i++) {
        printf("%s -> ", temp->data[i]);
    }
    printf("(Back to Head)\n");
}

int main() 
{
    char* List[] = {
        "Every","morning","the","sun","rises",
        "over","the","mountains",".",
        "Quiet","birds","sing","softly",
        "in","the","forest","."
    };

    int n = sizeof(List) / sizeof(List[0]);

    Node* head = createCircularList(List, n);
    display(head, n); 
    
    Queue* q1 = (Queue*)malloc(sizeof(Queue));
    Queue* q2 = (Queue*)malloc(sizeof(Queue));
    initQueue(q1); initQueue(q2);

    int i = 0;
    while(!(strcmp(List[i], ".") == 0)) {
        enqueue(q1, List[i]);
        i++;
    }
    enqueue(q1, List[i]);
    while(++i < n) {
        enqueue(q2, List[i]);
    }
    for (int j = 0; j < 9; j++)
        enqueue(q2, dequeue(q1));
    displayQ(q2, n);

    Node* newHead = createCircularShift(head, 9);
    display(newHead, n);

    char test[4][20] = {"There", "are", "many", "different"};
    int j, k, len[MAX];
    i = 0; n = 4;       // Remove later
    //  ;
    // // Step 1: Find word lengths
    for(i = 0; i < n; i++)
        // len[i] = strlen(newHead->word[i]);
        len[i] = strlen(test[i]);

    // Step 2: Difference Matrix
    printf("\nDifference Matrix:\n\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            A[i][j] = abs(len[i] - len[j]);
            printf("%6.0lf ", A[i][j]);
        }
        printf("\n");
    }

    // Step 3: Column Means
    for(j = 0; j < n; j++) {
        mean[j] = 0;
        for(i = 0; i < n; i++)
            mean[j] += A[i][j];
        mean[j] /= n;
    }

    printf("\nColumn Means:\n");
    for(j = 0; j < n; j++)
        printf("%8.3lf ", mean[j]);

    // Step 4: Centered Matrix
    printf("\n\nCentered Matrix:\n\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            centered[i][j] = A[i][j] - mean[j];
            printf("%8.3lf ", centered[i][j]);
        }
        printf("\n");
    }

    // Step 5: Variance
    for(j = 0; j < n; j++) {
        variance[j] = 0;
        for(i = 0; i < n; i++)
            variance[j] += centered[i][j] * centered[i][j];
        variance[j] /= n;
        sd[j] = sqrt(variance[j]);
    }

    printf("\nVariance:\n");
    for(j = 0; j < n; j++)
        printf("%8.4lf ", variance[j]);

    printf("\n\nStandard Deviation:\n");
    for(j = 0; j < n; j++)
        printf("%8.4lf ", sd[j]);

    // Step 6: Normalize
    printf("\n\nNormalized Matrix:\n\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(sd[j] != 0)
                norm[i][j] = centered[i][j] / sd[j];
            else
                norm[i][j] = 0;
            printf("%8.3lf ", norm[i][j]);
        }
        printf("\n");
    }

    // Step 7: Correlation Matrix
    // D = Transpose(norm) × norm

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            corr[i][j] = 0;
            for(k = 0; k < n; k++)
                corr[i][j] += norm[k][i] * norm[k][j];
            corr[i][j] /= n;
        }
    }

    printf("\nCorrelation Matrix:\n\n");

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++)
            printf("%8.3lf ", corr[i][j]);

        printf("\n");
    }
    
    return 0;
}