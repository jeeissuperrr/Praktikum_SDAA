#include <iostream>
using namespace std;

// Fungsi rekursif untuk menyelesaikan masalah Menara Hanoi
void hanoi(int n, char asal, char tujuan, char sementara) {
    if (n == 1) {
        cout << "Pindahkan piringan 1 dari menara " << asal << " ke menara " << tujuan << "." << endl;
        return;
    }
    
    hanoi(n - 1, asal, sementara, tujuan);
    cout << "Pindahkan piringan " << n << " dari menara " << asal << " ke menara " << tujuan << "." << endl;
    hanoi(n - 1, sementara, tujuan, asal);
}

int main() {
    int jumlahPiringan = 3; 
    
    cout << "POSTTEST 1 StrukData\n";
    cout << "Kita akan memindahkan " << jumlahPiringan << " piringan dari menara A ke menara C.\n";
    cout << "Lihat Output Dibawah ini.\n\n";

    hanoi(jumlahPiringan, 'A', 'C', 'B');
    
    cout << "\nSemua piringan berhasil dipindahkan! Terima kasih sudah menggunakan program ini.\n";
    
    return 0;
}
