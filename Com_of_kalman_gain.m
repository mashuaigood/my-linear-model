
clear
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
% R = diag(y_noise.^2);
% R = 0.002^2*eye(size(C_k,1));
R = 0.003*eye(size(C,1));
%% system noise
% Q =  0.002^2*eye(size(A_k,1));
Q_ = 0.003^2*eye(size(A,1));
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
load('nonlinear_data\\data_design');
load('nonlinear_data\\health_data');
load('data_cal\\com_A.mat');%load('data_cal\\BL.mat');
load('data_cal\\com_C.mat');%load('data_cal\\DM.mat');
load('data_cal\\com_D.mat');%load('data_cal\\M.mat');
load('data_cal\\com_B.mat');%load('data_cal\\L.mat');
load('data_cal\\com_Nl.mat');
load('data_cal\\com_y_stable.mat');load('data_cal\\com_u_stable.mat');
load('nonlinear_data\\engine_data.mat');
test_data = engine_data.data;
load('data_cal\\com_K.mat');%load('data_cal\\K_s.mat');
load('data_cal\\com_S.mat');
% load('data_cal\\A_k.mat');load('data_cal\\B_k.mat');load('data_cal\\C_k.mat');load('data_cal\\D_k.mat');
load('data_cal\\mean_design.mat');
load('data_cal\\HP_index.mat');load('data_cal\\T_index.mat');load('data_cal\\P_index.mat');load('data_cal\\U_index.mat');
load('data_cal\\y_index.mat');load('data_cal\\x_index.mat');
for i = 1:size(A,3)             %把三维矩阵变成2维，方便插值
%     A_k__ = A(:,:,i);A_k_(i,:) = A_k__(:);
%     B_k__ = BL(:,:,i);B_k_(i,:) = B_k__(:);
%     C_k__ = C(:,:,i);C_k_(i,:) = C_k__(:);
%     D_k__ = DM(:,:,i);D_k_(i,:) = D_k__(:);
    
    y_stable__ = y_stable{i};y_stable_(i,:) = y_stable__(:);
%     T_stable__ = T_stable{i}(1,T_i);T_stable_(i,:) = T_stable__(:);
    x_stable__ = y_stable{i}(1,[1,2]);x_stable_(i,:) = x_stable__(:);
    u_stable__ = u_stable{i}(1,1:3);u_stable_(i,:) = u_stable__(:);
    steadyInput(:,:,i) = u_stable__';
    steadyState(:,:,i) = x_stable__';
    steadyOutput(:,:,i) =  y_stable__';
    steadyHP(:,:,i) = zeros(length(HP_index),1);
end
clear A_k__ B_k__ C_k__ D_k__ P_stable__ T_stable__ N_stable__ Wf_stable__
com_piece.A = A;
com_piece.B = B;
% com_piece.BL = BL;
com_piece.C = C;
com_piece.D = D;
% com_piece.DM = DM;
% com_piece.L = L;
% com_piece.M = M;
com_piece.Nl = Nl;
% com_piece.steadyHP = steadyHP;
com_piece.steadyInput = steadyInput;
com_piece.steadyOutput = steadyOutput;
com_piece.steadyState = steadyState;
% piece.U = U;
% piece.HP = HP;
com_piece.u_stable_ = u_stable_;
com_piece.x_stable_ = x_stable_;
% N.time = [];
% N.signals.values = N_norm';
% N.signals.dimensions =2;
% piece.N = N;
com_piece.y_index = y_index;
com_piece.x_index = x_index;
com_piece.K = K;
% com_piece.A_k = A_k;
% com_piece.B_k = B_k;
% com_piece.C_k = C_k;
% com_piece.D_k = D_k;
com_piece.mean_design = mean_design;
com_piece.P_index = P_i ;
com_piece.T_index = T_i; 
% com_piece.HP_index = HP_index;
com_piece.U_index = U_index;
% com_piece.K_s = K_s;
com_piece.S = S;
% com_piece.S_det = S_det;
% com_piece.Nx = Nx;
% com_piece.Ny = Ny;
% com_piece.Nu = Nu;
% com_piece.Nuhp = Nuhp;
save('data_cal\\com_piece.mat','com_piece')
load('nonlinear_data\\health_data')
load('nonlinear_data\\health_data1')
save('data_cal\\com_K.mat','K');
% save('data_cal\\K_s.mat','K_s');
save('data_cal\\com_S.mat','S');
% clear K Q R w v 