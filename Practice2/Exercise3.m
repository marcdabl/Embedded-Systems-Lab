%% Exercise 3.
% Code  a  MATLAB script that makes the fan go from 0 to 255 in 15s.

clear all
UNO = arduino();

PWMpin = "D8";
Speedpin = "D9";

inPinA= [];
outPinA = [];
inPinD = [Speedpin];
outPinD = [PWMpin];

%Set up Pin configurations
setupPins(UNO,inPinA,outPinA,inPinD,outPinD);

% Lets make an Educated Guess
connection_rate = 9600; %baud


%% 
% the loop function runs over and over again forever
fspeed = 0;
tic
while (1)
    writeDigitalPin(UNO,PWMpin,1); 
    pause(fspeed*4/1e6);
    writeDigitalPin(UNO,PWMpin, 0);
    pause(1020/1e6 - fspeed*4/1e6);
    time = toc;
    fspeed = min(15*floor(time),255);
end

%the writeDigitalPin function does not work enough quickly to achieve the
%results required in the attachment. 
