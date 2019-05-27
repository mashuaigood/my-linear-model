function f = multiply23(a,b)
%%%2ЮЌОиеѓГЫвд3ЮЌОиеѓ
for i = 1:size(b,3)
    f(:,:,i) = a*b(:,:,i);
end
end
