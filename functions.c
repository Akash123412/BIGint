#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

// #include "header.h"

struct node
{
  int data;
  struct node *next;
  struct node *prev;
};



struct node* createnode(int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

struct node* reverselist(struct node* head) {
    struct node* prev = NULL;
    struct node* current = head;
    struct node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}


struct node* inputbigint() {
    struct node* temp = NULL;
    char ch;

    printf("Enter big integer (terminate with Enter):\n");

    while (1) {
        ch = getchar();
        if (ch == '\n' || !isdigit(ch)) {
            break;
        }

        int digit = ch - '0';
        struct node* newnode = createnode(digit);

        if (temp == NULL) {
            temp = newnode;
        } else {
            newnode->next = temp;
            temp = newnode;
        }
    }

    return temp;
}



struct node* addbigint(struct node* num1, struct node* num2) {
    struct node* result = NULL;
    struct node* temp;
    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry != 0) {
        int sum = carry;
        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum %= 10;

        struct node* newnode = createnode(sum);
        if (result == NULL) {
            result = newnode;
            temp = result;
        } else {
            temp->next = newnode;
            temp = temp->next;
        }
    }

    return result;
}


void print(struct node* temp) {
    if (temp == NULL) {
        printf("0");
        return;
    }

    temp = reverselist(temp);

    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}



struct node* multiplybigint(struct node* num1, struct node* num2) {
    struct node* result = createnode(0);
    struct node* tempresult = result;

    while (num2 != NULL) {
        int carry = 0;
        struct node* tempnum1 = num1;
        result = tempresult;

        while (tempnum1 != NULL) {
            int product = (num2->data * tempnum1->data) + carry;

            if (result == NULL) {
                result = createnode(product % 10);
                tempresult = result;
            } else {
                while (result->next != NULL) {
                    result = result->next;
                }
                result->next = createnode(product % 10);
            }

            carry = product / 10;
            tempnum1 = tempnum1->next;
        }

        if (carry > 0) {
            while (result->next != NULL) {
                result = result->next;
            }
            result->next = createnode(carry);
        }

        num2 = num2->next;
        tempresult = addbigint(tempresult, createnode(0));
    }

    return tempresult;
}
struct node* dividebigint(struct node* num1, struct node* num2) {
    struct node* result = NULL;

    while (num2 != NULL) {
        if (num2->data != 0) {
            break;
        }
        num2 = num2->next;
    }

    if (num2 == NULL) {
        fprintf(stderr, "by zero not allowed\n");
        exit(1);
    }

    while (num1 != NULL) {
        int quotient = 0;
        struct node* tempnum1 = num1;

        while (tempnum1 != NULL && greateroreq(tempnum1, num2)) {
            tempnum1 = subtractbigint(tempnum1, num2);
            quotient++;
        }

        if (result == NULL) {
            result = createnode(quotient);
        } else {
            struct node* tempresult = result;
            while (tempresult->next != NULL) {
                tempresult = tempresult->next;
            }
            tempresult->next = createnode(quotient);
        }

        num1 = num1->next;
    }

    return result;
}



struct node* subtractbigint(struct node* num1, struct node* num2) {
    struct node* result = NULL;
    struct node* temp;
    int borrow = 0;

    while (num1 != NULL || num2 != NULL) {
        int diff = borrow;
        if (num1 != NULL) {
            diff += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            diff -= num2->data;
            num2 = num2->next;
        }

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        struct node* newnode = createnode(diff);
        if (result == NULL) {
            result = newnode;
            temp = result;
        } else {
            temp->next = newnode;
            temp = temp->next;
        }
    }

    return result;
}
int greateroreq(struct node* num1, struct node* num2) {
    if (num1 == NULL) {
        return 0;
    }
    if (num2 == NULL) {
        return 1;
    }

    num1 = reverselist(num1);
    num2 = reverselist(num2);

    while (num1 != NULL && num2 != NULL) {
        if (num1->data > num2->data) {
            return 1;
        } else if (num1->data < num2->data) {
            return 0;
        }
        num1 = num1->next;
        num2 = num2->next;
    }

    return 1;
}



