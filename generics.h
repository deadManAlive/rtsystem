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
#define bool unsigned int

//type aliases, for readibility too hopefully
typedef unsigned int index;               //array index

//generic error macros
#define INPUT_ERROR "Err 001: Kesalahan pada masukan!"
#define TIME_ERROR "Err 002: Masukan data waktu diluar cakupan!"

#endif