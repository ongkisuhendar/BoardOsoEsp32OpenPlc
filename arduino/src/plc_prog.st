PROGRAM program0
  VAR
    led AT %QX0.1 : BOOL;
  END_VAR
  VAR
    delay : TIME := T#2S;
    TP0 : TP;
    TON0 : TON;
    val : BOOL;
  END_VAR

  TP0(IN := NOT(val), PT := delay);
  led := NOT(TP0.Q);
  TON0(IN := led AND NOT(val), PT := delay);
  val := TON0.Q;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
