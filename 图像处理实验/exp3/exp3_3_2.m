%幂次变换
clear
I=imread('../img/1234.png');
subplot(3,3,1),imshow(I),ylabel('原图像');
subplot(3,3,2),imhist(I);
C=1/(255^3); % 语句I
x=0:1:255;
y=C*(x.^4); 
subplot(3,6,6),plot(x,y),axis tight,xlabel('f'),ylabel('g'); %绘制变换曲线
[m,n]=size(I);
K=double(I);
g=C*(K.^4);
%{
%等价的循环语句实现
fori= l:m
    forj=l:n
        g(ij)=0;
        g(ij)=C*(K(ij)^4);
    end
end
%}
subplot(3,3,4),imshow(uint8(g)),ylabel('幂次变换');
subplot(3,3,5),imhist(uint8(g));
%###系统函数调用###
J=imadjust(I,[],[],4);
subplot(3,3,7),imshow(J),ylabel('幂次变换(系统调用');
subplot(3,3,8),imhist(J);
