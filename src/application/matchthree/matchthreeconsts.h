#ifndef MATCHTHREECONSTS_H
#define MATCHTHREECONSTS_H

#include <string>

namespace gincu {

constexpr int boardRowCount = 8;
constexpr int boardColumnCount = boardRowCount;
constexpr int boardCellSize = 60;
constexpr int boardStartX = 320;
constexpr int boardStartY = 80;

constexpr int secondsPerRound = 60;

constexpr int normalFontSize = 24;
constexpr int largeFontSize = 48;

const std::string backgroundImageName("matchthree/background.png");

} //namespace gincu

#endif
