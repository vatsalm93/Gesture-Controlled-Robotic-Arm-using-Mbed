
#include "mbed.h"
 
Serial xbee1(p9, p10);
DigitalOut rst1(p8);
PwmOut yaw(p21);
PwmOut pitch(p22);
PwmOut grab(p23);
Serial pc(USBTX, USBRX);
 
int main() {
    char recieve;
    yaw.period(0.020);
    pitch.period(0.020);
    grab.period(0.020);
    int got[3];
    float pwidth[2];
    // reset the xbees (at least 200ns)
    rst1 = 0;
    //rst2 = 0;
    wait_ms(1); 
    rst1 = 1;
    //rst2 = 1;
    wait_ms(1); 
 
    while(1) {
        if(xbee1.readable()) {
            ///////// YAW ANGLE ///////////
            recieve=xbee1.getc();
            got[0]=((0<<8)|recieve);
            pc.printf("%d",got[0])
            got[0]=2*got[0];
            if(got[0]>180)got[0]=180;
            if(got[0]<0)got[0]=0;
            pwidth[0]=(float)got[0]/(180*1000);
            yaw.pulsewidth(0.001+(pwidth[0]));
            printf("got[0]: %d",got[0]);
            printf("yaw pulsewidth: %f\n\r",0.001+pwidth[0]);
            
            ///////// PITCH ANGLE /////////
            recieve=xbee1.getc();
            got[1]=((0<<8)|recieve);
            pc.printf("%d",got[1])
            if(got[1]>90)got[1]=got[1]-180;
            got[1]=got[1]*2;
            if(got[1]>90)got[1]=90;
            if(got[1]<-90)got[1]=-90;
            pwidth[1]=(float)got[1]/(180*1000);
            pitch.pulsewidth(0.0015+(pwidth[1]));
            printf("got[1]: %d",got[1]);
            printf("pitch pulsewidth: %f\n\r",0.0015+pwidth[1]);
            
            ////////// GRAB CONTROL ////////
            recieve=xbee1.getc();
            got[2]=((0<<8)|recieve);
            if(got[2]==77)
                    grab.pulsewidth(0.001);
           if(got[2]==99)
                    grab.pulsewidth(0.0017);
            printf("Grab: %d\n\r\n",got[2]);
            
        }
       
    }
}