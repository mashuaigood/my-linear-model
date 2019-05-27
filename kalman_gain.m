

load('A_k.mat');
load('B_k.mat');
load('C_k.mat');
load('D_k.mat');
load('Wf_stable.mat');
load('A.mat');
load('B.mat');
load('C.mat');
load('D.mat');
clear K
for k = 1:size(A_k,3)
    
%     Q = 0.002^2*diag([1,1,zeros(1,size(A_k,1)-2)]);
    Q = 0.002^2*eye(size(A_k,1));
    R = 0.002^2*eye(size(D_k,1));
    Q_ = 0.002^2*eye(size(A,1));
    R_ = 0.002^2*eye(size(D,1));
    w = 0.002^2*randn(size(Wf_stable{1},1),size(Q,1));
    v = 0.002^2*randn(size(Wf_stable{1},1),size(R,1));
    [P,~,G] = dare(A_k(:,:,k)',C_k(:,:,k)',Q',R');
    K(:,:,k) = P*C_k(:,:,k)'/(C_k(:,:,k)*P*C_k(:,:,k)'+R);
%     K(:,:,k) = P'*C_k(:,:,k)'/R;
%     K(:,:,k) = G';
    [P_,~,G_] = dare(A(:,:,k)',C(:,:,k)',Q_',R_');
    K_s(:,:,k) = P_*C(:,:,k)'/(C(:,:,k)*P_*C(:,:,k)'+R_);
end

save('K.mat','K');save('K_s.mat','K_s');
% clear K Q R w v 