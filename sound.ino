#define NTD0 0

// low
#define NTDL1 262 // NOTE_C4  262  L1
#define NTDL2 294 // NOTE_D4  294  L2
#define NTDL3 330 // NOTE_E4  330  L3
#define NTDL4 349 // NOTE_F4  349  L4
#define NTDL5 392 // NOTE_G4  392  L5
#define NTDL6 440 // NOTE_A4  440  L6
#define NTDL7 494 // NOTE_B4  494  L7

#define NTD1 523 // NOTE_C5  523   1
#define NTD2 587 // NOTE_D5  587   2
#define NTD3 659 // NOTE_E5  659   3
#define NTD4 698 // NOTE_F5  698   4
#define NTD5 784 // NOTE_G5  784   5
#define NTD6 880 // NOTE_A5  880   6
#define NTD7 988 // NOTE_B5  988   7

// high 
#define NTDH1 1047 // NOTE_C6  1047  H1
#define NTDH2 1175 // NOTE_D6  1175  H2
#define NTDH3 1319 // NOTE_E6  1319  H3
#define NTDH4 1397 // NOTE_F6  1397  H4
#define NTDH5 1568 // NOTE_G6  1568  H5
#define NTDH6 1760 // NOTE_A6  1760  H6
#define NTDH7 1976 // NOTE_B6  1976  H7


// notes in the melody:
int melody[] = {NTDH1,NTDH3,NTDH2,NTD5,NTDH1,NTDH2,NTDH3,NTDH1};
/*
  //1   2      3    1      5 .     3      2     5     2    1    6   3.
 NTD1, NTD2, NTD3, NTD1, NTD5, NTD3, NTD2, NTD5, NTD2, NTD1, NTDL6, NTD3,
  //1     7     0     1     7     6     7     1     2     5     1     2
 NTD1, NTDL7, NTD0, NTD1, NTDL7, NTDL6, NTDL7,NTD1, NTD2, NTDL5, NTD1, NTD2,
 // 3     4     4     3     2     1     2
 NTD3, NTD4, NTD4, NTD3, NTD2, NTD1, NTD2,
   //1   2      3    1      5 .     3   2    5    2     1     6    6    7   1     5 
 NTD1, NTD2, NTD3, NTD1, NTD5, NTD3, NTD2, NTD5, NTD2, NTD1, NTDL6, NTDL6,NTDL7,NTD1,NTDL5,
  //0    5    6      7     1      2     5     1     2     
 NTD0, NTDL5, NTDL6, NTDL7, NTD1, NTD2, NTDL5, NTD1, NTD2,
 // 3     4     4     3     2     1     1
 NTD3, NTD4, NTD4, NTD3, NTD2, NTD1, NTD1,
 // 3  4     5     5    5     5     5    6      5     4      3    3      3     3        
 NTD3, NTD4, NTD5, NTD5, NTD5,NTD5, NTD5, NTD6, NTD5, NTD4, NTD3, NTD3, NTD3, NTD3,
 //3   4     3     2      1      1    1    7      6         0      7      7     1    2    2    3  2    3    2    
 NTD3, NTD4, NTD3, NTD2, NTD1, NTD1, NTD1, NTDL7, NTDL6, NTD0, NTDL7, NTDL7, NTD1,NTD2,NTD2,NTD3,NTD2,NTD3,NTD2,
 //3   4      5      5     5    5     5      6    5     4     3     3   3   3     4     3    2   1    7     6     0      6      7    1    2    5    1    2    3
 NTD3, NTD4, NTD5, NTD5, NTD5, NTD5, NTD5, NTD6, NTD5, NTD4, NTD3,NTD3,NTD3,NTD3,NTD4,NTD3,NTD2,NTD1,NTDL7,NTDL6,NTD0,NTDL6,NTDL7,NTD1,NTD2,NTDL5,NTD1,NTD2,NTD3,
 //2.   2      2     1     1      0    0      0       0    0      0 
 NTD2, NTD2, NTD2, NTD1, NTD1, NTD0, NTD0, NTD0, NTD0, NTD0,NTD0,
 //高音重复
   //1   2      3    1      5 .     3      2     5     2    1    6   3.
 NTDH1, NTDH2, NTDH3, NTDH1, NTDH5, NTDH3, NTDH2, NTDH5, NTDH2, NTDH1, NTD6, NTDH3,
  //1     7     0     1     7     6     7     1     2     5     1     2
 NTDH1, NTD7, NTD0, NTDH1, NTD7, NTD6, NTD7,NTDH1, NTDH2, NTD5, NTDH1, NTDH2,
 // 3     4     4     3     2     1     2
 NTDH3, NTDH4, NTDH4, NTDH3, NTDH2, NTDH1, NTDH2,
   //1   2      3    1      5 .     3   2    5    2     1     6    6    7   1     5 
 NTDH1, NTDH2, NTDH3, NTDH1, NTDH5, NTDH3, NTDH2, NTDH5, NTDH2, NTDH1, NTD6, NTD6,NTD7,NTDH1,NTD5,
  //0    5    6      7     1      2     5     1     2     
 NTD0, NTD5, NTD6, NTD7, NTDH1, NTDH2, NTD5, NTDH1, NTDH2,
 // 3     4     4     3     2     1     1
 NTDH3, NTDH4, NTDH4, NTDH3, NTDH2, NTDH1, NTDH1
 };
*/
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] =
{4,4,4,8,4,4,4,8};
/*{
 //12  3  1  5 .3  2  5  2  1  6  3. 
 2, 2, 2, 2, 4, 2, 4, 4, 4, 2, 2, 4, 
//1 7  0  1  7  6  7  1  2  5  1  2
 4, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2,
//3 4  4  3  2  1  2
 2, 4, 2, 2, 2, 2, 8, 
//1 2  3  1  5 .3  2  5  2  1  6  6  7  1  5 
 2, 2, 2, 2, 4, 2, 4, 4, 4, 2, 2, 4, 2,2,4,
//0 5  6  7  1  2  5  1  2 
  2,2, 4, 4, 2, 2, 4, 4, 2,
//3 4  4  3  2  1  1
 2, 4, 2, 2, 2, 2, 8,
 // 3 4 5 5  5  5  5  6  5  4  3   3  3  3        
2,2,4,4,4,4,2,2,2,2,4,4,4,4,
 //3 4  3  2  1  1  1  7  6  0  7   7  1 2 2  3 2 3  2    
   2,2,2,  2, 4 ,4, 2, 2, 2, 2, 4,  2, 2,4,2, 2,2,2, 8,
 //3 4 5 5 5 5 5 6 5 4 3 3 3 3 4 3 2 1 7 6 0 6 7 1 2 5 1 2 3
   2,2,4,4,4,4,2,2,2,2,4,4,4,2,2,2,2,2,2,2,2,2,2,2,2,4,4,2,2,
 //2. 2  2  1  1  0  0  0  0  0  0 
   4, 2, 2, 4, 4, 4 ,4 ,4, 4, 4, 4,
   //12  3  1  5 .3  2  5  2  1  6  3. 
 2, 2, 2, 2, 4, 2, 4, 4, 4, 2, 2, 4, 
//1 7  0  1  7  6  7  1  2  5  1  2
 4, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2,
//3 4  4  3  2  1  2
 2, 4, 2, 2, 2, 2, 8, 
//1 2  3  1  5 .3  2  5  2  1  6  6  7  1  5 
 2, 2, 2, 2, 4, 2, 4, 4, 4, 2, 2, 4, 2,2,4,
//0 5  6  7  1  2  5  1  2 
  2,2, 4, 4, 2, 2, 4, 4, 2,
//3 4  4  3  2  1  1
 2, 4, 2, 2, 2, 2, 8
  
};*/



void common_play() {
  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody)/4; thisNote++) {
    
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = ( 800 / 8 ) * noteDurations[thisNote];
    ledcSetup(LEDC_CHANNEL_0, melody[thisNote] , LEDC_TIMER_13_BIT);
    ledcAttachPin(LED_PIN, LEDC_CHANNEL_0);
    ledcWrite(LEDC_CHANNEL_0, 50);
    delay(noteDuration * 2.30);
  }
  ledcDetachPin(LED_PIN);
}
