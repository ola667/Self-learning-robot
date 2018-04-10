/*

trassel_robot.ino . - a chaotic self learning robot
Ola Hjelmgren 2018

this code is used for a small, self learning chaotic robot. 
I have described the robot here: https://www.instructables.com/id/Self-learning-Chaotic-Robot/


ps2 lib can be found here: https://github.com/jazzycamel/PS2Mouse


*/
#include <ps2.h>
#include <Servo.h>

PS2 mouse(12, 13);   //(clock, data)

Servo servo1;  
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

// [individ_nr][position_nr] The start array, later replaced as robot evolves
byte individ[50][50] = {{1,2,3,4,5,6,7,8,9,10,11,12,13,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {10,11,12,13,14,15,16,17,18,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {15,16,17,18,19,20,21,22,23,24,25,26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {203,78,62,164,0,48,157,171,101,109,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {141,191,228,185,63,53,75,201,224,212,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {232,107,77,248,130,43,24,102,24,244,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {246,242,250,204,30,80,74,170,37,89,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {198,156,90,36,61,156,129,157,130,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {140,174,129,100,144,60,72,221,78,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {174,40,164,185,106,32,127,8,10,89,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {164,135,240,224,27,34,152,224,66,249,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {131,254,18,180,7,56,119,44,142,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {233,198,211,115,60,217,70,46,113,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {72,22,11,158,157,6,20,140,193,171,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {201,89,187,154,57,120,228,186,63,117,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {156,52,108,254,165,45,140,113,127,254,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {238,152,76,225,125,177,253,46,153,152,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {78,108,148,248,130,3,48,120,11,221,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                       {252,155,4,247,88,18,248,45,134,170,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {188,52,100,217,187,235,210,240,240,191,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {162,175,15,192,119,86,93,26,104,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {235,225,172,34,61,206,217,173,25,195,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {38,63,14,101,164,35,235,147,143,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {80,250,203,160,190,100,0,45,199,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {218,123,214,50,221,46,99,63,175,237,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {254,10,4,254,140,42,102,0,172,73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {216,125,147,122,0,48,208,3,87,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {217,216,2,86,224,89,8,242,1,150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {195,51,139,236,45,210,139,111,19,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {169,29,247,75,163,157,106,237,153,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {162,38,150,217,26,31,94,213,176,127,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {251,115,148,193,189,120,2,18,75,154,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {139,200,84,240,93,111,191,34,41,82,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {167,227,114,5,211,103,65,193,21,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {242,3,142,37,24,73,155,14,72,236,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {92,247,105,173,110,238,181,96,237,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {217,123,120,64,90,175,1,81,183,169,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {113,238,185,24,233,204,8,36,177,71,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {69,169,118,130,119,150,47,218,161,173,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {93,29,180,24,74,98,139,168,231,201,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {81,39,252,222,235,241,72,107,77,223,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {36,14,44,172,7,119,163,191,153,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {251,159,251,41,74,68,78,192,24,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {151,168,120,254,139,54,245,143,183,239,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {232,17,47,201,174,247,243,219,193,228,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {147,119,222,193,151,116,195,117,63,113,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {148,193,200,244,184,78,241,149,121,126,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
                       {129,241,204,86,62,134,200,157,156,150,27,97,170,202,37,181,87,201,112,17,186,130,47,243,134,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},};   

byte length_of_individ[50];          
byte individ_to_mutate;
byte individ_to_print;
byte parent_1[50];
byte parent_2[50];
byte id_of_parent1;
byte id_of_parent2;
byte baby_1[50];
byte baby_2[50];
byte individ_to_tolken;         //individ that should be sent to tolken and then run
int  fitness_of_individs[50];   //the distance that every individ has performed
int  maxvalue;
byte index_of_maxvalue;
byte individs_are_tested[50];   //1=is tested   0=should be tested
byte four_monkeys[4];           //id of the four monkeys!
byte rang_of_monkeys[4];        //0=best, 1=second best.... 3=worst 
int m1;
int m2;
int m3;
int m4;
int m5;
int m6;
int m7;
int m8;
int test_tolk[5] = {1,50,100,150,200};
int motorkod1[4];
int motorkod2[4];
int motorkod3[4];
int motorkod4[4];
int motorkod5[4];
int motorkod6[4];
int motorkod7[4];
int motorkod8[4];
int y_dist;
volatile int current_dist;
volatile int dump_dist;
volatile unsigned long millis_start;
volatile unsigned long millis_stop;
volatile unsigned long test;

int dist;
char mstat;
int my;
int mx;
byte down;
byte left;

char inChar;
char dump;
boolean firstrun;

//---------------------------------------------------------- 
void mouse_init()
{
  mouse.write(0xff);  
  mouse.read();  
  mouse.read();  
  mouse.read();  
  mouse.write(0xf0);  
  mouse.read();  
  delayMicroseconds(100);
}
//------------------------------------------------------------------------------
void setup() {
Serial.begin(38400);
delay(1000);
Serial.println("Start");

mouse_init();

servo1.attach(39);   // servo 1 on D3
servo2.attach(41);   // servo 2 on D4
servo3.attach(43);   // servo 3 on D5
servo4.attach(45);   // servo 4 on D6
servo5.attach(47);   // servo 5 on D7
servo6.attach(49);   // servo 6 on D8
servo7.attach(51);   // servo 7 on D9
servo8.attach(53);  // servo 8 on D10

servo1.write(90);
servo2.write(90);
servo3.write(90);
servo4.write(90);
servo5.write(90);
servo6.write(90);
servo7.write(90);
servo8.write(90);

  

int slump = 0;
slump = analogRead(8);    //short antenna on A8 - not needed
Serial.print("slumptal: ");
Serial.println(slump);
randomSeed(slump);

individ_to_mutate = 0;
get_length();
individ_to_tolken = 0;

// warming up the mouse
int i=0;  
for(i=0;i<30;i++)
      {
        mouse.write(0xeb);  
        mouse.read();      
        mstat = mouse.read();
        mx = mouse.read();
        my = mouse.read();
        Serial.println(my);
        delay(100);
       }

my = 0;
firstrun = true;  

i = 0;
for (i=0; i<50;i++)
      {
         fitness_of_individs[i] = -99;
      }
}

//-------------------------------------------------------------------------------
void test_servo()
{
 servo1.write(0);
 delay(200);
 servo2.write(0);
 delay(200);
 servo3.write(0);
 delay(200);
 servo4.write(0);
 delay(200);
 servo5.write(0);
 delay(200);
 servo6.write(0);
 delay(200);
 servo7.write(0);
 delay(200);
 servo8.write(0);
 delay(3000);                       
 servo1.write(90);
 delay(200);
 servo2.write(90);
 delay(200);
 servo3.write(90);
 delay(200);
 servo4.write(90);
 delay(200);
 servo5.write(90);
 delay(200);
 servo6.write(90);
 delay(200);
 servo7.write(90);
 delay(200);
 servo8.write(90);
 delay(3000);
 servo1.write(180);
 delay(200);
 servo2.write(180);
 delay(200);
 servo3.write(180);
 delay(200);
 servo4.write(180);
 delay(200);
 servo5.write(180);
 delay(200);
 servo6.write(180);
 delay(200);
 servo7.write(180);
 delay(200);
 servo8.write(180);
 delay(3000);  
}
//-------------------------------------------------------------------------------
void print_ms()
{
 Serial.print("m1 = ");
 Serial.println(m1);
 Serial.print("m2 = ");
 Serial.println(m2);
 Serial.print("m3 = ");
 Serial.println(m3);
 Serial.print("m4 = ");
 Serial.println(m4);
 Serial.print("m5 = ");
 Serial.println(m5);
 Serial.print("m6 = ");
 Serial.println(m6);
 Serial.print("m7 = ");
 Serial.println(m7);
 Serial.print("m8 = ");
 Serial.println(m8);
}
//-------------------------------------------------------------------------------
//check_length_of_individuals
void get_length()
{  
        for (byte j=0; j <50; j++)
        {
                length_of_individ[j] = 0;        
                for (byte k=0; k <50; k++)
                {
                        if (individ[j][k] > 0) 
                         { 
                                  length_of_individ[j] = length_of_individ[j] + 1;
                         }      
                }        
        }
}
//----------------------------------------------------------------------------
void mutate()
 {
 get_length(); 
 byte mutation_position;
 byte mutant_lenght;
 mutant_lenght =  length_of_individ[individ_to_mutate];
 
 if(mutant_lenght < 50)
      {
       individ[individ_to_mutate][mutant_lenght] = random(1,255);
       individ[individ_to_mutate][mutant_lenght + 1] = random(1,255);       
      }
 mutation_position = random(0,mutant_lenght);  
 individ[individ_to_mutate][mutation_position] = random(1,255);
 mutation_position = random(0,mutant_lenght);  
 individ[individ_to_mutate][mutation_position] = random(1,255);
 
}  
//----------------------------------------------------------------------------
void printIndivid()
{
 Serial.print("individ nr: "); 
 Serial.print(individ_to_print);
 Serial.print(" {");
 for (byte m = 0; m < 50; m++)
 {  
          Serial.print(individ[individ_to_print][m]); 
          Serial.print(",");
 }
 Serial.print("}");
 Serial.println(" "); 
}  
//---------------------------------------------------------------------------
void printBabys()
{
Serial.println(" "); 

Serial.print(" Baby1: ");
byte a;
a = 0;
for  (a = 0; a < 50; a++)
      {
       Serial.print(baby_1[a]);
       Serial.print(", ");            
      }
Serial.println(" "); 

Serial.print(" Baby2: ");
a = 0;
for  (a = 0; a < 50; a++)
      {
       Serial.print(baby_2[a]);
       Serial.print(", ");            
      }      


 delay(500);     
}
//--------------------------------------------------------------------------
void test_mutation()
{
individ_to_mutate = random(0,49);
individ_to_print = individ_to_mutate;
printIndivid();
Serial.println("mutating");
delay(1000);
mutate();
printIndivid();
delay(1000);
}
//---------------------------------------------------------------------------
void print_lenghts()
{
        for (byte i=0; i < 50; i++)
        {
         Serial.print("lenght of individe nr");
         Serial.print(i);
         Serial.print(" = ");
         Serial.println(length_of_individ[i]);
        }
}
//----------------------------------------------------------------------------
void make_2babys()
{
get_length();  
byte cut1_parent1;    //this is the position that will be no 1 in the splice
byte cut2_parent1;    //this is the position that will be the last in the slice
byte cut1_parent2;    //this is the position that will be no 1 in the splice
byte cut2_parent2;    //this is the position that will be the last in the slice

cut1_parent1 = random(1, (length_of_individ[id_of_parent1]-3));
cut2_parent1 = random((cut1_parent1 + 1), (length_of_individ[id_of_parent1]-2));
cut1_parent2 = random(1, (length_of_individ[id_of_parent2]-3));
cut2_parent2 = random((cut1_parent2 + 1), (length_of_individ[id_of_parent2]-2));

//Serial.print("cut1 parent1: ");
//Serial.println(cut1_parent1);
//Serial.print("cut2 parent1: ");
//Serial.println(cut2_parent1);
//Serial.print("cut1 parent2: ");
//Serial.println(cut1_parent2);
//Serial.print("cut2 parent2: ");
//Serial.println(cut2_parent2);

for (byte p = 0; p < 50; p++)
{
        parent_1[p] = individ[id_of_parent1][p];
        parent_2[p] = individ[id_of_parent2][p];
}


byte lenght_splice1;
byte lenght_splice2;

lenght_splice1 = cut2_parent1 - cut1_parent1 + 1;
lenght_splice2 = cut2_parent2 - cut1_parent2 + 1;
byte splice1[lenght_splice1 + 1];
byte splice2[lenght_splice2 + 1];
//Serial.print("lenght splice1: ");
//Serial.println(lenght_splice1);
//Serial.print("lenght splice2: ");
//Serial.println(lenght_splice2);

//kopiera splicen fran parent 1
byte a;
a = 0;
//Serial.print("splice1: ");
for (a = 0; a < lenght_splice1; a++ )
      {
      splice1[a] =   parent_1[a + cut1_parent1];
      delay(200);
      //Serial.print(splice1[a]);
      //Serial.print(", ");
      }
      
//Serial.println(" ");      
//kopiera splicen fran parent 2
a = 0;
//Serial.print("splice2: ");
for (a = 0; a < lenght_splice2; a++)
      {
      splice2[a] = parent_2[a + cut1_parent2];
      delay(200);
      //Serial.print(splice2[a]);
      //Serial.print(", ");
      }
//Serial.println(" ");  

      
//measure tails and copt them
byte lenght_tail1;
byte lenght_tail2;
lenght_tail1 = length_of_individ[id_of_parent1] - cut2_parent1 - 1;
lenght_tail2 = length_of_individ[id_of_parent2] - cut2_parent2 - 1;

//Serial.print("lenght of tail 1: ");
//Serial.println(lenght_tail1);
//Serial.print("lenght of tail 2: ");
//Serial.println(lenght_tail2);

byte tail1[lenght_tail1];
byte tail2[lenght_tail2];

a = 0;
//Serial.print("Tail 1: ");
for (a = 0; a < lenght_tail1; a++)
      {
        tail1[a] = parent_1[a + cut2_parent1 + 1];
        delay(200);
      //Serial.print(tail1[a]);
      //Serial.print(", ");
      }
//Serial.println(" "); 
      
a = 0;
//Serial.print("Tail 2: ");
for (a = 0; a < lenght_tail2; a++)
    {
      tail2[a] = parent_2[a + cut2_parent2 + 1];
      delay(200);
      //Serial.print(tail2[a]);
      //Serial.print(", ");
    }  

// baby 1 = parent 1 + splice 2 + tail 1!

a = 0;

for (a = 0; a < 50; a++)
        {
        baby_1[a] = parent_1[a]; 
        delay(20);
        baby_2[a] = parent_2[a];
        delay(20);
        }
//Serial.println("  ");
//Serial.println("babys = parents");     
//printBabys();
delay(200);

        
a = 0;

for (a = 0; a < lenght_splice2 ; a++)
      {
       baby_1[a + cut1_parent1] = splice2[a];
       delay(20);
      } 
a = 0;

for (a = 0; a < lenght_splice1 ; a++)
      {
       baby_2[a + cut1_parent2] = splice1[a];
       delay(20);
      } 
      
//Serial.println("  ");
//Serial.println("splicen pa plats");
//printBabys();
delay(200);

//for baby 1: start printing tail in position = cut1_parent1 + length splice2

// awoid to long array, limit to 50 positions

byte total_l1;
byte total_l2;
total_l1 = cut1_parent1 + lenght_splice2 + lenght_tail1;
total_l2 = cut1_parent2 + lenght_splice1 + lenght_tail2;
Serial.println(" ");
//Serial.print("total lenght1: ");
//Serial.println(total_l1);
//Serial.print("total lenght2: ");
//Serial.println(total_l2);

byte overflow_control1;
byte overflow_control2;
overflow_control1 = 50 - total_l1;
overflow_control2 = 50 - total_l2;
//Serial.print("overflow_control1: ");
//Serial.println(overflow_control1);
//Serial.print("overflow_control2: ");
//Serial.println(overflow_control2);

// limiting maximum length

byte stopp;
stopp = lenght_tail1;
if (lenght_tail1 > overflow_control1)
      {
        stopp = overflow_control1;
      }


a = 0;
for (a = 0; a < stopp; a++)
      {
        baby_1[a + cut1_parent1 + lenght_splice2] = tail1[a]; 
      }

stopp = lenght_tail2;
if (lenght_tail2 > overflow_control2)
      {
        stopp = overflow_control2;
      }



a = 0;
for (a = 0; a < stopp; a++)
      {
        baby_2[a + cut1_parent2 + lenght_splice1] = tail2[a];
      }


//Serial.println("  ");
//Serial.println("tails in place");
//printBabys();

/*
delay(500);

a = 0;
for (a = total_l1; a < 50; a++)
      {
       baby_1[a] = 0;       
      }

a = 0;
for (a = total_l2; a < 50; a++)
      {
       baby_2[a] = 0;       
      }
Serial.println("  ");
Serial.println("zeros are written");
printBabys();      
delay(500);
*/

}
//----------------------------------------------------------------------------
void test_make2babys()
{
  
id_of_parent1 = random(0,49);
Serial.print("parent1 is: ");
Serial.println(id_of_parent1);
id_of_parent2 = random(0,49);
while (id_of_parent1 == id_of_parent2)
                {
                 id_of_parent2 = random(0,49); 
                }
          

Serial.print("parent2 is: ");
Serial.println(id_of_parent2);
individ_to_print = id_of_parent1;
printIndivid();
individ_to_print = id_of_parent2;
printIndivid();
make_2babys();
delay(10000);
}  

//--------------------------------------------------------------------------
void tolken()
{
// always the same start values for the m-values
m1 = 91;
m2 = -88;
m3 = 159;
m4 = 4;
m5 = -165;
m6 = -71;
m7 = 31;
m8 = -102;
int b;
b = 0;
for (b=0; b<4;b++)   //run four laps in the tolken
{



int a;
a = 0;
for (a=0; a<50;a++){
switch (individ[individ_to_tolken][a]){
case 0:
m1 = m1;
break;  
case 1:
m1 = m1 + m2;
break;
case 2:
m1 = m1 + m3;
case 3:
m1 = m1 + m4;
break;
case 4:
m1 = m1 + m5;
break;
case 5:
m1 = m1 + m6;
break;
case 6:
m1 = m1 + m7;
break;
case 7:
m1 = m1 + m8;
break;
case 8:
m1 = m1 - m1;
break;
case 9:
m1 = m1 - m2;
break;
case 10:
m1 = m1 - m3;
break;
case 11:
m1 = m1 - m4;
break;
case 12:
m1 = m1 - m5;
break;
case 13:
m1 = m1 - m6;
break;
case 14:
m1 = m1 - m7;
break;
case 15:
m1 = m1 - m8;
break;
case 16:
m1 = m1 * m1;
break;
case 17:
m1 = m1 * m2;
break;
case 18:
m1 = m1 * m3;
break;
case 19:
m1 = m1 * m4;
break;
case 20:
m1 = m1 * m5;
break;
case 21:
m1 = m1 * m6;
break;
case 22:
m1 = m1 * m7;
break;
case 23:
m1 = m1 * m8;
break;
case 24:
m1 = m1 / m1;
break;
case 25:
m1 = m1 / m2;
break;
case 26:
m1 = m1 / m3;
break;
case 27:
m1 = m1 / m4;
break;
case 28:
m1 = m1 / m5;
break;
case 29:
m1 = m1 / m6;
break;
case 30:
m1 = m1 / m7;
break;
case 31:
m1 = m1 / m8;
break;
case 32:
m2 = m2 + m1;
break;  
case 33:
m2 = m2 + m2;
break;
case 34:
m2 = m2 + m3;
case 35:
m2 = m2 + m4;
break;
case 36:
m2 = m2 + m5;
break;
case 37:
m2 = m2 + m6;
break;
case 38:
m2 = m2 + m7;
break;
case 39:
m2 = m2 + m8;
break;
case 40:
m2 = m2 - m1;
break;
case 41:
m2 = m2 - m2;
break;
case 42:
m2 = m2 - m3;
break;
case 43:
m2 = m2 - m4;
break;
case 44:
m2 = m2 - m5;
break;
case 45:
m2 = m2 - m6;
break;
case 46:
m2 = m2 - m7;
break;
case 47:
m2 = m2 - m8;
break;
case 48:
m2 = m2 * m1;
break;
case 49:
m2 = m2 * m2;
break;
case 50:
m2 = m2 * m3;
break;
case 51:
m2 = m2 * m4;
break;
case 52:
m2 = m2 * m5;
break;
case 53:
m2 = m2 * m6;
break;
case 54:
m2 = m2 * m7;
break;
case 55:
m2 = m2 * m8;
break;
case 56:
m2 = m2 / m1;
break;
case 57:
m2 = m2 / m2;
break;
case 58:
m2 = m2 / m3;
break;
case 59:
m2 = m2 / m4;
break;
case 60:
m2 = m2 / m5;
break;
case 61:
m2 = m2 / m6;
break;
case 62:
m2 = m2 / m7;
break;
case 63:
m2 = m2 / m8;
break;
case 64:
m3 = m3 + m1;
break;  
case 65:
m3 = m3 + m2;
break;
case 66:
m3 = m3 + m3;
case 67:
m3 = m3 + m4;
break;
case 68:
m3 = m3 + m5;
break;
case 69:
m3 = m3 + m6;
break;
case 70:
m3 = m3 + m7;
break;
case 71:
m3 = m3 + m8;
break;
case 72:
m3 = m3 - m1;
break;
case 73:
m3 = m3 - m2;
break;
case 74:
m3 = m3 - m3;
break;
case 75:
m3 = m3 - m4;
break;
case 76:
m3 = m3 - m5;
break;
case 77:
m3 = m3 - m6;
break;
case 78:
m3 = m3 - m7;
break;
case 79:
m3 = m3 - m8;
break;
case 80:
m3 = m3 * m1;
break;
case 81:
m3 = m3 * m2;
break;
case 82:
m3 = m3 * m3;
break;
case 83:
m3 = m3 * m4;
break;
case 84:
m3 = m3 * m5;
break;
case 85:
m3 = m3 * m6;
break;
case 86:
m3 = m3 * m7;
break;
case 87:
m3 = m3 * m8;
break;
case 88:
m3 = m3 / m1;
break;
case 89:
m3 = m3 / m2;
break;
case 90:
m3 = m3 / m3;
break;
case 91:
m3 = m3 / m4;
break;
case 92:
m3 = m3 / m5;
break;
case 93:
m3 = m3 / m6;
break;
case 94:
m3 = m3 / m7;
break;
case 95:
m3 = m3 / m8;
break;
case 96:
m4 = m4 + m1;
break;  
case 97:
m4 = m4 + m2;
break;
case 98:
m4 = m4 + m3;
case 99:
m4 = m4 + m4;
break;
case 100:
m4 = m4 + m5;
break;
case 101:
m4 = m4 + m6;
break;
case 102:
m4 = m4 + m7;
break;
case 103:
m4 = m4 + m8;
break;
case 104:
m4 = m4 - m1;
break;
case 105:
m4 = m4 - m2;
break;
case 106:
m4 = m4 - m3;
break;
case 107:
m4 = m4 - m4;
break;
case 108:
m4 = m4 - m5;
break;
case 109:
m4 = m4 - m6;
break;
case 110:
m4 = m4 - m7;
break;
case 111:
m4 = m4 - m8;
break;
case 112:
m4 = m4 * m1;
break;
case 113:
m4 = m4 * m2;
break;
case 114:
m4 = m4 * m3;
break;
case 115:
m4 = m4 * m4;
break;
case 116:
m4 = m4 * m5;
break;
case 117:
m4 = m4 * m6;
break;
case 118:
m4 = m4 * m7;
break;
case 119:
m4 = m4 * m8;
break;
case 120:
m4 = m4 / m1;
break;
case 121:
m4 = m4 / m2;
break;
case 122:
m4 = m4 / m3;
break;
case 123:
m4 = m4 / m4;
break;
case 124:
m4 = m4 / m5;
break;
case 125:
m4 = m4 / m6;
break;
case 126:
m4 = m4 / m7;
break;
case 127:
m4 = m4 / m8;
break;
case 128:
m5 = m5 + m1;
break;  
case 129:
m5 = m5 + m2;
break;
case 130:
m5 = m5 + m3;
case 131:
m5 = m5 + m4;
break;
case 132:
m5 = m5 + m5;
break;
case 133:
m5 = m5 + m6;
break;
case 134:
m5 = m5 + m7;
break;
case 135:
m5 = m5 + m8;
break;
case 136:
m5 = m5 - m1;
break;
case 137:
m5 = m5 - m2;
break;
case 138:
m5 = m5 - m3;
break;
case 139:
m5 = m5 - m4;
break;
case 140:
m5 = m5 - m5;
break;
case 141:
m5 = m5 - m6;
break;
case 142:
m5 = m5 - m7;
break;
case 143:
m5 = m5 - m8;
break;
case 144:
m5 = m5 * m1;
break;
case 145:
m5 = m5 * m2;
break;
case 146:
m5 = m5 * m3;
break;
case 147:
m5 = m5 * m4;
break;
case 148:
m5 = m5 * m5;
break;
case 149:
m5 = m5 * m6;
break;
case 150:
m5 = m5 * m7;
break;
case 151:
m5 = m5 * m8;
break;
case 152:
m5 = m5 / m1;
break;
case 153:
m5 = m5 / m2;
break;
case 154:
m5 = m5 / m3;
break;
case 155:
m5 = m5 / m4;
break;
case 156:
m5 = m5 / m5;
break;
case 157:
m5 = m5 / m6;
break;
case 158:
m5 = m5 / m7;
break;
case 159:
m5 = m5 / m8;
break;
case 160:
m6 = m6 + m1;
break;  
case 161:
m6 = m6 + m2;
break;
case 162:
m6 = m6 + m3;
case 163:
m6 = m6 + m4;
break;
case 164:
m6 = m6 + m5;
break;
case 165:
m6 = m6 + m6;
break;
case 166:
m6 = m6 + m7;
break;
case 167:
m6 = m6 + m8;
break;
case 168:
m6 = m6 - m1;
break;
case 169:
m6 = m6 - m2;
break;
case 170:
m6 = m6 - m3;
break;
case 171:
m6 = m6 - m4;
break;
case 172:
m6 = m6 - m5;
break;
case 173:
m6 = m6 - m6;
break;
case 174:
m6 = m6 - m7;
break;
case 175:
m6 = m6 - m8;
break;
case 176:
m6 = m6 * m1;
break;
case 177:
m6 = m6 * m2;
break;
case 178:
m6 = m6 * m3;
break;
case 179:
m6 = m6 * m4;
break;
case 180:
m6 = m6 * m5;
break;
case 181:
m6 = m6 * m6;
break;
case 182:
m6 = m6 * m7;
break;
case 183:
m6 = m6 * m8;
break;
case 184:
m6 = m6 / m1;
break;
case 185:
m6 = m6 / m2;
break;
case 186:
m6 = m6 / m3;
break;
case 187:
m6 = m6 / m4;
break;
case 188:
m6 = m6 / m5;
break;
case 189:
m6 = m6 / m6;
break;
case 190:
m6 = m6 / m7;
break;
case 191:
m6 = m6 / m8;
break;
case 192:
m7 = m7 + m1;
break;  
case 193:
m7 = m7 + m2;
break;
case 194:
m7 = m7 + m3;
case 195:
m7 = m7 + m4;
break;
case 196:
m7 = m7 + m5;
break;
case 197:
m7 = m7 + m6;
break;
case 198:
m7 = m7 + m7;
break;
case 199:
m7 = m7 + m8;
break;
case 200:
m7 = m7 - m1;
break;
case 201:
m7 = m7 - m2;
break;
case 202:
m7 = m7 - m3;
break;
case 203:
m7 = m7 - m4;
break;
case 204:
m7 = m7 - m5;
break;
case 205:
m7 = m7 - m6;
break;
case 206:
m7 = m7 - m7;
break;
case 207:
m7 = m7 - m8;
break;
case 208:
m7 = m7 * m1;
break;
case 209:
m7 = m7 * m2;
break;
case 210:
m7 = m7 * m3;
break;
case 211:
m7 = m7 * m4;
break;
case 212:
m7 = m7 * m5;
break;
case 213:
m7 = m7 * m6;
break;
case 214:
m7 = m7 * m7;
break;
case 215:
m7 = m7 * m8;
break;
case 216:
m7 = m7 / m1;
break;
case 217:
m7 = m7 / m2;
break;
case 218:
m7 = m7 / m3;
break;
case 219:
m7 = m7 / m4;
break;
case 220:
m7 = m7 / m5;
break;
case 221:
m7 = m7 / m6;
break;
case 222:
m7 = m7 / m7;
break;
case 223:
m7 = m7 / m8;
break;
case 224:
m8 = m8 + m1;
break;  
case 225:
m8 = m8 + m2;
break;
case 226:
m8 = m8 + m3;
case 227:
m8 = m8 + m4;
break;
case 228:
m8 = m8 + m5;
break;
case 229:
m8 = m8 + m6;
break;
case 230:
m8 = m8 + m7;
break;
case 231:
m8 = m8 + m8;
break;
case 232:
m8 = m8 - m1;
break;
case 233:
m8 = m8 - m2;
break;
case 234:
m8 = m8 - m3;
break;
case 235:
m8 = m8 - m4;
break;
case 236:
m8 = m8 - m5;
break;
case 237:
m8 = m8 - m6;
break;
case 238:
m8 = m8 - m7;
break;
case 239:
m8 = m8 - m8;
break;
case 240:
m8 = m8 * m1;
break;
case 241:
m8 = m8 * m2;
break;
case 242:
m8 = m8 * m3;
break;
case 243:
m8 = m8 * m4;
break;
case 244:
m8 = m8 * m5;
break;
case 245:
m8 = m8 * m6;
break;
case 246:
m8 = m8 * m7;
break;
case 247:
m8 = m8 * m8;
break;
case 248:
m8 = m8 / m1;
break;
case 249:
m8 = m8 / m2;
break;
case 250:
m8 = m8 / m3;
break;
case 251:
m8 = m8 / m4;
break;
case 252:
m8 = m8 / m5;
break;
case 253:
m8 = m8 / m6;
break;
case 254:
m8 = m8 / m7;
break;
case 255:
m8 = m8 / m8;
break;        
}            
}

//scaling of motorcodes
 motorkod1[b] = constrain(m1, -200, 200);
 motorkod2[b] = constrain(m2, -200, 200);
 motorkod3[b] = constrain(m3, -200, 200);
 motorkod4[b] = constrain(m4, -200, 200);
 motorkod5[b] = constrain(m5, -200, 200);
 motorkod6[b] = constrain(m6, -200, 200);
 motorkod7[b] = constrain(m7, -200, 200);
 motorkod8[b] = constrain(m8, -200, 200);

 motorkod1[b] = map(motorkod1[b], -200, 200, 10, 170);
 motorkod2[b] = map(motorkod2[b], -200, 200, 10, 170);
 motorkod3[b] = map(motorkod3[b], -200, 200, 10, 170);
 motorkod4[b] = map(motorkod4[b], -200, 200, 10, 170);
 motorkod5[b] = map(motorkod5[b], -200, 200, 10, 170);
 motorkod6[b] = map(motorkod6[b], -200, 200, 10, 170);
 motorkod7[b] = map(motorkod7[b], -200, 200, 10, 170);
 motorkod8[b] = map(motorkod8[b], -200, 200, 10, 170);

}

}
//----------------------------------------------------------------------------
void run_individ()
{
 Serial.println("Code is now inside run individ ");
 /* empty mouse before run individ */
 int i = 0;  
 for(i=0;i<40;i++)
      {
       
        mouse.write(0xeb);  
        mouse.read();      
        mstat = mouse.read();
        mx = mouse.read();
        my = mouse.read();
        //Serial.println(my);
        delay(50);
       }
      
 dist = 0;
 my = 0;
 mstat = 0;
 
 int b=0; 
      for(b=0;b<5;b++)
      {
      servo1.write(90);
      servo2.write(90);
      servo3.write(90);
      servo4.write(90);
      servo5.write(90);
      servo6.write(90);
      servo7.write(90);
      servo8.write(90);
      int a;
      a = 0; 
      for (a = 0; a<4; a++)
            {           
            servo1.write(motorkod1[a]);
            servo2.write(motorkod2[a]);
            servo3.write(motorkod3[a]);
            servo4.write(motorkod4[a]);
            servo5.write(motorkod5[a]);
            servo6.write(motorkod6[a]);
            servo7.write(motorkod7[a]);
            servo8.write(motorkod8[a]);
      
            read_mouse();
            //Serial.print("distance so far: ");
            //Serial.println(dist);    
            }
delay(100);            
      }
      
//Now all 4 motorcodes have been run 6 laps and is summoned into y_dist
//store y_dist for individ
 Serial.print("total distance: ");
 Serial.println(dist);
 fitness_of_individs[individ_to_tolken] = dist; 
   servo1.write(90);
   servo2.write(90);
   servo3.write(90);
   servo4.write(90);
   servo5.write(90);
   servo6.write(90);
   servo7.write(90);
   servo8.write(90);


   //time to align the robot to starting position
 tebax2:
 Serial.println("Put the robot in starting position and press r!");           
 while(Serial.available() == 0)
         {
          delay(100);
          }  

          
 inChar = (char)Serial.read();
              if(inChar  == 'r')
                    {
                      Serial.println("robot is now running!");   
                      dump = (char)Serial.read();
                      dump = (char)Serial.read();                        
                      delay(100);  
                      int i = 0;  
                      for(i=0;i<100;i++)
                            {
                             
                              mouse.write(0xeb);  
                              mouse.read();      
                              mstat = mouse.read();
                              mx = mouse.read();
                              my = mouse.read();
                              Serial.println(my);
                              delay(50);
                            }
  
                      }         
              
              if   (inChar!='r')
                    {    
                      Serial.println("incomplete answer, try again");  
                      dump = (char)Serial.read(); 
                      dump = (char)Serial.read(); 
                      delay(100);  
                      goto tebax2;
                    }  
        


          
}

//----------------------------------------------------------------------------
void read_mouse()
{
 int i=0;  
 for(i=0;i<8;i++)
      {
        /* get a reading from the mouse */
        mouse.write(0xeb);  // give me data!
        mouse.read();      // ignore ack
        mstat = mouse.read();
        mx = mouse.read();
       
        my = mouse.read();

        //Serial.print(mstat, BIN);
        //Serial.print("\tX=");
        left = bitRead(mstat, 4);
        if (left == 1)
              {
                mx = mx * -1;
              }
        //Serial.print(mx);
        //Serial.print("\tY=");
        down = bitRead(mstat, 5);
        if (down == 1)
              {
                my = my * -1;
              }
        if(my < -127)
              {
               //Serial.print("y var:  ");
               //Serial.println(my);
               //Serial.print("y korrigeras till: ");
                
               my = 0;
               //Serial.print(my); 
              }
        if(my > 127)
              {
               //Serial.print("y var:  ");
               //Serial.println(my);
               //Serial.print("y korrigeras till: ");
                
               my = 0;
               //Serial.print(my);   
              }
        //Serial.print("y= ");
        //Serial.println(my);
        //Serial.println();        
        dist = my + dist;
        delay(100);
       }
}
//---------------------------------------------------------------------------
 void print_motorkod()
 {
 int b = 0;       
      for (b = 0; b<4; b++){
            Serial.print("motorkod1: "); 
            Serial.println(motorkod1[b]);
            Serial.print("motorkod2: "); 
            Serial.println(motorkod2[b]);
            Serial.print("motorkod3: "); 
            Serial.println(motorkod3[b]);
            Serial.print("motorkod4: "); 
            Serial.println(motorkod4[b]);
            Serial.print("motorkod5: "); 
            Serial.println(motorkod5[b]);
            Serial.print("motorkod6: "); 
            Serial.println(motorkod6[b]);
            Serial.print("motorkod7: "); 
            Serial.println(motorkod7[b]);
            Serial.print("motorkod8: "); 
            Serial.println(motorkod8[b]);
      }
 }
//---------------------------------------------------------------------------
void rank_monkeys(){
//determine the rang of the four monkeys
if(fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[1]] && fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[2]] && fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[3]]){
       rang_of_monkeys[0] = four_monkeys[0];
       
       if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[2]] && fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[3]]){
               rang_of_monkeys[1] = four_monkeys[1];
               if(fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[3]]){
                     rang_of_monkeys[2] = four_monkeys[2];
                     rang_of_monkeys[3] = four_monkeys[3];      
               }
               if(fitness_of_individs[four_monkeys[3]] > fitness_of_individs[four_monkeys[2]]){
                     rang_of_monkeys[2] = four_monkeys[3];
                     rang_of_monkeys[3] = four_monkeys[2];
               }            
       
       }
       if(fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[1]] && fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[3]]){
               rang_of_monkeys[1] = four_monkeys[2]; 
               if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[3]]){
                     rang_of_monkeys[2] = four_monkeys[1];
                     rang_of_monkeys[3] = four_monkeys[3];      
               }
               if(fitness_of_individs[four_monkeys[3]] > fitness_of_individs[four_monkeys[1]]){
                     rang_of_monkeys[2] = four_monkeys[3];
                     rang_of_monkeys[3] = four_monkeys[1];
               }   
       }
       if(fitness_of_individs[four_monkeys[3]] >= fitness_of_individs[four_monkeys[1]] && fitness_of_individs[four_monkeys[3]] >= fitness_of_individs[four_monkeys[2]]){
               rang_of_monkeys[1] = four_monkeys[3];         
               if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[2]]){
                     rang_of_monkeys[2] = four_monkeys[1];
                     rang_of_monkeys[3] = four_monkeys[2];      
               }
               if(fitness_of_individs[four_monkeys[2]] > fitness_of_individs[four_monkeys[1]]){
                     rang_of_monkeys[2] = four_monkeys[2];
                     rang_of_monkeys[3] = four_monkeys[1];
               }   
       }        
}

if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[0]] && fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[2]] && fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[3]]){
       rang_of_monkeys[0] = four_monkeys[1];
       
       if(fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[2]] && fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[3]]){
               rang_of_monkeys[1] = four_monkeys[0];
               if(fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[3]]){
                     rang_of_monkeys[2] = four_monkeys[2];
                     rang_of_monkeys[3] = four_monkeys[3];      
               }
               if(fitness_of_individs[four_monkeys[3]] > fitness_of_individs[four_monkeys[2]]){
                     rang_of_monkeys[2] = four_monkeys[3];
                     rang_of_monkeys[3] = four_monkeys[2];
               }            
       
       }
       if(fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[0]] && fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[3]]){
               rang_of_monkeys[1] = four_monkeys[2]; 
               if(fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[3]]){
                     rang_of_monkeys[2] = four_monkeys[0];
                     rang_of_monkeys[3] = four_monkeys[3];      
               }
               if(fitness_of_individs[four_monkeys[3]] > fitness_of_individs[four_monkeys[0]]){
                     rang_of_monkeys[2] = four_monkeys[3];
                     rang_of_monkeys[3] = four_monkeys[0];
               }   
       }
       if(fitness_of_individs[four_monkeys[3]] >= fitness_of_individs[four_monkeys[0]] && fitness_of_individs[four_monkeys[3]] >= fitness_of_individs[four_monkeys[2]]){
               rang_of_monkeys[1] = four_monkeys[3];         
               if(fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[2]]){
                     rang_of_monkeys[2] = four_monkeys[0];
                     rang_of_monkeys[3] = four_monkeys[2];      
               }
               if(fitness_of_individs[four_monkeys[2]] > fitness_of_individs[four_monkeys[0]]){
                     rang_of_monkeys[2] = four_monkeys[2];
                     rang_of_monkeys[3] = four_monkeys[0];
               }   
       }      
}

if(fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[0]] && fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[1]] && fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[3]]){
       rang_of_monkeys[0] = four_monkeys[2];
       
       if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[0]] && fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[3]]){
               rang_of_monkeys[1] = four_monkeys[1];
               if(fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[3]]){
                     rang_of_monkeys[2] = four_monkeys[0];
                     rang_of_monkeys[3] = four_monkeys[3];      
               }
               if(fitness_of_individs[four_monkeys[3]] > fitness_of_individs[four_monkeys[0]]){
                     rang_of_monkeys[2] = four_monkeys[3];
                     rang_of_monkeys[3] = four_monkeys[0];
               }            
       
       }
       if(fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[1]] && fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[3]]){
               rang_of_monkeys[1] = four_monkeys[0]; 
               if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[3]]){
                     rang_of_monkeys[2] = four_monkeys[1];
                     rang_of_monkeys[3] = four_monkeys[3];      
               }
               if(fitness_of_individs[four_monkeys[3]] > fitness_of_individs[four_monkeys[1]]){
                     rang_of_monkeys[2] = four_monkeys[3];
                     rang_of_monkeys[3] = four_monkeys[1];
               }   
       }
       if(fitness_of_individs[four_monkeys[3]] >= fitness_of_individs[four_monkeys[1]] && fitness_of_individs[four_monkeys[3]] >= fitness_of_individs[four_monkeys[0]]){
               rang_of_monkeys[1] = four_monkeys[3];         
               if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[0]]){
                     rang_of_monkeys[2] = four_monkeys[1];
                     rang_of_monkeys[3] = four_monkeys[0];      
               }
               if(fitness_of_individs[four_monkeys[0]] > fitness_of_individs[four_monkeys[1]]){
                     rang_of_monkeys[2] = four_monkeys[0];
                     rang_of_monkeys[3] = four_monkeys[1];
               }   
       }        
}

if(fitness_of_individs[four_monkeys[3]] >= fitness_of_individs[four_monkeys[0]] && fitness_of_individs[four_monkeys[3]] >= fitness_of_individs[four_monkeys[1]] && fitness_of_individs[four_monkeys[3]] >= fitness_of_individs[four_monkeys[2]]){
       rang_of_monkeys[0] = four_monkeys[3];
       
       if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[0]] && fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[2]]){
               rang_of_monkeys[1] = four_monkeys[1];
               if(fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[2]]){
                     rang_of_monkeys[2] = four_monkeys[0];
                     rang_of_monkeys[3] = four_monkeys[2];      
               }
               if(fitness_of_individs[four_monkeys[2]] > fitness_of_individs[four_monkeys[0]]){
                     rang_of_monkeys[2] = four_monkeys[2];
                     rang_of_monkeys[3] = four_monkeys[0];
               }            
       
       }
       if(fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[1]] && fitness_of_individs[four_monkeys[0]] >= fitness_of_individs[four_monkeys[2]]){
               rang_of_monkeys[1] = four_monkeys[0]; 
               if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[2]]){
                     rang_of_monkeys[2] = four_monkeys[1];
                     rang_of_monkeys[3] = four_monkeys[2];      
               }
               if(fitness_of_individs[four_monkeys[2]] > fitness_of_individs[four_monkeys[1]]){
                     rang_of_monkeys[2] = four_monkeys[2];
                     rang_of_monkeys[3] = four_monkeys[1];
               }   
       }
       if(fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[1]] && fitness_of_individs[four_monkeys[2]] >= fitness_of_individs[four_monkeys[0]]){
               rang_of_monkeys[1] = four_monkeys[2];         
               if(fitness_of_individs[four_monkeys[1]] >= fitness_of_individs[four_monkeys[0]]){
                     rang_of_monkeys[2] = four_monkeys[1];
                     rang_of_monkeys[3] = four_monkeys[0];      
               }
               if(fitness_of_individs[four_monkeys[0]] > fitness_of_individs[four_monkeys[1]]){
                     rang_of_monkeys[2] = four_monkeys[0];
                     rang_of_monkeys[3] = four_monkeys[1];
               }   
       }        
}
int a = 0;


 for(a=0;a<4;a++){ 
 Serial.print("apa nr");
 Serial.print(a+1);
 Serial.print(": ");
 Serial.println(four_monkeys[a]);
 }

for(a=0;a<4;a++){
 Serial.print("fitness apa nr ");
 Serial.print(a+1);
 Serial.print("= ");
 Serial.println(fitness_of_individs[four_monkeys[a]]);
}

a = 0;
Serial.println("rang of apor: ");
for(a=0;a<4;a++){
 Serial.print("rang nr ");
 Serial.print(a+1);
 Serial.print(" är apa id nr: ");
 Serial.println(rang_of_monkeys[a]);
}
} 
//----------------------------------------------------------------------------
void choose_four(){
 four_monkeys[0] = random(0,49);
 four_monkeys[1] = random(0,49);
 while (four_monkeys[1] == four_monkeys[0])
      {
      four_monkeys[1] = random(0,49);
      }
 four_monkeys[2] = random(0,49); 
 while (four_monkeys[2] == four_monkeys[0] || four_monkeys[2] == four_monkeys[1])
      {
      four_monkeys[2] = random(0,49);
      }
 four_monkeys[3] = random(0,49);
 while (four_monkeys[3] == four_monkeys[0] || four_monkeys[3] == four_monkeys[1] || four_monkeys[3] == four_monkeys[2])
      {
      four_monkeys[3] = random(0,49);
      }
}


//----------------------------------------------------------------------------
void find_best()
{
 byte a = 0;
 maxvalue = 0;
 for(a=0;a<50;a++)
      {
      maxvalue = max(maxvalue, fitness_of_individs[a]);
      }
 a=0;
 for(a=0;a<50;a++)
      {
      if(maxvalue == fitness_of_individs[a])
            {
             index_of_maxvalue = a;        
            }
      }  
}
//---------------------------------------------------------------------------
void run_ten_times(){
 Serial.println("The best monkey is now runned ten times!"); 
 byte lap = 0;
 for(lap=0;lap<10;lap++)
       {
        Serial.print("Lap number: ");
        Serial.print(lap);
        Serial.println("of 10");
        byte b=0; 
              for(b=0;b<6;b++)
                    {
                      servo1.write(90);
                      servo2.write(90);
                      servo3.write(90);
                      servo4.write(90);
                      servo5.write(90);
                      servo6.write(90);
                      servo7.write(90);
                      servo8.write(90);
                      byte a;
                      a = 0; 
                      for (a = 0; a<4; a++)
                            {           
                              servo1.write(motorkod1[a]);
                              servo2.write(motorkod2[a]);
                              servo3.write(motorkod3[a]);
                              servo4.write(motorkod4[a]);
                              servo5.write(motorkod5[a]);
                              servo6.write(motorkod6[a]);
                              servo7.write(motorkod7[a]);
                              servo8.write(motorkod8[a]); 
                              delay(900);   
                            }
                      delay(500);            
                     } 
      }
}
//----------------------------------------------------------------------------
void loop() {

//1. choose four individs 
//2. evaluate fitness of the four individs
//3. let the two best get 2 babys 
//4. replace the two worst individs with the two babys
//5. mutate one parent

//6. pause the program when the best individ performs > 1000, print the motorcodes and run this individ for 10 laps


 Serial.println("");
 Serial.println("Starting the loop!!!");
//----------------------------------------------------------------
//1. choose four individs  (monkeys) 
 choose_four(); 
 if(firstrun == true)
      {
        four_monkeys[0]=12; //best so far
        four_monkeys[1]=33; //second best so far
        firstrun = false;
      }
 
 byte a = 0;
 for(a=0;a<4;a++)
      { 
        Serial.print("monkey nr");
        Serial.print(a+1);
        Serial.print(": ");
        Serial.println(four_monkeys[a]);
      }
 delay(1000);
 //--------------------------------------------------------------------------
//2. evaluate fitness of the four individs (monkeys)
//"individ_to_tolken"  is the individ that should be sent to tolken and then runned
 //Serial.println(" before tolken:");
 //print_ms();
 a = 0;
 for(a=0; a<4;a++)
      {
        individ_to_tolken = four_monkeys[a];
        Serial.print("individ now running: ");
        Serial.println(individ_to_tolken);      
        tolken();
        //Serial.println("after tolken: ");
        //print_motorkod();
        run_individ();
      } 
//rang monkeys
 rank_monkeys();
//--------------------------------------------------------------------------
//3A   this steps accelerates the start of the evolution
//if all monkeys perform = 0 -> randomly construct 4 new individs
 if(fitness_of_individs[rang_of_monkeys[0]] == 0) 
      {
        a = 0;
        for (a = 0; a < 50; a++)
            {
              individ[rang_of_monkeys[0]][a] = 0;
              individ[rang_of_monkeys[1]][a] = 0;
              individ[rang_of_monkeys[2]][a] = 0;
              individ[rang_of_monkeys[3]][a] = 0;
            }
        a = 0;
        for (a = 0; a < 20; a++)
            {
              individ[rang_of_monkeys[0]][a] = random(0,255);
              individ[rang_of_monkeys[1]][a] = random(0,255);
              individ[rang_of_monkeys[2]][a] = random(0,255);
              individ[rang_of_monkeys[3]][a] = random(0,255);
            }    

       goto steg6;     
      }

      
//3B: if the individ that is second best = 0 -> randomly construct new individs to rank 1 and 2, copy the best one to 3 and mutate this one. 

 if(fitness_of_individs[rang_of_monkeys[1]] == 0)
      {
        a = 0;
        for (a = 0; a < 50; a++)
            {              
              individ[rang_of_monkeys[1]][a] = 0;
              individ[rang_of_monkeys[2]][a] = 0;
              individ[rang_of_monkeys[3]][a] = 0;
            }

        
        a = 0;
        for (a = 0; a < 20; a++)
            {              
              individ[rang_of_monkeys[1]][a] = random(0,255);    
              individ[rang_of_monkeys[2]][a] = random(0,255);
              individ[rang_of_monkeys[3]][a] = individ[rang_of_monkeys[0]][a];        
            }     
          individ_to_mutate = rang_of_monkeys[3];
          mutate();
          mutate();
          mutate();
          goto steg6;  

             
      }




//3C. let the two best have babys 
 id_of_parent1 = rang_of_monkeys[0];
 id_of_parent2 = rang_of_monkeys[1];
 Serial.print("parent 1 is: ");
 Serial.println(id_of_parent1);
 Serial.print("parent 2 is: ");
 Serial.println(id_of_parent2);
 make_2babys();
//---------------------------------------------------------------------------
//4. replace the two worst with the babys
 a = 0;
 for (a = 0; a < 50; a++)
       {
        individ[rang_of_monkeys[2]][a] = baby_1[a];
        individ[rang_of_monkeys[3]][a] = baby_2[a];
       }
//---------------------------------------------------------------------------
//5. mutate one parent
 individ_to_mutate = rang_of_monkeys[1];
 mutate();
//---------------------------------------------------------------------------
steg6:
//clean the mouse
int i = 0;  
                      for(i=0;i<30;i++)
                            {
                             
                              mouse.write(0xeb);  
                              mouse.read();      
                              mstat = mouse.read();
                              mx = mouse.read();
                              my = mouse.read();
                              //Serial.println(my);
                              delay(100);
                            }
  

//6. stop when the best is > 1000
 find_best(); 
 if(maxvalue > 1000)
      {
       Serial.println(""); 
       Serial.println("one individ is better than 1000!");
       Serial.print("best is monkey number: ");
       Serial.println(index_of_maxvalue);
       Serial.print("The monkey performs: ");
       Serial.println(maxvalue);               
       
       tebax:
              Serial.println("run this individ for 10 laps? (y/n)");           
              while(Serial.available() == 0)
                    {
                     delay(100);
                    }
              inChar = (char)Serial.read();
              if(inChar  == 'y')
                    {
                      Serial.println("yes recieved");   
                      dump = (char)Serial.read();
                      dump = (char)Serial.read();                        
                      delay(1000);    
                      Serial.print("Individ: ");
                      Serial.print(index_of_maxvalue);
                      individ_to_tolken = index_of_maxvalue;
                      tolken();   
                      Serial.println("Motorcodes of the best monkey: ");             
                      print_motorkod();
                      run_ten_times();   
                    }
              if(inChar == 'n')
                    {
                      Serial.println("no recieved");
                      dump = (char)Serial.read(); 
                      dump = (char)Serial.read();                       
                      delay(1000);      
                    }
              if   (inChar!='y'&&inChar !='n' )
                    {    
                      Serial.println("incomplete answer, try again");  
                      dump = (char)Serial.read(); 
                      dump = (char)Serial.read(); 
                      delay(1000);  
                      goto tebax;  
                    }
              
               
      }

  Serial.print("best is monkey number: ");
       Serial.println(index_of_maxvalue);
       Serial.print("monkey performs: ");
       Serial.println(maxvalue);      
 Serial.println("");
 individ_to_print = index_of_maxvalue;
 printIndivid();
 Serial.println("");
 a = 0;
 for(a=0;a<50;a++)
      {
        
        Serial.print("Monkey number: ");
        Serial.print(a);
        Serial.print("   has performed: ");
        Serial.print(fitness_of_individs[a]);   
        Serial.print("   Length: ");
        Serial.println(length_of_individ[a]);
        
        
      }
 byte b=0;
 for(b=0; b<50;b++)
      {
       Serial.print(" {");
       a=0;
       for ( a = 0; a < 50; a++)
            {  
              Serial.print(individ[b][a]); 
              if(a < 49)
                    {
                     Serial.print(","); 
                    }
              
            }
       Serial.print("}");
       if(b<49)
            {
              Serial.print(", ");
            }
       
      }
           
 Serial.println("OK, now the code is runned from start of the loop!");      
}


  



