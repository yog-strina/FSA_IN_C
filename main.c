#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "include/fsa.h"

void	disp_ascii(int flag)
{
  FILE	*f;
  char	buf[2246] = {0};

  if (flag == 1)
    if ((f = fopen("grammar/.answer", "r")) == NULL)
      return ;
  if (flag == 2)
    if ((f = fopen("grammar/.mathieu", "r")) == NULL)
	return ;
  fread(buf, sizeof(buf), sizeof(*buf), f);
  printf("%s\n", buf);
}

int	main()
{
  State	*state;
  int	nbState;
  int	flag;

  state = NULL;
  if ((nbState = nb_state(GRAMMAR)) == -1)
    return (-1);
  if ((state = calloc(nbState, sizeof(*state))) == NULL)
    return (-1);
  if ((state = fill_state(state, nbState)) == NULL)
    return (-1);
  while ("Mathieu iz da best")
    {
      if ((flag = read_check_date(state, nbState)) != 1)
	{
	  if (flag == -1)
	    return (-1);
	  else if (flag == 42)
	    disp_ascii(1);
	  else if (flag == 1337)
	    disp_ascii(2);
	  else if (flag <= -2)
	    printf("\nBad date, error on character number %d\n", -flag - 1);
	  else
	    printf("\nGood date\n");
	  write(1, "Press enter to continue\n", 25);
	  read(1, state, 1);
	}
      fflush(stdin);
    }
  free(state);
  return (0);
}
