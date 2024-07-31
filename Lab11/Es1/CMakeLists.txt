cmake_minimum_required(VERSION 3.12)
project(Esercizio1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Esercizio1 main.c data.c data.h titoli.c titoli.h cmake-build-debug/quotazioneGiorn.c cmake-build-debug/quotazioneGiorn.h quotazioni.c quotazioni.h)