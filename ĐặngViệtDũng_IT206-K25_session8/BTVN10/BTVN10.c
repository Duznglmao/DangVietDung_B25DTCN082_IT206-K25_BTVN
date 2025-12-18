#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
#define MAX_FILENAME_LEN 100
#define MIN_AGE 15
#define MAX_AGE 100
#define MIN_GPA 0.0f
#define MAX_GPA 4.0f

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void trimRight(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }
}

int isValidId(Student students[], int n, int id) {
    if (id <= 0) return 0;
    for (int i = 0; i < n; i++) {
        if (students[i].id == id) return 0;
    }
    return 1;
}

int isValidAge(int age) {
    return age >= MIN_AGE && age <= MAX_AGE;
}

int isValidGPA(float gpa) {
    return gpa >= MIN_GPA && gpa <= MAX_GPA;
}

int isValidName(const char *name) {
    return name != NULL && strlen(name) > 0;
}

int inputId(Student students[], int n) {
    int id;
    do {
        printf("  ID: ");
        if (scanf("%d", &id) != 1) {
            printf("  Input khong hop le!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        if (!isValidId(students, n, id)) {
            if (id <= 0) {
                printf("  ID phai > 0!\n");
            } else {
                printf("  ID da ton tai!\n");
            }
        }
    } while (!isValidId(students, n, id));
    return id;
}

void inputName(char *name) {
    do {
        printf("  Ho ten: ");
        fgets(name, MAX_NAME_LEN, stdin);
        trimRight(name);
        
        if (!isValidName(name)) {
            printf("  Ten khong duoc rong!\n");
        }
    } while (!isValidName(name));
}

int inputAge() {
    int age;
    do {
        printf("  Tuoi (%d-%d): ", MIN_AGE, MAX_AGE);
        if (scanf("%d", &age) != 1) {
            printf("  Input khong hop le!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        if (!isValidAge(age)) {
            printf("  Tuoi phai trong khoang %d-%d!\n", MIN_AGE, MAX_AGE);
        }
    } while (!isValidAge(age));
    return age;
}

float inputGPA() {
    float gpa;
    do {
        printf("  GPA (%.1f-%.1f): ", MIN_GPA, MAX_GPA);
        if (scanf("%f", &gpa) != 1) {
            printf("  Input khong hop le!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        if (!isValidGPA(gpa)) {
            printf("  GPA phai trong khoang %.1f-%.1f!\n", MIN_GPA, MAX_GPA);
        }
    } while (!isValidGPA(gpa));
    return gpa;
}

Student inputStudent(Student students[], int n) {
    Student s;
    printf("\nNhap thong tin sinh vien:\n");
    s.id = inputId(students, n);
    inputName(s.name);
    s.age = inputAge();
    s.gpa = inputGPA();
    return s;
}

void saveToFile(const char *filename, Student students[], int n) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Loi: Khong mo duoc file %s de ghi!\n", filename);
        return;
    }

    fprintf(f, "+----+----------------------+-----+------+\n");
    fprintf(f, "| %-2s | %-20s | %-3s | %-4s |\n", "ID", "Name", "Age", "GPA");
    fprintf(f, "+----+----------------------+-----+------+\n");

    for (int i = 0; i < n; i++) {
        fprintf(f, "| %-2d | %-20s | %-3d | %-4.2f |\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }

    fprintf(f, "+----+----------------------+-----+------+\n");
    fclose(f);
    printf("Thanh cong: Da luu %d sinh vien vao file %s\n", n, filename);
}

int loadFromFile(const char *filename, Student students[], int maxN) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Loi: Khong mo duoc file %s de doc!\n", filename);
        return 0;
    }

    char line[256];
    int n = 0;

    for (int i = 0; i < 3 && fgets(line, sizeof(line), f); i++);

    while (fgets(line, sizeof(line), f) && n < maxN) {
        if (line[0] != '|') continue;

        Student temp;
        if (sscanf(line, "| %d | %49[^|] | %d | %f |",
                   &temp.id, temp.name, &temp.age, &temp.gpa) == 4) {
            trimRight(temp.name);
            
            // Validate data
            if (isValidId(students, n, temp.id) && 
                isValidAge(temp.age) && 
                isValidGPA(temp.gpa) &&
                isValidName(temp.name)) {
                students[n++] = temp;
            } else {
                printf("Canh bao: Bo qua sinh vien khong hop le (ID=%d)\n", temp.id);
            }
        }
    }

    fclose(f);
    printf("Thanh cong: Doc %d sinh vien tu file %s\n", n, filename);
    return n;
}

Student* findStudentById(Student students[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

float calculateAverageGPA(Student students[], int n) {
    if (n <= 0) return 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += students[i].gpa;
    }
    return sum / n;
}

void sortByGPA(Student students[], int n, int ascending) {
    for (int i = 0; i < n - 1; i++) {
        int targetIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (ascending) {
                if (students[j].gpa < students[targetIndex].gpa) {
                    targetIndex = j;
                }
            } else {
                if (students[j].gpa > students[targetIndex].gpa) {
                    targetIndex = j;
                }
            }
        }
        if (targetIndex != i) {
            Student tmp = students[i];
            students[i] = students[targetIndex];
            students[targetIndex] = tmp;
        }
    }
}

int addStudent(Student students[], int *n, int maxN, Student newS) {
    if (*n >= maxN) {
        printf("Loi: Mang da day, khong the them!\n");
        return 0;
    }

    if (!isValidId(students, *n, newS.id)) {
        printf("Loi: ID khong hop le hoac da ton tai!\n");
        return 0;
    }

    students[*n] = newS;
    (*n)++;
    printf("Thanh cong: Da them sinh vien ID=%d\n", newS.id);
    return 1;
}

int removeStudentById(Student students[], int *n, int id) {
    int index = -1;
    for (int i = 0; i < *n; i++) {
        if (students[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Loi: Khong tim thay sinh vien co ID=%d\n", id);
        return 0;
    }

    // Shift elements
    for (int i = index; i < *n - 1; i++) {
        students[i] = students[i + 1];
    }
    (*n)--;
    printf("Thanh cong: Da xoa sinh vien ID=%d\n", id);
    return 1;
}

void printTableBorder() {
    printf("+----+----------------------+-----+------+\n");
}

void printTableHeader() {
    printTableBorder();
    printf("| %-2s | %-20s | %-3s | %-4s |\n", "ID", "Name", "Age", "GPA");
    printTableBorder();
}

void printStudent(Student *s) {
    printf("| %-2d | %-20s | %-3d | %-4.2f |\n",
           s->id, s->name, s->age, s->gpa);
}

void printStudents(Student students[], int n) {
    if (n == 0) {
        printf("Danh sach rong.\n");
        return;
    }
    
    printTableHeader();
    for (int i = 0; i < n; i++) {
        printStudent(&students[i]);
    }
    printTableBorder();
    printf("Tong: %d sinh vien | GPA trung binh: %.2f\n", 
           n, calculateAverageGPA(students, n));
}


void menuInputStudents(Student students[], int *n) {
    int count;
    printf("So luong sinh vien muon nhap: ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("So luong khong hop le!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (*n + count > MAX_STUDENTS) {
        printf("Chi co the them toi da %d sinh vien.\n", MAX_STUDENTS - *n);
        count = MAX_STUDENTS - *n;
    }

    for (int i = 0; i < count; i++) {
        printf("\n--- Sinh vien %d/%d ---\n", i + 1, count);
        Student s = inputStudent(students, *n);
        addStudent(students, n, MAX_STUDENTS, s);
    }
}

void menuFileOperation(Student students[], int *n, int isRead) {
    char filename[MAX_FILENAME_LEN];
    printf("Ten file: ");
    scanf("%99s", filename);
    clearInputBuffer();

    if (isRead) {
        *n = loadFromFile(filename, students, MAX_STUDENTS);
    } else {
        saveToFile(filename, students, *n);
    }
}

void menuSearch(Student students[], int n) {
    int id;
    printf("Nhap ID can tim: ");
    if (scanf("%d", &id) != 1) {
        printf("Input khong hop le!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    Student *s = findStudentById(students, n, id);
    if (s) {
        printf("\nKet qua tim kiem:\n");
        printTableHeader();
        printStudent(s);
        printTableBorder();
    } else {
        printf("Khong tim thay sinh vien ID=%d\n", id);
    }
}

void menuSort(Student students[], int n) {
    int choice;
    printf("1. Tang dan\n2. Giam dan\nChon: ");
    if (scanf("%d", &choice) != 1) {
        printf("Lua chon khong hop le!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (choice == 1) {
        sortByGPA(students, n, 1);
        printf("Da sap xep tang dan theo GPA.\n");
    } else if (choice == 2) {
        sortByGPA(students, n, 0);
        printf("Da sap xep giam dan theo GPA.\n");
    } else {
        printf("Lua chon khong hop le!\n");
    }
}

void menuAdd(Student students[], int *n) {
    if (*n >= MAX_STUDENTS) {
        printf("Mang da day!\n");
        return;
    }
    Student s = inputStudent(students, *n);
    addStudent(students, n, MAX_STUDENTS, s);
}

void menuDelete(Student students[], int *n) {
    int id;
    printf("Nhap ID can xoa: ");
    if (scanf("%d", &id) != 1) {
        printf("Input khong hop le!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    removeStudentById(students, n, id);
}

void menuGenerateMock(Student students[], int *n) {
    Student mock[] = {
        {1, "Nguyen Van A", 19, 3.2f},
        {2, "Nguyen Van B", 20, 2.8f},
        {3, "Nguyen Van C", 18, 3.9f},
        {4, "Nguyen Van D", 21, 3.5f},
        {5, "Nguyen Van E", 19, 2.1f},
        {6, "Nguyen Van F", 22, 3.0f},
        {7, "Nguyen Van G", 20, 3.7f},
        {8, "Nguyen Van H", 18, 2.5f},
        {9, "Nguyen Van I", 21, 3.3f},
        {10, "Nguyen Van K", 19, 4.0f}
    };
    
    int mockCount = sizeof(mock) / sizeof(mock[0]);
    for (int i = 0; i < mockCount; i++) {
        students[i] = mock[i];
    }
    *n = mockCount;
    printf("Da sinh %d sinh vien gia lap.\n", mockCount);
}

void showMenu() {
    printf("\n========== STUDENT MANAGER ==========\n");
    printf("1.  Nhap sinh vien\n");
    printf("2.  Hien thi danh sach\n");
    printf("3.  Ghi vao file\n");
    printf("4.  Doc tu file\n");
    printf("5.  Tim kiem theo ID\n");
    printf("6.  Sap xep theo GPA\n");
    printf("7.  Them 1 sinh vien\n");
    printf("8.  Xoa sinh vien\n");
    printf("9.  Sinh du lieu mau\n");
    printf("0.  Thoat\n");
    printf("=====================================\n");
    printf("Lua chon: ");
}


int main() {
    Student students[MAX_STUDENTS];
    int n = 0;
    int choice;

    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Input khong hop le!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: menuInputStudents(students, &n); break;
            case 2: printStudents(students, n); break;
            case 3: menuFileOperation(students, &n, 0); break;
            case 4: menuFileOperation(students, &n, 1); break;
            case 5: menuSearch(students, n); break;
            case 6: menuSort(students, n); break;
            case 7: menuAdd(students, &n); break;
            case 8: menuDelete(students, &n); break;
            case 9: menuGenerateMock(students, &n); break;
            case 0: printf("\nCam on da su dung chuong trinh!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    return 0;
}