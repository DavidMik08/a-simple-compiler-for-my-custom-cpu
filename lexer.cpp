#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

vector<string> lex(string, ifstream&);


int usage (string name) {
  cout<<"USAGE:"<<endl;
  cout<<name<<" inputFile"<<endl;
  return 0;
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

vector<string> lexForExpression(string line, ifstream& fi) {    // line = var name = value; condition; increment;
  vector<string> tokens;
  string asignment;
  string condition;
  string increment;
  do {
    asignment += line[0];
    line.erase(0, 1);
  } while (line[0] != ';');
  asignment += line[0];
  line.erase(0, 1);
  while (line[0] == ' ') line.erase(0, 1);
  do {
    condition += line[0];
    line.erase(0, 1);
  } while (line[0] != ';');
  condition += line[0];
  line.erase(0, 1);
  while (line[0] == ' ') line.erase(0, 1);
  do {
    increment += line[0];
    line.erase(0, 1);
  } while (line[0] != ';');
  increment += line[0];
  line.erase(0, 1);
  while (line[0] == ' ') line.erase(0, 1);
  
  cout << "Asignment: " << asignment << ", Condition: " << condition << ", Increment: " << increment << endl;

  vector<string> asignmentTokens = lex(asignment, fi);
  vector<string> conditionTokens = lex(condition, fi);
  vector<string> incrementTokens = lex(increment, fi);
  for (int i = 0; i<asignmentTokens.size(); i++) {
    tokens.push_back(asignmentTokens[i]);
    cout << "Asignment Tokens: " << asignmentTokens[i] << endl;
  }
  cout << "Cond size: " << conditionTokens.size() << endl;
  for (int i = 0; i<conditionTokens.size(); i++) {
    tokens.push_back(conditionTokens[i]);
    cout << "Condition Tokens: " << conditionTokens[i] << endl;
  }
  for (int i = 0; i<incrementTokens.size(); i++) {
    tokens.push_back(incrementTokens[i]);
    cout << "Increment Tokens: " << incrementTokens[i] << endl;
  }
  return tokens;
}

vector<string> lexBlock(string& line, ifstream& fi) {
  vector<string> tokens;
  tokens.push_back("OPEN_B_T");
  vector<string> lineTokens;
  while (getline(fi, line)) {
    while (line[0] == ' ') line.erase(0, 1);
    if (line[0] == '}') {
      line.erase(0, 1);
      break;
    }
    lineTokens = lex(line, fi);
    for (int i = 0; i<lineTokens.size(); i++) tokens.push_back(lineTokens[i]);
  }
  tokens.push_back("CLOSE_B_T");
  return tokens;
}

vector<string> lex(string line, ifstream& fi) {
  vector<string> tokens;
  while (line[0] == ' ') line.erase(0, 1);
  if (line.compare(0, 4, "var ") == 0) {
    tokens.push_back("VAR_T");
    line.erase(0, 4);
    
    string name;
    while (line[0] == ' ') line.erase(0, 1);
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
   
  } else if (line.compare(0, 2, "if") == 0) {
    tokens.push_back("IF_T");
    line.erase(0, 2);
    while (line[0] == ' ') line.erase(0, 1);
    if (line[0] == '(') {
      tokens.push_back("OPEN_P_T");
      line.erase(0, 1);

      string expr;
      while (line[0] != ')') {
        expr.push_back(line[0]);
	line.erase(0, 1);
      }
      line.erase(0, 1);
      vector<string> exprTokens = lexExpression(expr);
      for (int i = 0; i<exprTokens.size(); i++) tokens.push_back(exprTokens[i]);
      while (line[0] == ' ') line.erase(0, 1);
      tokens.push_back("CLOSE_P_T");
      
      if (line[0] == '{') { // noinline if
	line.erase(0, 1);
	vector<string> blockTokens = lexBlock(line, fi);
	for (int i = 0; i<blockTokens.size(); i++) tokens.push_back(blockTokens[i]);
	vector<string> afterIf = lex(line, fi);
	for (int i = 0; i<afterIf.size(); i++) tokens.push_back(afterIf[i]); // lexes the rest of the line where the block ends 
      } else { // inline if
	vector<string> ifTokens = lex(line, fi);
	for (int i = 0; i<ifTokens.size(); i++) tokens.push_back(ifTokens[i]);
      }
    } else tokens.push_back("ERROR_T");
  } else if (line.compare(0, 4, "else") == 0) {    // else
    tokens.push_back("ELSE_T");
    line.erase(0, 4);
    while (line[0] == ' ') line.erase(0, 1);
    if (line[0] == '{') {    // noinline else
      line.erase(0, 1);
      vector<string> blockTokens = lexBlock(line, fi);
      for (int i = 0; i<blockTokens.size(); i++) tokens.push_back(blockTokens[i]);
      vector<string> afterElse = lex(line, fi);
      for (int i = 0; i<afterElse.size(); i++) tokens.push_back(afterElse[i]); // lexes the rest of the line where the block ends 
    } else {    // inline else
      vector<string> elseTokens = lex(line, fi);
      for (int i = 0; i<elseTokens.size(); i++) tokens.push_back(elseTokens[i]);
    }
  } else if (line.compare(0, 5, "while") == 0) {
    tokens.push_back("WHILE_T");
    line.erase(0, 5);
    while (line[0] == ' ') line.erase(0, 1);
    if (line[0] == '(') {
      tokens.push_back("OPEN_P_T");
      line.erase(0, 1);

      string expr;
      while (line[0] != ')') {
        expr.push_back(line[0]);
	line.erase(0, 1);
      }
      line.erase(0, 1);
      vector<string> exprTokens = lexExpression(expr);
      for (int i = 0; i<exprTokens.size(); i++) tokens.push_back(exprTokens[i]);
      while (line[0] == ' ') line.erase(0, 1);
      tokens.push_back("CLOSE_P_T");
      
      if (line[0] == '{') { // noinline while
	line.erase(0, 1);
	vector<string> blockTokens = lexBlock(line, fi);
	for (int i = 0; i<blockTokens.size(); i++) tokens.push_back(blockTokens[i]);
	vector<string> afterWhile = lex(line, fi);
	for (int i = 0; i<afterWhile.size(); i++) tokens.push_back(afterWhile[i]); // lexes the rest of the line where the block ends 
      } else { // inline while
	vector<string> whileTokens = lex(line, fi);
	for (int i = 0; i<whileTokens.size(); i++) tokens.push_back(whileTokens[i]);
      }
    } else tokens.push_back("ERROR_T");
  } else if (line.compare(0, 3, "for") == 0) {
    tokens.push_back("FOR_T");
    line.erase(0, 3);
    while (line[0] == ' ') line.erase(0, 1);
    if (line[0] == '(') {
      tokens.push_back("OPEN_P_T");
      line.erase(0, 1);

      string expr;
      while (line[0] != ')') {
        expr.push_back(line[0]);
	line.erase(0, 1);
      }
      line.erase(0, 1);
      cout << "For expression: " << expr << endl;
      vector<string> exprTokens = lexForExpression(expr, fi);
      for (int i = 0; i<exprTokens.size(); i++) tokens.push_back(exprTokens[i]);
      while (line[0] == ' ') line.erase(0, 1);
      tokens.push_back("CLOSE_P_T");
      
      if (line[0] == '{') { // noinline for
	line.erase(0, 1);
	vector<string> blockTokens = lexBlock(line, fi);
	for (int i = 0; i<blockTokens.size(); i++) tokens.push_back(blockTokens[i]);
	vector<string> afterFor = lex(line, fi);
	for (int i = 0; i<afterFor.size(); i++) tokens.push_back(afterFor[i]); // lexes the rest of the line where the block ends 
      } else { // inline for
	vector<string> forTokens = lex(line, fi);
	for (int i = 0; i<forTokens.size(); i++) tokens.push_back(forTokens[i]);
      }
    } else {
      string varName;
      while (line[0] != ' ' && line[0] != '=') {
	varName+=line[0];
	line.erase(0, 1);
      }
      tokens.push_back(varName);
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
  }
  return tokens;
}
