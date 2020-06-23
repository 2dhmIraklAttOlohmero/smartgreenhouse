//Το συγκεκριμένο πρόγραμμα είναι υπεύθυνο για να ανιχνεύει κίνηση κοντά στην πόρτα του θερμοκηπίου. Εάν ανιχνεύσει κίνηση τότε ανάβει ένα λαμπάκι να σε προειδοποιήσει.
//Επιπλέον δείχνει την απόσταση του αντικειμένου από το θερμοκήπιο σε μια οθόνη.


//οθόνη
#define segA 2   //τμήμα A στο pin2
#define segB 3   //τμήμα Β sto pin3
#define segC 4  //τμήμα C στο pin4
#define segD 5  //τμήμα D στο pin5
#define segE 6  //τμήμα Ε για το pin6
#define segF 7  //τμήμα F για το pin7
#define segG 8  //τμήμα G για το pin8
int temp=0;    //μετρητής

//ανίχνευση κίνησης
#define surveillancePin 13
int value=0;
bool motionState=false;

//led
int redLed=9;
int greenLed=11;

//αισθητήρας ultrasonic
int trigPin = 10;    // trigger
int echoPin = 12;    // echo
long duration, cm, inches;

void setup() {
  //σειριακή πόρτα ξεκινάει
  Serial.begin (9600);
  //καθορίζει την είσοδο και έξοδο του arduino για τον ultrasonic αισθητήρα
  pinMode(trigPin, OUTPUT); //καθορίζει το trigger στην θέση 12 ως έξοδο
  pinMode(echoPin, INPUT);  //καθορίζει το echo στην θέση 11 ως είσοδο
  
  //lights
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);

  //for the monitor
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  //motion detector
  pinMode(surveillancePin, INPUT);
}

void loop() {
  //ορίζονται παλμός LOW και ο παλμός HIGH ώστε να υπολογιστεί αργότερα η απόσταση του αντικειμένου που βρίσκεται μακρυά
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
 
  //διαβάζει ως είσοδο το σήμα του αισθητήρα
  //ένα HIGH παλμός είναι η διάρκεια σε microseconds από την αποστολή ενός παλμού ήχου έως την επιστροφή του αφού αντανακλάσει επάνω σε ένα αντικείμενο
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  //μετατροπή του χρόνου σε απόσταση βάση μιας συνάρτησης
  cm = (duration/2) *0.0343;
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if(cm>100){
      //ανάβει το πράσινο led
      digitalWrite(greenLed,LOW);

  }else{
      //σβήνει το πράσινο led
      digitalWrite(greenLed,HIGH);
      temp=cm/10;
      switch (temp)
      {
                case 0:   //δείχνει το "0"
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, HIGH);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, LOW);
                break;

                case 1:   //δείχνει το "1"
                digitalWrite(segA, LOW);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, LOW);
                digitalWrite(segE, LOW);
                digitalWrite(segF, LOW);
                digitalWrite(segG, LOW);
                break;

                case 2:   //δείχνει το "2"
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, LOW);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, HIGH);
                digitalWrite(segF, LOW);
                digitalWrite(segG, HIGH);
                break;

                case 3:   //δείχνει το "3"
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, LOW);
                digitalWrite(segF, LOW);
                digitalWrite(segG, HIGH);
                break;

                case 4:   //δείχνει το "4"
                digitalWrite(segA, LOW);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, LOW);
                digitalWrite(segE, LOW);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;

                case 5:   //δείχνει το "5"
                digitalWrite(segA, HIGH);
                digitalWrite(segB, LOW);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, LOW);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;

                case 6:   //δείχνει το "6"
                digitalWrite(segA, HIGH);
                digitalWrite(segB, LOW);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, HIGH);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;

                case 7:   //δείχνει το "7"
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, LOW);
                digitalWrite(segE, LOW);
                digitalWrite(segF, LOW);
                digitalWrite(segG, LOW);
                break;

                case 8:   //δείχνει το "8"
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, HIGH);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;

                case 9:   //δείχνει το "9"
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, LOW);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;
    }
  }

  //ανίχνευση κίνησης
  value = digitalRead(surveillancePin);
  //αν ανιχνεύσει κίνηση
  if (value == HIGH){
    digitalWrite(9, HIGH); //ανάβει το λαμπάκι
    if (motionState == false) {
      Serial.println("Ανιχνεύτηκε κίνηση!");
      motionState = true;
    }
  }
  else{
    digitalWrite(9, LOW); //σβήνει το λαμπάκι
    if (motionState == true) {
      Serial.println("Ολοκληρώθηκε η ανίχνευση κίνησης!");
      motionState = false;
    }
  }
}
