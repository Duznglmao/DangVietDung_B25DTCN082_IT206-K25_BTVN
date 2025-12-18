#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float gpa;
} Student;

void trimRight(char *str) {
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n' || str[len - 1] == '\r' || str[len - 1] == '\t')) {
        str[len - 1] = '\0';
        len--;
    }
}

void saveToFile(Student students[], int n) {
    FILE *f = fopen("students.txt", "w");
    if (f == NULL) {
        printf("Khong mo duoc file students.txt de ghi!\n");
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
    printf("Da luu danh sach sinh vien vao file students.txt\n");
}

int loadFromFile(Student students[], int maxN) {
    FILE *f = fopen("students.txt", "r");
    if (f == NULL) {
        printf("Khong mo duoc file students.txt de doc!\n");
        return 0;
    }

    char line[256];
    int n = 0;

    for (int i = 0; i < 3 && fgets(line, sizeof(line), f); i++);

    while (fgets(line, sizeof(line), f) && n < maxN) {
        if (line[0] != '|') {
            continue;
        }

        if (sscanf(line, "| %d | %49[^|] | %d | %f |",
            &students[n].id,
            students[n].name,
            &students[n].age,
            &students[n].gpa) == 4) {
            trimRight(students[n].name);
            n++;
        }
    }

    fclose(f);
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
    if (n <= 0) {
        return 0.0f;
    }
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += students[i].gpa;
    }
    return sum / n;
}

void runTestCases() {
    printf("==============================================\n");
    printf("==  Chay TEST CASES cho ham findStudentById ==\n");
    printf("==============================================\n\n");

    Student testStudents[3] = {
        {1, "A", 20, 3.5f},
        {2, "B", 21, 3.8f},
        {3, "C", 19, 3.2f}
    };
    int testIds[3] = {2, 10, -5};
    const char *descs[3] = {
        "Test 1 - ID ton tai (2)",
        "Test 2 - ID khong ton tai (10)",
        "Test 3 - ID am (-5)"
    };

    for (int i = 0; i < 3; i++) {
        printf("----------------------------------------------\n");
        printf("  %-35s\n", descs[i]);
        printf("----------------------------------------------\n");
        printf("| %-2s | %-20s | %-3s | %-4s |\n", "ID", "Name", "Age", "GPA");
        printf("+----+----------------------+-----+------+\n");
        Student *found = findStudentById(testStudents, 3, testIds[i]);
        if (found != NULL) {
            printf("| %-2d | %-20s | %-3d | %-4.2f |\n",
                found->id, found->name, found->age, found->gpa);
            printf("+----+----------------------+-----+------+\n");
            printf(">> KET QUA: TIM THAY ID = %d <<\n", testIds[i]);
        } else {
            printf(">> KET QUA: KHONG TIM THAY ID = %d <<\n", testIds[i]);
        }
        printf("\n");
    }

    printf("==============================================\n");
    printf("==       Ket thuc TEST CASES                ==\n");
    printf("==============================================\n\n");
}

void runGpaTestCases() {
    printf("==================================================\n");
    printf("==  Chay TEST CASES cho ham calculateAverageGPA ==\n");
    printf("==================================================\n\n");

    Student mockStudents[10] = {
        {1, "S1",  20, 2.0f},
        {2, "S2",  21, 2.5f},
        {3, "S3",  22, 3.0f},
        {4, "S4",  19, 3.5f},
        {5, "S5",  20, 4.0f},
        {6, "S6",  21, 1.8f},
        {7, "S7",  22, 2.7f},
        {8, "S8",  23, 3.9f},
        {9, "S9",  18, 3.3f},
        {10,"S10", 19, 2.2f}
    };

    float avgGpa10 = calculateAverageGPA(mockStudents, 10);
    printf("TC1 - 10 sinh vien gia lap:\n");
    printf("  So luong: 10\n");
    printf("  GPA trung binh tinh duoc: %.2f\n\n", avgGpa10);

    Student emptyList[1]; 
    float avgEmpty = calculateAverageGPA(emptyList, 0);
    printf("TC2 - Danh sach rong (n = 0):\n");
    printf("  So luong: 0\n");
    printf("  GPA trung binh tinh duoc: %.2f (mong doi: 0.00)\n\n", avgEmpty);

    printf("==============================================\n");
    printf("==       Ket thuc TEST CASES GPA            ==\n");
    printf("==============================================\n\n");
}

int main() {
    runTestCases();
    runGpaTestCases();

    Student students[5];
    int n;

    do {
        printf("Nhap so luong sinh vien (toi da 5): ");
        scanf("%d", &n);
        if (n < 1 || n > 5) {
            printf("So luong khong hop le. Vui long nhap lai.\n");
        }
    } while (n < 1 || n > 5);

    getchar();

    for (int i = 0; i < n; i++) {
        printf("\nSinh vien thu %d:\n", i + 1);

        int validId;
        do {
            validId = 1;
            printf("  ID: ");
            scanf("%d", &students[i].id);

            for (int k = 0; k < i; k++) {
                if (students[k].id == students[i].id) {
                    printf("  ID da ton tai, vui long nhap ID khac!\n");
                    validId = 0;
                    break;
                }
            }
        } while (!validId);
        getchar();

        printf("  Ho ten: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        int j = 0;
        while (students[i].name[j] != '\0') {
            if (students[i].name[j] == '\n') {
                students[i].name[j] = '\0';
                break;
            }
            j++;
        }

        printf("  Tuoi: ");
        scanf("%d", &students[i].age);

        do {
            printf("  GPA: ");
            scanf("%f", &students[i].gpa);
            if (students[i].gpa <= 0 || students[i].gpa > 4.0f) {
                printf("  GPA phai la so thuc duong va khong lon hon 4.0. Vui long nhap lai!\n");
            }
        } while (students[i].gpa <= 0 || students[i].gpa > 4.0f);

        getchar();
    }

    printf("\nDanh sach sinh vien vua nhap:\n");
    printf("+----+----------------------+-----+------+\n");
    printf("| %-2s | %-20s | %-3s | %-4s |\n", "ID", "Name", "Age", "GPA");
    printf("+----+----------------------+-----+------+\n");

    for (int i = 0; i < n; i++) {
        printf("| %-2d | %-20s | %-3d | %-4.2f |\n",
            students[i].id,
            students[i].name,
            students[i].age,
            students[i].gpa);
    }

    printf("+----+----------------------+-----+------+\n");

    saveToFile(students, n);

    Student loaded[5];
    int loadedCount = loadFromFile(loaded, 5);

    if (loadedCount > 0) {
        printf("\nDanh sach sinh vien doc tu file:\n");
        printf("+----+----------------------+-----+------+\n");
        printf("| %-2s | %-20s | %-3s | %-4s |\n", "ID", "Name", "Age", "GPA");
        printf("+----+----------------------+-----+------+\n");

        for (int i = 0; i < loadedCount; i++) {
            printf("| %-2d | %-20s | %-3d | %-4.2f |\n",
                loaded[i].id,
                loaded[i].name,
                loaded[i].age,
                loaded[i].gpa);
        }

        printf("+----+----------------------+-----+------+\n");

        int searchId;
        printf("\nNhap ID can tim: ");
        scanf("%d", &searchId);

        Student *found = findStudentById(loaded, loadedCount, searchId);
        if (found != NULL) {
            printf("\nTim thay sinh vien:\n");
            printf("+----+----------------------+-----+------+\n");
            printf("| %-2s | %-20s | %-3s | %-4s |\n", "ID", "Name", "Age", "GPA");
            printf("+----+----------------------+-----+------+\n");
            printf("| %-2d | %-20s | %-3d | %-4.2f |\n",
                found->id, found->name, found->age, found->gpa);
            printf("+----+----------------------+-----+------+\n");
        } else {
            printf("\nKhong tim thay sinh vien co ID = %d\n", searchId);
        }
    }

    return 0;
}