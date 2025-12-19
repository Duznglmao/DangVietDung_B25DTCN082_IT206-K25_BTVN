// ================== CHUONG TRINH TRO CHOI TRAC NGHIEM DON GIAN ==================
// Chuc nang chinh:
// 1. Hien thi cau hoi trac nghiem, moi lan choi lay ngau nhien 5 cau
// 2. Nguoi choi nhap dap an A/B/C/D
// 3. Tinh diem, luu diem vao file va hien thi bang xep hang

#include <stdio.h>   // printf, scanf, FILE, fopen, fprintf, fgets, fclose
#include <stdlib.h>  // rand, srand
#include <string.h>  // strcpy, strcmp
#include <time.h>    // time (dung lam seed cho rand)
#include <ctype.h>   // toupper (chuyen chu thuong -> chu hoa)

// So luong cau hoi co trong chuong trinh
#define TONG_CAU_HOI 10
// So cau hoi se duoc hoi moi lan choi
#define SO_CAU_CHOI 5
// So nguoi choi toi da doc tu file bang xep hang
#define MAX_NGUOI_CHOI 100

// ------------------ KIEU DU LIEU CAU HOI ------------------
// Luu thong tin mot cau hoi trac nghiem
typedef struct {
    char cauHoi[200];       // Noi dung cau hoi
    char luaChon[4][100];   // 4 lua chon A, B, C, D
    char dapAn;             // Dap an dung: 'A', 'B', 'C' hoac 'D'
} CauHoi;

// ------------------ KIEU DU LIEU NGUOI CHOI ------------------
// Luu thong tin ten va diem cua moi lan choi
typedef struct {
    char ten[50];
    int diem;
} NguoiChoi;

// ------------------ NGUYEN MAU HAM ------------------
void khoiTaoCauHoi(CauHoi dsCauHoi[]);
void xaoTronChiSoCauHoi(int mangIndex[], int soLuong);
int choiGame(CauHoi dsCauHoi[], char tenNguoiChoi[]);
void luuDiem(const char tenNguoiChoi[], int diem);
int docDanhSachDiem(NguoiChoi danhSach[], int maxNguoi);
void sapXepDiemGiamDan(NguoiChoi danhSach[], int soNguoi);
void hienThiBangXepHang();

// ------------------ HAM MAIN ------------------
// Luong chinh:
// 1. Khoi tao danh sach cau hoi
// 2. Nhap ten nguoi choi
// 3. Goi ham choiGame -> tra ve diem
// 4. Luu diem vao file
// 5. Doc file va hien thi bang xep hang
int main() {
    CauHoi dsCauHoi[TONG_CAU_HOI];  // Mang luu toan bo cau hoi
    khoiTaoCauHoi(dsCauHoi);        // Nap du lieu cau hoi vao mang

    char tenNguoiChoi[50];
    printf("Nhap ten nguoi choi: ");
    // " %[^\n]" -> doc ca dong, ke ca khoang trang, den khi gap '\n'
    scanf(" %[^\n]", tenNguoiChoi);

    // Choi game va nhan ve so diem dat duoc
    int diem = choiGame(dsCauHoi, tenNguoiChoi);

    // Luu diem vao file
    luuDiem(tenNguoiChoi, diem);

    // Hien thi bang xep hang sau moi lan choi
    hienThiBangXepHang();

    printf("\nNhan phim bat ky de thoat...");
    getchar(); // doc ky tu '\n' con lai
    getchar(); // cho nguoi dung nhan phim
    return 0;
}

// ------------------ KHOI TAO DANH SACH CAU HOI ------------------
// Ham nay gan noi dung cau hoi, 4 dap an va dap an dung cho tung cau
void khoiTaoCauHoi(CauHoi dsCauHoi[]) {
    // Cau 0
    strcpy(dsCauHoi[0].cauHoi, "Thu do cua Viet Nam la?");
    strcpy(dsCauHoi[0].luaChon[0], "A. Ha Noi");
    strcpy(dsCauHoi[0].luaChon[1], "B. TP Ho Chi Minh");
    strcpy(dsCauHoi[0].luaChon[2], "C. Da Nang");
    strcpy(dsCauHoi[0].luaChon[3], "D. Hue");
    dsCauHoi[0].dapAn = 'A';

    // Cau 1
    strcpy(dsCauHoi[1].cauHoi, "Ngon ngu nao dung de viet he dieu hanh Linux?");
    strcpy(dsCauHoi[1].luaChon[0], "A. Python");
    strcpy(dsCauHoi[1].luaChon[1], "B. C");
    strcpy(dsCauHoi[1].luaChon[2], "C. Java");
    strcpy(dsCauHoi[1].luaChon[3], "D. Go");
    dsCauHoi[1].dapAn = 'B';

    // Cau 2
    strcpy(dsCauHoi[2].cauHoi, "Ai la tac gia Truyen Kieu?");
    strcpy(dsCauHoi[2].luaChon[0], "A. Nguyen Du");
    strcpy(dsCauHoi[2].luaChon[1], "B. Nguyen Trai");
    strcpy(dsCauHoi[2].luaChon[2], "C. Ho Xuan Huong");
    strcpy(dsCauHoi[2].luaChon[3], "D. To Huu");
    dsCauHoi[2].dapAn = 'A';

    // Cau 3
    strcpy(dsCauHoi[3].cauHoi, "So Pi (pi) xap xi bang?");
    strcpy(dsCauHoi[3].luaChon[0], "A. 2.14");
    strcpy(dsCauHoi[3].luaChon[1], "B. 3.14");
    strcpy(dsCauHoi[3].luaChon[2], "C. 4.13");
    strcpy(dsCauHoi[3].luaChon[3], "D. 3.41");
    dsCauHoi[3].dapAn = 'B';

    // Cau 4
    strcpy(dsCauHoi[4].cauHoi, "Ngon ngu pho bien nhat de lap trinh web?");
    strcpy(dsCauHoi[4].luaChon[0], "A. C++");
    strcpy(dsCauHoi[4].luaChon[1], "B. JavaScript");
    strcpy(dsCauHoi[4].luaChon[2], "C. PHP");
    strcpy(dsCauHoi[4].luaChon[3], "D. Ruby");
    dsCauHoi[4].dapAn = 'B';

    // Cau 5
    strcpy(dsCauHoi[5].cauHoi, "He dieu hanh Windows do cong ty nao phat trien?");
    strcpy(dsCauHoi[5].luaChon[0], "A. Apple");
    strcpy(dsCauHoi[5].luaChon[1], "B. Google");
    strcpy(dsCauHoi[5].luaChon[2], "C. Microsoft");
    strcpy(dsCauHoi[5].luaChon[3], "D. IBM");
    dsCauHoi[5].dapAn = 'C';

    // Cau 6
    strcpy(dsCauHoi[6].cauHoi, "Quoc gia nao co dien tich lon nhat the gioi?");
    strcpy(dsCauHoi[6].luaChon[0], "A. My");
    strcpy(dsCauHoi[6].luaChon[1], "B. Trung Quoc");
    strcpy(dsCauHoi[6].luaChon[2], "C. Nga");
    strcpy(dsCauHoi[6].luaChon[3], "D. Canada");
    dsCauHoi[6].dapAn = 'C';

    // Cau 7
    strcpy(dsCauHoi[7].cauHoi, "HTML dung de lam gi?");
    strcpy(dsCauHoi[7].luaChon[0], "A. Thiet ke giao dien web");
    strcpy(dsCauHoi[7].luaChon[1], "B. Lap trinh he thong");
    strcpy(dsCauHoi[7].luaChon[2], "C. Phan tich du lieu");
    strcpy(dsCauHoi[7].luaChon[3], "D. Viet ung dung di dong");
    dsCauHoi[7].dapAn = 'A';

    // Cau 8
    strcpy(dsCauHoi[8].cauHoi, "Ai la nha bac hoc voi thuyet tuong doi?");
    strcpy(dsCauHoi[8].luaChon[0], "A. Newton");
    strcpy(dsCauHoi[8].luaChon[1], "B. Einstein");
    strcpy(dsCauHoi[8].luaChon[2], "C. Galileo");
    strcpy(dsCauHoi[8].luaChon[3], "D. Darwin");
    dsCauHoi[8].dapAn = 'B';

    // Cau 9
    strcpy(dsCauHoi[9].cauHoi, "Song nao dai nhat the gioi?");
    strcpy(dsCauHoi[9].luaChon[0], "A. Amazon");
    strcpy(dsCauHoi[9].luaChon[1], "B. Nile");
    strcpy(dsCauHoi[9].luaChon[2], "C. Mississippi");
    strcpy(dsCauHoi[9].luaChon[3], "D. Mekong");
    dsCauHoi[9].dapAn = 'B';
}

// ------------------ XAO TRON CHI SO CAU HOI ------------------
// Y tuong:
// - Tao mang chi so: 0, 1, 2, ..., TONG_CAU_HOI - 1
// - Dung thuat toan Fisher-Yates de xao tron mang nay
// - Sau do chi can dung mangIndex de truy cap cau hoi theo thu tu ngau nhien
void xaoTronChiSoCauHoi(int mangIndex[], int soLuong) {
    // Buoc 1: khoi tao mang index
    for (int i = 0; i < soLuong; i++) {
        mangIndex[i] = i;
    }

    // Buoc 2: tao seed cho rand() de moi lan chay khac nhau
    srand((unsigned int)time(NULL));

    // Buoc 3: xao tron mang bang Fisher-Yates (di tu cuoi ve dau)
    for (int i = soLuong - 1; i > 0; i--) {
        int j = rand() % (i + 1); // j nam trong [0, i]

        // Hoan doi mangIndex[i] va mangIndex[j]
        int temp = mangIndex[i];
        mangIndex[i] = mangIndex[j];
        mangIndex[j] = temp;
    }
}

// ------------------ HAM CHOI GAME ------------------
// Tra ve: so diem dat duoc
int choiGame(CauHoi dsCauHoi[], char tenNguoiChoi[]) {
    int diem = 0;                        // dem so cau dung
    int mangIndex[TONG_CAU_HOI];         // luu thu tu cau hoi sau khi xao tron

    // Xao tron thu tu cac cau hoi truoc khi hoi
    xaoTronChiSoCauHoi(mangIndex, TONG_CAU_HOI);

    printf("\n=== BAT DAU TRO CHOI ===\n");

    // Moi lan choi chi hoi SO_CAU_CHOI cau dau tien cua mangIndex
    for (int i = 0; i < SO_CAU_CHOI; i++) {
        int idx = mangIndex[i]; // vi tri cau hoi trong mang dsCauHoi

        // Hien thi cau hoi va cac phuong an
        printf("\n--- Cau %d ---\n%s\n", i + 1, dsCauHoi[idx].cauHoi);
        for (int j = 0; j < 4; j++) {
            printf("%s\n", dsCauHoi[idx].luaChon[j]);
        }

        // Nguoi dung nhap dap an
        char ans;
        do {
            printf("Nhap dap an (A-D): ");
            scanf(" %c", &ans);      // co dau cach truoc %c de bo qua ky tu '\n'
            ans = (char)toupper(ans); // chuyen ve chu hoa de de so sanh

            if (ans < 'A' || ans > 'D') {
                printf("Vui long chi nhap ky tu A, B, C hoac D.\n");
            }
        } while (ans < 'A' || ans > 'D'); // lap lai neu nhap sai ki tu

        // Kiem tra dap an
        if (ans == dsCauHoi[idx].dapAn) {
            printf("Chinh xac!\n");
            diem++; // tang diem neu tra loi dung
        } else {
            printf("Sai roi! Dap an dung la %c\n", dsCauHoi[idx].dapAn);
        }
    }

    // Thong bao ket qua
    printf("\n=== KET THUC TRO CHOI ===\n");
    printf("%s dat %d/%d diem.\n", tenNguoiChoi, diem, SO_CAU_CHOI);

    return diem;
}

// ------------------ LUU DIEM VAO FILE ------------------
// File: bangxephang.txt
// Moi dong co dang: <ten_nguoi_choi><tab><diem>
void luuDiem(const char tenNguoiChoi[], int diem) {
    // "a" = append: ghi them vao cuoi file, neu file chua ton tai thi tao moi
    FILE *f = fopen("bangxephang.txt", "a");
    if (f == NULL) {
        printf("Loi: Khong the mo file luu diem.\n");
        return;
    }

    // Ghi ten va diem vao file, ngan cach boi ky tu tab (\t)
    fprintf(f, "%s\t%d\n", tenNguoiChoi, diem);
    fclose(f);

    printf("\nDiem da duoc luu vao file bangxephang.txt\n");
}

// ------------------ DOC DANH SACH DIEM TU FILE ------------------
// Tra ve: so nguoi choi da doc duoc
int docDanhSachDiem(NguoiChoi danhSach[], int maxNguoi) {
    FILE *f = fopen("bangxephang.txt", "r"); // "r" = read: chi doc
    if (f == NULL) {
        // File chua ton tai -> chua co du lieu
        return 0;
    }

    int soNguoi = 0;
    char dong[100]; // luu tung dong doc duoc

    // Doc tung dong den khi het file hoac du maxNguoi
    while (fgets(dong, sizeof(dong), f) != NULL && soNguoi < maxNguoi) {
        char ten[50];
        int diem;

        // %[^\t] doc tat ca ky tu den truoc '\t'
        if (sscanf(dong, "%[^\t]\t%d", ten, &diem) == 2) {
            strcpy(danhSach[soNguoi].ten, ten);
            danhSach[soNguoi].diem = diem;
            soNguoi++;
        }
    }

    fclose(f);
    return soNguoi;
}

// ------------------ SAP XEP DIEM GIAM DAN ------------------
// Su dung thuat toan bubble sort don gian, phu hop cho nguoi moi hoc
void sapXepDiemGiamDan(NguoiChoi danhSach[], int soNguoi) {
    for (int i = 0; i < soNguoi - 1; i++) {
        for (int j = 0; j < soNguoi - i - 1; j++) {
            if (danhSach[j].diem < danhSach[j + 1].diem) {
                // Hoan doi hai phan tu neu diem dung truoc nho hon
                NguoiChoi temp = danhSach[j];
                danhSach[j] = danhSach[j + 1];
                danhSach[j + 1] = temp;
            }
        }
    }
}

// ------------------ HIEN THI BANG XEP HANG ------------------
// Buoc 1: Doc toan bo diem tu file vao mang danhSach
// Buoc 2: Sap xep giam dan theo diem
// Buoc 3: In ra man hinh theo thu tu tu cao den thap
void hienThiBangXepHang() {
    NguoiChoi danhSach[MAX_NGUOI_CHOI];

    // Doc du lieu tu file
    int soNguoi = docDanhSachDiem(danhSach, MAX_NGUOI_CHOI);
    if (soNguoi == 0) {
        printf("\nChua co du lieu bang xep hang.\n");
        return;
    }

    // Sap xep theo diem giam dan
    sapXepDiemGiamDan(danhSach, soNguoi);

    // In bang xep hang
    printf("\n========== BANG XEP HANG ==========\n");
    printf("%-3s %-30s %s\n", "STT", "Ten Nguoi Choi", "Diem");
    printf("----------------------------------------\n");

    for (int i = 0; i < soNguoi; i++) {
        printf("%-3d %-30s %d\n", i + 1, danhSach[i].ten, danhSach[i].diem);
    }

    printf("========================================\n");
}
