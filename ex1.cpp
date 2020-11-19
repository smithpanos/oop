#include <iostream>
#include <cstring>


const int out_sch_code = 0;
const int yard_code = 1;
const int staircase_code = 2;
const int corridor_code = 3;
const int class_code = 4;

using namespace std;

struct Student;
struct Classroom;
struct Floor;
struct Corridor;
struct Yard;
struct Staircase;
struct Teacher;

struct Classroom{
    int floor; //Initialize OK
    int number_of_class; //Initialize OK
    int current_students_in; //Initialize OK
    int capacity; //Initialize OK
    Student** students_of_class;
    Teacher teacher;
    bool teacher_in; //Initialize OK
    bool can_join_classroom; //Initialize OK

    Classroom(const int &fl, const int & num_of_class, const int & cap = 0 ):floor(fl), number_of_class(num_of_class), current_students_in(0), capacity(cap), teacher_in(false), can_join_classroom(true) {
        students_of_class = new Student*[capacity];
        cout << "Class " << number_of_class << "just created" ;
        if (cap == 0 ) cout << ", but  capacity of class is set to 0 (No capacity input). e.g. No one can enter the classroom";
        cout << "." << endl;
    }

    ~Classroom(){
        cout << "Class " << number_of_class << "deleted." << endl;
        for(int i = capacity-1 ; i>=0 ; i--)
            delete students_of_class[i];
    }

    void place_teacher(const Teacher& t) {
        teacher = t;
        teacher_in = true;
        can_join_classroom = false;
        cout << "Teacher ";
        teacher.print();
        cout << " has been places to Classroom " << number_of_class << "." << endl;
        return;
    }

    void place_student(Student* stud){
        students_of_class[ current_students_in ] = stud;
        current_students_in++;
        if ( capacity-1 == current_students_in ) can_join_classroom = false;
    }

    void print_classroom(){
        cout <<  "People in class " <<  number_of_class << " are:" << endl;
        teacher.print();

        for (int i = 0 ; i < current_students_in -1 ; i++ ){
            Student *temp = students_of_class[i];
            temp->print();
        }
    }
};

struct Floor{
    Classroom** floor_classrooms;
    Corridor corridor;
    int current_students_in_corr;
    const int floor_level;
    const int Cclass, Ccorridor, Cstair;
    bool can_join_floor;

    Floor(const int &level, const int Ccla, const int Ccorr, const int Csta):
          floor_level(level), Cclass(Ccla), Ccorridor(Ccorr), Cstair(Csta), corridor(Ccorr), can_join_floor(true) {
        floor_classrooms = new Classroom*[6];
    
        for (int i = 0 ; i < 6 ; i++)
            floor_classrooms[i] = new Classroom(floor_level, (floor_level-1)*6 + i+1 , Cclass);
    }

    ~Floor(){
        for (int i = 0 ; i < 6 ; i++)
            delete floor_classrooms[i];

        cout << "Floor Deleted!" << endl;
    }

    void place_student(Student *s){
        corridor.place_student(s);
        
    }

};

struct Student{
    const char* name;
    int current_possition;
    Classroom classroom;
    Student(const char *n, const int &num_of_class);
    ~Student(){};
    void print();
    bool is_same_student(Student s);
};

struct Yard{
    int current_students_in;
    int capacity;
    Student* students_of_yard;
};

struct Staircase{
    int current_students_in;
    int capacity;
    Student* students_of_staircase;
};

struct Corridor{ //Διάδρομος
    int current_students_in;
    int capacity;
    Student** students_of_corridor;
    bool can_join_corridor; //Initialize OK

    Corridor(const int cap): current_students_in(0), capacity(cap), can_join_corridor(true) {
        students_of_corridor = new Student*[capacity];
        for (int i =0 ; i < capacity-1 ; i++) 
            students_of_corridor[i] = NULL;
    }

    ~Corridor(){
        for (int i = capacity-1 ; i >= 0 ; i--)
            if (students_of_corridor[i] != NULL) 
                delete students_of_corridor[i];

        cout << "deleted corridor" << endl;
    }

    void place_student(Student* s){
        students_of_corridor[current_students_in] = s;
        current_students_in++;
        if ( current_students_in == capacity) can_join_corridor = false;
        s->print();
        cout << "enters Corridor!" << endl;
    }
    void unplace_student(Student* s){
        
        for (int i = 0 ; i < capacity -1 ; i++){
            if (  s->is_same_student( *students_of_corridor[i] )  ){ // Χρειάζεται προσοχή αυτό το κομμάτι στο debugging!
                students_of_corridor[i] = NULL; //Δεν διαγράφουμε το student γιατί δεν έφυγε απο το σχολείο και απλά αλλάζει όροφο
                current_students_in--;
                can_join_corridor=true;
            }
        }
    }
};

struct Teacher{
    char* name;    
    int class_number;
    bool in_class;
    Teacher(const char* n = "No name", const int & class_no = 0) :
                 class_number(class_no), in_class(false){

        name = new char [ strlen(n) + 1];
        strcpy(name,n);
        cout << "A New Teacher has been created! " << name << " Class: " << class_number << "." << endl;
    }
    ~Teacher(){
        cout << "A Teacher to be destroyed! " << name << " Class: " << class_number << "." << endl;
        delete name;
    }
    void print(){
        cout <<  "The teacher is :" << name  << endl;
    }
};


class School{
    private:
        struct Student;
        struct Classroom;
        struct Floor;
        struct Corridor;
        struct Yard;
        struct Staircase;
    public:
        School(const int &Cyard , const int &Ccorridor,  const int& Cstairs, const int &Cclass);
};


int main(){

    

}
