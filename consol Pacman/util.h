#pragma once
#include "Board.h"

int manhattenDistance(const VectorInt v1, const VectorInt v2);
VectorInt shotestDist(VectorInt pac_v, VectorInt deam_v, Board _b);
VectorInt shotestNeib(VectorInt v1, Board _b);
VectorInt randomClosePath(VectorInt v1, Board _b);
VectorInt copyPlayer(VectorInt v1, VectorInt v2, VectorInt v3, Board _b);

bool isValid(VectorInt pos);
bool samePlace(const VectorInt pos1, const VectorInt pos2);