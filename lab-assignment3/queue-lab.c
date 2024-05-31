// name: Kaustubha Eluri 
// email: eluri.k@northeastern.edu

#include <stdio.h>
#define N 8 //Max. capacity of Queue

static int rear = -1;
static int front = -1;

/*----To check if the queue is empty-------*/
int isempty()
{
    if (rear == -1)
        return 1;
    else
        return 0;
}

/*-----To check if the queue is full----------*/
int isfull()
{
    if (rear == N - 1)
        return 1;
    return 0;
}

/*---- To see the data at the front of the queue---*/
int peek(int *arr)
{
    if (isempty())
    {
        printf("Queue is empty.\n");
        return -1;
    }
    return arr[front + 1];
}

/*---To insert the elements into the queue------*/
void enqueue(int data, int *arr)
{
    if (isfull())
    {
        printf("Queue is full. Cannot enqueue %d\n", data);
        return;
    }

    if (isempty())
    {
        front = rear = 0;
    }
    else
    {
        rear++;
    }
    arr[rear] = data;
    printf("Enqueued %d\n", data);
}

/*----Function to remove the elements from the queue----*/
int dequeue(int *arr)
{
    if (isempty())
    {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    int data = arr[front + 1];
    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front++;
    }
    return data;
}

/*---Function to display the elements of the queue-------*/
void display(int *arr)
{
    int i;
    if (isempty())
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        for (i = front + 1; i <= rear; i++)
        {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

/*-----Main program-----*/
int main()
{
    int arr[N]; //array in which queue will live

    /* insert 8 items */
    display(arr);
    enqueue(1, arr);
    enqueue(2, arr);
    display(arr);
    enqueue(3, arr);
    enqueue(4, arr);
    enqueue(5, arr);
    enqueue(6, arr);
    enqueue(7, arr);
    enqueue(8, arr);
    display(arr);
    enqueue(9, arr); // This should show that the queue is full

    for (int i = 0; i < N - 1; i++)
    {
        printf("dequeued element is: %d\n", dequeue(arr));
    }
    display(arr);
    printf("The element at the front of the queue is: %d\n", peek(arr));
    return 0;
}
