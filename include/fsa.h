#ifndef	_FSA_H_
# define _FSA_H_

# define GRAMMAR	"grammar/date"
# define MAX_DATE_LEN	19
# define MAX_TRANS	19

typedef	struct	state
{
  int		currState;
  char		trans[MAX_TRANS];
  int		next[MAX_TRANS];
}		State;

#endif /* !_FSA_H_ */
