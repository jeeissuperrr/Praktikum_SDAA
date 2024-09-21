#include <iostream>
#include <map>
#include <string>
using namespace std;

struct Tiket {
    string tujuan;
    string maskapai;
    int harga;
};

struct Pengguna {
    string kataSandi;
    string peran;
};

Tiket daftarTiket[100];
int jumlahTiket = 3;
map<string, Pengguna> pengguna;

void daftarPengguna();
pair<bool, string> autentikasi(string namaPengguna, string kataSandi);
void masuk();
void menuAdmin(string namaPengguna);
void menuPengguna(string namaPengguna);
void lihatTiket();
void beliTiket(string namaPengguna);
void tambahTiket();
void hapusTiket();
void ubahTiket();
void detailTiket(Tiket* tiket);
void inputSalah();  

int main() {
    daftarTiket[0] = {"JPN", "GARUDA", 100};
    daftarTiket[1] = {"MLY", "EMIRATES", 300};
    daftarTiket[2] = {"SGP", "AIRASIA", 200};

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
    cout << "Apakah Anda ingin menjadi admin [a] atau pengguna biasa [u]? ";
    cin >> peran;

    pengguna[namaPengguna] = {kataSandi, (peran == "a") ? "admin" : "pengguna"};

    cout << "Registrasi berhasil!" << endl;
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
            menuAdmin(namaPengguna);
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

void menuAdmin(string namaPengguna) {
    while (true) {
        system("cls"); 
        cout << "\n--- MENU ADMIN ---" << endl;
        cout << "1. Lihat daftar tiket" << endl;
        cout << "2. Tambah tiket" << endl;
        cout << "3. Ubah tiket" << endl;
        cout << "4. Hapus tiket" << endl;
        cout << "5. Logout" << endl;

        string pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == "1") {
            lihatTiket();
        } else if (pilihan == "2") {
            tambahTiket();
        } else if (pilihan == "3") {
            ubahTiket();
        } else if (pilihan == "4") {
            hapusTiket();
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
        cout << "1. Lihat daftar tiket" << endl;
        cout << "2. Beli tiket" << endl;
        cout << "3. Logout" << endl;

        string pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == "1") {
            lihatTiket();
        } else if (pilihan == "2") {
            beliTiket(namaPengguna);
        } else if (pilihan == "3") {
            break;
        } else {
            inputSalah();
        }
    }
}

void lihatTiket() {
    if (jumlahTiket == 0) {
        cout << "Tidak ada tiket yang tersedia." << endl;
    } else {
        cout << "\n----- Daftar Tiket Pesawat -----" << endl;
        cout << "No. | Tujuan | Maskapai | Harga" << endl;
        for (int i = 0; i < jumlahTiket; i++) {
            cout << i + 1 << ". " << daftarTiket[i].tujuan << " | " << daftarTiket[i].maskapai << " | Rp " << daftarTiket[i].harga << endl;
        }
    }
    system("pause"); 
}

void beliTiket(string namaPengguna) {
    lihatTiket();
    int pilih;
    cout << "Pilih tiket (masukkan nomor): ";
    cin >> pilih;

    if (pilih >= 1 && pilih <= jumlahTiket) {
        detailTiket(&daftarTiket[pilih - 1]); 
        int jumlah;
        cout << "Masukkan jumlah tiket: ";
        cin >> jumlah;
        if (jumlah > 0) {
            int totalHarga = jumlah * daftarTiket[pilih - 1].harga;
            cout << "Anda membeli " << jumlah << " tiket dengan total harga Rp " << totalHarga << "." << endl;
        } else {
            cout << "Jumlah tiket tidak valid." << endl;
        }
    } else {
        cout << "Nomor tiket tidak valid." << endl;
    }
    system("pause"); 
}

void tambahTiket() {
    system("cls"); 
    string tujuan, maskapai;
    int harga;
    cout << "Masukkan tujuan: ";
    cin >> tujuan;
    cout << "Masukkan maskapai: ";
    cin >> maskapai;
    cout << "Masukkan harga tiket: ";
    cin >> harga;

    if (jumlahTiket < 100) {
        daftarTiket[jumlahTiket++] = {tujuan, maskapai, harga};
        cout << "Tiket berhasil ditambahkan." << endl;
    } else {
        cout << "Tidak dapat menambahkan tiket. Kapasitas penuh." << endl;
    }
    system("pause"); 
}

void hapusTiket() {
    lihatTiket();
    int pilih;
    cout << "Masukkan nomor tiket yang akan dihapus: ";
    cin >> pilih;

    if (pilih >= 1 && pilih <= jumlahTiket) {
        for (int i = pilih - 1; i < jumlahTiket - 1; i++) {
            daftarTiket[i] = daftarTiket[i + 1];
        }
        jumlahTiket--;
        cout << "Tiket berhasil dihapus." << endl;
    } else {
        cout << "Nomor tiket tidak valid." << endl;
    }
    system("pause"); 
}

void ubahTiket() {
    lihatTiket();
    int pilih;
    cout << "Masukkan nomor tiket yang akan diubah: ";
    cin >> pilih;

    if (pilih >= 1 && pilih <= jumlahTiket) {
        string tujuan, maskapai;
        int harga;

        cout << "Masukkan tujuan baru (biarkan kosong jika tidak diubah): ";
        cin.ignore();
        getline(cin, tujuan);

        cout << "Masukkan maskapai baru (biarkan kosong jika tidak diubah): ";
        getline(cin, maskapai);

        cout << "Masukkan harga baru (biarkan kosong jika tidak diubah): ";
        string inputHarga;
        getline(cin, inputHarga);

        if (!tujuan.empty()) {
            daftarTiket[pilih - 1].tujuan = tujuan;
        }
        if (!maskapai.empty()) {
            daftarTiket[pilih - 1].maskapai = maskapai;
        }
        if (!inputHarga.empty()) {
            harga = stoi(inputHarga);
            daftarTiket[pilih - 1].harga = harga;
        }
        cout << "Tiket berhasil diubah." << endl;
    } else {
        cout << "Nomor tiket tidak valid." << endl;
    }
    system("pause"); 
}

void detailTiket(Tiket* tiket) {
    cout << "\n--- Detail Tiket ---" << endl;
    cout << "Tujuan: " << tiket->tujuan << endl;
    cout << "Maskapai: " << tiket->maskapai << endl;
    cout << "Harga: Rp " << tiket->harga << endl;
}

void inputSalah() {
    cout << "Input tidak valid. Silakan coba lagi." << endl;
    system("pause"); 
}
