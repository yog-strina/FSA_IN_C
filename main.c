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

void	replace_char(char *str, char c, char rep)
{
  int	i;

  i = -1;
  while (str[++i])
    if (str[i] == c)
      str[i] = rep;
}

int	read_check_date(State *state, int nbState)
{
  char	date[MAX_DATE_LEN + 2] = {0};
  int	i;
  int	j;
  int	k;
  int	toState;
  int	currState;

  system("clear");
  printf("Please enter a date: ");
  if (fgets(date, sizeof(date) * sizeof(*date), stdin) == NULL)
    return (-1);
  replace_char(date, '_', ' ');
  i = 0;
  k = -1;
  while (date[++k])
    {
      j = -1;
      while (state[i].trans[++j] != date[k] && state[i].trans[j] != 0);
      if (state[i].trans[j] == 0)
	return (-2);
      if (state[i].trans[j] == '!' &&  date[k + 1] != 0)
	return (-2);
      toState = state[i].next[j];
      i = -1;
      while (++i < nbState && state[i].currState != toState);
      if (i == nbState)
	return (-2);
    }
  return (0);
}

int	main()
{
  State	*state;
  int	nbState;
  int	flag;

  if ((nbState = nb_state(GRAMMAR)) == -1)
    return (-1);
  if ((state = calloc(nbState, sizeof(*state))) == NULL)
    return (-1);
  if ((state = fill_state(state, nbState)) == NULL)
    return (-1);
  if ((flag = read_check_date(state, nbState)) == -1)
    return (-1);
  else if (flag == -2)
    printf("Bad date\n");
  else
    printf("Good date\n");
  return (0);
}
