function [out] = interp_3d(x,v,xq,method)
%%% interpolate a 3D vector through 1D index


if length(size(v))==3
    for i = 1:size(v,3)
        vv = v(:,:,i);
        vvv(i,:) = vv(:);
    end
    out_b = interp1(x,vvv,xq,method,'extrap');
    out = reshape(out_b,size(v(:,:,1)));
else
    out = interp1(x,v,xq,method,'extrap');
end
end