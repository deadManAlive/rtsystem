//generic functions

#include <stdio.h>

#include "generics.h"

//pause screen function
void pause_scr(char char_to_press){
    while (getchar() != char_to_press); //prevent adv. until user inputs certain char.
}