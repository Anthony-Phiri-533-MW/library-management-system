#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

class Staff
{
protected:
    string name;
    string password;

public:
    void setName(string name)
    {
        this->name = name;
    }

    void setPassword(string password)
    {
        this->password = password;
    }

    string getName()
    {
        return name;
    }

    string getPassword()
    {
        return password;
    }
};

class Book
{
private:
    string title;
    string author;
    int ISBN;
    bool status;

public:
    void setTitle(string title)
    {
        this->title = title;
    }

    void setAuthor(string author)
    {
        this->author = author;
    }

    void setISBN(int ISBN)
    {
        this->ISBN = ISBN;
    }

    void setStauts(bool status)
    {
        this->status = status;
    }
};

class Student : public Staff
{
private:
    int phone;
    string email;

public:
    void setPhone(int phone)
    {
        this->phone = phone;
    }

    void setEmail(string email)
    {
        this->email = email;
    }

    int getPhone()
    {
        return phone;
    }

    string getEmail()
    {
        return email;
    }
};

bool validatePassword(const string& password) {
    if (password.length() < 8) {
        return false;
    }
    
    bool hasUppercase = false;
    bool hasNumber = false;
    
    for (char c : password) {
        if (isupper(c)) {
            hasUppercase = true;
        }
        if (isdigit(c)) {
            hasNumber = true;
        }
    }
    
    return hasUppercase && hasNumber;
}

bool memberlogin(const string &username, const string &password)
{
    ifstream file("members.csv");
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

void writeBooksToFile(const string& title, const string& author, int ISBN, bool status) {
    ofstream file("books.csv", ios::app); // open the file in append mode
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    file << title << "," << author << "," << ISBN << "," << status << "\n";
    file.close();
}

void addBooks(){
    
}

void mainMenu()
{
    cout << "Welcome to sjbu library connect \n"
         << "Please select the required option" << endl;
    cout << "1.Staff Login\n2.Member Login" << endl;

    int option;
    cin >> option;

    switch (option)
    {
    case 1:
    {
        string password;
        string username;

        cout << "Staff login" << endl;

        cout << "Enter username" << endl;
        cin >> username;

        cout << "Enter password" << endl;
        cin >> password;

        if(stafflogin(username, password))
        {
            cout << "Login successful!" << endl;
        }
        else
        {
            cout << "Invalid username or password." << endl;
        }

        break;
    }

    case 2:
    {
        string password;
        string username;

        cout << "Member login" << endl;

        cout << "Enter username" << endl;
        cin >> username;

        cout << "Enter password" << endl;
        cin >> password;

        if(memberlogin(username, password))
        {
            cout << "Login successful!" << endl;
        }
        else
        {
            cout << "Invalid username or password." << endl;
        }

        break;
    }
    }
}

int main()
{
    mainMenu();
    return 0;
}