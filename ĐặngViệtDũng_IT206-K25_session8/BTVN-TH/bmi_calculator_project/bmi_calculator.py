"""
BMI Calculator - Ứng dụng tính chỉ số BMI và phân loại cơ thể.

Module này cung cấp class BMI_Calculator để tính toán và phân loại
chỉ số BMI (Body Mass Index) của người dùng.
"""


class BMI_Calculator:
    """
    Class tính toán và phân loại chỉ số BMI của người dùng.
    
    BMI (Body Mass Index) là chỉ số khối cơ thể, được tính bằng công thức:
    BMI = weight (kg) / (height (m))^2
    
    Attributes:
        name (str): Tên người dùng
        height (float): Chiều cao tính bằng mét (m)
        weight (float): Cân nặng tính bằng kilogam (kg)
    
    Examples:
        >>> person = BMI_Calculator("Nguyễn Văn A", 1.75, 70.0)
        >>> bmi = person.calculate_bmi()
        >>> print(f"BMI: {bmi:.2f}")
        BMI: 22.86
    """
    
    def __init__(self, name: str, height: float, weight: float):
        """
        Khởi tạo đối tượng BMI_Calculator.
        
        Args:
            name (str): Tên người dùng
            height (float): Chiều cao tính bằng mét (m), phải > 0
            weight (float): Cân nặng tính bằng kilogam (kg), phải > 0
        
        Raises:
            ValueError: Nếu height hoặc weight <= 0
        """
        # Kiểm tra tính hợp lệ của dữ liệu đầu vào
        if height <= 0:
            raise ValueError("Chiều cao phải lớn hơn 0")
        if weight <= 0:
            raise ValueError("Cân nặng phải lớn hơn 0")
        
        self.name = name
        self.height = height
        self.weight = weight
    
    def calculate_bmi(self) -> float:
        """
        Tính chỉ số BMI theo công thức chuẩn.
        
        Công thức: BMI = weight (kg) / (height (m))^2
        
        Returns:
            float: Chỉ số BMI được làm tròn đến 2 chữ số thập phân
        
        Examples:
            >>> person = BMI_Calculator("Test", 1.70, 65.0)
            >>> person.calculate_bmi()
            22.49
        """
        # Tính BMI theo công thức chuẩn của WHO
        bmi = self.weight / (self.height ** 2)
        # Làm tròn đến 2 chữ số thập phân để dễ đọc
        return round(bmi, 2)
    
    def get_category(self) -> str:
        """
        Phân loại cơ thể dựa trên chỉ số BMI.
        
        Phân loại theo tiêu chuẩn WHO:
        - BMI < 18.5: Gầy
        - 18.5 ≤ BMI < 25: Bình thường
        - 25 ≤ BMI < 30: Thừa cân
        - BMI ≥ 30: Béo phì
        
        Returns:
            str: Phân loại cơ thể ("Gầy", "Bình thường", "Thừa cân", "Béo phì")
        
        Examples:
            >>> person = BMI_Calculator("Test", 1.70, 50.0)
            >>> person.get_category()
            'Gầy'
        """
        bmi = self.calculate_bmi()
        
        # Phân loại theo các mức BMI
        if bmi < 18.5:
            return "Gầy"
        elif bmi < 25:
            return "Bình thường"
        elif bmi < 30:
            return "Thừa cân"
        else:  # bmi >= 30
            return "Béo phì"
    
    def display_info(self) -> None:
        """
        Hiển thị đầy đủ thông tin người dùng và kết quả BMI.
        
        Hiển thị bao gồm:
        - Tên người dùng
        - Chiều cao (m)
        - Cân nặng (kg)
        - Chỉ số BMI
        - Phân loại cơ thể
        
        Examples:
            >>> person = BMI_Calculator("Nguyễn Văn A", 1.75, 70.0)
            >>> person.display_info()
            Tên: Nguyễn Văn A
            Chiều cao: 1.75 m
            Cân nặng: 70.0 kg
            BMI: 22.86
            Phân loại: Bình thường
        """
        bmi = self.calculate_bmi()
        category = self.get_category()
        
        print(f"Tên: {self.name}")
        print(f"Chiều cao: {self.height} m")
        print(f"Cân nặng: {self.weight} kg")
        print(f"BMI: {bmi}")
        print(f"Phân loại: {category}")


# ============================================================================
# LOGIC HOẠT ĐỘNG TỔNG QUÁT CỦA CHƯƠNG TRÌNH
# ============================================================================
"""
LUỒNG XỬ LÝ TỔNG QUÁT:

1. KHỞI TẠO ĐỐI TƯỢNG (__init__):
   - Nhận thông tin: name, height, weight
   - Kiểm tra tính hợp lệ (height > 0, weight > 0)
   - Lưu trữ vào các thuộc tính của class

2. TÍNH TOÁN BMI (calculate_bmi):
   - Sử dụng công thức: BMI = weight / (height^2)
   - Làm tròn kết quả đến 2 chữ số thập phân
   - Trả về giá trị BMI

3. PHÂN LOẠI CƠ THỂ (get_category):
   - Gọi calculate_bmi() để lấy chỉ số BMI
   - So sánh BMI với các ngưỡng:
     * BMI < 18.5 → "Gầy"
     * 18.5 ≤ BMI < 25 → "Bình thường"
     * 25 ≤ BMI < 30 → "Thừa cân"
     * BMI ≥ 30 → "Béo phì"
   - Trả về chuỗi phân loại

4. HIỂN THỊ THÔNG TIN (display_info):
   - Gọi calculate_bmi() và get_category()
   - In ra màn hình tất cả thông tin: tên, chiều cao, cân nặng, BMI, phân loại

LUỒNG XỬ LÝ TỪ NHẬP DỮ LIỆU → TÍNH BMI → PHÂN LOẠI → HIỂN THỊ:

Input: name, height, weight
    ↓
[__init__] → Lưu trữ dữ liệu vào object
    ↓
[calculate_bmi] → Tính BMI = weight / (height^2)
    ↓
[get_category] → So sánh BMI với ngưỡng → Xác định phân loại
    ↓
[display_info] → Hiển thị tất cả thông tin ra màn hình
    ↓
Output: Thông tin đầy đủ về BMI và phân loại cơ thể
"""


def main():
    """
    Hàm main để chạy ứng dụng BMI Calculator với menu CLI.
    """
    # Danh sách lưu trữ các đối tượng BMI_Calculator
    users = []
    
    while True:
        # Hiển thị menu chính
        print("\n" + "="*50)
        print("     ỨNG DỤNG TÍNH CHỈ SỐ BMI")
        print("="*50)
        print("1. Nhập thông tin người dùng")
        print("2. Tính và hiển thị kết quả BMI")
        print("3. Thoát chương trình")
        print("="*50)
        
        choice = input("Chọn chức năng (1-3): ").strip()
        
        if choice == "1":
            # Nhập thông tin người dùng
            print("\n--- NHẬP THÔNG TIN NGƯỜI DÙNG ---")
            try:
                name = input("Nhập tên: ").strip()
                if not name:
                    print("Tên không được để trống!")
                    continue
                
                height = float(input("Nhập chiều cao (m): "))
                weight = float(input("Nhập cân nặng (kg): "))
                
                # Tạo đối tượng BMI_Calculator
                person = BMI_Calculator(name, height, weight)
                users.append(person)
                print(f"\n✓ Đã thêm thông tin của {name} thành công!")
                
            except ValueError as e:
                print(f"\n✗ Lỗi: {e}")
                print("Vui lòng nhập lại với dữ liệu hợp lệ!")
        
        elif choice == "2":
            # Hiển thị kết quả BMI dạng bảng
            if not users:
                print("\n✗ Chưa có thông tin người dùng nào!")
                print("Vui lòng nhập thông tin ở mục 1 trước.")
                continue
            
            print("\n" + "="*80)
            print("                        KẾT QUẢ BMI")
            print("="*80)
            # In header của bảng
            print(f"{'Tên':<20} | {'Chiều cao (m)':<15} | {'Cân nặng (kg)':<15} | {'BMI':<8} | {'Phân loại':<15}")
            print("-" * 80)
            
            # In từng dòng dữ liệu
            for person in users:
                bmi = person.calculate_bmi()
                category = person.get_category()
                print(f"{person.name:<20} | {person.height:<15.2f} | {person.weight:<15.2f} | {bmi:<8.2f} | {category:<15}")
            
            print("="*80)
        
        elif choice == "3":
            # Thoát chương trình
            print("\nCảm ơn bạn đã sử dụng ứng dụng BMI Calculator!")
            print("Hẹn gặp lại!")
            break
        
        else:
            print("\n✗ Lựa chọn không hợp lệ! Vui lòng chọn 1, 2 hoặc 3.")


if __name__ == "__main__":
    main()

