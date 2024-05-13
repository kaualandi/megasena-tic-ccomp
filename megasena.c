// O objetivo do Projeto 1 é implementar um programa em C que simule apostas da Mega-Sena com base nas sete regras descritas no final da Seção 1. Para isso, o simulador deve atender os seguintes requisitos:
// 1. Exibir um menu para o apostador que simule as opções de um volante semelhante à Figura 1. Sugestão abaixo:
// 1.1. Solicitar a quantidade de dezenas QD que o apostador irá jogar nas suas apostas (esperar 6 <= QD <= 15 como resposta);
// 1.2. Em seguida, o menu deve perguntar quantas apostas manuais (QM) o apostador deseja realizar (esperar 0 <= QM <= 3 como resposta);
// 1.3. Caso o apostador queira realizar apostas manuais, o menu deverá solicitar que o usuário digite sua(s) aposta(s) (as seis dezenas) QM vezes. Não pode haver dezenas repetidas na aposta. Vale ressaltar também que cada dezena digitada deve ser maior ou igual a 1 e menor ou igual a 60. Cada aposta manual terá QD dezenas escolhidas pelo apostador na Etapa 1.1;
// 1.4. Em seguida, o menu deve perguntar ao apostador se ele deseja jogar Surpresinhas (é esperado um valor inteiro 0 <= QS <= 7). Caso QS seja maior que 0, o programa deve gerar aleatoriamente QS apostas contendo QD dezenas distintas, onde cada dezena escolhida deve ser maior ou igual a 1 e menor ou igual a 60.
// 1.5. Por fim, o menu deve perguntar ao apostador a quantidade de Teimosinhas QT que ele deseja escolher. Espera-se um inteiro QT = 0, QT = 2 ou QT = 8. Nesse caso, as apostas Manuais mais as Teimosinhas se mantêm fixas para os próximos QT concursos.
// 2. Após as escolhas das opções disponíveis no volante, o programa deve exibir ao apostador o valor total das apostas em reais, de acordo com a fórmula QT * (VD * (QM + QS)), sendo VD o valor do custo das dezenas informado na Tabela 2. O usuário deve concordar com o valor mostrado;
// 3. Em seguida, o programa realizará o concurso ao sortear 6 dezenas distintas e pertencentes ao intervalo [01, 60]. Após, o programa deverá exibir as dezenas sorteadas do Concurso N (onde N =1 caso QT = 0 ou 1 <= N <= QT) e, logo em seguida, cada aposta do apostador (Manuais + Surpresinhas). Para cada aposta exibida, deve ser exibido logo abaixo a quantidade de acertos em relação ao sorteio do concurso;
// 4. Caso o apostador tenha definido QT > 0, a Etapa 3 será repetida QT vezes. Ao final (independente do valor de QT), o programa deve exibir as apostas premiadas juntamente com o subtotal do prêmio. Por fim, o programa deve exibir ao usuário o valor total de todos os prêmios, juntamente com o valor da aposta para efeitos comparativos. Para calcular os valores dos prêmios, baseie-se nas Tabelas 2 e 3. A Tabela 3 contém as quantias monetárias ofertadas para a Quadra, Quina e Sena no Concurso 2705.

// tabela de valores
// Dezenas marcadas  Valor da aposta (R$)
// 6                 5,00
// 7                 35,00
// 8                 140,00
// 9                 420,00
// 10                1.050,00
// 11                2.310,00
// 12                4.620,00
// 13                8.580,00
// 14                15.015,00
// 15                25.025,00

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

typedef struct
{
  int dozens;
  float price;
} PriceDozens;

PriceDozens price_dozens[] = {
    {6, 5.00},
    {7, 35.00},
    {8, 140.00},
    {9, 420.00},
    {10, 1050.00},
    {11, 2310.00},
    {12, 4620.00},
    {13, 8580.00},
    {14, 15015.00},
    {15, 25025.00}};

#define QUADRA_VALUE 834.93
#define QUINA_VALUE 32797.02
#define SENA_VALUE 118265926.76

void print_wellcome()
{
  printf(" __  __                                  ____\n");
  printf("|  \\/  |   ___    __ _    __ _          / ___|    ___   _ __     __ _\n");
  printf("| |\\/| |  / _ \\  / _` |  / _` |  _____  \\___ \\   / _ \\ | '_ \\   / _` |\n");
  printf("| |  | | |  __/ | (_| | | (_| | |_____|  ___) | |  __/ | | | | | (_| |\n");
  printf("|_|  |_|  \\___|  \\__, |  \\__,_|         |____/   \\___| |_| |_|  \\__,_|\n");
  printf("                 |___/\n");
  printf("\n");
  printf("Bem-vindo ao simulador da Mega-Sena\n");
  printf("Iremos te auxiliar a fazer suas apostas\n");
  printf("\n");
}

void get_start()
{
  printf("Pressione ENTER para continuar...\n");
  getchar();
}

void get_dozens_quantity(int *dozens_quantity)
{
  printf("Quantas dezenas você quer apostar? O valor deve ser entre 6 e 15: ");
  scanf("%d", dozens_quantity);

  if ((*dozens_quantity < 6 || *dozens_quantity > 15))
  {
    printf("A quantidade de dezenas deve ser entre 6 e 15\n");
    get_dozens_quantity(dozens_quantity);
  }
}

void get_manual_bets_quantity(int *manual_bets_quantity)
{
  printf("Qual a quantidade de apostas manuais quer fazer? O valor deve ser entre 0 e 3: ");
  scanf("%d", manual_bets_quantity);

  if (*manual_bets_quantity < 0 || *manual_bets_quantity > 3)
  {
    printf("A quantidade de apostas manuais deve ser entre 0 e 3\n");
    get_manual_bets_quantity(manual_bets_quantity);
  }
}

int **allocate_manual_bets(int manual_bets_quantity, int dozens_quantity)
{
  int **manual_bets = (int **)malloc(manual_bets_quantity * sizeof(int *));
  for (int i = 0; i < manual_bets_quantity; i++)
  {
    manual_bets[i] = (int *)malloc(dozens_quantity * sizeof(int));
  }
  return manual_bets;
}

void get_manual_bets(int manual_bets_quantity, int dozens_quantity, int **manual_bets)
{
  if (manual_bets_quantity == 0)
  {
    printf("Então ta bom, sem apostas manuais, todas automáticas\n\n");
    return;
  }

  for (int i = 0; i < manual_bets_quantity; i++)
  {
    bool has_repeated = false;
    printf("Digite a aposta %d (%d dezenas distintas, divididas por ENTER): ", i + 1, dozens_quantity);
    for (int j = 0; j < dozens_quantity; j++)
    {
      scanf("%d", &manual_bets[i][j]);
      if (manual_bets[i][j] < 1 || manual_bets[i][j] > 60)
      {
        printf("A dezena deve ser entre 1 e 60\n");
        j--;
      }
    }

    for (int j = 0; j < dozens_quantity; j++)
    {
      for (int k = j + 1; k < dozens_quantity; k++)
      {
        if (manual_bets[i][j] == manual_bets[i][k])
        {
          has_repeated = true;
          break;
        }
      }
      if (has_repeated)
        break;
    }

    if (has_repeated)
    {
      printf("Não pode haver dezenas repetidas na aposta\n");
      i--;
    }
  }

  printf("Perfeito, suas apostas manuais foram registradas\n\n");
}

void get_surprises_quantity(int *surprises_quantity)
{
  printf("Quer jogar Surpresinhas? (S/N): ");
  char answer;
  scanf(" %c", &answer);

  if (answer == 'S' || answer == 's')
  {
    printf("Quantas Surpresinhas quer jogar? O valor deve ser entre 1 e 7: ");
    scanf("%d", surprises_quantity);

    if (*surprises_quantity < 1 || *surprises_quantity > 7)
    {
      printf("A quantidade de Surpresinhas deve ser entre 1 e 7\n");
      get_surprises_quantity(surprises_quantity);
      return;
    }

    printf("Perfeito, suas Surpresinhas foram registradas\n\n");
    return;
  }

  if (answer == 'N' || answer == 'n')
  {
    *surprises_quantity = 0;
    printf("Então ta bom, sem Surpresinhas\n\n");
    return;
  }

  printf("Você não digitou uma opção válida, digite somente S ou N\n");
  get_surprises_quantity(surprises_quantity);
}

void get_stubborny_quantity(int *stubborny_quantity)
{
  printf("Quer jogar Teimosinhas? (S/N): ");
  char answer;
  scanf(" %c", &answer);

  if (answer == 'S' || answer == 's')
  {
    printf("Quantas Teimosinhas quer jogar? O valor deve ser 2 ou 8: ");
    scanf("%d", stubborny_quantity);

    if (*stubborny_quantity != 0 && *stubborny_quantity != 2 && *stubborny_quantity != 8)
    {
      printf("A quantidade de Teimosinhas deve ser 1, 2 ou 8\n");
      get_stubborny_quantity(stubborny_quantity);
      return;
    }

    printf("Perfeito, suas Teimosinhas foram registradas\n\n");
    return;
  }

  if (answer == 'N' || answer == 'n')
  {
    *stubborny_quantity = 1;
    printf("Então ta bom, sem Teimosinhas\n\n");
    return;
  }

  printf("Você não digitou uma opção válida, digite somente S ou N\n");
  get_stubborny_quantity(stubborny_quantity);
}

void generate_random_bet(int dozens_quantity, int *random_bets)
{
  bool has_repeated = false;
  for (int j = 0; j < dozens_quantity; j++)
  {
    random_bets[j] = rand() % 60 + 1;
  }

  for (int j = 0; j < dozens_quantity; j++)
  {
    for (int k = j + 1; k < dozens_quantity; k++)
    {
      if (random_bets[j] == random_bets[k])
      {
        has_repeated = true;
        break;
      }
    }
    if (has_repeated)
      break;
  }

  if (has_repeated)
  {
    generate_random_bet(dozens_quantity, random_bets);
  }
}

void generate_surprises_bets(int surprises_quantity, int dozens_quantity, int **random_bets)
{
  for (int i = 0; i < surprises_quantity; i++)
  {
    generate_random_bet(dozens_quantity, random_bets[i]);
  }
}

int **allocate_memory(int surprises_quantity, int dozens_quantity)
{
  int **random_bets = malloc(surprises_quantity * sizeof(int *));
  for (int i = 0; i < surprises_quantity; i++)
  {
    random_bets[i] = malloc(dozens_quantity * sizeof(int));
  }
  return random_bets;
}

void free_memory(int **bets, int surprises_quantity)
{
  for (int i = 0; i < surprises_quantity; i++)
  {
    free(bets[i]);
  }
  free(bets);
}

void print_bets(int dozens_quantity, int **manual_bets, int **random_bets, int manual_bets_quantity, int surprises_quantity)
{
  printf("Vamos revisar suas apostas...\n");
  if (manual_bets_quantity == 0)
  {
    printf("Você não fez apostas manuais\n");
  }
  else
  {
    printf("Apostas manuais:\n");
  }

  for (int i = 0; i < manual_bets_quantity; i++)
  {
    printf("Aposta %d: ", i + 1);
    for (int j = 0; j < dozens_quantity; j++)
    {
      printf("%d ", manual_bets[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  if (surprises_quantity == 0)
  {
    printf("Você não fez Surpresinhas\n");
  }
  else
  {
    printf("Surpresinhas:\n");
  }
  for (int i = 0; i < surprises_quantity; i++)
  {
    printf("Surpresinha %d: ", i + 1);
    for (int j = 0; j < dozens_quantity; j++)
    {
      printf("%d ", random_bets[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int calc_price(int dozens_quantity, int manual_bets_quantity, int surprises_quantity, int stubborny_quantity)
{
  float price = stubborny_quantity * (price_dozens[dozens_quantity - 6].price * (manual_bets_quantity + surprises_quantity));
  printf("O valor total das apostas é de R$ %.2f\n", price);
  return price;
}

int confirm_price()
{
  printf("Tudo certo, podemos prosseguir com a aposta? (S/N): ");
  char answer;
  scanf(" %c", &answer);

  if (answer == 'S' || answer == 's')
  {
    printf("Perfeito, vamos ao sorteio\n\n");
    return 1;
  }

  if (answer == 'N' || answer == 'n')
  {
    printf("Vamos ficar por aqui então, espero te ver em breve!\n");
    return 0;
  }

  printf("Você não digitou uma opção válida, digite somente S ou N\n");
  confirm_price();
  return 0;
}

int win_type(int hits)
{
  if (hits == 6)
  {
    printf("Parabéns, você ganhou a Sena!\n");
    return 6;
  }
  if (hits == 5)
  {
    printf("Parabéns, você ganhou a Quina!\n");
    return 5;
  }
  if (hits == 4)
  {
    printf("Parabéns, você ganhou a Quadra!\n");
    return 4;
  }
  return 0;
}

void value_4_hits(int dozens_quantity, int *prize_qtd)
{
  int quadra_values[10] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55};
  prize_qtd[0] = quadra_values[dozens_quantity - 6];
  prize_qtd[1] = 0;
  prize_qtd[2] = 0;
}

void value_5_hits(int dozens_quantity, int *prize_qtd)
{
  int quadra_values[10] = {0, 5, 15, 30, 50, 75, 105, 140, 180, 225};
  int quina_values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  prize_qtd[0] = quadra_values[dozens_quantity - 6];
  prize_qtd[1] = quina_values[dozens_quantity - 6];
  prize_qtd[2] = 0;
}

void value_6_hits(int dozens_quantity, int *prize_qtd)
{
  int quadra_values[10] = {0, 0, 15, 45, 90, 150, 225, 315, 420, 540};
  int quina_values[10] = {0, 6, 12, 18, 24, 30, 36, 42, 48, 54};
  prize_qtd[0] = quadra_values[dozens_quantity - 6];
  prize_qtd[1] = quina_values[dozens_quantity - 6];
  prize_qtd[2] = 1;
}

float value_hit_prize(int dozens_quantity, int hits)
{
  int prize_qtd[3];
  if (hits == 4)
  {
    value_4_hits(dozens_quantity, prize_qtd);
  }

  if (hits == 5)
  {
    value_5_hits(dozens_quantity, prize_qtd);
  }

  if (hits == 6)
  {
    value_6_hits(dozens_quantity, prize_qtd);
  }

  if (hits == 4 || hits == 5 || hits == 6)
  {
    float quadra_value = prize_qtd[0] * QUADRA_VALUE;
    float quina_value = prize_qtd[1] * QUINA_VALUE;
    float sena_value = prize_qtd[2] * SENA_VALUE;

    return quadra_value + quina_value + sena_value;
  }
  return 0;
}

int generate_competitions(int stubborny_quantity, int dozens_quantity, int manual_bets_quantity, int surprises_quantity, int **manual_bets, int **random_bets)
{
  float total_prize = 0;

  for (int i = 0; i < stubborny_quantity; i++)
  {
    printf("========== Concurso 000%d ==========\n", i + 1);
    printf("Dezenas sorteadas: ");
    int *sorted_dozens = malloc(6 * sizeof(int));
    generate_random_bet(6, sorted_dozens);
    int total_hits = 0;
    float prize = 0;

    for (int j = 0; j < 6; j++)
    {
      printf("%d ", sorted_dozens[j]);
    }
    printf("\n");

    for (int j = 0; j < manual_bets_quantity; j++)
    {
      int hits = 0;
      for (int k = 0; k < dozens_quantity; k++)
      {
        for (int l = 0; l < 6; l++)
        {
          if (manual_bets[j][k] == sorted_dozens[l])
          {
            if (hits >= 4)
              hits++;
          }
        }
      }
      printf("Aposta manual %d: %d/6 acertos\n", j + 1, hits);
      total_hits += win_type(hits);
    }

    for (int j = 0; j < surprises_quantity; j++)
    {
      int hits = 0;
      for (int k = 0; k < dozens_quantity; k++)
      {
        for (int l = 0; l < 6; l++)
        {
          if (random_bets[j][k] == sorted_dozens[l])
          {
            hits++;
          }
        }
      }
      printf("Surpresinha %d: %d/6 acertos\n", j + 1, hits);
      total_hits += win_type(hits);
    }

    prize = value_hit_prize(dozens_quantity, total_hits);
    total_prize += prize;
    printf("\nSub-total do premio: R$ %.2f\n", prize);

    free(sorted_dozens);
    printf("\n");
  }

  return total_prize;
}

void show_total_values(float total_price, float total_prize)
{
  printf("O valor total dos prêmios foi de R$ %.2f\n\n", total_prize);

  float liquid_value = total_prize - total_price;
  if (liquid_value < 0)
  {
    printf("Infelizmente você teve um prejuízo de R$ %.2f\n", liquid_value * -1);
    return;
  }

  printf("Restando um valor líquido de R$ %.2f\n", liquid_value);
  printf("\nObrigado por jogar!");
}