# LibraryManagementSystem

## Overview
Self Project

## Installation
1. Clone the repository:
    ```terminal
    git clone https://github.com/vatsal1021/Library-Management-System.git
    ```
2. Navigate to the project directory:

3. Compile the code and build an executable file using(although it already is included in the repo, so you may choose to skip this step)
    ```terminal
    g++ -o g Library_management.cpp
    ```
4. Run the Executable file using
    ```terminal
    ./g
    ```

## Project Structure
The repository is organized as
- `books.txt` : This is a txt file, which contains Information about all the books available.It contains columns as follows, all the columns are seperated by ','. `id`, `title`, `author`, `publisher`, `year`, `ISBN`, `Created_at`, `status`, `Borrowedby`, `Borrowed_when`, `borrowhistory(id, #of days borrowed)`,
- `students.txt` : This is a txt file, which contains Information about all the Students available.It contains columns as follows, all the columns are seperated by ','. `id`, `Username`, `Password`, `Status`, `Created_at`, `Fine`, `Paid`,;`Messages`;
- `faculty.txt` : This is a txt file, which contains Information about all the Faculties available.It contains columns as follows, all the columns are seperated by ','. `id`, `Username`, `Password`, `Status`, `Created_at`,;`Messages`;
- `librarian_data.txt` : This is a txt file, which contains Information about all the Faculties available.It contains columns as follows, all the columns are seperated by ','. `id`, `Username`, `Password`,;`Messages`;

- `classes.cpp` : This contains all the classes implemented in the assignment, they are
    - `Book` class:
        -Attributes : id, title, author, publisher, year, ISBN, Created_at, status(AVAILABLE, DISABLED(Reserved),   BORROWED ), BorrowedBy(empty string if not borrowed), Borrowed_at(-1 if not borrowed currently), BorrowHistory(`vector<pair<ID, #of days borrowed>>`)
        -Functions : Constructor  
    - `User` class:
        -Base class for Student, Faculty and Librarian.
        -Attributes : id, username, password, role, status(Active, Disabled), Messages(`vector<pair<Username_to_whom_message_was_sent, Actual_message>>`), Created_at.
        -Fucntions : Fucntions to set all the attributes, View Messages sent to this user, Display Borrow History for this user
        - `Student` class:
            -Attributes : (Attributes of User class) , `vector<Book> CurrentlyBorrowedBooks` , Fine, Paid.
            -Functions : PayFine(int amount), ShowFine(), BorrowBook(int idof book), ReturnBook(int id), ShowOverdueBooks().
        - `Faculty` class:
            -Attributes : (Attributes of User class), `vector<Book> CurrentlyBorrowedBooks`.
            -Fucntions : BorrowBook(), ReturnBook(), ShowOverDueBooks().
        - `Librarian` class:
            -Attributes : (Attributes of User class).
            -Functions : AddUser(), DeleteUser(), DisableUser(), AddBook(), DisableBook(), DeleteBook(), AddLibrarian().
    - `Library` class :
        -Attributes : Bookfile, studentsFile, FacultyFile, Librarianfile(These variables store the name of .txt files in which the data is to be stored and loaded from), Librarydata(Stores when the Library was last opened, helpful in Fine Calculations), `vector<Book> Curr_books`, `vector<students> Curr_students`, `vector<Faculty> Curr_faculty`, `vector<Librarian> curr_librarian`.
        -Functions : Function to view change Books, student, Faculty files , SendMessage(), SearchBooks(), SearchStudents(), SearchFaculty(), LoadData(from the .txt files), SaveData(write back into .txt).

    - `Few general Fucntions` :
        -Current_day() : calculates number of days elapsed since 7th March, 2025. Helps in calculating Fine.(For testing put, 1 day = 1 minute, To change this go to classes.cpp -> change oneDay to 60(Line 47)).
        -view() : Function overloaded to view Student, Faculty and Book.


## State Right Now
Right Now, the Database has 5 Students, 5 Books, 5Faculties and 3 librarians.
Books.txt Looks like
### BOOKS.TXT
| ID  | Title                          | Author               | Publisher        | Year | ISBN         | Created_at | Status    | Borrowed by | Borrowed at | History |
|---- |------------------------------|---------------------|-----------------|------|-------------|------------|----------|-------------|-------------|---------|
| 1   | Quantum Cryptography         | Cormen              | IITK            | 1990 | 12345654321  | 0          | AVAILABLE |             | -1          | 2,0     |
| 2   | Ramyana A Saga               | Valmiki             | Pearson         | 1050 | 2456909      | 0          | AVAILABLE |             | -1          |         |
| 4   | Mastering DSA                | Thomas H            | Harvard         | 2000 | 1289008921   | 0          | BORROWED  | stud 1      | 0           |         |
| 5   | Predicting The Future        | P K Kelkar          | IITK            | 1970 | 567898765    | 0          | AVAILABLE |             | -1          |         |
| 6   | Dictionary                   | Some Prof in Oxford | Oxford          | 1950 | 45667654     | 0          | AVAILABLE |             | -1          |         |
| 7   | Maintaining Clean Code       | Robert C. Martin    | Prentice Hall   | 2008 | 123654321    | 0          | AVAILABLE |             | -1          |         |
| 8   | The Pragmatic Programmer     | Andrew Hunt        | Addison-Wesley  | 1999 | 9780201616224| 0          | AVAILABLE |             | -1          |         |
| 9   | Artificial Intelligence      | Stuart Russell      | Pearson         | 2020 | 9780134610993| 0          | AVAILABLE |             | -1          |         |
| 10  | The Art of Computer Programming | Donald Knuth  | Addison-Wesley  | 1968 | 9780201896831| 0          | AVAILABLE |             | -1          |         |
| 11  | Deep Learning                | Ian Goodfellow      | MIT Press       | 2016 | 9780262035613| 0          | AVAILABLE |             | -1          |         |

### STUDENTS.TXT
| ID  | USERNAME | PASSWORD | STATUS  | Created_at | FINE | PAID | BorrowedBooks | MESSAGE                   |
|---- |---------|---------|-------- |------------|------|------|---------------|---------------------------|
| 2   | stud 1  | Pass1   | ACTIVE  | 0          | 0    | 0    | 4             | admin: Please Clear Dues  |
| 3   | stud 2  | pass2   | ACTIVE  | 0          | 0    | 0    |               |                           |
| 4   | stud 3  | Pass3   | ACTIVE  | 0          | 0    | 0    |               |                           |
| 5   | Stud 4  | Pass4   | ACTIVE  | 0          | 0    | 0    |               |                           |
| 6   | stud 5  | Pass5   | ACTIVE  | 0          | 0    | 0    |               |                           |


### FACULTY.txt
| ID  | USERNAME | PASSWORD | STATUS  | Created_at | Borrowed_books | MESSAGES |
|---- |---------|---------|-------- |------------|---------------|----------|
| 7   | fac1    | pass1   | ACTIVE  | 0          |               |          |
| 8   | fac2    | pass2   | ACTIVE  | 0          |               |          |
| 9   | fac3    | pass3   | ACTIVE  | 0          |               |          |
| 10  | fac4    | pass4   | ACTIVE  | 0          |               |          |
| 11  | fac5    | pass5   | ACTIVE  | 0          |               |          |

### LIBRARIAN.txt
| ID  | USERNAME  | PASSWORD  | MESSAGES                        |
|---- |----------|-----------|--------------------------------|
| 0   | admin    | 1234      | stud 1: Ok maam I will clear it |
| 12  | Admin2   | 12345678  |                                |
| 13  | admin 3  | password 3 |                                |

Student1 had borrowed book ID#1 previously, and returned it. He currently Now has borrowed Book ID#4.
There was a conversation between admin1 and Student 1 about his dues, which can be seen by either of them upon login.


## Assumptions

- A Librarian Can delete a User only if he doesn't have any Borrowed Books.
- A Librarian Can delete a Book only if it isn't Borrowed or Disabled(Reserved).
- Only a Librarian can Register a User or Faculty.
- A Student can't borrow/Return books if there is a pending fine on him, He can only do so by first clearing the fine.
- Anyone can send messages to anyone.
- If a Librarian Reserves a book, it means that no one can Borrow that book i.e the book stays in Library only.
- All the other Assumptions stated in the Implementation instructions.

## Author
- Vatsal Mittal
- IITK 
- 231127
