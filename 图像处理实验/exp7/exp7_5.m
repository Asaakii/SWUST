%sobel算子不同方向的边缘检测

clear
I=imread('cameraman.tif');
I=im2double(I);
I1=edge(I,'sobel','horizontal');%水平方向
I2=edge(I,'sobel','vertical');%垂直方向
I3=edge(I,'sobel','both');%水平和垂直两个方向
figure;
subplot(221);	imshow(I);  title("原始图像")
subplot(222);	imshow(I1);  title("sobel算子水平方向边缘检测")
subplot(223);	imshow(I2);  title("sobel算子垂直方向边缘检测")
subplot(224);	imshow(I3);  title("sobel算子水平和垂直方向边缘检测")