#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

typedef struct BigInteger
{
    struct node *head;
    int length;
}BigInteger;

BigInteger reverse(struct node **head)
{
    BigInteger num;
    struct node *prevNode = 0, *currNode = *head, *nextNode = *head;
    while(nextNode != 0)
    {
        nextNode = nextNode->next;
        currNode->next = prevNode;
        prevNode = currNode;
        currNode = nextNode;
    }
    *head = prevNode;
    num.head = *head;
    return num;
}

int compare(BigInteger a, BigInteger b)
{
    reverse(&a.head);
    reverse(&b.head);
    if(a.length < b.length)       //returns 1 when a is smaller
        return 1;
    else if(a.length > b.length)  //returns -1 when b is smaller
        return -1;
    struct node *tempA = a.head, *tempB = b.head;
    if(tempA->data > tempB->data)
        return -2;
    else if(tempA->data < tempB->data)
        return -3;
    while(tempA->data == tempB->data)
    {
        if(tempA->next == 0 && tempB->next == 0 && tempA->data == tempB->data)
            return 0;
        tempA = tempA->next;
        tempB = tempB->next;
    }
    if(tempA->data < tempB->data)
        return -3;
    if(tempA->data > tempB->data)
        return -2;
    else 
        return 0;
    //returns 0 when both are equal in size and value
    //returns -2 when both are equal in size but A is big
    //returns -3 when both are equal in size but B is big
}

void display(BigInteger num)
{
    struct node *head = num.head;
    if(head == 0)
    {
        return;
    }
    struct node *temp = head;
    while(temp != 0)
    {
        printf("%d", temp->data);
        temp = temp->next;
    } 
    printf("\n");
}

void formLL(struct node **head, int data)
{
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data = data;
    new->next = 0;
    if(*head == 0)
    {
        *head = new;
        return;
    }
    struct node *temp = *head;
    while(temp->next != 0)
        temp = temp->next;
    temp->next = new;
}

BigInteger add(BigInteger a, BigInteger b)
{
    BigInteger AddAns;
    struct node *headMain = 0;
    struct node *tempA = a.head;
    struct node *tempB = b.head;
    int carry = 0;
    while(tempA != 0 && tempB != 0)
    {
        int ans = carry + tempA->data + tempB->data;
        int temp = ans;
        formLL(&headMain, temp%10);
        if(ans > 9)
            carry = ans/10;
        else
            carry = 0;
        tempA = tempA->next;
        tempB = tempB->next;
    }
    while(tempA != 0)
    {
        int ans = carry + tempA->data;
        int temp = ans;
        formLL(&headMain, temp%10);
        if(ans > 9)
            carry = ans/10;
        else
            carry = 0;
        tempA = tempA->next;
    }
    while (tempB != 0)
    {
        int ans = carry + tempB->data;
        int temp = ans;
        formLL(&headMain, temp%10);
        if(ans > 9)
            carry = ans/10;
        else
            carry = 0;
        tempB = tempB->next;
    }
    
    if(carry != 0)
        formLL(&headMain, carry);

    AddAns.head = headMain;
    AddAns = reverse(&headMain);
    return AddAns;
}


BigInteger sub(BigInteger a, BigInteger b)
{
    BigInteger SubAns ;
    struct node *headMain = 0;
    struct node *tempA = a.head;
    struct node *tempB = b.head;
    while(tempA != 0 && tempB != 0)
    {
        if(tempA->data >= tempB->data)
            formLL(&headMain, (tempA->data - tempB->data));
        else
        {
            formLL(&headMain, (tempA->data + 10) - tempB->data);
            --tempA->next->data;
        }
        tempA = tempA->next;
        tempB = tempB->next;
    }

    while(tempA != 0)
    {
        formLL(&headMain, tempA->data);
        tempA = tempA->next;
    }

    SubAns.head = headMain;
    SubAns = reverse(&headMain);
    return SubAns;
}

BigInteger mul(BigInteger a, BigInteger b)
{
    BigInteger MulAns ;
    MulAns.head = 0;
    struct node *headMain = 0;
    struct node *tempA = a.head;
    struct node *tempB = b.head;
    int iter = 1;
    while(tempB != 0)
    {
        struct node *headNew = 0;
        tempA = a.head;
        while(tempA != 0)
        {
            formLL(&headNew, (tempA->data*tempB->data));
            tempA = tempA->next;
        }
        if(iter > 1)
        {
            int x = 1;
            while(x < iter)
            {
                struct node *new = (struct node*)malloc(sizeof(struct node));
                new->data = 0;
                new->next = headNew;
                headNew = new;
                x++;
            }
        }
        BigInteger NewAns;
        NewAns.head = headNew;
        MulAns = add(MulAns, NewAns);
        MulAns = reverse(&(MulAns.head));
        tempB = tempB->next;
        iter++;
    }
    MulAns = reverse(&(MulAns.head));
    return MulAns;
}

BigInteger div1(BigInteger dividend, BigInteger divisor)
{
    BigInteger divAns;
    BigInteger quotient = dividend;
    struct node *ans = 0;
    BigInteger one;
    struct node* new = 0;
    formLL(&new, 1);
    one.head = new;
    int compareBigInt = compare(dividend, divisor);
    if(compareBigInt == 0)
        formLL(&ans, 1);
    else if(compareBigInt == 1)
        formLL(&ans, 0);
    divAns.head = ans;
    return divAns; 
}

BigInteger initialize(char str[])
{
    BigInteger num;
    num.length = 0;
    struct node *head = 0, *ptr;
    for(int i = 0 ; str[i]!='\0' ; i++)
    {
        num.length++;
        struct node *new = (struct node*)malloc(sizeof(struct node));
        new->data = (int)(str[i] - 48);
        new->next = 0;
        if(head == 0)
        {
            head = new;
            ptr = new;
        }
        else
        {
            ptr->next = new;
            ptr = new;
        }
    }
    num.head = reverse(&head).head;
    return num;
}
