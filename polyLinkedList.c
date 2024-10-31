#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

Node* insertTerm(Node* head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (!head || exp > head->exp) {
        newNode->next = head;
        return newNode;
    }
    Node* temp = head;
    while (temp->next && temp->next->exp > exp)
        temp = temp->next;
    
    if (temp->exp == exp) {  
        temp->coeff += coeff;
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }
    return head;
}


void displayPolynomial(Node* poly) {
    if (!poly) {
        printf("0\n");
        return;
    }
    while (poly) {
        printf("%d*x^%d", poly->coeff, poly->exp);
        if (poly->next && poly->next->coeff > 0)
            printf(" + ");
        poly = poly->next;
    }
    printf("\n");
}

Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node* p1 = poly1;
    Node* p2 = poly2;
    
    while (p1 && p2) {
        if (p1->exp == p2->exp) {
            result = insertTerm(result, p1->coeff + p2->coeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            result = insertTerm(result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            result = insertTerm(result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }
    
    while (p1) {
        result = insertTerm(result, p1->coeff, p1->exp);
        p1 = p1->next;
    }
    
    while (p2) {
        result = insertTerm(result, p2->coeff, p2->exp);
        p2 = p2->next;
    }
    
    return result;
}


Node* multiplyPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    for (Node* p1 = poly1; p1 != NULL; p1 = p1->next) {
        for (Node* p2 = poly2; p2 != NULL; p2 = p2->next) {
            result = insertTerm(result, p1->coeff * p2->coeff, p1->exp + p2->exp);
        }
    }
    return result;
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;
    Node* sum = NULL;
    Node* product = NULL;
    
    int node1, coeff, exp;
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &node1);
    printf("Enter the terms:\n");
    for (int i = 0; i < node1; i++) {
        scanf("%d %d", &coeff, &exp);
        poly1 = insertTerm(poly1, coeff, exp);
    }
    

    int node2;
    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &node2);
    printf("Enter the terms:\n");
    for (int i = 0; i < node2; i++) {
        scanf("%d %d", &coeff, &exp);
        poly2 = insertTerm(poly2, coeff, exp);
    }
    
   
    
   int choice = 0;

   while (choice != 4) {
        printf("\nEnter your choice\n1. Display\n2. Addition\n3. Muliplication\n4. Exit\n");
        scanf("%d", &choice);
        
        switch (choice)
        {
        
        case 1:
            printf("First Polynomial: ");
            displayPolynomial(poly1);
            printf("Second Polynomial: ");
            displayPolynomial(poly2);
            break;
        case 2:
            sum = addPolynomials(poly1, poly2);
            printf("Sum of the Polynomials: ");
            displayPolynomial(sum);
            break;
        case 3:
            product = multiplyPolynomials(poly1, poly2);
            printf("Product of the Polynomials: ");
            displayPolynomial(product);
            break;
        case 4:
            break;
        
        default:
            printf("Invalid choice");
            break;
        }
    
   }
}
