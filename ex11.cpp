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
                    cout << endl;
    }
    ~Student(){
        cout << "A Student to be destroyed! ";
        print_student();
        cout << endl;
    }
    void print_student(){
        for (int i = 0 ; i < student_name.length() ; i++)
            cout << student_name[i];
    }
    string get_name(){
        return student_name;
    }
    bool same_students(Student* n){ 
        int x = this->student_name.compare(n->get_name());

        if ( x== 0) return true;
        else return false;
    }
    int get_class(){
        return class_number;
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
        cout << endl;
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
        // for (int i =0 ; i < Cclass ; i++) 
        //     if( table_of_students[i] != NULL ) delete table_of_students[i];
        delete[] table_of_students;

        cout << "Class has been destoyed! Floor of class: " << floor_no << " Number of class: " << number_of_class << endl;
    }
    void place_student(Student* s){
        table_of_students[current_students_in] = s;
        current_students_in++;
        if ( current_students_in == Cclass) can_join_class = false;
        s->print_student();
        cout << " has entered Class " << number_of_class << endl;;
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

//When removing a student from Corridor, we must keep its adress value.
struct Corridor{ 
    Student** table_of_students;
    Class** table_of_classes;
    const int Cclass, Ccorr, floor_number;
    int current_students_in;
    bool can_join_corr;

    Corridor(const int &Ccla, const int &Ccor, const int &flo_number):
            Cclass(Ccla), Ccorr(Ccor), floor_number(flo_number), can_join_corr(true), current_students_in(0) {
                table_of_students = new Student* [Ccorr];
                table_of_classes = new Class*[6];

                for (int i =0 ; i < 6 ; i++)
                    table_of_classes[i] = new Class(Cclass, floor_number, (floor_number-1)*6 + i+1);

                for (int i = 0 ; i <  Ccorr ; i++)
                    table_of_students[i] = NULL; //Initialization
                
                cout << "Corridor of floor " << floor_number << " created!" << endl;
    }
    ~Corridor(){
        // for (int i = 0 ; i < Cclass ; i++)
        //     if (table_of_students[i] != NULL) delete table_of_students[i];
        delete [] table_of_students;
        
        for (int i = 0 ; i < 6 ; i++)
            if( table_of_classes[i] != NULL) delete table_of_classes[i];
        delete [] table_of_classes;

        cout << "Corridor of floor " << floor_number << " deleted!" << endl;
    }
    void place_student(Student *s){
        table_of_students[current_students_in] = s;
        current_students_in++;
        if (current_students_in == Ccorr) can_join_corr = false;
        s->print_student();
        cout << " enters corridor of floor " << floor_number << "." << endl;
    }
    void remove_student(Student *s){ 
        for (int i = 0 ; i <  current_students_in ; i++){
            if ( s->same_students( table_of_students[i]) ) {
                table_of_students[i] = NULL;
                can_join_corr = true;
                current_students_in--;
                s->print_student();
                cout << " exits corridor of floor " << floor_number << "." << endl;
                fix_table();
                break;
            }
        }
    }
    void fix_table(){ //Φροντίζει ώστε τα στοιχεία του πίνακα να είναι στην αρχή
        for (int j = Ccorr-1 ; j >= 0 ; j--){
            if ( table_of_students[j] == NULL) continue;

            for (int i = 0 ; i < Ccorr ; i++){
                if ( i == j ) return;
                if ( table_of_students[i] != NULL ) continue;

                table_of_students[i] = table_of_students[j];
                table_of_students[j] = NULL;
                break;
            }
        }
    }
    void student_allocation(){
        int i = 0;
        while( table_of_students[i] != NULL ){
            if( table_of_classes[ (table_of_students[i]->get_class()-1)/6 ]->can_join() ){
                Student * s = table_of_students[i];
                remove_student(s);
                table_of_classes[ s->class_number - (floor_number-1)*6 ]->place_student( s );
            }
        }
        fix_table();
    }
    void print(){
        cout << "People in Corridor of floor " << floor_number << " are:" << endl;
        for (int i = 0 ; i < Ccorr ; i++){
            if (table_of_students[i] != NULL ) {
                table_of_students[i]->print_student();
                cout << endl;
            }
        }
            
    }
    bool can_join_corridor(){
        return can_join_corr;
    }
    int get_floor(){
        return floor_number;
    }
};

//Στο παρόν παράδειγμα θεωρώ ότι όποιος δε χωράει στο διάδρομο του ορόφου, δε χωράει και στον όροφο
//άρα η χωρητικότητα του διαδρόμου είναι ίδια με το floor.
//Τέλος, όταν κάποιος δε χωράει στον όροφο, παραμένει στις σκάλες.
struct Floor{ 
    Corridor corridor;
    // const int Cclass, Ccorr,floor_number;
    Floor(const int &Cclass, const int &Ccorridor, const int &floor_number):corridor( Cclass, Ccorridor, floor_number) {

                cout << "Floor " << floor_number << " has been created!" << endl;
            }
    ~Floor(){
        cout << "Floor " << corridor.get_floor() << " is beeing destroyd!" << endl;
    }
    bool can_join(){
        return corridor.can_join_corridor();
    }
    void place_student(Student *s){
        s->print_student();
        cout << "enters floor " << corridor.get_floor() << "." << endl;
        corridor.place_student(s);
    }
    void remove_student(Student *s){
        s->print_student();
        cout << "exits floor " << corridor.get_floor() << "." << endl;
        corridor.remove_student(s);
    }
    void print(){
        cout << " Floor number " << corridor.get_floor() << " contains: " << endl;
        corridor.print();
    }
    void student_allocation(){
        corridor.student_allocation();
    }
};


struct Stairs{
    Student** table_of_students;
    Floor** table_of_floors;
    const int Cclass, Ccorr, Cstair;
    int current_students_in;
    bool can_join_stairs;

    Stairs(const int &Ccla, const int &Ccor, const int & Csta):
            Cclass(Ccla), Ccorr(Ccor), Cstair(Csta), can_join_stairs(true), current_students_in(0){
                
                table_of_students = new Student*[Cstair];
                for (int i = 0 ; i < Cstair ; i++)
                    table_of_students[i] = NULL;

                table_of_floors = new Floor*[3];
                for (int i = 0 ; i < 3 ; i++)
                    table_of_floors[i]= new Floor(Cclass,Ccorr,i+1);
    }
    ~Stairs(){
        for (int i = 0 ; i < 3 ; i++)
            delete table_of_floors[i];
        delete[] table_of_floors;

        delete[] table_of_students;
    }
    bool can_join(){
        return can_join_stairs;
    }
    void place_student(Student *s){
        table_of_students[current_students_in] = s;
        current_students_in++;
        if (current_students_in == Ccorr) can_join_stairs = false;
        s->print_student();
        cout << " enters stairs." << endl;

    }
    void remove_student(Student *s){
        for (int i = 0 ; i <  current_students_in ; i++){
            if ( s->same_students( table_of_students[i]) ) {
                table_of_students[i] = NULL;
                can_join_stairs = true;
                current_students_in--;
                s->print_student();
                cout << " exits stairs." << endl;
                fix_table();
                break;
            }
        }
    }
    void fix_table(){ //Φροντίζει ώστε τα στοιχεία του πίνακα να είναι στην αρχή
        for (int j = Ccorr-1 ; j >= 0 ; j--){
            if ( table_of_students[j] == NULL) continue;

            for (int i = 0 ; i < Ccorr ; i++){
                if ( i == j ) return;
                if ( table_of_students[i] != NULL ) continue;

                table_of_students[i] = table_of_students[j];
                table_of_students[j] = NULL;
                break;
            }
        }
    }
    void allocate_students(){
        int i = 0;
        while( table_of_students[i] != NULL ){

            if ( table_of_floors[ table_of_students[i]->get_class()/6 ]->can_join() ){//if the floor can accept more ppl
                Student *s = table_of_students[i];
                remove_student(s);
                table_of_floors[s->get_class()/6]->place_student(s);
            }
        }
        fix_table();
        table_of_floors[0]->student_allocation();
        table_of_floors[1]->student_allocation();
        table_of_floors[2]->student_allocation();
    }
    void print(){
        cout << "People in stairs are: " << endl;
        for (int i = 0 ; i < Cstair ; i++){
            if( table_of_students[i] == NULL ) continue;
            table_of_students[i]->print_student();
            cout << endl;
        }
        table_of_floors[0]->print();
        table_of_floors[1]->print();
        table_of_floors[2]->print();
    }
};


int main(){
        // floor lvl, class_no, where_is
        Student a1("bob1", 1,1,0);
        Student a2("bob2",1,1,0);
        Student a3("bob3",1,8,0);
        Student a4("bob4",1,8,0);
        Student a5("bob5",1,8,0);
        Student a6("bob6",1,2,0);
        Student a7("bob7",1,3,0);
        Student a8("bob8",1,15,0);
        Student a9("bob9",1,3,0);
        Student a10("bob10",1,17,0);
        Student a11("bob11",1,4,0);
        Student a12("bob12",1,4,0);
        Student a13("bob13",1,2,0);
        Student a14("bob14",1,9,0);
        Student a15("bob15",1,10,0);
        Student a16("bob16",1,11,0);
        Student a17("bob17",1,12,0);
        Student a18("bob18",1,13,0);
        
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
    
    
    
    // Teacher t1("Teacher Panos", 1,2);
    // Teacher t2("Teacher Maria", 3,4);
    
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

    Stairs stair(20,50,100);

    for (int i =0 ; i < 18 ; i++)
        stair.place_student(table[i]);

    // floor1.print();
    // floor1.student_allocation();
    stair.allocate_students();

    // one.remove_student(table[10]);
    // one.remove_student(table[13]);
    // one.remove_student(table[15]);

    // one.print();

    return 0;    
}
