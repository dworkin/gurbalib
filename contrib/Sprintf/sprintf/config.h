# ifndef _CONFIG_H_
# define _CONFIG_H_

# include <limits.h>

# undef  __CLOSE_TO_C__      /* Define when putting output in first argument. */
# define __UPPER_CASE__      /* Define if upper_case is s/k/efun ().          */
# define __FLOATS__          /* Define if float conversions are wanted.       */
# define __TIME_CONVERSION__ /* Define if time conversions are wanted.        */
# define __TIME_ZONE__       /* Define for @Z conversion (timezone)           */

# define BASE  10         /* Base in which integers are presented by default. */

# define FLT_PRECISION 6  /* Default precision for floats.                    */

# endif
