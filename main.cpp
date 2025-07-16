#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX_NAME_LENGTH = 50;


struct Book {
    string title;
    string author;
    int isbn;
    bool available;
};

struct Student {
    int roll;
    string name;
    double balance;
};

unordered_map<int, Book> books; // isbn -> Book
unordered_map<int, Student> students; // roll -> Student

// File paths
const char* BOOKS_FILE = "books.txt";
const char* STUDENTS_FILE = "students.txt";

// Function prototypes for file management
void save_books_to_file(const char* filename);
void load_books_from_file(const char* filename);
void save_students_to_file(const char* filename);
void load_students_from_file(const char* filename);

// Function prototypes
void create_account();
void display(int roll);
void deposit_amount(int roll, double amount);
void issue_item(int roll);
void return_book(int roll);
void display_sorted();
Student* find_student(int roll);
Book* find_book(int isbn);
void add_book();
void edit_book();
void view_books();
void initialize_books();
void delete_book();
void search_book_by_author();


// Utility function to clear input buffer
void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // Load data from files
    load_books_from_file(BOOKS_FILE);
    load_students_from_file(STUDENTS_FILE);

    int option;
    bool is_admin;
    string password;
    while (true) {
        cout << "\nLogin as:\n1. Admin\n2. Student\n0. Exit\nChoice: ";
        if (!(cin >> option)) {
            cout << "Invalid input. Please enter a number.\n";
           // clear_input();
            continue;
        }
        if (option == 0) break;
        is_admin = (option == 1);
        cout << "Enter password: ";
        cin >> password;
        if (password == "password") {
            bool session_active = true;
            while (session_active) {
                if (is_admin) {
                    cout << "\nAdmin options:\n1. Add book\n2. Edit book\n3. View book status\n4. View enrolled students\n5. View student balance\n6. Delete book\n7. Search book by author\n0. Logout\nChoice: ";
                    if (!(cin >> option)) {
                        cout << "Invalid input. Please enter a number.\n";
                       // clear_input();
                        continue;
                    }
                    switch (option) {
                        case 1: add_book(); break;
                        case 2: edit_book(); break;
                        case 3: view_books(); break;
                        case 4: display_sorted(); break;
                        case 5: {
                            int roll; cout << "Enter student roll number: ";
                            if (!(cin >> roll)) { cout << "Invalid roll number.\n"; clear_input(); break; }
                            display(roll); break;
                        }
                        case 6: delete_book(); break;
                        case 7: search_book_by_author(); break;
                        case 0: session_active = false; break;
                        default: cout << "Invalid option.\n";
                    }
                } else {
                    int roll; cout << "Enter your roll number: ";
                    if (!(cin >> roll)) { cout << "Invalid roll number.\n"; clear_input(); continue; }
                    Student* s = find_student(roll);
                    if (!s) {
                        cout << "Student not found. Create an account? (1. Yes / 2. No): ";
                        if (!(cin >> option)) { cout << "Invalid input.\n"; clear_input(); continue; }
                        if (option == 1) create_account();
                        else session_active = false;
                    } else {
                        bool student_session = true;
                        while (student_session) {
                            cout << "\nStudent options:\n1. View balance\n2. Deposit amount\n3. Issue item\n4. Return book\n0. Logout\nChoice: ";
                            if (!(cin >> option)) { cout << "Invalid input.\n"; clear_input(); continue; }
                            switch (option) {
                                case 1: display(roll); break;
                                case 2: {
                                    double amount; cout << "Enter the amount to deposit: ";
                                    if (!(cin >> amount)) { cout << "Invalid amount.\n"; clear_input(); break; }
                                    deposit_amount(roll, amount); break;
                                }
                                case 3: issue_item(roll); break;
                                case 4: return_book(roll); break;
                                case 0: student_session = false; break;
                                default: cout << "Invalid option.\n";
                            }
                        }
                        session_active = false;
                    }
                }
            }
        } else {
            cout << "Incorrect password.\n";
        }
    }

    // Save data to files before exit
    save_books_to_file(BOOKS_FILE);
    save_students_to_file(STUDENTS_FILE);
    cout << "Data saved. Exiting program.\n";
    return 0;
}

// Not used anymore, replaced by file loading
void initialize_books() {}
// Save all books to file
void save_books_to_file(const char* filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Error: Could not open books file for writing." << endl;
        return;
    }
    for (const auto& pair : books) {
        const Book& b = pair.second;
        fout << b.title << ',' << b.author << ',' << b.isbn << ',' << b.available << '\n';
    }
    fout.close();
}

// Load all books from file
void load_books_from_file(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Warning: Books file not found. Starting with empty library." << endl;
        return;
    }
    books.clear();
    string line;
    while (getline(fin, line)) {
        Book b;
        int avail = 1;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;
        b.title = line.substr(0, pos1);
        b.author = line.substr(pos1 + 1, pos2 - pos1 - 1);
        b.isbn = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        avail = stoi(line.substr(pos3 + 1));
        b.available = avail;
        books[b.isbn] = b;
    }
    fin.close();
}

// Save all students to file
void save_students_to_file(const char* filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Error: Could not open students file for writing." << endl;
        return;
    }
    for (const auto& pair : students) {
        const Student& s = pair.second;
        fout << s.roll << ',' << s.name << ',' << s.balance << '\n';
    }
    fout.close();
}

// Load all students from file
void load_students_from_file(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Warning: Students file not found. Starting with no students." << endl;
        return;
    }
    students.clear();
    string line;
    while (getline(fin, line)) {
        Student s;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;
        s.roll = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.balance = stod(line.substr(pos2 + 1));
        students[s.roll] = s;
    }
    fin.close();
}

void create_account() {
    int roll; cout << "Enter roll number (BBRRRR format): ";
    if (!(cin >> roll)) { cout << "Invalid roll number.\n"; clear_input(); return; }
    if (find_student(roll)) { cout << "Account already exists for this roll number.\nOperation failed: Account not created.\n"; return; }
    Student s;
    s.roll = roll;
    cout << "Enter student name: ";
    cin.ignore(); getline(cin, s.name);
    double initial_deposit; cout << "Enter initial deposit amount ($50 minimum): ";
    if (!(cin >> initial_deposit)) { cout << "Invalid amount.\n"; clear_input(); return; }
    if (initial_deposit < 50) { cout << "Initial deposit must be at least $50.\nOperation failed: Account not created.\n"; return; }
    s.balance = initial_deposit - 20 - 30;
    students[s.roll] = s;
    cout << "Account created successfully!\n";
}

Student* find_student(int roll) {
    auto it = students.find(roll);
    if (it != students.end()) return &(it->second);
    return nullptr;
}

Book* find_book(int isbn) {
    auto it = books.find(isbn);
    if (it != books.end()) return &(it->second);
    return nullptr;
}

void display(int roll) {
    Student* s = find_student(roll);
    if (!s) { cout << "Student not found.\nOperation failed: No details to display.\n"; return; }
    cout << "Roll No: " << s->roll << endl;
    cout << "Name: " << s->name << endl;
    cout << "Balance: $" << fixed << setprecision(2) << s->balance << endl;
}

void deposit_amount(int roll, double amount) {
    Student* s = find_student(roll);
    if (!s) { cout << "Student not found.\nOperation failed: Deposit not completed.\n"; return; }
    s->balance += amount;
    cout << "New balance: $" << fixed << setprecision(2) << s->balance << endl;
    cout << "Deposit successful!\n";
}

void issue_item(int roll) {
    Student* s = find_student(roll);
    if (!s) { cout << "Student not found.\nOperation failed: Cannot issue book.\n"; return; }
    vector<Book*> available_books;
    for (auto& pair : books) {
        if (pair.second.available) available_books.push_back(&pair.second);
    }
    if (available_books.empty()) { cout << "No books available.\nOperation failed: No book issued.\n"; return; }
    cout << "Available books:\n";
    for (size_t i = 0; i < available_books.size(); ++i) {
        cout << (i+1) << ". " << available_books[i]->title << " by " << available_books[i]->author << " (ISBN: " << available_books[i]->isbn << ")\n";
    }
    int choice; cout << "Enter the number of the book you want to issue (0 to cancel): ";
    if (!(cin >> choice)) { cout << "Invalid choice.\n"; clear_input(); return; }
    if (choice == 0) { cout << "Operation cancelled.\n"; return; }
    if (choice < 1 || choice > (int)available_books.size() || !available_books[choice-1]->available || s->balance < 2) {
        cout << "Cannot issue the book. Insufficient balance or book is unavailable.\nOperation failed: No book issued.\n"; return;
    }
    available_books[choice-1]->available = false;
    s->balance -= 2;
    cout << "Book issued successfully. New balance: $" << fixed << setprecision(2) << s->balance << endl;
}

void return_book(int roll) {
    Student* s = find_student(roll);
    if (!s) { cout << "Student not found.\nOperation failed: Cannot return book.\n"; return; }
    vector<Book*> issued_books;
    for (auto& pair : books) {
        if (!pair.second.available) issued_books.push_back(&pair.second);
    }
    if (issued_books.empty()) { cout << "No books are currently issued.\nOperation failed: No book returned.\n"; return; }
    cout << "Books currently issued (not available):\n";
    for (size_t i = 0; i < issued_books.size(); ++i) {
        cout << (i+1) << ". " << issued_books[i]->title << " by " << issued_books[i]->author << " (ISBN: " << issued_books[i]->isbn << ")\n";
    }
    int choice; cout << "Enter the number of the book you want to return (0 to cancel): ";
    if (!(cin >> choice)) { cout << "Invalid choice.\n"; clear_input(); return; }
    if (choice == 0) { cout << "Operation cancelled.\n"; return; }
    if (choice < 1 || choice > (int)issued_books.size() || issued_books[choice-1]->available) {
        cout << "Invalid choice or book is already available.\nOperation failed: No book returned.\n"; return;
    }
    issued_books[choice-1]->available = true;
    cout << "Book returned successfully.\n";
}

void display_sorted() {
    if (students.empty()) { cout << "No students found.\n"; return; }
    vector<Student> arr;
    for (const auto& pair : students) arr.push_back(pair.second);
    sort(arr.begin(), arr.end(), [](const Student& a, const Student& b) { return a.roll < b.roll; });
    for (const auto& s : arr) {
        cout << s.roll << " - " << s.name << " - Balance: $" << fixed << setprecision(2) << s.balance << endl;
    }
}

void add_book() {
    Book b;
    cout << "Enter book title: ";
    cin.ignore(); getline(cin, b.title);
    cout << "Enter book author: ";
    getline(cin, b.author);
    cout << "Enter book ISBN: ";
    if (!(cin >> b.isbn)) { cout << "Invalid ISBN.\n"; clear_input(); return; }
    if (find_book(b.isbn)) { cout << "A book with this ISBN already exists.\nOperation failed: Book not added.\n"; return; }
    b.available = true;
    books[b.isbn] = b;
    cout << "Book added successfully!\n";
}

void edit_book() {
    int isbn; cout << "Enter book ISBN to edit: ";
    if (!(cin >> isbn)) { cout << "Invalid ISBN.\n"; clear_input(); return; }
    Book* b = find_book(isbn);
    if (!b) { cout << "Book not found.\nOperation failed: No changes made.\n"; return; }
    cout << "Current book title: " << b->title << endl;
    cout << "Enter new book title: ";
    cin.ignore(); getline(cin, b->title);
    cout << "Current book author: " << b->author << endl;
    cout << "Enter new book author: ";
    getline(cin, b->author);
    cout << "Book details updated.\n";
}

void view_books() {
    if (books.empty()) { cout << "No books found in the library.\n"; return; }
    for (const auto& pair : books) {
        const Book& b = pair.second;
        cout << "Title: " << b.title << endl;
        cout << "Author: " << b.author << endl;
        cout << "ISBN: " << b.isbn << endl;
        cout << "Available: " << (b.available ? "Yes" : "No") << endl;
        cout << "-----------Book Listed------------\n";
    }
}

void delete_book() {
    int isbn; cout << "Enter book ISBN to delete: ";
    if (!(cin >> isbn)) { cout << "Invalid ISBN.\n"; clear_input(); return; }
    if (books.erase(isbn)) {
        cout << "Book deleted successfully.\n";
    } else {
        cout << "Book not found.\nOperation failed: No book deleted.\n";
    }
}

void search_book_by_author() {
    string author;
    cout << "Enter author name to search: ";
    cin.ignore();
    getline(cin, author);
    bool found = false;
    for (const auto& pair : books) {
        const Book& b = pair.second;
        if (b.author == author) {
            cout << "Title: " << b.title << ", ISBN: " << b.isbn << ", Available: " << (b.available ? "Yes" : "No") << endl;
            found = true;
        }
    }
    if (!found) cout << "No books found by this author.\n";
}
