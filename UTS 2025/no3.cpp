#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    int vertexCount;
    vector<vector<int>> matrix;

public:
    // inisialisasi graph dengan jumlah vertex
    Graph(int V) {
        vertexCount = V;
        matrix.assign(V, vector<int>(V, 0));
    }

    // menambahkan koneksi antar vertex dengan bobot cost
    void addConnection(int src, int dest, int cost) {
        src--; dest--;
        if (src >= 0 && src < vertexCount && dest >= 0 && dest < vertexCount) {
            matrix[src][dest] = cost;
            matrix[dest][src] = cost;
        } else {
            cout << "Node tidak valid!\n";
        }
    }

    // mencetak adjacency matrixnya
    void displayMatrix() {
        cout << "Matriks Ketetanggaan (berisi jarak antar kota):\n";
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }

    // DFS berbobot dengan rekursi
    void dfsRecursive(int node, vector<bool>& visited, string city[]) {
        visited[node] = true;
        cout << city[node];

        vector<pair<int, int>> neighbor;  // (cost, index kota)

        // menyimpan tetangga yang belum dikunjungi
        for (int i = 0; i < vertexCount; i++) {
            if (matrix[node][i] != 0 && !visited[i]) {
                neighbor.push_back({ matrix[node][i], i });
            }
        }

        // mengurutkan tetangga berdasarkan bobot (cost) terkecil
        for (int i = 0; i < neighbor.size(); i++) {
            for (int j = i + 1; j < neighbor.size(); j++) {
                if (neighbor[j].first < neighbor[i].first)
                    swap(neighbor[i], neighbor[j]);
            }
        }

        // mengurutkan tetangga dan melanjutkan DFS
        for (auto& next : neighbor) {
            if (!visited[next.second]) {
                cout << " -> ";
                dfsRecursive(next.second, visited, city);
            }
        }
    }

    //memulai DFS dari node tertentu
    void dfsStart(int start, string city[]) {
        vector<bool> visited(vertexCount, false);
        cout << "PENJELAJAHAN PARUL (DFS dari A)" << city[start] << "):\n";
        dfsRecursive(start, visited, city);
        cout << "\n\n";
    }

    //mengembalikan isi vektor
    void reverseList(vector<int>& v) {
        int l = 0, r = v.size() - 1;
        while (l < r) {
            swap(v[l], v[r]);
            l++; r--;
        }
    }

    // mencari jalur terpendek menggunakan BFS berbobot
    void shortestPath(int start, int finish, string city[]) {
        vector<int> dist(vertexCount, 9999);
        vector<int> prev(vertexCount, -1);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) { // selam
            int cur = q.front(); q.pop();

            for (int next = 0; next < vertexCount; next++) {
                if (matrix[cur][next] != 0) {
                    int newDistance = dist[cur] + matrix[cur][next];
                    if (newDistance < dist[next]) {
                        dist[next] = newDistance;
                        prev[next] = cur;
                        q.push(next);
                    }
                }
            }
        }

        // membangun jalur dari finish ke start
        vector<int> path;
        for (int temp = finish; temp != -1; temp = prev[temp])
            path.push_back(temp);

        reverseList(path);

        //Output 
        cout << "JALUR TERCEPAT PARUL (BFS):\n";
        int totalCost = 0;

        // menampilkan jalur beserta biayanya
        for (int i = 0; i < path.size(); i++) {
            cout << city[path[i]];
            if (i < path.size() - 1) {
                totalCost += matrix[path[i]][path[i + 1]];
                cout << " (" << matrix[path[i]][path[i + 1]] << "m)\n";
            }
        }

        cout << "\n\nJalur terpendek: ";
        for (int i = 0; i < path.size(); i++) {
            cout << city[path[i]];
            if (i < path.size() - 1) cout << " -> ";
        }

        cout << "\nTotal langkah: " << path.size() - 1 << " edge";
        cout << "\nTotal jarak: " << totalCost << " meter\n";
    }
};

int main() {
    system("cls");
    Graph g(5);
    string city[5] = {"A", "B", "C", "D", "E"};

    g.addConnection(1, 2, 5);
    g.addConnection(1, 3, 2);
    g.addConnection(2, 4, 4);
    g.addConnection(3, 4, 1);
    g.addConnection(4, 5, 3);

    cout << "PENJELAJAHAN PARUL (DFS dari A)\n";
    g.displayMatrix();
    cout << endl;

    g.dfsStart(0, city);
    g.shortestPath(0, 4, city);

    return 0;
}
