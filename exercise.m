

close all
j = 5  ;k = 2;       %j represent different N  , k represents different step input
T = 0.02;
uu = delta_step_{j,k}(:,U_index)';
pp = delta_step_{j,k}(:,HP_index)';
x_hat = zeros(size(delta_x{j,k},1),size(delta_x{j,k},2)+1);
y_hat = zeros(size(delta_y{j,k}));
y_true = delta_step_{j,k}(:,[N_i,P_i,T_i])';

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
