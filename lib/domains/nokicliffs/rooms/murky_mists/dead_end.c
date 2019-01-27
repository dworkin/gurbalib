#include "../../domain.h"

inherit DIR + "/lib/room";

#define SEARCHING_INTERVAL 1
#define SEARCHING_DELAY_INTERVAL 10

static object demon_croc;
static object gem;
static object searcher;
static int search_handle;
static int search_interval_handle;

void tell_room(object originator, string str, varargs mixed obj ...) {
   if (str == "Ash to ash, dust to dust.") {
      gem = this_object()->present("gem");
      if (gem) {
	      gem->move(NOKICLIFFS_VOID);
      }
   }

   ::tell_room(originator, str, obj);
}

int delay_searching(void) {
   remove_call_out(search_interval_handle);
   search_interval_handle = 0;

   return 1;
}

int summon_demon_croc(void) {
   remove_call_out(search_handle);
   search_handle = 0;

   if (nilp(searcher) || !present(searcher->query_name())) {
      searcher = nil;

      return 0;
   }

   searcher = nil;

   if (!demon_croc) {
      demon_croc = clone_object(DIR + "/monsters/demon_croc.c");
      demon_croc->setup();
      demon_croc->move(this_object());

      TELL_ROOM(demon_croc, "Something big and evil splashes violently " +
         "about!");
   }

   return 1;
}

private int find_demon_croc(void) {
   if (nilp(searcher) || !present(searcher->query_name())) {
      remove_call_out(search_handle);
      search_handle = 0;
      searcher = nil;

      return 0;
   }

   if (!search_interval_handle && nilp(demon_croc)) {
      searcher->targeted_action("$N $vcontinue to fish around...", searcher);
      searcher->message_orig("What's that?!\n");
      search_handle = call_out("summon_demon_croc", SEARCHING_INTERVAL);

      return 1;
   }

   return 0;
}

private int find_gems(object *gems, object searcher) {
   int i;

   for (i = 0; i < sizeof(gems); i++) {
      gems[i]->move(searcher);
   }

   searcher->targeted_action("$N $vfind something.", searcher);
   searcher->message_orig("Check your pockets.\n");

   if (!search_interval_handle) {
      search_interval_handle = call_out("delay_searching",
         SEARCHING_DELAY_INTERVAL);
   }
}

int find_something(void) {
   int i, sz;
   object the_void;
   object *inv, *gems;

   if (nilp(searcher) || !present(searcher->query_name())) {
      return 0;
   }

   remove_call_out(search_handle);
   search_handle = 0;

   the_void = find_object(implode(explode(NOKICLIFFS_VOID, ".c"), ""));
   if (the_void) {
      inv = the_void->query_inventory();
      gems = allocate(sizeof(inv));

      for (i = 0; i < sizeof(inv); i++) {
	      if (inv[i]->is_id("gem")) {
	         gems[i] = inv[i];
	      }
      }

      gems -= ({ nil });
   } else {
      gems = ({ });
   }


   if (sizeof(gems) > 0 && searcher != nil && present(searcher->query_name())) {
      find_gems(gems, searcher);
   } else {
      find_demon_croc();
   }

   return 1;
}

int do_search(void) {
   string fish_around;

   fish_around = "$N $vfish around in the murky swamp water.";

   if (demon_croc) {
      write("Not with the demon croc about!");
      return 1;
   }

   if (present("corpse")) {
      write("Try looking at the corpse instead.");
      return 1;
   }

   searcher = this_player();
   this_player()->targeted_action(fish_around, this_player());
   search_handle = call_out("find_something", SEARCHING_INTERVAL + 1);

   return 1;
}

void setup(void) {
   set_short("Murky mists dead end");
   set_long("The swamp is deep and the mysterious mist, " +
      "as thick as ever, obscures even the sharpest eyes. " +
      "The depth of the swamp and the twisting mangroves " +
      "prevent further exploration of the area. But there " +
      "are other things on your mind, such as what lies " +
      "beneath.");

   set_exits(([
      "south" : DIR + "/rooms/murky_mists/before_dead_end.c"
   ]));

   searcher = nil;
   search_handle = 0;
   search_interval_handle = 0;
}
