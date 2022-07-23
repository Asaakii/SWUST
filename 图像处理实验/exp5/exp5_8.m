clear
I = imread('moon.tif'); 
f = im2double(I);
f1=imadjust(f,[0 1],[0 1],0.5);
J1=1.2*I+50;
f2 = histeq(I);%灰度级数为64
figure, imshow(I);title('原始图像');
figure, imshow(I);title('增加亮度图像');

%计算其傅里叶变换
F=fft2(f1);
F1 = fftshift(F); %中心化
%显示原图像及其幅度谱
figure, imshow(f1); title('imadjusted');
figure, imshow(abs(F),[]); colormap(gray); colorbar;
%将幅度谱对数变换后再显示
figure, imshow(log(1 + abs(F)),[]); colormap(gray); colorbar;
figure, imshow(log(1 + abs(F1)),[]); colormap(gray); colorbar; title('imadjust傅里叶变换频谱图');
%figure, mesh(1:640, 1:640, );

%计算其傅里叶变换
F3=fft2(f2);
F2 = fftshift(F3); %中心化
%显示原图像及其幅度谱
figure, imshow(f2); title('直方图均衡化');
figure, imshow(abs(F3),[]); colormap(gray); colorbar;
%将幅度谱对数变换后再显示
figure, imshow(log(1 + abs(F3)),[]); colormap(gray); colorbar;
figure, imshow(log(1 + abs(F2)),[]); colormap(gray); colorbar; title('直方图均衡化傅里叶变换频谱图');
%figure, mesh(1:640, 1:640, );