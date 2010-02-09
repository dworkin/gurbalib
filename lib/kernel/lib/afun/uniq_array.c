/*
 * Thingol, 10/25/2009
 * Filter an array of multiple instances of a member and return an array
 * consisting of unique members.
 *
 */
 
 
nomask static mixed *uniq_array(mixed *arr)
{
    int i;
    mapping rv;
    
    rv = ([]);
    
    for(i=0; i<sizeof(arr); i++)
        if(!rv[arr[i]])
            rv[arr[i]] = 1;

    return map_indices(rv);
}
