#ifndef MEGASENA_H
#define MEGASENA_H

#include <stdio.h>
#include <stdlib.h>

void print_wellcome();
void get_start();
void get_dozens_quantity(int *dozens_quantity);
void get_manual_bets_quantity(int *manual_bets_quantity);
void get_manual_bets(int manual_bets_quantity, int dozens_quantity, int (*manual_bets)[manual_bets_quantity][dozens_quantity]);
void get_surprises_quantity(int *surprises_quantity);
void get_stubborny_quantity(int *stubborny_quantity);

#endif