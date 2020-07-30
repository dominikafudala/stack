#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

enum INTERFACE
{
	INTERFACE_PUSH,
	INTERFACE_POP,
	INTERFACE_CLEAR,
	INTERFACE_FIND,
	INTERFACE_SAVE,
	INTERFACE_LOAD,
	INTERFACE_EXIT,
	INTERFACE_TOTAL

};

enum SEARCH_DATA
{
	LASTNAME_SEARCH,
	YEAR_SEARCH,
	MAJOR_SEARCH,
	SEARCH_TOTAL
};

void display();
void push();
void pop();
void clear();
void find();
void find_lastname();
void find_year();
void find_major();
void save();
void load();
void show_menu();
void show_majors();
void myMenu();

#endif // !INTERFACE_H

