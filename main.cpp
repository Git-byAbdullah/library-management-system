#include <iostream>
#include <string>

using namespace std;

class Book {
public:
    int id;
    string book_title;
    string author;
    bool availability;

    Book() : id(0), book_title(""), author(""), availability(true) {}  
    
    Book(int book_id, string title, string auth) {
        id = book_id;
        book_title = title;
        author = auth;
        availability = true;
    }
};

class Library {
private:
    Book books[100];
    int book_count;
    int next_id;

public:
    Library() : book_count(0), next_id(101) {}

    void add_book(string title, string author) {
        if (book_count < 100) {
            books[book_count] = Book(next_id++, title, author);
            book_count++;
            cout << "Book Added Successfully. ID: " << books[book_count - 1].id << "\n";
        } else {
            cout << "Library capacity is full.\n";
        }
    }

    void display_allBooks() const {
        if (book_count == 0) {
            cout << "No books in the library.\n";
        } else {
            for (int i = 0; i < book_count; ++i) {
                string status = books[i].availability ? "Available" : "Borrowed";
                cout << "ID     : " << books[i].id << "\n";
                cout << "Title  : " << books[i].book_title << "\n";
                cout << "Author : " << books[i].author << "\n";
                cout << "Status : " << status << "\n";
                cout << "-------------------------\n";
            }
        }
    }

    void search_book(int target_id) const {
        for (int i = 0; i < book_count; ++i) {
            if (books[i].id == target_id) {
                string status = books[i].availability ? "Available" : "Borrowed";
                cout << "ID     : " << books[i].id << "\n";
                cout << "Title  : " << books[i].book_title << "\n";
                cout << "Author : " << books[i].author << "\n";
                cout << "Status : " << status << "\n";
                return;
            }
        }
        cout << "Book Not Found.\n";
    }

    void borrow_book(int target_id) {
        for (int i = 0; i < book_count; ++i) {
            if (books[i].id == target_id) {
                if (books[i].availability) {
                    books[i].availability = false;
                    cout << "Book Borrowed Successfully.\n";
                    return;
                } else {
                    cout << "Book is Already borrowed\n";
                    return;
                }
            }
        }
        cout << "Book Not Found.\n";
    }

    void return_book(int target_id) {
        for (int i = 0; i < book_count; ++i) {
            if (books[i].id == target_id) {
                if (!books[i].availability) {
                    books[i].availability = true;
                    cout << "Book Returned Successfully.\n";
                    return;
                } else {
                    cout << "Book is already Available.\n";
                    return;
                }
            }
        }
        cout << "Book Not Found.\n";
    }

    void delete_book(int target_id) {
        for (int i = 0; i < book_count; ++i) {
            if (books[i].id == target_id) {
                if (!books[i].availability) {
                    cout << "Cannot delete borrowed book\n";
                    return;
                }
                for (int j = i; j < book_count - 1; ++j) {
                    books[j] = books[j + 1];
                }
                book_count--;
                cout << "Book Deleted Successfully.\n";
                return;
            }
        }
        cout << "Book Not Found.\n";
    }
};

bool authenticateAdmin() {
    string password;
    cout << "Enter admin password: ";
    cin >> password;
    cin.ignore();

    if (password == "admin123") {
        cout << "Access granted.\n";
        return true;
    } else {
        cout << "Access denied.\n";
        return false;
    }
}

int main() {
    Library library;
    library.add_book("Jurassic Park", "Michael Crichton");
    library.add_book("The Lost World : A Novel", "Michael Crichton");

    int choice;
    string title, author;
    int target_id;

    while (true) {
        cout << "\n========== LIBRARY SYSTEM ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Exit\n";
        cout << "Enter your Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            if (authenticateAdmin()) {
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Author Name: ";
                getline(cin, author);
                library.add_book(title, author);
            }
        } else if (choice == 2) {
            library.display_allBooks();
        } else if (choice == 3) {
            cout << "Enter Book ID: ";
            if (!(cin >> target_id)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            cin.ignore();
            library.search_book(target_id);
        } else if (choice == 4) {
            cout << "Enter Book ID to borrow: ";
            if (!(cin >> target_id)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            cin.ignore();
            library.borrow_book(target_id);
        } else if (choice == 5) {
            cout << "Enter Book ID to return: ";
            if (!(cin >> target_id)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            cin.ignore();
            library.return_book(target_id);
        } else if (choice == 6) {
            if (authenticateAdmin()) {
                cout << "Enter Book ID to delete: ";
                if (!(cin >> target_id)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
                cin.ignore();
                library.delete_book(target_id);
            }
        } else if (choice == 7) {
            cout << "Exiting...............\n";
            break;
        } else {
            cout << "Invalid Choice\n";
        }
    }

    return 0;
}
