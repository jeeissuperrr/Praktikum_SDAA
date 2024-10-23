#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;


struct Kamar {
    int nomor;
    string tipe;
    int harga;
    bool tersedia;
    Kamar* next;
};

struct Pengguna {
    string kataSandi;
    string peran;
};


Kamar* headKamar = nullptr;
int jumlahKamar = 0;
map<string, Pengguna> pengguna;
stack<string> logAdmin;
queue<string> antreanSewa;

// Deklarasi fungsi
void daftarPengguna();
pair<bool, string> autentikasi(string namaPengguna, string kataSandi);
void masuk();
void menuAdmin();
void menuPengguna(string namaPengguna);
void lihatKamar();
void lihatKamarAscending();
void lihatKamarDescending();
void sewaKamar(string namaPengguna);
void tambahKamar();
void hapusKamar();
void ubahKamar();
void detailKamar(Kamar* kamar);
void inputSalah();
void tambahKamarAwal(int nomor, string tipe, int harga, bool tersedia);
Kamar* cariKamar(int posisi);
void tampilkanLogAdmin();
void prosesAntrean();
Kamar* mergeSort(Kamar* head);
Kamar* sortedMerge(Kamar* a, Kamar* b);
void split(Kamar* head, Kamar** frontRef, Kamar** backRef);
Kamar* quickSort(Kamar* head, Kamar* end);
Kamar* partition(Kamar* head, Kamar* end, Kamar** newHead, Kamar** newEnd);


int fibonacciSearch(int arr[], int x, int n);


int jumpSearch(int arr[], int x, int n);


int boyerMooreSearch(string text, string pattern);


int main() {
    tambahKamarAwal(101, "Single", 300000, true);
    tambahKamarAwal(102, "Double", 500000, true);
    tambahKamarAwal(103, "Suite", 800000, true);

    pengguna["admin"] = {"admin123", "admin"};

    while (true) {
        system("cls");
        cout << "\nSelamat datang! Silakan masuk atau daftar." << endl;
        cout << "1. Masuk" << endl;
        cout << "2. Daftar" << endl;
        cout << "3. Keluar" << endl;

        string pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == "1") {
            masuk();
        } else if (pilihan == "2") {
            daftarPengguna();
        } else if (pilihan == "3") {
            cout << "Terima kasih telah menggunakan layanan kami!" << endl;
            break;
        } else {
            inputSalah();
        }
    }
    return 0;
}

// Fungsi Pencarian Fibonacci untuk integer
int fibonacciSearch(int arr[], int x, int n) {
    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;

    while (fib > 1) {
        int i = min(offset + fib2, n - 1);

        if (arr[i] < x) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (arr[i] > x) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else {
            return i;
        }
    }

    if (fib1 && arr[offset + 1] == x) {
        return offset + 1;
    }

    return -1;
}

// Fungsi Pencarian Jump Search untuk integer
int jumpSearch(int arr[], int x, int n) {
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n))
            return -1;
    }

    if (arr[prev] == x)
        return prev;

    return -1;
}

// Fungsi Pencarian Boyer-Moore untuk string
int boyerMooreSearch(string text, string pattern) {
    int m = pattern.size();
    int n = text.size();
    int badChar[256];

    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            return shift;
            shift += (shift + m < n) ? m - badChar[text[shift + m]] : 1;
        } else {
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }

    return -1;
}

// Fungsi lain

void daftarPengguna() {
    system("cls");
    string namaPengguna, kataSandi;
    cout << "Masukkan nama pengguna: ";
    cin >> namaPengguna;

    if (pengguna.find(namaPengguna) != pengguna.end()) {
        cout << "Nama pengguna sudah ada. Coba lagi!" << endl;
        return;
    }

    cout << "Masukkan kata sandi: ";
    cin >> kataSandi;

    pengguna[namaPengguna] = {kataSandi, "pengguna"};
    cout << "Registrasi berhasil!" << endl;
    system("pause");
}

pair<bool, string> autentikasi(string namaPengguna, string kataSandi) {
    auto it = pengguna.find(namaPengguna);
    if (it != pengguna.end() && it->second.kataSandi == kataSandi) {
        return {true, it->second.peran};
    }
    return {false, ""};
}

void masuk() {
    system("cls");
    string namaPengguna, kataSandi;
    cout << "Masukkan nama pengguna: ";
    cin >> namaPengguna;
    cout << "Masukkan kata sandi: ";
    cin >> kataSandi;

    auto [terotentikasi, peran] = autentikasi(namaPengguna, kataSandi);

    if (terotentikasi) {
        if (peran == "pengguna") {
            menuPengguna(namaPengguna);
        } else if (peran == "admin") {
            menuAdmin();
        }
    } else {
        char ulangi;
        cout << "Login gagal. Coba lagi? (y/n): ";
        cin >> ulangi;
        if (ulangi == 'y' || ulangi == 'Y') {
            masuk();
        }
    }
}

void menuAdmin() {
    while (true) {
        system("cls");
        cout << "Menu Admin\n";
        cout << "1. Tambah Kamar\n";
        cout << "2. Hapus Kamar\n";
        cout << "3. Ubah Data Kamar\n";
        cout << "4. Lihat Kamar\n";
        cout << "5. Tampilkan Log Admin\n";
        cout << "6. Proses Antrean Sewa\n";
        cout << "7. Keluar\n";

        string pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == "1") {
            tambahKamar();
        } else if (pilihan == "2") {
            hapusKamar();
        } else if (pilihan == "3") {
            ubahKamar();
        } else if (pilihan == "4") {
            lihatKamar();
        } else if (pilihan == "5") {
            tampilkanLogAdmin();
        } else if (pilihan == "6") {
            prosesAntrean();
        } else if (pilihan == "7") {
            break;
        } else {
            inputSalah();
        }
    }
}

void menuPengguna(string namaPengguna) {
    while (true) {
        system("cls");
        cout << "Menu Pengguna\n";
        cout << "1. Lihat Kamar\n";
        cout << "2. Sewa Kamar\n";
        cout << "3. Keluar\n";

        string pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == "1") {
            lihatKamar();
        } else if (pilihan == "2") {
            sewaKamar(namaPengguna);
        } else if (pilihan == "3") {
            break;
        } else {
            inputSalah();
        }
    }
}

void lihatKamar() {
    system("cls");
    cout << "Daftar Kamar:\n";
    
    if (headKamar == nullptr) {
        cout << "Tidak ada kamar tersedia.\n";
    } else {
        Kamar* temp = headKamar;
        while (temp != nullptr) {
            detailKamar(temp);
            temp = temp->next;
        }
    }
    system("pause");
}

void tambahKamar() {
    
    system("cls");
    int nomor, harga;
    string tipe;
    bool tersedia;

    cout << "Nomor Kamar: ";
    cin >> nomor;
    cout << "Tipe Kamar: ";
    cin >> tipe;
    cout << "Harga Kamar: ";
    cin >> harga;
    cout << "Apakah kamar tersedia? (1 = ya, 0 = tidak): ";
    cin >> tersedia;

    Kamar* newKamar = new Kamar{nomor, tipe, harga, tersedia, nullptr};
    if (headKamar == nullptr) {
        headKamar = newKamar;
    } else {
        Kamar* temp = headKamar;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newKamar;
    }
    jumlahKamar++;
    logAdmin.push("Kamar nomor " + to_string(nomor) + " ditambahkan.");
    cout << "Kamar berhasil ditambahkan!\n";
    system("pause");
}

void hapusKamar() {
    
    system("cls");
    int nomor;
    cout << "Masukkan nomor kamar yang akan dihapus: ";
    cin >> nomor;

    Kamar* temp = headKamar;
    Kamar* prev = nullptr;

    while (temp != nullptr && temp->nomor != nomor) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Kamar tidak ditemukan.\n";
    } else {
        if (prev == nullptr) {
            headKamar = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
        jumlahKamar--;
        logAdmin.push("Kamar nomor " + to_string(nomor) + " dihapus.");
        cout << "Kamar berhasil dihapus!\n";
    }
    system("pause");
}

void ubahKamar() {
    system("cls");
    int nomor, harga;
    string tipe;
    bool tersedia;

    cout << "Masukkan nomor kamar yang akan diubah: ";
    cin >> nomor;

    Kamar* kamar = headKamar;
    while (kamar != nullptr && kamar->nomor != nomor) {
        kamar = kamar->next;
    }

    if (kamar == nullptr) {
        cout << "Kamar tidak ditemukan.\n";
    } else {
        cout << "Nomor Kamar: " << kamar->nomor << "\n";
        cout << "Tipe Kamar saat ini: " << kamar->tipe << "\n";
        cout << "Harga Kamar saat ini: " << kamar->harga << "\n";
        cout << "Apakah kamar tersedia? (1 = ya, 0 = tidak): " << kamar->tersedia << "\n\n";

        cout << "Tipe Kamar baru: ";
        cin >> tipe;
        cout << "Harga Kamar baru: ";
        cin >> harga;
        cout << "Apakah kamar tersedia? (1 = ya, 0 = tidak): ";
        cin >> tersedia;

        kamar->tipe = tipe;
        kamar->harga = harga;
        kamar->tersedia = tersedia;

        logAdmin.push("Kamar nomor " + to_string(nomor) + " diubah.");
        cout << "Kamar berhasil diubah!\n";
    }
    system("pause");
}

void detailKamar(Kamar* kamar) {
    cout << "Nomor Kamar: " << kamar->nomor << "\n";
    cout << "Tipe Kamar: " << kamar->tipe << "\n";
    cout << "Harga Kamar: Rp " << kamar->harga << "\n";
    cout << "Tersedia: " << (kamar->tersedia ? "Ya" : "Tidak") << "\n\n";
}

void tampilkanLogAdmin() {
    system("cls");
    cout << "Log Admin:\n";
    if (logAdmin.empty()) {
        cout << "Tidak ada aktivitas log.\n";
    } else {
        stack<string> tempLog = logAdmin;
        while (!tempLog.empty()) {
            cout << tempLog.top() << endl;
            tempLog.pop();
        }
    }
    system("pause");
}

void prosesAntrean() {
    system("cls");
    cout << "Proses Antrean Sewa:\n";
    if (antreanSewa.empty()) {
        cout << "Tidak ada antrean.\n";
    } else {
        while (!antreanSewa.empty()) {
            cout << "Pelanggan " << antreanSewa.front() << " diproses.\n";
            antreanSewa.pop();
        }
    }
    system("pause");
}

void sewaKamar(string namaPengguna) {
    system("cls");
    cout << "Masukkan nomor kamar yang ingin disewa: ";
    int nomor;
    cin >> nomor;

    Kamar* kamar = headKamar;
    while (kamar != nullptr && kamar->nomor != nomor) {
        kamar = kamar->next;
    }

    if (kamar == nullptr || !kamar->tersedia) {
        cout << "Kamar tidak tersedia atau tidak ditemukan.\n";
    } else {
        kamar->tersedia = false;
        antreanSewa.push(namaPengguna);
        cout << "Kamar berhasil disewa! Anda masuk antrean sewa.\n";
    }
    system("pause");
}

void inputSalah() {
    cout << "Input tidak valid, coba lagi.\n";
    system("pause");
}

void tambahKamarAwal(int nomor, string tipe, int harga, bool tersedia) {
    Kamar* newKamar = new Kamar{nomor, tipe, harga, tersedia, nullptr};
    if (headKamar == nullptr) {
        headKamar = newKamar;
    } else {
        Kamar* temp = headKamar;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newKamar;
    }
    jumlahKamar++;
}

Kamar* cariKamar(int posisi) {
    Kamar* temp = headKamar;
    int count = 0;
    while (temp != nullptr && count != posisi) {
        count++;
        temp = temp->next;
    }
    return temp;
}