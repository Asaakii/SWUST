%直方图均衡化、规定化
clear
I = imread('../img/1234.png');
I = rgb2gray(I);
J = histeq(I);%灰度级数为64
imshow(I)
title('灰度图像')
figure, imshow(J);
title('增强灰度图像')
figure,imhist(I,64)
title('灰度图像直方图')
figure,imhist(J,256)
title('增强灰度图像直方图')