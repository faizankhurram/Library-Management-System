#include <iostream>
#include <unistd.h>     //for the sleep function
#include <windows.h>    //for the cls function
#include <vector>
using namespace std;

class Library{
private:
    string title, publisher, isbn;
    vector<string> authors;
    float price;
    int copies;
    static int totalbooks;
public:
    //default constructor
    Library() : price(0.0) , copies(0) {}

    //getters
    string getTitle(void) const;
    string getPublisher(void) const;
    string getIsbn(void) const;
    float getPrice(void) const;
    int getCopies(void) const;
    void getAuthors(void) const;

    //setters
    void setTitle(string title);
    void setPublisher(string publisher);
    void setIsbn(string isbn);
    void setPrice(float price);
    void setCopies(int copies);
    void setAuthors(void);

    //methods (features)
    void addBook(void);
    void showBookInfo(void) const;
    void searchBook(string tag, vector<Library> bookArr);
    void lendBook(string tag, vector<Library> &bookArr, vector<Library> &userBooks);
    void showLendedBookInfo(vector<Library> userBooks) const;
    void showLibraryBookInfo(vector<Library> bookArr) const;
    void showLendedBookCount(vector<Library> userBooks) const;
    void removeFromLibrary(string tag, vector<Library> &bookArr);
    void removeFromAccount(string tag, vector<Library> &userBooks);
    static void showLibraryBookCount(void);
    static void showMenu(void);
};

string Library :: getTitle(void) const{
    return title;
}
string Library :: getPublisher(void) const{
    return publisher;
}
string Library :: getIsbn(void) const{
    return isbn;
}
float Library :: getPrice(void) const{
    return price;
}
int Library :: getCopies(void) const{
    return copies;
}
void Library :: getAuthors(void) const{
    for(int i = 0; i < authors.size(); i++){
        cout << "\nAuthor # " << i + 1 << " : " << authors[i] << "";
    }
}

void Library :: setTitle(string title){
    this -> title = title;
}
void Library :: setPublisher(string publisher){
    this -> publisher = publisher;
}
void Library :: setIsbn(string isbn){
    this -> isbn = isbn;
}
void Library :: setPrice(float price){
    this -> price = price;
}
void Library :: setCopies(int copies){
    this -> copies = copies;
}
void Library :: setAuthors(void){
    int n;

    cout << "\nEnter the number of authors for your book: ";
    cin >> n;

    for(int i = 0; i < n; i++){
        string authorname;
        cout << "\nEnter the name for author # " << i + 1 << " :";
        getline(cin >> ws, authorname);
        authors.push_back(authorname);
    }
}

void Library :: addBook(void){
    string Title, Publisher, ISBN;
    float Price;
    int Copies;
    cout << "\nEnter the Title and Publisher of the book in the order mentioned:";
    getline(cin >> ws, Title); getline(cin >> ws, Publisher);
    while(true){
        cout << "\nEnter the ISBN Code for the book (13 digits and excluding hyphens):";
        getline(cin >> ws, ISBN);
        if(ISBN.length() != 13 || ISBN.find('-') != string :: npos){
            cout << "\nInvalid ISBN Code! Please refer to the order desribed.";
        }
        else{
            break;
        }
    }
    cout << "\nEnter the Price of the book: ";
    cin >> Price;
    cout << "\nEnter the total number of Copies of the book: ";
    cin >> Copies;

    this -> setTitle(Title); this -> setPublisher(Publisher); this -> setIsbn(ISBN);
    this -> setPrice(Price); this -> setCopies(Copies);
    this -> setAuthors();

    totalbooks += Copies;
}

void Library :: showBookInfo(void) const{
    cout << "\nTitle: " << title << "\nPublisher: " << publisher;
    this -> getAuthors();
    cout << "\nISBN Code: " << isbn << "\nPrice: Rupees " << price << "\nCopies Available: " << copies << endl;
}

void Library :: searchBook(string tag, vector<Library> bookArr){
    bool found = false;
    for(auto &book : bookArr){
        if((book.title == tag || book.isbn == isbn) && book.copies > 0){
            book.showBookInfo(); sleep(8); found = true; break;
        }
    }
    if(!found){
        cout << "\nSorry! The book with the provided search tag does not exist!"; sleep(3);
    }
}

void Library :: lendBook(string tag, vector<Library> &bookArr, vector<Library> &userBooks){
    bool found = false;
    for(auto &book : bookArr){
        if((book.title == tag || book.isbn == tag) && book.copies > 0){
            int n = 0;

            while(true){
                cout << "\nEnter the number of copies of the book you want to lend: ";
                cin >> n;
                if(n < 0){
                    cout << "\nInvalid input.";
                }
                else if(n > book.copies){
                    cout << "\nYou cannot lend more than the number of copies of the book (" << book.copies << ")";
                }
                else{
                    break;
                }
            }
            userBooks.push_back(book); userBooks[userBooks.size() - 1].copies = n; book.copies -= n; totalbooks -= n;
            found = true; break;
        }
    }
    if(!found){
        cout << "\nSorry! The book with the provided search tag does not exist!"; sleep(2);
    }
    else{
        cout << "\nThe required book has been successfully added into your account!"; sleep(2);
    }
}

void Library :: showLendedBookInfo(vector<Library> userBooks) const{
    bool found = false;
    for(auto &book : userBooks){
        if(book.copies > 0){
            book.showBookInfo(); found = true; sleep(7); cout << endl << endl;
        }
    }
    if(!found){
        cout << "\nYou have not lended any book yet!"; sleep(2);
    }
}

void Library :: showLibraryBookInfo(vector<Library> bookArr) const{
    bool found = false;
    for(auto &book : bookArr){
        if(book.copies > 0){
            book.showBookInfo(); found = true; sleep(7); cout << endl << endl;
        }
    }
    if(!found){
        cout << "\nThe library does not have any books yet!"; sleep(2);
    }
}

void Library :: showLendedBookCount(vector<Library> userBooks) const{
    int total = 0;
    for(auto &book : userBooks){
        total += book.copies;
    }
    cout << "\nThe total number of lended books are: " << total << endl; sleep(2);
}

void Library :: removeFromLibrary(string tag, vector<Library> &bookArr){
    bool found = false;
    for(auto &book :bookArr){
        if((book.title == tag || book.isbn == tag) && book.copies > 0){
            totalbooks -= book.copies; book.copies = 0; found = true; break;
        }
    }
    if(!found){
        cout << "\nThe required book does not exist in the library!"; sleep(2);
    }
    else{
        cout << "\nThe required book has been successfully removed from the library!"; sleep(2);
    }
}

void Library :: removeFromAccount(string tag, vector<Library> &userBooks){
    bool found = false;
    for(auto &book : userBooks){
        if((book.title == tag || book.isbn == tag) && book.copies > 0){
            book.copies = 0; found = true; break;
        }
    }
    if(!found){
        cout << "\nThe required book does not exist in our account!"; sleep(2);
    }
    else{
        cout << "\nThe required book has been successfully removed from your account!"; sleep(2);
    }
}

int Library :: totalbooks = 0;

void Library :: showLibraryBookCount(void){      //static member function
    cout << "\nThe total number of books in the library are: " << totalbooks << endl; sleep(2);
}

void Library :: showMenu(void){                  //static member function
    cout << "\n------Welcome to the Library Management System------";
    cout << "\n\n1. Add a Book" << "\n2. Search by ISBN or Title" << "\n3. Lend a Book" << "\n4. Check Library Book Count";
    cout << "\n5. See all Library Books" << "\n6. Check Lended Book Count" << "\n7. See all Lended Books";
    cout << "\n8. Remove a Book (Library)" << "\n9. Remove a Book (Account)" << "\n10. Exit" << endl;
}

int main(void){

    vector<Library> libraryBooks, lendedBooks;

    string username;

    cout << "\nPlease enter your username:";
    getline(cin >> ws, username);
    sleep(1);

    while(true){
        system("cls");
        Library :: showMenu();
        sleep(4);

        int choice = 0;
        while(true){        //here we keep taking the choice as input as long as it is invalid
            cout << "\nEnter your choice from the above menu: ";
            cin >> choice;
            if(choice >= 1 && choice <= 10){
                break;
            }
            cout << "\nInvalid choice entered!"; choice = 0;
        }

        sleep(2);
        system("cls");

        Library dummy;
        string search_tag;

        //not implementing a switch-case because I hate it

        if(choice == 1){
            dummy.addBook();
            sleep(1);
            libraryBooks.push_back(dummy);
            cout << "\nThe book has been successfully added into the Library!"; sleep(3);
        }
        else if(choice == 2){
            cout << "\nEnter the ISBN or Title of the book you want to search for:";
            getline(cin >> ws, search_tag);

            dummy.searchBook(search_tag, libraryBooks);   
        }
        else if(choice == 3){
            cout << "\nEnter the ISBN or Title of the Book you want to lend:";
            getline(cin >> ws, search_tag);

            dummy.lendBook(search_tag, libraryBooks, lendedBooks);
        }
        else if(choice == 4){
            Library :: showLibraryBookCount(); sleep(3);
        }
        else if(choice == 5){
            dummy.showLibraryBookInfo(libraryBooks);
        }
        else if(choice == 6){
            dummy.showLendedBookCount(lendedBooks); sleep(3);   
        }
        else if(choice == 7){
            dummy.showLendedBookInfo(lendedBooks);
        }
        else if(choice == 8){
            cout << "\nEnter the ISBN or Title of the book you want to remove from the library:";
            getline(cin >> ws, search_tag);
            dummy.removeFromLibrary(search_tag, libraryBooks);
        }
        else if(choice == 9){
            cout << "\nEnter the ISBN or Title of the book you want to remove from your account:";
            getline(cin >> ws, search_tag);
            dummy.removeFromAccount(search_tag, lendedBooks);   
        }
        else{
            cout << "Thankyou for spending your time in the Library, " << username << "! Do visit again!"; sleep(3); break;
        }
    }
    
    return 0;
}