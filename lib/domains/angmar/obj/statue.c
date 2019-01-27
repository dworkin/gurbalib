#include "../domain.h"

inherit "/std/object";

void setup(void) {
  set_id("stone statue");
  add_id("statue");
  set_short("A stone statue");
  set_long("A stone status of an elf. It is very well made. It almost looks alive...");
  set_gettable(0);
}

void revive(void) {
  object elf;

  this_object()->query_environment()->tell_room(this_object(),
        "The statue begins to glow!");

  elf = clone_object(DIR + "/monsters/elf_warrior.c");
  elf->setup();
  elf->move(this_object()->query_environment());

  this_object()->query_environment()->tell_room(this_object(),
        "The status has suddenly transformed into an elf warrior!");

  this_object()->destruct();
}
