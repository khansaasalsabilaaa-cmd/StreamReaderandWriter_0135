#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>

using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    // Constructor
    TokoElektronik() {
        etalase[0] = "Laptop ASUS";
        etalase[1] = "Smartphone Samsung";
        etalase[2] = "Printer Epson";
    }

    // Method mengambil produk
    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw string("Gagal Mengambil Barang : Rak nomor " +
                         to_string(nomorRak) +
                         " kosong atau tidak tersedia!");
        }
    }
};

// ================= CRUD FILE =================

const string NAMA_FILE = "gudang.txt";

void tampilkanBarang() {
    ifstream file(NAMA_FILE);

    cout << "\n===== DATA BARANG DI GUDANG =====\n";

    string barang;
    int no = 1;

    while (getline(file, barang)) {
        cout << no++ << ". " << barang << endl;
    }

    if (no == 1)
        cout << "Gudang masih kosong.\n";

    file.close();
}

void tambahBarang() {
    ofstream file(NAMA_FILE, ios::app);

    string barang;
    cin.ignore();

    cout << "Masukkan nama barang: ";
    getline(cin, barang);

    file << barang << endl;
    file.close();

    cout << "Barang berhasil ditambahkan!\n";
}

void updateBarang() {
    ifstream file(NAMA_FILE);

    vector<string> data;
    string barang;

    while (getline(file, barang))
        data.push_back(barang);

    file.close();

    int nomor;
    cout << "Nomor barang yang ingin diubah: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    cin.ignore();

    cout << "Masukkan nama barang baru: ";
    getline(cin, data[nomor - 1]);

    ofstream tulis(NAMA_FILE);

    for (string item : data)
        tulis << item << endl;

    tulis.close();

    cout << "Data berhasil diperbarui!\n";
}

void hapusBarang() {
    ifstream file(NAMA_FILE);

    vector<string> data;
    string barang;

    while (getline(file, barang))
        data.push_back(barang);

    file.close();

    int nomor;
    cout << "Nomor barang yang ingin dihapus: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    data.erase(data.begin() + nomor - 1);

    ofstream tulis(NAMA_FILE);

    for (string item : data)
        tulis << item << endl;

    tulis.close();

    cout << "Data berhasil dihapus!\n";
}

// ================= MAIN =================

int main() {
    TokoElektronik toko;

    int pilihan;

    do {
        cout << "\n====================================";
        cout << "\n MANAJEMEN TOKO ELEKTRONIK GIBRAN JAYA";
        cout << "\n====================================\n";

        tampilkanBarang();

        cout << "\nMenu:";
        cout << "\n1. Tambah Barang";
        cout << "\n2. Update Barang";
        cout << "\n3. Hapus Barang";
        cout << "\n4. Simulasi Etalase";
        cout << "\n0. Keluar";
        cout << "\nPilihan : ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahBarang();
            break;

        case 2:
            updateBarang();
            break;

        case 3:
            hapusBarang();
            break;

        case 4:
            cout << "\n=== SIMULASI ETALASE ===\n";

            // Skenario 1
            try {
                cout << "Rak 1 : "
                     << toko.ambilProduk(1)
                     << endl;
            }
            catch (string pesan) {
                cout << pesan << endl;
            }

            // Skenario 2
            try {
                cout << "Rak 5 : "
                     << toko.ambilProduk(5)
                     << endl;
            }
            catch (string pesan) {
                cout << pesan << endl;
            }

            break;

        case 0:
            cout << "Program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak tersedia!\n";
        }

    } while (pilihan != 0);

    return 0;
}