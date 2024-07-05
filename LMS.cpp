#include <iostream>
#include <string>
#include <limits>
#include <stack>
#include <iomanip>
#include <vector>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;
    string issuedTo;

    Book(int id, string title, string author)
        : id(id), title(title), author(author), isIssued(false), issuedTo("None") {}
};

class Library {
private:
    vector<Book> books;
    stack<Book> issuedBooks;

public:
    void addBook(int id, string title, string author) {
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].id == id) {
                cout << "Book with ID " << id << " already exists. Please choose a different ID." << endl;
                return;
            }
        }

        books.push_back(Book(id, title, author));
        cout << "Book added successfully!" << endl;
    }

    void searchBookByID(int id) {
        bool found = false;
        printLine();
        cout << left << "| " << setw(8) << "ID" << " | " << setw(28) << "Title" << " | " << setw(28) << "Author" << " | " << setw(13) << "Status" << " | " << setw(28) << "Issued To" << " |" << endl;
        printLine();
        for (size_t i = 0; i < books.size(); ++i) {
            const Book& book = books[i];
            if (book.id == id) {
                cout << left << "| " << setw(8) << book.id << " | " << setw(28) << book.title << " | " << setw(28) << book.author << " | " << setw(13) << (book.isIssued ? "Issued" : "Available") << " | " << setw(28) << (book.isIssued ? book.issuedTo : "None") << " |" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found!" << endl;
        } else {
            printLine();
        }
    }

    void searchBookByTitle(string title) {
        bool found = false;
        printLine();
        cout << left << "| " << setw(8) << "ID" << " | " << setw(28) << "Title" << " | " << setw(28) << "Author" << " | " << setw(13) << "Status" << " | " << setw(28) << "Issued To" << " |" << endl;
        printLine();
        for (size_t i = 0; i < books.size(); ++i) {
            const Book& book = books[i];
            if (book.title == title) {
                cout << left << "| " << setw(8) << book.id << " | " << setw(28) << book.title << " | " << setw(28) << book.author << " | " << setw(13) << (book.isIssued ? "Issued" : "Available") << " | " << setw(28) << (book.isIssued ? book.issuedTo : "None") << " |" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found!" << endl;
        } else {
            printLine();
        }
    }

    void issueBook(int id, string student) {
        for (size_t i = 0; i < books.size(); ++i) {
            Book& book = books[i];
            if (book.id == id) {
                if (book.isIssued) {
                    cout << "Book already issued to " << book.issuedTo << "!" << endl;
                    return;
                } else {
                    book.isIssued = true;
                    book.issuedTo = student;
                    issuedBooks.push(book);
                    cout << "Book issued to " << student << endl;
                    return;
                }
            }
        }
        cout << "Book not available for issue!" << endl;
    }

    void returnBook(int id) {
        for (size_t i = 0; i < books.size(); ++i) {
            Book& book = books[i];
            if (book.id == id && book.isIssued) {
                book.isIssued = false;
                book.issuedTo = "None";
                cout << "Book returned successfully!" << endl;
                return;
            }
        }
        cout << "Book not found or not issued!" << endl;
    }

    void listAllBooks() {
        printLine();
        cout << left << "| " << setw(8) << "ID" << " | " << setw(28) << "Title" << " | " << setw(28) << "Author" << " | " << setw(13) << "Status" << " | " << setw(28) << "Issued To" << " |" << endl;
        printLine();
        for (size_t i = 0; i < books.size(); ++i) {
            const Book& book = books[i];
            cout << left << "| " << setw(8) << book.id << " | " << setw(28) << book.title << " | " << setw(28) << book.author << " | " << setw(13) << (book.isIssued ? "Issued" : "Available") << " | " << setw(28) << (book.isIssued ? book.issuedTo : "None") << " |" << endl;
        }
        printLine();
    }

    void deleteBook(int id) {
        for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                books.erase(it);
                cout << "Book deleted successfully!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void printLine() const {
        cout << "+----------+------------------------------+------------------------------+---------------+------------------------------+" << endl;
    }
};

int getValidIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    Library lib;
    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. List All Books\n";
        cout << "7. Delete Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidIntInput("");

        int id;
        string title, author, student;

        switch (choice) {
        case 1:
            id = getValidIntInput("Enter book ID: ");
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            lib.addBook(id, title, author);
            break;
        case 2:
            id = getValidIntInput("Enter book ID to search: ");
            lib.searchBookByID(id);
            break;
        case 3:
            cout << "Enter book title to search: ";
            getline(cin, title);
            lib.searchBookByTitle(title);
            break;
        case 4:
            id = getValidIntInput("Enter book ID to issue: ");
            cout << "Enter student name: ";
            getline(cin, student);
            lib.issueBook(id, student);
            break;
        case 5:
            id = getValidIntInput("Enter book ID to return: ");
            lib.returnBook(id);
            break;
        case 6:
            lib.listAllBooks();
            break;
        case 7:
            id = getValidIntInput("Enter book ID to delete: ");
            lib.deleteBook(id);
            break;
        case 8:
            cout << "Exiting the system..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}

