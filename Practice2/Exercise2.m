%% Exercise 2.
% Code  a  MATLAB script that  shows  the  distance  to  an  object  
% measured  by  a HC-SR04 connected to Arduino.

clear all
UNO = arduino();

tgrPin = "D2";
echoPin = "D3";

inPinA= [];
outPinA = [];
inPinD = [echoPin];
outPinD = [tgrPin];

%Set up Pin configurations
setupPins(UNO,inPinA,outPinA,inPinD,outPinD);

% Lets make an Educated Guess
connection_rate = 9600; %baud


%% Checking the time needed to read the digital pin
tic
echoP = readDigitalPin(UNO,echoPin);
toc

% Elapsed time is 0.024312 which is too high and this does not allow to
% read the distance 

%% 
% the loop function runs over and over again forever
for i=1:1
    % Writing 0 to trigger and waiting to ensure change to 1 is detected.
    tic
    writeDigitalPin(UNO,tgrPin,0); 
    pause(0.000005)
    writeDigitalPin(UNO,tgrPin, 1);
    pause(0.00001)
    writeDigitalPin(UNO,tgrPin, 0);
    toc
    % Just in case echo is still not launched
    time = 0;
    echoP = readDigitalPin(UNO,echoPin)
    while(echoP == 0)
        echoP = readDigitalPin(UNO,echoPin);
    end
    disp("Echo recieved")
    % Wait for echo to finish
    while(echoP == 1)
        echoP = readDigitalPin(UNO,echoPin)
        time = time+(1/connection_rate)*2;
    end
    time
    distance = time*1e6/58
    pause(1)
end