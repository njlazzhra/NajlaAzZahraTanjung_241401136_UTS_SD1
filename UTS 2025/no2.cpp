#include <iostream>
#include <string>
using namespace std;

struct Node {
    string title;
    int year;
    int rating;
    Node* next;

    Node(string t, int y, int r): 
    title(t), 
    year(y), 
    rating(r), 
    next(nullptr) {}
};

class LinkedList {
private:
    Node* head; // pointer ke node pertama
    int count;

public:
    LinkedList() : head(nullptr), count(0) {} //ini konstruktor untuk inisialisasi linked list

    //ini destruktor untuk membersihkan memori saat linked list dihapus
    ~LinkedList() {
        Node* cur = head;
        while (cur) {
            Node* temp = cur->next;
            delete cur;
            cur = temp;
        }
    }

    // mengembalikan ukuran list
    int size() const {
        return count;
    }

    // insert data film ke belakang list
    void insertFilm(const string& title, int year, int rating) {
        Node* node = new Node(title, year, rating);

        if (head == nullptr) { // jika list masih kosong
            head = node;
        } else { // cari node terakhir
            Node* cur = head;
            while (cur->next != nullptr)
                cur = cur->next;

            cur->next = node;
        }
        count++;
    }

    // hapus film berdasarkan judul
    bool deleteFilm(const string& title) {
        if (!head) return false;

        // jika film yang dihapus ada di head
        if (head->title == title) {
            Node* del = head;
            head = head->next;
            delete del;
            count--;
            return true;
        }
        // maka cari di node selanjutnya
        Node* cur = head;
        while (cur->next != nullptr) {
            if (cur->next->title == title) {
                Node* del = cur->next;
                cur->next = cur->next->next;
                delete del;
                count--;
                return true;
            }
            cur = cur->next; // lanjut cek ke node berikutnya
        }
        return false;
    }

    // menampilkan seluruh film
    void displayFilms() const {
        cout << "\n===== DAFTAR WATCHLIST FILM =====\n";
        if (head == nullptr) {
            cout << "(Belum ada film tersimpan)\n";
            return;
        }
        //
        Node* cur = head;
        int index = 1;
        while (cur != nullptr) {
            cout << index++ << ". " << cur->title
                 << " (" << cur->year << ")"
                 << " - Rating: " << cur->rating << "/10\n";
            cur = cur->next;
        }
    }
};

int main() {
    system("cls");
    LinkedList list;
    int n;

    cout << "Masukkan jumlah film awal: "; cin >> n;
    cin.ignore(); 

    for (int i = 1; i <= n; i++) {
        string title;
        int year, rating;

        cout << "\nFilm " << i << endl;
        cout << "Judul  : ";
        getline(cin, title);

        cout << "Tahun  : ";
        cin >> year;

        cout << "Rating (1-10): ";
        cin >> rating;

        cin.ignore(); 
        list.insertFilm(title, year, rating);
    }

    char del;
    cout << "\nApakah ingin menghapus film? (y/n): ";
    cin >> del;
    cin.ignore();

    if (del == 'y' || del == 'Y') {
        string target;
        cout << "Masukkan judul film: ";
        getline(cin, target);

        if (!list.deleteFilm(target)) {
            cout << "\nFilm tidak ditemukan!\n";
        }
    }

    list.displayFilms();
    cout << "\nTotal film tersisa: " << list.size() << endl;

    return 0;
}
