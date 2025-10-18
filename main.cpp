#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

class Var {    // a class used to store data about a variable
public:
  int addr;
  string name;
  Var(int addr, string name) {
    this -> addr = addr;
    this -> name = name;
  }
};

vector<Var> vars;    // a vector to store all of the variables

const int startAddress = 8388608;    // the address where the first variable is stored

void genVarStore(int addr, ofstream& fo) {    // a function that generates asm code for storing a value to a variable
  Var var = vars[addr - startAddress];    // getting the variable from the vector
  fo << endl << "; Storing to the variable " << var.name <<" at the address: " << addr << endl;
  // setting the variables ram address
  fo << "add " << var.name << ".Low 0 r7" << endl;
  fo << "add " << var.name << ".Mid 0 r8" << endl;
  fo << "add " << var.name << ".High 0 r9" << endl;
  // storing the variables value to its address
  fo << "add stk 0 ram" << endl;
  return;
}

void handleExpression(string expression, ofstream& fo) {
  cout << expression << endl;
  if (all_of(expression.begin(), expression.end(), ::isdigit)) fo << "add " << stoi(expression) << " 0 stk" << endl;
  else {
    int num = 0;
    int place = 1;
    vector<char> op;
    for (int c = 0; c < expression.size(); c++) {
      switch (expression[c]) {
      case '+':
      case '-':
      case '|':
      case '/':
      case '&':
      case '$':
      case '^':
      case '#':
      case '>': op.push_back(expression[c]); break;
      }
    }
    for (int i = expression.size() - 1; i >= 0; i--) {
      if (isdigit(expression[i])) {
	num += (expression[i] - '0') * place;
	place *= 10;
      } else {
	fo << "add " << num << " 0 stk" << endl;
	place = 1;
	num = 0;
      }
    }
    fo << "add " << num << " 0 stk" << endl;
    place = 1;
    num = 0;

    for (int i = 0; i < op.size(); i++) {
      fo << "add stk 0 r1" << endl;
      fo << "add stk 0 r2" << endl;
      switch (op[i]) {
      case '+': fo << "add r1 r2 stk"  << endl; break;
      case '-': fo << "sub r1 r2 stk"  << endl; break;
      case '|': fo << "or r1 r2 stk"   << endl; break;
      case '/': fo << "nor r1 r2 stk"  << endl; break;
      case '&': fo << "and r1 r2 stk"  << endl; break;
      case '$': fo << "nand r1 r2 stk" << endl; break;
      case '^': fo << "xor r1 r2 stk"  << endl; break;
      case '#': fo << "xnor r1 r2 stk" << endl; break;
      case '>': fo << "shr r1 r2 stk"  << endl; break;
      }
    }
  }
  return;
}

void handleVar(string line, ofstream& fo) { // handles variable declaration, example: "var a = 10"
  line.erase(0, 4); // removes "var " from the begining leaving us with "varName = value;", example: "a = 10"
  bool select = false;
  string name;
  string expression;
  for (int i = 0; i < line.size(); i++) {
    if (line[i] != ' ' && line[i] != '\n' && line[i] != '=' && !select) name += line[i];    // extracts the name of the variable from the line
    else if (line[i] != ' ' && line[i] != '\n' && line[i] != '=' && select) expression += line[i];    // extracts the expression that needs to be calculated from the line
    else if (line [i] == '=') select = true;    // switches from extracting the name to extracting the expression
  }
  
  int addr = vars.size() + startAddress;
  Var temp(addr, name);
  vars.push_back(temp);
  fo << endl << "; Making a definition for the address of variable: " << name << endl;
  fo << "#define " << name << " " << addr << endl;    // defines a constant value with the same name as the variable, and sets its value to the variables address (used for cleaner asm code)
  handleExpression(expression, fo);
  genVarStore(addr, fo);
  return;
}

void parse (string line, ofstream& fo) {
  if (line.compare(0, 4, "var ") == 0) handleVar(line, fo);
  return;
}

int main(int argc, char** argv) {
  int startAddr = 8388608;

  if (argc < 3) {
    cerr << "ERROR: wrong use format" << endl << "correct format \"./compiler input output\"";
    return 1;
  }
  
  ifstream fi(argv[1]);
  if (!fi.is_open()) {
    cerr << "Error opening the file!";
    return 1;
  }
  ofstream fo(argv[2]);

  string line;
  while (getline(fi, line)) {
    parse(line, fo);
  }
}
