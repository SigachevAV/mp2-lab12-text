#include <iostream>
#include "Text.h"

using namespace std;

int main()
{
	char* temp = "New text";
	Text T(temp);
	TextIter i = T.FindWord("New");

	//T.Insert(" sdsfsdfsfsdf zxczczcxc\n skkyukys\n fggfgff", T.GetRoot());

	//TextIter i2 = T.FindWord("zxczczcxc");
	T.Delete(3, i);
	T.FileSave();
  return 0;
}
