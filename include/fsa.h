#ifndef	_FSA_H_
# define _FSA_H_

# define GRAMMAR	"grammar/date"
# define MAX_DATE_LEN	20
# define MAX_TRANS	19

typedef	struct	state
{
  int		currState;
  char		trans[MAX_TRANS];
  int		next[MAX_TRANS];
}		State;

int	nb_state(const char *);
int	read_check_date(State *, int);
State	*fill_state(State *, int);

#endif /* !_FSA_H_ */
