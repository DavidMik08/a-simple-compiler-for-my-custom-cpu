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

vector<string> lex(string line) {
  vector<string> tokens;
  if (line.compare("var ", 0, 4) == 0) {
    tokens.push_back("VAR_T");
    string name;
    for (int i = 4; i<line.size(); i++) {
      if (line[i] == ' ') break;
      name+=line[i];
    }
    tokens.push_back(name);
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
  while (getline(fi, line)) {
    vector<string> tokens = lex(line);
  }

  fi.close();
}
