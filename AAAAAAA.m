piece.A = A;
piece.B = B;piece.BL = BL;
piece.C = C;
piece.D = D;piece.DM = DM;
piece.L = L;
piece.M = M;
piece.Nl = Nl;
piece.steadyHP = steadyHP;
piece.steadyInput = steadyInput;piece.steadyOutput = steadyOutput;
piece.steadyState = steadyState;
piece.U = U;
piece.HP = HP;piece.Wf_stable_ = Wf_stable_;piece.N_stable_ = N_stable_;
N.time = [];
N.signals.values = N_norm';
N.signals.dimensions =2;
piece.N = N;
piece.K = K;
piece.A_k = A_k;
piece.B_k = B_k;
piece.C_k = C_k;
piece.D_k = D_k;
piece.mean_design = mean_design;
piece.P_index = P_i ; piece.T_index = T_i; 
piece.HP_index = HP_index;piece.U_index = U_index;
piece.K_s = K_s;
save('data_cal\\piece.mat','piece')
load('nonlinear_data\\engine_data1')