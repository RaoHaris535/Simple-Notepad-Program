#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T d = 0, Node* n = nullptr, Node* p = nullptr) {
        data = d; next = n; prev = p;
    }
    T GetData() { return data; }
    Node* GetNext() { return next; }
    Node* Getprev() { return prev; }
    ~Node() {}
};

template<typename T>
class Linkedlist {
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* cursor;      // visual cursor node (contains '|')
    int size;

public:
    Linkedlist(Node<T>* h = nullptr, Node<T>* t = nullptr, Node<T>* c = nullptr, int s = 0) {
        head = h; tail = t; cursor = c; size = s;

        Node<T>* dummy2 = new Node<T>('|');
        Node<T>* dummy = new Node<T>;
        tail = head = dummy;
        cursor = dummy2;
        dummy->next = cursor;
        cursor->prev = dummy;
    }

    void InsertAtHead(T value) {
        if (size == 0) {
            Node<T>* temp = new Node<T>(value, head->next, head);
            head->next = temp;
            tail = temp;
            tail->next->prev = tail; // tail->next is cursor
            size++;
        }
        else {
            Node<T>* temp = new Node<T>(value, head->next, head);
            head->next = temp;
            size++;
        }
    }

    void InsertAtTail(T value) {
        if (size == 0) {
            Node<T>* temp = new Node<T>(value, head->next, head);
            head->next = temp;
            tail = temp;
            size++;
        }
        else {
            Node<T>* temp = new Node<T>(value, tail->next, tail);
            tail->next = temp;
            tail = temp;
            temp->next = cursor;
            cursor->prev = tail;
            size++;
        }
    }

    void InsertAtCursor(T value) {
        if (size == 0) {
            this->InsertAtHead(value);
            return;
        }
        else if (cursor->prev == tail) {
            this->InsertAtTail(value);
            return;
        }
        else {
            Node<T>* temp = new Node<T>(value, cursor, cursor->prev);
            cursor->prev->next = temp;
            cursor->prev = temp;
            size++;
            return;
        }
    }

    void Erase() {
        if (cursor->prev == head) {
            return;
        }
        else {
            Node<T>* temp = cursor->prev;
            cursor->prev = cursor->prev->prev;
            cursor->prev->next = cursor;
            if (tail == temp) {
                delete temp;
                tail = cursor->prev;
                size--;
                return;
            }
            delete temp;
            size--;
            return;
        }
    }

    void Move(int order) {
        if (order == -32) {
            int ch = _getch();
            if (ch == 75) { // left
                if (cursor->prev == tail) {
                    tail->next = cursor->next;
                    cursor->next = tail;
                    tail->prev->next = cursor;
                    cursor->prev = tail->prev;
                    tail->prev = cursor;
                    return;
                }
                else if (cursor->prev == head) {
                    return;
                }
                else {
                    Node<T>* ptemp = cursor->prev;
                    Node<T>* ntemp = cursor->next;
                    cursor->prev = cursor->prev->prev;
                    cursor->prev->next = cursor;
                    cursor->next = ptemp;
                    ptemp->prev = cursor;
                    ptemp->next = ntemp;
                    ntemp->prev = ptemp;
                    return;
                }
            }
            else if (ch == 77) { // right
                if (cursor->next == nullptr) {
                    return;
                }
                else if (cursor->next == tail) {
                    Node<T>* ptemp = cursor->prev;
                    ptemp->next = tail;
                    tail->prev = ptemp;
                    tail->next = cursor;
                    cursor->prev = tail;
                    cursor->next = nullptr;
                    return;
                }
                else {
                    Node<T>* ptemp = cursor->prev;
                    Node<T>* ntemp = cursor->next;
                    cursor->next = ntemp->next;
                    ntemp->next->prev = cursor;
                    ptemp->next = ntemp;
                    ntemp->prev = ptemp;
                    ntemp->next = cursor;
                    cursor->prev = ntemp;
                    if (cursor->next == tail) {
                        cursor->next = tail;
                        tail->prev = cursor;
                    }
                    return;
                }
            }
        }
        else if (order == 8) { // backspace
            this->Erase();
            return;
        }
    }

    void Print() {
        if (head->next != nullptr) {
            Node<T>* temp = head->next;
            while (temp != nullptr) {
                cout << temp->data;
                temp = temp->next;
            }
            cout << endl;
        }
    }

    // --------- NEW: Persistence helpers ----------

    // Serialize list to a std::string (skipping the visual cursor node)
    string ToString() const {
        string out;
        Node<T>* temp = head->next;
        while (temp != nullptr) {
            if (temp == cursor) {
                temp = temp->next;
                continue;
            }
            out.push_back(static_cast<char>(temp->data));
            temp = temp->next;
        }
        return out;
    }

    // Clear all content nodes (keep head and cursor wiring intact)
    void ClearContent() {
        Node<T>* temp = head->next;
        while (temp && temp != cursor) {
            Node<T>* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
        head->next = cursor;
        cursor->prev = head;
        tail = head;
        size = 0;
    }

    // Load text into the list at cursor (replaces current content)
    void LoadFromString(const string& s) {
        ClearContent();
        for (char c : s) {
            InsertAtCursor(c);
        }
    }

    ~Linkedlist() {
        Node<T>* prev = head;
        Node<T>* curr = head->next;
        while (curr != nullptr) {
            delete prev;
            prev = curr;
            curr = curr->next;
        }
        delete prev;
    }
};

// ----------------- File I/O helpers -----------------

// Ensure file exists; if not, create empty.
void ensureFileExists(const string& path) {
    ifstream in(path, ios::in | ios::binary);
    if (!in.good()) {
        ofstream out(path, ios::out | ios::binary);
        // creates empty file
    }
}

// Read entire file to string
string readAll(const string& path) {
    ifstream in(path, ios::in | ios::binary);
    if (!in.good()) return {};
    string data;
    in.seekg(0, ios::end);
    data.resize(static_cast<size_t>(in.tellg()));
    in.seekg(0, ios::beg);
    if (!data.empty()) in.read(&data[0], data.size());
    return data;
}

// Write entire string to file (truncate)
void writeAll(const string& path, const string& data) {
    ofstream out(path, ios::out | ios::binary | ios::trunc);
    out.write(data.data(), static_cast<std::streamsize>(data.size()));
}

// ----------------- Main -----------------

int main() {
    // 1) Ask for filename (default: note.txt)
    string filename;
    cout << "Enter filename to edit (default: note.txt): ";
    getline(cin, filename);
    if (filename.empty()) filename = "note.txt";

    ensureFileExists(filename);

    // 2) Init editor and load existing file content
    Linkedlist<char> note;
    {
        string contents = readAll(filename);
        note.LoadFromString(contents);
    }

    // 3) Start UI loop
    cout << "Notepad Started – editing file: " << filename << "\n";
    note.Print();

    char ch = _getch();
    int order = ch;

    auto autosave = [&]() {
        writeAll(filename, note.ToString());
        };

    if (order == 27) { // ESC immediately
        cout << "\nNotepad Exited\n\n";
        return 0;
    }
    else {
        while (order != 27) {
            system("cls");
            bool changed = false;

            if (order == -32 || order == 8) {
                // Move or Backspace
                int beforeSizeAware = 0; // simple marker to force save on delete/move that changes text
                string before = note.ToString();

                note.Move(order);

                // Save only if content changed (moving cursor left/right doesn't change content)
                if (note.ToString() != before) changed = true;
                note.Print();
            }
            else if (order == 13) { // Enter
                note.InsertAtCursor('\n');
                changed = true;
                note.Print();
            }
            else {
                note.InsertAtCursor(ch);
                changed = true;
                note.Print();
            }

            if (changed) autosave(); // write every change

            ch = _getch();
            order = ch;
        }
        system("cls");
        // final save on exit
        writeAll(filename, note.ToString());
        cout << "\nNotepad Exited\n\n";
        return 0;
    }
}
