#include "../domain.h"

inherit "/std/room";

int errors, valid;
string *output;

int test_area(void) {
   string *areas;

   areas = query_areas();
   if (!areas) {
      errors += 1;
      output += ({ "Error in query_areas() when areas nil" });
   } else {
      valid += 1;
   }

   if (query_in_area("test")) {
      errors += 1;
      output += ({ "Error in query_in_area(\"test\") invalid area" });
   } else {
      valid += 1;
   }

   add_area("test");

   if (!query_in_area("test")) {
      errors += 1;
      output += ({ "Error in query_in_area(\"test\") valid area" });
   } else {
      valid += 1;
   }
}

void setup(void) {
   output = ({ "" });
   errors = 0;
   valid = 0;

   test_area();

   set_short("Test room 1");
   set_long("Welcome to the testing area.");

   set_exits(([
      "out" : STARTING_ROOM,
   ]));
}

string query_long(void) {
   int x, max;

   write("Welcome to the test room1.\n");
   write("Report:\n");
   write("\t" + valid + " Successful tests.\n");
   write("\t" + errors + " Failed tests.\n");
   max = sizeof(output);
   for (x = 0; x < max; x++) {
      write(output[x] + "\n");
   }
}

