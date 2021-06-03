// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char op) {
  if (op == '(' || op == ')')
    return 0;
  else if (op == '+' || op == '-')
    return 1;
  else if (op == '*' || op == '/')
    return 2;
}

std::string infx2pstfx(std::string inf) {
  std::string result = "";
  TStack<char> ops;
  for (int i = 0; i < inf.length(); i++) {
    if (inf[i] >= '0' && inf[i] <= '9') {
      if (!(inf[i-1] >= '0' && inf[i-1] <= '9') && result[result.length()-1] != ' ')
        result += ' ';
      result += inf[i];
    } else if (inf[i] == '(') {
      if (result != "" && result[result.length()-1] != ' ')
        result += ' ';
      ops.push(inf[i]);
    } else if (inf[i] == ')') {
      while (ops.get() != '(') {
        if (result[result.length()-1] != ' ')
          result += ' ';
        result += ops.get();
        ops.pop();
      }
      ops.pop();
    } else if (inf[i] != ' ') {
      if (!ops.isEmpty()) {
        while ((!ops.isEmpty()) && priority(ops.get()) >= priority(inf[i])) {
          result += ' ';
          result += ops.get();
          ops.pop();
        }
      }
      ops.push(inf[i]);
    }
  }
  while (!ops.isEmpty()) {
      result += ' ';
      result += ops.get();
      ops.pop();
    }
  if (result[0] == ' ')
    result.erase(0, 1);
  return result;
}

int eval(std::string pst) {
     int result = 0, temp = 0, x = 0, y = 0;
  TStack<int> opns;
  if (pst[0] >= '0' && pst[0] <= '9')
    opns.push((int)pst[0] - 48);
  for (int i = 1; i < pst.length(); i++) {
    if (pst[i] >= '0' && pst[i] <= '9') {
      if (pst[i-1] >= '0' && pst[i-1] <= '9') {
        temp = opns.get() * 10 + (int) pst[i] - 48;
        opns.pop();
        opns.push(temp);
      } else {
        opns.push((int)pst[i] - 48);
    } else if (pst[i] != ' ') {
      y = opns.get();
      opns.pop();
      x = opns.get();
      opns.pop();
      if (pst[i] == '+')
        opns.push(x + y);
      else if (pst[i] == '-')
        opns.push(x - y);
      else if (pst[i] == '*')
        opns.push(x * y);
      else if (pst[i] == '/')
        opns.push(x / y);
    }
  }
  result = opns.get();
  return result;
}
