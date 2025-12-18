#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float gpa;
} Student;

int main() {
    Student students[3] = {
        {1, "Nguyen Minh Hien", 18, 4.0},
        {2, "Vu Le Minh Hieu", 18, 3.8},
        {3, "Quach Tran Anh", 18, 3.9}
    };

    printf("+----+----------------------+-----+------+\n");
    printf("| %-2s | %-20s | %-3s | %-4s |\n", "ID", "Name", "Age", "GPA");
    printf("+----+----------------------+-----+------+\n");

    for (int i = 0; i < 3; i++) {
        printf("| %-2d | %-20s | %-3d | %-4.2f |\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].gpa);
    }

    printf("+----+----------------------+-----+------+\n");

    return 0;
}