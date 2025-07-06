#include<iostream>
#include"classes.cpp"
using namespace std;

int main(){
    Library L("books.txt", "students.txt", "faculty.txt", "Librarian_data.txt", "Library_data.txt");
    string input, enteredpword, enteredIDstring;
    int enteredid;
    
    bool logged_in_student,logged_in_Librarian, logged_in_faculty;
    logged_in_faculty = logged_in_student = logged_in_Librarian = false;
    int k;//The index of user/Faculty;

    vector<Student>::iterator stud = L.Current_students.end();
    vector<Faculty>::iterator fac = L.Current_faculty.end();
    vector<Librarian>::iterator libraian = L.Current_librarian.end();
    vector<Book>::iterator book = L.Current_books.end();

    for(int i = 0 ; ; i++){
        if( i == 0){
            cout << "                             WELCOME TO LMS\n";
            cout << "press 1, to login as STUDENT\npress 2, to login as FACULTY\npress 3, to login as LIBRARIAN\npress 4, to close and save the changes you just made safely\n";
            cin >> input;
            if(input == "1"){
                logged_in_student = true;
            }
            else if(input == "2"){
                logged_in_faculty = true;
            }
            else if(input == "3"){
                logged_in_Librarian = true;
            }
            else if(input == "4"){
                cout << "Saving and closing\n";
                break;
            }
            else {
                cout << "Invalid input, Please try again!?!\n";
                i--;
            }
        }
        else if(i == 1){
            cout << "Kindly Enter ID or type \"back\", to go back: ";
            cin >> enteredIDstring;
            if(enteredIDstring == "back"){
                i = -1;
            }
        }
        else if(i == 2){
            try{
                enteredid = stoi(enteredIDstring);
                // cout << enteredid;
            }
            catch(const std::exception& e){
                cerr << "Enter a valid ID\n";
                i = 0;
                continue;
            }
            bool correctid = false;
            if(logged_in_student){
                for(Student s : L.Current_students){
                    if(s.id == enteredid){
                        correctid = true;
                        break;
                    }
                }
            }
            else if(logged_in_faculty){
                for(Faculty s : L.Current_faculty){
                    if(s.id == enteredid){
                        correctid = true;
                        break;
                    }
                }
            }
            else if(logged_in_Librarian){
                for(Librarian s : L.Current_librarian){
                    if(s.id == enteredid){
                        correctid = true;
                        break;
                    }
                }
            }

            if(!correctid){
                cout << "Please enter a valid ID\n";
                i = 0;
                continue;
            }

            bool valid_id = false;
            enteredid = stoi(enteredIDstring);
            cout << "Kindly Enter Password : ";
            cin.ignore();
            getline(cin, enteredpword);
            if(logged_in_student){
                for(auto it = L.Current_students.begin(); it != L.Current_students.end(); it++){
                    Student s = *it;
                    if(s.id == enteredid){
                        if(s.getPassword() == enteredpword){
                            cout << "Welcome " << s.getUsername() << "\n";
                            stud = it;
                            valid_id = true;
                            break;
                        }
                        else{
                            cout << "Wrong Password, Try again\n";
                            valid_id = true;
                            i = 0;
                            break;
                        }
                    }
                }
                if(!valid_id){
                    cout << "Please enter a Valid ID\n";
                    i = 0;
                    continue;
                }
            }
            else if(logged_in_faculty){
                for(vector<Faculty>::iterator it = L.Current_faculty.begin(); it != L.Current_faculty.end(); it++){
                    Faculty s = *it;
                    if(s.id == enteredid){
                        if(s.getPassword() == enteredpword){
                            cout << "Welcome " << s.getUsername() << "\n";
                            fac = it;
                            valid_id = true;
                            break;
                        }
                        else{
                            cout << "Wrong Password, Try again\n";
                            valid_id = true;
                            i = 0;
                            break;
                        }
                    }
                }
                if(!valid_id){
                    cout << "Please enter a Valid ID\n";
                    i = 0;
                    continue;
                }
            }
            else if(logged_in_Librarian){
                for(vector<Librarian>::iterator it = L.Current_librarian.begin(); it != L.Current_librarian.end(); it++){
                    Librarian s = *it;
                    if(s.id == enteredid){
                        if(s.getPassword() == enteredpword){
                            cout << "Welcome " << s.getUsername() << "\n";
                            libraian = it;
                            valid_id = true;
                            break;
                        }
                        else{
                            cout << "Wrong Password, Try again\n";
                            valid_id = true;
                            i = 0;
                            break;
                        }
                    }
                }
            }
        }
        else if(i == 3){

            if(logged_in_student){
                // 1- 12
                
                cout << "Enter 1 for borrowing a book\nEnter 2 for returning a book\nEnter 3 for paying & viewing fine\nEnter 4 for viewing overdue books\nEnter 5 for viewing all books\nEnter 6 for logging out\nEnter 7 for viewing a particular book\nEnter 8 for viewing your Borrowed books\nEnter 9 for Searching books with title names\nEnter 10, for Viewing History Associated with this Account\nEnter 11, for viewing messages associated with this account\nEnter 12, for sending Messages\n";
                cout << "Current Time : " << Current_day() << "\n";
                cin >> input;
                if(input != "12" && input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6" && input != "7" && input != "8" && input != "9" && input != "10" && input != "11"){
                    cout << "Invalid input, Please try again\n";
                    i = 2;
                    continue;
                }
                if(input == "6"){
                    cout << "Logging out\n";
                    i = -1;
                    stud = L.Current_students.end();
                    logged_in_student = false;
                    continue;
                }
            }
            else if(logged_in_faculty){
                // 1- 11
                
                cout << "Enter 1 for borrowing a book\nEnter 2 for returning a book\nEnter 3 for viewing overdue books\nEnter 4 for viewing all books\nEnter 5 for logging out\nEnter 6 for viewing a particular book\nEnter 7 for viewing your Borrowed books\nEnter 8 for Searching books via Title name\nEnter 9, for viewing History Associated with this Account\nEnter 10, to view Messages associated with this account\nEnter 11 to send Messages\n";    
                cout << "Current Time : " << Current_day() << "\n";
                cin >> input;
                if(input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6" && input != "7" && input != "8" && input != "9" && input != "10" && input != "11"){
                    cout << "Invalid input, Please try again\n";
                    i = 2;
                    continue;
                }
                if(input == "5"){
                    cout << "Logging out\n";
                    i = -1;
                    fac = L.Current_faculty.end();
                    logged_in_faculty = false;
                    continue;
                }
            }
            else if(logged_in_Librarian){
                //1 - 14
                
                cout << "Enter 1 for adding a user\nEnter 2 for changing user status\nEnter 3 for adding a book\nEnter 4 for changing book status\nEnter 5 for viewing all students\nEnter 6 for viewing all faculty\nEnter 7 for viewing all books\nEnter8 for logging out\nEnter 9 for viewing a particular book\nEnter 10 for viewing a particular student\nEnter 11 for viewing a particular faculty\nEnter 12 for Adding a New Librarian\nEnter 13 for viewing Messages\nEnter 14, for Sending Messages";
                cout << "\nCurrent Time : " << Current_day() << "\n";
                cin >> input;   
                if(input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6" && input != "7" && input != "8" && input != "9" && input != "10" && input != "11" && input != "12" && input != "13" && input != "14"){
                    cout << "Invalid input, Please try again\n";
                    i = 2;
                    continue;
                }
                if(input == "8"){
                    cout << "Logging out\n";
                    i = -1;
                    libraian = L.Current_librarian.end();
                    logged_in_Librarian = false;
                    continue;
                }
            }
        }
        else if(i == 4){
            if(logged_in_student){
                if(input == "1"){
                    cout << "Enter the book id you want to borrow\n";
                    int id;
                    cin >> id;
                    stud->BorrowBook(id, L.Current_books);
                }
                else if(input == "2"){
                    cout << "Enter the book id you want to return\n";
                    int id;
                    cin >> id;
                    stud->RuturnBook(id, L.Current_books);
                }
                else if(input == "3"){
                    cout << "Your fine amount is " << stud->FineToPay() << "\n";
                    cout << "Enter the amount you want to pay, U can also choose to pay 0 fine\n";
                    int amt;
                    cin >> amt;
                    stud->PayFine(amt);
                }
                else if(input == "4"){
                    stud->ShowOverdue();
                }
                else if(input == "5"){
                    L.ViewAllBooks();
                }
                else if(input == "7"){
                    cout << "Enter the book id you want to view\n";
                    int id;
                    cin >> id;
                    viewBook_bare_minimum(id, L.Current_books);
                }
                else if (input == "8"){

                    for(Book b : stud->Currently_Borrowed_books){
                        view(b);
                    }
                    if(stud->Currently_Borrowed_books.size() == 0){
                        cout << "NO BOOKS BORROWED\n";
                    }
                }
                else if(input == "9"){
                    cin.ignore();
                    string TITLE;
                    getline(cin, TITLE);
                    L.SearchBookViaTitle(TITLE);
                }
                else if(input == "10"){
                    stud->DisplayHistory(L.Current_books);
                }
                else if(input == "11"){
                    stud->ViewMessages();
                }
                else if(input == "12"){
                    cout << "Enter the ID to whom you want to Send Message\n";
                    int id;
                    cin >> id;
                    cout << "Enter the message, please don't include commas , : and ; in your message\n";
                    cin.ignore();
                    string massage;
                    getline(cin, massage);
                    L.SendMessage(stud->getUsername(), id, massage);
                    // stud->SendMessage(id, massage, L.Current_students, L.Current_faculty, L.Current_librarian);
                }
                i = 2;
            }
            else if(logged_in_faculty){
                // cout << "Enter 1 for borrowing a book\nEnter 2 for returning a book\nEnter 3 for viewing overdue books\n
                // Enter 4 for viewing all books\nEnter 5 for logging out\nEnter 6 for viewing a particular book\n";
                if(input == "1"){
                    cout << "Enter the id of the book which you want to borrow\n";
                    int id;
                    cin >> id;  
                    fac->BorrowBook(id, L.Current_books);
                }
                else if(input == "2"){
                    cout << "Enter the id of the book which you want to return\n";
                    int id;
                    cin >> id;
                    fac->ReturnBook(id, L.Current_books);
                }
                else if(input == "3"){
                    fac->ShowOverdues();
                }
                else if(input == "4"){
                    L.ViewAllBooks();
                }
                else if(input == "6"){
                    cout << "Enter the book id you want to view\n";
                    int id;
                    cin >> id;
                    viewBook_bare_minimum(id, L.Current_books);
                }
                else if(input == "7"){
                    for(Book b : fac->Currently_Borrowed_books){
                        view(b);
                    }
                    if(fac->Currently_Borrowed_books.size() == 0){
                        cout << "NO BOOKS BORROWED\n";
                    }
                }
                else if(input == "8"){
                    cin.ignore();
                    string TITLE;
                    getline(cin, TITLE);
                    L.SearchBookViaTitle(TITLE);
                }
                else if(input == "9"){
                    fac->DisplayHistory(L.Current_books);
                }
                else if(input == "10"){
                    fac->ViewMessages();
                }
                else if(input == "11"){
                    cout << "Enter the ID to whom you want to Send Message\n";
                    int id;
                    cin >> id;
                    cout << "Enter the message, please don't include commas , : and ; in your message\n";
                    cin.ignore();
                    string massage;
                    getline(cin, massage);
                    L.SendMessage(fac->getUsername(), id, massage);
                    // fac->SendMessage(id, massage, L.Current_students, L.Current_faculty, L.Current_librarian);
                }
                
                i = 2;
            }
            else if(logged_in_Librarian){
                //1 - 12
                if(input == "1"){
                    cout << "Enter the role of the user you want to add(STUDENT, FACULTY)\n";
                    string role;
                    cin.ignore();
                    getline(cin, role);
                    cout << "Enter the username of the user you want to add\n";
                    string username;
                    // cin >> username;
                    getline(cin, username);
                    cout << "Enter the password of the user you want to add\n";
                    string password;
                    // cin >> password;
                    getline(cin, password);
                    libraian->AddUser(role, username, password, L.Current_students, L.Current_faculty);
                }
                else if(input == "2"){
                    cout << "Enter the ID of the user whose status you want to change, i.e change to DELETE or ACTIVATE or DISABLE\n";
                    int ID;
                    cin >> ID;
                    cout << "Enter the status you want to change to (DELETED, ACTIVE, DISABLED)\n";
                    string status;
                    cin.ignore();
                    getline(cin, status);
                    transform(status.begin(), status.end(), status.begin(), ::toupper);
                    libraian->ChangeUserStatus(ID, status, L.Current_students, L.Current_faculty);
                }
                else if(input == "3"){
                    cout << "Enter the publisher of the book you want to add\n";
                    string publisher;
                    cin.ignore();
                    getline(cin, publisher);
                    cout << "Enter the title of the book you want to add\n";
                    string title;
                    getline(cin, title);
                    cout << "Enter the author of the book you want to add\n";
                    string author;
                    getline(cin, author);
                    cout << "Enter the year of the book you want to add\n";
                    string year;
                    getline(cin, year);
                    cout << "Enter the ISBN of the book you want to add\n";
                    string ISBN;
                    getline(cin, ISBN);
                    libraian->AddBook(publisher, title, author, year, ISBN, L.Current_books);
                }
                else if(input == "4"){
                    cout << "Enter the id of the book whose status you want to change\n";
                    int id;
                    cin >> id;
                    cout << "Enter the status you want to change to, (AVAILABLE, DISABLED, DELETE)\n";
                    string status;
                    cin >> status;
                    transform(status.begin(), status.end(), status.begin(), ::toupper);
                    libraian->ChangeBookStatus(id, status, L.Current_books);
                }
                else if(input == "5"){
                    L.ViewAllStudents();
                }
                else if(input == "6"){
                    L.ViewAllFaculty();
                }
                // cout << "Enter 1 for adding a user\nEnter 2 for changing user status\nEnter 3 for adding a book\nEnter 4 for changing book status\nEnter 5 for viewing all students\nEnter 6 for viewing all faculty\nEnter 7 for viewing all books\nE
                // nter8 for logging out\nEnter 9 for viewing a particular book\nEnter 10 for viewing a particular student\nEnter 11 for viewing a particular faculty\n";
                else if(input == "7"){
                    L.ViewAllBooks();
                }
                else if(input == "9"){
                    cout << "Enter the book id you want to view\n";
                    int id;
                    cin >> id;
                    viewBook_bare_minimum(id, L.Current_books);

                }
                else if(input == "10"){
                    cout << "Enter the student id you want to view\n";
                    int id;
                    cin >> id;
                    bool viewed = false;
                    for(Student s : L.Current_students){
                        if(s.id == id){
                            cout << "----------------------------------------------------------------------------------------------------------\n";
                            cout << setw(setwforint) << "ID" << setw(setwforString) << "USERNAME" << setw(setwforString) << "STATUS" << setw(setwforint+10) << "Createat" << setw(setwforint+5) << "FINE" << "      " << "BORROWED BOOKS\n";
                            cout << "----------------------------------------------------------------------------------------------------------\n";
                            view(s);
                            viewed = true;
                            
                        }
                    }
                    if(!viewed){
                        cout << "Enter a valid student id\n";
                    }
                }
                else if(input == "11"){
                    cout << "Enter the faculty id you want to view\n";
                    int id;
                    cin >> id;
                    bool viewed = false;
                    for(Faculty f : L.Current_faculty){
                        if(f.id == id){
                            cout << "----------------------------------------------------------------------------------------------------------\n";
                            cout << setw(setwforint) << "ID" << setw(setwforString) << "USERNAME" << setw(setwforString) << "STATUS" << "        " << "BORROWED BOOKS\n";
                            cout << "----------------------------------------------------------------------------------------------------------\n";
                            view(f);
                            viewed = true;
                           
                        }
                    }
                    if(!viewed){
                        cout << "Enter a valid faculty id\n";
                    }
                }
                else if(input == "12"){
                    cout << "Enter the username of the librarian you want to add\n";
                    string username;
                    cin.ignore();
                    getline(cin, username);
                    cout << "Enter the password of the librarian you want to add\n";
                    string password;
                    getline(cin, password);
                    libraian->AddLibrarian(username, password, L.Current_librarian);
                }
                else if(input == "13"){
                    libraian->ViewMessages();
                }
                else if(input == "14"){
                    cout << "Enter the ID to whom you want to Send Message\n";
                    int id;
                    cin >> id;
                    cout << "Enter the message, please don't include commas , : and ; in your message\n";
                    cin.ignore();
                    string massage;
                    getline(cin, massage);
                    L.SendMessage(libraian->getUsername(), id, massage);
                    // libraian->SendMessage(id, massage, L.Current_students, L.Current_faculty, L.Current_librarian);
                }

                i = 2;  
            }

        }
    }
    return 0;
}

