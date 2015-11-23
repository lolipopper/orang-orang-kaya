#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include "player.h"
#include "petakBoard.h"
#include "chance.h"
#include "dadu.h"
#include "mesinkata.h"
#include "action.h"

void PetakToDo(Address P);

void BacaCommand(Kata *K);

void DoCommand(Kata K, ListBoard LB, TabKota Kota, Player *P);

#endif // COMMAND_H
