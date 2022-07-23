clear;
video_det=VideoReader('traffic.avi');
vidheight=video_det.Height;
vidwidth=video_det.Width;
nframes=video_det.NumFrames;
s=read(video_det,[1 100]);
rate=video_det.FrameRate;
for k=1:20:100
    figure(k);
    im11=s(:,:,:,k);
    subplot(221),imshow(im11);
    mov(k).cdata=rgb2gray(im11);
    subplot(222),imshow(s(:,:,:,k+5));
    mov(k+1).cdata=rgb2gray(s(:,:,:,k+5));
    reg_im=abs(mov(k).cdata-mov(k+1).cdata)>8;
    subplot(223),imshow(reg_im);
    SE=ones(5,5);%结构元素
    i3=bwmorph(reg_im,'dilate',9);%形态学的膨胀操作
    i3=imerode(i3,SE);%腐蚀操作
    [L,nm]=bwlabel(i3,8);%按 8 连通方式寻找，进行图像分割
    subplot(224);imshow(im11);
    for i=1:nm
        [r,c]=find(L==i);
        left=min(c);
        right=max(c);
        top=min(r);
        buttom=max(r);
        width=right-left+1;
        height=buttom-top+1;
        rectangle('Position',[left,top,width,height],'Edgecolor','r');
    end
    % result=
end
