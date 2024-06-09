#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct data{
    string id;
    string namaBarang;
    float hargaBarang;
    int stokBarang;
} dataBarang;

struct barang {
    data dataBarang;
    struct barang *next;
    struct barang *prev;
}*head = NULL, *tail = NULL, *curr;

struct pesanan {
    string idPesanan;
    string idBarang;
    int jumlahPesanan;
};

const int MAXPesanan = 5;
int totalPesanan = 0;
pesanan antrean[MAXPesanan];

void printLogo(string fileName);
void pushTail(data DataBarang);
string cekIdBarang();
int cekStok(string *idBarang);
void insertBarang();
void printSemuaBarang();
void editBarang();
void deleteBarang();
void clearMemo();
void insertAntre();
void printSemuaPesanan();
void editPesanan();
void deletePesanan();

int main(){
    int pilMain;
    int pilSub;
    string searchId;

    printLogo("supes_art.txt");
    
    do
    {
        cout << "===== Menu Utama =====\n";
        cout << "1. Atur Barang\n";
        cout << "2. Kasir\n";
        cout << "3. Keluar\n> ";
        cin >> pilMain;
        cout << endl;

        switch (pilMain){
        case 1:
            do
            {
                cout << "\n===== Atur Barang =====\n";
                cout << "1. Tambah barang\n";
                cout << "2. Tampilkan semua barang\n";
                cout << "3. Edit barang\n";
                cout << "4. Hapus barang\n";
                cout << "5. Kembali\n> ";
                cin >> pilSub;
                cout << endl;

                switch (pilSub){
                case 1:
                    insertBarang();
                    break;
                case 2:
                    printSemuaBarang();
                    break;
                case 3:
                    editBarang();
                    break;
                case 4:
                    deleteBarang();
                    break;
                
                default:
                    break;
                }
                
            } while (pilSub != 5);
            
            break;
        case 2:
            do
            {
                cout << "\n===== Atur Antrean =====\n";
                cout << "1. Tambah pesanan\n";
                cout << "2. Tampilkan semua pesanan\n";
                cout << "3. Edit pesanan\n";
                cout << "4. Hapus pesanan\n";
                cout << "5. Kembali\n> ";
                cin >> pilSub;
                cout << endl;
                
                switch (pilSub){
                case 1:
                    insertAntre();
                    break;
                case 2:
                    printSemuaPesanan();
                    break;
                case 3:{
                    editPesanan();
                    break;
                }
                case 4:
                    deletePesanan();
                    break;
                default:
                    break;
                }
                
            } while (pilSub != 5);
            break;
            case 3:
                clearMemo();
                cout << "Terima kasih!";
                break;
            
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilMain != 3);

    return 0;
}

void printLogo(string fileName){
    string line = "";
    ifstream inFile;
    inFile.open("supes_art.txt");
    if (inFile.is_open()){
        while (getline(inFile, line)){
            cout << line << endl;
        }
        cout << endl;
        cout << endl;
    } else {
        cout << "Logo gagal dimuat.\n";
    }
    inFile.close();
    
}

void pushTail(data DataBarang){
    curr = new barang;
    curr->dataBarang = DataBarang;
    curr->next = curr->prev = NULL;

    if (head == NULL){
        head = tail = curr;
    } else {
        tail->next = curr;
        curr->prev = tail;
        tail = curr;
    }
    head->prev = tail->next = NULL;
}

/*
fungsi agar pengguna tak perlu keluar program ketika salah memasukkan ID
dan bisa memasukkan lagi ID yang benar
*/  
string cekIdBarang(){
    curr = head;
    string id;

    cin >> id;
    
    while (id != curr->dataBarang.id){
        cout << "ID barang tak ditemukan. Masukkan lagi: ";
        cin >> id;
        if (curr->next == NULL){
            curr = head;
        } else {
            curr = curr->next;
        }
    };

    return id;
}

// fungsi agar jumlah stok berkurang ketika pesanan dibuat
int cekStok(string *idBarang){
    int jumlahBarangDibeli;
    cout << "Masukkan jumlah barang yang dibeli: ";
    cin >> jumlahBarangDibeli;

    curr = head;
    while (curr->dataBarang.id != *idBarang){
        curr = curr->next;
    }

    while (jumlahBarangDibeli > curr->dataBarang.stokBarang){
        cout << "Stok tidak mencukupi(" << curr->dataBarang.stokBarang << "). Kurangi jumlah barang yang dibeli.";    
        cout << "Masukkan jumlah barang yang dibeli: ";
        cin >> jumlahBarangDibeli;
    }
    curr->dataBarang.stokBarang = curr->dataBarang.stokBarang-jumlahBarangDibeli;

    return jumlahBarangDibeli;
}

void insertBarang(){
    cout << "=== Tambah Data Barang ===\n";
    data data_barang;

    cout << "Masukkan ID: ";
    cin >> data_barang.id;
    cout << "Masukkan nama: ";
    cin.ignore();
    getline(cin, data_barang.namaBarang);
    cout << "Masukkan harga: ";
    cin >> data_barang.hargaBarang;
    cout << "Masukkan stok: ";
    cin >> data_barang.stokBarang;
    pushTail(data_barang);
    cout << "Barang berhasil ditambahkan.\n";
}

void printSemuaBarang(){
    cout << "=== Data Barang ===\n";
    curr = head;
    if (curr == NULL){
        cout << "Gudang kosong. Harap isi terlebih dahulu\n";
        cout << "===================\n";
    } else {
        while (curr != NULL){
            cout << curr->dataBarang.id << " | ";
            cout << curr->dataBarang.namaBarang << " | ";
            cout << curr->dataBarang.hargaBarang << " | ";
            cout << curr->dataBarang.stokBarang << endl;
            cout << "===================\n";
            curr = curr->next;
        }
    }
}

void editBarang(){
    cout << "=== Edit Data Barang ===\n\n";
    printSemuaBarang();

    if (head != NULL){
        string searchId;
        char pilLagi;

        cout << "Masukkan ID barang yang akan diedit: ";
        searchId = cekIdBarang();

        curr = head;
        while (searchId != curr->dataBarang.id) {
            curr = curr->next;
        }

        cout << "Masukkan nama: ";
        cin.ignore();
        getline(cin, curr->dataBarang.namaBarang);
        cout << "Masukkan harga: ";
        cin >> curr->dataBarang.hargaBarang;
        cout << "Masukkan stok: ";
        cin >> curr->dataBarang.stokBarang;
        cout << "Data barang berhasil diubah\n";
    }
}

void deleteBarang(){
    cout << "=== Hapus Data Barang ===\n\n";
    printSemuaBarang();

    if (head != NULL){
        string searchId;

        cout << "Masukkan ID barang yang akan dihapus: ";
        searchId = cekIdBarang();
        
        curr = head;
        while (searchId != curr->dataBarang.id) {
            curr = curr->next;
        }

        if (curr->prev == NULL && curr->next == NULL){
            curr = head = NULL;
            free(curr);
        } else if (curr == head){
            head = curr->next;
            head->prev = NULL;
            free(curr);
        } else if (curr == tail){
            tail = curr->prev;
            tail->next = NULL;
            free(curr);
        } else {
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            free(curr);
        }
        cout << "Barang berhasil dihapus\n";
    }
}

// fungsi untuk mencabut semua memori yang dipakai oleh list
void clearMemo(){
    curr = head;
    while (curr != NULL){
        head = head->next;
        free(curr);
        curr = head;
    }
    head = tail = NULL;
}

void insertAntre(){
    cout << "=== Tambah Pesanan ===\n\n";
    printSemuaBarang();
    totalPesanan = 0;
    char pilLagi;

    do
    {
        cout << "Masukkan ID pesanan: ";
        cin >> antrean[totalPesanan].idPesanan;
        cout << "Masukkan ID barang pesanan: ";
        antrean[totalPesanan].idBarang = cekIdBarang();
        antrean[totalPesanan].jumlahPesanan = cekStok(&antrean[totalPesanan].idBarang);
        
        totalPesanan++;

        cout << "Masukkan pesanan lagi? (y/n) ";
        cin >> pilLagi;
    } while (pilLagi != 'n');
}

void printSemuaPesanan(){
    cout << "=== Data Pesanan ===\n";
    int i = 0;
    curr = head;

    if (totalPesanan == 0){
        cout << "Antrean kosong.\n";
        cout << "===================\n";
    } else {
        for (int i = 0; i < totalPesanan; i++){
            cout << "Pesanan ke- " << i+1 << ":\n";
            while (curr->dataBarang.id != antrean[i].idBarang){
                curr = curr->next;
            }
                
            cout << "ID: " << antrean[i].idPesanan << " | ";
            cout << "Nama Barang: " << curr->dataBarang.namaBarang << " | ";
            cout << "Jumlah: " << antrean[i].jumlahPesanan << " | ";
            cout << "Harga: " << curr->dataBarang.hargaBarang*antrean[i].jumlahPesanan << endl;
            cout << "===================\n";
        }    
    }
    
}

void editPesanan(){
    string searchId;
    int i = 0;
    
    cout << "=== Edit Data Pesanan ===\n\n";
    printSemuaPesanan();
    if (totalPesanan > 0){
        cout << "Masukkan ID pesanan yang akan diedit: ";
        cin >> searchId;
        while (searchId != antrean[i].idPesanan){
            i++;
        }
        printSemuaBarang();
        cout << "Masukkan ID barang yang akan diedit: ";
        antrean[i].idBarang = cekIdBarang();
        cout << "Masukkan jumlah barang yang dibeli: ";
        cin >> antrean[i].jumlahPesanan;
        cout << "Pesanan berhasil diubah.\n";
    }
}

void deletePesanan(){
    string searchId;
    int i = 0;
    
    cout << "=== Delete Pesanan ===\n\n";
    printSemuaPesanan();
    if (totalPesanan > 0){
        cout << "Masukkan ID pesanan yang akan dihapus: ";
        cin >> searchId;
        while (searchId != antrean[i].idPesanan){
            i++;
        }

        for (int a = i; a < totalPesanan; a++){
            antrean[i] = antrean[i+1];
        }
        totalPesanan--;
        cout << "Pesanan berhasil dihapus.\n";
    }
}