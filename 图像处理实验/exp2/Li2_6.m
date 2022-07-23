I=imread('/img/photo.tif');
imshow(I);
rect=[30 60 120 160];
I2=imcrop(I,rect);
rectangle('Position',rect,'linewidth',2,'edgecolor','r');
figure;imshow(I2)