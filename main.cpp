#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

void write_csv(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename,ios::app);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}

void write_csv_header(const string& filename) {
    ofstream file(filename);  // This will overwrite the file
    file << "Name,Passcode\n";
}

void admin(){
    cout << "\tEnter Your Name: \n\t";

    string Name;
    cin >> Name;

    string Passcode;
    cout << "\tEnter Your passcode: \n\t";
    cin >> Passcode;

    string strName = "Anthony";
    string strPasscode = "00000000";

    // if (Name==strName){
    //     cout << "Your name is " << Name << " and Passcode is " << Passcode;
    // }else
    // {
    //     cout << "Wrong staff nigga";
    // }
    
    //added Header manually - make it automatic
    vector<vector<string>> data = {
        {Name, Passcode},
    };
    write_csv("admin.csv", data);

    cout << "Added to csv db";
    
}

//title,author, ISBN, and availability status
class Book {
    private:
        string title;
        string author;
        int ISBN;
        int Status;
    
    public:
        void setTitle(string Title){
            title = Title;
        }

        void setAuthor(string Author){
            author = Author;
        }

        void setISBN(int isbn){
            ISBN = isbn;
        }

        void setAvailabilityStatus(int status){
            Status = status;
        }

        string getTitle(string Title){
            return title;
        }

        string getAuthor(string Author){
            return author;
        }

        int getISBN(int isbn){
            return ISBN;
        }

        int getAvailabilityStatus(int status){
            return Status;
        }
};

class User {
    private:
        string UserName;
        string Password;

    public:
        void setUserName(string username){
            UserName = username;
        }

        void setPassword(string password){
            Password = password;
        }

        string getUserName(){
            return UserName;
        }

        string getPassword(){
            return Password;
        }
};

class Member {
    private:
        string UserName;
        string MembershipId;
        string Email;
        int PhoneNumber;

    public:
        void setUserName(string username){
            UserName =  username;
        }

        void setMembershipId(string membershipid){
            MembershipId = membershipid;
        }

        void setEmail(string email){
            Email = email;
        }

        void setPhoneNumber(int phonenumber){
            PhoneNumber = phonenumber;
        }

        string getUserName(){
            return UserName;
        }

        string getMembershipId(){
            return MembershipId;
        }

        string getEmail(){
            return Email;
        }

        int getPhoneNumber(){
            return PhoneNumber;
        }
};

class Staff {
    private:
        string username;
        string password;
    void createLibraryUser(){
        cout << "\tEnter a suitable username\n\t";
        
        cin >> username;

        cout << "\tEnter a valid password\n\t";
        
        cin >> password;

        cout << "Your password is " << password << " and your username is " << username;

        vector<vector<string>> data = {
            {username, password},
        };
        write_csv("LibraryStaff.csv", data);
    }

    public:

    void setUsername(string UserName){
        username = UserName;
    }

    void setPassword(string PassWord){
        password = PassWord;
    }

    string getUsername(){
        return username;
    }

    string getPassword(){
        return password;
    }

    void libraryStaffMenu(){
        cout << "\tCreate Library User\n";
        createLibraryUser();
    }
}; 

int main(){
    char text[] = "Welcome";

    cout << "Library Management system\n";

    cout << text << " - Choose Your preferred option: \n";

    cout << "\t1.Admin\n\t2.Library Staff\n\t3.Library Member\n\t4.Exit\n\t";

    int option;

    cin >> option;

    switch(option)
    {
        case 1:
            admin();
            break;
        case 2:
            cout << "\t staff section";
            break;
        case 3:
            cout << "\tYou are in Members section";
            break;
        case 4:
            cout << "\tYou chose Exit";
            break;
    }

    return 0;
}
