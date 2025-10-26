#include "Words.h"
#include <fstream>

std::vector<std::string> word_list()
{
  const int wordNum = 354296;
  std::ifstream is{"data/english.txt"};
  std::vector<std::string> ret;
  ret.reserve(wordNum);
  std::string word;
  while (std::getline(is, word)) {
    ret.push_back(word);
  }
  return ret;
}