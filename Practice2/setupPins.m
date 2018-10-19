function [] = setupPins(UNO,inPinA,outPinA,inPinD,outPinD)
    for i = 1:length(inPinA)
        configurePin(UNO,inPinA(i,:),'AnalogInput');
    end
    for i = 1:length(outPinA)
        configurePin(UNO,outPinA(i,:),'AnalogOutput');
    end
    for i = 1:length(inPinD)
        configurePin(UNO,inPinD(i,:),'DigitalInput');
    end
    for i = 1:length(outPinD)
        configurePin(UNO,outPinD(i,:),'DigitalOutput');
    end
end

