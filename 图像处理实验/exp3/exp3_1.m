%线性变换
clear
X1=imread('../img/1234.png');
X1=rgb2gray(X1);
figure,imshow (X1)
title('原始灰度图像')
f0=0;g0=0;
f1=60;g1=30;
f2=180;g2=240;
f3=255;g3=255;
%绘制变换曲线
figure,plot([f0,f1,f2, f3], [g0,g1,g2,g3])
axis tight,xlabel('f') ,ylabel ('g');
title('线性变换曲线');
r1=(g1-g0)/ (f1-f0);%求0~60灰度级范围内的压缩比
b1=g0-r1*f0;
r2=(g2-g1)/ (f2-f1) ;%60~180灰度级范围内的压缩比
b2=g1-r2*f1;
r3= (g3-g2)/ (f3-f2) ; %180~255灰度级范围内的压缩比
b3=g2-r3*f2;
[m,n]=size (X1); %求矩阵的行数 m,列数n 
X2=im2double(X1) ;%将数据类型转换为双精度型
%变换矩阵中的每个元素
for i=1:m
    for j=1:n
        f=X2(i,j);
        g(i,j)=0;
        if (f>=0)&&(f<=f1)%找出灰度级范围在0~60的元素
            g(i,j)=r1*f+b1;%进行灰度变换
        elseif (f>=f1)&&(f<=f2)%找出灰度级范围在60~180的元素
            g(i,j)=r2*f+b2;%进行灰度变换
        elseif (f>=f2)&&(f<=f3)%找出灰度级范围在180~255的元素
            g(i,j)=r3*f+b3;%进行灰度变换
        end
    end
end
figure,imshow(mat2gray(g))%将数据矩阵转换成灰度图像
title('线性变换后灰度图像');
