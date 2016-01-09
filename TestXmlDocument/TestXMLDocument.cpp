///////////////////////////////////////////////////////////////////  //
// TestXMLDocument.cpp - To provide public interfaces to the XML tree//
//                                                                   //
// Application: CSE687 - Object Oriented Design-XML Document Model   //
// Platform:    Dell Inspiron, Win 8.1, Visual Studio 2013           //
// Author:      Venkata Subba Rao Cheedella, Syracuse Univesity      //
//              vcheedel@syr.edu                                     //
///////////////////////////////////////////////////////////////////////



#include "TestXMLDocument.h"
#include "../XmlDocument/XmlDocument.h"
#include "../XmlElement/XmlElement.h"
#include <memory>
#include "../XmlReader/XmlReader.h"
#include "../FileSystemDemo/FileSystem.h"
#include <fstream>

using attribs = std::vector<std::pair<std::string, std::string>>;

//-------------------<Promotion constructor>-------------------------

TestXMLDocument::TestXMLDocument(XmlProcessing::XmlDocument& xmlDoc) : 
_xmlDoc(xmlDoc)
{	
	_pDocElem=_xmlDoc.getDocElement();
	_pRootTagElem = xmlDoc.getRootTaggedElement();
}

//------------------<Destructor>--------------------------

TestXMLDocument::~TestXMLDocument()
{
}

//attribs TestXMLDocument::getAttributes(sPtr elemPtr)
//{
//
//	if (_pRootTagElem == elemPtr)
//	{
//
//	}
//	XmlProcessing::TaggedElement* tElem = dynamic_cast<XmlProcessing::TaggedElement*>(_pRootTagElem.get());
//	
//}

//---------------<To demonstrate requirements>-----------------------

void TestXMLDocument::testStub2(string input)
{
	Display disp(_xmlDoc);
	disp.title("Demonstration of req# 8- To get the attributes of an element, root-tagged element");
	attribs elemattribs = getAttributesOfElem(_pRootTagElem);
	disp.getAttributesOfElemInfo(elemattribs);

	disp.title("Demonstration of req# 8- To retrive children of an element, LectureNote");
	vector<sPtr> childElems;
	childElems.clear();
	if (getChildren("LectureNote", childElems).size() != 0)
		childElems = getChildren("LectureNote", childElems);
	disp.dispChildren(childElems);

	pair<string, string> sampleattrib;
	sampleattrib.first = "name";
	sampleattrib.second = "Jim";
	disp.title("Demonstration of req# 9- Attribute addition to an element, reference");
	bool addAttribStatus = addAttribute("reference", sampleattrib);
	disp.addAttribStatusInfo(addAttribStatus);

	disp.title("Demonstration of req# 9-Delete attributes of an element, Publisher");
	bool delAttribStatus = deleteAttribute("publisher", "name");
	disp.deleteAttributeInfo(delAttribStatus);

	disp.title("Demonstrate of req# 4-To write XMLtree to a file and to a string :");
	WriteXMLtoFile(input);
}

//-------------< Demonstration of tree creation without sourceXML>-----------------------

void TestXMLDocument::createTreeWithoutSrc()
{
	XmlProcessing::XmlDocument xmlDocWoSrc;
	sPtr tElem = XmlProcessing::makeTaggedElement("Parent");
	tElem->addAttrib("color", "black");
	tElem->addAttrib("back-ground", "white");
	xmlDocWoSrc.getDocElement()->addChild(tElem);
	Display disp(xmlDocWoSrc);
	disp.displayXMLToString();
}

//------------Demonstration of move operations to XmlElement objects>--------------------------

void TestXMLDocument::moveOpsForTaggedElem()
{
	XmlProcessing::TaggedElement te1("child1");						// Tagged Element creation
	te1.addAttrib("version", "1.1");
	te1.addAttrib("back-ground", "green");
	Display::printStatus("te1 information before move");
	std::cout << te1.value() << endl;
	Display::printStatus("attributes:");
	for (auto s : te1.getAttributes())
	{
		std::cout << s.first << "\"" << s.second << "\"" << endl;
	}
	XmlProcessing::TaggedElement te2 = std::move(te1);					// move of an element
	Display::printStatus("Demonstration of move constructor of a tagged element");
	Display::printStatus("te2 information after move");
	std::cout << te2.value() << endl;
	Display::printStatus("attributes:");
	for (auto s : te2.getAttributes())
	{
		std::cout << s.first << "\"" << s.second << "\"" << endl;
	}
	if (te1.value() == "")
		std::cout << "\n" << "The data of te1 is moved" << endl;
	Display::printStatus("Demonstration of move assignment of a tagged element");	
	te1 = std::move(te2);													// calls move assignment operator
	Display::printStatus("te1 information after move assignment ");
	std::cout << te1.value() << endl;
	Display::printStatus("attributes:");
	for (auto s : te1.getAttributes())
	{
		std::cout << s.first << "\"" << s.second << "\"" << endl;
	}
	if (te2.value() == "")
		Display::printStatus("The data of te2 is moved");
	Display::printStatus("Move constructor and move assignment are designed for all XElement clasees. But, they are not demonstrated here");
}

//---------------------<Test stub to demonstrate the requirements of the project>---------------------

void TestXMLDocument::testStub(string input)
{
	Display disp(_xmlDoc);
	disp.title("Demonstration of req# 4- move constructors and move assignment operations of XElements");
	moveOpsForTaggedElem();

	disp.title("Demonstation of Req# 5- To get an element by ID, ID = Wintellect");
	sPtr idPtr = getElementforID("Wintellect");
	disp.disElemIDInfo(idPtr);

	tagElementsVec.clear();
	disp.title("Demonstration of req# 6- To get an element by tag, tag =title");
	tagElementsVec = getElementsforTag("title", tagElementsVec);
	disp.getElementsForTagInfo(tagElementsVec);

	disp.title("Demonstration of req# 7- Addition of an element by tag search, tag= page");
	bool addstatus = addElementToTree("<pChild course=\"CSE-681\"> </pChild>", "page", 0);
	disp.addElementToTreeInfo(addstatus);

	addstatus = false;
	disp.title("Demonstration of req# 7 -Addition of an element by value search, value = venkat");
	addstatus = addElementToTree("<pChild course=\"CSE-681\"> </pChild>", "venkat", 1);
	disp.addElementtoTreebyIdInfo(addstatus);

	disp.title("Demonstration of req# 7- Deletion of child by tag, parent:author, child:note");
	bool delStatus = removeElemFromTreebyTag("author", "note");
	disp.removeElemFromTreebyTagInfo(delStatus);
	delStatus = false;
	disp.title("Demonstration of req# 7- Deletion of child by ID, id:venkat, parent:pChild");
	delStatus = removeElemFromTreebyID("venkat", "pChild");
	disp.removeElemFromTreebyIDInfo(delStatus);

	disp.title("Demonstration of req# 7- Tree creation without source");
	createTreeWithoutSrc();

	testStub2(input);
}

//--------------------<Get Children for an element>-------------------------------

vector<sPtr>& TestXMLDocument::getChildren(string tag, vector<sPtr>& childPtrs)
{
	 vector<sPtr> pElems = getElementsforTag(tag, childPtrs);
	if (pElems.size() != 0)
	{	
		for (auto s : pElems)
		{
			XmlProcessing::TaggedElement* te = dynamic_cast<XmlProcessing::TaggedElement*>(s.get());
			if (te != nullptr)
			{
				if (s->value() == tag)
				{
					childPtrs = te->getChildern();
					return childPtrs;
				}				
			}
		}
		return childPtrs;
	}
	else
		return childPtrs;
}

//----------------------<Write the tree to a file>-----------------------------------
void TestXMLDocument::WriteXMLtoFile(string input)
{
	string outputXML = _pDocElem->toString();
	std::cout << "\n" << "XML after the operations and from a string :" << "\n" << outputXML << endl;
	string currentDir = FileSystem::Directory::getCurrentDirectory();
	string treeString = _pDocElem->toString();
	treeString = treeString.substr(3);
	if (input == "")
	{
		ofstream outfile("xmloutput.txt");
		
		outfile << treeString;
		currentDir = FileSystem::Path::fileSpec(currentDir, "xmloutput.txt");
		std::cout << "\n" << "The output XMLfile, xmloutput present at :" << FileSystem::Path::getFullFileSpec(currentDir) << "\n";
		outfile.close();
	}		
	else
	{
		ofstream outfile(input);
		outfile << treeString;
		currentDir = FileSystem::Path::fileSpec(currentDir, input);
		std::cout << "\n" << "The output XMLfile, xmloutput present at :" << FileSystem::Path::getFullFileSpec(currentDir) << "\n";
		outfile.close();
	}			
}

//--------------------------<Add attributes to a given element if present>---------------------

bool TestXMLDocument::addAttribute(string tag, pair<string, string> attrib)
{
	tagElementsVec.clear();
	tagElementsVec = getElementsforTag(tag, tagElementsVec);
	if (tagElementsVec.size() != 0)
	{
		sPtr elemPtr = tagElementsVec[0];
		elemPtr->addAttrib(attrib.first, attrib.second);
		return true;
	}
	else
	{
		return false;
	}

}

//---------------------<Delete attributes for an element if present>---------------

bool TestXMLDocument::deleteAttribute(string tag, string value)
{
	bool removeStatus = false;
	tagElementsVec.clear();
	tagElementsVec = getElementsforTag(tag, tagElementsVec);
	sPtr elemPtr = nullptr;
	if (tagElementsVec.size() != 0)
	{		
		for (unsigned int i = 0; i < tagElementsVec.size(); i++)			// Iteration of vector to check the attributes
		{			
			elemPtr = tagElementsVec[i];
			if (elemPtr->value() == "?xml")
			{
				XmlProcessing::XmlDeclarElement* pXmlDec = dynamic_cast<XmlProcessing::XmlDeclarElement*>(elemPtr.get());
				attributes = pXmlDec->getAttribs();
			}
			else if (elemPtr->value().find("?") != -1)
			{
				XmlProcessing::ProcInstrElement* pXmlProc = dynamic_cast<XmlProcessing::ProcInstrElement*>(elemPtr.get());
				attributes = pXmlProc->getAttribs();
			}
			else
			{
				XmlProcessing::TaggedElement* pTagElem = dynamic_cast<XmlProcessing::TaggedElement*>(elemPtr.get());
				attributes = pTagElem->getAttributes();
			}
			for (auto attrib : attributes)
			{
				if (attrib.first == value)
				{
					removeStatus = elemPtr->removeAttrib(value);
					return removeStatus;
				}				 
			}
		}	
		return removeStatus;
	}
	else
	{
		return false;
	}
}

//---------------------<Get attributes of an element>-------------------------------

attribs TestXMLDocument::getAttributesOfElem(sPtr elemPtr)
{
	attributes.clear();
	if (elemPtr->value() == "?xml")
	{
		XmlProcessing::XmlDeclarElement* pXmlDec = dynamic_cast<XmlProcessing::XmlDeclarElement*>(elemPtr.get());
		attributes = pXmlDec->getAttribs();
		return attributes;
	}
	else if (elemPtr->value().find("?") != -1)
	{
		XmlProcessing::ProcInstrElement* pXmlProc = dynamic_cast<XmlProcessing::ProcInstrElement*>(elemPtr.get());
		attributes = pXmlProc->getAttribs();
		return attributes;
	}
	else
	{
		XmlProcessing::TaggedElement* pTagElem = dynamic_cast<XmlProcessing::TaggedElement*>(elemPtr.get());
		attributes = pTagElem->getAttributes();
		return attributes;
	}
}


//----------------------<Add an element to a tree>-------------------------------

void TestXMLDocument::addElemToTree(sPtr pElemPtr, string elem)
{
	sPtr pNewElem = nullptr;
	XmlReader elemRdr(elem);
	while (elemRdr.next())
	{
		string _tag = elemRdr.tag();
		string comment;
		attribs _attribs = elemRdr.attributes();
		if (_tag == "!--")															// check if it is comment
		{
			int startpoint = elemRdr.element().find_first_of(" ");
			int endpoint = elemRdr.element().find_last_of("--");
			int lenofcomment = endpoint - startpoint;
			comment = elemRdr.element().substr(startpoint, lenofcomment - 1);
			pNewElem = XmlProcessing::makeCommentElement(comment);
		}
		else if (_tag == "?xml")
			pNewElem = XmlProcessing::makeXmlDeclarElement();
		else if (_tag.find("?") != std::string::npos && _tag != "?xml")
			pNewElem = XmlProcessing::makeProcInstrElement(_tag);
		else if (_tag == "")														// check if it is text element
			pNewElem = XmlProcessing::makeTextElement(elem);
		else
			pNewElem = XmlProcessing::makeTaggedElement(_tag);
		if (_attribs.size() != 0)
		{
			for (auto attrib : _attribs)
				pNewElem->addAttrib(attrib.first, attrib.second);
		}
	}
	pElemPtr->addChild(pNewElem);	
}

//----------------------<Add an element to a tree>----------------------------------------

bool TestXMLDocument::addElementToTree(string elem, string stagorID, unsigned int type)
{
	tagElementsVec.clear();
	sPtr pElemPtr = nullptr, pNewElem = nullptr;
	bool addStatus = false;
	if (type == 0)
	{
		tagElementsVec = getElementsforTag(stagorID, tagElementsVec);
		if (tagElementsVec.size() != 0)
		pElemPtr = tagElementsVec[0];
	}		
	else if (type == 1)
		pElemPtr = getElementforID(stagorID);
	else
		return false;
	if (pElemPtr != nullptr)
	{	
		addElemToTree(pElemPtr, elem);		
		return true;
	}
	else
		return false;
}

//---------------------<Remove an element from a tree by ID>-------------------------

bool TestXMLDocument::removeElemFromTreebyID(string parentId, string childTag)
{
	tagElementsVec.clear();
	sPtr pElemPtr = nullptr;
	bool delStatus = false;
	pElemPtr = getElementforID(parentId);
	if (pElemPtr == nullptr)
		return false;
	XmlProcessing::TaggedElement* te = dynamic_cast<XmlProcessing::TaggedElement*>(pElemPtr.get());
	if (te != nullptr)
	{
		if (te->getChildern().size() != 0)
		{
			for (unsigned int i = 0; i < te->getChildern().size(); i++)
			{
				if (te->getChildern()[i]->value() == childTag)
				{
					delStatus = pElemPtr->removeChild(te->getChildern()[i]);
					return delStatus;
				}
			}
			return delStatus;
		}
		else
			return delStatus;
	}
	else
		return delStatus;
}

//---------------------<Remove an element from tree by Tag>--------------------------

bool TestXMLDocument::removeElemFromTreebyTag(string parentTagorID, string childTag)
{
	tagElementsVec.clear();
	sPtr pElemPtr = nullptr;
	bool delStatus = false;	
	tagElementsVec = getElementsforTag(parentTagorID, tagElementsVec);
	if (tagElementsVec.size() != 0)
	{
			for (unsigned int j = 0; j < tagElementsVec.size(); j++)
			{
				XmlProcessing::TaggedElement* te = dynamic_cast<XmlProcessing::TaggedElement*>(tagElementsVec[j].get());
				if (te != nullptr)
				{
					if (te->getChildern().size() != 0)
					{
						vector<sPtr> vsPtr = te->getChildern();
						for (unsigned int i = 0; i < vsPtr.size(); i++)
						{
							if (vsPtr[i]->value() == childTag)
							{
								delStatus = tagElementsVec[j]->removeChild(vsPtr[i]);
								return delStatus;
							}								

						}
					}
				}
			}
			return delStatus;
		}				
	else
		return false;	
}

//--------------< Search the tree recursively to delete an element>-----------------

bool TestXMLDocument::recSrchForDelElem(sPtr _pTElem, sPtr elemPtr)
{
	bool delStatus = false;
	XmlProcessing::TaggedElement* _pTagElem;
	vector<sPtr> childElems;
	_pTagElem = dynamic_cast<XmlProcessing::TaggedElement*>(_pTElem.get());
	if (_pTagElem != nullptr)
	{
		childElems = _pTagElem->getChildern();
		for (unsigned int i = 0; i < childElems.size(); i++)
		{
			if (elemPtr == childElems[i])
			{
				//childElems.erase(childElems.begin() + i);
				_pTagElem->getChildern().erase(_pTagElem->getChildern().begin() + i);
				delStatus = true;
				return delStatus;
			}
			else
			{
				_pTagElem = dynamic_cast<XmlProcessing::TaggedElement*>(childElems[i].get());
				if (_pTagElem != nullptr)
				{
					delStatus = recSrchForDelElem(childElems[i], elemPtr);
					if (delStatus == true)
						return delStatus;
				}
			}
		}
	}	
	return delStatus;
}

//---------------<Remove an element from a tree>------------------------

bool TestXMLDocument::removeElemFromTree(sPtr elemPtr)
{
	bool removeStatus = false;
	attribs attributes;
	XmlProcessing::DocElement* docPtr = nullptr;
		docPtr = dynamic_cast<XmlProcessing::DocElement*>(_pDocElem.get());
		vector<sPtr> childElems;
		XmlProcessing::TaggedElement* _pTagElem = nullptr;
		if (docPtr != nullptr)
		{
			childElems = docPtr->getChildern();
			for (unsigned int i = 0; i < childElems.size(); i++)
			{
				if (elemPtr == childElems[i])
				{
					childElems.erase(childElems.begin() + i);
					removeStatus = true;
					return removeStatus;
				}
				else
				{
					_pTagElem = dynamic_cast<XmlProcessing::TaggedElement*>(childElems[i].get());
					if (_pTagElem != nullptr)
					{
						removeStatus = recSrchForDelElem(childElems[i], elemPtr);
						if (removeStatus == true)
							return removeStatus;
					}
				}
			}
		}			
		return removeStatus;
}

//------------------------<Get attributes of an element by Id>--------------------------

bool TestXMLDocument::getAttributeElem(XmlProcessing::ProcInstrElement* pPtr, string id)
{
	bool attribStatus = false;
	attribs attributes = pPtr->getAttribs();
	for (auto attrib : attributes)
	{
		if (attrib.second == id)
		{
			attribStatus = true;
			return attribStatus;
		}
	}
	return attribStatus;
}

//------------------------<Get an element of a tree by ID>----------------------------

sPtr TestXMLDocument::getElementforID(std::string id)
{	
	XmlProcessing::DocElement* docPtr = dynamic_cast<XmlProcessing::DocElement*>(_pDocElem.get());
	sPtr elemPtr = nullptr;
	if (docPtr != nullptr)
	{
		std::vector<std::shared_ptr<XmlProcessing::AbstractXmlElement>> children = docPtr->getChildern();
		if (children.size() != 0)
		{
			for (auto s : children)
			{
				XmlProcessing::ProcInstrElement* pPtr = nullptr;
				XmlProcessing::XmlDeclarElement* dPtr = nullptr;
				XmlProcessing::TaggedElement* tPtr = nullptr;
				tPtr = dynamic_cast<XmlProcessing::TaggedElement*>(s.get());
				if (tPtr == NULL)
				{
					pPtr = dynamic_cast<XmlProcessing::ProcInstrElement*>(s.get());
					dPtr = dynamic_cast<XmlProcessing::XmlDeclarElement*>(s.get());
					if (pPtr != nullptr)
					{
						bool presentStatus = getAttributeElem(pPtr, id);
						if (presentStatus == true)
							return s;
					}
					else if (dPtr != nullptr)
					{
						attribs attributes = dPtr->getAttribs();
						bool attribStatus = getAttributeElem(dPtr, id);
						if (attribStatus == true)
							return s;
					}
				}
				else
				{
					elemPtr = recursiveSearchForId(id, s);
					return elemPtr;
				}
			}
			return elemPtr;
		}
		else
			return elemPtr;
	}
	else
		return elemPtr;
}

//--------------------------<Get attributes of an element by ID>---------------------------

bool TestXMLDocument::getAttributeElem(XmlProcessing::XmlDeclarElement* dPtr, string id)
{
	bool attribPresentStat = false;
	attribs attributes = dPtr->getAttribs();
	for (auto attrib : attributes)
	{
		if (attrib.second == id)
		{
			attribPresentStat = true;
			return attribPresentStat;
		}
	}
	return attribPresentStat;
}

//--------------------------<Search the tree recursively for an ID>---------------------

sPtr TestXMLDocument::recursiveSearchForId(std::string id, sPtr tPtr)
{
	XmlProcessing::TaggedElement* tePtr = nullptr;
	sPtr idPtr = nullptr;
	tePtr = dynamic_cast<XmlProcessing::TaggedElement*>(tPtr.get());
	if (tePtr == nullptr)
	{
		return idPtr;
	}
	attribs attributes = tePtr->getAttributes();
	if (attributes.size() != 0)
	{
		for (auto attrib : attributes)
		{
			if (attrib.second == id)
			{
				return tPtr;
			}
		}
	}
	std::vector<std::shared_ptr<XmlProcessing::AbstractXmlElement>> childPtrs = tePtr->getChildern();
	if (childPtrs.size() != 0)
	{
		for (auto childPtr : childPtrs)
		{
			idPtr = recursiveSearchForId(id, childPtr);
			if (idPtr != nullptr)
				return idPtr;
		}
	}
	return idPtr;
}

//--------------------------<Retrieve the elements from the tree of a given tag>------------------

vector<sPtr>& TestXMLDocument::getElementsforTag(std::string tag, vector<sPtr>& tagElemsVector)
{
	XmlProcessing::DocElement* docPtr = dynamic_cast<XmlProcessing::DocElement*>(_pDocElem.get());
	if (docPtr != nullptr)
	{
		vector<shared_ptr<XmlProcessing::AbstractXmlElement>> children = docPtr->getChildern();
		if (children.size() != 0)
		{
			for (auto s : children)
			{
				XmlProcessing::TaggedElement* tPtr = dynamic_cast<XmlProcessing::TaggedElement*>(s.get());
				if (tPtr != nullptr)
				{
					tagElemsVector = recursiveSearchForTag(tag, s, tagElemsVector);
				}
			}
		}
	}
	return tagElemsVector;
}

//--------------------------<Search the tree recursively for a tag>-------------------------

vector<sPtr>& TestXMLDocument::recursiveSearchForTag(std::string tag, sPtr s, vector<sPtr>& tagElemsVector)
{
	XmlProcessing::TaggedElement* tePtr = nullptr;
	if (s->value() == tag)
		tagElemsVector.push_back(s);
	tePtr = dynamic_cast<XmlProcessing::TaggedElement*>(s.get());
	vector<shared_ptr<XmlProcessing::AbstractXmlElement>> children = tePtr->getChildern();
	if (children.size() != 0)
	{
		XmlProcessing::TaggedElement* tempPtr = nullptr;
		for (auto childPtr : children)
		{
			tempPtr = dynamic_cast<XmlProcessing::TaggedElement*>(childPtr.get());
			if (tempPtr != nullptr)
				tagElemsVector = recursiveSearchForTag(tag, childPtr, tagElemsVector);
		}
	}
	return tagElemsVector;
}


//--------------------<Test Stub>------------------

#ifdef TEST_TESTXMLDOCUMENT
int main()
{
	Display::printStatus("Testing TestXMLDocument class");
	std::string inputSample = "< ? xml version = \"1.1\" encoding=\"UTF - 8\" ?><?xml-proc color=\"black\" background=\"white\" ?><!--  XML test case  -->";
	XmlProcessing::XmlDocument doc(inputSample);
	doc.controller();
	TestXMLDocument testDoc(doc);
	//sPtr APtr = testDoc.getElementforID("1.1");
	//std::cout << "The given value is present in the tag:" << testDoc.getElementforID("1.1")->value() << endl;	
	vector<sPtr> vecPtr;
	vecPtr = testDoc.getElementsforTag("!--", vecPtr);
	if (vecPtr.size() != 0)
		std::cout << "The given tag is present";
}

#endif