/////////////////////////////////////////////////////////////////////////
// FileReader.cpp - Implementation of FileReader package to read file  //
//                                                                     //
// Application: CSE687 - Object Oriented Design-XML Document Model     //
// Platform:    Dell Inspiron, Win 8.1, Visual Studio 2013             //
// Author:      Venkata Subba Rao Cheedella, Syracuse Univesity        //
//              vcheedel@syr.edu                                       //
/////////////////////////////////////////////////////////////////////////




#include "FileReader.h"
#include <iostream>
#include <fstream>
#include "../Display/Display.h"



//----------------------<Destructor>---------------------

FileReader::~FileReader()
{
}

//-----------------------<To read a file and copy the content to string>---------------

string& FileReader::convertoString()
{
	ifstream input(filename);
	string sample;	
	if (input.is_open())
	{
		if (input.good())
		{
			while (getline(input, sample))
			{
				size_t pos = sample.find_first_not_of(" ");
				sample = sample.substr(pos, sample.size() - pos);
				totalinput += sample;
				//totalinput += "\n";
			}
		}
	}
	//std::cout << totalinput;
	return totalinput;
}


//------------------<Test Stub>-----------------------

#ifdef TEST_FILEREADER

int main(int argc, char* argv[])
{
	vector<string> cmdargs;
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
			cmdargs.push_back(argv[i]);
	}
	if (cmdargs.size() != 0)
	{
		FileReader fr(cmdargs[0]);
		std::cout << "\n" << fr.convertoString() << endl;
	}		
	else
		std::cout << "\n" << "Please provide the path again" << endl;}

#endif
