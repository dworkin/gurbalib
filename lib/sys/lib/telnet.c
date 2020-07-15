/*
 * Telnet reference implementation in LPC, closely following DGD.
 *
 * The TELOPT_SGA hacks are not included because no MUD clients are known
 * to support it, either.
 * Note that DGD is very particular about what it supports, deliberately
 * not following the telnet standard because doing so would break compatibility
 * with some clients.  TELOPT_ECHO, TELOPT_TM and TELOPT_LINEMODE handling in
 * this code should probably not be changed.
 */

#include <status.h>
#include <type.h>
#include <telnet.h>

/*
 * Gurba-specific
 */
#define TELNET_PARSER           TELNET_D        /* telnet parser daemon */

static void _receive_message(string str);       /* called with telnet input */


private string buffer;          /* partial line */
private string partial;         /* partial telnet command sequence */
private int echo;               /* echo input (off for passwords) */

/*
 * initialize telnet layer
 */
static void open() {
    buffer = "";
    partial = "";
    echo = TRUE;
    ::send_message(IAC + WONT + TELOPT_ECHO + IAC + DO + TELOPT_LINEMODE);
}

/*
 * called by the higher layer to send telnet commands
 */
static void send(string str) {
    ::send_message(str);
}

/*
 * send_message() override to handle IAC and newlines in output
 */
static void send_message(mixed arg) {
    switch (typeof(arg)) {
    case T_INT:
        if (echo != !!arg) {
            echo = !echo;
            ::send_message(IAC + ((echo) ? WONT : WILL) + TELOPT_ECHO);
        }
        break;

    case T_STRING:
        arg = implode(explode(IAC + arg + IAC, IAC), IAC + IAC);
        arg = implode(explode("\n" + arg + "\n", "\n"), "\r\n");
        ::send_message(arg);
        break;

    default:
        error("Bad argument 1 for function send_message");
    }
}

/*
 * override telnet_do(), telnet_dont(), telnet_will(), telnet_wont() and
 * telnet_subnegotiation() in higher level code to implement new options
 */

static void telnet_do(int option) {
    if (option == TELOPT_TM[0]) {
        ::send_message(IAC + WONT + TELOPT_TM);
    }
}

static void telnet_dont(int option) {
}

static void telnet_will(int option) {
    if (option == TELOPT_LINEMODE[0]) {
        ::send_message(IAC + SB + TELOPT_LINEMODE + LM_MODE + MODE_EDIT +
                       IAC + SE);
    }
}

static void telnet_wont(int option) {
}

static void telnet_subnegotiation(string subnegotiation) {
}

/*
 * Handle telnet commands in input.  Break up the remainder in lines, handle
 * backspaces, and pass each line back to the higher level.
 */
static void receive(mixed tls, string str) {
    string *strings, head, pre;
    int i, len;
    string rc;

    /* find telnet commands in input */
    /* stop jerks from running cat /dev/urandom | nc mudname 4000 and crashing */
    rc = catch(({ strings, partial }) = TELNET_PARSER->parse_telnet(partial + str));
    if (rc) {
       destruct_object(this_player());
    }

    for (i = 0; i < sizeof(strings); i++) {
        /*
         * each string can start with a telnet command
         */
        str = strings[i];
        if (str[0] == IAC[0]) {
            switch (str[1]) {
            case IAC[0]:
                buffer += IAC;
                break;

            case DO[0]:
                telnet_do(str[2]);
                break;

            case DONT[0]:
                telnet_dont(str[2]);
                break;

            case WILL[0]:
                telnet_will(str[2]);
                break;

            case WONT[0]:
                telnet_wont(str[2]);
                break;

            case SB[0]:
                telnet_subnegotiation(str[2 .. strlen(str) - 3]);
                break;

            default:
                call_other(this_object(), "telnet_" + str[1]);
                break;
            }
        } else {
            /* normal input */
            buffer += str;
            while (sscanf(buffer, "%s\r\n%s", str, buffer) != 0 ||
                   sscanf(buffer, "%s\n%s", str, buffer) != 0) {
                while (sscanf(str, "%s\b%s", head, str) != 0) {
                    while (sscanf(head, "%s\x7f%s", pre, head) != 0) {
                        len = strlen(pre);
                        if (len != 0) {
                            head = pre[0 .. len - 2] + head;
                        }
                    }
                    len = strlen(head);
                    if (len != 0) {
                        str = head[0 .. len - 2] + str;
                    }
                }
                while (sscanf(str, "%s\x7f%s", head, str) != 0) {
                    len = strlen(head);
                    if (len != 0) {
                        str = head[0 .. len - 2] + str;
                    }
                }

                _receive_message(str);
            }
        }
    }
}

static void telnet_246() {      /* AYT */
    ::send_message("\r\n[" + status()[ST_VERSION] + "]\r\n");
}

static void telnet_244() {      /* IP */
    ::send_message("\x7f");
}

static void telnet_243() {      /* BREAK */
    ::send_message("\x1c");
}
