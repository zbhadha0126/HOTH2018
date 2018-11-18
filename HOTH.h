#include <InternetButton.h>
#include <math.h>



InternetButton b = InternetButton();
int mode;
uint8_t r = 50;
uint8_t g = 50;
uint8_t blue = 50;
int seconds = 0;

void setup() {

    b.begin();
    
    while(true)
    {
        b.allLedsOn(50, 50, 50);
        delay(1000);
        b.allLedsOff();
        delay(1000);
        
        if(b.buttonOn(1))
        {
            mode = 1;
            break;
        }
        else if(b.buttonOn(2))
        {
            mode = 2;
            break;
        }
        else if(b.buttonOn(3))
        {
            mode = 3;
            break;
        }
        else if(b.buttonOn(4))
        {
            mode = 4;
            break;
        }
    }

    

}

void loop() {
    
    //Play music
    if(mode == 1)
    {
        if(b.buttonOn(1))
        {
            b.playNote("G3",8);
        }
    
        if(b.buttonOn(2))
        { 
            b.playNote("G4",8);
        }
    
        if(b.buttonOn(3))
        {
            b.playNote("G5",8);
        }
    
        if(b.buttonOn(4))
        {
            b.playNote("G6",8);
        }
        
        if(b.allButtonsOn())
        {
            setup();
        }
    }
    
    
    // Adjust color
    if(mode == 2)
    {
        b.allLedsOn(r, g, blue);
        
        if(b.buttonOn(1))
        {
            r = 50;
            g = 50;
            blue = 50;
            b.allLedsOn(r, g, blue);
        }
        if(b.buttonOn(2))
        {
            r += 5;
            b.allLedsOn(r, 0, 0);
        }
        
        if(b.buttonOn(3))
        {
            g += 5;
            b.allLedsOn(0, g, 0);
        }
        
        if(b.buttonOn(4))
        {
            blue += 5;
            b.allLedsOn(0, 0, blue);
        }
        
        if(b.allButtonsOn())
        {
            setup();
        }
    }
    
    
    // Game: Read color, press button
    // 4: red
    // 3: green
    // 2: blue
    if(mode == 3)
    {
        if(b.allButtonsOn())
        {
            setup();
        }
        
        int check = rand()%3+1;
        
        if(check == 1)
        {
            b.allLedsOn(50, 0, 0);
            delay(1000);
            if(!b.buttonOn(4))
            {
                b.allLedsOn(50, 50, 50);
                delay(1000);
            }
        }
        
        if(check == 2)
        {
            b.allLedsOn(0, 50, 0);
            delay(1000);
            if(!b.buttonOn(3))
            {
                b.allLedsOn(50, 50, 50);
                delay(1000);
            }
        }
        
        if(check == 3)
        {
            b.allLedsOn(0, 0, 50);
            delay(1000);
            if(!b.buttonOn(2))
            {
                b.allLedsOn(50, 50, 50);
                delay(1000);
            }
        }
        
    }
    
    // Timer
    // 2 adds 60 seconds, 4 takes 60 seconds off
    // 1 adds 1 second, 3 takes 1 second off
    // 1 and 3 simultaneously to start
    if(mode == 4)
    {
        if(b.allButtonsOn())
        {
            setup();
        }
        
        if(b.buttonOn(1) && b.buttonOn(3))
        {
            if(seconds < 0)
            {
                seconds = 0;
            }
            delay(seconds*1000);
            blinkBlue();
        }
        
        if(b.buttonOn(2))
        {
            seconds += 60;
            b.ledOn(2, 0, 50, 0);
            b.ledOn(3, 0, 50, 0);
            b.ledOn(4, 0, 50, 0);
            delay(100);
            b.allLedsOff();
        }
        
        if(b.buttonOn(4))
        {
            seconds -= 60;
            b.ledOn(8, 50, 0, 0);
            b.ledOn(9, 50, 0, 0);
            b.ledOn(10, 50, 0, 0);
            delay(100);
            b.allLedsOff();
        }
        
        if(b.buttonOn(1))
        {
            seconds += 1;
            b.ledOn(3, 0, 50, 0);
            delay(100);
            b.allLedsOff();
        }
        
        if(b.buttonOn(3))
        {
            seconds -= 1;
            b.ledOn(9, 50, 0, 0);
            delay(100);
            b.allLedsOff();
        }
        
    }

}

void blinkBlue()
{
    while(!b.allButtonsOn())
    {
        b.allLedsOn(0, 0, 50);
        delay(500);
        b.allLedsOff();
        delay(500);
    }
}