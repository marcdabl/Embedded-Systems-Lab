%% Exercise 1.
% Code  a  MATLAB script (program) that  shows  the  temperature  measured 
% by a LM35 connected to an Arduino analog input.

clear all
UNO = arduino();

voutPinA = "A0";

inPinA= [voutPinA];
outPinA = [];
inPinD = [];
outPinD = [];

%Set up Pin configurations
setupPins(UNO,inPinA,outPinA,inPinD,outPinD);

% the loop function runs over and over again forever
for i=1:1
  voltage = readVoltage(UNO,voutPinA);
  temp = voltage*100
end
