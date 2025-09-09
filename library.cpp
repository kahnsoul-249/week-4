#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Lớp sách thường (book)
class Book {
protected:
    string title;
    string author;
    string isbn;
    bool available;
public:
    Book(string t = "", string a = "", string i = "") 
        : title(t), author(a), isbn(i), available(true) {}
    virtual ~Book() {}

    virtual void borrow() { // Hàm mượn sách (14 ngày cho sách thường)
        if (available) {
            available = false;
            cout << "[INFO] " << title << " has been borrowed for 14 days.\n";
        } else {
            cout << "[WARNING] " << title << " is currently not available.\n";
        }
    }

    virtual void returnBook() { // Hàm trả sách
        if (!available) {
            available = true;
            cout << "[INFO] " << title << " has been returned.\n";
        } else {
            cout << "[WARNING] " << title << " was not borrowed.\n";
        }
    }

    virtual void displayInfo() const { // Hiển thị thông tin sách
        cout << "----------------------------------\n";
        cout << "Title: " << title 
             << "\nAuthor: " << author 
             << "\nISBN: " << isbn 
             << "\nStatus: " << (available ? "Available" : "Borrowed") 
             << "\n----------------------------------\n";
    }

    bool isAvailable() const { return available; } // Kiểm tra sách còn có sẵn không
    string getTitle() const { return title; }      // Lấy tiêu đề
    string getISBN() const { return isbn; }        // Lấy ISBN
};

// Lớp dẫn xuất cho audiobook
class Audiobook : public Book {
private:
    int duration;        // Thời lượng 
    string narrator;     // narrator : người đọc
public:
    Audiobook(string t = "", string a = "", string i = "", int d = 0, string n = "")
        : Book(t, a, i), duration(d), narrator(n) {}

    void borrow() override { // Ghi đè: Mượn audiobook là 7 ngày ( có trong example)
        if (available) {
            available = false;
            cout << "[INFO] " << title << " (audiobook) has been borrowed for 7 days.\n";
        } else {
            cout << "[WARNING] " << title << " (audiobook) is currently not available.\n";
        }
    }

    void displayInfo() const override { // Hiển thị thông tin audiobook
        cout << "----------------------------------\n";
        cout << "Title: " << title 
             << "\nAuthor: " << author
             << "\nISBN: " << isbn 
             << "\nDuration: " << duration << " mins"
             << "\nNarrator: " << narrator
             << "\nStatus: " << (available ? "Available" : "Borrowed") 
             << "\n----------------------------------\n";
    }
};

// Lớp thành viên của thư viện
class Member {
private:
    string name;                  // Tên thành viên
    int id;                       // Mã thành viên
    vector<Book*> borrowedBooks;  // Danh sách sách đã mượn
public:
    Member(string n = "", int i = 0) : name(n), id(i) {}

    void borrowBook(Book* book) { // Mượn sách   ( 3 phần void của lớp member này em có tham khảo 1 ít qua LLM ạ)
        if (borrowedBooks.size() >= 3) {
            cout << "[ERROR] " << name << " cannot borrow more than 3 books.\n";
            return;
        }
        if (book->isAvailable()) {
            book->borrow();
            borrowedBooks.push_back(book);
        } else {
            cout << "[ERROR] This book is not available for borrowing.\n";
        }
    }

    void returnBook(Book* book) { // Trả sách
        for (size_t i = 0; i < borrowedBooks.size(); i++) {
            if (borrowedBooks[i]->getISBN() == book->getISBN()) {
                book->returnBook();
                borrowedBooks.erase(borrowedBooks.begin() + i);
                return;
            }
        }
        cout << "[ERROR] " << name << " did not borrow this book.\n";
    }

    void displayInfo() const { // Hiển thị thông tin thành viên
        cout << "========== MEMBER INFO ==========\n";
        cout << "Member Name: " << name << "\nID: " << id << endl;
        cout << "Borrowed Books: \n";
        if (borrowedBooks.empty()) {
            cout << "  (None)\n";
        } else {
            for (auto* b : borrowedBooks) {
                cout << "  - " << b->getTitle() << endl;
            }
        }
        cout << "================================\n";
    }
};

int main() {
    // Tạo sách thường và audiobook
    Book book1("C++ Inheritance", "Huynh Xuan Phung", "1092025");
    Audiobook ab1("C++ check LLM", "Huynh Xuan Phung", "1192025", 90, "Tai Huynh");

    // Tạo thành viên
    Member m1("Phong Giao Duc", 1);

    // Thử mượn sách
    m1.borrowBook(&book1);
    m1.borrowBook(&ab1);

    // Hiển thị thông tin sách
    book1.displayInfo();
    ab1.displayInfo();

    // Hiển thị thông tin thành viên
    m1.displayInfo();

    // Trả sách
    m1.returnBook(&book1);
    book1.displayInfo();

    return 0;
}
