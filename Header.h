#pragma once


#ifndef HEADER_H
#define HEADER_H

#include<iostream>
#include<string>

using namespace std;

class node {
public:
	node();
	string key;
	node* left;
	node* right;
	int height;
};

class tree {
private:
	node* root;
	bool searchn(node*, string);
	node* searchp(node*, string, node*);
	void findplace(string, node*);
	void checkbal(string);
	node* findsucc(node*);
	void tleft(node*);
	void tright(node*);
public:
	bool search(string);
	bool insert(string);
	bool deleten(string);
	void display();
};

#endif