cmake_minimum_required(VERSION 3.10)
project(Statki)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(statki
    main.cpp Pole.cpp Statek.cpp StatkiPochodne.cpp Plansza.cpp
    Gracz.cpp Czlowiek.cpp KomputerLosowy.cpp KomputerSprytny.cpp
    Wynik.cpp Ranking.cpp Gra.cpp)
