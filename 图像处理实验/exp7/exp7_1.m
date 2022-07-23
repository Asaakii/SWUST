%基于微分算子的边缘检测

clear
I=imread('cameraman.tif');
I=im2double(I);
[J, thresh]=edge(I, 'prewitt', [], 'both');%prewitt算子
figure;
subplot(121);	imshow(I);  title("原始图像")
subplot(122);	imshow(J);  title("prewitt算子边缘检测")
