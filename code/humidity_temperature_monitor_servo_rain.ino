//Το συγκεκριμένο πρόγραμμα είναι υπεύθυνο για να ελέγχει την υγρασία, την θερμοκρασία του θερμοκηπίου συνδεοντάς το με ένα σερβομηχανισμού. Η τιμή της υγρασίας και της θερμοκρασίας
//εμφανίζονται σε μια οθόνη LED 16 θέσεων. Σε περίπτωση που η υγρασία είναι μεγαλύτερη από την τιμή 70 τότε ένας σερβομηχανισμός ανοίγει ένα παράθυρο στην οροφή. Επίσης υπάρχει ένας
//αισθητήρας υγρασίας και σε περίπτωση που ανιχνεύσει βροχή τότε ένας σερβομηχανισμός αναλαμβάνει να κλείσει ένα παράθυρο στην οροφή που είναι ανοιχτό.


#include <dht.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

dht DHT;

#define DHT11_PIN 7

//servo
Servo myservo;  //δημιουργεί ένα αντικείμενο servo
int pos = 0;    //μεταβλητή που αποθηκεύει την θέση σε μοίρες του servo
int servoOn=0;

//led
int greenLed=6;

//rain sensor
const int rain_D=8;
const int rain_A=A0;
int rainLed=10;
int tempRainValue;
//rainServo
Servo myservorain;  //δημιουργεί ένα αντικείμενο servo
int posRain = 0;    //μεταβλητή που αποθηκεύει την θέση σε μοίρες του servo
int servoRainOn=0;

void setup(){
  lcd.begin(16, 2);  
  //servo
  myservo.attach(9); //καθορίζει ως είσοδο του servo στην θέση 6
  //lights
  pinMode(greenLed,OUTPUT);
  //rain sensor
  pinMode(rain_A, INPUT);
  pinMode(rain_D, INPUT);
  pinMode(rainLed,OUTPUT);
  myservorain.attach(13);
  
  Serial.begin(9600);
}

void loop()
{
   int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0); 
  lcd.print("Θερμοκρασία: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Yγρασία: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  delay(1500);
  

  if(DHT.humidity<70.00){
    if(servoOn==0){
      //σβήνει το πράσινο led
      digitalWrite(greenLed,LOW);
      delay(20);
      for(pos = 90; pos >= 0; pos -= 1) //πάει από το 90 στις 0 μοίρες μειώνοντας το 1 μοίρα κάθε φορά
      { 
        myservo.write(pos); //ο σερβομηχανισμός πάει στη θέση της μεταβλητής pos
        delay(100); //περιμένει κάποιο χρόνο ώστε το servo να πάει στη θέση του
      }
      servoOn=1;
    }
  }
  else{
    if(servoOn==1){
      //ανάβει το πράσινο led
      digitalWrite(greenLed,HIGH);
      delay(20);
      for(pos = 0; pos < 90; pos += 1) //πάει από το 0 στις 90 μοίρες αυξανόμενο 1 μοίρα κάθε φορά
      {
        myservo.write(pos); //ο σερβομηχανισμός πάει στη θέση της μεταβλητής pos
        delay(50); //περιμένει κάποιο χρόνο ώστε το servo να πάει στη θέση του
      } 
      servoOn=0; 
    }
  }

  //rain sensor
  if(digitalRead(rain_D) == LOW) 
  {
    digitalWrite(rainLed,HIGH);
    if(servoRainOn==0){
      for(posRain = 90; posRain >= 0; posRain -= 1) //πάει από το 90 στις 0 μοίρες μειώνοντας το 1 μοίρα κάθε φορά
      { 
        myservorain.write(posRain); //ο σερβομηχανισμός πάει στη θέση της μεταβλητής pos
        delay(100); //περιμένει κάποιο χρόνο ώστε το servo να πάει στη θέση του
      }
      servoRainOn=1;
    }
    Serial.println("Ψηφιακή τιμή: υγρό"); 
    delay(10); 
  }
  else
  {
    digitalWrite(rainLed,LOW);
    if(servoRainOn==1){
      for(posRain = 0; posRain < 90; posRain += 1) //πάει από το 0 στις 90 μοίρες αυξανόμενο 1 μοίρα κάθε φορά
      {
        myservorain.write(posRain); //ο σερβομηχανισμός πάει στη θέση της μεταβλητής posRain
        delay(50); //περιμένει κάποιο χρόνο ώστε το servo να πάει στη θέση του
      }
      servoRainOn=0;
    }
    Serial.println("Ψηφιακή τιμή: στεγνό");
    delay(10); 
  }
  tempRainValue=analogRead(rain_A); 
  Serial.print("Αναλογική τιμή : ");
  Serial.println(tempRainValue); 
  Serial.println("");
  delay(1000);
}
