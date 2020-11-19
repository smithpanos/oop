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
        cout << endl;
    }
    bool same_students(Student n){ 
        int x = this->student_name.compare(n.student_name);

        if ( x== 0) return true;
        else return false;
    }
};


int main(){
    Student p("Panos", 1,2,3);
    Student m("Maria",4,5,6);

    p.print_student();
    m.print_student();

    bool e = p.same_students(m);
    
    bool q = p.same_students(p);
    
    
}
