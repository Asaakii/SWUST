I1=imread('/img/Pepper.bmp');
I2=imread('/img/photo640.bmp');
[m1,n1]=size(I1);
[m2,n2]=size(I2);
ADD=imadd(I1,I2);
SUB=imsubtract(I1,I2);
MUL=immultiply(I1,I2);
DIV=imdivide(I1,I2);
subplot(2,3,1),imshow(I1);
title('Pepper.bmp');
subplot(2,3,2),imshow(I2);
title('photo640.bmp');
subplot(2,3,3),imshow(ADD);
title('ADD图像');
subplot(2,3,4),imshow(SUB);
title('SUB图像');
subplot(2,3,5),imshow(MUL);
title('MUL图像');
subplot(2,3,6),imshow(DIV);
title('DIV图像');