#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <queue>

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
        cout << "\n--- MENU ADMIN ---" << endl;
        cout << "1. Lihat daftar kamar (Ascending)" << endl;
        cout << "2. Lihat daftar kamar (Descending)" << endl;
        cout << "3. Tambah kamar" << endl;
        cout << "4. Ubah kamar" << endl;
        cout << "5. Hapus kamar" << endl;
        cout << "6. Tampilkan log aktivitas" << endl;
        cout << "7. Logout" << endl;

        string pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == "1") {
            lihatKamarAscending();
        } else if (pilihan == "2") {
            lihatKamarDescending();
        } else if (pilihan == "3") {
            tambahKamar();
        } else if (pilihan == "4") {
            ubahKamar();
        } else if (pilihan == "5") {
            hapusKamar();
        } else if (pilihan == "6") {
            tampilkanLogAdmin();
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
        cout << "\n--- MENU PENGGUNA ---" << endl;
        cout << "1. Lihat daftar kamar" << endl;
        cout << "2. Sewa kamar" << endl;
        cout << "3. Proses antrean" << endl;
        cout << "4. Logout" << endl;

        string pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == "1") {
            lihatKamar();
        } else if (pilihan == "2") {
            sewaKamar(namaPengguna);
        } else if (pilihan == "3") {
            prosesAntrean();
        } else if (pilihan == "4") {
            break;
        } else {
            inputSalah();
        }
    }
}

void lihatKamarAscending() {
    headKamar = mergeSort(headKamar); // Menggunakan Merge Sort (Ascending)
    lihatKamar();
}

void lihatKamarDescending() {
    headKamar = quickSort(headKamar, nullptr); // Menggunakan Quick Sort (Descending)
    lihatKamar();
}

void lihatKamar() {
    if (jumlahKamar == 0) {
        cout << "Tidak ada kamar yang tersedia." << endl;
    } else {
        cout << "\n----- Daftar Kamar -----" << endl;
        cout << "No. | Nomor Kamar | Tipe | Harga | Tersedia" << endl;
        Kamar* current = headKamar;
        int i = 1;
        while (current != nullptr) {
            cout << i++ << ". " << current->nomor << " | " << current->tipe << " | Rp " << current->harga << " | " << (current->tersedia ? "Ya" : "Tidak") << endl;
            current = current->next;
        }
    }
    system("pause");
}

void sewaKamar(string namaPengguna) {
    lihatKamar();
    int pilih;
    cout << "Pilih kamar (masukkan nomor): ";
    cin >> pilih;

    Kamar* kamarDipilih = cariKamar(pilih - 1);
    if (kamarDipilih && kamarDipilih->tersedia) {
        kamarDipilih->tersedia = false;
        cout << "Anda telah menyewa kamar nomor " << kamarDipilih->nomor << " dengan tipe " << kamarDipilih->tipe << " dan harga Rp " << kamarDipilih->harga << "." << endl;
        antreanSewa.push(namaPengguna); // Tambahkan pengguna ke antrean
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

    tambahKamarAwal(nomor, tipe, harga, true);
    logAdmin.push("Menambah kamar: " + to_string(nomor)); // Tambah log
    cout << "Kamar berhasil ditambahkan." << endl;
    system("pause");
}

void hapusKamar() {
    lihatKamar();
    int pilih;
    cout << "Pilih kamar untuk dihapus (masukkan nomor): ";
    cin >> pilih;

    Kamar* kamarDihapus = cariKamar(pilih - 1);
    if (kamarDihapus) {
        logAdmin.push("Menghapus kamar: " + to_string(kamarDihapus->nomor)); // Tambah log
        if (kamarDihapus == headKamar) {
            headKamar = headKamar->next;
        } else {
            Kamar* prev = cariKamar(pilih - 2);
            prev->next = kamarDihapus->next;
        }
        delete kamarDihapus;
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
    cout << "Pilih kamar untuk diubah (masukkan nomor): ";
    cin >> pilih;

    Kamar* kamarDipilih = cariKamar(pilih - 1);
    if (kamarDipilih) {
        string tipeBaru;
        int hargaBaru;
        cout << "Masukkan tipe baru: ";
        cin >> tipeBaru;
        cout << "Masukkan harga baru: ";
        cin >> hargaBaru;

        kamarDipilih->tipe = tipeBaru;
        kamarDipilih->harga = hargaBaru;
        logAdmin.push("Mengubah kamar: " + to_string(kamarDipilih->nomor)); // Tambah log
        cout << "Kamar berhasil diubah." << endl;
    } else {
        cout << "Nomor kamar tidak valid." << endl;
    }
    system("pause");
}

void detailKamar(Kamar* kamar) {
    if (kamar != nullptr) {
        cout << "Nomor Kamar: " << kamar->nomor << endl;
        cout << "Tipe: " << kamar->tipe << endl;
        cout << "Harga: Rp " << kamar->harga << endl;
        cout << "Tersedia: " << (kamar->tersedia ? "Ya" : "Tidak") << endl;
    } else {
        cout << "Kamar tidak ditemukan." << endl;
    }
}

void inputSalah() {
    cout << "Input tidak valid. Coba lagi!" << endl;
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
    if (posisi < 0 || posisi >= jumlahKamar) {
        return nullptr;
    }

    Kamar* current = headKamar;
    for (int i = 0; i < posisi; i++) {
        current = current->next;
    }
    return current;
}

void tampilkanLogAdmin() {
    if (logAdmin.empty()) {
        cout << "Log aktivitas kosong." << endl;
    } else {
        cout << "\n--- Log Aktivitas ---" << endl;
        while (!logAdmin.empty()) {
            cout << logAdmin.top() << endl;
            logAdmin.pop();
        }
    }
    system("pause");
}

void prosesAntrean() {
    if (antreanSewa.empty()) {
        cout << "Tidak ada antrean sewa." << endl;
    } else {
        cout << "Antrean sewa sedang diproses untuk " << antreanSewa.front() << endl;
        antreanSewa.pop();
    }
    system("pause");
}

// Fungsi untuk Merge Sort
Kamar* mergeSort(Kamar* head) {
    if (!head || !head->next) {
        return head;
    }
    Kamar* a;
    Kamar* b;
    split(head, &a, &b);
    a = mergeSort(a);
    b = mergeSort(b);
    return sortedMerge(a, b);
}

Kamar* sortedMerge(Kamar* a, Kamar* b) {
    if (!a) return b;
    if (!b) return a;

    Kamar* result = nullptr;
    if (a->harga <= b->harga) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

void split(Kamar* head, Kamar** frontRef, Kamar** backRef) {
    Kamar* slow = head;
    Kamar* fast = head->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = head;
    *backRef = slow->next;
    slow->next = nullptr;
}

// Fungsi untuk Quick Sort
Kamar* quickSort(Kamar* head, Kamar* end) {
    if (!head || head == end) {
        return head;
    }

    Kamar* newHead = nullptr;
    Kamar* newEnd = nullptr;
    Kamar* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Kamar* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;
        newHead = quickSort(newHead, temp);
        temp = cariKamar(jumlahKamar - 1);
        temp->next = pivot;
    }
    pivot->next = quickSort(pivot->next, newEnd);

    return newHead;
}

Kamar* partition(Kamar* head, Kamar* end, Kamar** newHead, Kamar** newEnd) {
    Kamar* pivot = end;
    Kamar* prev = nullptr;
    Kamar* curr = head;
    Kamar* tail = pivot;

    while (curr != pivot) {
        if (curr->harga > pivot->harga) {
            if (!*newHead) *newHead = curr;
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) prev->next = curr->next;
            Kamar* temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if (!*newHead) *newHead = pivot;

    *newEnd = tail;
    return pivot;
}
