///////////////////////////////////////////////////////////////////
// XmlElement.cpp - define XML Element types                     //
// ver 1.4                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948                 //
//              jfawcett@twcny.rr.com                            //
///////////////////////////////////////////////////////////////////

#include "XmlElement.h"
#include <iostream>

using namespace XmlProcessing;

size_t AbstractXmlElement::count = 0;
size_t AbstractXmlElement::tabSize = 2;

//----< factory for doc elements >----------------------------------------

std::shared_ptr<AbstractXmlElement> XmlProcessing::makeDocElement(std::shared_ptr<AbstractXmlElement> pRoot)
{
  std::shared_ptr<AbstractXmlElement> ptr(new DocElement(pRoot));
  return ptr;
}

//----< factory for tagged elements >----------------------------------------

std::shared_ptr<AbstractXmlElement> XmlProcessing::makeTaggedElement(const std::string& tag)
{
  std::shared_ptr<AbstractXmlElement> ptr(new TaggedElement(tag));
  return ptr;
}
//----< factory for text elements >------------------------------------------

std::shared_ptr<AbstractXmlElement> XmlProcessing::makeTextElement(const std::string& text)
{
  std::shared_ptr<AbstractXmlElement> ptr(new TextElement(text));
  return ptr;
}
//----< factory for comment elements >---------------------------------------

std::shared_ptr<AbstractXmlElement> XmlProcessing::makeCommentElement(const std::string& text)
{
  std::shared_ptr<AbstractXmlElement> ptr(new CommentElement(text));
  return ptr;
}
//----< factory for processing instruction elements >------------------------

std::shared_ptr<AbstractXmlElement> XmlProcessing::makeProcInstrElement(const std::string& text)
{
  std::shared_ptr<AbstractXmlElement> ptr(new ProcInstrElement(text));
  return ptr;
}
//----< factory for XML Declaration elements >-------------------------------

std::shared_ptr<AbstractXmlElement> XmlProcessing::makeXmlDeclarElement()
{
  std::shared_ptr<AbstractXmlElement> ptr(new XmlDeclarElement());
  return ptr;
}
//----< doc element constructor and destructor >-----------------------------

DocElement::DocElement(std::shared_ptr<AbstractXmlElement> pRoot) 
{
  std::shared_ptr<AbstractXmlElement> pDecl = makeXmlDeclarElement();
  pDecl->addAttrib("version", "1.0");
  children_.push_back(pDecl);
  if (pRoot != nullptr)
    children_.push_back(pRoot);
}

//----------------------<Doc Element default constructor>--------------------

//DocElement::DocElement()
//{	
//	std::shared_ptr<AbstractXmlElement> pDecl = makeXmlDeclarElement();
//	pDecl->addAttrib("version", "1.0");
//	this->children_.push_back(pDecl);
//}

//----------------------<Doc Element move assignment>----------------------

DocElement& DocElement::operator=(DocElement&& docElem)
{
	if (this == &docElem)
		return *this;
	children_ = std::move(docElem.children_);
	return *this;
}
//----< private helper for DocElement::addChild(...) >-----------------------

bool DocElement::hasXmlRoot()
{
  for (auto pElement : children_)
  {
    if (dynamic_cast<TaggedElement*>(pElement.get()) != nullptr)
      return true;
  }
  return false;
}
//----< add only one child to doc element using pointer to child >-----------

bool DocElement::addChild(std::shared_ptr<AbstractXmlElement> pChild)
{
  // don't add TextElements
  TextElement* pTxEl = dynamic_cast<TextElement*>(pChild.get());
  if (pTxEl != 0)  // don't add text elements to DocElement
    return false;

  // don't add another DocElement
  DocElement* pDcEl = dynamic_cast<DocElement*>(pChild.get());
  if (pDcEl != 0)  // don't add text elements to DocElement
    return false;

  // add ProcInstrElements and CommentElements 
  TaggedElement* te = dynamic_cast<TaggedElement*>(pChild.get());
  if (te == nullptr) // is not a TaggedElement
  {
    children_.push_back(pChild);
    return true;
  }

  // add only one TaggedElement
  if (!hasXmlRoot())
  {
    children_.push_back(pChild);
    return true;
  }
  return false;
}
//----< remove child from doc element using pointer to child >---------------

bool DocElement::removeChild(std::shared_ptr<AbstractXmlElement> pChild)
{
  auto iter = std::find(begin(children_), end(children_), pChild);
  if (iter != end(children_))
  {
    children_.erase(iter);
    return true;
  }
  return false;
}
//----< return value = tag from doc element >-----------------------------

std::string DocElement::value() { return std::string(""); }

//----< generate xml string for tagged element >-----------------------------

std::string DocElement::toString()
{
  std::string rtn;
  for (auto elem : children_)
    rtn += elem->toString();
  return rtn;
}

//----------<move constructor for tagged element>----------------

TaggedElement::TaggedElement(TaggedElement&& tagElem) :tag_(std::move(tagElem.tag_)), children_(std::move(tagElem.children_)), attribs_(std::move(tagElem.attribs_))
{
	
}

//

TaggedElement& TaggedElement::operator=(TaggedElement&& te)
{
	if (this == &te) return *this;
	this->tag_ = std::move(te.tag_);
	this->children_ = std::move(te.children_);
	this->attribs_ = std::move(te.attribs_);
	return *this;
}
//----< add child to tagged element using pointer to child >-----------------

bool TaggedElement::addChild(std::shared_ptr<AbstractXmlElement> pChild)
{
  children_.push_back(pChild);
  return true;
}
//----< remove child from tagged element using pointer to child >------------

bool TaggedElement::removeChild(std::shared_ptr<AbstractXmlElement> pChild)
{
  auto iter = std::find(begin(children_), end(children_), pChild);
  if (iter != end(children_))
  {
    children_.erase(iter);
    return true;
  }
  return false;
}
//----< remove child from tagged element using child's value >---------------

bool TaggedElement::removeChild(const std::string& value)
{
  for (auto iter = begin(children_); iter != end(children_); ++iter)
  {
    if ((*iter)->value() == value)
    {
      children_.erase(iter);
      return true;
    }
  }
  return false;
}
//----< add attribute to tagged element >------------------------------------

bool TaggedElement::addAttrib(const std::string& name, const std::string& value)
{
  std::pair<std::string, std::string> atPair(name, value);
  attribs_.push_back(atPair);
  return true;
}
//----< remove attribute from tagged element >-------------------------------

bool TaggedElement::removeAttrib(const std::string& name)
{
  for (auto iter = begin(attribs_); iter != end(attribs_); ++iter)
  {
    if (iter->first == name)
    {
      attribs_.erase(iter);
      return true;
    }
  }
  return false;
}
//----< return value = tag from tagged element >-----------------------------

std::string TaggedElement::value() { return tag_; }

//----< generate xml string for tagged element >-----------------------------

std::string TaggedElement::toString()
{
  std::string spacer(tabSize*++count, ' ');
  std::string xml = "\n" + spacer + "<" + tag_;
  for (auto at : attribs_)
  {
    xml += " ";
    xml += at.first;
    xml += "=\"";
    xml += at.second;
    xml += "\"";
  }
  xml += ">";
  for (auto pChild : children_)
    xml += pChild->toString();
  xml += "\n" + spacer + "</" + tag_ + ">";
  --count;
  return xml;
}

//---------------<move assignment for text element>--------------------

TextElement& TextElement::operator=(TextElement&& te)
{
	if (this == &te) return *this;
	text_ = std::move(te.text_);
	return *this;
}

//----< generate xml string for text element >-------------------------------

std::string TextElement::toString()
{
  std::string spacer(tabSize * ++count, ' ');
  std::string xml = "\n" + spacer + text_;
  --count;
  return xml;
}

//-----<move assignment to ProcInstElement>--------------------

ProcInstrElement& ProcInstrElement::operator=(ProcInstrElement&& procElem)
{
	if (this == &procElem) return *this;
	type_ = std::move(procElem.type_);
	attribs_ = std::move(procElem.attribs_);
	return *this;
}

//----< add attribute to ProcInstElement >-----------------------------------

bool ProcInstrElement::addAttrib(const std::string& name, const std::string& value)
{
  std::pair<std::string, std::string> atPair(name, value);
  attribs_.push_back(atPair);
  return true;
}
//----< remove attribute from ProcInstElement >------------------------------

bool ProcInstrElement::removeAttrib(const std::string& name)
{
  for (auto iter = begin(attribs_); iter != end(attribs_); ++iter)
  {
    if (iter->first == name)
    {
      attribs_.erase(iter);
      return true;
    }
  }
  return false;
}


//--------<to print the proc element in XML format>---------------------

std::string ProcInstrElement::toString()
{
	std::string spacer(tabSize*++count, ' ');
	std::string procInstext = "\n" + spacer + "<" + type_;
	for (auto at : attribs_)
	{
		procInstext += " ";
		procInstext += at.first;
		procInstext += "=\"";
		procInstext += at.second;
		procInstext += "\"";
	}
	procInstext += "?>";
	--count;
	return procInstext;
}

//----< generate xml string for text element >-------------------------------

std::string XmlDeclarElement::toString()
{
  std::string spacer(tabSize * ++count, ' ');
  std::string xml = "\n" + spacer + "<?xml";
  for (auto at : attribs_)
  {
    xml += " ";
    xml += at.first;
    xml += "=\"";
    xml += at.second;
    xml += "\"";
  }
  xml += "?>";
  --count;
  return xml;
}
//----< add attribute to ProcInstElement >-----------------------------------

bool XmlDeclarElement::addAttrib(const std::string& name, const std::string& value)
{
  std::pair<std::string, std::string> atPair(name, value);
  attribs_.push_back(atPair);
  return true;
}
//----< remove attribute from ProcInstElement >------------------------------

bool XmlDeclarElement::removeAttrib(const std::string& name)
{
  for (auto iter = begin(attribs_); iter != end(attribs_); ++iter)
  {
    if (iter->first == name)
    {
      attribs_.erase(iter);
      return true;
    }
  }
  return false;
}
//----< helper function displays titles >------------------------------------

void XmlProcessing::title(const std::string& title, char underlineChar)
{
  std::cout << "\n  " << title;
  std::cout << "\n " << std::string(title.size() + 2, underlineChar);
}


//--------------<move assignment for comment Element>------------------------

CommentElement& CommentElement::operator=(CommentElement&& commElem)
{
	if (this == &commElem) return *this;
	commentText_ = std::move(commElem.commentText_);
	return *this;
}


//----< test stub >----------------------------------------------------------



#ifdef TEST_XMLELEMENT

int main()
{
  title("Testing XmlElement Package", '=');
  std::cout << "\n";

  using sPtr = std::shared_ptr < AbstractXmlElement > ;

  sPtr root = makeTaggedElement("root");
  root->addChild(makeTextElement("this is a test"));

  sPtr child = makeTaggedElement("child");
  child->addChild(makeTextElement("this is another test"));
  child->addAttrib("first", "test");
  root->addChild(child);

  sPtr docEl = makeDocElement(root);
  std::cout << "  " << docEl->toString();
  std::cout << "\n\n";
  TaggedElement te1("child1");
  te1.addAttrib("version", "1.1");
  TaggedElement te2("child2");
  te2.addAttrib("version", "2.2");
  te2 = std::move(te1);
  std::cout << te2.value();
  std::cout << te1.value();
  TaggedElement te3 = std::move(te2);
  std::cout << te3.value();
 /* if (te2.getAttributes().size() != 0)
  {
	  for (auto s: te2.)
  }*/
}

#endif
