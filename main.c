#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/fsa.h"

int	nb_state(const char *grammar)
{
  FILE	*gFile;
  int	nb;
  int	st;
  int	prev_st;
  char	line[16];

  nb = 0;
  if ((gFile = fopen(grammar, "r")) == NULL)
    return (-1);
  if (fgets(line, sizeof(*line) * sizeof(line), gFile) != NULL)
    {
      st = atoi(line);
      prev_st = st;
      nb++;
    }
  while (fgets(line, sizeof(*line) * sizeof(line), gFile) != NULL)
    {
      st = atoi(line);
      if (st != prev_st)
	nb++;
      prev_st = st;
    }
  fclose(gFile);
  return (nb);
}

void	print_int_array(int *array, int size)
{
  int	i = -1;
  while (++i < size-1)
    printf("%d,", array[i]);
  printf("%d\n", array[i]);
}

State	*fill_state(State *state, int nbState)
{
  FILE	*gFile;
  char	line[16];
  int	i;
  int	j;
  int	k;
  int	n;
  int	prevState;
  char	*fgetsValue;

  i = -1;
  if ((gFile = fopen(GRAMMAR, "r")) == NULL)
    return (NULL);
  fgetsValue = fgets(line, sizeof(*line) * sizeof(line), gFile);
  while (++i < nbState && fgetsValue != NULL)
    {
      n = -1;
      state[i].currState = atoi(line);
      /* printf("STATE:\n\tcurrState = %d\n", state[i].currState); */
      prevState = state[i].currState;
      do
	{
	  n++;
	  j = -1;
	  while (line[++j] && line[j] != ' ');
	  k = j + 1;
	  state[i].trans[n] = line[k];
	  while (line[++j] && line[j] != ' ');
	  k = j + 1;
	  while (line[++j] && line[j] != '\n');
	  if (strndup(line + k, j - k) == NULL)
	    return (NULL);
	  state[i].next[n] = atoi(strndup(line + k, j - k));
	  fgetsValue = fgets(line, sizeof(*line) * sizeof(line), gFile);
	  state[i].currState = atoi(line);
	}
      while (prevState == state[i].currState && fgetsValue != NULL);
      /* printf("\ttrans: %s\n\t", state[i].trans); */
      /* print_int_array(state[i].next, MAX_TRANS); */
    }
  fclose(gFile);
  return (state);
}

int	read_check_date(State *state)
{
  char	date[MAX_DATE_LEN + 2] = {0};
  int	i;
  int	j;
  int	toState;
  int	currState;

  i = -1;
  system("clear");
  printf("Please enter a date: ");
  if (fgets(date, sizeof(date) * sizeof(*date), stdin) == NULL)
    return (-1);
  while (*date)
    {
      j = -1;
      while (state[i].trans[++j] != *date && state[i].trans[j] != 0);
      if (state[i].trans[j] == 0)
	return (-2);
    }
  return (0);
}

int	main()
{
  State	*state;
  int	nb;

  if ((nb = nb_state(GRAMMAR)) == -1)
    return (-1);
  if ((state = calloc(nb, sizeof(*state))) == NULL)
    return (-1);
  if ((state = fill_state(state, nb)) == NULL)
    return (-1);
  if (read_check_date(state) == -1)
    return (-1);
  return (0);
}
