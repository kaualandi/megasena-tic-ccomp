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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void get_manual_bets(int manual_bets_quantity, int dozens_quantity, int *manual_bets)
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
      scanf("%d", &manual_bets[j]);
      if (manual_bets[j] < 1 || manual_bets[j] > 60)
      {
        printf("A dezena deve ser entre 1 e 60\n");
        j--;
      }
    }

    for (int j = 0; j < dozens_quantity; j++)
    {
      for (int k = j + 1; k < 6; k++)
      {
        if (manual_bets[j] == manual_bets[k])
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
      printf("A quantidade de Teimosinhas deve ser 0, 2 ou 8\n");
      get_stubborny_quantity(stubborny_quantity);
      return;
    }

    printf("Perfeito, suas Teimosinhas foram registradas\n\n");
    return;
  }

  if (answer == 'N' || answer == 'n')
  {
    *stubborny_quantity = 0;
    printf("Então ta bom, sem Teimosinhas\n\n");
    return;
  }

  printf("Você não digitou uma opção válida, digite somente S ou N\n");
  get_stubborny_quantity(stubborny_quantity);
}