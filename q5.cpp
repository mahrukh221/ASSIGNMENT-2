#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void display_menu();
void reverse_string(char *str);
void toggle_bits(char *str);
void encode_message(char *message);
void decode_message(char *message);

int main() {
    char message[MAX_LENGTH];
    int choice;

    do {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            choice = 0;
            while (getchar() != '\n');
        }
        
        if (choice >= 1 && choice <= 2) {
            printf("\nEnter message (max %d chars): ", MAX_LENGTH - 1);
            while (getchar() != '\n');
            fgets(message, MAX_LENGTH, stdin);
            message[strcspn(message, "\n")] = 0;

            if (strlen(message) == 0) {
                printf("\nError: Message cannot be empty.\n");
                continue;
            }
        }

        switch (choice) {
            case 1:
                encode_message(message);
                printf("\nEncoded Message: %s\n", message);
                break;
            case 2:
                decode_message(message);
                printf("\nDecoded Message: %s\n", message);
                break;
            case 3:
                printf("\nTerminating the program.\n");
                break;
            default:
                printf("\nInvalid option. Please choose a number between 1 and 3.\n");
        }
        
        if (choice != 3) {
            printf("\n(Press Enter to continue...)\n");
            if (choice >= 1 && choice <= 2) {
            } else {
                while (getchar() != '\n');
            }
            getchar();
        }
    } while (choice != 3);

    return 0;
}

void display_menu() {
    printf("\n===================================\n");
    printf(" TCS Lightweight Cipher Utility \n");
    printf("===================================\n");
    printf(" 1. Encode Message\n");
    printf(" 2. Decode Message\n");
    printf(" 3. EXIT\n");
    printf("-----------------------------------\n");
    printf("Enter choice: ");
}

void reverse_string(char *str) {
    int len = strlen(str);
    int i;
    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void toggle_bits(char *str) {
    int i = 0;
    char toggle_mask = (1 << 1) | (1 << 4);
    
    while (str[i] != '\0') {
        str[i] = str[i] ^ toggle_mask;
        i++;
    }
}

void encode_message(char *message) {
    reverse_string(message);
    toggle_bits(message);
}

void decode_message(char *message) {
    toggle_bits(message);
    reverse_string(message);
}

