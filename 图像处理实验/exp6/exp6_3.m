%添加高斯噪声，并用约束最小二乘法复原

clear
I=imread('rice.png'); 
I=im2double(I); 
PSF=fspecial('gaussian', 8, 4); 
J=imfilter(I, PSF, 'conv'); 
figure;
subplot(121); imshow(I); title('原始图像')
subplot(122); imshow(J); v=0.02; title('滤波后图像')
K=imnoise(J, 'gaussian', 0, v); 
NP=v*numel(I); 
L=deconvreg(K, PSF, NP); 
figure;
subplot(121);	imshow(K); title('添加高斯噪声后图像')
subplot(122);	imshow(L); title('约束最小二乘法复原图像')
