#include<bits/stdc++.h>

#include<unistd.h>

#include <thread>

#include <chrono>

#include<ctime>

using namespace std;

class Book {
  private:
    string title;
  string author;
  string ISBN;
  string Publication;
  int status;
  string issued_user;
  int dd;
  int mm;
  int yy;
  int due_dd;
  int due_mm;
  int due_yy;
  time_t due_now;

  public:
    Book() {

    }

  Book(string title, string author, string ISBN, string Publication) {
    this -> title = title;
    this -> author = author;
    this -> ISBN = ISBN;
    this -> Publication = Publication;
    status = 0;
    issued_user = "";
  }
  void Book_request() {
    if (status == 1) {
      cout << "Book is already issued to someone" << endl;
    } else {
      status = 1;
      time_t now = time(0);
      tm * ltm = localtime( & now);
      dd = ltm -> tm_mday;
      mm = 1 + ltm -> tm_mon;
      yy = 1900 + ltm -> tm_year;
      cout << "This book is issued to you successfully" << endl;
    }
  };
  void show_duedate() {
    cout << "due_date " << due_dd << "/" << due_mm << "/" << due_yy << endl;
  };
  void setDueDate(time_t now, int d, int m, int y) {
    due_now = now;

    due_dd = d;
    due_mm = m;
    due_yy = y;
  }
  void return_book() {
    status = 0;
  }

  string get_title() {
    return title;
  }
  string get_author() {
    return author;
  }
  string get_ISBN() {
    return ISBN;
  }
  string get_publication() {
    return Publication;
  }
  string get_issued_user() {
    return issued_user;
  }
  int get_status() {
    return status;
  }
  void set_title(string name) {
    title = name;
  }
  void set_author(string author) {
    this -> author = author;
  }
  void set_ISBN(string ISBN) {
    this -> ISBN = ISBN;
  }
  void set_publication(string Publication) {
    this -> Publication = Publication;
  }
  void set_issued_user(string issued_user) {
    this -> issued_user = issued_user;
  }
  void set_status(int status) {
    this -> status = status;
  }

  time_t get_due_now() {
    return due_now;
  }

};

class book_database {
  private:
    map < string, Book > db;
  public:
    void add(Book book) {
      if (db.find(book.get_title()) != db.end()) {
        cout << "You can't add a book already added" << endl;
      } else {
        db.insert({
          book.get_title(),
          book
        });
      }
    }
  void update(string title) {
    if (db.find(title) == db.end()) {
      cout << "This book is not present in Library" << endl;
    } else if (db.find(title) -> second.get_status()) {
      cout << "Currently book is issued to someone and Can't its detials can't be updated untill the book returns to the library" << endl;
    } else {
      string author;
      string ISBN;
      string Publication;

      cout << "Enter author: ";

      getline(cin, author, '\n');
      cout << "Enter ISBN number: ";
      getline(cin, ISBN, '\n');
      cout << "Enter Publication: ";
      getline(cin, Publication, '\n');
      Book book(title, author, ISBN, Publication);
      db[title] = book;
    }
  }
  void Delete(string title) {
    if (db.find(title) == db.end()) {
      cout << "This book is already not present in the library" << endl;
    } else {
      db.erase(title);
    }
  };

  void Deletel(string title) {
    if (db.find(title) == db.end()) {
      cout << "This book is already not present in the library" << endl;
    } else if (db.find(title) -> second.get_status()) {
      cout << "Currently book is issued to someone and Can't be removed while issued" << endl;
    } else {
      db.erase(title);
    }
  };

  int exists(string title) {
    if (db.find(title) != db.end()) {
      return 1;
    } else {
      return 0;
    }
  }
  Book extract(string title) {
    return db[title];
  }
  void display() {
    int count = 1;
    for (auto i = db.begin(); i != db.end(); i++) {
      cout << "Book no. " << count << "\n\nTitle: " << i -> second.get_title() << "\n\nauthor: " << i -> second.get_author() << endl << endl;
      if (i -> second.get_status()) {
        cout << "This book is issued to " << i -> second.get_issued_user() << " with ";
        i -> second.show_duedate();
        cout << endl;
      } else {
        cout << "This book is currently available for issuing" << endl;
      }
      count++;
      cout << "-------------------------------------------------" << endl;
    }
  }

  void display(string username) {
    int count = 1;
    for (auto i = db.begin(); i != db.end(); i++) {
      if (i -> second.get_status() && i -> second.get_issued_user() == username) {
        cout << "Book no. " << count << "\n\nTitle of the book : " << i -> second.get_title() << "\nauthor: " << i -> second.get_author() << endl;
        count++;
        cout << "-------------------------------------------------" << endl;
      }

    }
  }
};
class User {
  protected:
    string name;
  string username;
  string password;
  int role;
  string type;
  map < string, Book > collection;
  int issued_number;
  public:
    User() {
      issued_number = 0;
    }

  User(string name, string password, string username, int role, string type) {
    this -> name = name;
    this -> username = username;
    this -> password = password;
    this -> role = role;
    this -> type = type;
    this -> issued_number = 0;
  }

  void display() {
    cout << issued_number << endl;
    int count = 1;
    for (auto i: collection) {
      cout << count << " Book : " << i.second.get_title() << " author : " << i.second.get_author() << " " << i.second.get_status() << "\n" << flush;
      count++;
    }
  }

  string get_username() {
    return username;
  }

  string get_name() {
    return name;
  }

  int get_role() {
    return role;
  }
  string get_type() {
    return type;
  }

  int get_issued_number() {
    return issued_number;
  }

  Book get_book(string title) {
    return collection[title];
  }

  void set_username(string username) {
    this -> username = username;
  }

  void set_name(string name) {
    this -> name = name;
  }

  void set_type(string type) {
    this -> type = type;
  }

  void set_role(int role) {
    this -> role = role;
  }
  void set_book(Book & book) {
    this -> collection[book.get_title()] = book;
  }
  void set_issued_number(int number) {
    this -> issued_number = number;
  }

  string get_password() {
    return password;
  }

  void delete_book(string title) {
    collection.erase(title);
  }

  map < string, Book > get_collection() {
    return collection;
  }

  void increment_issued_number() {
    issued_number++;
  }

  void decrement_issued_number() {
    issued_number--;
  }

};

class Professor: public User {
  private: long long pending_fine;
  public: Professor() {
    pending_fine = 0;
    type = "Professor";
    role = 2;
  }
  Professor(string name, string password, string username) {
    this -> name = name;
    this -> username = username;
    this -> password = password;
    this -> role = 2;
    this -> type = "Professor";
    this -> issued_number = 0;
    this -> pending_fine = 0;

  }
  int calculate_fine() {
    cout << "prof 5\n" << flush;
    time_t now = time(0);
    long long t_days = 0;
    for (auto itr: collection) {
      time_t diff = now - itr.second.get_due_now();
      long long days = diff / 86400;
      days = max(0ll, days - 60);
      t_days += days;
    }
    return 5 * t_days + pending_fine;

  }
  int calculate_fine_on_return(string title) {
    cout << "prof 5 return\n" << flush;
    time_t now = time(0);
    long long t_days = 0;
    auto itr = * collection.find(title);

    time_t diff = now - itr.second.get_due_now();
    long long days = diff / 86400;
    days = max(0ll, days - 60);
    t_days += days;

    return 5 * t_days;
  }

  int get_pending_fine() {

    return pending_fine;
  }

  void set_pending_fine(int pendin_fine) {
    this -> pending_fine = pendin_fine;
  }

};

class Student: public User {
  private: long long pending_fine;
  public: Student() {
    pending_fine = 0;
    issued_number = 0;
    type = "Student";
    role = 1;
  }
  int calculate_fine() {
    time_t now = time(0);
    long long t_days = 0;
    for (auto itr: collection) {
      time_t diff = now - itr.second.get_due_now();
      long long days = diff / 86400;
      days = max(0ll, days - 30);
      t_days += days;

    }
    return 2 * t_days + pending_fine;

  }
  int calculate_fine_on_return(string title) {
    time_t now = time(0);
    long long t_days = 0;
    auto itr = * collection.find(title);

    time_t diff = now - itr.second.get_due_now();
    long long days = diff / 86400;
    days = max(0ll, days - 60);
    t_days += days;

    return 2 * t_days;
  }
  int get_pending_fine() {

    return pending_fine;
  }

  void set_pending_fine(int pendin_fine) {
    this -> pending_fine = pendin_fine;
  }

  Student(string name, string password, string username) {
    this -> name = name;
    this -> username = username;
    this -> password = password;
    this -> role = 1;
    this -> type = "Student";
    this -> issued_number = 0;
    this -> pending_fine = 0;

  }

};

class Librarian: public User {
  public: Librarian() {
    type = "Librarian";
    role = 3;
  }
  Librarian(string name, string password, string username) {
    this -> name = name;
    this -> username = username;
    this -> password = password;
    this -> role = 3;
    this -> type = "Librarian";

  }
};

class user_database {
  private:
    map < string, User > db;
  map < string, Student > db_student;
  map < string, Professor > db_prof;
  map < string, Librarian > db_lib;

  public:
    void add(User user) {
      db[user.get_username()] = user;
    }
  void delete_user(string username) {
    db.erase(username);
  }
  void add_student(Student user) {
    db_student[user.get_username()] = user;
  }
  void delete_student(Student user) {
    db_student.erase(user.get_username());
  }

  void delete_student(string username) {
    db_student.erase(username);
  }

  void add_prof(Professor user) {
    db_prof[user.get_username()] = user;
  }
  void delete_prof(Professor user) {
    db_prof.erase(user.get_username());
  }
  void delete_prof(string username) {
    db_prof.erase(username);
  }
  void add_librarian(Librarian user) {
    db_lib[user.get_username()] = user;
  }
  void delete_librarian(string username) {
    db_lib.erase(username);
  }
  void display() {
    int count = 1;
    for (auto i: db) {
      cout << "User no: " << count << endl;
      cout << "Name : " << i.second.get_name() << "\nUsername: " << i.second.get_username() << "\nUser Type: " << i.second.get_type() << "\n";

      cout << "----------------------------------------------" << endl;
      count++;
    }
  }
  int exists(string username) {
    if (db.find(username) != db.end()) {
      return 1;
    } else {
      return 0;
    }
  }
  User extract(string username) {
    return db[username];
  }

  Student extract_student(string username) {
    return db_student[username];
  }

  Professor extract_prof(string username) {
    return db_prof[username];
  }

  Librarian extract_librarian(string username) {
    return db_lib[username];
  }

};

void Initializating_db(book_database & book_db, user_database & user_db) {
  cout << "Enter number of books in the library: ";
  int num = 0;
  string nu;
  cin >> nu;
  while (1) {
    int f = 1;
    for (int i = 0; i < nu.length(); i++) {
      if (nu[i] - '0' < 0 || nu[i] - '0' > 9) {
        f = 0;
        break;
      }
    }
    if (f) {
      break;
    }
    cout << "Please enter a valid number" << endl;
    cin >> nu;
  }
  long long mul = 1;
  for (int j = 0; j < nu.length(); j++) {
    num += (nu[nu.length() - j - 1] - '0') * mul;
    mul *= 10;
  }
  int index = 1;
  string title;
  string author;
  string ISBN;
  string Publication;
  while (num--) {
    system("clear");
    cout << "Enter the details of book " << index << "\n";
    cout << "Enter Title: ";
    if (index == 1) {
      cin.ignore();
    }
    getline(cin, title, '\n');
    cout << "Enter author: ";
    getline(cin, author, '\n');
    cout << "Enter ISBN number: ";
    getline(cin, ISBN, '\n');
    cout << "Enter Publication: ";
    getline(cin, Publication, '\n');
    index++;
    Book book(title, author, ISBN, Publication);
    book_db.add(book);

  }
  cout << endl;
  book_db.display();
  system("clear");
  cout << "Enter number of users in the library: ";
  cin >> nu;
  num = 0;
  while (1) {
    int f = 1;
    for (int i = 0; i < nu.length(); i++) {
      if (nu[i] - '0' < 0 || nu[i] - '0' > 9) {
        f = 0;
        break;
      }
    }
    if (f) {
      break;
    }
    cout << "Please enter a valid number" << endl;
    cin >> nu;
  }
  mul = 1;
  for (int j = 0; j < nu.length(); j++) {
    num += (nu[nu.length() - j - 1] - '0') * mul;
    mul *= 10;
  }
  index = 1;
  string name;
  string username;
  string password;
  string confirm;
  int role;
  string roles;
  while (num) {
    system("clear");
    cout << "Enter the details of user " << index << "\n";
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name, '\n');
    cout << "Enter Username: ";
    cin >> username;
    if (user_db.exists(username)) {
      cout << "This username is already taken please enter the details again" << endl;
      sleep(2);
      system("clear");
      continue;
    } else {

      while (1) {
        cout << "Enter password: ";
        cin >> password;
        cout << "confirm password: ";
        cin >> confirm;
        if (confirm == password) {
          break;
        }
        cout << "Passwords do not match\n";

      }
      while (1) {
        cout << "Enter role as\n1 for student\n2 for professor\n3 for librarian" << endl;
        cin >> roles;

        if (roles == "1") {
          Student student(name, password, username);
          user_db.add(student);
          user_db.add_student(student);
          break;
        } else if (roles == "2") {
          Professor prof(name, password, username);
          user_db.add(prof);
          user_db.add_prof(prof);
          break;
        } else if (roles == "3") {
          Librarian librarian(name, password, username);
          user_db.add(librarian);
          user_db.add_librarian(librarian);
          break;
        }

        cout << "Please enter one of the available options\n";

      }
      num--;

      index++;
    }
  }
  user_db.display();
  sleep(1);

}

int main() {
  system("clear");
  book_database book_db;
  user_database user_db;
  string name;
  string username;
  string password;
  string confirm;
  system("clear");
  cout << "Enter the details of super user Librarian " << "\n";
  cout << "Enter Name: ";
  getline(cin, name, '\n');
  cout << "Enter Username: ";
  cin >> username;

  while (1) {
    cout << "Enter password: ";
    cin >> password;
    cout << "confirm password: ";
    cin >> confirm;
    if (confirm == password) {
      break;
    }
    cout << "Passwords do not match\n";

  }

  Librarian librarian(name, password, username);
  user_db.add(librarian);
  user_db.add_librarian(librarian);

  system("clear");
  Initializating_db(book_db, user_db);
  system("clear");
  cout << "Now db has been initialized\n";
  system("clear");
  while (1) {

    cout << "Enter Login Credentials below:\n\n";
    string username;
    string password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    if (user_db.exists(username)) {
      auto user = user_db.extract(username);

      if (user.get_password() == password) {
        system("clear");
        cout << "You are logged in successfully\n";
        sleep(0.5);
        system("clear");
        if (user.get_role() == 1) {
          auto roled_user = user_db.extract_student(username);
          string opcode;
          while (1) {
            system("clear");
            cout << "Enter respectively as\n1 for viewing all books\n2 for viewing your books\n3 check if a book is available\n4 for issuing a book\n5 for checking pending fine\n6 for returning a book\n7 to logout\n";
            cin >> opcode;
            system("clear");
            if (opcode == "1") {
              book_db.display();

            } else if (opcode == "2") {
              book_db.display(user.get_username());

            } else if (opcode == "3") {
              string title;
              cout << "Enter Title: ";
              cin.ignore();
              getline(cin, title, '\n');
              if (book_db.exists(title) == 0 || book_db.extract(title).get_status() == 1) {
                cout << "This book is not Available for Issue\n" << flush;
              } else {
                cout << "Yes , This book is Available for Issue\n" << flush;
              }

            } else if (opcode == "4") {
              if (user.get_issued_number() == 5) {
                cout << "You are already at your limit of 5 books cant issue any more books \n" << flush;
              } else {
                string title;
                cout << "Enter Title: ";
                cin.ignore();
                getline(cin, title, '\n');
                if (book_db.exists(title) == 0 || book_db.extract(title).get_status() == 1) {
                  cout << "This book is not Available for Issue\n" << flush;
                } else {
                  time_t now = time(0);
                  now += (30 * 24 * 60 * 60);
                  tm * ltm = localtime( & now);
                  int dd = ltm -> tm_mday;
                  int mm = 1 + ltm -> tm_mon;
                  int yy = 1900 + ltm -> tm_year;
                  auto book = book_db.extract(title);
                  book_db.Delete(title);
                  book.setDueDate(now, dd, mm, yy);
                  book.Book_request();
                  book.set_issued_user(username);
                  //user.collection[title]=book;
                  user.set_book(book);
                  user.increment_issued_number();
                  book_db.add(book);

                }
              }
            } else if (opcode == "5") {
              cout << roled_user.calculate_fine() << endl;
            } else if (opcode == "6") {
              string title;
              cout << "Enter Title: ";
              cin.ignore();
              getline(cin, title, '\n');
              auto book = book_db.extract(title);
              //user.collection.erase(title);
              if (book.get_issued_user() != user.get_username()) {
                cout << "You Cant return the book you have not issued" << endl;
              } else {
                user.delete_book(title);
                user.decrement_issued_number();
                book_db.Delete(title);
                book.set_status(0);
                book_db.add(book);
                cout << "The book is returned successfully" << endl;
              }

            } else if (opcode == "7") {
              break;
            } else {
              system("clear");
              cout << "Please enter one of the available options\n";
              continue;
            }
            user_db.add(user);
            string dummy;
            cout << "Enter 0 to continue\n";
            cin >> dummy;
          }
        } else if (user.get_role() == 2) {
          string opcode;
          auto roled_user = user_db.extract_prof(username);
          while (1) {
            system("clear");
            cout << "Enter respectively as\n1 for viewing all books\n2 for viewing your books\n3 check if a book is available\n4 for issuing a book\n5 for checking pending fine\n6 for returning a book\n7 to logout\n";
            cin >> opcode;
            system("clear");
            if (opcode == "1") {
              book_db.display();
            } else if (opcode == "2") {
              book_db.display(user.get_username());

            } else if (opcode == "3") {
              string title;
              cout << "Enter Title: ";
              cin.ignore();
              getline(cin, title, '\n');
              if (book_db.exists(title) == 0 || book_db.extract(title).get_status() == 1) {
                cout << "This book is not Available for Issue\n" << flush;
              } else {
                cout << "Yes , This book is Available for Issue\n" << flush;
              }

            } else if (opcode == "4") {
              string title;
              cout << "Enter Title: ";
              cin.ignore();
              getline(cin, title, '\n');
              if (book_db.exists(title) == 0 || book_db.extract(title).get_status() == 1) {
                cout << "This book is not Available for Issue\n" << flush;
              } else {
                time_t now = time(0);
                now += (60 * 24 * 60 * 60);
                tm * ltm = localtime( & now);
                int dd = ltm -> tm_mday;
                int mm = 1 + ltm -> tm_mon;
                int yy = 1900 + ltm -> tm_year;
                auto book = book_db.extract(title);
                book_db.Delete(title);
                book.setDueDate(now, dd, mm, yy);
                book.Book_request();
                book.set_issued_user(username);
                //user.collection[title]=book;
                user.set_book(book);
                user.increment_issued_number();
                book_db.add(book);

              }
            } else if (opcode == "5") {
              cout << roled_user.calculate_fine() << endl;
            } else if (opcode == "6") {
              string title;
              cout << "Enter Title: ";
              cin.ignore();
              getline(cin, title, '\n');

              auto book = book_db.extract(title);
              //user.collection.erase(title);
              if (book.get_issued_user() != user.get_username()) {
                cout << "You Cant return the book you have not issued" << endl;
              } else {
                user.delete_book(title);
                user.decrement_issued_number();
                book_db.Delete(title);
                book.set_status(0);
                book_db.add(book);
                cout << "The book is returned successfully" << endl;
              }

            } else if (opcode == "7") {

              break;
            } else {
              system("clear");
              cout << "Please enter one of the available options\n";
              continue;
            }
            user_db.add(user);
            string dummy;
            cout << "Enter 0 to continue\n";
            cin >> dummy;
          }
        } else if (user.get_role() == 3) {
          string opcode;
          auto roled_user = user_db.extract_librarian(username);
          while (1) {
            system("clear");
            cout << "Enter respectively as\n1 for viewing all books\n2 for viewing all users\n3 add a book\n4 for deleting a book\n5 for updating a book\n6 Checking which user book is issued to\n7 for viewing list of books issued to a user\n8 to add a user\n9 to remove a user\n10 to update a user\n11 to viewing fine for a user\n12 for clear fine on a user\n13 to logout\n";
            cin >> opcode;
            system("clear");
            if (opcode == "1") {
              book_db.display();

            } else if (opcode == "2") {
              user_db.display();

            } else if (opcode == "3") {
              string title;
              string author;
              string ISBN;
              string Publication;
              cout << "Enter the details of book\n";
              cout << "Enter Title: ";
              cin.ignore();
              getline(cin, title, '\n');
              cout << "Enter author: ";
              getline(cin, author, '\n');
              cout << "Enter ISBN number: ";
              getline(cin, ISBN, '\n');
              cout << "Enter Publication: ";
              getline(cin, Publication, '\n');
              Book book(title, author, ISBN, Publication);
              book_db.add(book);

            } else if (opcode == "4") {
              string title;
              cout << "Enter Title: ";
              cin.ignore();
              getline(cin, title, '\n');
              book_db.Deletel(title); 
            } else if (opcode == "5") {
              string title;
              cout << "Enter Title: ";
              cin.ignore();
              getline(cin, title, '\n');
              book_db.update(title);
            } else if (opcode == "6") {
              string title;
              cout << "Enter Title: ";
              cin.ignore();
              getline(cin, title, '\n');

              if (book_db.exists(title)) {
                auto book = book_db.extract(title);
                if (book.get_status()) {
                  string username = book.get_issued_user();
                  auto user = user_db.extract(username);
                  cout << "Details of the user the book is issued to :\n\n" << flush;
                  cout << "Name : " << user.get_name() << endl;
                  cout << "Designation : " << user.get_type() << endl;
                } else {
                  cout << "Book is not issued to anyone" << endl;
                }
              } else {
                cout << "Book does not exist in Library\n";
              }

            } else if (opcode == "7") {
              string username;
              cout << "Enter username: ";
              cin >> username;
              if (user_db.exists(username)) {
                auto tuser = user_db.extract(username);
                cout << "User Details\n\n" << flush;
                cout << "Name : " << tuser.get_name() << endl;
                cout << "Designation : " << tuser.get_type() << endl << endl;
                int count = 0;
                cout << "List of books issued to the user : " << endl;
                book_db.display(tuser.get_username());
                cout << endl;

              } else {
                cout << "This username does not exist in database, Please check again and retry\n" << endl;
              }
            } else if (opcode == "8") {
              string name;
              string username;
              string password;
              string confirm;
              int role;
              string roles;
              cout << "Enter the details of user " << "\n";
              cout << "Enter Name: ";
              cin.ignore();
              getline(cin, name, '\n');
              cout << "Enter Username: ";
              cin >> username;
              while (1) {
                cout << "Enter password: ";
                cin >> password;
                cout << "confirm password: ";
                cin >> confirm;
                if (confirm == password) {
                  break;
                }
                cout << "Passwords do not match\n";

              }
              while (1) {
                cout << "Enter role as\n1 for student\n2 for professor\n3 for librarian" << endl;
                cin >> roles;

                if (roles == "1") {
                  Student student(name, password, username);
                  user_db.add(student);
                  user_db.add_student(student);
                  break;
                } else if (roles == "2") {
                  Professor prof(name, password, username);
                  user_db.add(prof);
                  user_db.add_prof(prof);
                  break;
                } else if (roles == "3") {
                  Librarian librarian(name, password, username);
                  user_db.add(librarian);
                  user_db.add_librarian(librarian);
                  break;
                }

                cout << "Please enter one of the available options\n";

              }

            } else if (opcode == "9") {
              string username;
              cout << "Enter username: " << endl;
              cin >> username;
              if (user_db.exists(username)) {
                if (user_db.extract(username).get_issued_number()) {
                  cout << "Can't remove the user as he/she has some books issued which are not returned yet" << endl;
                } else {
                  auto user = user_db.extract(username);
                  user_db.delete_user(username);
                  if (user.get_role() == 1) {
                    user_db.delete_student(username);
                  } else if (user.get_role() == 2) {
                    user_db.delete_prof(username);
                  } else {
                    user_db.delete_librarian(username);
                  }

                }
              } else {
                cout << "This user is already not a member of Library" << endl;
              }

            } else if (opcode == "10") {
              string username;
              string password;
              string roles;
              string confirm;
              cout << "Enter username: " << endl;
              cin >> username;
              string name;
              if (user_db.exists(username)) {
                auto user = user_db.extract(username);
                user_db.delete_user(username);
                if (user.get_role() == 1) {
                  user_db.delete_student(username);
                } else if (user.get_role() == 2) {
                  user_db.delete_prof(username);
                } else {
                  user_db.delete_librarian(username);
                }
                cout << "Enter the updated details of the user " << "\n";
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name, '\n');
                cout << "Enter Username: ";
                cin >> username;

                while (1) {
                  cout << "Enter password: ";
                  cin >> password;
                  cout << "confirm password: ";
                  cin >> confirm;
                  if (confirm == password) {
                    break;
                  }
                  cout << "Passwords do not match\n";

                }
                while (1) {
                  cout << "Enter role as\n1 for student\n2 for professor\n3 for librarian" << endl;
                  cin >> roles;

                  if (roles == "1") {
                    Student student(name, password, username);
                    user_db.add(student);
                    user_db.add_student(student);
                    break;
                  } else if (roles == "2") {
                    Professor prof(name, password, username);
                    user_db.add(prof);
                    user_db.add_prof(prof);
                    break;
                  } else if (roles == "3") {
                    Librarian librarian(name, password, username);
                    user_db.add(librarian);
                    user_db.add_librarian(librarian);
                    break;
                  }

                  cout << "Please enter one of the available options\n";

                }

              } else {
                cout << "This user is not a member of Library" << endl;
              }
            } else if (opcode == "11") {
              string username;
              cout << "Enter Username for which you want to know the fine" << endl;
              cin >> username;
              if (user_db.exists(username)) {
                if (user_db.extract(username).get_role() == 1) {
                  auto roled_user = user_db.extract_student(username);
                  cout<<"The pending fine on this user is :";
                  cout<< roled_user.calculate_fine()<<endl;

                } else if (user_db.extract(username).get_role() == 2) {
                  auto roled_user = user_db.extract_prof(username);
                  cout<<"The pending fine on this user is :";
                  cout<<roled_user.calculate_fine()<<endl;

                }
              } else {
                cout << "This user is not a member of Library" << endl;
              }

            } 
            else if(opcode=="12"){
            string username;
              cout << "Enter Username for which you want to clear the fine" << endl;
              cin >> username;
              if (user_db.exists(username)) {
                if (user_db.extract(username).get_role() == 1) {
                  auto roled_user = user_db.extract_student(username);
                  user_db.delete_student(roled_user);
                  roled_user.set_pending_fine(0);
                  user_db.add_student(roled_user);

                } else if (user_db.extract(username).get_role() == 2) {
                  auto roled_user = user_db.extract_prof(username);
                  user_db.delete_prof(roled_user);
                  roled_user.set_pending_fine(0);
                  user_db.add_prof(roled_user);

                }
            }
            else{
              cout << "This user is not a member of Library" << endl;
            }
            }
            else if (opcode == "13") {
              break;
            } else {
              system("clear");
              cout << "Please enter one of the available options\n";
              continue;
            }
            user_db.add(user);
            string dummy;
            cout << "Enter 0 to continue\n";
            cin >> dummy;
          }
        }

        system("clear");
        cout << "You logged out sucessfully\n";
        sleep(1);
        cout << "\n";
        system("clear");

      } else {
        cout << "Username or password is incorrect\n";
        sleep(1);
        system("clear");
      }
    } else {
      cout << "Username or password is incorrect\n";
      cout << "Reloading Screen .." << flush;
      for (int i = 1; i < 4; i++) {
        sleep(1);
        cout << "." << flush;
      }
      cout << "\n";
      system("clear");
    }
  }
  return 0;
}