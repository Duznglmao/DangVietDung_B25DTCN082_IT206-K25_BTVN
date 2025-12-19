#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TONG_CAU_HOI 10
#define SO_CAU_CHOI 5

typedef struct {
    char cauHoi[200];
    char luaChon[4][100];
    char dapAn; // A, B, C, D
} CauHoi;

void khoiTaoCauHoi(CauHoi q[]);
int choiGame(CauHoi q[], char tenNguoiChoi[]);
void luuDiem(char tenNguoiChoi[], int diem);
void hienThiBangXepHang();

int main() {
    CauHoi q[TONG_CAU_HOI];
    khoiTaoCauHoi(q);

    char tenNguoiChoi[50];
    printf("Nhap ten nguoi choi: ");
    scanf(" %[^\n]s", tenNguoiChoi); 

    int diem = choiGame(q, tenNguoiChoi);
    luuDiem(tenNguoiChoi, diem);
    hienThiBangXepHang();

    printf("\nNhan phim bat ky de thoat...");
    getchar(); getchar(); 
    return 0;
}

void khoiTaoCauHoi(CauHoi q[]) {
    strcpy(q[0].cauHoi, "Thu do cua Viet Nam la?");
    strcpy(q[0].luaChon[0], "A. Ha Noi");
    strcpy(q[0].luaChon[1], "B. TP Ho Chi Minh");
    strcpy(q[0].luaChon[2], "C. Da Nang");
    strcpy(q[0].luaChon[3], "D. Hue");
    q[0].dapAn = 'A';

    strcpy(q[1].cauHoi, "Ngon ngu nao dung de viet he dieu hanh Linux?");
    strcpy(q[1].luaChon[0], "A. Python");
    strcpy(q[1].luaChon[1], "B. C");
    strcpy(q[1].luaChon[2], "C. Java");
    strcpy(q[1].luaChon[3], "D. Go");
    q[1].dapAn = 'B';

    strcpy(q[2].cauHoi, "Ai la tac gia Truyen Kieu?");
    strcpy(q[2].luaChon[0], "A. Nguyen Du");
    strcpy(q[2].luaChon[1], "B. Nguyen Trai");
    strcpy(q[2].luaChon[2], "C. Ho Xuan Huong");
    strcpy(q[2].luaChon[3], "D. To Huu");
    q[2].dapAn = 'A';

    strcpy(q[3].cauHoi, "So Pi (pi) xap xi bang?");
    strcpy(q[3].luaChon[0], "A. 2.14");
    strcpy(q[3].luaChon[1], "B. 3.14");
    strcpy(q[3].luaChon[2], "C. 4.13");
    strcpy(q[3].luaChon[3], "D. 3.41");
    q[3].dapAn = 'B';

    strcpy(q[4].cauHoi, "Ngon ngu pho bien nhat de lap trinh web?");
    strcpy(q[4].luaChon[0], "A. C++");
    strcpy(q[4].luaChon[1], "B. JavaScript");
    strcpy(q[4].luaChon[2], "C. PHP");
    strcpy(q[4].luaChon[3], "D. Ruby");
    q[4].dapAn = 'B';

    strcpy(q[5].cauHoi, "He dieu hanh Windows do cong ty nao phat trien?");
    strcpy(q[5].luaChon[0], "A. Apple");
    strcpy(q[5].luaChon[1], "B. Google");
    strcpy(q[5].luaChon[2], "C. Microsoft");
    strcpy(q[5].luaChon[3], "D. IBM");
    q[5].dapAn = 'C';

    strcpy(q[6].cauHoi, "Quoc gia nao co dien tich lon nhat the gioi?");
    strcpy(q[6].luaChon[0], "A. My");
    strcpy(q[6].luaChon[1], "B. Trung Quoc");
    strcpy(q[6].luaChon[2], "C. Nga");
    strcpy(q[6].luaChon[3], "D. Canada");
    q[6].dapAn = 'C';

    strcpy(q[7].cauHoi, "HTML dung de lam gi?");
    strcpy(q[7].luaChon[0], "A. Thiet ke giao dien web");
    strcpy(q[7].luaChon[1], "B. Lap trinh he thong");
    strcpy(q[7].luaChon[2], "C. Phan tich du lieu");
    strcpy(q[7].luaChon[3], "D. Viet ung dung di dong");
    q[7].dapAn = 'A';

    strcpy(q[8].cauHoi, "Ai la nha bac hoc voi thuyet tuong doi?");
    strcpy(q[8].luaChon[0], "A. Newton");
    strcpy(q[8].luaChon[1], "B. Einstein");
    strcpy(q[8].luaChon[2], "C. Galileo");
    strcpy(q[8].luaChon[3], "D. Darwin");
    q[8].dapAn = 'B';

    strcpy(q[9].cauHoi, "Song nao dai nhat the gioi?");
    strcpy(q[9].luaChon[0], "A. Amazon");
    strcpy(q[9].luaChon[1], "B. Nile");
    strcpy(q[9].luaChon[2], "C. Mississippi");
    strcpy(q[9].luaChon[3], "D. Mekong");
    q[9].dapAn = 'B';
}

int choiGame(CauHoi q[], char tenNguoiChoi[]) {
    int diem = 0;
    int daChon[SO_CAU_CHOI];
    srand(time(NULL));

    for (int i = 0; i < SO_CAU_CHOI; i++) {
        int idx;
        int khac;
        do {
            idx = rand() % TONG_CAU_HOI;
            khac = 1;
            for (int j = 0; j < i; j++) {
                if (daChon[j] == idx) {
                    khac = 0;
                    break;
                }
            }
        } while (!khac);
        daChon[i] = idx;

        printf("\n--- Cau %d ---\n%s\n", i+1, q[idx].cauHoi);
        for (int j = 0; j < 4; j++) {
            printf("%s\n", q[idx].luaChon[j]);
        }

        char ans;
        do {
            printf("Nhap dap an (A-D): ");
            scanf(" %c", &ans);
            ans = toupper(ans); 
            if (ans < 'A' || ans > 'D') {
                printf("Vui long chi nhap ky tu A, B, C hoac D.\n");
            }
        } while (ans < 'A' || ans > 'D');

        if (ans == q[idx].dapAn) {
            printf("Chinh xac!\n");
            diem++;
        } else {
            printf("Sai roi! Dap an dung la %c\n", q[idx].dapAn);
        }
    }

    printf("\nKet thuc! %s dat %d/%d diem.\n", tenNguoiChoi, diem, SO_CAU_CHOI);
    return diem;
}

void luuDiem(char tenNguoiChoi[], int diem) {
    FILE *f = fopen("bangxephang.txt", "a");
    if (f == NULL) {
        printf("Loi: Khong the mo file luu diem.\n");
        return;
    }
    fprintf(f, "%-20s\t%d\n", tenNguoiChoi, diem);
    fclose(f);
}

void hienThiBangXepHang() {
    FILE *f = fopen("bangxephang.txt", "r");
    if (f == NULL) {
        printf("\nChua co du lieu bang xep hang.\n");
        return;
    }
    printf("\n========== BANG XEP HANG ==========\n");
    printf("%-20s\t%s\n", "Ten Nguoi Choi", "Diem");
    printf("-----------------------------------\n");
    char dong[100];
    while (fgets(dong, sizeof(dong), f)) {
        printf("%s", dong);
    }
    fclose(f);
}