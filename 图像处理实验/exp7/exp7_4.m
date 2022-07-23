%三种不同算子的边缘检测

clear
I=imread('cameraman.tif');
I=im2double(I);
I1=edge(I,'roberts');
I2=edge(I,'sobel');
I3=edge(I,'log');
figure;
subplot(221);	imshow(I);  title("原始图像")
subplot(222);	imshow(I1);  title("roberts算子边缘检测")
subplot(223);	imshow(I2);  title("sobel算子边缘检测")
subplot(224);	imshow(I3);  title("log算子边缘检测")