#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "megasena.h"

int main()
{
  setlocale(LC_ALL, "pt_BR.UTF-8");

  int dozens_quantity, manual_bets_quantity, surprises_quantity, stubborny_quantity;
  float total_price, total_prize;

  print_wellcome();
  get_start();
  get_dozens_quantity(&dozens_quantity);
  get_manual_bets_quantity(&manual_bets_quantity);

  int **manual_bets = allocate_manual_bets(manual_bets_quantity, dozens_quantity);
  get_manual_bets(manual_bets_quantity, dozens_quantity, manual_bets);

  get_surprises_quantity(&surprises_quantity);

  get_stubborny_quantity(&stubborny_quantity);

  int **random_bets = allocate_memory(surprises_quantity, dozens_quantity);

  generate_surprises_bets(surprises_quantity, dozens_quantity, random_bets);

  print_bets(dozens_quantity, manual_bets, random_bets, manual_bets_quantity, surprises_quantity);

  total_price = calc_price(dozens_quantity, manual_bets_quantity, surprises_quantity, stubborny_quantity);

  if (confirm_price() == 0)
  {
    free_memory(manual_bets, manual_bets_quantity);
    free_memory(random_bets, surprises_quantity);
    return 0;
  }

  total_prize = generate_competitions(stubborny_quantity, dozens_quantity, manual_bets_quantity, surprises_quantity, manual_bets, random_bets);

  show_total_values(total_price, total_prize);

  free_memory(manual_bets, manual_bets_quantity);
  free_memory(random_bets, surprises_quantity);
  return 0;
}
