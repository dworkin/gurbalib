string *banes;

void set_banes(string *new_banes) {
   banes = new_banes;
}

void add_bane(string bane) {
   if (!banes) {
      banes = ({ });
   }
   banes += ({ bane });
   banes = uniq_array(banes);
}

string *query_banes(void) {
   if (!banes) {
      banes = ({ });
   }
   return banes;
}

int query_baneful(string *test_banes) {
   if (!banes) {
      banes = ({ });
   }

   return sizeof(set_intersection(banes, test_banes));
}

