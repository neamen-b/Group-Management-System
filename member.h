#ifndef MEMBER_STRUCT
#define MEMBER_STRUCT

#include <iostream>
#include "assignment.h"

using namespace std;

//Definition of member structure
typedef struct member{
    string name;
    string get_role_in(struct assignment ass_name){
        return ass_name.get_role_of(name);
    }
    void get_all_my_roles(struct assignment *ass_list, int ass_count){
        cout << "\nList of roles for " << name << ":" << endl;
        for (int i = 0; i < ass_count; i++){
           cout << i+1 << ". " << ass_list[i].get_role_of(name) << " in " << ass_list[i].ass_name << endl;
        }
    }
} member;

void display_all_members(struct member *member_list, int num_members);

#endif