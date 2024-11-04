#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Book { //структура до книг
    int id;
    string title;
    string author;
    int year;
    string genre;
};

void addBook(Book*& books, int& bookCount) {
    Book newBook;
    cout << "Enter book ID: ";
    cin >> newBook.id;

    // перевірка на наявність книги з таким айді 
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == newBook.id) {
            cout << "Error: Book with this ID already exists.\n";
            return;  // виводим якщо книга є.
        }
    }
    cout << "Enter title (one word): ";
    cin >> newBook.title;
    cout << "Enter author (one word): ";
    cin >> newBook.author;
    cout << "Enter publication year: ";
    cin >> newBook.year;
    cout << "Enter genre (one word): ";
    cin >> newBook.genre;
    Book* temp = new Book[bookCount + 1];
    for (int i = 0; i < bookCount; i++) { // додавання новоъ книги
        temp[i] = books[i];
    }
    temp[bookCount] = newBook;
    delete[] books;
    books = temp;
    bookCount++;
    cout << "Book added successfully!" << endl;
}
//функція для відображення книг 
void displayBooks(Book* books, int bookCount) {
    if (bookCount == 0) {// перевірка на наявність книг ввцілому 
        cout << "No books available." << endl;
        return;
    }
    for (int i = 0; i < bookCount; i++) { // вивод книга на єкран 
        cout << "ID: " << books[i].id << ", Title: " << books[i].title
        << ", Author: " << books[i].author << ", Year: " << books[i].year
        << ", Genre: " << books[i].genre << endl;
    }
}
//функція для пошуку книг за айді
void searchBookById(Book* books, int bookCount, int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {// перевірка якщо айді співпадає вивести книгу за цим айді
            cout << "ID: " << books[i].id << ", Title: " << books[i].title
                << ", Author: " << books[i].author << ", Year: " << books[i].year
                << ", Genre: " << books[i].genre << endl;
            return;
        }
    }
    cout << "Book not found." << endl;
}

int main(){
    Book* books = 0;// динамічний масив для зберігання книг та його розмір
    int bookCount = 0;
}