// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char prior) {
    if (prior == '*' || prior == '/') {
        return 3;
    } else {
        if (prior == '+' || prior == '-') {
            return 2;
        } else if (prior == ')')
            return 1;
        else
            return 0;
    }
}

std::string infx2pstfx(std::string inf) {
    TStack<char> firstStack;
    std::string strochka;
    for (int i = 0; i < inf.length(); i++) {
        if ((inf[i] >= '0') && (inf[i] <= '9')) {
            strochka += inf[i];
            strochka += ' ';
        } else if ((inf[i] == '(') || (priority(inf[i]) > priority(firstStack.get())) || (firstStack.isEmpty())) {
            firstStack.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!firstStack.isEmpty() && firstStack.get() != '(') {
                strochka += firstStack.get();
                strochka += ' ';
                firstStack.pop();
            }
            if (firstStack.get() == '(')
                firstStack.pop();
        } else {
            while ((!firstStack.isEmpty()) && (priority(firstStack.get()) >= priority(inf[i]))) {
                strochka = firstStack.get();
                strochka += ' ';
                firstStack.pop();
            }
            firstStack.push(inf[i]);
        }
    }
    while (!firstStack.isEmpty()) {
        strochka += firstStack.get();
        strochka += ' ';
        firstStack.pop();
    }
    return strochka;
}

int eval(std::string pst) {
      TStack<int> secondStack;
    int output;
    for (int i = 0; i < pst.length(); i++) {
        if ((pst[i] >= '0') && (pst[i] <= '9')) {
            secondStack.push(pst[i] - '0');
        } else {
            if (pst[i] != ' ') {
                int z = secondStack.get();
                secondStack.pop();
                int y = secondStack.get();
                secondStack.pop();
                if (pst[i] == '-') {
                    secondStack.push(y - z);
                } else if (pst[i] == '+') {
                    secondStack.push(y + z);
                } else if (pst[i] == '*') {
                    secondStack.push(y * z);
                } else {
                    secondStack.push(y / z);
                }
            }
        }
    }
    output = secondStack.get();
    return output;
}
