int member_map(mixed item, mapping map) {
   mixed *arr;

   argcheck(map, 2, "mapping");

   arr = map_indices(map);
   if (member_array(item, arr) > -1) {
      return 1;
   }
   arr = map_values(map);
   if (member_array(item, arr) > -1) {
      return 1;
   }

   return 0;

}
