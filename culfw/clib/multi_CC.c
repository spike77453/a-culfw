#include "board.h"

#ifdef HAS_MULTI_CC

#include <stdint.h>

#include "multi_CC.h"
#include "display.h"
#include "ttydata.h"

extern const t_fntab fntab[];
extern const t_fntab fntab1[];
extern const t_fntab fntab2[];
extern const t_fntab fntab3[];

const t_fntab* fntabs[] =  {
    fntab,
    fntab1,
#if HAS_MULTI_CC > 2
    fntab2,
#endif
#if HAS_MULTI_CC > 3
    fntab3,
#endif
};
multiCC_t multiCC;


uint8_t callfn2(char *buf)
{
  for(uint8_t idx = 0; ; idx++) {
    uint8_t n = fntabs[ multiCC.instance][idx].name;
    void (*fn)(char *) = (void (*)(char *))fntabs[ multiCC.instance][idx].fn;
    if(!n)
      break;
    if(buf == 0) {
      DC(' ');
      DC(n);
    } else if(buf[0] == n) {
      fn(buf);
      return 1;
    }
  }
  return 0;
}

void multiCC_func(char *in) {

  in++;
  multiCC.instance++;

  if(!callfn2(in)) {
    DS_P("? (");
    display_string(in);
    DS_P(" is unknown) Use one of");
    callfn2(0);
    DNL();
  }
}

#endif
