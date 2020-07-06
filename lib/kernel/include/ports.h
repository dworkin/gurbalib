#include <status.h>

#define LOGIN_PORT  (status()[ST_BINARYPORTS][0])
#define FTP_PORT    (LOGIN_PORT + 1)
#define I3_TCP_PORT (LOGIN_PORT + 2)
#define I3_UDP_PORT (LOGIN_PORT + 3)

# define MODE_DISCONNECT	0
# define MODE_NOECHO		1	/* telnet */
# define MODE_ECHO		2	/* telnet */
# define MODE_LINE		2	/* binary */
# define MODE_RAW		3	/* binary */
# define MODE_NOCHANGE		4	/* telnet + binary */
# define MODE_UNBLOCK		5	/* unblock to previous mode */
# define MODE_BLOCK		6	/* block input */
