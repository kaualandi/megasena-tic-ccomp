#ifndef MEGASENA_H
#define MEGASENA_H

#include <stdio.h>
#include <stdlib.h>

void print_wellcome();
void get_start();
void get_dozens_quantity(int *dozens_quantity);
void get_manual_bets_quantity(int *manual_bets_quantity);
int **allocate_manual_bets(int manual_bets_quantity, int dozens_quantity);
void get_manual_bets(int manual_bets_quantity, int dozens_quantity, int **random_bets);
void get_surprises_quantity(int *surprises_quantity);
void get_stubborny_quantity(int *stubborny_quantity);
int **allocate_memory(int surprises_quantity, int dozens_quantity);
void generate_surprises_bets(int surprises_quantity, int dozens_quantity, int **random_bets);
void free_memory(int **bets, int surprises_quantity);
void print_bets(int dozens_quantity, int **manual_bets, int **random_bets, int manual_bets_quantity, int surprises_quantity);
int calc_price(int dozens_quantity, int manual_bets_quantity, int surprises_quantity, int stubborny_quantity);
int confirm_price();
int generate_competitions(int stubborny_quantity, int dozens_quantity, int manual_bets_quantity, int surprises_quantity, int **manual_bets, int **random_bets);
void show_total_values(float total_price, float total_prize);

#endif