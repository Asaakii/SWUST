clear
I=imread('../img/1234.png');
I=rgb2gray(I);
J=imnoise(I, 'salt & pepper', 0.2);%椒盐噪声，噪声水平0.2
I2=medfilt2(J,[3,3]);
I3=medfilt2(J,[5,5]);
subplot(2,2,1), imshow(I), title('原图像');
subplot(2,2,2), imshow(J), title('加椒盐噪声图像');
subplot(2,2,3), imshow(I2, [ ]), title('3*3中值滤波后图像');
subplot(2,2,4), imshow(I3, [ ]), title('5*5中值滤波后图像');