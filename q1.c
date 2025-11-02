#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define TITLE_MAX_LENGTH 50
#define LOW_STOCK_THRESHOLD 5

void display_main_menu(); 
int find_book_index_by_isbn(int isbns[], int current_count, int target_isbn);
void handle_add_new_book(int isbns[], char titles[][TITLE_MAX_LENGTH], float prices[], int quantities[], int *current_count);
void handle_process_sale(int isbns[], int quantities[], int current_count);
void generate_low_stock_report(char titles[][TITLE_MAX_LENGTH], float prices[], int quantities[], int current_count);

int main() {
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][TITLE_MAX_LENGTH];
    float prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];
    
    int book_count = 0; 
    int user_choice;

    do {
        display_main_menu();
        printf("Please enter your choice (1-4): ");
        scanf("%d", &user_choice);

        switch (user_choice) {
            case 1:
                handle_add_new_book(isbns, titles, prices, quantities, &book_count);
                break;
            case 2:
                handle_process_sale(isbns, quantities, book_count);
                break;
            case 3:
                generate_low_stock_report(titles, prices, quantities, book_count);
                break;
            case 4:
                printf("\nThank you for using the inventory system. Goodbye!\n");
                break;
            default:
                printf("\nThat's not a valid option. Please choose a number from 1 to 4.\n");
        }
        
        if (user_choice != 4) {
            printf("\n(Press Enter to return to the main menu...)\n");
            getchar();
            getchar();
        }
        
    } while (user_choice != 4);

    return 0;
}

void display_main_menu() {
    printf("\n===================================\n");
    printf(" Liberty Books Inventory Manager \n");
    printf("===================================\n");
    printf(" 1. Add New Book\n");
    printf(" 2. Process a Sale\n");
    printf(" 3. Generate Low-Stock Report\n");
    printf(" 4. Exit Application\n");
    printf("-----------------------------------\n");
}

int find_book_index_by_isbn(int isbns[], int current_count, int target_isbn) {
    int i;
    for (i = 0; i < current_count; i++) {
        if (isbns[i] == target_isbn) {
            return i;
        }
    }
    return -1;
}

void handle_add_new_book(int isbns[], char titles[][TITLE_MAX_LENGTH], float prices[], int quantities[], int *current_count) {
    int new_isbn;
    
    printf("\n-- Adding New Book --\n");

    if (*current_count >= MAX_BOOKS) {
        printf("Sorry! The inventory is full. Cannot add more than %d books.\n", MAX_BOOKS);
        return;
    }

    do {
        printf("Enter the unique ISBN: ");
        if (scanf("%d", &new_isbn) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            new_isbn = 0;
            continue;
        }

        if (find_book_index_by_isbn(isbns, *current_count, new_isbn) != -1) {
            printf("This ISBN already exists in the system. Please enter a different one.\n");
        }
    } while (find_book_index_by_isbn(isbns, *current_count, new_isbn) != -1);
    
    isbns[*current_count] = new_isbn;

    while (getchar() != '\n'); 

    printf("Enter the Book Title (up to %d characters): ", TITLE_MAX_LENGTH - 1);
    fgets(titles[*current_count], TITLE_MAX_LENGTH, stdin);
    titles[*current_count][strcspn(titles[*current_count], "\n")] = 0;

    printf("Enter the Price (e.g., 99.50): ");
    scanf("%f", &prices[*current_count]);

    printf("Enter the initial Quantity: ");
    scanf("%d", &quantities[*current_count]);
    
    (*current_count)++;
    printf("\nSuccess! Book details saved to inventory.\n");
}

void handle_process_sale(int isbns[], int quantities[], int current_count) {
    int sale_isbn;
    int copies_to_sell;
    int book_index;

    printf("\n-- Processing Sale --\n");

    if (current_count == 0) {
        printf("The inventory is empty. Please add books first (Option 1).\n");
        return;
    }

    printf("Enter the ISBN of the book being sold: ");
    scanf("%d", &sale_isbn);

    book_index = find_book_index_by_isbn(isbns, current_count, sale_isbn);

    if (book_index == -1) {
        printf("Error: Book not found! Please check the ISBN and try again.\n");
        return;
    }

    printf("Enter the number of copies to sell: ");
    scanf("%d", &copies_to_sell);

    if (copies_to_sell <= 0) {
        printf("Sale cancelled: You must sell at least 1 copy.\n");
    } else if (quantities[book_index] < copies_to_sell) {
        printf("Sale Failed: Insufficient stock. Only %d copies are currently available.\n", 
               quantities[book_index]);
    } else {
        quantities[book_index] -= copies_to_sell;
        printf("\nSale successful!\n");
        printf("Updated Stock Level: %d copies remaining.\n", quantities[book_index]);
    }
}

void generate_low_stock_report(char titles[][TITLE_MAX_LENGTH], float prices[], int quantities[], int current_count) {
    int i;
    int low_stock_found = 0;
    
    printf("\n===================================\n");
    printf("   LOW STOCK ALERT REPORT \n");
    printf("===================================\n");
    
    if (current_count == 0) {
        printf("No books have been added to the inventory yet.\n");
        return;
    }

    printf("Trigger Limit: Quantity is less than %d\n\n", LOW_STOCK_THRESHOLD);
    printf("TITLE\t\t\tPRICE\t\tQUANTITY\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < current_count; i++) {
        if (quantities[i] < LOW_STOCK_THRESHOLD) {
            printf("%-25s\t%.2f\t\t%d\n", titles[i], prices[i], quantities[i]);
            low_stock_found = 1;
        }
    }

    if (!low_stock_found) {
        printf("Great news! All books are currently well-stocked.\n");
    }
    printf("--------------------------------------------------\n");
}

