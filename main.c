#include <stdlib.h>
#include <stdio.h>
#include "include/fsa.h"

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
  if ((flag = read_check_date(state, nbState)) == -1)
    return (-1);
  else if (flag <= -2)
    printf("\nBad date, error on character number %d\n", -flag - 1);
  else
    printf("\nGood date\n");
  free(state);
  return (0);
}
