%简单二值图像的傅里叶变换及幅度谱

clear
%创建一个二值图像
f = zeros(256, 256);
f(100:156,118:138)= 1;
%计算其傅里叶变换
F=fft2(f);
F1 = fftshift(F); %中心化
%显示原图像及其幅度谱
figure, imshow(f)
figure, imshow(abs(F),[]); colormap(gray); colorbar;
%将幅度谱对数变换后再显示
figure, imshow(log(1 + abs(F)),[]); colormap(gray); colorbar;
figure, imshow(log(1 + abs(F1)),[]); colormap(gray); colorbar;
figure, mesh(1:256,1:256, abs(F1));
%将图像旋转45度，然后重做上述步骤
f45 =imrotate(f,45, 'crop');
F2 =fft2(f45);
F3 = fftshift(F2);
figure, imshow(f45);
figure, imshow(log(1+ abs(F3)),[]); colormap(gray); colorbar
figure, mesh(1:256, 1:256, abs(F3));
