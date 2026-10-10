#include <iostream>
#include <string>
using namespace std;

// Task 1: Book Request Node
struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

// Task 2: Priority Queue Class
class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    // Constructor
    PriorityQueue()
    {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    // Task 3: Add request according to priority
    void Add(BookRequestNode* request)
    {
        request->next = NULL;

        if (front == NULL)
        {
            front = request;
            rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            BookRequestNode* current = front;

            while (current->next != NULL &&
                   current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == NULL)
            {
                rear = request;
            }
        }

        count++;
    }

    // Task 4: Remove highest-priority request
    BookRequestNode* Remove()
    {
        if (front == NULL)
        {
            return NULL;
        }

        BookRequestNode* request = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        request->next = NULL;
        count--;

        return request;
    }

    // Task 5: Check queue status
    bool IsEmpty()
    {
        return front == NULL;
    }

    bool IsNotEmpty()
    {
        return front != NULL;
    }

    // Task 6: Display all requests
    void PrintQueue()
    {
        if (IsEmpty())
        {
            cout << "The Priority Queue is empty." << endl;
            return;
        }

        BookRequestNode* current = front;

        cout << "\n===== PENDING REQUESTS =====\n";

        while (current != NULL)
        {
            cout << "Student Name: "
                 << current->studentName << endl;

            cout << "Student ID: "
                 << current->studentID << endl;

            cout << "Book Title: "
                 << current->bookTitle << endl;

            cout << "Book ID: "
                 << current->bookID << endl;

            cout << "Priority: "
                 << current->priority << " ";

            if (current->priority == 1)
                cout << "[Exam / Urgent]";
            else if (current->priority == 2)
                cout << "[Assignment / Project]";
            else
                cout << "[Normal Reading]";

            cout << "\n-----------------------------\n";

            current = current->next;
        }

        cout << "Total pending requests: "
             << count << endl;
    }

    // Task 7: Destructor
    ~PriorityQueue()
    {
        while (front != NULL)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
        count = 0;
    }
};

// Task 8: Create a new request
BookRequestNode* CreateRequest(
    int studentID,
    string studentName,
    int bookID,
    string bookTitle,
    int priority)
{
    BookRequestNode* request = new BookRequestNode;

    request->studentID = studentID;
    request->studentName = studentName;
    request->bookID = bookID;
    request->bookTitle = bookTitle;
    request->priority = priority;
    request->next = NULL;

    return request;
}

// Task 9: Main program
int main()
{
    PriorityQueue requests;
    int choice;

    do
    {
        cout << "\n===== LIBRARY PRIORITY QUEUE SYSTEM =====\n";
        cout << "1. Add a New Book Request\n";
        cout << "2. Process Highest-Priority Request\n";
        cout << "3. Display All Pending Requests\n";
        cout << "4. Exit\n";
        cout << "Enter choice (1-4): ";

        cin >> choice;

        if (choice == 1)
        {
            int sID, bID, prio;
            string sName, bTitle;

            cout << "Enter Student ID: ";
            cin >> sID;

            cin.ignore(1000, '\n');

            cout << "Enter Student Name: ";
            getline(cin, sName);

            cout << "Enter Book ID: ";
            cin >> bID;

            cin.ignore(1000, '\n');

            cout << "Enter Book Title: ";
            getline(cin, bTitle);

            do
            {
                cout << "Enter Priority "
                     << "(1 = Exam, 2 = Assignment, 3 = Normal): ";

                cin >> prio;

                if (prio < 1 || prio > 3)
                {
                    cout << "Invalid priority! Enter 1, 2, or 3.\n";
                }

            } while (prio < 1 || prio > 3);

            BookRequestNode* node =
                CreateRequest(sID, sName, bID, bTitle, prio);

            requests.Add(node);

            cout << "Request successfully added!\n";
        }
        else if (choice == 2)
        {
            BookRequestNode* processed = requests.Remove();

            if (processed != NULL)
            {
                cout << "\n===== PROCESSED REQUEST =====\n";

                cout << "Student Name: "
                     << processed->studentName << endl;

                cout << "Student ID: "
                     << processed->studentID << endl;

                cout << "Book Title: "
                     << processed->bookTitle << endl;

                cout << "Book ID: "
                     << processed->bookID << endl;

                cout << "Priority: "
                     << processed->priority << endl;

                delete processed;
            }
            else
            {
                cout << "Queue underflow! No pending requests.\n";
            }
        }
        else if (choice == 3)
        {
            requests.PrintQueue();
        }
        else if (choice == 4)
        {
            cout << "Exiting application. Goodbye!\n";
        }
        else
        {
            cout << "Invalid choice! Enter a number from 1 to 4.\n";
        }

    } while (choice != 4);

    return 0;
}
