I=imread('/img/photo.tif');
J=imrotate(I,35,'bicubic','loose');%逆时针旋转35度，双三次插值，完整显示旋转后图像
imshow(I);
figure,imshow(J);