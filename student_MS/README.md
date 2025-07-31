# Student Management System 🎓

A comprehensive student record management system with CRUD operations, persistent storage, and sorting capabilities.

## Features
- **Student Records**: Store ID, name, age, course, and grade information
- **CRUD Operations**: Complete Create, Read, Update, Delete functionality
- **Persistent Storage**: Binary file storage for data persistence
- **Search Functionality**: Find students by ID
- **Sorting Options**: Sort by name (alphabetical) or grade (descending)
- **Data Validation**: Input validation and error handling

## Compilation & Usage
```bash
gcc -o student_ms student_MS.c
./student_ms
```

## Menu Options
```
===== 🎓 Student Management System =====
1. Add Student
2. List Students
3. Search Student
4. Update Student
5. Delete Student
6. Sort by Name
7. Sort by Grade
0. Exit
```

## Data Structure
```c
typedef struct {
    int id;
    char name[50];
    int age;
    char course[50];
    float grade;
} Student;
```

## File Storage
- **Filename**: `students.bin`
- **Format**: Binary format for efficient I/O
- **Auto-save**: Data automatically saved after each operation
- **Auto-load**: Previous data loaded on program startup

## Usage Examples

### Adding a Student
```
Enter ID: 1001
Enter Name: John Doe
Enter Age: 20
Enter Course: Computer Science
Enter Grade: 85.5
✅ Student added successfully!
```

### Listing Students
```
ID    Name                 Age   Course          Grade
------------------------------------------------------------
1001  John Doe             20    Computer Science 85.50
1002  Jane Smith           19    Mathematics      92.00
```

## Technical Highlights
- Structure-based data organization
- Binary file I/O for performance
- Bubble sort algorithms
- Dynamic array management (max 100 students)