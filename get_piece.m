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
save('data_cal\\piece.mat','piece')
load('nonlinear_data\\health_data')