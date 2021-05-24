#include <gtest.h>
#include <Text.h>

TEST(TestText, create_empty_text) {
  ASSERT_NO_THROW(Text T());
}

TEST(TestText, create_non_empty_text) {
  char* t = "Some text";
  ASSERT_NO_THROW(Text T(t));
}

TEST(TestText, multiple_lines_be_added) {
  char* t = "Some text. \nSome line of text.";
  ASSERT_NO_THROW(Text T(t));
}

TEST(TestText, insert_data_into_text) {
  char* t = "Some text.";
  Text T(t);
  TextIter K = T.Find("x");
  
  ASSERT_NO_THROW(T.DataInsert("Qwerty", K));
}

TEST(TestText, get_the_first_symbol) {
  char* t = "Some text";
  Text T(t);
  TextIter iter = T.GetRoot();
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'S');
}

TEST(TestText, get_the_first_symbol_of_the_next_word) {
  char* t = "Some text";
  Text T(t);
  TextIter i = T.GetRoot();
  while (i.Get()->GetC() != ' ')
  {
    i.GoNextChar();
  }
  i.GoNextChar();
  ASSERT_EQ(i.Get()->GetC(), 't');
}

TEST(TestText, cannot_get_the_next_symbol_if_there_is_none) {
  char* t = "N";
  Text T(t);
  TextIter i = T.GetRoot();
  i.GoNextChar();
  ASSERT_EQ(i.GoNextChar(), false);
}

TEST(TestText, go_next) {
  char* t = "Some text";
  Text T(t);
  TextIter i = T.GetRoot();
  ASSERT_EQ(i.GoNext(), true);
}

TEST(TestText, find_the_symbol) {
  char* t = "Some text";
  Text T(t);
  TextIter i = T.Find('o');
  i.GoNextChar();
  ASSERT_EQ(i.Get()->GetC(), 'm');
}

TEST(TestText, insert_the_symbol) {
  char* t = "Some text";
  Text T(t);
  TextIter i = T.GetRoot();
  ASSERT_NO_THROW(T.Insert("Q", i));
}

TEST(TestText, find_the_word) {
  char* t = "Some text";
  Text T(t);
  char* t_find = "text";
  TextIter i = T.FindWord(t_find);
  i.GoNextChar();
  ASSERT_EQ(i.Get()->GetC(), 't');
}

TEST(TestText, text_delete) {
  char* t = "Some text";
  Text T(t);
  char* t_find = "Some";
  TextIter i = T.FindWord(t_find);
  ASSERT_NO_THROW(T.Delete(3, i));
}


TEST(TestText, save_to_file) {
  char* t = "Some text";
  Text T(t);
  ASSERT_NO_THROW(T.FileSave());
}

TEST(TestText, load_from_file) {
  char* t = "";
  Text T(t);
  ASSERT_NO_THROW(T.FileLoad("Text.txt"));
}

TEST(TestText, _copy) {
  char* t = "Some text";
  Text T(t);
  char t_find = 't';
  TextIter i = T.Find(t_find);
  ASSERT_NO_THROW(char* result = T.Copy(4, i));
}