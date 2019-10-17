UCLA ECE-3 Introduction To Electrical Engineering Final Project
--------------------------------------------------------------
Code written by Isabel Dominik and Jackie Peng

Line Follower is a program written in C++ that allows the TI-RSLK robotic car to follow a black line over a track. As per the project requirements, once the car sees a horizontal line at the end of the track, it completes a 180 degree turn then repeats the track backwards before stopping back at the beginning.

To keep the car on the line, PD control is used (the integral term of PID was deemed not necessary to keep the car aligned with the track). Currently, the PD is tuned only for slower speeds. All PD tuning notes are contained in PID_Notes.txt.

The working code for the assignment is in CarCode.

The extra credit portion of the assignment wanted the car to monitor its speed with encoders, then when it encounters a horizontal line, turns on the blue LED and slows down. Once the car encounters another black line, the car turns off the LED and speeds up again, stopping at the end of the course. To speed up and slow down, the car uses primitive P control (not tuned).

Developed using Energia for the TI-RSLK kit (TI Launchpad).
