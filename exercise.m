

close all
j = 3  ;k = 2;       %j represent different N  , k represents different step input
T = 0.02;
uu = delta_u{j,k};
pp = delta_p{j,k};
x_hat = zeros(size(delta_x{j,k},1),size(delta_x{j,k},2)+1);
y_hat = zeros(size(delta_y{j,k}));
y_true = delta_y{j,k};
% for i = 1:length(uu)
%     x_hat(:,i+1) = A(:,:,j)*x_hat(:,i)+B(:,:,j)*uu(:,i)+L(:,:,j)*pp(:,i);
%     y_hat(:,i) = C(:,:,j)*x_hat(:,i)+D(:,:,j)*uu(:,i)+M(:,:,j)*pp(:,i);
% end
% A_d = A(:,:,j);B_d = [B(:,:,j),L(:,:,j)];
% C_d = C(:,:,j);D_d = [D(:,:,j),M(:,:,j)];
% sys = ss(A_d, B_d, C_d, D_d, T);
% sys_c = d2c(sys);
x_c = zeros(size(delta_x{j,k},1),size(delta_x{j,k},2)+1);
y_c = zeros(size(delta_y{j,k}));

for i = 1:length(uu)
    x_c(:,i+1) = A(:,:,j)*x_c(:,i) + BL(:,:,j)*[uu(:,i);pp(:,i)];
    
    y_c(:,i) = C(:,:,j)*x_c(:,i) + DM(:,:,j)*[uu(:,i);pp(:,i)];
end
figure
for i = 1:8
    subplot(2,4,i);
    plot(y_true(i,:),'k');
    hold on
    plot(y_c(i,:),'r--')
    legend('nonlin','lin')
 
end
hold off
