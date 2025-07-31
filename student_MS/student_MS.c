#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    int age;
    char course[50];
    float grade;
} Student;

Student students[MAX];
int count = 0;

void load_data() {
    FILE *fp = fopen("students.bin", "rb");
    if (fp) {
        fread(&count, sizeof(int), 1, fp);
        fread(students, sizeof(Student), count, fp);
        fclose(fp);
    }
}

void save_data() {
    FILE *fp = fopen("students.bin", "wb");
    if (fp) {
        fwrite(&count, sizeof(int), 1, fp);
        fwrite(students, sizeof(Student), count, fp);
        fclose(fp);
    }
}

void add_student() {
    if (count >= MAX) {
        printf("Student list is full!\n");
        return;
    }

    Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    getchar();  // consume newline
    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // remove newline
    printf("Enter Age: ");
    scanf("%d", &s.age);
    getchar();
    printf("Enter Course: ");
    fgets(s.course, sizeof(s.course), stdin);
    s.course[strcspn(s.course, "\n")] = '\0';
    printf("Enter Grade: ");
    scanf("%f", &s.grade);

    students[count++] = s;
    save_data();
    printf("✅ Student added successfully!\n");
}

void list_students() {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\n%-5s %-20s %-5s %-15s %-6s\n", "ID", "Name", "Age", "Course", "Grade");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-5d %-15s %-6.2f\n", students[i].id, students[i].name,
               students[i].age, students[i].course, students[i].grade);
    }
}

void search_student() {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Found: %s (%d y/o), Course: %s, Grade: %.2f\n",
                   students[i].name, students[i].age, students[i].course, students[i].grade);
            return;
        }
    }
    printf("Student not found.\n");
}

void update_student() {
    int id;
    printf("Enter ID of student to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Updating student: %s\n", students[i].name);
            printf("Enter new Age: ");
            scanf("%d", &students[i].age);
            getchar();
            printf("Enter new Course: ");
            fgets(students[i].course, sizeof(students[i].course), stdin);
            students[i].course[strcspn(students[i].course, "\n")] = '\0';
            printf("Enter new Grade: ");
            scanf("%f", &students[i].grade);

            save_data();
            printf("✅ Student updated successfully.\n");
            return;
        }
    }

    printf("Student not found.\n");
}

void delete_student() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            save_data();
            printf("✅ Student deleted.\n");
            return;
        }
    }

    printf("Student not found.\n");
}

void sort_by_name() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(students[i].name, students[j].name) > 0) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("📚 Students sorted by name.\n");
}

void sort_by_grade() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].grade < students[j].grade) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("📈 Students sorted by grade.\n");
}

int main() {
    load_data();
    int choice;

    do {
        printf("\n===== 🎓 Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. List Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Sort by Name\n");
        printf("7. Sort by Grade\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_student(); break;
            case 2: list_students(); break;
            case 3: search_student(); break;
            case 4: update_student(); break;
            case 5: delete_student(); break;
            case 6: sort_by_name(); break;
            case 7: sort_by_grade(); break;
            case 0: printf("👋 Goodbye!\n"); break;
            default: printf("❌ Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
