#ifndef GENERICS_H
#define GENERICS_H

//all aliases, structs, and datas used by all parts

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
typedef unsigned long int distance_meter; //distance
typedef unsigned int index;               //array index

//error macros
#define INPUT_ERROR "Err 001: masukkan salah! Masukkan 1 untuk lanjut: "

#endif