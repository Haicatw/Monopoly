cmake_minimum_required(VERSION 2.8)
project(HoardingCPPVersion)

set(CMAKE_CXX_STANDARD 14)
set(GPP_ENABLE_WARNINGS "-O0 -Wall -Werror -Wno-unused-result")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GPP_ENABLE_WARNINGS}")
set(SOURCE_FILES main.cpp setup.cpp setup.h utility.cpp utility.h display.cpp display.h game.cpp game.h board.cpp board.h diceroller.cpp diceroller.h player.cpp player.h rules.cpp rules.h gamelogic.cpp gamelogic.h propertylogic.cpp propertylogic.h playerlogic.cpp playerlogic.h)
add_executable(HoardingCPPVersion ${SOURCE_FILES} setup.cpp setup.h utility.cpp utility.h display.cpp display.h game.cpp game.h board.cpp board.h diceroller.cpp diceroller.h player.cpp player.h rules.cpp rules.h gamelogic.cpp gamelogic.h propertylogic.cpp propertylogic.h playerlogic.cpp playerlogic.h)