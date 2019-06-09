function [y,size_y] = trans3d_2d(v)
%%%把三维的数组转化为二维，、
%转换方式：先把每一页的二维变成一行，变换后的每行对应的是元数组每页的数据，方便用interp1插值
if length(size(v))==3
    for i = 1:size(v,3)
        vv = v(:,:,i);
        vvv(i,:) = vv(:);
    end
    y = vvv;
    size_y = size(v(:,:,1));
else
    y = v;
    size_y = size(y);
    print('v is not 3 dimention')
end
end
