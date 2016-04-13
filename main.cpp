#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
using namespace std;

enum cohort {FRESHMAN, SOPHOMORE, JUNIOR, SENIOR};

class Contact {
private:
		char cAddress[75];
		char cPhone[25];
		char cEmail[75];
public:
		void setAddress(char *cAddress) {strcpy(this->cAddress, cAddress);}
		void setPhone(char *cPhone) { strcpy(this->cPhone, cPhone); }
		void setEmail(char *cEmail) { strcpy(this->cEmail, cEmail); }
		char* getAddress() { return cAddress; }
		char* getPhone() { return cPhone; }
		char* getEmail() { return cEmail; }

		Contact(char *cAddress, char *cPhone, char *cEmail) { // constructor
			setAddress(cAddress);
			setPhone(cPhone);
			setEmail(cEmail);
		}
};

class Personnel {
	private:
		char cName[50];
		int iId;
		char cBirthday[11];
	protected:
		Contact *pContact;
	public:
		void setName(char *cName) { strcpy(this->cName, cName); }
		void setBirthday(char *cBirthday) {strcpy(this->cBirthday, cBirthday);}
		void setId(int iId) { this->iId = iId; }
		char* getName() { return cName; }
		int getId() { return iId;}
		char* getBirthday() { return cBirthday; }
		Contact * getContact() { return pContact; }
		virtual void display() {
			cout << "PERSONNEL" << endl;
			cout << "Name:\t" << getName() << endl;
			cout << "Id:\t" << getId() << endl;
			cout << "Birthday:\t" << getBirthday() << endl;
			cout << "Address:\t" << pContact->getAddress() << endl;
			cout << "Phone:\t" << pContact->getPhone() << endl;
			cout << "Email:\t" << pContact->getEmail() << endl;
		}

		Personnel(char *cName, char *cBirthday, char *cAddress, char *cPhone, char *cEmail) { 					// constructor
			static int iIdCounter = 0;
			setName(cName);		// set Name
			setId(iIdCounter);	// set Id by a self-incremental counter
			iIdCounter++;		// increment the ID generator;
			setBirthday(cBirthday);	// set Birthday
			pContact = new Contact(cAddress, cPhone, cEmail);
		}

		virtual ~Personnel() {				// destructor
			delete pContact;		// delete the object linked to pContact
			pContact = NULL;		// Make sure pContact not point to an object
		}
};

class Employee : public Personnel	 {	// inherit from Personnel
	private:
		char cDepartment[75];
		float fSalary;
		char cRank[75];

	public:
		void setDepartment(char *cDepartment) {strcpy(this->cDepartment, cDepartment);}
		void setSalary(float fSalary) { this->fSalary = fSalary; }
		virtual void setRank(char *cRank) { strcpy(this->cRank, cRank); }
		char* getDepartment() { return cDepartment; }
		float getSalary() { return fSalary; }
		virtual char* getRank() { return cRank; }

		void display() {
			Personnel::display();
			cout << "EMPLOYEE" << endl;
			cout << "Department:\t" << getDepartment() << endl;
			cout << "Salary:\t" << getSalary() << endl;
			cout << "Rank:\t" << getRank() << endl;
		}

		Employee(char *cName, char *cBirthday, char *cAddress, char *cPhone, char *cEmail, char *cDepartment, float fSalary, char *cRank)
			: Personnel(cName, cBirthday, cAddress, cPhone, cEmail)
		{
			setDepartment(cDepartment);
			setSalary(fSalary);
			setRank(cRank);
		}

		virtual ~Employee() {				// destructor
			delete pContact;		// delete the object linked to pContact
			pContact = NULL;		// Make sure pContact does not point to
		}						// any object
};

class Faculty : public Employee {	// inherit from Employee
	private:
		char cResearch[75];
	public:
		virtual void setResearch(char *cResearch) {
			strcpy(this->cResearch, cResearch);
		}
		char* getResearch() { return cResearch; }
		virtual void display() {
			Employee::display();
			cout << "FACULTY" << endl;
			cout << "Research\t" << getResearch() << endl;
		}

		Faculty(char *cName, char *cBirthday, char *cAddress, char *cPhone, char *cEmail, char *cDepartment, float fSalary, char *cRank, char *cResearch)
			: Employee(cName, cBirthday, cAddress, cPhone, cEmail, cDepartment, fSalary, cRank)
		{
			setResearch(cResearch);
		}

		virtual ~Faculty() {				// destructor
			delete pContact;		// delete the object linked to pContact
			pContact = NULL;		// Make sure pContact does not
		}						// point to any object
};




class PersonnelNode {		// This is a container class
	private:
		Personnel		*pNode;	// It contains a Personnel class
		PersonnelNode	*pNext;	// pointer used to form a linked list
	public:
		void setNode(Personnel *pNode) { this->pNode = pNode; }
		void setNext(PersonnelNode *pNext) { this->pNext = pNext; }
		Personnel* getNode() { return pNode; }
		PersonnelNode* getNext() { return pNext; }

		PersonnelNode() {		// constructor
			pNode = NULL;
			pNext = NULL;
		}
} *head = NULL;	// declare a global pointer variable head

typedef struct Book {
	char title[100];
	char url[100];
	Book *left;
	Book *right;
} Book;

class Student : public Personnel {
	private:
		Book *bookTree;
		cohort level;

	public:
	void setLevel(cohort level) { this->level = level; }
	cohort getLevel() { return this->level; }
	Book * getBookTree() { return this->bookTree; }
	void displayBT(Book *book) {
		if(book == NULL) {
			return;
		}
		displayBT(book->left);
		cout << "Title: " << book->title << endl;
		cout << "URL: " << book->url << endl;
		displayBT(book->left);
	}
	virtual void display() {
		Personnel::display();
		cout << "STUDENT" << endl;
		switch(level) {
			case FRESHMAN:
				cout << "Freshman" << endl;
				break;
			case SOPHOMORE:
				cout << "Sophomore" << endl;
				break;
			case JUNIOR:
				cout << "Junior" << endl;
				break;
			case SENIOR:
				cout << "Senior" << endl;
				break;
			default:
				break;

		}
		displayBT(this->getBookTree());
		Book *b = this->getBookTree();
		cout << b->title << endl;
	}

	Student(char *cName, char *cBirthday, char *cAddress, char *cPhone, char *cEmail, cohort level)
			: Personnel(cName, cBirthday, cAddress, cPhone, cEmail)
	{
		setLevel(level);
		this->bookTree = NULL;
	}

	virtual ~Student() {				// destructor
		delete pContact;		// delete the object linked to pContact
		pContact = NULL;		// Make sure pContact does not point to
	}


};

// Forward declaration of global functions outside any class
int main();				// The main function
void menu();			// display main choices
void branching(char);	// branch to the chosen function
void sub_menu();			// display different insertion options
void insert();			// call sub_menu() and branch to chosen function
int insert_personnel();	// insert a personnel node
int insert_employee();	// insert an employee node
int insert_faculty();	// insert a faculty node
int insert_student();
int insert_book();
void search(char title[], Book *tree);
void search_book();
void deleteBooks(Book *tree);
void delete_all_books();

void remove();			// call remove function
void display_all();		// display members in all nodes in the linked list
void display_node(Personnel*, int);	// display the members in one node

int main() {	// main function is the entry point of the program
	char ch;
	cout << "CLASSES INHERITANCE, HIERARCHY AND POLYMORPHISM" << endl;
	cout << "***********************************************" << endl;

	do {
		 menu();				// display choices
		 cin >> ch;			// enter a choice from the keyboard
		 ch = tolower(ch);	// convert to lower case
		 branching(ch);		// branch to the chosen function
	}
	while (ch != 'q');			// 'q' for quit
	return 0;
}

void menu() {
	cout <<	endl << endl << "MENU" << endl;
	cout << "----" << endl;
	cout << "i: Insert a new entry." << endl;
	cout << "d: display all entries." << endl;
	cout << "r: remove an entry." << endl;
	cout << "q: Quit the program." << endl;
	cout << endl << "Please enter your choice (i, d, r, or q) --> ";
}

void branching(char c) {		// branch to chosen function
	 switch(c) {
		case 'i':	insert();
				break;
 		case 'd':	display_all();
				break;
 		case 'r':	remove();
				break;
		case 'q':	cout << endl << "@Exiting the program..............." << endl;
				cin.get();	//type any key.
				break;
		default:	cout << endl << "@ERROR - Invalid input." << endl;
				cout << "@Try again....." << endl;
	 }
}

void sub_menu() {	// display insertion options
	cout <<	endl << endl << "INSERTION SUB-MENU" << endl;
	cout << "------------------" << endl;
	cout << "p: insert a personnel entry." << endl;
	cout << "e: insert an employee entry." << endl;
	cout << "f: insert a faculty entry." << endl;
	cout << "s: insert a student entry." << endl;
	cout << "b: insert a book entry." << endl;
	cout << "?: book search." << endl;
	cout << "!: delete all books." << endl;
	cout << "q: Quit insertion and back to main menu." << endl;
	cout << endl << "Please enter your choice (p, e, f, c, or q) --> ";
}

// insert() is the umbrella insertion function that calls different insertion
// functions according to the selection in the sub-menu.
void insert() {
	char ch;

	cout << endl << "@Insertion module...............";
	do {
		 sub_menu();
		 cin >> ch;
		 ch = tolower(ch);

		 switch(ch) {
			case 'p':	if(insert_personnel() != 0)
							cout << "@INSERTION OPERATION FAILED." << endl;
						else
							cout << "@INSERTED SUCCESSFULLY." << endl;
							break;
			case 'e':	if(insert_employee() != 0)
							cout << "@INSERTION OPERATION FAILED." << endl;
						else
							cout << "@INSERTED SUCCESSFULLY." << endl;
							break;
			case 'f':	if(insert_faculty() != 0)
							cout << "@INSERTION OPERATION FAILED." << endl;
						else
							cout << "@INSERTED SUCCESSFULLY." << endl;
							break;
			case 's':	if(insert_student() != 0)
							cout << "@INSERTION OPERATION FAILED." << endl;
						else
							cout << "@INSERTED SUCCESSFULLY." << endl;
						break;
			case 'b':	if(insert_book() != 0)
							cout << "@INSERTION OPERATION FAILED." << endl;
						else
							cout << "@INSERTED SUCCESSFULLY." << endl;
						break;
			case '?':	search_book();
				 		break;
			case '!':	delete_all_books();
				 		break;
			case 'q':	cout << endl << "@Exiting the insertion..." << endl;
						cin.get();
						break;
			default:		cout << endl << "@ERROR - Invalid input." << endl;
						cout << "@Try again....." << endl;
		}
	}
	while (ch != 'q');
}

int insert_personnel() {		// insert a Personnel node
	Personnel *person = NULL;
	PersonnelNode *node = NULL;
	char name[50], birthday[11], address[75], phone[25], email[75];
	cout << endl << "@Inserting personnel node.........." << endl;
	cout << "Enter the name: ";
	cin.ignore();	// fflush()
	cin.getline(name, 50);
	cout << "Enter the birthday, e.g., 05/24/1985: ";
	cin.getline(birthday, 11);
	cout << "Enter the address: ";
	cin.getline(address, 75);
	cout << "Enter the phone number: ";
	cin.getline(phone, 25);
	cout << "Enter the email: ";
	cin.getline(email, 75);
	person = new Personnel(name, birthday, address, phone, email);
	node = new PersonnelNode();

	if((person != NULL) && (node != NULL)) {
		node->setNode(person);
		node->setNext(head);
		head = node;
		return 0;
	}
	else {
		cout << endl << "@ERROR - Could not allocate enough memory!" << endl;
		return -1;
	}
}

int insert_employee() {		// insert an Employee node
	Personnel *person = NULL;
	PersonnelNode *node = NULL;
	char name[50], birthday[11], address[75], phone[25], email[75], department[75], rank[75];
	float salary;

	cout << endl << "@Inserting employee node.........." << endl;
	cout << "Enter the name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "Enter the birthday, e.g., 05/24/1985: ";
	cin.getline(birthday, 11);
	cout << "Enter the address:";
	cin.getline(address, 75);
	cout << "Enter the phone number: ";
	cin.getline(phone, 25);
	cout << "Enter the email: ";
	cin.getline(email, 75);
	cout << "Enter the department: ";
	cin.getline(department, 75);
	cout << "Enter the salary. It must be a float number: ";
	cin >> salary;
	cout << "Enter the rank: ";
	cin.ignore();
	cin.getline(rank, 75);

	person = new Employee(name, birthday, address, phone, email, department, salary, rank);
	node = new PersonnelNode();

	if((person != NULL) && (node != NULL)) {
		node->setNode(person);
		node->setNext(head);
		head = node;
		return 0;
	}
	else {
		cout << endl << "@ERROR - Could not allocate enough memory!" << endl;
		return -1;
	}
}

int insert_faculty() {		// insert a Faculty node
	Personnel *person = NULL;
	PersonnelNode *node = NULL;
	char name[50], birthday[11], address[75], phone[25], email[75], department[75], rank[75], research[75];
	float salary;

	cout << endl << "@Inserting faculty node.........." << endl;
	cout << "Enter the name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "Enter the birthday, e.g., 05/24/1985: ";
	cin.getline(birthday, 11);
	cout << "Enter the address: ";
	cin.getline(address, 75);
	cout << "Enter the phone number: ";
	cin.getline(phone, 25);
	cout << "Enter the email: ";
	cin.getline(email, 75);
	cout << "Enter the department: ";
	cin.getline(department, 75);
	cout << "Enter the salary. It must be a float number: ";
	cin >> salary;
	cout << "Enter the rank: ";
	cin.ignore();
	cin.getline(rank, 75);

	cout << "Enter the research: ";
	cin.getline(research, 75);

	person = new Faculty(name, birthday, address, phone, email, department, salary, rank, research);
	node = new PersonnelNode();
	if((person != NULL) && (node != NULL)) {
		node->setNode(person);
		node->setNext(head);
		head = node;
		return 0;
	}
	else {
		cout << endl << "@ERROR - Could not allocate enough memory!" << endl;
		return -1;
	}
}

int insert_student() {		// insert a Faculty node
	Personnel *person = NULL;
	PersonnelNode *node = NULL;
	char name[50], birthday[11], address[75], phone[25], email[75], level[75];
	cohort elevel;

	cout << endl << "@Inserting student node.........." << endl;
	cout << "Enter the name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "Enter the birthday, e.g., 05/24/1985: ";
	cin.getline(birthday, 11);
	cout << "Enter the address: ";
	cin.getline(address, 75);
	cout << "Enter the phone number: ";
	cin.getline(phone, 25);
	cout << "Enter the email: ";
	cin.getline(email, 75);

	cout << "Enter the level, (freshman, sophomore, junior, senior): ";
	cin.getline(level, 75);
	cout <<  level << endl;

	if(strcmp(level, "freshman") == 0) {
		elevel = FRESHMAN;
		cout << elevel;
	} else if(strcmp(level, "sophomore") == 0) {
		elevel = SOPHOMORE;
	} else if(strcmp(level, "junior") == 0) {
		elevel = JUNIOR;
	} else if(strcmp(level, "senior") == 0) {
		elevel = SENIOR;
	}

	person = new Student(name, birthday, address, phone, email, elevel);
	node = new PersonnelNode();
	if((person != NULL) && (node != NULL)) {
		node->setNode(person);
		node->setNext(head);
		head = node;
		return 0;
	}
	else {
		cout << endl << "@ERROR - Could not allocate enough memory!" << endl;
		return -1;
	}
}

int insert_book() {
	Book *newBook = (Book *)malloc(sizeof(Book));
	char studentName[50], title[75], url[75];

	cout << endl << "@Inserting a book node.........." << endl;
	cout << "Enter the student name: ";
	cin.ignore();
	cin.getline(studentName, 50);
	cout << "Enter the title: ";
	cin.getline(title, 75);
	cout << "Enter the url: ";
	cin.getline(url, 75);

	strcpy(newBook->title, title);
	strcpy(newBook->url, url);
	newBook->left = NULL;
	newBook->right = NULL;

	PersonnelNode *node = head;
	while(strcmp(node->getNode()->getName(), studentName) != 0) {
		node = node->getNext();
		if(node == NULL) {
			cout << endl << "@ERROR - Student does not exist!" << endl;
			return -1;
		}
	}

	Student *sNode = (Student *)node->getNode();

	Book *bNode = sNode->getBookTree();
	while(bNode != NULL) {
		if(strcmp(newBook->title, bNode->title) < 0) {
			bNode = bNode->left;
		} else {
			bNode = bNode->right;
		}
	}
	bNode = newBook;
	return 0;
}

void search(char title[], Book *tree) {
	if(strcmp(title, tree->title) == 0) {
		cout << tree->title << endl;
		cout << tree->url << endl;
		return;
	}
	if(strcmp(title, tree->title) < 0)
		search(title, tree->left);
	else
		search(title, tree->right);
}
void search_book() {
	char title[100], student[100];

	cout << endl << "@Searching a book.........." << endl;
	cout << "Enter the student name: ";
	cin.ignore();
	cin.getline(student, 50);
	cout << "Enter the title: ";
	cin.getline(title, 75);

	PersonnelNode *node = head;
	while(strcmp(node->getNode()->getName(), student) != 0) {
		node = node->getNext();
		if(node == NULL) {
			cout << endl << "@ERROR - Student does not exist!" << endl;
			return;
		}
	}

	Student *sNode = (Student *)node->getNode();
	search(title, sNode->getBookTree());
}

void deleteBooks(Book *tree) {
	if(tree == NULL)
		return;
	Book *left = tree->left, *right = tree->right;
	deleteBooks(left);
	free(tree);
	deleteBooks(right);
	return;
}

void delete_all_books() {
	char student[100];

	cout << endl << "@Deleting all book.........." << endl;
	cout << "Enter the student name: ";
	cin.ignore();
	cin.getline(student, 50);

	PersonnelNode *node = head;
	while(strcmp(node->getNode()->getName(), student) != 0) {
		node = node->getNext();
		if(node == NULL) {
			cout << endl << "@ERROR - Student does not exist!" << endl;
			return;
		}
	}

	Student *sNode = (Student *)node->getNode();
	deleteBooks(sNode->getBookTree());
}

/* void remove() function removes a node in the linked list. In the remove function, an id number will be entered as the key. The node whose id field stored an id number that is equal to the entered id number will be removed. */
void remove() {
	 int id;
	 PersonnelNode *temp, *prev;
	 Personnel *person;
	 int index = 1;
	 cout<<"Remove module...............\n" << endl ;
	 cout<<"Please enter the ID number of the person to be deleted: "<<endl;
	 cin>> id;
	 temp = head;
	 while (temp != NULL) {
		 person = temp->getNode();
	 		if (id != person->getId()){
				prev = temp;
				temp = temp->getNext();
				index++;
			}
			else {
				cout <<"Person to delete is found at index" << index<<endl;
				display_node(person, index);
				if(temp != head)
				prev->setNext(temp->getNext());
				else
					head = head->getNext();
				delete person;	// explicit garbage-collection
				person = NULL;	// Make person not to point to any object
				delete temp;		// explicit garbage-collection
				temp = NULL;		// Make temp not to point to any object
				return;
			}
		}
	 cout <<"The person with ID = << id << does not exist."<< endl;
}

void display_all() {	// Display contents of all nodes in the linked list
	PersonnelNode *node;
	int node_count= 0;
	cout << endl << "@Display module...............";
	node = head;
	while(node != NULL) {
		display_node(node->getNode(), ++node_count);
		node = node->getNext();
	}
	cout << endl << "@No more records." << endl;
}

void display_node(Personnel *node, int index) {// Display contents of node
	cout << endl << "Record " << index << "." << endl;
	node->display();// Polymorphic call. Depending on the object pointed to
}				// by node, a different display function will be invoked.
