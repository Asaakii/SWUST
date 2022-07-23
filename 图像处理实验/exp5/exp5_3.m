%理想低通滤波器的简单实现

clear
I = imread('moon.tif'); 
f = im2double(I);
D0 = 10;	% 定义滤波器截止频率
F = fft2(f); %快速傅里叶变换 
Fc = fftshift(F); % 中心化 
[height, width]=size(Fc);
%初始化理想低通滤波器系数矩阵(频率域设计滤波器）

H = zeros(height, width);
%计算理想低通滤波器系数 
for u=1:height
    for v =1:width
        if(sqrt((u-height/2)^2 + (v-width/2)^2) < D0) 
            H(u,v) =1;
        else
            H(u,v) = 0;
        end
    end
end
%进行理想低通滤波,图像傅里叶变换矩阵与滤波器系数矩阵对应点乘
G = Fc.*H;
G = ifftshift(G);	% 去中心化
g= real(ifft2(G));	% 逆傅里叶变换并取实部
g = im2uint8(g);	% 把输出图像转换为uint8数据类型
figure, imshow(I);title('Original Image');
figure, imshow(g); title('the ILP Smoothed Image');
