#include <iostream>
#include <string>

using namespace std;

const int out = 0;
const int yard = 1;
const int staircase = 2;
const int corridor = 3;
const int clas = 4;



struct Student{
    string student_name;
    int floor_level, class_number, where_is;

    Student( const char* s, const int &floor_lv, const int & class_nu, const int& where_i):
                 student_name(s), floor_level(floor_lv), class_number(class_nu), where_is(out){
                    
                    cout << "A new student has been created! " ;
                    print_student();
    }
    ~Student(){
        cout << "A Student to be destroyed! ";
        print_student();
    }
    void print_student(){
        for (int i = 0 ; i < student_name.length() ; i++)
            cout << student_name[i];
    }
    bool same_students(Student n){ 
        int x = this->student_name.compare(n.student_name);

        if ( x== 0) return true;
        else return false;
    }
};

struct Teacher{
    string teacher_name;
    int floor_level, class_number;
    bool is_inside;
    
    Teacher( const char* t, const int &flo_level, const int &cla_number): teacher_name(t), floor_level(flo_level), class_number(cla_number), is_inside(false){
           cout << "A new Teacher has been created! ";
           print_teacher();
           cout << endl;
           
    }
    ~Teacher(){
        cout << "A Teacher to be destroyed! ";
        print_teacher();
    }
    void print_teacher(){
        for (int i = 0 ; i < teacher_name.length() ; i++)
            cout << teacher_name[i];
            
    }
};

struct Class{
    Student** table_of_students;
    Teacher* teacher;
    const int Cclass, floor_no, number_of_class;
    int current_students_in;
    bool can_join_class, teacher_in;

    Class(const int &Ccla, const int &flo, const int &num_of_class):
        Cclass(Ccla), floor_no(flo), number_of_class(num_of_class), current_students_in(0), can_join_class(true), teacher_in(false) { 
        
            table_of_students = new Student*[Cclass];
            for (int i =0 ; i < Cclass ; i++)
                table_of_students[i] = NULL;
            
            teacher = NULL;     
            cout << "A new class has been created! Floor of class: " << floor_no << " Number of class: " << number_of_class << endl;   
    }
    ~Class(){
            for (int i =0 ; i < Cclass ; i++)
            delete table_of_students[i];
            
        delete table_of_students;
        cout << "Class has been destoyed! Floor of class: " << floor_no << " Number of class: " << number_of_class << endl;
    }
    void place_student(Student* s){
        table_of_students[current_students_in] = s;
        current_students_in++;
        if ( current_students_in == Cclass) can_join_class = false;
        s->print_student();
        cout << " has entered Class " << number_of_class;
    }
    void place_teacher(Teacher* t){
        teacher = t;
        can_join_class = false;
        teacher_in = true;
        teacher->print_teacher();
        cout << "- Teacher has entered the classroom " << number_of_class << ".";
    }
    bool can_join(){
        return can_join_class;
    }
};


int main(){
    Student p("Panos", 1,2,3);
    Student m("Maria",4,5,6);

    p.print_student();
    m.print_student();

    // bool e = p.same_students(m);
    
    // bool q = p.same_students(p);
    
    Teacher t1("Teacher Panos", 1,2);
    Teacher t2("Teacher Maria", 3,4);
    
    t1.print_teacher();
    cout << endl;
    t2.print_teacher();
    cout << endl;
    
    Class clas1(100,1,2);
    clas1.place_student(&p);
    cout << endl;
    clas1.place_teacher(&t1);
    cout << endl;
    if ( clas1.can_join() ) clas1.place_student(&m);
    else {
        cout << "Student ";
        m.print_student();
        cout << " cannot join class." ;
        cout << endl;
    }
    
}
