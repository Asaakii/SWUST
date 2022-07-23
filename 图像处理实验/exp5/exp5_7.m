%Laplacian 图像锐化增强的频域实现

clear
I = imread('moon.tif'); 
f = im2double(I);
AB = size(f);
h = fspecial('laplacian',0); 
CD = size(h);
PQ = AB + CD -1;
H = fft2 (h,PQ(1),PQ(2));
H = fftshift(H);
F = fft2(I,PQ(1),PQ(2));
F = fftshift(F);
% calculate the laplacian image 
G= F.*H;
ge = real(ifft2(ifftshift(G)));
ge = imcrop(ge,[1,1,AB(2)-1,AB(1)-1]);
figure, imshow(mat2gray(ge),[]);
% calculate the enhanced image using laplacian operator 
ge = ge/max(max(abs(ge)));
gs = f-ge;
gs = im2uint8(gs); 
figure, imshow(I); 
figure, imshow(gs);
