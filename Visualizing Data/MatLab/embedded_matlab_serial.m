%create a serial object at COM3 (changed based on which port to be used),
%and a specified baud rate of 9600.
inputData = serial('COM3' , 'baudrate' , 9600);
%Set the input buffer size to 5,since we will be transmitting the data in
%sets of 5, tens place, ones place, decimal place,
set(inputData , 'InputBufferSize' , 5);
fopen(inputData);

i=1;
h = animatedline;
while(1)
    addpoints(h,i,str2num(fscanf(inputData)));
    i = i+1;
    drawnow limitrate
end



