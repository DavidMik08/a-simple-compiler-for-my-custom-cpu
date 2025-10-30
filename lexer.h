#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <fstream>
using namespace std;
vector<string> lex(string, ifstream&);
int usage (string name);
vector<string> lexExpression(string line);
vector<string> lexForExpression(string line, ifstream& fi);
vector<string> lexBlock(string& line, ifstream& fi);
vector<string> lex(string line, ifstream& fi);


#endif
