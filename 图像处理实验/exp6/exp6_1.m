%维纳滤波复原（点扩散函数创建运动模糊图像，并复原）

clear
I=imread('moon.tif'); 
I=im2double(I);
LEN=25; 
THETA=20;
PSF=fspecial('motion', LEN, THETA); 
J=imfilter(I, PSF, 'conv', 'circular'); 
NSR=0;
K=deconvwnr(J, PSF, NSR); 
figure;
subplot(131); imshow(I); title('原始图像')
subplot(132); imshow(J); title('滤波图像')
subplot(133); imshow(K); title('复原图像')
