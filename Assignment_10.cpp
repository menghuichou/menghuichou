//Meng-Hui Chou
//20363369
//Assignment_10
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

// class Student prototype -----------------------
class Student
{
private:
   string lastName;
   string firstName;
   int totalPoints;

public:
   static const string DEFAULT_NAME;
   static const int DEFAULT_POINTS = 0;
   static const int MAX_POINTS = 1000;

public:
   Student(string lst = DEFAULT_NAME, string fst = DEFAULT_NAME,
      int pts = DEFAULT_POINTS);

   // accessors and mutators
   string getLastName() { return lastName; }
   string getFirstName() { return firstName; }
   int getTotalPoints() { return totalPoints; }

   bool setLastName(string last);
   bool setFirstName(string first);
   bool setPoints(int pts);

   static int compareTwoStudents(Student firstStud, Student secondStud);
   string toString();

private:
   static bool validString(string testStr);
   static bool validPoints(int testPoints);

public:
   static const int SORT_BY_FIRST = 88;
   static const int SORT_BY_LAST = 98;
   static const int SORT_BY_POINTS = 108;

private:
   static int sortkey;

public:
   static bool setSortKey(int key);
   int getSortKey() { return sortkey; }

public:
   static const int  MAX_STUDENTS;



};  // end of class Student prototype --------------

int const Student::MAX_STUDENTS = 20;

// class StudentArrayUtilities prototype -----------------------
class StudentArrayUtilities
{
private:
   Student theArray[Student::MAX_STUDENTS];
   int numStudents = 0;

public:
   bool addStudent(Student stud);
   Student removeStudent();

public:
   string toString(string title);
   void arraySort();

private:
   bool floatLargestToTop(int top);
   static void mySwap(Student &a, Student &b);

public:
   double getMedianDestructive();

};

// static initializations that can't be done in-line
const string Student::DEFAULT_NAME = "zz-error";
int Student::sortkey = SORT_BY_LAST;

int main()
{

   Student evenClass[] =
   {
      Student("Chou","Anna", 666),Student("Ma","Joyce",466),
      Student("Chiang","Sylvia",123),Student("Lee","Tracy",333),
      Student("Tsai","Angelica", 218),Student("Chen","Jeff",302),
      Student("Chang","Jacob", 108),Student("Huang","Vera",111),
      Student("Chu","Ivy",100),Student("Mao","Stephenie",311),
      Student("Chung","Yating",305),Student("Yang","Vicky",112),
      Student("Chang","Pingu",120),Student("Ling","Jenet",206),
      Student("Wang","Amy",810),Student("Tu","teacher",311),
   };

   Student student;
   int arraySizeEven = sizeof(evenClass) / sizeof(evenClass[0]);

   // instantiate an SAU object
   StudentArrayUtilities myStuds;

   // we can add stdunts manually and individually
   myStuds.addStudent(Student("Bartman", "Petra", 102));
   myStuds.addStudent(Student("Charters", "Rodney", 295));

   // if we happen to have an array available, we can add students in loop.
   for (int k = 0; k < arraySizeEven; k++)
      myStuds.addStudent(evenClass[k]);

   cout << myStuds.toString("Before: ");

   myStuds.arraySort();
   cout << myStuds.toString("After default sort: ");

   Student::setSortKey(Student::SORT_BY_FIRST);
   myStuds.arraySort();
   cout << myStuds.toString("After sort by first: ");

   // test median
   cout << "Median of evenClass = "
      << myStuds.getMedianDestructive()
      << endl;

   // various tests of removing and adding too many students
   for (int k = 0; k < 50; k++)
   {
      student = myStuds.removeStudent();
      if (Student::compareTwoStudents(student, Student()))
         cout << "Removed " << student.toString();
      else
      {
         cout << "Empty after " << k << " removes." << endl;
         break;
      }
   }

   for (int k = 0; k < 100; k++)
   {
      if (!myStuds.addStudent(Student("first", "last", 22)))
      {
         cout << "Full after " << k << " adds." << endl;
         break;
      }
   }



}

// beginning of Student method definitions -------------

// constructor requires parameters - no default supplied
Student::Student(string last, string first, int points)
{
   if (!setLastName(last))
      lastName = DEFAULT_NAME;
   if (!setFirstName(first))
      firstName = DEFAULT_NAME;
   if (!setPoints(points))
      totalPoints = DEFAULT_POINTS;
}

bool Student::setLastName(string last)
{
   if (!validString(last))
      return false;
   lastName = last;
   return true;
}

bool Student::setFirstName(string first)
{
   if (!validString(first))
      return false;
   firstName = first;
   return true;
}

bool Student::setPoints(int pts)
{
   if (!validPoints(pts))
      return false;
   totalPoints = pts;
   return true;
}

// could be an instance method and, if so, would take one parameter
int Student::compareTwoStudents(Student firstStud, Student secondStud)
{
   int result;

   switch (sortkey)
   {
   case SORT_BY_LAST:
      result = firstStud.lastName.compare(secondStud.lastName);
      break;

   case SORT_BY_FIRST:
      result = firstStud.firstName.compare(secondStud.firstName);
      break;

   case SORT_BY_POINTS:
      result = firstStud.totalPoints - secondStud.totalPoints;
      break;
   }

   return result;
}

string Student::toString()
{
   string resultString;
   ostringstream cnvrtFirst, cnvrtLast, cnvrtPoints;

   cnvrtFirst << firstName;
   cnvrtLast << lastName;
   cnvrtPoints << totalPoints;

   resultString = " " + cnvrtLast.str()
      + ", " + cnvrtFirst.str()
      + " points: " + cnvrtPoints.str()
      + "\n";
   return resultString;
}

bool Student::validString(string testStr)
{
   if (testStr.length() > 0 && isalpha(testStr[0]))
      return true;
   return false;
}

bool Student::validPoints(int testPoints)
{
   if (testPoints >= 0 && testPoints <= MAX_POINTS)
      return true;
   return false;
}

bool Student::setSortKey(int key)
{
   if (key == SORT_BY_FIRST)
   {
      sortkey = key;
      return true;
   }
   else if (key == SORT_BY_LAST)
   {
      sortkey = key;
      return true;
   }
   else if (key == SORT_BY_POINTS)
   {
      sortkey = key;
      return true;
   }
   else
      return false;
}

bool StudentArrayUtilities::addStudent(Student stud)
{
   if (numStudents < Student::MAX_STUDENTS)
   {
      Student &slot = theArray[numStudents++];
      slot = stud;

      return true;
   }
   return false;
}

Student StudentArrayUtilities::removeStudent()
{
   if (numStudents > 0)
   {
      numStudents--;
      return theArray[numStudents];
   }
   else
      return Student::Student();
  
}


// end of Student method definitions  --------------

// beginning of StudentArrayUtilities method definitions -------------

// print the array with string as a title for the message box
// this is somewhat controversial - we may or may not want an I/O
// methods in this class.  we'll accept it today
double StudentArrayUtilities::getMedianDestructive()
{
   double median;
   bool odd = numStudents % 2;
   int saveSort;
   Student student;
   saveSort = student.getSortKey();

   Student::setSortKey(Student::SORT_BY_FIRST);
   StudentArrayUtilities::arraySort();

   if (odd)
   {
      int medianIdx = numStudents / 2;
      median = theArray[medianIdx].getTotalPoints();
   }
   else
   {
      if (numStudents == 0)
         return 0.0;

      int largerMedianIdx = numStudents / 2;
      int smallerMedianIdx = largerMedianIdx - 1;
      median = (theArray[largerMedianIdx].getTotalPoints()
         + theArray[smallerMedianIdx].getTotalPoints()) / 2.;
   }
   Student::setSortKey(saveSort);
   return median;

}

string StudentArrayUtilities::toString(string title)
{
   string output = "";

   cout << title << endl;

   // build the output string from the individual Students:
   for (int k = 0; k < numStudents; k++)
      output += " " + theArray[k].toString();

   return output;
}

void StudentArrayUtilities::arraySort()
{
   for (int k = 0; k < numStudents; k++)
      // compare with method def to see where inner loop stops
      if (!floatLargestToTop(numStudents - 1 - k))
         return;
}

// returns true if a modification was made to the array
bool StudentArrayUtilities::floatLargestToTop(int top)
{
   bool changed = false;

   // compare with client call to see where the loop stops
   for (int k = 0; k < top; k++)
      if (Student::compareTwoStudents(theArray[k], theArray[k + 1]) > 0)
      {
         mySwap(theArray[k], theArray[k + 1]);
         changed = true;
      }
   return changed;
}

void StudentArrayUtilities::mySwap(Student &a, Student &b)
{
   Student temp("", "", 0);

   temp = a;
   a = b;
   b = temp;
}

// end of StudentArrayUtilities method definitions  --------------

/*------------PASTE OF RUN-------------------
Before:
  Bartman, Petra points: 102
  Charters, Rodney points: 295
  Chou, Anna points: 666
  Ma, Joyce points: 466
  Chiang, Sylvia points: 123
  Lee, Tracy points: 333
  Tsai, Angelica points: 218
  Chen, Jeff points: 302
  Chang, Jacob points: 108
  Huang, Vera points: 111
  Chu, Ivy points: 100
  Mao, Stephenie points: 311
  Chung, Yating points: 305
  Yang, Vicky points: 112
  Chang, Pingu points: 120
  Ling, Jenet points: 206
  Wang, Amy points: 810
  Tu, teacher points: 311
After default sort:
  Bartman, Petra points: 102
  Chang, Jacob points: 108
  Chang, Pingu points: 120
  Charters, Rodney points: 295
  Chen, Jeff points: 302
  Chiang, Sylvia points: 123
  Chou, Anna points: 666
  Chu, Ivy points: 100
  Chung, Yating points: 305
  Huang, Vera points: 111
  Lee, Tracy points: 333
  Ling, Jenet points: 206
  Ma, Joyce points: 466
  Mao, Stephenie points: 311
  Tsai, Angelica points: 218
  Tu, teacher points: 311
  Wang, Amy points: 810
  Yang, Vicky points: 112
After sort by first:
  Wang, Amy points: 810
  Tsai, Angelica points: 218
  Chou, Anna points: 666
  Chu, Ivy points: 100
  Chang, Jacob points: 108
  Chen, Jeff points: 302
  Ling, Jenet points: 206
  Ma, Joyce points: 466
  Bartman, Petra points: 102
  Chang, Pingu points: 120
  Charters, Rodney points: 295
  Mao, Stephenie points: 311
  Chiang, Sylvia points: 123
  Lee, Tracy points: 333
  Huang, Vera points: 111
  Yang, Vicky points: 112
  Chung, Yating points: 305
  Tu, teacher points: 311
Median of evenClass = 111
Removed  Tu, teacher points: 311
Removed  Chung, Yating points: 305
Removed  Yang, Vicky points: 112
Removed  Huang, Vera points: 111
Removed  Lee, Tracy points: 333
Removed  Chiang, Sylvia points: 123
Removed  Mao, Stephenie points: 311
Removed  Charters, Rodney points: 295
Removed  Chang, Pingu points: 120
Removed  Bartman, Petra points: 102
Removed  Ma, Joyce points: 466
Removed  Ling, Jenet points: 206
Removed  Chen, Jeff points: 302
Removed  Chang, Jacob points: 108
Removed  Chu, Ivy points: 100
Removed  Chou, Anna points: 666
Removed  Tsai, Angelica points: 218
Removed  Wang, Amy points: 810
Empty after 18 removes.
Full after 20 adds.

C:\Users\varna\OneDrive\文件\Visual Studio 2017\Assignment_10\Debug\Assignment_10.exe (process 17912) exited with code 0.
Press any key to close this window . . .

---------------------------------------*/