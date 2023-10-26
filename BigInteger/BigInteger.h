#ifndef BigInteger_h
#define BigInteger_h

struct node {
    int data;
    struct node *next;
};

typedef struct BigInteger
{
    struct node *head;
    int length;
}BigInteger;

BigInteger reverse(struct node **head);
int compare(BigInteger a, BigInteger b);
void display(BigInteger num);
void formLL(struct node **head, int data);
BigInteger add(BigInteger a, BigInteger b);
BigInteger sub(BigInteger a, BigInteger b);
BigInteger mul(BigInteger a, BigInteger b);
BigInteger div1(BigInteger dividend, BigInteger divisor);
BigInteger initialize(char str[]);

#endif;