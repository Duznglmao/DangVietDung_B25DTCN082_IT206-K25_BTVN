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

void saveToFile(const char *filename, Student students[], int n) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Khong mo duoc file %s de ghi!\n", filename);
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
    printf("Da luu danh sach sinh vien vao file %s\n", filename);
}

int loadFromFile(const char *filename, Student students[], int maxN) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong mo duoc file %s de doc!\n", filename);
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

void sortByGPA(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (students[j].gpa < students[minIndex].gpa) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Student tmp = students[i];
            students[i] = students[minIndex];
            students[minIndex] = tmp;
        }
    }
}

int addStudent(Student students[], int *n, int maxN, Student newS) {
    if (*n >= maxN) {
        printf("Mang da day, khong the them sinh vien moi!\n");
        return 0;
    }

    for (int i = 0; i < *n; i++) {
        if (students[i].id == newS.id) {
            printf("ID %d da ton tai, khong the them sinh vien moi!\n", newS.id);
            return 0;
        }
    }

    students[*n] = newS;
    (*n)++;
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
        printf("Khong tim thay sinh vien co ID = %d de xoa!\n", id);
        return 0;
    }

    for (int i = index; i < *n - 1; i++) {
        students[i] = students[i + 1];
    }
    (*n)--;
    return 1;
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

void runSortTestCases() {
    printf("==================================================\n");
    printf("==  Chay TEST CASES cho ham sortByGPA          ==\n");
    printf("==================================================\n\n");

    Student sameGpa[4] = {
        {1, "A", 20, 3.0f},
        {2, "B", 21, 3.0f},
        {3, "C", 22, 3.0f},
        {4, "D", 23, 3.0f}
    };
    printf("TC1 - GPA bang nhau:\n");
    printf("  Truoc khi sap xep (ID - GPA):\n");
    for (int i = 0; i < 4; i++) {
        printf("    %d - %.2f\n", sameGpa[i].id, sameGpa[i].gpa);
    }
    sortByGPA(sameGpa, 4);
    printf("  Sau khi sap xep (ID - GPA):\n");
    for (int i = 0; i < 4; i++) {
        printf("    %d - %.2f\n", sameGpa[i].id, sameGpa[i].gpa);
    }
    printf("\n");

    Student sortedGpa[4] = {
        {1, "A", 20, 1.5f},
        {2, "B", 21, 2.0f},
        {3, "C", 22, 3.0f},
        {4, "D", 23, 3.5f}
    };
    printf("TC2 - GPA da tang dan san:\n");
    printf("  Truoc khi sap xep (ID - GPA):\n");
    for (int i = 0; i < 4; i++) {
        printf("    %d - %.2f\n", sortedGpa[i].id, sortedGpa[i].gpa);
    }
    sortByGPA(sortedGpa, 4);
    printf("  Sau khi sap xep (ID - GPA):\n");
    for (int i = 0; i < 4; i++) {
        printf("    %d - %.2f\n", sortedGpa[i].id, sortedGpa[i].gpa);
    }
    printf("\n");

    Student randomGpa[5] = {
        {1, "A", 20, 3.2f},
        {2, "B", 21, 2.1f},
        {3, "C", 22, 3.9f},
        {4, "D", 23, 1.8f},
        {5, "E", 24, 2.7f}
    };
    printf("TC3 - GPA ngau nhien:\n");
    printf("  Truoc khi sap xep (ID - GPA):\n");
    for (int i = 0; i < 5; i++) {
        printf("    %d - %.2f\n", randomGpa[i].id, randomGpa[i].gpa);
    }
    sortByGPA(randomGpa, 5);
    printf("  Sau khi sap xep (ID - GPA):\n");
    for (int i = 0; i < 5; i++) {
        printf("    %d - %.2f\n", randomGpa[i].id, randomGpa[i].gpa);
    }
    printf("\n");

    printf("==============================================\n");
    printf("==       Ket thuc TEST CASES SORT GPA       ==\n");
    printf("==============================================\n\n");
}

void generateMockClasses() {
    Student classA[] = {
        {101, "A_Student1", 18, 3.2f},
        {102, "A_Student2", 19, 3.8f},
        {103, "A_Student3", 18, 2.9f}
    };
    Student classB[] = {
        {201, "B_Student1", 20, 2.5f},
        {202, "B_Student2", 21, 3.0f},
        {203, "B_Student3", 20, 3.7f},
        {204, "B_Student4", 19, 3.1f}
    };
    Student classC[] = {
        {301, "C_Student1", 19, 3.9f},
        {302, "C_Student2", 18, 3.4f}
    };

    saveToFile("classA.txt", classA, sizeof(classA) / sizeof(classA[0]));
    saveToFile("classB.txt", classB, sizeof(classB) / sizeof(classB[0]));
    saveToFile("classC.txt", classC, sizeof(classC) / sizeof(classC[0]));

    printf("\nDa sinh du lieu gia lap cho 3 lop: classA.txt, classB.txt, classC.txt\n\n");
}

void runAddRemoveTestCases() {
    printf("==================================================\n");
    printf("==  Chay TEST CASES cho addStudent/removeStudentById ==\n");
    printf("==================================================\n\n");

    Student arr[5] = {
        {1, "A", 20, 3.0f},
        {2, "B", 21, 3.5f},
        {3, "C", 22, 2.8f}
    };
    int n = 3;
    int maxN = 5;

    printf("Trang thai ban dau (n = %d):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  ID=%d, Name=%s, GPA=%.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
    printf("\n");

    printf("TC1 - Them sinh vien moi voi ID bi trung (ID = 2):\n");
    Student newS1 = {2, "TrungID", 19, 3.6f};
    int rs1 = addStudent(arr, &n, maxN, newS1);
    printf("  Ket qua addStudent: %s (n hien tai = %d)\n\n", rs1 ? "THANH CONG" : "THAT BAI", n);

    printf("TC2 - Xoa sinh vien voi ID khong ton tai (ID = 99):\n");
    int rs2 = removeStudentById(arr, &n, 99);
    printf("  Ket qua removeStudentById: %s (n hien tai = %d)\n\n", rs2 ? "THANH CONG" : "THAT BAI", n);

    printf("TC3 - Them sinh vien moi voi ID khac (ID = 4):\n");
    Student newS2 = {4, "NewStudent", 20, 3.9f};
    int rs3 = addStudent(arr, &n, maxN, newS2);
    printf("  Ket qua addStudent: %s (n hien tai = %d)\n", rs3 ? "THANH CONG" : "THAT BAI", n);
    printf("  Danh sach sau khi them:\n");
    for (int i = 0; i < n; i++) {
        printf("    ID=%d, Name=%s, GPA=%.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
    printf("\n");

    printf("TC4 - Xoa sinh vien voi ID ton tai (ID = 1):\n");
    int rs4 = removeStudentById(arr, &n, 1);
    printf("  Ket qua removeStudentById: %s (n hien tai = %d)\n", rs4 ? "THANH CONG" : "THAT BAI", n);
    printf("  Danh sach sau khi xoa:\n");
    for (int i = 0; i < n; i++) {
        printf("    ID=%d, Name=%s, GPA=%.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
    printf("\n");

    printf("==================================================\n");
    printf("==      Ket thuc TEST CASES ADD/REMOVE         ==\n");
    printf("==================================================\n\n");
}

int main() {
    runTestCases();
    runGpaTestCases();
    runSortTestCases();
    runAddRemoveTestCases();
    generateMockClasses();

    Student students[5];
    int n;

    printf("=== Nhap danh sach sinh vien moi (toi da 5) ===\n");
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

    sortByGPA(students, n);

    printf("\nDanh sach sinh vien vua nhap (da sap xep theo GPA tang dan):\n");
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

    char filename[100];
    printf("\nNhap ten file lop can doc du lieu (vd: classA.txt): ");
    scanf("%99s", filename);

    Student loaded[50];
    int loadedCount = loadFromFile(filename, loaded, 50);

    if (loadedCount > 0) {
        printf("\nDanh sach sinh vien doc tu file %s:\n", filename);
        printf("+-----+----------------------+-----+------+\n");
        printf("| %-3s | %-20s | %-3s | %-4s |\n", "ID", "Name", "Age", "GPA");
        printf("+----+-----------------------+-----+------+\n");

        for (int i = 0; i < loadedCount; i++) {
            printf("| %-2d | %-20s | %-3d | %-4.2f |\n",
                   loaded[i].id,
                   loaded[i].name,
                   loaded[i].age,
                   loaded[i].gpa);
        }

        printf("+-----+----------------------+-----+------+\n");
    } else {
        printf("\nKhong doc duoc du lieu tu file %s\n", filename);
    }

    return 0;
}