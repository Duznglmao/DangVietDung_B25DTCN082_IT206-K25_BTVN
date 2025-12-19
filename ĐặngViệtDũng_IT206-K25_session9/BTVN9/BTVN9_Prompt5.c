// ================== CHUONG TRINH TRO CHOI TRAC NGHIEM DON GIAN ==================
// Chuc nang chinh:
// 1. Hien thi cau hoi trac nghiem, moi lan choi lay ngau nhien 5 cau
// 2. Nguoi choi nhap dap an A/B/C/D
// 3. Tinh diem, luu diem vao file va hien thi bang xep hang
//
// Cau truc refactor:
// - Cac ham duoc tach thanh nhom chuc nang ro rang
// - Code de doc va de bao tri hon

#include <stdio.h>   // printf, scanf, FILE, fopen, fprintf, fgets, fclose
#include <stdlib.h>  // rand, srand
#include <string.h>  // strcpy, strcmp
#include <time.h>    // time (dung lam seed cho rand)
#include <ctype.h>   // toupper (chuyen chu thuong -> chu hoa)

// ================== CAC HANG SO ==================
#define TONG_CAU_HOI 10        // So luong cau hoi co trong chuong trinh
#define SO_CAU_CHOI 5          // So cau hoi se duoc hoi moi lan choi
#define MAX_NGUOI_CHOI 100     // So nguoi choi toi da doc tu file bang xep hang
#define TEN_FILE_XEP_HANG "bangxephang.txt"  // Ten file luu bang xep hang

// ================== CAC KIEU DU LIEU ==================
// Luu thong tin mot cau hoi trac nghiem
typedef struct {
    char cauHoi[200];       // Noi dung cau hoi
    char luaChon[4][100];   // 4 lua chon A, B, C, D
    char dapAn;             // Dap an dung: 'A', 'B', 'C' hoac 'D'
} CauHoi;

// Luu thong tin ten va diem cua moi lan choi
typedef struct {
    char ten[50];
    int diem;
} NguoiChoi;

// ================== NGUYEN MAU HAM ==================
// Nhom 1: Quan ly cau hoi
void khoiTaoCauHoi(CauHoi dsCauHoi[]);
void xaoTronChiSoCauHoi(int mangIndex[], int soLuong);
void hienThiCauHoi(const CauHoi *cauHoi, int soThuTu);

// Nhom 2: Xu ly game
char nhapDapAn();
int kiemTraDapAn(char dapAnNguoiChoi, char dapAnDung);
int choiGame(CauHoi dsCauHoi[], const char tenNguoiChoi[]);

// Nhom 3: Quan ly diem va file
void luuDiem(const char tenNguoiChoi[], int diem);
int docDanhSachDiem(NguoiChoi danhSach[], int maxNguoi);

// Nhom 4: Bang xep hang
void sapXepDiemGiamDan(NguoiChoi danhSach[], int soNguoi);
void hienThiBangXepHang();

// Nhom 5: Ham tien ich
void nhapTenNguoiChoi(char ten[], int doDai);

// ================== HAM MAIN ==================
int main() {
    // Khoi tao danh sach cau hoi
    CauHoi dsCauHoi[TONG_CAU_HOI];
    khoiTaoCauHoi(dsCauHoi);

    // Nhap ten nguoi choi
    char tenNguoiChoi[50];
    nhapTenNguoiChoi(tenNguoiChoi, sizeof(tenNguoiChoi));

    // Choi game va nhan ve so diem dat duoc
    int diem = choiGame(dsCauHoi, tenNguoiChoi);

    // Luu diem vao file
    luuDiem(tenNguoiChoi, diem);

    // Hien thi bang xep hang sau moi lan choi
    hienThiBangXepHang();

    // Cho nguoi dung nhan phim de thoat
    printf("\nNhan phim bat ky de thoat...");
    getchar(); // doc ky tu '\n' con lai
    getchar(); // cho nguoi dung nhan phim
    
    return 0;
}

// ================== NHOM 1: QUAN LY CAU HOI ==================

// Khoi tao danh sach cau hoi voi du lieu co san
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

// Xao tron mang chi so cau hoi bang thuat toan Fisher-Yates
void xaoTronChiSoCauHoi(int mangIndex[], int soLuong) {
    // Buoc 1: Khoi tao mang index: 0, 1, 2, ..., soLuong - 1
    for (int i = 0; i < soLuong; i++) {
        mangIndex[i] = i;
    }

    // Buoc 2: Tao seed cho rand() de moi lan chay khac nhau
    srand((unsigned int)time(NULL));

    // Buoc 3: Xao tron mang bang Fisher-Yates (di tu cuoi ve dau)
    for (int i = soLuong - 1; i > 0; i--) {
        int j = rand() % (i + 1); // j nam trong [0, i]

        // Hoan doi mangIndex[i] va mangIndex[j]
        int temp = mangIndex[i];
        mangIndex[i] = mangIndex[j];
        mangIndex[j] = temp;
    }
}

// Hien thi mot cau hoi va cac phuong an tra loi
void hienThiCauHoi(const CauHoi *cauHoi, int soThuTu) {
    printf("\n--- Cau %d ---\n", soThuTu);
    printf("%s\n", cauHoi->cauHoi);
    
    for (int i = 0; i < 4; i++) {
        printf("%s\n", cauHoi->luaChon[i]);
    }
}

// ================== NHOM 2: XU LY GAME ==================

// Nhap va kiem tra dap an tu nguoi choi (chi nhan A, B, C, D)
char nhapDapAn() {
    char ans;
    
    do {
        printf("Nhap dap an (A-D): ");
        scanf(" %c", &ans);  // Co dau cach truoc %c de bo qua ky tu '\n'
        ans = (char)toupper(ans); // Chuyen ve chu hoa de de so sanh

        if (ans < 'A' || ans > 'D') {
            printf("Vui long chi nhap ky tu A, B, C hoac D.\n");
        }
    } while (ans < 'A' || ans > 'D'); // Lap lai neu nhap sai ki tu
    
    return ans;
}

// Kiem tra dap an cua nguoi choi co dung khong
// Tra ve: 1 neu dung, 0 neu sai
int kiemTraDapAn(char dapAnNguoiChoi, char dapAnDung) {
    if (dapAnNguoiChoi == dapAnDung) {
        printf("Chinh xac!\n");
        return 1;
    } else {
        printf("Sai roi! Dap an dung la %c\n", dapAnDung);
        return 0;
    }
}

// Ham chinh de choi game
// Tra ve: so diem dat duoc
int choiGame(CauHoi dsCauHoi[], const char tenNguoiChoi[]) {
    int diem = 0;
    int mangIndex[TONG_CAU_HOI];

    // Xao tron thu tu cac cau hoi truoc khi hoi
    xaoTronChiSoCauHoi(mangIndex, TONG_CAU_HOI);

    printf("\n=== BAT DAU TRO CHOI ===\n");

    // Moi lan choi chi hoi SO_CAU_CHOI cau dau tien cua mangIndex
    for (int i = 0; i < SO_CAU_CHOI; i++) {
        int idx = mangIndex[i]; // Vi tri cau hoi trong mang dsCauHoi

        // Hien thi cau hoi va cac phuong an
        hienThiCauHoi(&dsCauHoi[idx], i + 1);

        // Nguoi dung nhap dap an
        char dapAnNguoiChoi = nhapDapAn();

        // Kiem tra dap an va cap nhat diem
        if (kiemTraDapAn(dapAnNguoiChoi, dsCauHoi[idx].dapAn)) {
            diem++;
        }
    }

    // Thong bao ket qua
    printf("\n=== KET THUC TRO CHOI ===\n");
    printf("%s dat %d/%d diem.\n", tenNguoiChoi, diem, SO_CAU_CHOI);

    return diem;
}

// ================== NHOM 3: QUAN LY DIEM VA FILE ==================

// Luu diem cua nguoi choi vao file
void luuDiem(const char tenNguoiChoi[], int diem) {
    FILE *f = fopen(TEN_FILE_XEP_HANG, "a"); // "a" = append: ghi them vao cuoi file
    if (f == NULL) {
        printf("Loi: Khong the mo file luu diem.\n");
        return;
    }

    // Ghi ten va diem vao file, ngan cach boi ky tu tab (\t)
    fprintf(f, "%s\t%d\n", tenNguoiChoi, diem);
    fclose(f);

    printf("\nDiem da duoc luu vao file %s\n", TEN_FILE_XEP_HANG);
}

// Doc danh sach diem tu file
// Tra ve: so nguoi choi da doc duoc
int docDanhSachDiem(NguoiChoi danhSach[], int maxNguoi) {
    FILE *f = fopen(TEN_FILE_XEP_HANG, "r"); // "r" = read: chi doc
    if (f == NULL) {
        // File chua ton tai -> chua co du lieu
        return 0;
    }

    int soNguoi = 0;
    char dong[100]; // Luu tung dong doc duoc

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

// ================== NHOM 4: BANG XEP HANG ==================

// Sap xep danh sach nguoi choi theo diem giam dan (bubble sort)
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

// Hien thi bang xep hang tu file
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

// ================== NHOM 5: HAM TIEN ICH ==================

// Nhap ten nguoi choi tu ban phim
void nhapTenNguoiChoi(char ten[], int doDai) {
    printf("Nhap ten nguoi choi: ");
    // " %[^\n]" -> doc ca dong, ke ca khoang trang, den khi gap '\n'
    scanf(" %[^\n]", ten);
}

