

load('data_cal\\A_k.mat');
load('data_cal\\B_k.mat');
load('data_cal\\C_k.mat');
load('data_cal\\D_k.mat');
 load('data_cal\\mean_design.mat');
load('data_cal\\A.mat');
load('data_cal\\B.mat');
load('data_cal\\C.mat');
load('data_cal\\D.mat');
load('data_cal\\y_index.mat');
load('nonlinear_data\\data_design');
load('nonlinear_data\\health_data');
load('data_cal\\A.mat');load('data_cal\\BL.mat');
load('data_cal\\C.mat');load('data_cal\\DM.mat');
load('data_cal\\D.mat');load('data_cal\\M.mat');load('data_cal\\B.mat');load('data_cal\\L.mat');
load('data_cal\\Nl.mat');
load('data_cal\\y_stable.mat');load('data_cal\\u_stable.mat');
load('nonlinear_data\\engine_data.mat');
test_data = engine_data.data;
load('data_cal\\K.mat');load('data_cal\\K_s.mat');load('data_cal\\S_s.mat');
load('data_cal\\A_k.mat');load('data_cal\\B_k.mat');load('data_cal\\C_k.mat');load('data_cal\\D_k.mat');
load('data_cal\\mean_design.mat');
load('data_cal\\HP_index.mat');load('data_cal\\T_index.mat');load('data_cal\\P_index.mat');load('data_cal\\U_index.mat');
load('data_cal\\y_index.mat');load('data_cal\\x_index.mat');
load('data_cal\\Nx.mat');
load('data_cal\\Ny.mat');
load('data_cal\\Nu.mat');
load('data_cal\\Nuhp.mat');
clear K 
%% measurement noise
y_design = mean_design(y_index);
N_noise = [0.051,0.051]*0.01;
P_noise = [0.164,0.164,0.15,0.15]*0.01;
T_noise = [0.23,0.23,0.097,0.097]*0.01;
y_svar = [N_noise,P_noise,T_noise];
y_noise = y_svar;
R = 0.001*eye(size(C_k,1));
R_ = 0.003*eye(size(C,1));
%% system noise
Q =  0.0001*eye(size(A_k,1));
Q_ = 0.003^2*eye(size(A,1));
%% kalman gain
for k = 1:size(A_k,3)
%     w = 0.002^2*randn(size(Wf_stable{1},1),size(Q,1));
%     v = 0.002^2*randn(size(Wf_stable{1},1),size(R,1));
    [P,~,G] = dare(A_k(:,:,k)',C_k(:,:,k)',Q',R');
    S(:,:,k) = C_k(:,:,k)*P*C_k(:,:,k)'+R;
    K(:,:,k) = P*C_k(:,:,k)'/(C_k(:,:,k)*P*C_k(:,:,k)'+R);
%     K(:,:,k) = P'*C_k(:,:,k)'/R;
%     K(:,:,k) = G';
    [P_,~,G_] = dare(A(:,:,k)',C(:,:,k)',Q_',R_');
    S_s(:,:,k) = C(:,:,k)*P_*C(:,:,k)'+R_;
    S_det(:,:,k) = det(S_s(:,:,k));
    K_s(:,:,k) = P_*C(:,:,k)'/(C(:,:,k)*P_*C(:,:,k)'+R_);
    R_det = det(R_);
end
for i = 1:size(A,3)             %把三维矩阵变成2维，方便插值
    A_k__ = A(:,:,i);A_k_(i,:) = A_k__(:);
    B_k__ = BL(:,:,i);B_k_(i,:) = B_k__(:);
    C_k__ = C(:,:,i);C_k_(i,:) = C_k__(:);
    D_k__ = DM(:,:,i);D_k_(i,:) = D_k__(:);
    
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
save('data_cal\\K.mat','K');save('data_cal\\K_s.mat','K_s');save('data_cal\\S_s.mat','S_s');
% clear K Q R w v 
piece.A = A;
piece.B = B;
piece.BL = BL;
piece.C = C;
piece.D = D;
piece.DM = DM;
piece.L = L;
piece.M = M;
piece.Nl = Nl;
piece.steadyHP = steadyHP;
piece.steadyInput = steadyInput;
piece.steadyOutput = steadyOutput;
piece.steadyState = steadyState;
% piece.U = U;
% piece.HP = HP;
piece.u_stable_ = u_stable_;
piece.x_stable_ = x_stable_;
% N.time = [];
% N.signals.values = N_norm';
% N.signals.dimensions =2;
% piece.N = N;
piece.y_index = y_index;
piece.x_index = x_index;
piece.K = K;
piece.A_k = A_k;
piece.B_k = B_k;
piece.C_k = C_k;
piece.D_k = D_k;
piece.mean_design = mean_design;
piece.P_index = P_i ;
piece.T_index = T_i; 
piece.HP_index = HP_index;
piece.U_index = U_index;
piece.K_s = K_s;
piece.S_s = S_s;
piece.S_det = S_det;
piece.Nx = Nx;
piece.Ny = Ny;
piece.Nu = Nu;
piece.Nuhp = Nuhp;
save('data_cal\\piece.mat','piece')
load('nonlinear_data\\health_data')
load('nonlinear_data\\health_data1')
load('data_cal\\act_piece.mat')
load('data_cal\\sen2_piece.mat')
load('data_cal\\sen3_piece.mat')
load('data_cal\\sen8_piece.mat')
load('data_cal\\com_piece.mat')