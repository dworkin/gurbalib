#include "../../domain.h"

inherit "/std/room";

int smell_cmd(string str) {
    write("You sniff the air, but choke on the dust swirling around you. ");
    return 1;
}

void setup(void) {
    add_area(AREA);
    add_area(CASTLE_AREA);
    set_short("Corridor");
    set_long("You are in a corridor deep under the ancient castle. The air "
        + "in here hasn't been breathed for hundreds of years. You "
        + "cough and sneeze from the dust in the air. ");

    add_exit("west", CASTLE_ROOMS + "/downstairs");
    add_exit("east", CASTLE_ROOMS + "/empty");
    add_exit("south", CASTLE_ROOMS + "/dungeons");

    add_item("corridor", "The corridor is lined with black flagstones");
    add_item("flagstones", "The stones are just there as part of the wall supports");
    add_item("supports", "They are behind the walls. You cannot see them");
    add_item("walls", "They seem sturdy and sound");
    add_item("dust", "There is a thick layer of dust on the ground");
    add_item("ground", "You see few footprints in the dust");
    add_item("footprints", "You see your own, and a strange wave pattern");
    add_item("pattern", "It looks like someone dragged a cloth lightly over the dust");

    add_action("smell_cmd", "smell");
}
