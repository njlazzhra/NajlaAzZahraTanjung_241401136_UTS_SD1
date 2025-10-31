#include <iostream>
#include <string>
using namespace std;

struct Patient {
    string name;
    string species;
    int age;
    int emergency;
};

struct Queue {
    Patient* arr;
    int capacity;
    int size;

    // inisialisasi queue dengan kapasitas awal
    Queue(int cap) {
        capacity = cap;
        size = 0;
        arr = new Patient[capacity];
    }

    // fungsi untuk menambah pasien ke dalam queue
    void enqueue(const Patient& p) {
        if (size == capacity) {
            capacity *= 2;
            Patient* newArr = new Patient[capacity];

            for (int i = 0; i < size; i++) 
                newArr[i] = arr[i]; //ini maksudnya copy semua elemen lama ke array baru

            delete[] arr; // kemudian hapus array lama
            arr = newArr;
        }
        arr[size++] = p;
    }

    // urut berdasarkan emergency terbesar → prioritas tertinggi
    void sortQueue() {
        for (int i = 0; i < size - 1; i++) { 
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j].emergency < arr[j + 1].emergency) {
                    swap(arr[j], arr[j + 1]); //ini akan menukar posisi pasien berdasrkan emergency
                }
            }
        }
    }

    // menampilkan isi queue
    void display() {
        cout << "\n=== Urutan Penanganan Pasien ===\n";
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". " << arr[i].name
                 << " (" << arr[i].age << " tahun) - Darurat: "
                 << arr[i].emergency << endl;
        }
    }
};


// fungsi untuk ekstraksi angka dari input umur (tahun)
int extractAge(const string& input) {
    string angka = "";

    for (char c : input) { // iterasi setiap karakter
        if (isdigit(c))
            angka += c;
    }

    return angka.empty() ? 0 : stoi(angka); //maksudnya mengembalikan 0 jika tidak ada angka
}


int main() {
    system("cls"); 
    int n;
    cout << "Masukkan jumlah pasien: "; cin >> n;
    cin.ignore(); 

    Queue q(n); 
    for (int i = 0; i < n; i++) {
        Patient p;
        cout << "\nPasien " << i + 1 << ":\n";

        cout << "Nama hewan: "; getline(cin, p.name);
        cout << "Jenis hewan: "; getline(cin, p.species);
        cout << "Umur: "; string ageInput; getline(cin, ageInput);
        p.age = extractAge(ageInput);   // otomatis mengambil angka saja
        cout << "Tingkat darurat (1-5): ";
        cin >> p.emergency; cin.ignore(); 

        q.enqueue(p);
    }

    q.sortQueue();
    q.display();

    return 0;
}
