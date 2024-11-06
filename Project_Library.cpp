#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// структура для зберігання інформації про книгу
struct Book {
    int id; // унікальний ідентифікатор книги
    string title; // назва книги
    string author; // автор книги
    int year; // рік публікації книги
    string genre; // жанр книги
};

// функція для додавання книги до колекції
void addBook(Book*& books, int& bookCount) {
    Book newBook; // створюємо новий екземпляр книги
    cout << "Enter book ID: ";
    cin >> newBook.id;

    // перевірка, чи існує книга з таким же ідентифікатором
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == newBook.id) { // якщо ідентифікатори збігаються
            cout << "Error: Book with this ID already exists.\n";
            return;  // завершуємо функцію, якщо книга з таким ID вже є
        }
    }

    // запитуємо дані для нової книги
    cout << "Enter title (one word): ";
    cin >> newBook.title;
    cout << "Enter author (one word): ";
    cin >> newBook.author;
    cout << "Enter publication year: ";
    cin >> newBook.year;
    cout << "Enter genre (one word): ";
    cin >> newBook.genre;

    // створюємо новий масив на одиницю більший для додавання нової книги
    Book* temp = new Book[bookCount + 1];
    for (int i = 0; i < bookCount; i++) { // копіюємо наявні книги в новий масив
        temp[i] = books[i];
    }

    temp[bookCount] = newBook; // додаємо нову книгу до кінця масиву
    delete[] books; // видаляємо старий масив
    books = temp; // оновлюємо вказівник на новий масив
    bookCount++; // збільшуємо лічильник книг
    cout << "Book added successfully!" << endl;
}

// функція для відображення списку книг
void displayBooks(Book* books, int bookCount) {
    if (bookCount == 0) { // перевірка, чи є взагалі книги в колекції
        cout << "No books available." << endl;
        return;
    }
    for (int i = 0; i < bookCount; i++) { // цикл для виведення інформації про кожну книгу
        cout << "ID: " << books[i].id << ", Title: " << books[i].title
            << ", Author: " << books[i].author << ", Year: " << books[i].year
            << ", Genre: " << books[i].genre << endl;
    }
}

// функція для пошуку книги за ідентифікатором
void searchBookById(Book* books, int bookCount, int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) { // якщо знайдено книгу з заданим ID, виводимо її дані
            cout << "ID: " << books[i].id << ", Title: " << books[i].title
                << ", Author: " << books[i].author << ", Year: " << books[i].year
                << ", Genre: " << books[i].genre << endl;
            return; // завершуємо функцію, якщо книга знайдена
        }
    }
    cout << "Book not found." << endl; // якщо книгу не знайдено, виводимо повідомлення
}

// функція для видалення книги за ідентифікатором
void deleteBookById(Book*& books, int& bookCount, int id) {
    int index = 0;
    for (int i = 0; i < bookCount; i++) { // пошук книги з відповідним ID
        if (books[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == 0) { // якщо книга не знайдена
        cout << "Book not found." << endl;
        return;
    }

    // створюємо новий масив меншого розміру для видалення книги
    Book* temp = new Book[bookCount - 1];
    for (int i = 0, j = 0; i < bookCount; i++) {
        if (i != index) { // копіюємо всі книги, окрім видаленої
            temp[j++] = books[i];
        }
    }
    delete[] books; // видаляємо старий масив
    books = temp; // оновлюємо вказівник на новий масив
    bookCount--; // зменшуємо лічильник книг
    cout << "Book deleted successfully!" << endl;
}

// Функция для редактирования книги
void editBook(Book* books, int bookCount, int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            cout << "Enter new title: ";
            cin << books[i].title;
            cout << "Enter new author: ";
            cin << books[i].author;
            cout << "Enter new publication year: ";
            cin >> books[i].year;
            cout << "Enter new genre: ";
            cin << books[i].genre;
            cout << "Book updated successfully!" << endl;
            return;
        }
    }
    cout << "Book not found." << endl;
}

// Функция для сохранения книг в файлы по жанрам
void saveToFile(Book* books, int bookCount) {
    for (int i = 0; i < bookCount; i++) {
        string filename = books[i].genre + ".txt";
        ofstream outFile(filename, ios::app);
        if (outFile.is_open()) {
            outFile << books[i].id << endl
                << books[i].title << endl
                << books[i].author << endl
                << books[i].year << endl
                << books[i].genre << endl;
            outFile.close();
        }
    }
    cout << "Data saved to files." << endl;
}

// головна функція
int main() {
    Book* books = 0; // ініціалізуємо динамічний масив для зберігання книг
    int bookCount = 0; // лічильник кількості книг

    // тут можна викликати функції для роботи з книгами
    return 0; // завершення програми
}
