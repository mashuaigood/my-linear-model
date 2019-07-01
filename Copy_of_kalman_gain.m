

% load('data_cal\\A_k.mat');
% load('data_cal\\B_k.mat');
% load('data_cal\\C_k.mat');
% load('data_cal\\D_k.mat');
 load('data_cal\\mean_design.mat');
load('data_cal\\com_A.mat');
load('data_cal\\com_B.mat');
load('data_cal\\com_C.mat');
load('data_cal\\com_D.mat');
load('data_cal\\y_index.mat');
clear K 
%% measurement noise
y_design = mean_design(y_index);
N_noise = [0.051,0.051]*0.01;
P_noise = [0.164,0.164,0.15,0.15]*0.01;
T_noise = [0.23,0.23,0.097,0.097]*0.01;
y_svar = [N_noise,P_noise,T_noise];
y_noise = y_svar;
R = diag(y_noise.^2);
% R = 0.002^2*eye(size(C_k,1));
%% system noise
% Q =  0.002^2*eye(size(A_k,1));
Q_ = 0.002^2*eye(size(A,1));
%% kalman gain
for k = 1:size(A,3)
%     w = 0.002^2*randn(size(Wf_stable{1},1),size(Q,1));
%     v = 0.002^2*randn(size(Wf_stable{1},1),size(R,1));
%     [P,~,G] = dare(A_k(:,:,k)',C_k(:,:,k)',Q',R');
%     S(:,:,k) = C_k(:,:,k)*P*C_k(:,:,k)'+R;
%     K(:,:,k) = P*C_k(:,:,k)'/(C_k(:,:,k)*P*C_k(:,:,k)'+R);
%     K(:,:,k) = P'*C_k(:,:,k)'/R;
%     K(:,:,k) = G';
    [P_,~,G_] = dare(A(:,:,k)',C(:,:,k)',Q_',R');
    S(:,:,k) = C(:,:,k)*P_*C(:,:,k)'+R;
    S_det(:,:,k) = det(S(:,:,k));
    K(:,:,k) = P_*C(:,:,k)'/(C(:,:,k)*P_*C(:,:,k)'+R);
    R_det = det(R);
end

save('data_cal\\com_K.mat','K');
% save('data_cal\\K_s.mat','K_s');
save('data_cal\\com_S.mat','S');
% clear K Q R w v 