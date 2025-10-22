#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

void usage (string name) {
  cout<<"USAGE:"<<endl;
  cout<<name<<" inputFile"<<endl;
  return;
}

vector<string> lexExpression(string line) {
  vector<string> exprTokens;
  string value;
  while (line.size()) {
    while (line[0] == ' ') line.erase(0, 1);
    if (line[0] == '\n') break;
    switch (line[0]) {
    case '+':
      exprTokens.push_back(value);
      exprTokens.push_back("PLUS_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      break;
    case '-':
      exprTokens.push_back(value);
      exprTokens.push_back("MINUS_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      break;
    case '|':
      exprTokens.push_back(value);
      exprTokens.push_back("OR_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      break;
    case '/':
      exprTokens.push_back(value);
      exprTokens.push_back("NOR_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      break;
    case '&':
      exprTokens.push_back(value);
      exprTokens.push_back("AND_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      break;
    case '$':
      exprTokens.push_back(value);
      exprTokens.push_back("NAND_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      break;
    case '^':
      exprTokens.push_back(value);
      exprTokens.push_back("XOR_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      break;
    case '#':
      exprTokens.push_back(value);
      exprTokens.push_back("XNOR_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      break;
    case '>':
      exprTokens.push_back(value);
      if (line[1] == '>') {
	exprTokens.push_back("SHR_T");
	line.erase(0, 2);
	value.erase(0, value.size());
      } else if (line[1] == '=') {
	exprTokens.push_back("GRATER_EQ_T");
	line.erase(0, 2);
	value.erase(0, value.size());
      } else {
      exprTokens.push_back("GRATER_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      }
      break;
    case '<':
      if (line[1] == '=') {
	exprTokens.push_back(value);
	exprTokens.push_back("LESS_EQ_T");
	line.erase(0, 2);
	value.erase(0, value.size());
      } else {
      exprTokens.push_back(value);
      exprTokens.push_back("LESS_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      }
      break;
    case ';':
      exprTokens.push_back(value);
      exprTokens.push_back("SEMICOLON_T");
      line.erase(0, 1);
      value.erase(0, value.size());
      break;
    case '=':
      if (line[1] == '=') {
	exprTokens.push_back(value);
	exprTokens.push_back("EQ_T");
	line.erase(0, 2);
	value.erase(0, value.size());
      } else {
	exprTokens.push_back(value);
	exprTokens.push_back("ERROR_T");
	line.erase(0, 1);
	value.erase(0, value.size());
      }
      break;
    default:
      value+=line[0];
      line.erase(0, 1);
    }
  }
  return exprTokens;
}

vector<string> lex(string line) {
  vector<string> tokens;
  if (line.compare(0, 4, "var ") == 0) {
    tokens.push_back("VAR_T");
    line.erase(0, 4);
    
    string name;
    while (line[4] == ' ') line.erase(4, 1);
    for (int i = 0; i<line.size(); i++) {
      if (line[i] == ' ' || line[i] == '=') break;
      name+=line[i];
    }
    tokens.push_back(name);
    line.erase(0, name.size());
    
    while (line[0] == ' ') line.erase(0, 1);
    switch (line[0]) {
    case '=': {
      tokens.push_back("ASSERT_T");
      line.erase(0, 1);
      vector<string> exprTokens = lexExpression(line);
      for (int i = 0; i<exprTokens.size(); i++) tokens.push_back(exprTokens[i]);
      break;
    }
    case ';':
      tokens.push_back("SEMICOLON_T");
      line.erase(0, 1);
      break;
    default: tokens.push_back("ERROR_T"); break;
    }
   
  }
  return tokens;
}

int main(int argc, char** argv) {
  string name = argv[0];
  if (argc < 2) {
    cout<<"ERROR: No input file specified!"<<endl;
    usage(name);
    return 1;
  }

  ifstream fi(argv[1]);

  if (!fi) {
    cout<<"ERROR: Can't open file: "<<argv[1]<<endl;
    return 1;
  }

  string line;
  vector<string> tokens;
  while (getline(fi, line)) {
    tokens = lex(line);
  }
  for (int i = 0; i< tokens.size(); i++) cout<<tokens[i]<<endl;

  fi.close();
}
