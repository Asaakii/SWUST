%根据直方图设定域值进行图像分割

clear
I=imread('rice.png');
imshow(I);  title('原始图像')
%输出直方图
figure;imhist(I);
%手动选定阈值进行分割，选择阈值为140
[width,height]=size(I);
T1=140;
for i=1:width
    for j=1:height
        if(I(i,j)<T1)
            BW1(i,j)=0;
        else 
            BW1(i,j)=1;
        end
    end
end
figure;imshow(BW1),title('手动阈值进行分割');
%自动选择阈值
T2=graythresh(I);
BW2=im2bw(I,T2);%Otus阈值进行分割
figure;imshow(BW2),title('Otus阈值进行分割');

