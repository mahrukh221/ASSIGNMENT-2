#include <stdio.h>

#define MAX_SIZE 5

int stack[MAX_SIZE];
int top = -1;

void display_menu();
void push(int stack_arr[], int item, int max_size);
int pop(int stack_arr[], int *top_ptr);
int peek(int stack_arr[], int top);
void display(int stack_arr[], int top);

int main() {
    int choice, item;

    do {
        display_menu();
        
        if (scanf("%d", &choice) != 1) {
            choice = 0;
            while (getchar() != '\n');
        }

        switch (choice) {
            case 1:
                printf("\nEnter element to PUSH: ");
                scanf("%d", &item);
                push(stack, item, MAX_SIZE);
                break;
            case 2:
                item = pop(stack, &top);
                if (item != -1) {
                    printf("\nPOP successful. Removed element: %d\n", item);
                }
                break;
            case 3:
                item = peek(stack, top);
                if (item != -1) {
                    printf("\nPEEK successful. Top element is: %d\n", item);
                }
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("\nTerminating the program.\n");
                break;
            default:
                printf("\nInvalid option. Please choose a number between 1 and 5.\n");
        }
        
        if (choice != 5) {
            printf("\n(Press Enter to continue...)\n");
            while (getchar() != '\n');
            getchar();
        }
    } while (choice != 5);

    return 0;
}

void display_menu() {
    printf("\n===================================\n");
    printf(" Stack Implementation (Max size: %d) \n", MAX_SIZE);
    printf("===================================\n");
    printf(" 1. PUSH (Insert)\n");
    printf(" 2. POP (Remove)\n");
    printf(" 3. PEEK (Top Element)\n");
    printf(" 4. DISPLAY (All Elements)\n");
    printf(" 5. EXIT\n");
    printf("-----------------------------------\n");
    printf("Enter choice: ");
}

void push(int stack_arr[], int item, int max_size) {
    if (top == max_size - 1) {
        printf("\nError: Stack OVERFLOW! Cannot push element.\n");
    } else {
        top = top + 1;
        stack_arr[top] = item;
        printf("\nPUSH successful. Element %d added.\n", item);
    }
}

int pop(int stack_arr[], int *top_ptr) {
    int item;
    if (*top_ptr == -1) {
        printf("\nError: Stack UNDERFLOW! Cannot pop element.\n");
        return -1;
    } else {
        item = stack_arr[*top_ptr];
        *top_ptr = *top_ptr - 1;
        return item;
    }
}

int peek(int stack_arr[], int top_val) {
    if (top_val == -1) {
        printf("\nError: Stack is empty. Cannot PEEK.\n");
        return -1;
    } else {
        return stack_arr[top_val];
    }
}

void display(int stack_arr[], int top_val) {
    int i;
    if (top_val == -1) {
        printf("\nStack is empty. Nothing to display.\n");
    } else {
        printf("\nStack elements (Top to Bottom):\n");
        for (i = top_val; i >= 0; i--) {
            printf("| %-5d |\n", stack_arr[i]);
            printf("-------\n");
        }
    }
}

