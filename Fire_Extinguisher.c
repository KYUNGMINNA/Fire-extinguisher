#include <mega128.h>             
#include <delay.h>
typedef unsigned char u_char;
flash u_char seg_pat[10]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
void  AD_disp(int);         // A/D 변환값 표시 
 
void fire(int);
void main(void)
{              

    int   ad_val;
    int  fire;
    DDRB = 0xFF;                // 포트 B 출력 설정 
    DDRD = 0xFF;                // 포트 D 출력 설정
    DDRG = 0xFF;                // 포트 G 출력 설정
    DDRE=0b00001000;
    PORTB = 0x0;
   PORTD = 0x0;
    ADMUX = 0b00000000;                // ADC7 단극성 입력 선택   // 아날로그 신호를 디지털 신호로 변환 
    ADCSRA = 0b10000100;              // ADEN=1, 16MHz  256분주 -> 125kHz 
    delay_ms(5);
    while(1){
        ADCSRA = 0b11000100;                              // ADEN=1, ADSC = 1 변환 시작
        while((ADCSRA & 0x10) == 0);                // ADIF=1이 될떄까지
        ad_val = (int)ADCL + ((int)ADCH << 8);      // A/D 변환값 읽기      
         fire = (int)ADCL + ((int)ADCH << 8);
        AD_disp(ad_val);                            // A/D 변환값 표시
            }
    }                                                       // A/D 변환값 표시
 void fire(int fir)
 {
   int fi;
   
   fi=(int)fir*5.0/1024;
   
   if(fi>0)
   {
       DDRE=0xFF;
 
        PORTE=0xFF;
 
        DDRB=0xFF;
 
        PORTE=0xFF;
 
        delay_ms(500);   
 
        PORTE=0x00;
 
        delay_ms(500);
 
          DDRE=0x00;
   }
 }

void AD_disp(int val)
 
{                
 
    float  fval;
 
    int  ival, buf; 
 
    u_char N100, N10, N1;
 
    fval = (float)val * 5.0 / 1024.0;       // 전압값(V)으로 변환 
 
    // 온도값으로 변환 : fval * 1000mV / 10mv (도/10mV) 
 
    fval = fval * 100;                       // 온도값으로 변환  
 
    ival = (int)(fval  * 10.0 + 0.5);       // 반올림 후 정수화(소수 첫 째자리까지) 
 
    N100 = ival / 10;              // 온도 10자리 추출
 
    buf = ival % 100;        

                               // N100 = ival / 10;
 
    if(N100>100)      //가스센서는 N100>100
 
    {
 
        DDRE=0xFF;
 
        PORTE=0xFF;
 
        DDRB=0xFF;
 
        PORTE=0xFF;
 
        delay_ms(500);   
 
        PORTE=0x00;
 
        delay_ms(500);
 
          DDRE=0x00;
 
    }    
 
    N10 = buf / 10;                 // 온도 1자리 추출
 
 
 
    N1 = buf % 10;                  // 온도 소수 첫째 자리 추출
 
    PORTG = 0b00000100;             // 맨 우측 7-Segment DIG4 ON (PG3=1)  
 
    PORTB = (seg_pat[N1] & 0x70) | (PORTB & 0x0F);   // 소수 자리 e,f,g 표시
 
    PORTD = ((seg_pat[N1] & 0x0F) << 4) | (PORTD & 0x0F);   // a, b, c, d 
 
    delay_ms(1);  

    PORTG = 0b00000010;                // 7-Segment DIG3 ON (PG2=1)  

    PORTB = (seg_pat[N10] & 0x70) | (PORTB & 0x0F);           // 1자리 e,f,g 표시 
 
    PORTB = PORTB | 0x80;                                   // Decimal Point

    PORTD = ((seg_pat[N10] & 0x0F) << 4) | (PORTD & 0x0F);  // a, b, c, d 표시  
 
    delay_ms(1);
 
    PORTG = 0b00000001;               // 7-Segment DIG2 ON(PG1=1)  

    PORTB = (seg_pat[N100] & 0x70) | (PORTB & 0x0F);          // 10자리 e,f,g 표시
    PORTD = ((seg_pat[N100] & 0x0F) << 4) | (PORTD & 0x0F); // a, b, c, d 표시
    delay_ms(1);
 

} 





