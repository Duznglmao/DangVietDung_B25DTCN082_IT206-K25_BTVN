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

int main() {
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

        printf("  ID: ");
        scanf("%d", &students[i].id);
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

        printf("  GPA: ");
        scanf("%f", &students[i].gpa);

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
    }

    return 0;
}