#include <string>
#include <iostream>
#include "member.h"
using namespace std;

void display_all_members(struct member *member_list, int num_members){
    cout << "\nList of Members\n" << endl;
    for (int i = 0; i < num_members; i++){
        cout << i+1 << ". " << member_list[i].name << endl;
    } 
}
