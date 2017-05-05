
pkg load instrument-control
pkg load image

s1 = serial("/dev/ttyACM0", 115200);
set(s1, "baudrate", 115200);
set(s1, "bytesize", 8);
set(s1, "parity", "N");
set(s1, "stopbits", 1);





im=imread('class2_9.jpg');
img=rgb2gray(im);



srl_write(s1,'s');
  for i=1:32
    for j=1:32
      srl_write(s1,uint8(img(i,j)));
    end  
  end  
  
  

  
