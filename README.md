# RHL Drone Racing Platform
Rogue Hack Lab's 2016 Rogue Valley Mini Maker Faire main event is 
micro drone racing.


The RHL Drone Race Platform is built on the Particle.IO internet of things 
device platform.

It consists of three products:

### Race Timer

The race timer has three race lanes.
Each lane has an LCD timer at 1/10th of a second accuracy and a stop button.

All lanes share a single start button that starts all lanes at the same time, 
a buzzer, and a lighting strip to cue actions to racers.

The race timer is the process owner. It will communicate status instructions to
 the particle cloud which will be picked up by other products.

### Race Gates
Race gates are 2 meter long flexible PVC tubes containing multicolor light 
strips. 
The tubes can be configured in any arrangement of hoops, bows, poles, etc.

Gates will receive instructions from the Race Timer and display 
lighting animations for entertainment and provide status indication to racers 
and spectators, similar to a flagger in an automotive race.

### Scoreboard

display of current race stats for spectators