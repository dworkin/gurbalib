inherit "/sys/lib/modules/m_cmds";

#include <type.h>

static string *que;
static int time;
static int actionssize;
static string *actions;

void do_respond(void) {
   do_game_command(que[0]);
   que = que[1..];
}

void respond(string message) {
   if (!que) {
      que = ( { } );
   }
   que += ( { message } );

   call_out("do_respond", random(3));
}

void do_action(void) {
   respond(actions[random(actionssize)]);
   call_out("do_action", time);
}

void set_actions(int t, string * act) {
   time = t;
   actions = act;
   actionssize = sizeof(actions);

   call_out("do_action", time);
}
