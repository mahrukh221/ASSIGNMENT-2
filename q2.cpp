#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 4
#define MAX_CART_ITEMS 10
#define NAME_LENGTH 30
#define CNIC_LENGTH 15

int product_codes[MAX_PRODUCTS] = {1, 2, 3, 4};
int quantities_in_stock[MAX_PRODUCTS] = {50, 10, 20, 8};
float prices_per_product[MAX_PRODUCTS] = {100.0, 200.0, 300.0, 150.0};

char customer_name[NAME_LENGTH];
char customer_cnic[CNIC_LENGTH];

int cart_codes[MAX_CART_ITEMS];
int cart_quantities[MAX_CART_ITEMS];
int cart_count = 0;

void get_customer_info();
void display_inventory();
int find_product_index(int code);
void add_item_to_cart();
void display_total_bill();
void show_invoice(float total_bill, int discount_applied);
void clear_cart();

int main() {
    int user_choice;

    get_customer_info();

    do {
        printf("\n===================================\n");
        printf(" Inventory and Billing System \n");
        printf("===================================\n");
        printf(" 1. Display Inventory\n");
        printf(" 2. Add Item to Cart\n");
        printf(" 3. Display Total Bill (Checkout)\n");
        printf(" 4. Exit the system\n");
        printf("-----------------------------------\n");
        printf("Please enter your choice (1-4): ");
        scanf("%d", &user_choice);

        switch (user_choice) {
            case 1:
                display_inventory();
                break;
            case 2:
                add_item_to_cart();
                break;
            case 3:
                display_total_bill();
                break;
            case 4:
                printf("\nExiting application. Thank you, %s!\n", customer_name);
                break;
            default:
                printf("\nInvalid option. Please choose a number from 1 to 4.\n");
        }
        
        if (user_choice != 4) {
            printf("\n(Press Enter to continue...)\n");
            getchar();
            getchar();
        }
        
    } while (user_choice != 4);

    return 0;
}

void get_customer_info() {
    printf(" Customer Information \n");
    printf("Enter Customer Name: ");
    while (getchar() != '\n');
    fgets(customer_name, NAME_LENGTH, stdin);
    customer_name[strcspn(customer_name, "\n")] = 0;

    printf("Enter Customer CNIC: ");
    fgets(customer_cnic, CNIC_LENGTH, stdin);
    customer_cnic[strcspn(customer_cnic, "\n")] = 0;
    printf("Welcome, %s!\n", customer_name);
}

void display_inventory() {
    int i;
    printf("\n Current Inventory Stock \n");
    printf("Product Code | Quantity in Stock | Price per Product\n");
    printf("===================================================\n");
    for (i = 0; i < MAX_PRODUCTS; i++) {
        printf("%12d | %17d | %17.2f\n", 
               product_codes[i], 
               quantities_in_stock[i], 
               prices_per_product[i]);
    }
    printf("===================================================\n");
}

int find_product_index(int code) {
    int i;
    for (i = 0; i < MAX_PRODUCTS; i++) {
        if (product_codes[i] == code) {
            return i;
        }
    }
    return -1;
}

void add_item_to_cart() {
    int code_to_add;
    int quantity_to_add;
    int index;

    if (cart_count >= MAX_CART_ITEMS) {
        printf("\nCart is full! You cannot add more than %d items. Proceed to checkout.\n", MAX_CART_ITEMS);
        return;
    }

    printf("\n Add Item to Cart \n");
    printf("Enter Product Code to add: ");
    scanf("%d", &code_to_add);

    index = find_product_index(code_to_add);

    if (index == -1) {
        printf("Error: Invalid Product Code.\n");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &quantity_to_add);

    if (quantity_to_add <= 0) {
        printf("Error: Quantity must be greater than zero.\n");
        return;
    }

    if (quantities_in_stock[index] < quantity_to_add) {
        printf("Error: Insufficient stock. Only %d units available.\n", quantities_in_stock[index]);
        return;
    }

    quantities_in_stock[index] -= quantity_to_add;

    cart_codes[cart_count] = code_to_add;
    cart_quantities[cart_count] = quantity_to_add;
    cart_count++;

    printf("\nItem(s) added successfully. %d remaining in stock.\n", quantities_in_stock[index]);
}

void display_total_bill() {
    float total = 0.0;
    float final_bill = 0.0;
    char voucher[10];
    int discount_applied = 0;
    int i;

    if (cart_count == 0) {
        printf("\nYour cart is empty. Please add items first.\n");
        return;
    }

    printf("\n Cart Summary and Checkout \n");
    printf("Code | Quantity | Unit Price | Item Total\n");
    printf("==========================================\n");

    for (i = 0; i < cart_count; i++) {
        int index = find_product_index(cart_codes[i]);
        if (index != -1) {
            float item_total = prices_per_product[index] * cart_quantities[i];
            total += item_total;
            printf("%4d | %8d | %10.2f | %10.2f\n", 
                   cart_codes[i], 
                   cart_quantities[i], 
                   prices_per_product[index], 
                   item_total);
        }
    }
    printf("==========================================\n");
    printf("Subtotal (before discount): %.2f\n", total);
    
    final_bill = total;

    printf("\nDo you have the 'Eid2025' voucher? (Type 'Eid2025' or 'no'): ");
    scanf("%s", voucher);

    if (strcmp(voucher, "Eid2025") == 0) {
        float discount = total * 0.25;
        final_bill = total - discount;
        discount_applied = 1;
        printf("Voucher Applied! Discount: %.2f (25%%)\n", discount);
    } else {
        printf("No discount applied.\n");
    }

    printf("FINAL BILL AMOUNT: %.2f\n", final_bill);

    show_invoice(final_bill, discount_applied);
}

void show_invoice(float total_bill, int discount_applied) {
    printf("\n===================================\n");
    printf("           SALES INVOICE \n");
    printf("===================================\n");
    printf("Customer: %s\n", customer_name);
    printf("CNIC:     %s\n", customer_cnic);
    printf("===================================\n");

    if (cart_count == 0) {
        printf("Cart was empty - no transaction recorded.\n");
        return;
    }

    printf("Items Purchased:\n");
    printf("Code | Qty | Price\n");

    for (int i = 0; i < cart_count; i++) {
        int index = find_product_index(cart_codes[i]);
        if (index != -1) {
            printf("%4d | %3d | %5.2f\n", 
                   cart_codes[i], 
                   cart_quantities[i], 
                   prices_per_product[index]);
        }
    }

    printf("===================================\n");
    
    float total_without_discount = total_bill / (discount_applied ? 0.75 : 1.0);
    printf("Total Bill (without discount): %.2f\n", total_without_discount);
    
    if (discount_applied) {
        float discount_amount = total_without_discount * 0.25;
        printf("Discount Applied (25%%): %.2f\n", discount_amount);
    }
    
    printf("FINAL AMOUNT DUE: %.2f\n", total_bill);
    printf("===================================\n");
    
    clear_cart();
}

void clear_cart() {
    cart_count = 0;
}

