#pragma once
#include <iostream>
#include "Stack.h"
#include <cstring>

enum class level { TEXT = 0, STRING = 1, WORD = 2, LETTER = 3 };

class TextNode
{
protected:
  static TextNode* firstFree; 
  static TextNode* textNodes; 
  static TextNode* textNodes_tmp; 

  TextNode* next; 
  TextNode* down; 
  char c; 
  level lvl;

public:
  TextNode(level _l = level::STRING, char _c = 0);
  TextNode(char* _c, level _l);
  TextNode(const TextNode& _node);
  ~TextNode(); 

  TextNode* GetNext();  
  TextNode* GetDown();  
  char GetC(); 
  level GetLevel();  

  void SetNext(TextNode* _next); 
  void SetDown(TextNode* _down); 
  void SetC(char _c); 
  void SetLevel(level _l);

  static void InitMem(int _size = 10);
  static void FreeMem();
  
  void* operator new(size_t size);
  void operator delete(void* p);

  friend std::ostream& operator<<(std::ostream& o, TextNode& t);
};

TextNode* TextNode::firstFree = 0;
TextNode* TextNode::textNodes = 0;
TextNode* TextNode::textNodes_tmp = 0;

std::ostream& operator<<(std::ostream& o, TextNode& t)
{
  if (t.lvl == level::LETTER)
  {
    o << t.c;
    if (t.next != nullptr)
      o << *(t.next);
  }
  else
  {
    if (t.down != nullptr)
      o << *(t.down);

    if (t.next != nullptr)
      o << *(t.next);
  }

  return o;
}

TextNode::TextNode(level _l, char _c)
{
  next = nullptr;
  down = nullptr;
  c = _c;
  lvl = _l;
}

TextNode::TextNode(char* _c, level l)
{
  if (l == level::STRING) {
    next = nullptr;
    c = 0;
    lvl = l;
    int size = strlen(_c);

    if (size > 0)
    {
      int start = 0; 
      TextNode* wcur = new TextNode(level::WORD);
      this->SetDown(wcur);

      for (int i = 0; i < size; i++)
      {
        if (_c[i] == ' ' || i == size - 1)
        {
          if (start != 0) 
          {
            wcur->SetNext(new TextNode(level::WORD)); 
            wcur = wcur->GetNext(); 
          }

          TextNode* lcur = new TextNode(level::LETTER, _c[start]); 
          wcur->SetDown(lcur); 

          for (int j = start + 1; j <= i; j++) 
          {
            lcur->SetNext(new TextNode(level::LETTER, _c[j]));
            lcur = lcur->GetNext();
          }

          lcur->SetNext(nullptr);
          start = i + 1;
        }
      }
      wcur->SetNext(nullptr);
    }
  }

  if (l == level::WORD) {
    next = nullptr;
    c = 0;
    lvl = l;
    int size = strlen(_c);
    if (size > 0) 
    {
      TextNode* lcur = new TextNode(level::LETTER, _c[0]);
      this->SetDown(lcur); 

      for (int i = 1; i < size; i++) 
      {
        lcur->SetNext(new TextNode(level::LETTER, _c[i]));
        lcur = lcur->GetNext();
      }
      lcur->SetNext(nullptr);
    }
  }

  if (l == level::LETTER)
  {
    c = _c[0]; 
    lvl = l; 
    next = nullptr;
    down = nullptr;
  }
}

TextNode::TextNode(const TextNode& _node)
{
    next = nullptr;
    down = nullptr;
    c = _node.c;
    lvl = _node.lvl;
}

TextNode::~TextNode() {}

TextNode* TextNode::GetNext() { return next; }

TextNode* TextNode::GetDown() { return down; }

char TextNode::GetC() { return c; }

level TextNode::GetLevel() { return lvl; }

void TextNode::SetNext(TextNode* _next) { next = _next; }

void TextNode::SetDown(TextNode* _down) { down = _down; }

void TextNode::SetC(char _c) { c = _c; }

void TextNode::SetLevel(level _l)
{
  if (_l >= level::STRING && _l <= level::LETTER)
  {
    lvl = _l;
  }
  else throw -1; 
}

void TextNode::InitMem(int _size) 
{
  if (_size <= 0)  throw -1;

  if ((firstFree == 0) && (textNodes == 0)) 
  {
    textNodes = new TextNode[_size];
    firstFree = textNodes;
  }
  else if ((firstFree != 0) && (textNodes == 0))
  {
    throw -1;
  }
  else
  {
    textNodes_tmp = new TextNode[_size]; 

    for (int i = 0; i < _size; i++)
    {
      textNodes_tmp[i] = (textNodes[i]);
    }

    textNodes = new TextNode[_size * 2];
    firstFree = textNodes;

    for (int i = 0; i < _size; i++)
    {
      textNodes[i] = textNodes_tmp[i]; 
    }

    delete[] textNodes_tmp;
    textNodes_tmp = 0; 
  }
}

void TextNode::FreeMem()
{
  if (textNodes != NULL)
  {
    delete[] textNodes;
  }
  textNodes = 0;
  firstFree = 0;
}

void* TextNode::operator new(size_t size)
{
  if ((firstFree == 0) && (textNodes == 0))
    InitMem();

  if ((firstFree == 0) && (textNodes != 0)) 
    InitMem();

  TextNode* node = firstFree;
  firstFree = firstFree->next;

  node->next = 0;

  return node;
}

void TextNode::operator delete(void* p)
{
  TextNode* node = (TextNode*)p;

  if ((firstFree == 0) && (textNodes == 0)) throw -1;

  node->next = nullptr;
  node->down = nullptr;
  node->c = 0;
  node->lvl = level::LETTER;

  node->next = firstFree;
  firstFree = node;
}