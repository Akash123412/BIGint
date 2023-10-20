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
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
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

void print(struct node* num) {
    if (num == NULL) {
        printf("0");
        return;
    }

    num = reverselist(num);

    while (num != NULL) {
        printf("%d", num->data);
        num = num->next;
    }
    printf("\n");
}

struct node* inputbigint() {
    struct node* num = NULL;
    char ch;

    printf("Enter big number (terminate with Enter):\n");

    while (1) {
        ch = getchar();
        if (ch == '\n' || !isdigit(ch)) {
            break;
        }

        int digit = ch - '0';
        struct node* newNode = createnode(digit);

        if (num == NULL) {
            num = newNode;
        } else {
            newNode->next = num;
            num = newNode;
        }
    }

    return num;
}



struct node* multiplybigint(struct node* num1, struct node* num2) {
    struct node* result = createnode(0);
    struct node* tempResult = result;

    while (num2 != NULL) {
        int carry = 0;
        struct node* tempNum1 = num1;
        result = tempResult;

        while (tempNum1 != NULL) {
            int product = (num2->data * tempNum1->data) + carry;

            if (result == NULL) {
                result = createnode(product % 10);
                tempResult = result;
            } else {
                while (result->next != NULL) {
                    result = result->next;
                }
                result->next = createnode(product % 10);
            }

            carry = product / 10;
            tempNum1 = tempNum1->next;
        }

        if (carry > 0) {
            while (result->next != NULL) {
                result = result->next;
            }
            result->next = createnode(carry);
        }

        num2 = num2->next;
        tempResult = addbigint(tempResult, createnode(0));
    }

    return tempResult;
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

        struct node* newNode = createnode(sum);
        if (result == NULL) {
            result = newNode;
            temp = result;
        } else {
            temp->next = newNode;
            temp = temp->next;
        }
    }

    return result;
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
        struct node* tempNum1 = num1;

        while (tempNum1 != NULL && greateroreq(tempNum1, num2)) {
            tempNum1 = subtractbigint(tempNum1, num2);
            quotient++;
        }

        if (result == NULL) {
            result = createnode(quotient);
        } else {
            struct node* tempResult = result;
            while (tempResult->next != NULL) {
                tempResult = tempResult->next;
            }
            tempResult->next = createnode(quotient);
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

        struct node* newNode = createnode(diff);
        if (result == NULL) {
            result = newNode;
            temp = result;
        } else {
            temp->next = newNode;
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



