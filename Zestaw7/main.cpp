#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

bool is_number(const string& s) {
  for (size_t i = 0; i < s.length(); i++) {
    if (i == 0 && s[i] == '-' && s.length() > 1) continue;
    if (!isdigit(s[i])) return false;
  }

  return true;
}

int rpn(vector<string> input) {
  stack<int> stack;

  for (auto i : input) {
    if (is_number(i)) {
      stack.push(stoi(i));
    } else {
      int a = stack.top();
      stack.pop();
      int b = stack.top();
      stack.pop();

      if (i == "+") {
        stack.push(b + a);
      } else if (i == "-") {
        stack.push(b - a);
      } else if (i == "*") {
        stack.push(b * a);
      } else if (i == "/") {
        assert(a != 0);
        stack.push(b / a);
      }
    }
  }

  return stack.top();
}

int main(int argc, char const *argv[]) {
  vector<string> input;

  input = {"-6", "2", "/"};
  for (auto i : input) cout << i << ' ';
  cout << "= " << rpn(input) << '\n';// result = -3

  input = {"2", "3", "+", "5", "*"};
  for (auto i : input) cout << i << ' ';
  cout << "= " << rpn(input) << '\n'; // result = 25

  input = {"2", "3", "+", "5", "/"};
  for (auto i : input) cout << i << ' ';
  cout << "= " << rpn(input) << '\n'; // result = 1

  input = {"2", "3", "-", "5", "*"};
  for (auto i : input) cout << i << ' ';
  cout << "= " << rpn(input) << '\n'; // result = 1

  return 0;
}
