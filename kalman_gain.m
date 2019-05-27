

load('data_cal\\A_k.mat');
load('data_cal\\B_k.mat');
load('data_cal\\C_k.mat');
load('data_cal\\D_k.mat');
load('data_cal\\Wf_stable.mat');
load('data_cal\\A.mat');
load('data_cal\\B.mat');
load('data_cal\\C.mat');
load('data_cal\\D.mat');
clear K
%% measurement noise
N_noise = [0.0025,0.0025];
P_noise = [0.005,0.005,0.005,0.005];
T_noise = [0.0075,0.0075,0.0075,0.0075];
R = diag([N_noise,P_noise,T_noise].^2);
%% system noise
Q =  0.0002^2*eye(size(A_k,1));
Q_ = 0.002^2*eye(size(A,1));
%% kalman gain
for k = 1:size(A_k,3)
%     w = 0.002^2*randn(size(Wf_stable{1},1),size(Q,1));
%     v = 0.002^2*randn(size(Wf_stable{1},1),size(R,1));
    [P,~,G] = dare(A_k(:,:,k)',C_k(:,:,k)',Q',R');
    K(:,:,k) = P*C_k(:,:,k)'/(C_k(:,:,k)*P*C_k(:,:,k)'+R);
%     K(:,:,k) = P'*C_k(:,:,k)'/R;
%     K(:,:,k) = G';
    [P_,~,G_] = dare(A(:,:,k)',C(:,:,k)',Q_',R');
    K_s(:,:,k) = P_*C(:,:,k)'/(C(:,:,k)*P_*C(:,:,k)'+R);
end

save('data_cal\\K.mat','K');save('data_cal\\K_s.mat','K_s');
% clear K Q R w v 