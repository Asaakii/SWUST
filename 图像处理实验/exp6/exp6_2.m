%维纳滤波复原（含噪声）

clear
I=imread('rice.png');
I=im2double(I);
LEN=20;
THETA=10;
PSF=fspecial('motion', LEN, THETA); 
J=imfilter(I, PSF, 'conv', 'circular'); 
figure;
subplot(121);	imshow(I); title('原始图像')
subplot(122);	imshow(J); title('滤波后图像')
noise=0.03*randn(size(I)); 
K=imadd(J, noise); 
NP=abs(fft2(noise)).^2;
NPower=sum(NP(:))/numel(noise);
NCORR=fftshift(real(ifft2(NP))); 
IP=abs(fft2(I)).^2; 
IPower=sum(IP(:))/numel(I); 
ICORR=fftshift(real(ifft2(IP))); 
L=deconvwnr(K, PSF, NCORR, ICORR);
figure;
subplot(121);	imshow(K); title('添加噪声的运动模糊图像')
subplot(122);	imshow(L); title('复原图像')
