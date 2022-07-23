clear
I=imread('../img/1234.png');
I=rgb2gray(I);
J=imnoise(I, 'gaussian', 0.2);%高斯噪声，噪声水平0.2
h=fspecial('average', 3);
k=fspecial('average', 5);
I2=filter2(h, J);
I3=filter2(k, J);
subplot(2,2,1), imshow(I), title('原图像');
subplot(2,2,2), imshow(J), title('加高斯噪声图像');
subplot(2,2,3), imshow(I2, [ ]), title('3*3均值滤波后图像');
subplot(2,2,4), imshow(I3, [ ]), title('5*5均值滤波后图像');