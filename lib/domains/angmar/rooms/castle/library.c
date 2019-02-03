#include "../../domain.h"

inherit "/std/room";

void setup(void) {
  add_area(AREA);
  add_area(CASTLE_AREA);
  set_short("The library");
  set_long("This is Angmar's library. Along the walls are shelves full of books, "
     + "papers, and magic scrolls. The entire room seems to emanate a dark, "
     + "chilling feeling, as if Angmar were still here in spirit. "
	  + "There is a magic wardrobe in the corner.");
  add_exit("east", CASTLE_ROOMS + "/magroom.c");

  add_item("shelves", "They hold what look like the collected works of Angmar's magic.");
  add_item("books", "The book you examine deals with the pitfalls of magical human mutation.");
  add_item("papers", "The paper seems to be thinner than normal parchment. Surely, magical.");

  set_objects(
     DIR + "/obj/notebook.c",
     DIR + "/obj/statue.c",
     DIR + "/obj/magic_wardrobe.c"
  );
}
