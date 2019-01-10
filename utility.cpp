//
// Created by Kirby Zhou on 2/4/18.
//
#include "utility.h"

using namespace Monopoly;

int Monopoly::max(int a, int b) {
    if (a < b) {
        return b;
    } else {
        return a;
    }
}