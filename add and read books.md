#include <iostream>
#include <fstream>
#include <string>

void addBooks(const std::string& title, const std::string& author, const std::string& ISBN, int status) {
    std::ofstream outFile("books.csv", std::ios::app);
    
    if (outFile.is_open()) {
        outFile << title << "," << author << "," << ISBN << "," << (status ? "Available" : "Checked Out") << "\n";
        outFile.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}

void viewAllBooks() {
    std::ifstream inFile("books.csv");
    std::string line;

    // Check if the file is open
    if (inFile.is_open()) {
        std::cout << "List of Books:\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Title,Author,ISBN,Status\n"; // Header

        // Read each line and display
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }

        inFile.close(); // Close the file
    } else {
        std::cerr << "Error opening file! It may not exist." << std::endl;
    }
}

int main() {
    std::string title, author, ISBN;
    int status;

    // Example to add a book (optional, for demonstration purposes)
    // Uncomment these lines to add a book directly when running the program
    /*
    std::cout << "Enter book title: ";
    std::getline(std::cin, title);
    std::cout << "Enter author name: ";
    std::getline(std::cin, author);
    std::cout << "Enter ISBN: ";
    std::getline(std::cin, ISBN);
    std::cout << "Enter status (1 for Available, 0 for Checked Out): ";
    std::cin >> status;

    addBooks(title, author, ISBN, status);
    std */

    // View all books
    viewAllBooks();

    return 0;
}
