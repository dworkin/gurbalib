/* Defines */

#define GRAMMAR \
  "escaped=/\\\\/\n"+\
  "quote=/\"/\n"+\
  "floats=/[\-]?[0-9]*[.][0-9]+/\n"+\
  "arraystart=/[(][{][ ]*/\n"+\
  "arrayend=/[ ]*[}][)]/\n"+\
  "arraysep=/[ ]*,[ ]*/\n"+\
  "mapstart=/[(][[][ ]*/\n"+\
  "mapend=/[ ]*][)]/\n"+\
  "mapsep=/[ ]*:[ ]*/\n"+\
  "ints=/[\-]?[0-9]+/\n"+\
  "char=/./\n"+\
  "var: float\n"+\
  "var: int\n"+\
  "var: string\n"+\
  "var: array\n"+\
  "var: map\n"+\
  "string: quote quote ? emptystring\n"+\
  "string: quote chars quote ? concatstring\n"+\
  "array: arraystart arrayend ? mkemptyarray\n"+\
  "array: arraystart arrayelements arrayend ? mkarray\n"+\
  "map: mapstart mapend ? mkemptymap\n"+\
  "map: mapstart mapelements mapend ? mkmap\n"+\
  "arrayelements: element\n"+\
  "arrayelements: arrayelements arraysep element\n"+\
  "arrayelements: arrayelements arraysep\n"+\
  "element: int\n"+\
  "element: float\n"+\
  "element: string\n"+\
  "element: array\n"+\
  "element: map\n"+\
  "mapelements: element mapsep element\n"+\
  "mapelements: mapelements arraysep element mapsep element\n"+\
  "mapelements: mapelements arraysep\n"+\
  "chars: char\n"+\
  "chars: escaped escaped\n"+\
  "chars: escaped quote\n"+\
  "chars: arraystart\n"+\
  "chars: arrayend\n"+\
  "chars: mapstart\n"+\
  "chars: mapend\n"+\
  "chars: arraysep\n"+\
  "chars: mapsep\n"+\
  "chars: floats\n"+\
  "chars: ints\n"+\
  "chars: chars char\n"+\
  "chars: chars escaped escaped\n"+\
  "chars: chars escaped quote\n"+\
  "chars: chars arraystart\n"+\
  "chars: chars arrayend\n"+\
  "chars: chars mapstart\n"+\
  "chars: chars mapend\n"+\
  "chars: chars arraysep\n"+\
  "chars: chars mapsep\n"+\
  "chars: chars floats\n"+\
  "chars: chars ints\n"+\
  "int: ints ? cnvint\n"+\
  "float: floats ? cnvfloat\n"
