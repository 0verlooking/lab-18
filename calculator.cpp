#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Book {
public:
    std::string title;
    std::string author;
    int year;

    Book(const std::string& t, const std::string& a, int y)
        : title(t), author(a), year(y) {}
};

class Library {
public:
    std::vector<std::shared_ptr<Book>> books;

    void addBook(const std::shared_ptr<Book>& book) {
        books.push_back(book);
    }

    std::shared_ptr<Book> findBookByTitle(const std::string& title) {
        auto it = std::find_if(books.begin(), books.end(),
        [&title](const std::shared_ptr<Book>& book) {
            return book->title == title;
        });

        return (it != books.end()) ? *it : nullptr;
    }

    std::vector<std::shared_ptr<Book>> findBooksByAuthor(const std::string& author) {
        std::vector<std::shared_ptr<Book>> result;
        for (const auto& book : books) {
            if (book->author == author) {
                result.push_back(book);
            }
        }
        return result;
    }

    std::vector<std::shared_ptr<Book>> findBooksByYear(int year) {
        std::vector<std::shared_ptr<Book>> result;
        for (const auto& book : books) {
            if (book->year == year) {
                result.push_back(book);
            }
        }
        return result;
    }
};

int main() {
    Library library;

    auto book1 = std::make_shared<Book>("Title1", "Author1", 2001);
    auto book2 = std::make_shared<Book>("Title2", "Author2", 2002);

    library.addBook(book1);
    library.addBook(book2);

    auto foundBook = library.findBookByTitle("Title1");
    if (foundBook) {
        std::cout << "Found book: " << foundBook->title << ", " << foundBook->author << ", " << foundBook->year << "\n";
    }

    auto booksByAuthor = library.findBooksByAuthor("Author2");
    for (const auto& book : booksByAuthor) {
        std::cout << "Book by Author2: " << book->title << ", " << book->year << "\n";
    }

    auto booksByYear = library.findBooksByYear(2002);
    for (const auto& book : booksByYear) {
        std::cout << "Book from year 2002: " << book->title << ", " << book->author << "\n";
    }

    return 0;
}