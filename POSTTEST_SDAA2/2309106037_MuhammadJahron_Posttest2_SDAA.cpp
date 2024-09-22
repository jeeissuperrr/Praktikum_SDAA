#include <iostream>
#include <map>
#include <string>
using namespace std;

struct Kamar {
    int nomor;
    string tipe;
    int harga;
    bool tersedia;
};

struct Pengguna {
    string kataSandi;
    string peran;
};

Kamar daftarKamar[100];
int jumlahKamar = 3;
map<string, Pengguna> pengguna;

void daftarPengguna();
pair<bool, string> autentikasi(string namaPengguna, string kataSandi);
void masuk();
void menuAdmin();
void menuPengguna(string namaPengguna);
void lihatKamar();
void sewaKamar(string namaPengguna);
void tambahKamar();
void hapusKamar();
void ubahKamar();
void detailKamar(Kamar* kamar);
void inputSalah();

int main() {
    daftarKamar[0] = {101, "Single", 300000, true};
    daftarKamar[1] = {102, "Double", 500000, true};
    daftarKamar[2] = {103, "Suite", 800000, true};

    pengguna["admin"] = {"admin123", "admin"}; // Admin statis

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

void daftarPengguna() {
    system("cls"); 
    string namaPengguna, kataSandi, peran;
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
        cout << "\n--- MENU ADMIN ---" << endl;
        cout << "1. Lihat daftar kamar" << endl;
        cout << "2. Tambah kamar" << endl;
        cout << "3. Ubah kamar" << endl;
        cout << "4. Hapus kamar" << endl;
        cout << "5. Logout" << endl;

        string pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == "1") {
            lihatKamar();
        } else if (pilihan == "2") {
            tambahKamar();
        } else if (pilihan == "3") {
            ubahKamar();
        } else if (pilihan == "4") {
            hapusKamar();
        } else if (pilihan == "5") {
            break;
        } else {
            inputSalah();
        }
    }
}

void menuPengguna(string namaPengguna) {
    while (true) {
        system("cls"); 
        cout << "\n--- MENU PENGGUNA ---" << endl;
        cout << "1. Lihat daftar kamar" << endl;
        cout << "2. Sewa kamar" << endl;
        cout << "3. Logout" << endl;

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
    if (jumlahKamar == 0) {
        cout << "Tidak ada kamar yang tersedia." << endl;
    } else {
        cout << "\n----- Daftar Kamar -----" << endl;
        cout << "No. | Nomor Kamar | Tipe | Harga | Tersedia" << endl;
        for (int i = 0; i < jumlahKamar; i++) {
            cout << i + 1 << ". " << daftarKamar[i].nomor << " | " << daftarKamar[i].tipe << " | Rp " << daftarKamar[i].harga << " | " << (daftarKamar[i].tersedia ? "Ya" : "Tidak") << endl;
        }
    }
    system("pause");
}

void sewaKamar(string namaPengguna) {
    lihatKamar();
    int pilih;
    cout << "Pilih kamar (masukkan nomor): ";
    cin >> pilih;

    if (pilih >= 1 && pilih <= jumlahKamar && daftarKamar[pilih - 1].tersedia) {
        daftarKamar[pilih - 1].tersedia = false; // Set kamar tidak tersedia
        cout << "Anda telah menyewa kamar nomor " << daftarKamar[pilih - 1].nomor << " dengan tipe " << daftarKamar[pilih - 1].tipe << " dan harga Rp " << daftarKamar[pilih - 1].harga << "." << endl;
    } else {
        cout << "Nomor kamar tidak valid atau kamar sudah disewa." << endl;
    }
    system("pause");
}

void tambahKamar() {
    system("cls"); 
    int nomor;
    string tipe;
    int harga;

    cout << "Masukkan nomor kamar: ";
    cin >> nomor;
    cout << "Masukkan tipe kamar: ";
    cin >> tipe;
    cout << "Masukkan harga kamar: ";
    cin >> harga;

    if (jumlahKamar < 100) {
        daftarKamar[jumlahKamar++] = {nomor, tipe, harga, true};
        cout << "Kamar berhasil ditambahkan." << endl;
    } else {
        cout << "Tidak dapat menambahkan kamar. Kapasitas penuh." << endl;
    }
    system("pause");
}

void hapusKamar() {
    lihatKamar();
    int pilih;
    cout << "Masukkan nomor kamar yang akan dihapus: ";
    cin >> pilih;

    if (pilih >= 1 && pilih <= jumlahKamar) {
        for (int i = pilih - 1; i < jumlahKamar - 1; i++) {
            daftarKamar[i] = daftarKamar[i + 1];
        }
        jumlahKamar--;
        cout << "Kamar berhasil dihapus." << endl;
    } else {
        cout << "Nomor kamar tidak valid." << endl;
    }
    system("pause");
}

void ubahKamar() {
    lihatKamar();
    int pilih;
    cout << "Masukkan nomor kamar yang akan diubah: ";
    cin >> pilih;

    if (pilih >= 1 && pilih <= jumlahKamar) {
        int nomor;
        string tipe;
        int harga;

        cout << "Masukkan nomor kamar baru (biarkan kosong jika tidak diubah): ";
        cin >> nomor;

        cout << "Masukkan tipe kamar baru (biarkan kosong jika tidak diubah): ";
        cin.ignore();
        getline(cin, tipe);

        cout << "Masukkan harga kamar baru (biarkan kosong jika tidak diubah): ";
        cin >> harga;

        if (nomor > 0) {
            daftarKamar[pilih - 1].nomor = nomor;
        }
        if (!tipe.empty()) {
            daftarKamar[pilih - 1].tipe = tipe;
        }
        if (harga > 0) {
            daftarKamar[pilih - 1].harga = harga;
        }
        cout << "Kamar berhasil diubah." << endl;
    } else {
        cout << "Nomor kamar tidak valid." << endl;
    }
    system("pause");
}

void detailKamar(Kamar* kamar) {
    cout << "\n--- Detail Kamar ---" << endl;
    cout << "Nomor: " << kamar->nomor << endl;
    cout << "Tipe: " << kamar->tipe << endl;
    cout << "Harga: Rp " << kamar->harga << endl;
    cout << "Tersedia: " << (kamar->tersedia ? "Ya" : "Tidak") << endl;
}

void inputSalah() {
    cout << "Input tidak valid. Silakan coba lagi." << endl;
    system("pause"); 
}
