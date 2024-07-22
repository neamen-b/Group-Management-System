#include "assignment.h"
#include "member.h"
#include <iostream>
#include <string>
#include <algorithm> // For shuffle()
#include <random> // For default_random_engine()
using namespace std;

void display_all_assignments(struct assignment *ass_list, int ass_count){
    //Calculate the length of the milestones array
    //to be able to reference the last element in it
    int num_of_milestones = sizeof(ass_list[0].milestones)/sizeof(ass_list[0].milestones[0]);

    cout << "\nList of Assignments\n" << endl;
    for (int i = 0; i < ass_count; i++){
        cout << i+1 << ". " << ass_list[i].ass_name << " due on " << ass_list[i].milestones[num_of_milestones-1] << "." << endl;
    }
}

bool find_assignment(struct assignment *ass_list, string find_ass, int ass_count, int remove_count){
    for (int i=0; i<ass_count; i++){
        if (find_ass == ass_list[i].ass_name){
            return true;
        }
        remove_count ++;
    }
    return false;
}

//Algorithm for randomly assigning roles
void assign_roles(struct assignment * ass_list, int ass_count, struct member *member_list){
    /*
    //Create a new assignment type variable by using the assignment list (ass_list) and
    //the number of already created assignments (ass_count) as an index.
    struct assignment ass = ass_list[ass_count];
    */
    //Access the number of members in the assignment
    int num_members = ass_list[ass_count].num_members_MAX;

    //Algorithm for shuffling an existing array
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); //To obtain a time-based seed
    
    //Shuffling our array until there are no duplicate roles for each member
    do{
        /*
        for (int i = 0; i < 5; i++)
        {
            cout << i+1 << ". " << ass_list[ass_count].roles[i] << endl;
        }
        */
        shuffle(ass_list[ass_count].roles, ass_list[ass_count].roles+num_members, default_random_engine(seed)); 
        seed++; 
    } while(duplicate_roles(ass_list, ass_count, member_list));
    
}

//Function that checks if a member has two similar roles
bool duplicate_roles(struct assignment *ass_list, int ass_count, struct member *member_list){

    //Access the number of members in the assignment
    int num_members = ass_list[0].num_members_MAX;
    //For looping through the members
    for (int i = 0; i < num_members; i++){
        //For looping through the assignments
        for (int j = 0; j < ass_count; j++){
            for (int k = j+1; k <= ass_count; k++){
                if( ass_list[j].get_role_of(member_list[i].name) == ass_list[k].get_role_of(member_list[i].name) ){
                    return true;
                }
            }
        }
    }
    return false;
}

//Function that checks the number of running assignments on a given date
int num_of_ass_on(struct assignment *ass_list, int ass_count){
    int num_of_ass(0);
    struct tm * date = ass_list[ass_count].given;
    //Loop through the array list
    //if date is in between the given and due dates of the assignment, increment
    for (int i = 0; i < ass_count; i++){
        if(date->tm_yday > ass_list[i].given->tm_yday && date->tm_yday < ass_list[i].due->tm_yday){
            num_of_ass++;
        }
    }
    return num_of_ass;
}

void generate_report(struct assignment ass){
    //Generate final report and write to file
    string file_name = ass.ass_name + "_Report.txt";
    ofstream gen_report_stream(file_name.c_str());

    //Input file streams for getting data from the text files
    ifstream rules_stream("rules.txt");
    ifstream timeline_stream("timeline.txt");
    ifstream roles_stream("roles.txt");


    gen_report_stream << "\n\nGENERAL REPORT for " << ass.ass_name << " Assignment \n";
    gen_report_stream << "Type: " << ass.type << "\n";
    gen_report_stream << "Max mark: " << ass.max_mark << "\n";


    gen_report_stream << "\nDeposits:" << "\n";
    gen_report_stream << "Members' deposit = " << ass.member_dep() << "\n";
    gen_report_stream << "Leader's deposit = " << ass.leader_dep() << "\n";
    
    gen_report_stream << "\nMember List" << "\n";
    for (int i=0;i<ass.num_members_MAX;i++){
        gen_report_stream << i+1 << ". " << ass.roles[i] << " -> " << ass.mem_list[i] << "\n"; 
    }

    gen_report_stream << "\nDates for each Milestone in The Timeline" << "\n";
    for (int i = 0, j = 0; i <= 100; i+=20, j++){
        gen_report_stream << (i/20)+1 << ". " << i << "% => " << ass.milestones[j] << "\n";
    }
    gen_report_stream << "\n";

    //String for holding one line of each file to be read
    string one_line="";

    //Read from timeline.txt and write to report.txt
    while(!timeline_stream.eof()){
        getline(timeline_stream, one_line);
        gen_report_stream << one_line << "\n";
    }

    //Read from rules.txt and write to report.txt
    while(!rules_stream.eof()){
        getline(rules_stream, one_line);
        gen_report_stream << one_line << "\n";
    }

    //Read from roles.txt and write to report.txt
    while(!roles_stream.eof()){
        getline(roles_stream, one_line);
        gen_report_stream << one_line << "\n";
    }

    gen_report_stream.close();
    timeline_stream.close();
    rules_stream.close();
    roles_stream.close();
}