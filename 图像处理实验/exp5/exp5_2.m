%空间域高斯低通滤波器的频率域实现

clear
I = imread('moon.tif'); 
f = im2double(I); 
sigma = 2;
%根据标准差sigma大小，确定滤波模板的尺寸
hsize = floor(6*sigma); 
if mod(hsize,2) == 0
    hsize = hsize+1;
end
%生成指定大小的空间域高斯低通滤波模板 
h = fspecial('gaussian', hsize, sigma);
AB = size(f);
CD = size(h);
PQ = AB + CD -1;
F = fft2(f,PQ(1),PQ(2));
H = fft2 (h,PQ(1),PQ(2));
g = real(ifft2(F .* H));
g = imcrop(g, [1,1,AB(2)-1, AB(1)-1]);
g =im2uint8(g);
figure, imshow(I); title('Original Image'); 
figure, imshow(g); title('the Smoothed Image');
