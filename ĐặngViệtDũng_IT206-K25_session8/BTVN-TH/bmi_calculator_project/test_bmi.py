"""
Test file cho BMI Calculator.

File này chứa các test case để kiểm thử class BMI_Calculator,
đảm bảo các phương thức hoạt động đúng với các trường hợp khác nhau.
"""

from bmi_calculator import BMI_Calculator


def test_case_1_gay():
    """
    Test case 1: Người có BMI < 18.5 → Phân loại "Gầy".
    
    Ví dụ: Người cao 1.70m, nặng 50kg
    BMI = 50 / (1.70)^2 = 17.30 < 18.5 → Gầy
    """
    print("\n" + "="*60)
    print("TEST CASE 1: BMI < 18.5 → Gầy")
    print("="*60)
    
    person = BMI_Calculator("Nguyễn Văn A", 1.70, 50.0)
    bmi = person.calculate_bmi()
    category = person.get_category()
    
    print(f"Tên: {person.name}")
    print(f"Chiều cao: {person.height} m")
    print(f"Cân nặng: {person.weight} kg")
    print(f"BMI: {bmi}")
    print(f"Phân loại: {category}")
    
    # Kiểm tra kết quả
    assert bmi < 18.5, f"BMI phải < 18.5, nhưng nhận được {bmi}"
    assert category == "Gầy", f"Phân loại phải là 'Gầy', nhưng nhận được '{category}'"
    print("✓ TEST CASE 1: PASSED")


def test_case_2_binh_thuong():
    """
    Test case 2: Người có BMI từ 18.5–24.9 → Phân loại "Bình thường".
    
    Ví dụ: Người cao 1.75m, nặng 70kg
    BMI = 70 / (1.75)^2 = 22.86 → Bình thường
    """
    print("\n" + "="*60)
    print("TEST CASE 2: BMI từ 18.5–24.9 → Bình thường")
    print("="*60)
    
    person = BMI_Calculator("Trần Thị B", 1.75, 70.0)
    bmi = person.calculate_bmi()
    category = person.get_category()
    
    print(f"Tên: {person.name}")
    print(f"Chiều cao: {person.height} m")
    print(f"Cân nặng: {person.weight} kg")
    print(f"BMI: {bmi}")
    print(f"Phân loại: {category}")
    
    # Kiểm tra kết quả
    assert 18.5 <= bmi < 25, f"BMI phải từ 18.5 đến 24.9, nhưng nhận được {bmi}"
    assert category == "Bình thường", f"Phân loại phải là 'Bình thường', nhưng nhận được '{category}'"
    print("✓ TEST CASE 2: PASSED")


def test_case_3_beo_phi():
    """
    Test case 3: Người có BMI ≥ 30 → Phân loại "Béo phì".
    
    Ví dụ: Người cao 1.65m, nặng 85kg
    BMI = 85 / (1.65)^2 = 31.22 ≥ 30 → Béo phì
    """
    print("\n" + "="*60)
    print("TEST CASE 3: BMI ≥ 30 → Béo phì")
    print("="*60)
    
    person = BMI_Calculator("Lê Văn C", 1.65, 85.0)
    bmi = person.calculate_bmi()
    category = person.get_category()
    
    print(f"Tên: {person.name}")
    print(f"Chiều cao: {person.height} m")
    print(f"Cân nặng: {person.weight} kg")
    print(f"BMI: {bmi}")
    print(f"Phân loại: {category}")
    
    # Kiểm tra kết quả
    assert bmi >= 30, f"BMI phải ≥ 30, nhưng nhận được {bmi}"
    assert category == "Béo phì", f"Phân loại phải là 'Béo phì', nhưng nhận được '{category}'"
    print("✓ TEST CASE 3: PASSED")


def test_case_4_thua_can():
    """
    Test case 4: Người có BMI từ 25–29.9 → Phân loại "Thừa cân".
    
    Ví dụ: Người cao 1.70m, nặng 80kg
    BMI = 80 / (1.70)^2 = 27.68 → Thừa cân
    """
    print("\n" + "="*60)
    print("TEST CASE 4: BMI từ 25–29.9 → Thừa cân")
    print("="*60)
    
    person = BMI_Calculator("Phạm Thị D", 1.70, 80.0)
    bmi = person.calculate_bmi()
    category = person.get_category()
    
    print(f"Tên: {person.name}")
    print(f"Chiều cao: {person.height} m")
    print(f"Cân nặng: {person.weight} kg")
    print(f"BMI: {bmi}")
    print(f"Phân loại: {category}")
    
    # Kiểm tra kết quả
    assert 25 <= bmi < 30, f"BMI phải từ 25 đến 29.9, nhưng nhận được {bmi}"
    assert category == "Thừa cân", f"Phân loại phải là 'Thừa cân', nhưng nhận được '{category}'"
    print("✓ TEST CASE 4: PASSED")


def test_batch_10_users():
    """
    Test hàng loạt với 10 người dùng ngẫu nhiên.
    
    Tạo danh sách 10 người với thông tin hợp lệ và kiểm tra
    tính toán BMI và phân loại cho tất cả.
    """
    print("\n" + "="*60)
    print("TEST HÀNG LOẠT: 10 người dùng ngẫu nhiên")
    print("="*60)
    
    # Danh sách 10 người dùng với thông tin hợp lệ
    test_users = [
        ("Nguyễn Văn An", 1.68, 55.0),   # BMI ~19.5 → Bình thường
        ("Trần Thị Bình", 1.60, 45.0),   # BMI ~17.6 → Gầy
        ("Lê Văn Cường", 1.75, 90.0),    # BMI ~29.4 → Thừa cân
        ("Phạm Thị Dung", 1.65, 95.0),   # BMI ~34.9 → Béo phì
        ("Hoàng Văn Em", 1.72, 65.0),    # BMI ~22.0 → Bình thường
        ("Vũ Thị Phương", 1.58, 48.0),   # BMI ~19.2 → Bình thường
        ("Đỗ Văn Giang", 1.80, 100.0),   # BMI ~30.9 → Béo phì
        ("Bùi Thị Hoa", 1.55, 42.0),     # BMI ~17.5 → Gầy
        ("Ngô Văn Ích", 1.70, 75.0),     # BMI ~26.0 → Thừa cân
        ("Đinh Thị Khoa", 1.63, 58.0),   # BMI ~21.8 → Bình thường
    ]
    
    # Tạo danh sách đối tượng BMI_Calculator
    persons = []
    for name, height, weight in test_users:
        person = BMI_Calculator(name, height, weight)
        persons.append(person)
    
    # Hiển thị kết quả dạng bảng
    print(f"\n{'STT':<5} | {'Tên':<20} | {'Chiều cao (m)':<15} | {'Cân nặng (kg)':<15} | {'BMI':<8} | {'Phân loại':<15}")
    print("-" * 90)
    
    # Kiểm tra từng người
    for idx, person in enumerate(persons, 1):
        bmi = person.calculate_bmi()
        category = person.get_category()
        
        print(f"{idx:<5} | {person.name:<20} | {person.height:<15.2f} | {person.weight:<15.2f} | {bmi:<8.2f} | {category:<15}")
        
        # Kiểm tra tính hợp lệ của BMI và phân loại
        assert bmi > 0, f"BMI phải > 0, nhưng nhận được {bmi}"
        assert category in ["Gầy", "Bình thường", "Thừa cân", "Béo phì"], \
            f"Phân loại không hợp lệ: {category}"
    
    print("-" * 90)
    print(f"✓ Đã test thành công {len(persons)} người dùng!")
    print("✓ TEST HÀNG LOẠT: PASSED")


def run_all_tests():
    """
    Chạy tất cả các test case.
    """
    print("\n" + "="*60)
    print("           BẮT ĐẦU CHẠY TEST SUITE")
    print("="*60)
    
    try:
        # Chạy các test case cơ bản
        test_case_1_gay()
        test_case_2_binh_thuong()
        test_case_3_beo_phi()
        test_case_4_thua_can()
        
        # Chạy test hàng loạt
        test_batch_10_users()
        
        print("\n" + "="*60)
        print("           TẤT CẢ TEST ĐÃ PASSED!")
        print("="*60)
        print("\n✓ Tất cả các test case đều chạy thành công!")
        print("✓ Class BMI_Calculator hoạt động đúng như mong đợi.")
        
    except AssertionError as e:
        print(f"\n✗ TEST FAILED: {e}")
        raise
    except Exception as e:
        print(f"\n✗ LỖI KHÔNG MONG ĐỢI: {e}")
        raise


if __name__ == "__main__":
    run_all_tests()

