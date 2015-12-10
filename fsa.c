#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/fsa.h"

void	replace_char(char *str, char c, char rep)
{
  int	i;

  i = -1;
  while (str[++i])
    if (str[i] == c)
      str[i] = rep;
}

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

State	*fill_state(State *state, int nbState)
{
  FILE	*gFile;
  char	line[16];
  int	i;
  int	j;
  int	k;
  int	n;
  int	nextState;
  char	*fgetsValue;

  i = -1;
  if ((gFile = fopen(GRAMMAR, "r")) == NULL)
    return (NULL);
  fgetsValue = fgets(line, sizeof(*line) * sizeof(line), gFile);
  while (++i < nbState && fgetsValue != NULL)
    {
      n = -1;
      state[i].currState = atoi(line);
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
		  {
		    fclose(gFile);
		    free(fgetsValue);
		    return (NULL);
		  }
		state[i].next[n] = atoi(strndup(line + k, j - k));
		fgetsValue = fgets(line, sizeof(*line) * sizeof(line), gFile);
		nextState = atoi(line);
	      }
	    while (nextState == state[i].currState && fgetsValue != NULL);
    }
  fclose(gFile);
  return (state);
}

int     read_check_date(State *state, int nbState)
{
  char  date[MAX_DATE_LEN + 2] = {0};
  int   i;
  int   j;
  int   k;
  int   toState;

  system("clear");
  printf("Please enter a date: ");
  if (fgets(date, sizeof(date) * sizeof(*date), stdin) == NULL)
    return (-1);
  if (strcmp(date, "42\n") == 0)
    return (42);
  if (strcasecmp(date, "Mathieu\n") == 0)
    return (1337);
  if (strcmp(date, "\n") == 0)
    return (1);
  if (strchr(date, 95) != NULL)
    return (date - strchr(date, 95) - 2);
  replace_char(date, ' ', '_');
  i = 0;
  k = -1;
  while (date[++k])
    {
      j = -1;
      while (state[i].trans[++j] != date[k] && state[i].trans[j] != 0);
      if (state[i].trans[j] == 0)
	{
	  j = -1;
	  while (state[i].trans[++j] != '!' && state[i].trans[j] != 0);
	}
      if (state[i].trans[j] == '!' &&  date[k] == '\n')
	return (0);
      if (state[i].next[j] == 0)
	return (-k - 2);
      toState = state[i].next[j];
      i = -1;
      while (++i < nbState && state[i].currState != toState);
      if (i == nbState)
	return (-2);
    }
  return (-2);
}
