%高斯Gaussian高通滤波器的简单实现

clear
I = imread('moon.tif'); 
f = im2double(I);
D0 = 10;	%定义滤波器截止频率，可令D0分别等于 30,60..观察结果
F = fft2(f);
Fc = fftshift(F); 
[height,width]=size(Fc);
%初始化高斯高通滤波器系数矩阵(频率域设计滤波器）
H = zeros(height, width);
%计算高斯高通滤波器系数矩阵 
for u =1:height
    for v =1:width
        %计算高斯高通滤波器在频率点 (u,v)的系数值(注意与高斯低通滤波器之间的差异） 
        sqDist = (u-height/2)^2 + (v-width/2)^2;
        H(u, v) = 1- exp(-sqDist/(2*D0^2));
    end
end
%进行高斯高低通滤波, 图像傅里叶变换矩阵与滤波器系数矩阵对应点乘
G= Fc.* H;
G = ifftshift(G);
g= real(ifft2(G)); 
g = im2uint8(g);
figure, imshow(I);title('Original Image');
figure, imshow(g); title('the Gaussian HPF Image');
