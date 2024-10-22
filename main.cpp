#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>

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

class Member : public Staff
{
private:
    string membershipID;
    string name;
    int phone;
    string email;

public:
    void setName(string name){
        this->name=name;
    }

    void setMembershipID(string membershipID){
        this->membershipID=membershipID;
    }

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
    string title;
    string author;
    int ISBN;
    bool status;

    cout<<"Enter The book title"<<endl;
    cin.ignore();
    getline(cin,title);
    //cin>>title;

    cout<<"Enter the author"<<endl;
    cin>>author;

    cout<<"Enter the book's ISBN"<<endl;
    cin>>ISBN;

    cout<<"Enter the status(1 ro 0)"<<endl;
    cin>>status;

    writeBooksToFile(title,author,ISBN,status);
}

void readBooks() {
    ifstream file("books.csv");
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, statusStr;
        int ISBN;
        bool status;
        
        getline(ss, title, ',');
        getline(ss, author, ',');
        ss >> ISBN >> ws;
        //ss >> status;
        ss >> statusStr;

        //status = (statusStr == "1");
        
        cout << "\nTitle: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Status: " << (status ? "Available" : "Not Available") << endl;
        cout << "---------------------------" << endl;
    }

    file.close();
}

void writeMembersToFile(const string& name, const string& membershipID, int phone, const string& email) {
    ofstream file("members.csv", ios::app); // open the file in append mode
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    file << name << "," << membershipID << "," << phone << "," << email << "\n";
    file.close();
}

void addMember(){

    string membershipID;
    string name;
    int phone;
    string email;

    cout <<"Register a new member"<< endl;

    cout<<"Enter their user name"<<endl;
    cout<<"Do not use spaces, use hyphens"<<endl;
    cin>>name;
    //getline(cin,username);

    Member memberObj1;

    memberObj1.setName(name);

    int id= 1 + (rand() % 6);

    stringstream sstm;
    sstm << name << id;
    membershipID = sstm.str();

    //memberObj1.setPassword(password);
    //automatically generating mmbership ID
    cout<<"membership id is "<<membershipID<<endl;

    cout<<"Enter their phone number"<<endl;
    cin>>phone;

    memberObj1.setPhone(phone);

    cout<<"Enter their email address"<<endl;
    cin.ignore();
    cin>>email;

    memberObj1.setEmail(email);

    writeMembersToFile(name,membershipID,phone,email);



}

void staffMenu(){
    cout<<"STAFF SECTION"<<endl;
    cout<<"1.Add books"<<endl;
    cout<<"2.View all books"<<endl;
    cout<<"3.Register a member"<<endl;
    cout<<"4.View all members"<<endl;

    int staffOption;

    cin>>staffOption;

    switch (staffOption)
    {
    case 1:
        {
        addBooks();
        break;

        }
    case 2:
    {
        readBooks();
        break;
    }
    case 3:
    {
        addMember();
        break;
    }
    default:
        break;
    }
    
    
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

        Member staffObj;

        cout << "Staff login" << endl;

        cout << "Enter username" << endl;
        cin >> username;

        staffObj.setName(username);

        cout << "Enter password" << endl;
        cin >> password;

        staffObj.setPassword(password);

        if(stafflogin(username, password))
        {
            cout << "Login successful!" << endl;
            staffMenu();
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

        Member memberObj;

        cout << "Member login" << endl;

        cout << "Enter username" << endl;
        cin >> username;
        //cin.ignore();
        //getline(cin,username);

        cout << "Enter password" << endl;
        cin >> password;
        //cin.ignore();
        //getline(cin,password);

        memberObj.setPassword(password);
        memberObj.setName(username);

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