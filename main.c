#include <stdio.h>
#include <stdlib.h>
#include "megasena.h"

int main()
{
  int dozens_quantity, manual_bets_quantity, surprises_quantity, stubborny_quantity;

  print_wellcome();
  get_start();
  get_dozens_quantity(&dozens_quantity);
  get_manual_bets_quantity(&manual_bets_quantity);

  int manual_bets[manual_bets_quantity][dozens_quantity];
  get_manual_bets(manual_bets_quantity, dozens_quantity, &manual_bets);

  get_surprises_quantity(&surprises_quantity);

  get_stubborny_quantity(&stubborny_quantity);

  return 0;
}
