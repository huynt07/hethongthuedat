#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;
const double pi = 3.14;
class HinhHoc {
private:
    int khuVuc;
    double giaDat, thueSuat, mienGiam;
public:
    // getter - setter
    void setkhuVuc(int kv)       { khuVuc   = kv;  }
    void setgiaDat(double gia)   { giaDat   = gia; }
    void setthueSuat(double ts)  { thueSuat = ts;  }
    void setmienGiam(double mg)  { mienGiam = mg;  }
    
    int    getkhuVuc  () const { return khuVuc;   }
    double getgiaDat  () const { return giaDat;   }
    double getthueSuat() const { return thueSuat; }
    double getmienGiam() const { return mienGiam; }
    
    // ham ho tro
    void setThongTin(int kv, double gia, double ts, double mg) {
        khuVuc = kv; giaDat = gia; thueSuat = ts; mienGiam = mg;
    }
    
    // constructor
    HinhHoc(int kv = 0, double gia = 0, double ts = 0, double mg = 0)
		: khuVuc(kv), giaDat(gia), thueSuat(ts), mienGiam(mg) {}
		
    HinhHoc(const HinhHoc& h)
		: khuVuc(h.khuVuc), giaDat(h.giaDat), thueSuat(h.thueSuat), mienGiam(h.mienGiam) {}
		
    virtual ~HinhHoc() {}    // destructor
    
    virtual double TinhDienTich() const = 0;
    virtual double TinhChuVi()    const = 0;
    virtual string getTenHinh()   const = 0;
    
    double TinhThue() const {
        double hesoKV;
        if (khuVuc == 1) hesoKV = 2.0;
        else if (khuVuc == 2) hesoKV = 1.5;
        else if (khuVuc == 3) hesoKV = 1.0;
        return TinhDienTich() * hesoKV * giaDat * (thueSuat / 100.0);
    }
    double ThuePhaiNop() const {
        return TinhThue() - (mienGiam / 100.0 * TinhThue());
    }
    
    virtual void nhap() = 0;
    virtual void xuat() const = 0;
};
class HinhTron : public HinhHoc {
private:
    double banKinh;
public:
    // getter - setter
    void setbanKinh(double r) { banKinh = r; }
    double getbanKinh() const { return banKinh; }
    
    // constructor
    HinhTron(double r = 0, int kv = 0, double gia = 0, double ts = 0, double mg = 0)
		: HinhHoc(kv, gia, ts, mg), banKinh(r) {}
    
	HinhTron(const HinhTron& h)
		: HinhHoc(h), banKinh(h.banKinh) {}
		
    ~HinhTron() {}    // destructor
    
    double TinhDienTich() const override { return pi * pow(banKinh, 2); }
    double TinhChuVi()    const override { return 2.0 * pi * banKinh;   }
    string getTenHinh()   const override { return "Hinh Tron";          }
    
    // operator
    friend istream& operator>>(istream& in, HinhTron& h) {
        int kv; double gia, ts, mg;
        do {
        	cout << "Nhap ban kinh: "; in >> h.banKinh;
        	if (h.banKinh <= 0) cout << "Ban kinh khong hop le! Nhap lai.\n";
        	else break;
		} while (true);
        do {
        	cout << "Nhap khu vuc (1. Trung Tam/2. Ven Do/3. Ngoai O): "; in >> kv;
        	if (kv < 1 || kv > 3) cout << "Khu vuc khong hop le! Nhap lai.\n";
        	else break;
		} while (true);
        cout << "Nhap gia dat (VND/m^2): "; in >> gia;
        cout << "Nhap thue suat (%): "; in >> ts;
        cout << "Nhap mien giam (%): "; in >> mg;
        h.setThongTin(kv, gia, ts, mg);
        return in;
    }
    friend ostream& operator<<(ostream& out, const HinhTron& h) {
        out << "Hinh Tron" << endl;
        out << "Dien tich: " << h.TinhDienTich() << endl;
        out << "Chu vi: " << h.TinhChuVi() << endl;
        out << "Thue phat sinh: " << h.TinhThue() << endl;
        out << "Thue phai nop: " << h.ThuePhaiNop() << endl;
        return out;
    }
    void nhap() override       { cin  >> *this; }
    void xuat() const override { cout << *this; }
};
class HinhChuNhat : public HinhHoc {
private:
    double dai, rong;
public:
    // getter - setter
    void   setDai (double d) { dai  = d; }
    void   setRong(double r) { rong = r; }
    double getDai()  const { return dai;  }
    double getRong() const { return rong; }
    
    // constructor
    HinhChuNhat(double d = 0, double r = 0, int kv = 0, double gia = 0, double ts = 0, double mg = 0)
		: HinhHoc(kv, gia, ts, mg), dai(d), rong(r) {}
		
    HinhChuNhat(const HinhChuNhat& h)
		: HinhHoc(h), dai(h.dai), rong(h.rong) {}
		
    ~HinhChuNhat() {}    // destructor
    
    double TinhDienTich() const override { return dai * rong;         }
    double TinhChuVi()    const override { return (dai + rong) * 2.0; }
    string getTenHinh()   const override { return "Hinh Chu Nhat";    }
    
    // operator
    friend istream& operator>>(istream& in, HinhChuNhat& h) {
        int kv; double gia, ts, mg;
        do {
        	cout << "Nhap dai, rong: "; in >> h.dai >> h.rong;
        	if (h.dai <= 0 || h.rong <= 0) cout << "Hinh chu nhat khong hop le! Nhap lai.\n";
        	else break;
		} while (true);
        do {
        	cout << "Nhap khu vuc (1. Trung Tam/2. Ven Do/3. Ngoai O): "; in >> kv;
        	if (kv < 1 || kv > 3) cout << "Khu vuc khong hop le! Nhap lai.\n";
        	else break;
		} while (true);
        cout << "Nhap gia dat (VND/m^2): "; in >> gia;
        cout << "Nhap thue suat (%): "; in >> ts;
        cout << "Nhap mien giam (%): "; in >> mg;
        h.setThongTin(kv, gia, ts, mg);
        return in;
    }
    friend ostream& operator<<(ostream& out, const HinhChuNhat& h) {
        out << "Hinh Chu Nhat" << endl;
        out << "Dien tich: " << h.TinhDienTich() << endl;
        out << "Chu vi: " << h.TinhChuVi() << endl;
        out << "Thue phat sinh: " << h.TinhThue() << endl;
        out << "Thue phai nop: " << h.ThuePhaiNop() << endl;
        return out;
    }
    void nhap() override       { cin  >> *this; }
    void xuat() const override { cout << *this; }
};
class TamGiac : public HinhHoc {
private:
    double a, b, c;
public:
    // getter - setter
    void   seta(double _a) { a = _a; }
    void   setb(double _b) { b = _b; }
    void   setc(double _c) { c = _c; }
    double geta() const { return a; }
    double getb() const { return b; }
    double getc() const { return c; }
    
    // constructor
    TamGiac(double a = 0, double b = 0, double c = 0, int kv = 0, double gia = 0, double ts = 0, double mg = 0)
		: HinhHoc(kv, gia, ts, mg), a(a), b(b), c(c) {}
		
    TamGiac(const TamGiac& h)
		: HinhHoc(h), a(h.a), b(h.b), c(h.c) {}
    
	~TamGiac() {}    // destructor
    
	double TinhDienTich() const override {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    double TinhChuVi()  const override { return a + b + c; }
    string getTenHinh() const override { return "Tam Giac"; }
    
    // operator
    friend istream& operator>>(istream& in, TamGiac& h) {
        int kv; double gia, ts, mg;
        do {
            cout << "Nhap canh a, b, c: "; in >> h.a >> h.b >> h.c;
            if (h.a <= 0 || h.b <= 0 || h.c <= 0 ||
                h.a + h.b <= h.c ||
                h.a + h.c <= h.b ||
                h.b + h.c <= h.a) {
                cout << "Tam giac khong hop le! Nhap lai.\n";
            } else break;
        } while (true);
        do {
        	cout << "Nhap khu vuc (1. Trung Tam/2. Ven Do/3. Ngoai O): "; in >> kv;
        	if (kv < 1 || kv > 3) cout << "Khu vuc khong hop le! Nhap lai.\n";
        	else break;
		} while (true);
        cout << "Nhap gia dat: "; in >> gia;
        cout << "Nhap thue suat: "; in >> ts;
        cout << "Nhap mien giam: "; in >> mg;
        h.setThongTin(kv, gia, ts, mg);
        return in;
    }
    friend ostream& operator<<(ostream& out, const TamGiac& h) {
        out << "Tam Giac" << endl;
        out << "Dien tich: " << h.TinhDienTich() << endl;
        out << "Chu vi: " << h.TinhChuVi() << endl;
        out << "Thue phat sinh: " << h.TinhThue() << endl;
        out << "Thue phai nop: " << h.ThuePhaiNop() << endl;
        return out;
    }
    void nhap() override       { cin  >> *this; }
    void xuat() const override { cout << *this; }
};
void xuatDanhSach(HinhHoc* ds[], int n) {
    if (n == 0) {
        cout << "Chua co lo dat nao!\n";
        return;
    }
    double tongThue = 0;
    cout << "\n					DANH SACH CHI TIET CAC LO DAT\n";
    cout << string(100, '-') << "\n";
    cout << left
         << setw(10)  << "Lo Dat"
         << setw(16) << "Ten Hinh"
         << setw(14) << "Dien Tich"
         << setw(12) << "Chu Vi"
         << setw(20) << "So Tien Thue"
         << setw(17) << "Thue Phai Nop"
         << "\n";
    cout << string(100, '-') << "\n";
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(2);
        cout << left
             << "#" << setw(10) << (i + 1)
             << setw(16) << ds[i]->getTenHinh()
             << setw(14) << ds[i]->TinhDienTich()
             << setw(12) << ds[i]->TinhChuVi()
             << setw(20) << ds[i]->TinhThue()
             << setw(17) << ds[i]->ThuePhaiNop()
             << " VND\n";
        tongThue += ds[i]->ThuePhaiNop();
    }
    cout << string(100, '-') << "\n";
    cout << "TONG THUE PHAI NOP: " << fixed << setprecision(2) << tongThue << " VND\n";
}

int main() {
    HinhHoc* ds[100];
    int n = 0, choice;
    do {
        cout << "\n" << string(100, '=') << "\n"
			 << "				HE THONG TINH THUE DAT HINH HOC\n"
			 << string(100, '=') << "\n"
             << "1. Them Hinh Tron\n"
             << "2. Them Hinh Chu Nhat\n"
             << "3. Them Tam Giac\n"
             << "4. Xem danh sach lo dat\n"
             << "0. Thoat\n"
             << string(100, '-') << "\n"
             << "Nhap lua chon: ";
        cin >> choice;
        if (choice == 0) { cout << "\nCam on ban da su dung chuong trinh!"; break;	}
        if (choice == 4) {
            xuatDanhSach(ds, n);
         	cout << "Press any key to continue . . .";
            cin.ignore();
            cin.get();
            continue;
        }
        if (n >= 100) { cout << "Danh sach day!\n"; continue; }
        switch (choice) {
            case 1: ds[n] = new HinhTron();    break;
            case 2: ds[n] = new HinhChuNhat(); break;
            case 3: ds[n] = new TamGiac();     break;
            default:
                cout << "Lua chon khong hop le!\n";
                continue;
        }
        ds[n]->nhap();
        n++;
        cout << "=> Them thanh cong lo dat!\n"
        	 << "Press any key to continue . . .";
        cin.ignore();
        cin.get();
    } while (true);
    
    for (int i = 0; i < n; i++) delete ds[i]; // giai phong bo nho
    return 0;
}
