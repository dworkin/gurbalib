/*
 * prepends an object in front of the head of a list, 
 * a member or the sentinel for the list must be provided.
 *
 */

int list_prepend(string list, object member) {
  member = member->list_sentinel(list);

  if(!member) {
    return 0;
  }

  member = member->list_next(list);

  if(member) {
    return list_insert( list, member );
  }
}
