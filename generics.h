//aliases, structs, and datas used by all mechanics

#ifndef GENERICS_H
#define GENERICS_H

//OS command compatibility
#ifdef _WIN32
#define CLEAR_SCREEN "cls"     // for Windows
#else
#define CLEAR_SCREEN "clear"   // for *nix
#endif

//bool macros, for readibility
#define TRUE  1
#define FALSE 0
#define UNKNOWN -1 //in case three-state logic needed
#define bool int

//type aliases, for readibility too hopefully
typedef unsigned int index;               //array index

//generic error macros
#define INPUT_ERROR "ERR 001: Kesalahan pada masukan!"
#define TIME_ERROR  "ERR 002: Masukan data waktu diluar cakupan!"
#define STAT_ERROR  "ERR 003: Stasiun asal dan tujuan sama!"

#endif