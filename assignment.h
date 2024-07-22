#ifndef ASS_STRUCT
#define ASS_STRUCT

#include <string>
#include <fstream> // For all file operations
#include <chrono>
#include <time.h>
#include <iostream>

using namespace std;

typedef struct assignment{

    //Number of milestones of assignment
    const static int num_of_milestones = 6;

    //Max number of members
    const static int num_members_MAX = 5;

    //Assignment name
    string ass_name;

    //Date the assignment was given
    struct tm * given;
    
    //Date the assignment is due
    struct tm * due;
    
    //Member list for this specific assignment
    string mem_list[num_members_MAX];
    
    //Maximum mark of assignment
    float max_mark;

    //Type of assignment
    string type = "Document Submission";

    //Array containing the dates of each milestone
    string milestones[num_of_milestones];

    //Array containing the list of roles
    string roles[num_members_MAX] = {"Leader", "Treasurer", "Secretary", "Member 1", "Member 2"};

    //Number of assignments on the day this assignment was given
    int num_of_ass;
    
    float member_dep(){
        //Calculate the number of running assignments
        return (5 * max_mark)/(num_of_ass+1);
    }
    float leader_dep(){
        //Calculate the number of running assignments
        return ((7 * max_mark)/(num_of_ass+1));
    }
    string get_role_of(string name){
        for (int i=0;i<num_members_MAX;i++){
            if (name == mem_list[i]){
                return roles[i];
            }
        }
    }
    void add_members(string member_names[num_members_MAX]){
        for (int i = 0; i < num_members_MAX; i++){
            mem_list[i] = member_names[i];
        }
    }
    void make_timeline(){
        time_t rawtime; 
        struct tm * timeinfo;  
        int date[2][3]; 
        for (int i=0; i<2; i++){
            if (i==0){
                cout << "Enter the year, month and day of the given date in order separated by space. " << endl;
            }else{
                cout << "Enter the year, month and day of the due date in order separated by space. " << endl;
            }
            for (int j=0; j<3; j++){
                cin >> date[i][j];
            }
        }
        time ( &rawtime ); 
        given = localtime ( &rawtime ); 
        due = localtime ( &rawtime ); 

        due->tm_year = date[1][0] - 1900;
        due->tm_mon = date[1][1] - 1;
        due->tm_mday = date[1][2];
        
        mktime ( due ); 
        //cout << "Due: " << due->tm_yday << endl;
        int due_in_yday = due->tm_yday;

        given->tm_year = date[0][0] - 1900;
        given->tm_mon = date[0][1] - 1;
        given->tm_mday = date[0][2];

        mktime ( given ); 
        //cout << "Given: " << given->tm_yday << endl;
        int given_in_yday = given->tm_yday;


        //Calculate interval between milestones
        int interval = (due_in_yday - given_in_yday) / (num_of_milestones-1);
        //cout << "Interval: " << interval << endl;
        
        string extratext = "/" + to_string (given->tm_mon+1) + "/" + to_string(given->tm_year+1900);
        milestones[0]= to_string(given->tm_mday) + extratext;
        
        for (int i=1;i<num_of_milestones;i++){
            int day = (given->tm_mday) + (i*interval);
            //cout << "I: " << i << " Day: " << day << " " << given->tm_mday << endl;
            milestones[i] = to_string (day) + extratext;
            //cout << milestones[i] << endl;
        }
    }
    void set_num_of_ass(int new_num_of_ass){
        num_of_ass = new_num_of_ass;
    }

} assignment;

void display_all_assignments(struct assignment *ass_list, int ass_count);

bool find_assignment(struct assignment *ass_list, string find_ass, int ass_count, int remove_count);

void assign_roles(struct assignment *ass_list, int ass_count, struct member *member_list);

bool duplicate_roles(struct assignment *ass_list, int ass_count, struct member *member_list);

int num_of_ass_on(struct assignment *ass_list, int ass_count);

void generate_report(struct assignment ass);

#endif 
