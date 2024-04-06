  int forward = 10;
  int reverce = 10;
  int cicle = 30000;
  int cicle_0 = 20;
  int Enable = 10;
  int FR = 9;
  int Step = 8;
bool Numeral [10][8] = // набор цифр
{
  {0,0,1,1,1,1,1,1}, // 0
  {0,0,0,0,0,1,1,0}, // 1
  {0,1,0,1,1,0,1,1}, // 2
  {0,1,0,0,1,1,1,1}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {0,1,1,0,1,1,0,1}, // 5
  {0,1,1,1,1,1,0,1}, // 6
  {0,0,1,0,0,1,1,1}, // 7
  {0,1,1,1,1,1,1,1}, // 8
  {0,1,1,0,1,1,1,1}  // 9
};
int Control_Board_Size = 5; //отсчет с нуля
long Control_Board_Number [6];
long Number_06 = 0;
long Number_max  = cicle;
int In = 11;
int Clock = 12;
int Large = 13;

void setup() {
  
  pinMode (Enable, OUTPUT);
  pinMode (FR, OUTPUT);
  pinMode (Step, OUTPUT);
  pinMode (0, INPUT); // Кнопка включения
  pinMode (In, OUTPUT);
  pinMode (Clock, OUTPUT);
  pinMode (Large, OUTPUT); 
  digitalWrite (In, 0);
  digitalWrite (Clock, 0);
  digitalWrite (Large, 0); 
  digitalWrite (Enable, 1); // Enable
  digitalWrite (FR, 0); // Forward/Revere
  digitalWrite (Step, 0); // Step

  Serial.begin (9600);
}

void loop() { 
   
  Serial.println ("Чтобы сделать хорошо нажмите кнопку.");
  while (analogRead (0) < 1000){ delay (500);}
 
///////////////////////////////////////////////
/*
 Serial.println ("Намотка 1 клик - 1 оборот.");
 digitalWrite (9, 1);
 int k = 0;
Metka:  
  k++;
  one_cicle (); Serial.print ("+ ");Serial.print (k); Serial.print ("  ");
  while (analogRead (0) < 1000){ delay (500);}
  goto Metka;
  //*/
//////////////////////////////////////
  Serial.print ("Предварительная намотка   "); Serial.print (cicle_0); Serial.println ("  оборотов.");
    digitalWrite (9, 1);
    for(int j = 0; j < cicle_0; j++)
    {   one_cicle ();    Serial.print ("+");}
    digitalWrite (9, 0);
    Serial.println (""); 
////////////////////////////////////////// 
  Serial.println ("Хорошо намотали.");
  cicle_pause:
  Serial.println ("Продолжить хорошо?");
  while (analogRead (0) < 1000){ delay (500);}
  Serial.println ("Поехали!");
//////////////////////////////////////////
 for (int i = 0; i < cicle; i++)
 {
    Serial.print (i+1); Serial.print (" круг  ");
    full_cicle ();
    Serial.println ("");
    Number_06 = i + 1;
    Number_To_Array ();
    Print_Control_Board_Number ();
 }
 
 Serial.print ("Задание закончено.");
 goto cicle_pause;
 while (1){} 
}


void one_cicle_f ()
{
  for (int i = 0; i < 200; i++) //
    { 
      digitalWrite (8, 1); delay (1); 
      digitalWrite (8, 0); delay (1);
    }
}

void one_cicle_r ()
{  
  for (int i = 0; i < 200; i++) //
    { 
      digitalWrite (8, 1); delay (1); 
      digitalWrite (8, 0); delay (1);
    }
}

void cicle_adjustment ()
{  
  for (int i = 0; i < 2; i++) //
    { 
      digitalWrite (8, 1); delay (1); 
      digitalWrite (8, 0); delay (1);
    }
}

void one_cicle ()
{
  for (int i = 0; i < 200*2; i++) //
    { 
      digitalWrite (8, !digitalRead (8)); delay (1); 
    }
}

void full_cicle () 
{   
    digitalWrite (9, 1);
    for(int i = 0; i < forward; i++)
    {   one_cicle ();    Serial.print ("+");}
    digitalWrite (9, 0);
    cicle_adjustment ();  
    for(int j = 0; j < reverce; j++)
    {   one_cicle ();        Serial.print ("-");} 

}

void Print_Control_Board_Number () { 
  for (int i = Control_Board_Size; i >= 0; i--){
    //Serial.println (Control_Board_Number [i]);
    for (int j = 0; j < 8 ; j++) {
      digitalWrite (In, Numeral [Control_Board_Number [i]] [j]); 
      digitalWrite (Clock, 1); delay (1);
      digitalWrite (Clock, 0);
      digitalWrite (In, 0);
    }
   }
   digitalWrite (Large, 1); delay (1);
   digitalWrite (Large, 0);
}

void Number_To_Array (){
  long dummy = Number_06;
  //Serial.println (Number_06);
  Control_Board_Number [0] = dummy / 100000;
  //Serial.println (Control_Board_Number [0]);
  Control_Board_Number [1] = dummy / 10000 - dummy / 10000 / 10 * 10;
  //Serial.println (Control_Board_Number [1]);
  Control_Board_Number [2] = dummy / 1000  - dummy / 1000 / 10 * 10;
  //Serial.println (Control_Board_Number [2]);  
  Control_Board_Number [3] = dummy / 100 - dummy / 100 / 10 * 10;
  //Serial.println (Control_Board_Number [3]);
  Control_Board_Number [4] = dummy / 10 - dummy /10 / 10 * 10; //
  //Serial.println (Control_Board_Number [4]);
  Control_Board_Number [5] = dummy - dummy / 10 * 10;
  //Serial.println (Control_Board_Number [5]);
  }
