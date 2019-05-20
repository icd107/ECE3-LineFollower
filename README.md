UCLA ECE3 Introduction To Electrical Engineering Final Project
--------------------------------------------------------------
Code written by Isabel Dominik and Jackie Peng

Developed using Energia for the TI-RSLK kit

Line Follower is a program written in C++ that allows the TI-RSLK robotic car to follow a black line over a track. As per the project requirements, once the car sees a horizontal line at the end of the track, it completes a 180 degree turn then repeats the track backwards before stopping back at the beginning.

To keep the car on the line, PD control is used (the integral term of PID was deemed not necessary to keep the car aligned with the track).
