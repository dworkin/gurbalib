#include "../../../../domain.h"

int affix_rescue_effect(string id, string on, object player) {
   player->simple_action("$N $vtouch the " + on +
      "on $p " + id + " and $vcall for immediate " +
      "evacuation from the area and $vdisappear in a puff " +
      "of emerald green smoke.", player);
   player->move(NOCLIFFS_TOWN_SQUARE_MIDDLE);
   player->simple_action("$N $vappear in a puff of " +
         "emerald green smoke.", player);
   return 1;
}
