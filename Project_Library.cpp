#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// структура для зберігання інформації про книгу
struct Book {
    int id;        // унікальний ідентифікатор книги
    string title;  // назва книги
    string author; // автор книги
    int year;      // рік публікації книги
    string genre;  // жанр книги
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
            return; // завершуємо функцію, якщо книга з таким ID вже є
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
    for (int i = 0; i < bookCount;i++) { // цикл для виведення інформації про кожну книгу
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
    cout << "Book not found."
        << endl; // якщо книгу не знайдено, виводимо повідомлення
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

// Функція для редагування книг
void editBook(Book* books, int bookCount, int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) { // пошук книги за ID
            cout << "Enter new title: ";
            cin >> books[i].title; // оновлюємо назву книги
            cout << "Enter new author: ";
            cin >> books[i].author; // оновлюємо автора книги
            cout << "Enter new publication year: ";
            cin >> books[i].year; // оновлюємо рік публікації
            cout << "Enter new genre: ";
            cin >> books[i].genre; // оновлюємо жанр
            cout << "Book updated successfully!" << endl;
            return;
        }
    }
    cout << "Book not found." << endl; // якщо книга з таким ID не знайдена
}

// Функція для збереження книг у файли за жанрами
void saveToFile(Book* books, int bookCount) {
    for (int i = 0; i < bookCount; i++) {
        string filename = books[i].genre + ".txt"; // ім'я файлу — назва жанру
        ofstream outFile(filename, ios::app); // відкриваємо файл для запису
        if (outFile.is_open()) { // перевіряємо, чи файл відкрився
            outFile << books[i].id << endl
                << books[i].title << endl
                << books[i].author << endl
                << books[i].year << endl
                << books[i].genre << endl; // записуємо дані книги у файл
            outFile.close();                   // закриваємо файл
        }
    }
    cout << "Data saved to files." << endl; // повідомлення про успішне збереження
}

// функція для завантаження попередніх даних із файлів
void loadFromFile(Book*& books, int& bookCount) {
    string genreList[] = { "Fiction", "Non-Fiction", "Science",
                          "Fantasy" };       // список жанрів
    for (const string& genre : genreList) { // для кожного жанру
        ifstream inFile(genre + ".txt"); // відкриваємо відповідний файл
        if (inFile.is_open()) { // перевіряємо, чи файл відкрився
            while (!inFile.eof()) { // поки не кінець файлу
                Book newBook;
                inFile >> newBook.id;
                inFile >> newBook.title;
                inFile >> newBook.author;
                inFile >> newBook.year;
                inFile >> newBook.genre;

                // перевірка на наявність книги з таким ID
                int i;
                for (i = 0; i < bookCount; i++) {
                    if (books[i].id == newBook.id) { // якщо ID збігається, пропускаємо
                        break;
                    }
                }

                // додаємо книгу, якщо її ID унікальний
                if (!inFile.fail() &&
                    i == bookCount) { // якщо не було помилок при зчитуванні
                    Book* temp = new Book[bookCount + 1];
                    for (int j = 0; j < bookCount; j++) {
                        temp[j] = books[j]; // копіюємо наявні книги
                    }
                    temp[bookCount] = newBook; // додаємо нову книгу
                    delete[] books; // видаляємо старий масив
                    books = temp; // оновлюємо вказівник на новий масив
                    bookCount++; // збільшуємо лічильник книг
                }
            }
            inFile.close(); // закриваємо файл
        }
    }
}

// головна функція
int main() {
    Book* books = 0; // ініціалізуємо динамічний масив для зберігання книг
    int bookCount = 0; // лічильник кількості книг
    loadFromFile(books, bookCount);
    int id;
    while (true) {
        int choice;
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Delete Book by ID\n";
        cout << "5. Edit Book\n";
        cout << "6. Save Data to File\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            addBook(books, bookCount);
        }
        else if (choice == 2) {
            displayBooks(books, bookCount);
        }
        else if (choice == 3) {
            cout << "Enter book ID to search: ";
            cin >> id;
            searchBookById(books, bookCount, id);
        }
        else if (choice == 4) {
            cout << "Enter book ID to delete: ";
            cin >> id;
            deleteBookById(books, bookCount, id);
        }
        else if (choice == 5) {
            cout << "Enter book ID to edit: ";
            cin >> id;
            editBook(books, bookCount, id);
        }
        else if (choice == 6) {
            saveToFile(books, bookCount);
        }
        else if (choice == 7) {
            cout << "Exiting program." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
    saveToFile(books, bookCount); // збереження данних при виході з программи
    delete[] books; // очистка памяті
    return 0;
}
