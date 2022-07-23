clear;
yuantu=imread('greens.jpg');
maxr=0.95;
pipeitu=imcrop(yuantu);
imwrite(pipeitu,'../img/pipeix.png');
%pipeitu=imread('pipei.png');
yuantu2gray=rgb2gray(yuantu);
pipei2gray=rgb2gray(pipeitu);
[pipei_height,pipei_width]=size(pipei2gray);
[yuantu_height,yuantu_width]=size(yuantu2gray);
imshow(yuantu2gray);
hold on;
maxi=1;
maxj=1;
for i=1:yuantu_height-pipei_height
    for j=1:yuantu_width-pipei_width
        temp_picture=imcrop(yuantu2gray,[j,i,pipei_width-1,pipei_height-1]);
        r=corr2(temp_picture,pipei2gray);
        if r>0.95 && r>maxr
            maxi=i;
            maxj=j;
            maxr =r;
            picture=temp_picture;
        end
    end
end
rectangle('Position',[maxj,maxi,pipei_width,pipei_height],'LineWidth',3,'LineStyle','-','EdgeColor','r');
