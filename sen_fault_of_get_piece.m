

act_piece.A = A;
act_piece.B = B;
% com_piece.BL = BL;
act_piece.C = C;
act_piece.D = D;
% com_piece.DM = DM;
% com_piece.L = L;
% com_piece.M = M;
act_piece.Nl = Nl;
% com_piece.steadyHP = steadyHP;
act_piece.steadyInput = steadyInput;
act_piece.steadyOutput = steadyOutput;
act_piece.steadyState = steadyState;
% piece.U = U;
% piece.HP = HP;
act_piece.u_stable_ = u_stable_;
act_piece.x_stable_ = x_stable_;
% N.time = [];
% N.signals.values = N_norm';
% N.signals.dimensions =2;
% piece.N = N;
act_piece.y_index = y_index;
act_piece.x_index = x_index;
act_piece.K = K;
% com_piece.A_k = A_k;
% com_piece.B_k = B_k;
% com_piece.C_k = C_k;
% com_piece.D_k = D_k;
act_piece.mean_design = mean_design;
act_piece.P_index = P_i ;
act_piece.T_index = T_i; 
% com_piece.HP_index = HP_index;
act_piece.U_index = U_index;
% com_piece.K_s = K_s;
act_piece.S = S;
% com_piece.S_det = S_det;
% com_piece.Nx = Nx;
% com_piece.Ny = Ny;
% com_piece.Nu = Nu;
% com_piece.Nuhp = Nuhp;
save('data_cal\\act_piece.mat','act_piece')
load('nonlinear_data\\health_data')
load('nonlinear_data\\health_data1')