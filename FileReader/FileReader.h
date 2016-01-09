#ifndef FILEREADER_H
#define FILEREADER_H

/////////////////////////////////////////////////////////////////////
// FileReader.h - Open the file and get the details                //
//                                                                 //
// Application: CSE687 - Object Oriented Design-XML Document Model //
// Platform:    Dell Inspiron, Win 8.1, Visual Studio 2013         //
// Author:      Venkata Subba Rao Cheedella, Syracuse Univesity    //
//              vcheedel@syr.edu                                   //
/////////////////////////////////////////////////////////////////////
/*


Package Operations
===================

This package helps to read the file and store the XML to a string for parsing.


Required Files
==============
This dosen't depends on other packages. XmlDocument gets the help from FileReader package
to read the file.
FileReader.h, FileReader.cpp

Public Interfaces
==================

string& convertoString(); --> Get the filename and read the file content to a string.

Build Process
===============
From the Visual Studio Developer's Command Prompt:
devenv XmlDocument.sln /rebuild debug

Maintenance History
=========================

ver 1.0  : 23 Mar 2015
- First Release

*/

#include <iostream>
#include <string>
using namespace std;

class FileReader
{
public:
	FileReader(string& fname) :filename(fname){}
	~FileReader();
	string& convertoString();
private:
	string filename;
	string totalinput= "";
};


#endif
