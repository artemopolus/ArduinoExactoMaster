File FileToData;
File File4Log;
String LogPath;
String FilePath;
String filedirname = "/sessions";
String logdirname = "/logs";

void setFilesLogDefault()
{
  /* устанавливаем значения логов и файлов записи по умолчанию */
  String filename = "data";
  String logname = "log";
  String fileext = ".txt";
  FilePath = filedirname + "/" + filename + "0" +fileext;
  LogPath = logdirname + "/" +logname + "0" + fileext;
  /* только пустой файл */
  writeFile(SD,FilePath.c_str(),"");
  writeFile(SD,LogPath.c_str(),"Log on\n");
}
void setupFile()
{
  /* значения имен для файлов и логов плюс расширение */
  String filename = "data";
  String logname = "log";
  String fileext = ".txt";
  int counter = 0;
  dirIsExist(SD,filedirname.c_str());
  dirIsExist(SD,logdirname.c_str());
  bool fileIsFounded = false;
  String trgfilename = filename + "0" + fileext;
  /* ищем имя, которое не занято */
  while(isFileInDir(SD, filedirname.c_str(), trgfilename.c_str()))
  {
    counter++;
    trgfilename = filename + String(counter) + fileext;
  }
  /* запоминаем пути */
  FilePath = filedirname + "/" + filename + String(counter) +fileext;
  LogPath = logdirname + "/" +logname + String(counter) + fileext;

  /* стартовые данные в файлах */
  writeFile(SD,FilePath.c_str(),"");
  writeFile(SD,LogPath.c_str(),"Log on\n");
}
void closeDataFile()
{
  /* закрываем файл записи данных */
  close2openedFile(& FileToData);
}
void smbl2log(const char smbl)
{
  if (Serial){
    Serial.print(smbl);
  }
  if(writing)
  {
    if (logCounter == 0)
    {
      open2appendFile(SD, LogPath.c_str(), & File4Log);
    }
    appendSMBLtoFile(&File4Log,smbl);
    if (logCounter < logMaxCounter)
    {
      logCounter++;
    }
    else
    {
      close2openedFile(& File4Log);
      logCounter = 0;
    }
  }
}
void data2log(const char * message)
{
  /* Если открыт серийник, то льем туда данные */
  if (Serial){
    Serial.print(message);
  }
  /* если можно писать на карту, то логируем по счетчику (НАДО ли????) */
  if (writing)
  {
    if (logCounter == 0)
    {
      open2appendFile(SD, LogPath.c_str(), & File4Log);
    }
    append2openedFile(&File4Log,message);
    if (logCounter < logMaxCounter)
    {
      logCounter++;
    }
    else
    {
      close2openedFile(& File4Log);
      logCounter = 0;
    }
  }
}
