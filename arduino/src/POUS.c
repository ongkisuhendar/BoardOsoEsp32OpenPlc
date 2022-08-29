#include "POUS.h"

void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__QX0_1,data__->LED,retain)
  __INIT_LOCATED_VALUE(data__->LED,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->DELAY,__time_to_timespec(1, 0, 2, 0, 0, 0),retain)
  TP_init__(&data__->TP0,retain);
  TON_init__(&data__->TON0,retain);
  __INIT_VAR(data__->VAL,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PROGRAM0_body__(PROGRAM0 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->TP0.,IN,,!(__GET_VAR(data__->VAL,)));
  __SET_VAR(data__->TP0.,PT,,__GET_VAR(data__->DELAY,));
  TP_body__(&data__->TP0);
  __SET_LOCATED(data__->,LED,,!(__GET_VAR(data__->TP0.Q,)));
  __SET_VAR(data__->TON0.,IN,,(__GET_LOCATED(data__->LED,) && !(__GET_VAR(data__->VAL,))));
  __SET_VAR(data__->TON0.,PT,,__GET_VAR(data__->DELAY,));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->,VAL,,__GET_VAR(data__->TON0.Q,));

  goto __end;

__end:
  return;
} // PROGRAM0_body__() 





