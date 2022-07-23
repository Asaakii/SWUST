%添加高斯噪声，并用盲解卷积复原

clear
I=imread('rice.png');
I=im2double(I); 
PSF=fspecial('gaussian', 7, 10); 
v=0.001;
J=imnoise(imfilter(I, PSF), 'gaussian', 0, v); 
INITPSF=ones(size(PSF)); 
WT=zeros(size(I));
WT(5:end-4, 5:end-4)=1;
[K, PSF2]=deconvblind(J, INITPSF, 20, 10*sqrt(v), WT); 
figure;
subplot(131); imshow(I); title('原始图像');
subplot(132); imshow(J); title('退化后图像');
subplot(133); imshow(K); title('盲解卷积复原后图像')