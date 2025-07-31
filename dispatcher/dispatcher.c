#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "data.txt"

// Function prototypes
void add_data();
void count_lines();
void count_chars();
void to_uppercase();
void to_lowercase();

// Function pointer type
typedef void (*FunctionHandler)();

// Menu structure
typedef struct {
    char *name;
    FunctionHandler handler;
} MenuOption;

void add_data() {
    FILE *fp = fopen(FILENAME, "a");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    char *buffer = (char *)malloc(1024);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(fp);
        return;
    }

    printf("Enter text to add to the file:\n> ");
    getchar(); // clear buffer
    fgets(buffer, 1024, stdin);
    fprintf(fp, "%s", buffer);

    printf("✅ Data added successfully!\n");
    free(buffer);
    fclose(fp);
}

void count_lines() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    int lines = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            lines++;
    }

    printf("📄 Total lines: %d\n", lines);
    fclose(fp);
}

void count_chars() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    int chars = 0;
    while (fgetc(fp) != EOF)
        chars++;

    printf("🔤 Total characters: %d\n", chars);
    fclose(fp);
}

void convert_case(int to_upper) {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        perror("Error reading file");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    rewind(fp);

    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(fp);
        return;
    }

    fread(buffer, 1, length, fp);
    buffer[length] = '\0';
    fclose(fp);

    for (int i = 0; i < length; i++) {
        buffer[i] = to_upper ? toupper(buffer[i]) : tolower(buffer[i]);
    }

    fp = fopen(FILENAME, "w");
    if (!fp) {
        perror("Error writing file");
        free(buffer);
        return;
    }

    fwrite(buffer, 1, length, fp);
    printf("✅ File content converted to %s.\n", to_upper ? "UPPERCASE" : "lowercase");

    free(buffer);
    fclose(fp);
}

void to_uppercase() {
    convert_case(1);
}

void to_lowercase() {
    convert_case(0);
}

int main() {
    MenuOption *menu = malloc(6 * sizeof(MenuOption));
    if (!menu) {
        perror("Menu allocation failed");
        return 1;
    }

    menu[0] = (MenuOption){"Add Data to File", add_data};
    menu[1] = (MenuOption){"Count Lines", count_lines};
    menu[2] = (MenuOption){"Count Characters", count_chars};
    menu[3] = (MenuOption){"Convert to UPPERCASE", to_uppercase};
    menu[4] = (MenuOption){"Convert to lowercase", to_lowercase};
    menu[5] = (MenuOption){"Exit", NULL};

    int choice;
    do {
        printf("\n===== 📁 Dynamic Function Dispatcher =====\n");
        for (int i = 0; i < 6; i++) {
            printf("%d. %s\n", i + 1, menu[i].name);
        }

        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5) {
            menu[choice - 1].handler();
        } else if (choice != 6) {
            printf("❌ Invalid option.\n");
        }

    } while (choice != 6);

    printf("👋 Exiting program.\n");
    free(menu);
    return 0;
}
