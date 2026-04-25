#include <iostream>
#include <cmath>
#include <iomanip>
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
    
    double TinhThue() const {
        double heSo = 0;
        if (khuVuc == 1) heSo = 2.0;
        else if (khuVuc == 2) heSo = 1.5;
        else if (khuVuc == 3) heSo = 1.0;
        return TinhDienTich() * heSo * giaDat * (thueSuat / 100.0);
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
    double TinhChuVi()    const override { return 2.0 * pi * banKinh;     }
    
    // operator
    friend istream& operator>>(istream& in, HinhTron& h) {
        int kv; double gia, ts, mg;
        cout << "Nhap ban kinh: "; in >> h.banKinh;
        cout << "Nhap khu vuc (1/2/3): "; in >> kv;
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
    
    // operator
    friend istream& operator>>(istream& in, HinhChuNhat& h) {
        int kv; double gia, ts, mg;
        cout << "Nhap dai, rong: "; in >> h.dai >> h.rong;
        cout << "Nhap khu vuc (1/2/3): "; in >> kv;
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
    double TinhChuVi() const override { return a + b + c; }
    
    // operator
    friend istream& operator>>(istream& in, TamGiac& h) {
        int kv; double gia, ts, mg;
        cout << "Nhap canh a, b, c: "; in >> h.a >> h.b >> h.c;
        cout << "Nhap khu vuc (1/2/3): "; in >> kv;
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
int main() {
    HinhHoc* ds[100];
    int n = 0, choice;
    do {
        cout << "\n==================================================\n"
			 << "	HE THONG TINH THUE DAT HINH HOC\n"
			 << "==================================================\n"
             << "1. Them Hinh Tron\n"
             << "2. Them Hinh Chu Nhat\n"
             << "3. Them Tam Giac\n"
             //<< "4. Hinh Vuong\n"
             << "0. Thoat\n"
             << "--------------------------------------------------\n"
             << "Nhap lua chon: ";
        cin >> choice;
        if (choice == 0) break;
        if (n >= 100) { cout << "Danh sach day!\n"; break; }
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
    } while (true);
    
    cout << "\n======= DANH SACH =======\n";
    for (int i = 0; i < n; i++) {
        ds[i]->xuat();
        cout << endl;
    }
    
    for (int i = 0; i < n; i++) delete ds[i]; // giai phong bo nho
    return 0;
}
