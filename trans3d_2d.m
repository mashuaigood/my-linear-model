function [y,size_y] = trans3d_2d(v)
%%%����ά������ת��Ϊ��ά����
%ת����ʽ���Ȱ�ÿһҳ�Ķ�ά���һ�У��任���ÿ�ж�Ӧ����Ԫ����ÿҳ�����ݣ�������interp1��ֵ
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
