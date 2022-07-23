I=imread('/img/photo.tif');
J=imrotate(I,30,'bilinear');
J1=imrotate(I,30,'bilinear','crop');
imshow(I);
figure,imshow(J);
figure,imshow(J1);
J2=imrotate(I,-15,'bilinear');
figure,imshow(J2)