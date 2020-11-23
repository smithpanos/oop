#include <string>


struct Student{
    std::string name;
    int floor_level, class_number, where_is;

    Student( const char* Name, const int &floor, const int & class_no, const int& where_is);
    ~Student();
    int get_class();
    int get_floor();
    void print();
    bool same_student( Student * );
    std::string get_name();
    void set_state(int);
};

struct Teacher{
    std::string name;
    int floor_level, class_number;
    bool is_inside;
    Teacher( const char* Name, const int &floor, const int & class_no);
    ~Teacher();
    int get_class();
    int get_floor();
    void print();
    void set_if_inside(bool);
};

struct Class{
    Student** table_of_students;
    Teacher* teacher;
    const int Cclass, floor_level, class_number;
    int current_students_in;
    bool can_join_in, teacher_in;

    Class(const int &Ccla, const int &flo, const int &num_of_class);
    ~Class();
    int get_class();
    int get_floor();
    void print();
    bool can_join();
    void place_student(Student *s);
    void place_teacher(Teacher *t);
    bool teacher_inside();
    void dont_enter();
};
struct Corridor{
    Student** table_of_students;
    Class** table_of_classes;
    const int Cclass, Ccorr, floor_level;
    int current_students_in;
    bool can_join_in;

    Corridor(const int &Ccla, const int &Ccor, const int &flo_level);
    ~Corridor();
    int get_floor();
    void print();
    bool can_join();
    void place_student(Student *s);
    void place_teacher(Teacher *t);
    void remove_student(Student *s);
    void student_allocation();
};

struct Floor{
    Corridor corridor;

    Floor(const int &Cclass, const int &Ccorridor, const int &floor_number);
    ~Floor();
    int get_floor();
    void print();
    bool can_join();
    void place_student(Student *s);
    void place_teacher(Teacher *t);
    void remove_student(Student *s);
    void student_allocation();
};

struct Stairs{
    Student** table_of_students;
    Floor** table_of_floors;
    const int Cclass, Ccorr, Cstair;
    int current_students_in;
    bool can_join_in;

    Stairs(const int &Ccla, const int &Ccor, const int & Csta);
    ~Stairs();
    void print();
    bool can_join();
    void place_student(Student *s);
    void place_teacher(Teacher *t);
    void remove_student(Student *s);
    void student_allocation();
};

struct Yard{
    Student** table_of_students;
    Stairs stairs;
    const int Cclass, Ccorr, Cstair, Cyard;
    int current_students_in;
    bool can_join_in;

    Yard( const int & Ccla, const int &Ccor, const int & Cstai, const int Cya);
    ~Yard();
    void print();
    bool can_join();
    void place_student(Student *s);
    void place_teacher(Teacher *t);
    void remove_student(Student *s);
    void student_allocation();
};

struct inside_error_checker{

};

class School{
    private:
        Yard yard;
        const int Cclass, Ccorr, Cstair, Cyard;
        int current_students_in;
        bool can_join_in;
    
    public:
        School( const int & Ccla, const int &Ccor, const int & Cstai, const int Cya);
        ~School();
        void print();
        bool can_join();
        void place_student(Student *s);
        void place_teacher(Teacher* t);
        void student_allocation();
};
#include <iostream>
#include <string>
#include </home/sideras/oop/homework1/ex1/sch.h>
#include <assert.h>

using namespace std;

int out1 = 0;
int yard1 = 1;
int staircase1 = 2;
int corridor1 = 3;
int class1 = 4;

// struct Student{
//     std::string name;
//     int floor_level, class_number, where_is;
    Student::Student(const char* Name, const int &floor, const int & class_no, const int& where_is):
                    name(Name),floor_level(floor), class_number(class_no), where_is(out1) {

                        cout << "A new student has been created! " ;
                        print();
                        cout << endl;
                        return;
    }
    Student::~Student(){
        cout << "A Student to be destroyed! ";
        print();
        cout << endl;
        return;
    }
    int Student::get_class(){
        return class_number;
    }
    int Student::get_floor(){
        return floor_level;
    }
    void Student::print(){
        for (int i = 0 ; i < name.length() ; i++)
            cout << name[i];
        return;
    }
    string Student::get_name(){
            return name;
        }
    bool Student::same_student( Student *n ){
        int x = this->name.compare(n->get_name());

        if ( x== 0) return true;
        else return false;
    }
    void Student::set_state(int state){
        where_is=state;
        return;
    }


// struct Teacher{
//     std::string name;
//     int floor_level, class_number;
//     bool is_inside;

    Teacher::Teacher( const char* Name, const int &floor, const int & class_no):
                    name(Name), floor_level(floor), class_number(class_no), is_inside(false){
        cout << "A new Teacher has been created! ";
        print();
        cout << endl;
        return;
    }
    Teacher::~Teacher(){
        cout << "A Teacher to be destroyed! ";
        print();
        cout << endl;
        return;
    }
    int Teacher::get_class(){
        return class_number;
    }
    int Teacher::get_floor(){
        return floor_level;
    }
    void Teacher::print(){
        for (int i = 0 ; i < name.length() ; i++)
            cout << name[i];
        return;
    }
    void Teacher::set_if_inside(bool temp){
        is_inside = temp;
        return;
    }


// struct Class{
//     Student** table_of_students;
//     Teacher* teacher;
//     const int Cclass, floor_level, class_number;
//     int current_students_in;
//     bool can_join_in, teacher_in;

    Class::Class(const int &Ccla, const int &flo, const int &num_of_class):
                Cclass(Ccla), floor_level(flo), class_number(num_of_class), 
                teacher_in(false), current_students_in(0), teacher(NULL)  {

                    can_join_in = true;
                    cout << "A new class has been created! Floor of class: " 
                    << floor_level << " Number of class: " << class_number << endl;

                    table_of_students = new Student* [Cclass];
                    for (int i = 0 ; i < Cclass ; i++ )
                        table_of_students[i] = NULL;

                    return;
    }
    Class::~Class(){

        cout << "Class has been destoyed! Floor of class: " 
        << floor_level << " Number of class: " << class_number << endl;

        delete[] table_of_students;
        return;
    }
    int Class::get_class(){
        return class_number;
    }
    int Class::get_floor(){
        return floor_level;
    }
    void Class::print(){

        cout << "People in class " << class_number + (floor_level-1)*6 << " are: " << endl;
        if (teacher_in == true) {
            teacher->print();
            cout << endl;
        }

        for (int i = 0 ; i < Cclass ; i++){
            
            if( table_of_students[i] != NULL )
                table_of_students[i]->print();
                cout << endl;
            } 
        return;
    }
    bool Class::can_join(){
        return can_join_in;
    }
    void Class::place_student(Student *s){
        s->print();
        cout << " has entered Class " << class_number << endl;
        for (int i = 0 ; i < Cclass ; i++){
            if (table_of_students[i] == NULL){
                table_of_students[i]=s;
                current_students_in++;
                s->set_state( class1 );
                if ( current_students_in ==  Cclass) can_join_in = false;
                return;
            }
        }
        assert(0);
    }
    void Class::place_teacher(Teacher *t){
        cout << "Teacher ";
        t->print();
        cout << " has entered classroom " << class_number << endl;

        teacher=t;
        teacher_in=true;
        can_join_in=false;
        t->set_if_inside(true);
        return;
    }
    bool Class::teacher_inside(){
        return teacher_in;
    }
    void Class::dont_enter(){
        this->can_join_in = false;
        return;
    }



// struct Corridor{
//     Student** table_of_students;
//     Class** table_of_classes;
//     const int Cclass, Ccorr, floor_level;
//     int current_students_in;
//     bool can_join;

    Corridor::Corridor(const int &Ccla, const int &Ccor, const int &flo_level):
        Cclass(Ccla), Ccorr(Ccor), floor_level(flo_level),
        can_join_in(true), current_students_in(0) {

            cout << "Corridor of floor " << floor_level << " created!" << endl; 

            table_of_students = new Student*[Ccorr];
            for (int i = 0 ; i < Ccorr ; i++)
            table_of_students[i] = NULL;

            table_of_classes = new Class*[6];
            for (int i = 0 ; i < 6 ; i++)                           // i+1 = Class number
                table_of_classes[i] = new Class(Cclass,  floor_level,  i+1);
            return;
    }
    Corridor::~Corridor(){
        cout << "Corridor of floor " << floor_level << " deleted!" << endl;
        
        for (int i = 0 ; i < 6 ; i++)
                delete table_of_classes[i];
        delete[] table_of_classes;

        delete[] table_of_students;
        return;
    }
    int Corridor::get_floor(){
        return floor_level;
    }
    void Corridor::print(){
        cout << "People in Corridor of floor " << floor_level << " are:" << endl;

        for (int i = 0 ; i < Ccorr ; i++){

            if(table_of_students[i] != NULL ){
                table_of_students[i]->print();
                cout << endl;
            }

        }
        for (int i = 0 ; i < 6 ; i++)
            table_of_classes[i]->print();
        return;
    }
    bool Corridor::can_join(){
        return can_join_in;
    }
    void Corridor::place_student(Student *s){
        s->print();
        cout << " has entered Corridor of floor " << floor_level << endl;
        for (int i = 0 ; i < Ccorr ; i++){

            if (table_of_students[i] == NULL){
                table_of_students[i] = s;
                current_students_in++;
                s->set_state(corridor1);
                if ( current_students_in ==  Ccorr) can_join_in = false;
                return;
            }
        }
        assert(0);
    }
    void Corridor::place_teacher(Teacher *t){
        table_of_classes[ t->get_class()-1 ]->place_teacher ( t );
        return;
    }
    void Corridor::remove_student(Student *s){
        for (int i = 0 ; i < Ccorr ; i++){
            if (table_of_students[i] == NULL) continue;

            if( table_of_students[i]->same_student(s) ){
                s->print(); cout << " exits corridor of floor " << floor_level << "." << endl;
                table_of_students[i] = NULL;
                can_join_in = true;
                current_students_in--;
                return;
            }
        }
        assert(0);
    }
    void Corridor::student_allocation(){
        for (int i = 0 ; i < Ccorr ; i++){

            if (table_of_students[i] == NULL ) continue;
            
            Student* s = table_of_students[i];
            cout << "HELPER! Student ";
            s->print();
            cout << " class " << s->get_class() << endl;
            if (table_of_classes[ s->get_class()%6]->can_join() == true ){
                table_of_classes[ s->get_class()%6]->place_student(s);
                remove_student( s );
            }else if(table_of_classes[ s->get_class()%6]->can_join() == false){ 
                s->print();
                cout << " cannot join class " << s->get_class() << endl;
            }

        }
        return;
    }


// struct Floor{
//     Corridor corridor;

    Floor::Floor(const int &Cclass, const int &Ccorridor, const int &floor_number):
                corridor(Cclass,Ccorridor, floor_number) {
            
        cout << "Floor " << floor_number << " has been created!" << endl;
    }
    Floor::~Floor(){
        cout << "Floor " << corridor.get_floor() << " is beeing destroyd!" << endl;
    }
    int Floor::get_floor(){
        return corridor.get_floor();
    }
    void Floor::print(){
        cout << "Floor number " << corridor.get_floor() << " contains: " << endl;
        corridor.print();
    }
    bool Floor::can_join(){
        return corridor.can_join();
    }
    void Floor::place_student(Student *s){
        s->print();
        cout << " has entered Floor " << corridor.get_floor() << endl;
        corridor.place_student(s);
        return;
    }
    void Floor::place_teacher(Teacher *t){
        corridor.place_teacher(t);
    }
    void Floor::remove_student(Student *s){
        s->print();
        cout << " has left floor " << corridor.get_floor() << "." << endl;
        corridor.remove_student(s);
    }
    void Floor::student_allocation(){
        corridor.student_allocation();
    }

// struct Stairs{
//     Student** table_of_students;
//     Floor** table_of_floors;
//     const int Cclass, Ccorr, Cstair;
//     int current_students_in;
//     bool can_join_in;

    Stairs::Stairs(const int &Ccla, const int &Ccor, const int & Csta):
                    Cclass(Ccla), Ccorr(Ccor), Cstair(Csta),
                    can_join_in(true), current_students_in(0)  {
        
        cout << "New Stairs has been created!" << endl;

        table_of_students = new Student*[Cstair];
        for (int i = 0 ; i < Cstair ; i++)
            table_of_students[i] = NULL;

        table_of_floors = new Floor*[3];
        table_of_floors[0] = new Floor(Cclass, Ccorr, 1);
        table_of_floors[1] = new Floor(Cclass, Ccorr, 2);
        table_of_floors[2] = new Floor(Cclass, Ccorr, 3);
    return;
    }
    Stairs::~Stairs(){
        cout << "Stairs has been destroyed!" << endl;

        delete[] table_of_students;

        delete table_of_floors[0];
        delete table_of_floors[1];
        delete table_of_floors[2];
        delete[] table_of_floors;
        return;
    }
    void Stairs::print(){
        cout << "People in stairs are: " << endl;

        for (int i = 0 ; i < Cstair ; i++){
            if (table_of_students[i] == NULL )continue;
            table_of_students[i]->print();
            cout << endl;
        }

        table_of_floors[0]->print();
        table_of_floors[1]->print();
        table_of_floors[2]->print();
        return;
    }
    bool Stairs::can_join(){
        return can_join_in;
    }
    void Stairs::place_student(Student *s){
        s->print();
        cout << " has entered Stairs " << endl;
        for (int i = 0 ; i <  Cstair ; i++){
            if (table_of_students[i] == NULL){
                table_of_students[i]=s;
                current_students_in++;
                s->set_state(staircase1);
                if(current_students_in ==  Cstair) can_join_in = false;
                return;
            }
        }
        assert(0);
    }
    void Stairs::place_teacher(Teacher *t){
        table_of_floors[ t->get_floor() - 1 ]->place_teacher(t);
        return;
    }
    void Stairs::remove_student(Student *s){
        for (int i =0 ; i < Cstair ; i++){
            if (table_of_students[i] == NULL) continue;

            if (table_of_students[i]->same_student(s) ){
                s->print(); cout << " exits Stairs." << endl;
                table_of_students[i] = NULL;
                can_join_in = true;
                current_students_in--;
                return;
            }
        }
        assert(0);
    }
    void Stairs::student_allocation(){
        for (int i = 0 ; i < Cstair ; i++) {
            if (table_of_students[i] == NULL) continue;

            Student* s = table_of_students[i];
            if( table_of_floors[ s->get_floor() - 1]->can_join() ){
                remove_student(s);
                table_of_floors[s->get_floor() - 1]->place_student(s);
            }
        }
        table_of_floors[0]->student_allocation();
        table_of_floors[1]->student_allocation();
        table_of_floors[2]->student_allocation();
    }

// struct Yard{
//     Student** table_of_students;
//     Stairs stairs;
//     const int Cclass, Ccorr, Cstair, Cyard;
//     int current_students_in;
//     bool can_join_in;

    Yard::Yard( const int & Ccla, const int &Ccor, const int & Cstai, const int Cya):
                Cclass(Ccla), Ccorr(Ccor), Cstair(Cstai), Cyard(Cya),
                can_join_in(true), current_students_in(0), stairs(Ccla, Ccor, Cstai){

        cout << "A new Yard has been created!" << endl;

        table_of_students = new Student*[Cyard];
                for (int i = 0 ; i < Cyard ; i++)
                    table_of_students[i] = NULL; 
        return;
    }
    Yard::~Yard(){
        cout << "A Yard to be destroyed!" << endl;
        delete[] table_of_students;
        return;
    }
    void Yard::print(){
        cout << "People in Yard are: " << endl;

        for (int i = 0 ; i < Cyard ; i++){
            if( table_of_students[i] == NULL ) continue;
            table_of_students[i]->print();
            cout << endl;
        }

        stairs.print();
        return;
    }
    bool Yard::can_join(){
        return can_join_in;
    }
    void Yard::place_student(Student *s){
        s->print();
        cout << " has entered Yard " << endl;

        for (int i = 0 ; i < Cyard ; i++){
            if (table_of_students[i] ==  NULL){
                table_of_students[i] = s;
                current_students_in++;
                if(current_students_in == Cyard) can_join_in = false;
                s->set_state(yard1);
                return;
            }
        }
        assert(0);
    }
    void Yard::place_teacher(Teacher *t){
        stairs.place_teacher(t);
        return;
    }
    void Yard::remove_student(Student *s){
        for (int i =0 ; i < Cyard ; i++){
            if (table_of_students[i] == NULL) continue;

            if (table_of_students[i]->same_student(s) ){
                s->print(); cout << " exits Yard." << endl;
                table_of_students[i] = NULL;
                can_join_in = true;
                current_students_in--;
                return;
            }
        }
        assert(0);
    }
    void Yard::student_allocation(){
        for (int i = 0 ; i < Cyard ; i++) {
            if (table_of_students[i] == NULL) continue;

            Student* s = table_of_students[i];
            if( stairs.can_join() ){
                remove_student(s);
                stairs.place_student(s);
            }
        }
        stairs.student_allocation();
    }


// struct inside_error_checker{

// };

// class School{
//     private:
//         Yard yard;
//         const int Cclass, Ccorr, Cstair, Cyard;
//         int current_students_in;
//         bool can_join_in;
    
        School::School( const int & Ccla, const int &Ccor, const int & Cstai, const int Cya):
                        Cclass(Ccla), Ccorr(Ccor), Cstair(Cstai), Cyard(Cya),
                        can_join_in(true), current_students_in(0), yard(Ccla, Ccor, Cstai, Cya){
            cout << "A New School has been created!" << endl;
            return;
        }
        School::~School(){
            cout << "A School to be destroyed!" << endl;
            return;
        }
        void School::print(){
            cout << "School life consists of: " << endl;
            yard.print();
            return;
        }
        bool School::can_join(){
            // return can_join_in;
        }
        void School::place_student(Student *s){
            s->print();
            cout << " has entered School " << endl;
            yard.place_student(s);
        }
        void School::place_teacher(Teacher* t){
            yard.place_teacher(t);
        }
        void School::student_allocation(){
            yard.student_allocation();
        }



int main(){
        // floor lvl, class_no, where_is
        Student a1("bob1", 1,1,0);
        Student a2("bob2",1,2,0);
        Student a3("bob3",1,3,0);
        Student a4("bob4",1,4,0);
        Student a5("bob5",1,5,0);
        Student a6("bob6",1,6,0);
        Student a7("bob7",2,7,0);
        Student a8("bob8",2,8,0);
        Student a9("bob9",2,9,0);
        Student a10("bob10",2,10,0);
        Student a11("bob11",2,11,0);
        Student a12("bob12",2,12,0);
        Student a13("bob13",3,13,0);
        Student a14("bob14",3,14,0);
        Student a15("bob15",3,15,0);
        Student a16("bob16",3,16,0);
        Student a17("bob17",3,17,0);
        Student a18("bob18",3,18,0);
        
        Student* table[18];
        table[0] = &a1;
        table[1] = &a2;
        table[2] = &a3;
        table[3] = &a4;
        table[4] = &a5;
        table[5] = &a6;
        table[6] = &a7;
        table[7] = &a8;
        table[8] = &a9;
        table[9] = &a10;
        table[10] = &a11;
        table[11] = &a12;
        table[12] = &a13;
        table[13] = &a14;
        table[14] = &a15;
        table[15] = &a16;
        table[16] = &a17;
        table[17] = &a18;


    


    // a1.print_student();
    // cout << endl;
    // a2.print_student();
    // cout << endl;
    // a3.print_student();
    // cout << endl;
    // a4.print_student();
    // cout << endl;
    // a5.print_student();
    // cout << endl;
    // a6.print_student();
    // cout << endl;
    // a7.print_student();
    // cout << endl;
    // a8.print_student();
    // cout << endl;
    // a9.print_student();
    // cout << endl;
    // a10.print_student();
    // cout << endl;
    // a11.print_student();
    // cout << endl;
    
    
    
    Teacher t1("Teacher Panos", 1,2);
    Teacher t2("Teacher Maria", 3,4);
    
    // t1.print_teacher();
    // cout << endl;
    // t2.print_teacher();
    // cout << endl;
    
    // Class clas1(100,1,2);
    // clas1.place_student(&p);
    // cout << endl;
    // clas1.place_teacher(&t1);
    // cout << endl;
    // if ( clas1.can_join() ) clas1.place_student(&m);
    // else {
    //     cout << "Student ";
    //     m.print_student();
    //     cout << " cannot join class." ;
    //     cout << endl;
    // }

    // Corridor one(20,50,1);
    // Corridor two(20,50,2);

    // Floor floor1(20,50,1);
    // Floor floor2(20,50,2);

    School sch(20,50,100,100);

    for (int i =0 ; i < 18 ; i++)
        sch.place_student(table[i]);

    sch.place_teacher(&t1);
    sch.place_teacher(&t2);
    
    // floor1.print();
    // floor1.student_allocation();
    sch.student_allocation();
    sch.print();

    // one.remove_student(table[10]);
    // one.remove_student(table[13]);
    // one.remove_student(table[15]);

    // one.print();

    return 0;    
}
