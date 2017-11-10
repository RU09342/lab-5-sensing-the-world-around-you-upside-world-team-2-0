inputData = serial('COM3' , 'baudrate' , 9600);
set(inputData , 'InputBufferSize' , 5);
fopen(inputData);

i=1;
h = animatedline;
while(1)
    addpoints(h,i,str2num(fscanf(inputData)));
    i = i+1;
    drawnow limitrate
end



