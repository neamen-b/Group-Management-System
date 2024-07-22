#include <iostream>
#include "assignment.h"
#include "member.h"

using namespace std;

//Function prototype
void welcome_message();

int main(){
    //Number of assignments already created
    int ass_count = 0;

    //
    int remove_count;

    //Max number of assignments
    const int num_assignments_MAX = 5;

    //Max number of members
    const int num_members_MAX = 5;

    //Global array containing all the assignments created
    struct assignment ass_list [num_assignments_MAX];

    //Global array containing all the members in the group
    struct member member_list [num_members_MAX]; 

    //Boolean variable for tracking the creation of members
    bool members_created = false;
    
    //User's option
    int option = 0;

    cout << "\nWelcome to your group management system!\n" ;
    
    //Parent loop that runs until the user wants to quit
    do{
        welcome_message();

        //Loop for validating option
        do{
            cin >> option;
            if (option < 1 || option > 8)
                cout << "\nWarning! Enter a number only from the provided list." << endl;
        }while (option < 1 || option > 8);

        //Will store the latest response of the user for the latest question
        int choice(0);

        switch (option){
            case 1:{//Add member
                cout << "This program requires 5 members (no more no less)." << endl;
                
                for (int i = 0; i < num_members_MAX; i++){
                    cout << "Enter name of member " << i+1 << ": ";
                    cin >> member_list[i].name;
                }
                members_created = true;
                break;
            }
            case 2:{//Add assignment
                if(!members_created){
                    cout << "Please create members first. \n";
                    break;
                }

                //Add all registered members to this assignment
                string names_of_stud [num_members_MAX];
                for (int i = 0; i < num_members_MAX; i++){
                    names_of_stud[i] = member_list[i].name;
                }
                ass_list[ass_count].add_members(names_of_stud);
    
                //Get name of assignment
                cout << "Enter the name of the assignment: " << endl;
                cin >> ass_list[ass_count].ass_name;

                //Get time info about assignment
                ass_list[ass_count].make_timeline();

                //Calculate the number of running assignments on given date
                //and reset member value in assignmetn structure
                int num_of_ass = num_of_ass_on(ass_list, ass_count);
                ass_list[ass_count].set_num_of_ass(num_of_ass);

                //Get maximum mark of assignment
                cout << "Enter the maximum mark of the assignment: " << endl;
                cin >> ass_list[ass_count].max_mark; 
                
                //Assign roles to members of assignment
                assign_roles(ass_list, ass_count, member_list);

                //Increment the assignment count
                ass_count++;
                
                break;
            }
            case 3:{//Remove assignment
                if(!members_created){
                    cout << "Please create members first. \n";
                    break;
                }
                string find_ass;
                //Get name of assignment
                cout << "Enter the name of the assignment: " << endl;
                cin >> find_ass;
                bool found = find_assignment(ass_list, find_ass, ass_count, remove_count);
                if (found){
                    for (int i=remove_count; i<ass_count-1; i++){
                        ass_list[i] = ass_list[i+1];
                    }
                }
                break;
            }
            case 4:{//Display list of assignments
                if(!members_created){
                    cout << "Please create members first. \n";
                    break;
                }
                display_all_assignments(ass_list, ass_count);
                break;
            }
            case 5:{//Display list of members
                if(!members_created){
                    cout << "Please create members first. \n";
                    break;
                }
                display_all_members(member_list, num_members_MAX);
                break;
            }
            case 6:{//Display the roles of one member in each assignment
                if(!members_created){
                    cout << "Please create members first. \n";
                    break;
                }
                display_all_members(member_list, num_members_MAX);
                cout << "Enter the index of the member whose roles you want to see: ";
                cin >> choice;
                member_list[choice-1].get_all_my_roles(ass_list, ass_count);
                break;
            }
            case 7:{//Generate report
                if(!members_created){
                    cout << "Please create members first. \n";
                    break;
                }
                cout << "Enter the index of the assignment you want to generate a report for: ";
                display_all_assignments(ass_list, ass_count);
                cin >> choice;
                generate_report(ass_list[choice-1]);
                break;
            }
            case 8:{//Generate report for all the running assignments
                if(!members_created){
                    cout << "Please create members first. \n";
                    break;
                }
                for (int i=0; i<ass_count;i++){
                    ass_list[i].generate_report();
                } 
                cout<<"A General Report file has been generated for each assignment"<<endl;
                break;
            }
            default:{//Quit
                cout << "\n\nYou've decided to quit the program. Goodbye.\n\n";
                break;
            }       
        }
    } while (option != 9);
    

    return 0;
}

void welcome_message(){
    cout << "\nWhat do you want to do?\n" 
        << "\t 1. Add members\n"
        << "\t 2. Add assignment\n"
        << "\t 3. Remove assignment\n" 
        << "\t 4. Display list of assignments\n" 
        << "\t 5. Display list of members\n"
        << "\t 6. Display the roles of one member in each assignment\n" 
        << "\t 7. Generate report\n" 
        << "\t 8. Generate Report for all assginments"
        << "\t 9. Quit" << endl;  
}