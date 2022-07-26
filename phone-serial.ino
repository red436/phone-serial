#include<SoftwareSerial.h>

SoftwareSerial mySerial(8,9);
int ringCount = 0;
String lastNumber;


//EEPROM.put(address,data);
//EEPROM.get(address,varToWriteInto);

const int callButtonPin = 6;
int callButtonState = 0;
const int clearMessagesPin = 5;
int clearMessagesButtonState = 0;
const int resetButtonPin = 4;
int resetButtonState = 0;

bool newNumber = false;
bool inCall = false;

void setup()
{
    pinMode(callButtonPin, INPUT);
    pinMode(clearMessagesPin, INPUT);
    pinMode(resetButtonPin, INPUT);
    mySerial.begin(9600);
    delay(4000);
    mySerial.println("AT");
    delay(1000);
    mySerial.println("ATE0");
    delay(500);
    mySerial.println("AT+CMGF=1");
    delay(500);
    mySerial.println("AT+CLIP=1");
    delay(500);
    mySerial.println("AT+CNMI=1,2,0,0,0");
    mySerial.flush();
}

void loop()
{
     callButtonState = digitalRead(callButtonPin);
     clearMessagesButtonState = digitalRead(clearMessagesPin);
     resetButtonState = digitalRead(resetButtonPin);
     if(newNumber == true)
     {
         tone(7, 988, 500);
         delay(1000);
         tone(7, 988, 500);
         delay(1000);
     }
     if(callButtonState == HIGH && newNumber == true)
     {
         mySerial.println("ATD+ " + lastNumber + ";");
         mySerial.flush();
         newNumber = false;
         inCall = true;
     }
     if(callButtonState == HIGH && inCall == true && newNumber == false)
     {
         mySerial.println("ATH");
         mySerial.flush();
         inCall = false;
     }
     if(clearMessagesButtonState == HIGH)
     {
        mySerial.println("AT+CMGD=4");
        mySerial.flush();
     }
     if(resetButtonState == HIGH)
     {
        mySerial.println("AT+CREG=1");
        mySerial.flush();
        delay(4000);
        mySerial.println("AT");
        mySerial.flush();
        delay(500);
        mySerial.println("ATE0");
        mySerial.flush();
        delay(500);
        mySerial.println("AT+CMGF=1");
        mySerial.flush();
        delay(500);
        mySerial.println("AT+CNMI=1,2,0,0,0");
        mySerial.flush();
        delay(500);
     }
     while(mySerial.available())
     {
         String line = mySerial.readStringUntil('\n');
         if(line.indexOf("+CLIP:") >= 0 && ringCount < 3)
         {
            if(ringCount == 2)
            {
                lastNumber = String("+") + line.substring(8,19);
                mySerial.println("ATH");
                mySerial.flush();
                ringCount = 0;
                newNumber = true;
            }
            ringCount++;
         }
         if(line.indexOf("+CMT:") >= 0)
         {
           lastNumber = line.substring(7,19);
           newNumber = true;
         }
     }
}
