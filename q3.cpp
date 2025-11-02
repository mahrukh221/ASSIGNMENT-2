#include <stdio.h>

#define ROWS 3
#define COLS 3

#define POWER_BIT 1
#define OVERLOAD_BIT 2
#define MAINTENANCE_BIT 4

int grid[ROWS][COLS] = {
    {0, 1, 2},
    {4, 0, 7},
    {1, 5, 0}
};

void display_menu();
void update_status();
void query_status();
void run_scan();
void print_status(int status);

int main() {
    int choice;

    do {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            choice = 0;
            while (getchar() != '\n');
        }

        switch (choice) {
            case 1:
                update_status();
                break;
            case 2:
                query_status();
                break;
            case 3:
                run_scan();
                break;
            case 4:
                printf("\nExiting Power Grid Monitoring System.\n");
                break;
            default:
                printf("\nInvalid option. Please choose 1, 2, 3, or 4.\n");
        }
        
        if (choice != 4) {
            printf("\n(Press Enter to continue...)\n");
            while (getchar() != '\n');
            getchar();
        }
    } while (choice != 4);

    return 0;
}

void display_menu() {
    printf("\n===================================\n");
    printf(" Power Grid Monitoring System \n");
    printf("===================================\n");
    printf(" 1. Update Sector Status\n");
    printf(" 2. Query Sector Status\n");
    printf(" 3. Run System Diagnostic Scan\n");
    printf(" 4. Exit System\n");
    printf("-----------------------------------\n");
    printf("Enter choice: ");
}

void print_status(int status) {
    printf("Status Report:\n");
    
    if (status & POWER_BIT) {
        printf("  - Power Status: ON (1)\n");
    } else {
        printf("  - Power Status: OFF (0)\n");
    }
    
    if (status & OVERLOAD_BIT) {
        printf("  - Overload Warning: YES (1)\n");
    } else {
        printf("  - Overload Warning: Normal (0)\n");
    }
    
    if (status & MAINTENANCE_BIT) {
        printf("  - Maintenance Required: YES (1)\n");
    } else {
        printf("  - Maintenance Required: NO (0)\n");
    }
}

void update_status() {
    int row, col, flag_choice, value, current_status, mask = 0;

    printf("\n Update Sector Status \n");
    printf("Enter coordinates (Row 0-%d, Column 0-%d): ", ROWS - 1, COLS - 1);
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Error: Invalid row or column index.\n");
        return;
    }

    current_status = grid[row][col];
    printf("Current Status Value: %d\n", current_status);
    print_status(current_status);

    printf("\nSelect flag to update:\n");
    printf(" 1. Power Status (ON/OFF)\n");
    printf(" 2. Overload Warning (YES/NO)\n");
    printf(" 3. Maintenance Required (YES/NO)\n");
    printf("Enter flag number (1-3): ");
    scanf("%d", &flag_choice);

    switch (flag_choice) {
        case 1: mask = POWER_BIT; break;
        case 2: mask = OVERLOAD_BIT; break;
        case 3: mask = MAINTENANCE_BIT; break;
        default:
            printf("Error: Invalid flag choice.\n");
            return;
    }

    printf("Enter new value (1 for SET, 0 for CLEAR): ");
    scanf("%d", &value);

    if (value == 1) {
        grid[row][col] = current_status | mask;
        printf("Flag SET successfully.\n");
    } else if (value == 0) {
        grid[row][col] = current_status & ~mask;
        printf("Flag CLEARED successfully.\n");
    } else {
        printf("Error: Value must be 1 or 0.\n");
    }

    printf("New Status Value: %d\n", grid[row][col]);
    print_status(grid[row][col]);
}

void query_status() {
    int row, col, status;

    printf("\n Query Sector Status \n");
    printf("Enter coordinates (Row 0-%d, Column 0-%d): ", ROWS - 1, COLS - 1);
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Error: Invalid row or column index.\n");
        return;
    }

    status = grid[row][col];
    printf("\nStatus of Sector (%d, %d):\n", row, col);
    printf("Integer Value: %d\n", status);
    print_status(status);
}

void run_scan() {
    int r, c, maintenance_count = 0, overload_count = 0;

    printf("\n System Diagnostic Scan \n");

    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            int status = grid[r][c];

            printf("\nSector (%d, %d) Status Value: %d\n", r, c, status);
            print_status(status);
            
            if (status & OVERLOAD_BIT) {
                overload_count++;
            }
            
            if (status & MAINTENANCE_BIT) {
                maintenance_count++;
            }
        }
    }

    printf("\n===================================\n");
    printf(" System Scan Summary\n");
    printf("===================================\n");
    printf(" Total sectors currently running overload warning: %d\n", overload_count);
    printf(" Total sectors currently require maintenance: %d\n", maintenance_count);
    printf("===================================\n");
}

