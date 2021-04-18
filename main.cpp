#include "data.h"
using namespace std;

book phone_book;

int getParent(int i) {
    int old_parent, new_parent=i;
    if(phone_book.name_number.array[i].parent!=i) {
        new_parent=getParent(phone_book.name_number.array[i].parent);
        old_parent=phone_book.name_number.array[i].parent;
        if(old_parent!=new_parent) {
            phone_book.name_number.array[new_parent].children.push_back(i);
            phone_book.name_number.array[old_parent].children.remove(i);
        }
        phone_book.name_number.array[i].parent=new_parent;
    }
    return new_parent;
}

void merge(int src, int des) {
    src=getParent(src);
    des=getParent(des);
    if(src!=des) {
        if(phone_book.name_number.array[des].rank>phone_book.name_number.array[src].rank) {
            phone_book.name_number.array[src].parent=des;
            phone_book.name_number.array[des].children.push_back(src);
        }
        else {
            phone_book.name_number.array[des].parent=src;
            phone_book.name_number.array[src].children.push_back(des);
            if(phone_book.name_number.array[src].rank==phone_book.name_number.array[des].rank) {
                phone_book.name_number.array[src].rank+=1;
            }
        }
    }
}

void dfs(int i, bool *done) {
    done[i]=1;
    linkedList* temp;
    if(phone_book.name_number.array[i].rows) {
        for(int j=0; j<map_size; j++) {
            temp=phone_book.name_number.array[i].data.contacts[j];
            while(temp!=NULL) {
                cout<<temp->key<<": "<<temp->value<<"\n";
                temp=temp->next;
            }
        }
    }
    if(phone_book.name_number.size!=0) {
        for(int j=0; j<phone_book.name_number.array[i].children.size; j++) {
            dfs(phone_book.name_number.array[i].children.array[j], done);
        }
    }
}

void displayAll() {
    bool done[phone_book.name_number.size]={0};
    int parent;
    cout<<"#######################\n\n";
    for(int i=0; i<phone_book.name_number.size; i++) {
        if(!done[phone_book.name_number.array[i].ind]) {
            parent=getParent(phone_book.name_number.array[i].ind);
            cout<<"Source "<<phone_book.name_number.array[parent].ind+1<<": \n";
            dfs(parent, done);
            cout<<"\n";
        }
    }
    cout<<"#######################\n";
}

string searchName(string name) {
    string number;
    for(int i=0; i<phone_book.name_number.size; i++) {
        if(phone_book.name_number.array[i].rows!=0) {
            number=phone_book.name_number.array[i].data.search(name);
            if(number!="") {
                return number;
            }
        }
    }
    return "Contact not found";
}

void insertContact(string name, string number, int src) {
    src=getParent(src);
    phone_book.name_number.array[src].data.insert(name, number);
    phone_book.name_number.array[src].rows++;
}

bool deleteContact(string name) {
    for(int i=0; i<phone_book.name_number.size; i++) {
        if(phone_book.name_number.array[i].rows!=0) {
            if(phone_book.name_number.array[i].data.search(name)!="") {
                phone_book.name_number.array[i].data.erase(name);
                phone_book.name_number.array[i].rows--;
                return true;
            }
        }
    }
    return false;
}


int main() {
    populateData(&phone_book);
    cout<<"-------------------\nUNIVERSAL PHONEBOOK\n-------------------\n\n";
    displayAll();
    int x, n1, n2;
    string name, number, temp;
    char yn;
    bool flag=1, success;
    while(flag) {
        cout<<"\n****MENU****\n";
        cout<<"Click 1 to insert a new contact\n";
        cout<<"Click 2 to delete an existing contact\n";
        cout<<"Click 3 to search for a contact\n";
        cout<<"Click 4 to merge contacts from 2 sources\n";
        cout<<"Click 5 to display the phonebook\n";
        cout<<"Click 6 to exit the phonebook\n";
        cout<<"Your input: ";
        cin>>x;
        switch(x) {
            case 1:
                cout<<"Enter contact name to be inserted: ";
                cin>>name;
                cout<<"Enter contact number to be inserted: ";
                cin>>number;
                cout<<"Enter the source number in which the contact is to be inserted: ";
                cin>>n1;
                if(n1<1 or n1>5) {
                    cout<<"Invalid input\n";
                    break;
                }
                temp=searchName(name);
                if(temp=="Contact not found") {
                    insertContact(name, number, --n1);
                    cout<<"Contact inserted successfully\n";
                }
                else {
                    cout<<"A contact with the same name already exists\n";
                    cout<<name<<": "<<temp<<"\n";
                    cout<<"Do you want to overwrite the contact? (y / n): ";
                    cin>>yn;
                    if(yn=='y') {
                        success=deleteContact(name);
                        insertContact(name, number, --n1);
                        cout<<"Contact overwritten successfully\n";
                    }
                }
                break;
            case 2:
                cout<<"Enter contact name to be deleted: ";
                cin>>name;
                success=deleteContact(name);
                if(success) {
                    cout<<"Contact deleted successfully\n";
                }
                else {
                    cout<<"No contact with the given name exists\n";
                }
                break;
            case 3:
                cout<<"Enter contact name to be searched: ";
                cin>>name;
                number=searchName(name);
                if(number=="Contact not found") {
                    cout<<number<<'\n';
                }
                else {
                    cout<<"Contact found\n";
                    cout<<name<<": "<<number<<"\n";
                }
                break;
            case 4:
                cout<<"Enter two source numbers to be merged: ";
                cin>>n1>>n2;
                if(n1>=1 && n1<=5 && n2>=1 && n2<=5) {
                    merge(--n1, --n2);
                    cout<<"Merged successfully\n";
                }
                else {
                    cout<<"Invalid input\n";
                }
                break;
            case 5:
                displayAll();
                break;
            default:
                flag=0;
                cout<<"-----------------------------------------------\n";
                cout<<"Thanks for using the Universal Phonebook\n";
                cout<<"Developed by: Akshay Jain and Md Areeb Hussain\n";
                cout<<"-----------------------------------------------\n";
                break;
        }
    }
    return 0;
}