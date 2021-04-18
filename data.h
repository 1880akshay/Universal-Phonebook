#include "structure.h"
using namespace std;

#ifndef DATA_H
#define DATA_H

string getfield(char* line, int num) {
    string s="";
    if(num==1) {
        for(int i=0; ; i++) {
            if(line[i]!=',') s+=line[i];
            else break;
        }
    }
    else if(num==2) {
        int ind;
        for(int i=0; ; i++) {
            if(line[i]==',') {
                ind=i;
                break;
            }
        }
        for(int i=ind+1; ; i++) {
            if(line[i]=='\n' || line[i]=='\0') break;
            s+=line[i];
        }
    }
    return s;
}

void populateData(book* phone_book) {
    table temp;
    for(int i=0; i<5; i++) {
        temp.parent=i;
        temp.ind=i;
        (*phone_book).name_number.push_back(temp);
    }
    FILE* filePointer=fopen("data.csv", "r");
    if(filePointer==NULL) return;
    char line[256];
    int ind;
    srand(time(NULL));
    while (fgets(line, 256, filePointer)) {
        string name=getfield(line, 1);
        string number=getfield(line, 2);
        ind=rand()%5;
        (*phone_book).name_number.array[ind].data.insert(name, number);
        (*phone_book).name_number.array[ind].rows++;
    }
    fclose(filePointer);
}

#endif