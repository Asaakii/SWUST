%巴特沃斯 Butterworth 低通滤波器的简单实现

clear
I = imread('moon.tif'); 
f = im2double(I);
D0 = 10;	%定义滤波器截止频率，可令D0分别等于 30,60..观察结果
n= 2;	% 定义滤波器阶数，可增大阶数n=3,4…观察滤波效果
F = fft2(f);
Fc = fftshift(F);
[height, width] = size(Fc);
%初始化巴特沃斯低通滤波器系数矩阵(频率域设计滤波器） 
H = zeros(height, width);
%计算巴特沃斯低通滤波器系数矩阵 
for u =1:height
    for v =1:width

    %计算巴特沃斯低通滤波器在频率点 (u,v)的系数值 
        Dist = sqrt((u-height/2)^2 + (v-width/2)^2); 
        H(u, v) = 1/(1+(Dist/D0).^(2*n));
    end
end
%进行巴特沃斯低通滤波, 图像傅里叶变换矩阵与滤波器系数矩阵对应点乘
G= Fc.* H;
G = ifftshift(G);
g= real(ifft2(G)); g = im2uint8(g);
figure, imshow(I);title('Original Image');
figure, imshow(g); title('the Butterworth LPF Smoothed Image');
