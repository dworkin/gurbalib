string *blocks;
string block_action;

int is_blocking(string dir) {
   int i, max;

   if (blocks) {
      max = sizeof(blocks);
      for (i = 0; i < max; i++) {
         if (blocks[i] == dir) {
            return 1;
         }
      }
   }
   return 0;
}

int query_blocking(string dir) {
   return is_blocking(dir);
}

void add_block(string exit) {
   if (!blocks) {
      blocks = ( { } );
   }
   blocks -= ( { exit } );
   blocks += ( { exit } );
   if (!block_action) {
      block_action = "$N $vstop $t from going $o. \n";
   }
}

void set_block_action(string action) {
   block_action = action;
}

string query_block_action(void) {
   return block_action;
}
