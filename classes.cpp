#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include<iomanip>
#include<string>
#include<algorithm>
#include<cctype>
#define ll long long
using namespace std;


//A few general function visible to all classes
int MAX_Borrowing_time_student = 15;
int MAX_borrowable_Book_student = 3;
int MAX_borrowable_Book_Faculty = 5;
int Fine_per_day = 10;
int Dont_allow_borrow_after_faculty = 60;
int setwforString = 15;
int setwforint = 5;

//Returns true if key exits;
template <typename T>
bool exists(vector<T> &v, T key){
    for(T item : v){
        if(item == key){
            return true;
        }
    }
    return false;
}

//All classes are declared here
class Library;
class User;
class Student;void view(Student s);
class Book;void view(Book b);
class Faculty;void view(Faculty f);
class Librarian;void view(Librarian l);
void viewBook_bare_minimum(int id,vector<Book> &Current_books);
/*View() is overloaded*/



int Current_day(){
    ll Library_start_time = 1741341521;//The time in seconds when the library started
    ll oneDay = 86400;//Change to 86400 for actual time;
    return ((ll)(time(nullptr)) - Library_start_time)/oneDay;//# of seconds in a day = 86400
}

class Book{
private:
    /* data */
public:
    static int Total_books;
    string status;
    string publisher;
    string Borrowed_by;//Put the id number here
    string title;
    string author;
    int borrowed_at;
    string ISBN;
    string year;
    int Created_at;
    int id;
    vector<pair<int,int>> Borrow_history;//First is id, Second is #days ::: stores id of persons who had borrowed it previously, and number of days
    Book(string Publisher, string Title, string Author, string Year, string ISBN_numb){
        this->publisher = Publisher;
        this->title = Title;
        this->author = Author;
        this->year = Year;
        this->ISBN = ISBN_numb;
        this->Created_at = Current_day();
        this->borrowed_at = -1;
        this->status = "AVAILABLE";//"AVAILABALE", "BORROWED", "DISABLED"
        this->Borrowed_by = "";//if borrowed by no one this field is empty
        this->id = Total_books++;
        /*SToring format in database : id title author publisher year ISBN Created_at status Borrowedby Borrowed_when borrowhistory*/
    }
    
};
int Book::Total_books = 0;

class User
{
protected:
    string username;
    string password;
public:
    string role;
    static int Total_users;
    string status;//ACTIVE, DISABLED, DELETED
    vector<pair<string,string>> Messages;
    int Createdat;
    int id;
    virtual bool BorrowBook(int id, vector<Book> &Current_Books){return true;}
    virtual bool ReturnBook(int id, vector<Book> &Current_Books){return true;}

    void ViewMessages();
    void DisplayHistory(vector<Book> &Current_Books);

    string getUsername();
    string getPassword();
    bool setUsername(string Username);
    bool setPassword(string Password);

    User(string Role, string UserName, string PassWord){
        this->role = Role;
        this->status = "ACTIVE";
        this->Createdat = Current_day();
        id = Total_users++;
        setUsername(UserName);setPassword(PassWord);
    }
};
int User::Total_users = 0;

void User::ViewMessages(){
    if(Messages.size() == 0){
        cout << "NO MESSAGES\n";
        return;
    }
    for(pair<string,string> p : Messages){
        cout << p.first << " : " << p.second << "\n";
    }
    return;
}

void User::DisplayHistory(vector<Book> &Current_Books){
    bool printed = false;
    for(Book b : Current_Books){
        for(pair<int,int> p : b.Borrow_history){
            if(p.first == this->id){
                printed = true;
                cout << "Book id : " << b.id << " || Borrowed for : " << p.second << "\n";
            }
        }
    }
    if(!printed){
        cout << "NO HISTORY, Borrow Books to Create History and start your Journey with this Legendary Program\n";
    }
    return;
}

string User::getUsername(){
    return username;
}
string User::getPassword(){
    return password;
}
bool User::setUsername(string Username){
    this->username = Username;
    return true;
}
bool User::setPassword(string Password){
    this->password = Password;
    return true;
}
//User ends here

class Student : public User{
    private:
        /* data */
    public:
        vector<Book> Currently_Borrowed_books;
        int Fine;
        int Paid;
    
        int FineToPay();
        bool PayFine(int amt);
        void ShowOverdue();
        bool RuturnBook(int id, vector<Book> &Current_books);
        bool BorrowBook(int id, vector<Book> &Current_books);
    
        //In the initializing function, fine is updated with the help of last calculated date
        Student(int Last_calculated,int paid,int Fine ,string UserName, string PassWord) : User("STUDENT", UserName, PassWord){
            // Calls the user constructor with arguments "STUDENT", Fine Update is done while loading the book from database in Load_student()
            this->Fine = Fine;
            this->Paid = paid;
        }
        // ~Student();
};

int Student::FineToPay(){
    return Fine - Paid;
}

bool Student::PayFine(int amt){
    cout << "YOUR PENDING FINE IS : " << Fine - Paid - amt << "\n";
    Paid += amt;
    return true;
}

void Student::ShowOverdue(){
    vector<Book> v;
    for(Book b : Currently_Borrowed_books){
        if(Current_day() - b.borrowed_at > MAX_borrowable_Book_student){
            v.push_back(b);
        }
    }
    if(v.size() == 0){
        cout << "NO Overdues books\n";
    }
    else{
        for(Book b : v){
            cout << "id : " << b.id << " || Title : " << b.title << " || Borrowed_for : " << Current_day() - b.borrowed_at << "\n";
        }
    }
}

bool Student::BorrowBook(int id, vector<Book> &Current_books){
    if(this->status != "ACTIVE"){
        cout << "THIS ACCOUNT Isn't ACTIVE, GO TO LIBRARIAN TO GET IT BACK\n";
        return false;
    }
    if(Currently_Borrowed_books.size() >= MAX_borrowable_Book_student){
        cout << "MAX BOOK LIMIT REACHED\n";
        return false;
    }
    else if(Fine - Paid > 0){
        cout << "Clear all your fines to borrow more books. Fine amount = " << Fine - Paid << "\n";
        return false;
    }
    cout << "hi";
    for(auto b  = Current_books.begin(); b != Current_books.end(); b++){
        if(b->id == id){
            if(b->status == "AVAILABLE"){
                
                b->status = "BORROWED";
                b->borrowed_at = Current_day();
                b->Borrowed_by = this->username;
                cout << "Yo\n";
                this->Currently_Borrowed_books.push_back(*b);
                cout << "succesfully took book\n";
                return true;
            }
            else if(b->status == "DISABLED"){
                cout << "Book has been disabled\n";
                return false;
            }
            else if(b->status == "BORROWED"){
                cout << "Book is borrowed, come back other time\n";
                return false;
            }
            else{
                cout << "Book has been deleted\n";
                return false;
            }
        }
    }
    cout << "ENTER A VALID ID :-(\n";
    return false;
}

bool Student::RuturnBook(int id, vector<Book> &Current_books){
    if(Fine - Paid > 0){
        cout << "First clear your fine of " << Fine - Paid << "\n";
        return false;
    }
    for(auto b = Currently_Borrowed_books.begin(); b != Currently_Borrowed_books.end(); b++){
        if(b->id == id){
            for(auto it = Current_books.begin(); it != Current_books.end(); it++){
                if(it->id == id){
                    it->status = "AVAILABLE";
                    it->Borrowed_by = "";
                    it->Borrow_history.push_back({this->id, Current_day() - it->borrowed_at});
                    it->borrowed_at = -1;    
                }
            }    
            Currently_Borrowed_books.erase(b);
            cout << "SUCCESSFULLY RETURNED BOOK\n";
            return true;
        }
    }
    cout << "Enter a valid book id, which you have borrowed\n";
    return false;
}

class Faculty : public User{
    private:
        //Any leftover data
    public:
        vector<Book> Currently_Borrowed_books;
    
        bool BorrowBook(int id, vector<Book>&Current_books);
        bool ReturnBook(int id, vector<Book> &Current_books);
        bool ShowOverdues();
    
        Faculty(string UserName, string PassWord) : User("FACULTY" , UserName, PassWord){}
        // ~Faculty();
};

bool Faculty::BorrowBook(int id, vector<Book>&Current_books){
    if(status != "ACTIVE"){
        cout << "YOUR ACCOUNT Isn't ACTIVE, TALK TO LIBRARIAN TO GET IT ACTIVATED\n";
        return false;
    }
    //check book borrowing capacity
    if(Currently_Borrowed_books.size() >= MAX_borrowable_Book_Faculty){
        cout << "MAX BOOK LIMIT REACHED\n";
        return false;
    }
    //CHeck if any overdue books
    for(Book b : Currently_Borrowed_books){
        if(Current_day() - b.borrowed_at > Dont_allow_borrow_after_faculty){
            cout << "Book id : " << b.id << " is overdue, return it to borrow more books\n";
            return false;
        }
    }
    for(auto b  = Current_books.begin(); b != Current_books.end(); b++){
        if(b->id == id){
            if(b->status == "AVAILABLE"){
                b->status = "BORROWED";
                b->borrowed_at = Current_day();
                b->Borrowed_by = this->username;
                Currently_Borrowed_books.push_back(*b);
                cout << "succesfully took book\n";
                return true;
            }
            else if(b->status == "DISABLED"){
                cout << "Book has been disabled\n";
                return false;
            }
            else if(b->status == "BORROWED"){
                cout << "Book is borrowed, come back other time\n";
                return false;
            }
            else{
                cout << "Book has been deleted\n";
                return false;
            }
        }
    }
    cout << "ENTER A VALID ID :-(\n";
    return false;
}

bool Faculty::ReturnBook(int id, vector<Book> &Current_books){
    for(auto it = Currently_Borrowed_books.begin(); it != Currently_Borrowed_books.end(); it++){
        if(it->id == id){
            for(auto b = Current_books.begin(); b != Current_books.end(); b++){
                if(b->id == id){
                    b->status = "AVAILABLE";
                    b->Borrowed_by = "";
                    b->Borrow_history.push_back({this->id, Current_day() - b->borrowed_at});
                    b->borrowed_at = -1;
                }
            }
            Currently_Borrowed_books.erase(it);
            cout << "SUccesfully returned book\n";
            return true;
        }
    }
    cout << "Enter a valid book, which u have borrowed\n";
    return false;
}

bool Faculty::ShowOverdues(){
    bool entered = false;
    for(Book b : Currently_Borrowed_books){
        if(Current_day() - b.borrowed_at > MAX_borrowable_Book_Faculty){
            view(b);
            entered = true;
            return true;
        }
    }
    if(!entered){
        cout << "NO OVERDUE BOOKS\n";
        return false;
    }
    return false;
}


class Librarian : public User{
    private:
    /*Any data here*/
    public: 
        bool AddUser(string Role, string UserName, string PassWord, vector<Student> &Current_students, vector<Faculty> &Current_faculty );
        bool AddLibrarian(string UserName, string PassWord, vector<Librarian> &Current_librarian);
        //to delete pass delete as status
        bool ChangeUserStatus(int id, string Status, vector<Student> &Current_students, vector<Faculty> &Current_faculty);
        bool AddBook(string Publisher , string Title , string Author , string YEAR , string ISBN, vector<Book> &Current_books);
        bool ChangeBookStatus(int ID, string Status, vector<Book> &Current_books);

        Librarian(string usnm,string pword) : User("Librarian", usnm, pword){
            //Empty Constructur, Just call User
        }
};

bool Librarian::AddUser(string Role, string UserName, string PassWord, vector<Student> &Current_students, vector<Faculty> &Current_faculty ){
    if(Role == "STUDENT"){
        for(Student s : Current_students){
            if(s.getUsername() == UserName){
                cout << "Please select another username, this one's taken\n";
                return false;
            }
        }
        Student new_student(Current_day(), 0,0,UserName, PassWord);
        Current_students.push_back(new_student);
        cout << "Successfuly registered with ID#" << new_student.id << "\n";
        return true;
    }
    else if(Role == "FACULTY"){
        for(Faculty f : Current_faculty){
            if(f.getUsername() == UserName){
                cout << "Please select another username, this one's taken\n";
                return false;
            }
        }
        Faculty new_faculty(UserName, PassWord);
        Current_faculty.push_back(new_faculty);
        cout << "Successfuly registered with ID#\n" << new_faculty.id << "\n"; 
        return true;
    }

    cout << "Can't Understand Input, please type STUDENT or FACULTY\n";
    return false;
}

bool Librarian::AddLibrarian(string UserName, string PassWord, vector<Librarian> &Current_librarian){
    for(Librarian l : Current_librarian){
        if(l.getUsername() == UserName){
            cout << "Please select another username, this one's taken\n";
            return false;
        }
    }
    Librarian new_librarian(UserName, PassWord);
    Current_librarian.push_back(new_librarian);
    cout << "Successfully added Librarian\n";
    return true;
}
//to delete pass delete as status
bool Librarian::ChangeUserStatus(int id, string Status, vector<Student> &Current_students, vector<Faculty> &Current_faculty){

    for (auto it = Current_students.begin(); it != Current_students.end(); it++){
        if (it->id == id){
            if (it->Currently_Borrowed_books.size() > 0){
                cout << "Cannot change account status as this guy has borrowed books\n";
                return false;
            }
            else if (Status == "DISABLED" || Status == "ACTIVE"){
                cout << "SUccessfully disabled\n";
                it->status = Status;
                return true;
            }
            else if (Status == "DELETED"){
                Current_students.erase(it);
                cout << "Successfully deleted\n";
                return true;
            }
            else{
                cout << "Invalid status\n";
                return false;
            }
        }
    }

    for (auto it = Current_faculty.begin(); it != Current_faculty.end(); it++){
        if (it->id == id){
            if (it->Currently_Borrowed_books.size() > 0){
                cout << "Cannot change account status as this guy has borrowed books\n";
                return false;
            }
            else if (Status == "DISABLED" || Status == "ACTIVE"){
                cout << "SUccessfully disabled\n";
                it->status = Status;
                return true;
            }
            else if (Status == "DELETED"){
                Current_faculty.erase(it);
                cout << "Successfully deleted\n";
                return true;
            }
            else{
                cout << "Invalid status\n";
                return false;
            }
        }
    }
    cout << "No such faculty or student\n";
    return false;

    cout << "some error\n";
    return false;
}

bool Librarian::AddBook(string Publisher , string Title , string Author , string YEAR , string ISBN, vector<Book> &Current_books){
    Book b(Publisher, Title, Author, YEAR, ISBN);
    Current_books.push_back(b);
    cout << "SUccessfully added book\n";
    return true;
}

bool Librarian::ChangeBookStatus(int ID, string Status, vector<Book> &Current_books){
    if(Status != "AVAILABLE" && Status != "DISABLED" && Status != "DELETE"){
        cout << "Invalid status\n";
        return false;
    }
    for(auto it = Current_books.begin(); it != Current_books.end(); it++){
        if(it->id == ID){
            if(it->status != "AVAILABLE"){
                cout << "BOOK IS EITHER BORROWED OR DISABLED\n";
                return false;
            }
            else if(Status == "DISABLED"){
                it->status = Status;
                cout << "SUccessfully disabled\n";
                return true;
            }
            else if(Status == "DELETE"){
                Current_books.erase(it);
                cout << "Successfully deleted book\n";
                return true;
            }
            else{
                cout << "Invalid status\n";
                return false;
            }
        }
    }
    cout << "No such book\n";
    return false;
    cout << "Some error\n";
    return false;
}


class Library
{
private:
    string Bookdata;
    string Studentdata;
    string Facultydata;
    string Librariandata;
    string libdata;
public:
    bool isTxtFile(const std::string& filename) {return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".txt";}
    vector<Student> Current_students;
    vector<Faculty> Current_faculty;
    vector<Book> Current_books;
    vector<Librarian> Current_librarian;

    string viewbookfile(){return Bookdata;}
    string viewstudentfile(){return Studentdata;}
    string viewfacultyfile(){return Facultydata;}
    string viewlibrariandata(){return Librariandata;}
    // bool SendMessage(string usnm, int reciever, string message); Here usnm is of Sender
    // void SearchBookViaTitle(string TITLE);
    // bool changebookfile(string newbook);
    // bool changestudentfile(string newbook);
    // bool changefacultyfile(string newbook);
    // bool changeLibrarianfile(string newbook);
    // bool ViewAllStudents();
    // bool ViewAllFaculty();
    // bool ViewAllBooks();
    // int Load_Librarian();
    // void Save_Librarian();
    // void Load_books();
    // void Save_books();
    // int Load_Students();
    // bool Save_students();
    // int Load_faculty();
    // void Save_faculty();
    //These are all the member fuctions associated with Libaray Class, below is their defination

    bool SendMessage(string usnm, int reciever, string message);

    void SearchBookViaTitle(string TITLE);


    bool changebookfile(string newbook);
    bool changestudentfile(string newbook);
    bool changefacultyfile(string newbook);
    bool changeLibrarianfile(string newbook);

    bool ViewAllStudents();
    bool ViewAllFaculty();
    bool ViewAllBooks();

    int Load_Librarian();
    void Save_Librarian();

    /*SToring format in database : id title author publisher year ISBN Created_at status Borrowedby Borrowed_when borrowhistory*/
    void Load_books();
    void Save_books();

    int Load_Students();
    bool Save_students();

    int Load_faculty();
    void Save_faculty();

    Library(string Bd, string Sd,string fd ,string Librariandat, string libraydata){
        this->Bookdata = Bd;
        this->Facultydata = fd;
        this->Studentdata = Sd;
        this->Librariandata = Librariandat;
        this->libdata = libraydata;
        Load_books();
        User::Total_users = max(Load_Students(), Load_faculty());//Update totalUsers which helps assign uniqe id 
        User::Total_users = max(User::Total_users, Load_Librarian()) + 1;
        ofstream file(this->libdata);
        if(!file.is_open()){
            cout << "!!!!Can't update Libraries, last opened time!!!!\n";
        }
        file << Current_day();
        file.close();
    }
    ~Library(){
        Save_books();
        Save_faculty();
        Save_students();
        Save_Librarian();
        cout << "BYE BYE take care";
    }
};

bool Library::SendMessage(string usnm, int reciever, string message){
    for(auto it = Current_students.begin(); it != Current_students.end(); it++){
        if(it->id == reciever){
            it->Messages.push_back({usnm, message});
            cout << "Message sent\n";
            return true;
        }
    }
    for(auto it = Current_faculty.begin(); it != Current_faculty.end(); it++){
        if(it->id == reciever){
            it->Messages.push_back({usnm, message});
            cout << "Message sent\n";
            return true;
        }
    }
    for(auto it = Current_librarian.begin(); it != Current_librarian.end(); it++){
        if(it->id == reciever){
            it->Messages.push_back({usnm, message});
            cout << "Message sent\n";
            return true;
        }
    }
    cout << "No such ID found ;(\n";
    return false;
}

void Library::SearchBookViaTitle(string TITLE){
    bool found = false;
    transform(TITLE.begin(), TITLE.end(), TITLE.begin(), ::tolower);
    for(Book b : Current_books){
        string ruff = b.title;
        transform(ruff.begin(), ruff.end(), ruff.begin(), ::tolower);
        if(ruff.find(TITLE) != string::npos){
            view(b);
            found = true;
        }
    }
    if(!found){
        cout << "NO SUCH BOOK FOUND\n";
    }
}


bool Library::changebookfile(string newbook){
    if(isTxtFile(newbook)){
        cout << "OK DONE\n";
        Bookdata = newbook;
        return true;
    }
    else{
        cout << "INVALID FILE NAME\n";
        return false;
    }
}
bool Library::changestudentfile(string newbook){
    if(isTxtFile(newbook)){
        cout << "OK DONE\n";
        Studentdata = newbook;
        return true;
    }
    else{
        cout << "INVALID FILE NAME\n";
        return false;
    }
}
bool Library::changefacultyfile(string newbook){
    if(isTxtFile(newbook)){
        cout << "OK DONE\n";
        Facultydata = newbook;
        return true;
    }
    else{
        cout << "INVALID FILE NAME\n";
        return false;
    }
}
bool Library::changeLibrarianfile(string newbook){
    if(isTxtFile(newbook)){
        cout << "OK DONE\n";
        Librariandata = newbook;
        return true;
    }
    else{
        cout << "INVALID FILE NAME\n";
        return false;
    }
}
bool Library::ViewAllStudents(){
    cout << "Total Students = " << this->Current_students.size() << "\n";
    cout << "----------------------------------------------------------------------------------------------------------\n";
    cout << setw(setwforint) << "ID" << setw(setwforString) << "USERNAME" << setw(setwforString) << "STATUS" << setw(setwforint+10) << "Createat" << setw(setwforint+5) << "FINE" << "      " << "BORROWED BOOKS\n";
    cout << "----------------------------------------------------------------------------------------------------------\n";
    for(Student s : this->Current_students){
        view(s);
    }
    return true;
}

bool Library::ViewAllFaculty(){
    cout << "Total Faculties = " << this->Current_faculty.size() << "\n";
    cout << "----------------------------------------------------------------------------------------------------------\n";
    cout << setw(setwforint) << "ID" << setw(setwforString) << "USERNAME" << setw(setwforString) << "STATUS" << "        " << "BORROWED BOOKS\n";
    cout << "----------------------------------------------------------------------------------------------------------\n";
    for(Faculty f : this->Current_faculty){
        view(f);
    }
    return true;
}

bool Library::ViewAllBooks(){
    // cout << " BOOK ID || TITLE || STATUS || BORROWED BY ||Borrowed for ||ADDED AT";
    cout << "----------------------------------------------------------------------------------------------------------\n";
    cout  << "ID" << setw(setwforString +15) << "TITLE" << setw(setwforString + 10) << "YEAR" << setw(setwforString) << "STATUS" << setw(setwforString) << "BORROWED BY" << setw(setwforint +10) << "Daysbrw" << setw(setwforint+10) << "Add dt" <<  "      History(user id, #days)\n";
    cout << "----------------------------------------------------------------------------------------------------------\n";
    for(Book b : this->Current_books){
        view(b);
    }
    return true;
}

int Library::Load_Librarian(){
    int max_id = 0;
    ifstream file(this->Librariandata);
    if(!file.is_open()){
        cerr << "Error!! Can't open file containing Librarian Password and Username";
        return -1;
    }
    string line;
    string usnm;
    string Identifier;
    string pword;
    
    while(getline(file, line)){
        Librarian Libian("", "");
        string parts;
        stringstream streamline(line);
        vector<pair<string, string>> massagevec;
        for(int i = 0 ; getline(streamline, parts, ';'); i++){
            if(i == 0){
                stringstream ss(parts);
                string word;
                getline(ss, word, ',');
                Identifier = word;
                getline(ss, word, ',');
                usnm = word;
                getline(ss , word, ',');
                pword = word;
                Libian.setUsername(usnm);
                Libian.setPassword(pword);
                Libian.id = stoi(Identifier);
                max_id = max(max_id, Libian.id);
            }

            else{
                stringstream goth(parts);
                string word;
                pair<string, string> p;
                getline(goth, word, ':');
                p.first = word;
                getline(goth, word, ':');
                p.second = word;
                massagevec.push_back(p);
            }
            
        }
        Libian.Messages = massagevec;
        Current_librarian.push_back(Libian);
    }
    return max_id;
}

void Library::Save_Librarian(){
    ofstream file(this->Librariandata);
    if(!file.is_open()){
        cerr << "Can't open file to save Librarian data\n";
        return;
    }
    for(Librarian l : this->Current_librarian){
        file << l.id << "," << l.getUsername() << "," << l.getPassword() << ";";
        for(pair<string,string> p : l.Messages){
            file << p.first << ":" << p.second << ":"<< ";";
        }
        file << "\n";
    }
    cout << "Succesfully saved Librarian data\n";
    file.close();
    return;
}

void Library::Load_books(){
    int max_id = 0;
    ifstream file(this->Bookdata);
    if(!file){
        cerr << "ERROR opening " << this->Bookdata;
    }
    // cout << "Opened bookfile\n";
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string word;
        int cnt = 0;
        string title ,author, publisher, year ,ISBN ,status ,Borrowedby;
        int id, Borrowed_when, Created_at;
        vector<pair<int,int>> v;
        while(getline(ss,word,',')){
            // cout << cnt;
            if(cnt == 0) id = stoi(word);
            else if(cnt == 1) title = word;
            else if(cnt == 2) author = word;                
            else if(cnt == 3) publisher = word;
            else if(cnt == 4) year = word;
            else if(cnt == 5) ISBN = word;
            else if(cnt == 6) Created_at = stoi(word);
            else if(cnt == 7) status = word;
            else if(cnt == 8) Borrowedby = word;
            else if(cnt == 9) {Borrowed_when = stoi(word);}
            else{
                pair<int,int> p;
                while(word != ""){
                    p.first = stoi(word);
                    getline(ss, word, ',');
                    p.second = stoi(word);
                    getline(ss, word, ',');
                    v.push_back(p);
                }
            }
            // cout << cnt;
            cnt++;
        }
        Book newbook(publisher, title, author, year, ISBN);
        newbook.borrowed_at = Borrowed_when;
        // cout << Borrowed_when << "   "  << id<< "   Borrwoed when & id \n";
        newbook.Created_at = Created_at;
        newbook.id = id;
        newbook.Borrowed_by = Borrowedby;
        newbook.status = status;
        newbook.Borrow_history = v;
        this->Current_books.push_back(newbook);
        max_id = max(max_id, id);
    }
    Book::Total_books = max_id + 1;
    file.close();
    // id title author publisher year ISBN Created_at status Borrowedby Borrowed_when
}
/*SToring format in database : id title author publisher year ISBN Created_at status Borrowedby Borrowed_when borrowhistory*/
void Library::Save_books(){
    ofstream file(this->Bookdata);
    if(!file.is_open()){
        cerr << "Unable to open Book file while saving\n";
        return;
    }
    for(Book b : this->Current_books){
        file << b.id << "," << b.title << "," << b.author << "," << b.publisher << "," << b.year << "," << b.ISBN << "," << b.Created_at << "," << b.status << "," << b.Borrowed_by << "," << b.borrowed_at << ",";
        for(pair <int,int> p : b.Borrow_history){
            file << p.first << "," << p.second << ",";
        }
        file << "\n";
    }
    cout << "safely saved books\n";
    file.close();
    return;
}


int Library::Load_Students(){
    ifstream lastopendata(this->libdata);
    string lastopen;
    getline(lastopendata, lastopen);
    int Last_calc = stoi(lastopen);
    lastopendata.close();
    int max_id = 0;
    ifstream file(this->Studentdata);
    if(!file){
        cerr << "Error opening Students database\n";
        return -1;
    }
    
    string line;
    while(getline(file, line)){
        Student new_student(Last_calc, 0, 0, "", "");
        string parts;
        stringstream streamline(line);
        for(int i = 0 ;getline(streamline, parts, ';') ; i++){
            if(i == 0){
                stringstream ss(parts);
                string word;
                int cnt = 0;
                int id, Created_at, Fine, Paid;
                string Username, Password, Status;
                vector<int> book_id;
                while(getline(ss, word, ',')){

                    if(cnt == 0) id = stoi(word);
                    else if(cnt == 1) Username = word;
                    else if(cnt == 2) Password = word;
                    else if(cnt == 3) Status = word;
                    else if(cnt == 4) Created_at = stoi(word);
                    else if(cnt == 5) {Fine = stoi(word);}
                    else if(cnt == 6) {Paid = stoi(word);}
                    else{
                        while(word != ""){
                            book_id.push_back(stoi(word));
                            getline(ss, word, ',');
                        }
                        break;
                    }
                    cnt++;
                }
                max_id = max(max_id, id);
                new_student.setUsername(Username);
                new_student.setPassword(Password);
                new_student.Paid = Paid;
                new_student.Fine = Fine;
                new_student.id = id;
                new_student.Createdat = Created_at;
                new_student.status = Status;
                vector<Book> v;
                for(int id : book_id){
                    for(Book b : Current_books){
                        if(b.id == id){
                            v.push_back(b);
                            break;
                        }
                    }
                }
                new_student.Currently_Borrowed_books = v;
                for(Book b : new_student.Currently_Borrowed_books){
                    new_student.Fine += max(min(Current_day() - (b.borrowed_at + MAX_Borrowing_time_student), Current_day() - Last_calc), 0)*Fine_per_day;
                }   
            }
            else{
                stringstream goth(parts);
                string word;
                pair<string, string> p;
                getline(goth, word, ':');
                p.first = word;
                getline(goth, word, ':');
                p.second = word;
                new_student.Messages.push_back(p);
            }
                
            
        }
        this->Current_students.push_back(new_student);
    }
    file.close();
    return max_id;
}

bool Library::Save_students(){
    ofstream file(this->Studentdata);
    if(!file.is_open()){
        cerr << "Can't open Students file while saving\n";
        return false;
    }
    for(Student s : this->Current_students){
        file << s.id << "," << s.getUsername() << "," << s.getPassword() << "," << s.status << "," << s.Createdat << "," << s.Fine << "," << s.Paid << ",";
        for(Book b : s.Currently_Borrowed_books){
            file << b.id << ",";
        }
        file << ";";
        for(pair<string,string> p : s.Messages){
            file << p.first << ":" << p.second << ":;";
        }
        file << "\n";
    }

    cout << "Saved Students\n";
    file.close();
    return true;
}

int Library::Load_faculty(){
    ifstream lastopendata(this->libdata);
    string lastopen;
    getline(lastopendata, lastopen);
    int Last_calc = stoi(lastopen);
    lastopendata.close();
    // cout << "Opening faculty data\n";
    int max_id = 0;
    ifstream file(this->Facultydata);
    if(!file){
        cerr << "Error opening Faculty database\n";
        return -1;
    }

    string line;
    while(getline(file, line)){
        Faculty new_faculty("", "");
        string parts;
        stringstream streamline(line);
        for(int i = 0 ;getline(streamline, parts, ';') ; i++){
            if(i == 0){
                stringstream ss(parts);
                string word;
                int cnt = 0;
                int id, Created_at, Fine, Paid;
                string Username, Password, Status;
                vector<int> book_id;
                while(getline(ss, word, ',')){
                    // cout << cnt;
                    if(cnt == 0) id = stoi(word);
                    else if(cnt == 1) Username = word;
                    else if(cnt == 2) Password = word;
                    else if(cnt == 3) Status = word;
                    else if(cnt == 4) Created_at = stoi(word);
                    else{
                        while(word != ""){
                            book_id.push_back(stoi(word));
                            getline(ss, word, ',');
                        }
                        break;
                    }
                    cnt++;
                }
                max_id = max(max_id, id);
                new_faculty.setUsername(Username);
                new_faculty.setPassword(Password);
                new_faculty.id = id;
                new_faculty.Createdat = Created_at;
                new_faculty.status = Status;
                vector<Book> v;
                for(int id : book_id){
                    for(Book b : Current_books){
                        if(b.id == id){
                            v.push_back(b);
                            break;
                        }
                    }
                }
                new_faculty.Currently_Borrowed_books = v;
            }
            else{
                stringstream goth(parts);
                string word;
                pair<string, string> p;
                getline(goth, word, ':');
                p.first = word;
                
                getline(goth, word, ':');
                p.second = word;
                new_faculty.Messages.push_back(p);
            }
                
            
        }
        this->Current_faculty.push_back(new_faculty);
    }
    file.close();
    return max_id;
}



void Library::Save_faculty(){
    ofstream file(this->Facultydata);
    if(!file.is_open()){
        cerr << "Error in opening faculty file, while opening\n";
        return;
    }
    for(Faculty f : this->Current_faculty){
        file << f.id << "," << f.getUsername() << "," << f.getPassword() << "," << f.status << "," << f.Createdat << ",";
        for(Book b : f.Currently_Borrowed_books){
            file << b.id << ",";
        }
        file << ";";
        for(pair<string,string> p : f.Messages){
            file << p.first << ":" << p.second << ":" << ";";
        }
        file << "\n";
    }
    cout << "safely saved faculty\n";
    file.close();
    return;
}


//Fucntions to view the data in a better way

void view(Student s){
    // cout << "id : " << s.id << " ||Username : " << s.getUsername() << "||Status " << s.status << setw(setwforint) << "Createdat" <<" ||Fine : " << s.FineToPay() << " ||Borrowed Books : ";
    cout << setw(setwforint) << s.id << setw(setwforString) << s.getUsername() << setw(setwforString) << s.status<< setw(setwforint+10) << s.Createdat << setw(setwforint+5) << s.FineToPay() << "       ";
    for(Book b : s.Currently_Borrowed_books){
        cout << "(" << b.id << "," << " " << Current_day() - b.borrowed_at<< ")  ";
    }
    cout << "\n";
}

void view(Book b){
    // cout << " BOOK ID || TITLE || STATUS || BORROWED BY ||Borrowed for ||ADDED AT ";
    if(b.status == "BORROWED"){
        cout << b.id << setw(setwforString+30) << b.title << setw(setwforint +5) << b.year  << setw(setwforString) << b.status  << setw(setwforString) << b.Borrowed_by  << setw(setwforint + 10) << Current_day() - b.borrowed_at << setw(setwforint + 10) << b.Created_at  << setw(5);
    }
    else{
        cout << b.id << setw(setwforString+30) << b.title << setw(setwforint +5) << b.year  << setw(setwforString) << b.status  << setw(setwforString) << b.Borrowed_by  << setw(setwforint + 10) << b.borrowed_at << setw(setwforint + 10) << b.Created_at  << setw(5);
    }
    for(pair<int,int> p : b.Borrow_history){
        cout << "(" << p.first << "," << p.second << "),";
    }
    cout << "\n\n\n";
}

void viewBook_bare_minimum(int id, vector<Book> &Current_books){
    for(Book b : Current_books){
        if(b.id == id){
            cout <<"ID" << setw(setwforString+10) << "TITLE" << setw(setwforString+10) << "AUTHOR" << setw(setwforString) << "STATUS" << setw(setwforString) << "ISBN" << setw(setwforint+5) << "Borrowed for\n";
            if(b.status == "BORROWED"){
                cout << b.id << setw(setwforString + 10) << b.title << setw(setwforString+10) << b.author << setw(setwforString) << b.status << setw(setwforString) << b.ISBN << setw(setwforint+5) << Current_day() - b.borrowed_at << "\n";
            }
            else{
                cout << b.id << setw(setwforString + 10) << b.title << setw(setwforString+10) << b.author << setw(setwforString) << b.status << setw(setwforString) << b.ISBN << setw(setwforint+5) << b.borrowed_at << "\n";
            }
            return;
        }
    }
    cout << "Enter a valid book id\n";
    return;
}


void view(Faculty s){
    cout << setw(setwforint)<< s.id << setw(setwforString) << s.getUsername() << setw(setwforString) << s.status << setw(setwforint+5);
    for(Book b : s.Currently_Borrowed_books){
        cout << "(" << b.id << "," << " " << Current_day() - b.borrowed_at<< ")  ";
    }
    cout << "\n";
}

void view(Librarian l) {
    cout << setw(setwforint) << l.id << setw(setwforString) << l.getUsername() << setw(setwforString) << l.status << setw(setwforint+5) << "\n";
}
