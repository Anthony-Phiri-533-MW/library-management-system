#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
class Staff{
    private:
        string password;
    public:
        string username;
        void createStaff(const string& username, const string& password);
        bool isValidPassword(const string& password);
        void setPassword(string password){
            this->password=password;
        }

        string getPassword(){ return password;}

};

class Member{
    public:
        string name;
        string membershipID;
        string phoneNumber;
        string email;
        //string membershipID;

        void registerMember(const string& name, const string& membershipID, const std::string& phoneNumber, const std::string& email );
        void viewAllMembers();
        void memberHistory(const string& name);
        
};

class Book{
    public:
        string ISBN;
        string author;
        string title;
        int status;

        void addBooks(const string& title, const string& author, const string& ISBN, int status);
        void viewAllBooks();
        //void returnBook();
        void changeStatus(const string& ISBN);
        void searchBookByTitle(const string& title);
        void searchBookByISBN(const string& ISBN);
        void searchBookByAuthor(const string& author);

};

bool Staff :: isValidPassword(const string& password) {
    // Check for minimum length
    if (password.length() < 8) {
        return false;
    }

    bool hasUppercase = false;
    bool hasNumber = false;

    // Iterate through each character in the password
    for (char ch : password) {
        if (isupper(ch)) {
            hasUppercase = true;
        } else if (isdigit(ch)) {
            hasNumber = true;
        }
        
        // If both conditions are met, no need to check further
        if (hasUppercase && hasNumber) {
            return true;
        }
    }

    return false; // Return false if conditions aren't met
}

void writeToFile(const string& username, const string& password) {
    // Open the file in append mode
    ofstream outFile("staff.csv", ios::app);
    
    // Check if the file is open
    if (outFile.is_open()) {
        // Write the username and password to the file
        outFile << username << "," << password << "\n";
        outFile.close(); // Close the file
    } else {
        cerr << "Error opening file!" << endl;
    }
}

void Staff :: createStaff(const string& username, const string& password) {
    // Call the write function to append details to the CSV file
    writeToFile(username, password);
}

void writeMemberToFile(const std::string& name, const std::string& membershipID, const std::string& phoneNumber, const std::string& email) {
    // Open the file in append mode
    std::ofstream outFile("members.csv", std::ios::app);
    
    // Check if the file is open
    if (outFile.is_open()) {
        // Write member details to the file
        outFile << name << "," << membershipID << "," << phoneNumber << "," << email << "\n";
        outFile.close(); // Close the file
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}

void Member :: registerMember(const std::string& name, const std::string& membershipID, const std::string& phoneNumber, const std::string& email) {
    // Call the write function to append member details to the CSV file
    writeMemberToFile(name, membershipID, phoneNumber, email);
}

void Member :: viewAllMembers() {
    std::ifstream inFile("members.csv");
    std::string line;

    // Check if the file is open
    if (inFile.is_open()) {
        std::cout << "Member Details:\n";
        std::cout << "-----------------------------------------\n";
        
        // Read each line and display
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }

        inFile.close(); // Close the file
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}

void recordBorrowedBook(const std::string& personName, const std::string& bookTitle, int returned) {
    // Use the person's name as the filename (with .csv extension)
    std::string fileName = personName + ".csv";
    
    // Open the file in append mode
    std::ofstream outFile(fileName, std::ios::app);
    
    // Check if the file is open
    if (outFile.is_open()) {
        // Write the book title and returned status to the file
        outFile << bookTitle << "," << (returned ? "Returned" : "Not Returned") << "\n";
        outFile.close(); // Close the file
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}

void Member :: memberHistory(const std::string& name) {
    std::string fileName = name + ".csv";
    std::ifstream inFile(fileName);
    std::string line;
    // Check if the file is open
    if (inFile.is_open()) {
        std::cout << "Borrowing History for " << name << ":\n";
        std::cout << "-----------------------------------------\n";
        
        // Read each line and display
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }

        inFile.close(); // Close the file
    } else {
        std::cerr << "Error opening file for " << name << ". It may not exist." << std::endl;
    }
}

void Book :: addBooks(const std::string& title, const std::string& author, const std::string& ISBN, int status) {
    // Open the file in append mode
    std::ofstream outFile("books.csv", std::ios::app);
    
    // Check if the file is open
    if (outFile.is_open()) {
        // Write book details to the file
        outFile <<"\n" << title << "," << author << "," << ISBN << "," << status  << "\n";
        outFile.close(); // Close the file
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}

void Book :: viewAllBooks() {
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


void Book :: changeStatus(const std::string& ISBN) {
    std::ifstream inFile("books.csv");
    std::vector<std::string> lines;
    std::string line;

    if (inFile.is_open()) {
        bool found = false;

        while (std::getline(inFile, line)) {
            std::istringstream ss(line);
            std::string title, author, isbn, statusStr;
            std::getline(ss, title, ',');
            std::getline(ss, author, ',');
            std::getline(ss, isbn, ',');
            std::getline(ss, statusStr, ',');
             if (isbn == ISBN) {
                // Toggle the status
                int status = (statusStr == "1") ? 0 : 1; // 1 becomes 0, and 0 becomes 1
                statusStr = std::to_string(status);
                found = true;
            }

            // Rebuild the line
            lines.push_back(title + "," + author + "," + isbn + "," + statusStr);
        }

        inFile.close(); // Close the input file

        // Rewrite the updated data back to the file
        std::ofstream outFile("books.csv");
        for (const auto& updatedLine : lines) {
            outFile << updatedLine << "\n";
        }
        outFile.close(); // Close the output file

         if (found) {
            std::cout << "Status changed successfully for book with ISBN: " << ISBN << std::endl;
        } else {
            std::cout << "No book found with ISBN: " << ISBN << std::endl;
        }
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}

void Book :: searchBookByTitle(const std::string& title) {
    std::ifstream inFile("books.csv");
    std::string line;
    bool found = false;

    if (inFile.is_open()) {
        std::cout << "Searching for books with title: " << title << "\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Title,Author,ISBN,Status\n"; // Header

        while (std::getline(inFile, line)) {
            if (line.find(title) != std::string::npos) { // Check if title is in the line
                std::cout << line << std::endl;
                found = true;
            }
        }

        inFile.close();
        
        if (!found) {
            std::cout << "No books found with title: " << title << std::endl;
        }
    } else {
        std::cerr << "Error opening file! It may not exist." << std::endl;
    }
}

void Book :: searchBookByISBN(const std::string& ISBN) {
    std::ifstream inFile("books.csv");
    std::string line;
    bool found = false;

    if (inFile.is_open()) {
        std::cout << "Searching for book with ISBN: " << ISBN << "\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Title,Author,ISBN,Status\n"; // Header

        while (std::getline(inFile, line)) {
            if (line.find(ISBN) != std::string::npos) { // Check if ISBN is in the line
                std::cout << line << std::endl;
                found = true;
            }
        }

        inFile.close();

        if (!found) {
            std::cout << "No books found with ISBN: " << ISBN << std::endl;
        }
    } else {
        std::cerr << "Error opening file! It may not exist." << std::endl;
    }
}

void Book :: searchBookByAuthor(const std::string& author) {
    std::ifstream inFile("books.csv");
    std::string line;
    bool found = false;

    if (inFile.is_open()) {
        std::cout << "Searching for books by author: " << author << "\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Title,Author,ISBN,Status\n"; // Header

        while (std::getline(inFile, line)) {
            if (line.find(author) != std::string::npos) { // Check if author is in the line
                std::cout << line << std::endl;
                found = true;
            }
        }

        inFile.close();

        if (!found) {
            std::cout << "No books found by author: " << author << std::endl;
        }
    } else {
        std::cerr << "Error opening file! It may not exist." << std::endl;
    }
}

bool stafflogin(const string &username, const string &password)
{
    ifstream file("staff.csv");
    if (!file)
    {
        cerr << "Error opening file." << endl;
        return false;
    }

    string line, fileUsername, filePassword;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, fileUsername, ',');
        getline(ss, filePassword, ',');

        if (username == fileUsername && password == filePassword)
        {
            return true;
        }
    }

    return false;
}

bool memberlogin(const string &name, const string &membershipId)
{
    ifstream file("members.csv");
    if (!file)
    {
        cerr << "Error opening file." << endl;
        return false;
    }

    string line, fileName, fileMembershipId;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, fileName, ',');
        getline(ss, fileMembershipId, ',');

        if (name == fileName && membershipId == fileMembershipId)
        {
            return true;
        }
    }

    return false;
}

void staffMenu(){
    cout<<"\tSelect task to perform"<<endl;
    cout<<"\n";
    cout<<"\t1.Register a new member\n\t2.AddBooks\n\t3.view all books\n\t4.view all members\n\tcheck member history"<<endl;

    int option;
    cin>>option;
    cin.ignore();

    switch (option) {
        case 1:
        {
            Member mObj1;
            // Get user input for member registration
            std::cout << "\tEnter member name: ";
            
            std::getline(std::cin, mObj1.name);
            std::cout << "\tEnter membership ID: ";
            cin.ignore();
            std::getline(std::cin, mObj1.membershipID);
            std::cout << "\tEnter phone number: ";
            cin.ignore();
            std::getline(std::cin, mObj1.phoneNumber);
            std::cout << "\tEnter email: ";
            cin.ignore();
            std::getline(std::cin, mObj1.email);

            // Register the member
            mObj1.registerMember(mObj1.name, mObj1.membershipID, mObj1.phoneNumber, mObj1.email);
            std::cout << "\tMember details added successfully.\n";
        
            break;
        }
        case 2:
        {
            Book bObj1;
            std::string title, author, ISBN;
            int status;
            
            std::cout << "Enter book title: ";
            std::getline(std::cin, bObj1.title);
            std::cout << "Enter author name: ";
            std::getline(std::cin, bObj1.author);
            std::cout << "Enter ISBN: ";
            std::getline(std::cin, bObj1.ISBN);
            std::cout << "Enter status (1 for Available, 0 for Checked Out): ";
            std::cin >> bObj1.status;

            bObj1.addBooks(bObj1.title, bObj1.author, bObj1.ISBN, bObj1.status);
            
            cout<<"Book added sucessfully"<<endl;
            // View all books
            //bObj1.viewAllBooks();
            break;
        }
        case 3:
        {
            Book bObj;
            bObj.viewAllBooks();
            break;
        }
        case 4:
        {
            Member mObj2;

            mObj2.viewAllMembers();
            break;
        }
    }
}

void memberMenu(){
    cout<<"\tSelect task to perform"<<endl;
    cout<<"\n";
    cout<<"\t1.Borrow a Book\n\t2.Return a book\n\t3.view all books\n\t4.Search for a book\n\t5.check history"<<endl;

    int option;
    cin>>option;
    cin.ignore();

    switch(option){
        case 1:
        {
            Book bObj5;
            Member mObj7;
            cout<<"Enter the ISBN of the Book You are interested to borrow"<<endl;
            cin>>bObj5.ISBN;

            cout<<"Enter the book titile"<<endl;
            cin.ignore();
            std::getline(std::cin, bObj5.title);

            cout<<"Enter your name"<<endl;
            //cin.ignore();
            std::getline(std::cin, mObj7.name);

            bObj5.status=0;

            bObj5.changeStatus(bObj5.ISBN);
            recordBorrowedBook(mObj7.name,bObj5.title,bObj5.status);

            break;
        }
        case 2:
        {
            Book bObj6;
            Member mObj8;
            cout<<"Enter the ISBN of the Book You are want to return"<<endl;
            cin>>bObj6.ISBN;

            cout<<"Enter the book titile"<<endl;
            cin.ignore();
            std::getline(std::cin, bObj6.title);

            cout<<"Enter your name"<<endl;
            //cin.ignore();
            std::getline(std::cin, mObj8.name);

            bObj6.status=1;

            bObj6.changeStatus(bObj6.ISBN);
            recordBorrowedBook(mObj8.name,bObj6.title,bObj6.status);

            break;
        }
        case 3:
        {
            Book bObj3;
            bObj3.viewAllBooks();
            break;
        }
        case 4:
        {
            Book bObj4;
            cout<<"\n\tSelect the criteria to be used for searching"<<endl;
            cout<<"\n\t1.By Author\n\t2.By ISBN\n\t3.By Title"<<endl;

            int option;

            cin>>option;

            if(option == 1){
                cin.ignore();
                cout<<"\tEnter the authors name"<<endl;

                std::getline(std::cin, bObj4.author);
                bObj4.searchBookByAuthor(bObj4.author);
            }else if(option == 2){
                cin.ignore();
                cout<<"\tEnter the book's ISBN"<<endl;

                std::getline(std::cin, bObj4.ISBN);
                bObj4.searchBookByAuthor(bObj4.ISBN);
            }else if(option == 3){
                cin.ignore();
                cout<<"\tEnter the book's title"<<endl;

                std::getline(std::cin, bObj4.title);
                bObj4.searchBookByAuthor(bObj4.title);
            }else{
                cout<<"Invalid option selected"<<endl;
            }
            break;
        }
        case 5:
        {
            Member mObj9;
            cout<<"Enter your name"<<endl;
            cin>>mObj9.name;

            mObj9.memberHistory(mObj9.name);
            break;
        }
    }

}

void mainMenu(){
    cout<<"\tLibrary"<<endl;

    cout<<"\n"<<endl;

    cout<<"\tLogin"<<endl;

    cout<<"\t1.Staff\n\t2.Member\n\t3.exit"<<endl;

    int option;

    cin>>option;

    switch(option){
        case 1:
        {
            cout<<"enter your username"<<endl;
            Staff sObj;
            cin.ignore();
            cin>>sObj.username;
            cout<<"enter your password"<<endl;
            string password;
            cin.ignore();
            cin>>password;

            sObj.setPassword(password);

            if (stafflogin(sObj.username, sObj.getPassword())){
                cout<<"login Successful"<<endl;
                staffMenu();
            }else{
                cout<<"login failed"<<endl;
            }
            break;
        }
        case 2:
        {
            cout<<"Enter your name\n Use hyphens instead of spaces"<<endl;
            Member mObj;
            cin.ignore();
            cin>>mObj.name;

            cout<<"Enter your Membership Id"<<endl;
            cin.ignore();
            cin>>mObj.membershipID;

            if (memberlogin(mObj.name, mObj.membershipID)){
                cout<<"Login Successful"<<endl;
                memberMenu();
            }else{
                cout<<"Login Unsuccessful";
            }
            break;
        }
        case 3:
            break;
    }
}

int main(){
    mainMenu();
}