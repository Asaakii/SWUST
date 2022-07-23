clear;
videoObj = VideoReader('traffic.avi');
numFrames =videoObj.NumFrames;
FPS = videoObj.FrameRate;
newframe = read(videoObj, 1);
fmed = double(newframe);
[height, width, numColor] = size(newframe);
Threh = 20;
beta = 0.6;
fg = false(height, width);
se = strel('square',3);
for n = 1:numFrames
    newframe = read(videoObj, n);
    Idiff = double(newframe) - fmed;
    pixInc = find(Idiff > 0);
    fmed(pixInc) = fmed(pixInc) + beta;
    pixDec = find(Idiff < 0);
    fmed(pixDec) = fmed(pixDec) - beta;
    fg = abs(Idiff) >Threh;
    if ( numColor == 3)	% color image
        fg = fg(:, :, 1) | fg(:, :, 2) | fg(:, :, 3);
    end
    fg2 = imopen(fg,se);
    fg2 = imclose(fg2,se);
    %对分割结果进行形态学滤波先进行了开操作，再进行闭操作。
    figure(1);
    subplot(1,3,1), imshow(newframe);
    title(strcat('Current Image, No. ', int2str(n)));
    subplot(1,3,2), imshow(fg);
    title('使用近似中值滤波器的分割结果'); 
    subplot(1,3,3), imshow(fg2);
    title('使用形态学滤波器的分割结果');
end
