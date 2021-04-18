#include<bits/stdc++.h>
using namespace std;

#ifndef STRUCTURE_H
#define STRUCTURE_H

template <class T>
class dynamicArray {
    public:
    T* array=(T*)malloc(sizeof(T)*32);
    int size=0;
    int max_size=32;

    void push_back(T data) {
        if(size<max_size) {
            array[size++]=data;
        }
        else {
            array=(T*)realloc(array, 2*max_size);
            array[size++]=data;
            max_size*=2;
        }
    }

    void remove(T data) {
        if (array[size-1] == data) {
            size--;
            return;
        }
        T prev = array[size-1];
        int i;
        for (i=size-2; i>=0 && array[i]!=data; i--) {
            T curr = array[i];
            array[i] = prev;
            prev = curr;
        }
        if (i < 0) return;
        array[i] = prev;
        size--;
        return;
    }
};
class linkedList {
    public:
    string key;
    string value;
    linkedList* next=NULL;

    linkedList(string name, string number) {
        key=name;
        value=number;
    }

    string search(linkedList** head, string key) {
        linkedList* temp=*head;
        while(temp!=NULL) {
            if(temp->key==key) return temp->value;
            temp=temp->next;
        }
        return "";
    }

    void insert_back(linkedList** head, string key, string value) {
        linkedList* temp=*head;
        if(temp==NULL) {
            *head=new linkedList(key, value);
            return;
        }
        while(temp->next!=NULL) {
            temp=temp->next;
        }
        temp->next=new linkedList(key, value);
        return;
    }

    void delete_node(linkedList** head, string key) {
        linkedList* temp = *head;
        linkedList* prev = NULL;
        if (temp!=NULL && temp->key==key) {
            *head = temp->next;
            delete temp;
            return;
        }
        while (temp!=NULL && temp->key!=key) {
            prev=temp;
            temp=temp->next;
        }
        if(temp == NULL) return;
        prev->next = temp->next;
        delete temp;
        return;
    }
};

int map_size=101;
int prime=31;

class hashMap {
    public:
    linkedList* contacts[101]={NULL};

    int hashFunction(string name) {
        int n=name.size();
        int hashValue=0;
        int ascii;
        for(int i=n-1; i>=0; i--) {
            hashValue=(hashValue*prime)%map_size;
            ascii=int(name[i]);
            if(ascii>=65 && ascii<=90) {
                hashValue+=ascii-64;
            }
            else if(ascii>=97 && ascii<=122) {
                hashValue+=ascii-96;
            }
            hashValue%=map_size;
        }
        return hashValue;
    }

    string search(string name) {
        int hash=hashFunction(name);
        return contacts[hash]->search(&contacts[hash], name);
    }

    void insert(string name, string number) {
        int hash=hashFunction(name);
        contacts[hash]->insert_back(&contacts[hash], name, number);
    }

    void erase(string name) {
        int hash=hashFunction(name);
        contacts[hash]->delete_node(&contacts[hash], name);
    }
};

class table {
    public:
    int rows=0, parent, rank=0, ind;
    dynamicArray<int> children;
    hashMap data;
};

class book {
    public:
    dynamicArray<table> name_number;
};

#endif