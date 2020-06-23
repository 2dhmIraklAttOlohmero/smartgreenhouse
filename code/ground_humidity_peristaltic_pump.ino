//Το συγκεκριμένο πρόγραμμα είναι υπεύθυνο για να ελέγχει την υγρασία του χώματος. Σε περίπτωση που η τιμή πέσει κάτω από 4 τότε ανοίγει η αντλία νερού και ποτίζει το θερμοκήπιο
ώσπου να ξαναφτάσει η τιμή 4 και πάνω.


//pin για την υγρασία
int sensor_pin = A0;

#define segA 2  //τμήμα A στο pin2
#define segB 3  //τμήμα Β sto pin3
#define segC 4  //τμήμα C στο pin4
#define segD 5  //τμήμα D στο pin5
#define segE 6  //τμήμα Ε για το pin6
#define segF 7  //τμήμα F για το pin7
#define segG 8  //τμήμα G για το pin8

//μεταβλητές για την υγρασία
int output_value ;
int temp;

//μεταβλητές για την αντλία
const int motor=10;
int pumpLed=11;

void setup() {

   Serial.begin(9600);
   Serial.println("Διαβάζει από τον αισθητήρα...");
   delay(2000);

   //κώδικας για την οθόνη
   for (int i=2;i<9;i++)
   {
      pinMode(i, OUTPUT);// χρησιμοποιεί όλα τα pin από το 2-8 ως έξοδο
   }

   //for pump
   pinMode(motor, OUTPUT);
   pinMode(pumpLed, OUTPUT);
}

void loop() {

   output_value= analogRead(sensor_pin);
   Serial.print("\nΥγρασία : ");
   Serial.print(output_value);
   output_value = map(output_value,990,419,0,100); //η τιμή 990 είναι η τιμή που έδειξε στο στεγνό χώμα και η τιμή 419 είναι η τιμή που έδειξε στο υγρό χώμα
   Serial.print("\n%: ");
   temp=(int)output_value/10;
   Serial.print(temp);
   delay(1000);
   
    

   if (temp<4){
      digitalWrite(pumpLed,HIGH);
      delay(20);
      digitalWrite(motor,HIGH);
      delay(20);
   }else{
    digitalWrite(pumpLed,LOW);
    delay(20);
   }
   


   //για την οθόνη
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

                break;
                }

}
