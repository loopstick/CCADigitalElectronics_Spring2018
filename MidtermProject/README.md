
## Midterm Project Documentation Example 

   - written description of your concept (this can be taken from your original project proposal)
   
### Harvey - the Shy Robot

#### Concept: Create a shy robot. 

I'm not sure yet what that means so for the first few iterations the focus of the project will be getting basic functionality working.
I decided to base the project on a design published in Make Magazine 61:

![Ultradar Robot Pic](UltraDAR/images/9fb649f13b055a1754cfbe000f67afff_preview_featured.jpg)

The key feature of this robot is a simple "ultradar" that is used to sense obstacles in front of the robot. 
Adam Kemp provides the [code](UltraDAR/files/UltraDAR-SingleSweep.ino) (very helpful!) and files to 3D print the parts here: www.thingiverse.com/thing:2481918

[//]: # (comment test: UltraDAR/images/UltraDAR-Top.jpg)

I printed the ultradar pieces and assembled the mechanism. 
I tested the servo. [Servo test code](code/ServoTest.ino)
I tested the ultrasonic sensor. [Ultrasonic test code](code/UltraTest.ino)
I used a breadboard shield to set up 2 transistors to drive two motors and tested (first with LEDs)
I decided against hot gluing the motors to the wooden platform and spent a little extra time to 
drill holes and cut plates so I could use bolts to hold the motors in place (allowing for repositioning and swapping motors later)

![Harv1_top](images/Harv1_top.jpg)
![Harv1_side](images/Harv1_side.JPG)

#### Initial Functionality:

 - sense obstacles
   - use ultrasonic sensor to detect distance
   - use servo to position ultrasonic sensor so an sweep of sensor readings can be made to map the area in front (and sides) of the bot
 - move forward and turn to avoid obstacles
   -  In this iteration I chose to use DC gearhead motors to drive the robot to keep things simple. But that means that without an H-Bridge I cannot reverse the motors.
   - Adam Kemp used continuous rotation servos, which can be reversed more easily. 
 

 In this video we see the problem with using Adam's code and not being able to reverse: 
 when the bot is too close to an obstacle the code sends a flag which would reverse the bot, but my modified code ignores the reverse flag and drives forward instead.
 
 https://youtu.be/EkJ2UbEyxtQ
 
 But as long as the bot doesn't get too close to anything, it does pretty well! 
 
#### Challenges

 - one of my drive motors is stronger than the other, so I had to use analogWrite to vary the speed of one motor to match the other. 
   - I could have done a better job of matching with PWM or pulled the motors to see if there's another pair that would work better.
 - it turns out you can't use PWM on pins 9 & 10 if you use the Servo library, so that's something to consider in the future. I had to move my motor drive control to pins 5 & 6.
 - for a while I thought the ultrasonic sensor had burned out, but a wire had just come loose. I thought I had checked all the connections but apparently not. 
 	When I tested with a brand new sensor (always have 2!) I found the same problem. It turned out one of the connections on the Arduino side was loose.
 

#### Future Functionality:

 - H-Bridge and reverse-ability
   - or continuous rotation servos
   
 - faster forward motion
 
 - a sound sensor that would
 	- make the bot move away from sound (this seems a bit tough to do well: sound localization)
 		http://42bots.com/showcase/experimenting-with-sound-localization-and-arduino/
 		http://forum.arduino.cc/index.php?topic=55578.0
 		https://www.rs-online.com/designspark/diy-sound-localization-sensor-using-arduino
 	- respond to sound by driving quickly forward
 	  -  I like the idea that sometimes this might make the bot run into obstacles after getting "scared" by a loud sound
 	  
 - Other possible shy functionality/behavior
   - hiding under tables
   - seeking out dark places
   - emerging only when people are not around (or only if they're very still and quiet)
     - How is Harv going to be different from a Roomba?
     - Before I go too far down the road of reinventing the wheel, maybe I should think about starting with a Roomba as the base unit...
   
 	  
 	  
 	  