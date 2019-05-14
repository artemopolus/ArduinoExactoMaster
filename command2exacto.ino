                          //01234567
char OutputMessageUART[] = "[0w0000]";

void send2uart()
{
  for (int i = 0; i < 8; i++) Serial1.write(OutputMessageUART[i]);
}
void setCmdW(const char TrgSens, const char RegAdr, const char RegVal)
{
  OutputMessageUART[1] = TrgSens;
  OutputMessageUART[2] = 'w';
  OutputMessageUART[1] = RegAdr;
  OutputMessageUART[1] = RegVal;
}
void setCmdR(const char TrgSens, const char RegAdr, const char RegVal)
{
  OutputMessageUART[1] = TrgSens;
  OutputMessageUART[2] = 'r';
  OutputMessageUART[1] = RegAdr;
  OutputMessageUART[1] = RegVal;
}
void correctCommand(const char cmd)
{
  switch(cmd)
  {
    case '0':
      break;
    case '1':
      break;
  }
}
