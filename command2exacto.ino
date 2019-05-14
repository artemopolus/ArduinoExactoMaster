                          //01234567
char OutputMessageUART[] = "[0w0000]";

void send2uart()
{
  data2log("cmd:");
  data2log(OutputMessageUART);
  for (int i = 0; i < 8; i++) Serial1.write(OutputMessageUART[i]);
  smbl2log('\n');
}
void setExCmd(const char TrgSens, const char Type, const char RegAdr1, const char RegAdr2, const char RegVal1, const char RegVal2)
{
  OutputMessageUART[1] = TrgSens;
  OutputMessageUART[2] = Type;
  OutputMessageUART[3] = RegAdr1;
  OutputMessageUART[4] = RegAdr2;
  OutputMessageUART[5] = RegVal1;
  OutputMessageUART[6] = RegVal2;
}
void correctCommand(const char cmd)
{
  switch(cmd)
  {
    case '0':
      setExCmd('0','w','0','0','0','0');
      break;
    case '1':
      setExCmd('0','w','0','0','0','1');
      break;
  }
}
