
clear
% load('data_cal\\A_k.mat');
% load('data_cal\\B_k.mat');
% load('data_cal\\C_k.mat');
% load('data_cal\\D_k.mat');
for i = 1:10
    load('data_cal\\mean_design.mat');
    eval(['load(''data_cal\\sen',num2str(i),'_A.mat'')']);
    eval(['load(''data_cal\\sen',num2str(i),'_B.mat'')']);
    eval(['load(''data_cal\\sen',num2str(i),'_C.mat'')']);
    eval(['load(''data_cal\\sen',num2str(i),'_D.mat'')']);
    eval(['load(''data_cal\\sen',num2str(i),'_Nl.mat'')']);
    eval(['load(''data_cal\\sen',num2str(i),'_y_stable.mat'')']);
    eval(['load(''data_cal\\sen',num2str(i),'_u_stable.mat'')']);
    eval(['load(''data_cal\\sen',num2str(i),'_D.mat'')']);
    eval(['load(''data_cal\\sen',num2str(i),'_D.mat'')']);
    
    load('nonlinear_data\\data_design');
    load('nonlinear_data\\health_data');
    load('data_cal\\y_index.mat');
    load('nonlinear_data\\engine_data.mat');
    test_data = engine_data.data;
    load('data_cal\\mean_design.mat');
    load('data_cal\\HP_index.mat');load('data_cal\\T_index.mat');
    load('data_cal\\P_index.mat');load('data_cal\\U_index.mat');
    load('data_cal\\y_index.mat');load('data_cal\\x_index.mat');
    
    
    clear K
    %% measurement noise
    y_design = mean_design(y_index);
    N_noise = [0.051,0.051]*0.01;
    P_noise = [0.164,0.164,0.15,0.15]*0.01;
    T_noise = [0.23,0.23,0.097,0.097]*0.01;
    y_svar = [N_noise,P_noise,T_noise];
    y_noise = y_svar;
%     R = diag(y_noise.^2);
    R = 0.003*eye(size(C,1));
    % R = 0.002^2*eye(size(C_k,1));
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
    
    eval(['save(''data_cal\\sen',num2str(i),'_K.mat'',''K'')']);
    % save('data_cal\\K_s.mat','K_s');
    eval(['save(''data_cal\\sen',num2str(i),'_S.mat'',''S'')']);
    % clear K Q R w v
    for j = 1:size(A,3)             %把三维矩阵变成2维，方便插值
        
        y_stable__ = y_stable{j};y_stable_(j,:) = y_stable__(:);
        %     T_stable__ = T_stable{i}(1,T_i);T_stable_(i,:) = T_stable__(:);
        x_stable__ = y_stable{j}(1,[1,2]);x_stable_(j,:) = x_stable__(:);
        u_stable__ = u_stable{j}(1,1:3);u_stable_(j,:) = u_stable__(:);
        steadyInput(:,:,j) = u_stable__';
        steadyState(:,:,j) = x_stable__';
        steadyOutput(:,:,j) =  y_stable__';
        steadyHP(:,:,j) = zeros(length(HP_index),1);
    end
    clear A_k__ B_k__ C_k__ D_k__ P_stable__ T_stable__ N_stable__ Wf_stable__
    
    eval(['sen',num2str(i),'_piece.A = A']);
    eval(['sen',num2str(i),'_piece.B = B']);
    eval(['sen',num2str(i),'_piece.C = C']);
    eval(['sen',num2str(i),'_piece.D = D']);
    
    eval(['sen',num2str(i),'_piece.Nl = Nl']);
    
    eval(['sen',num2str(i),'_piece.steadyInput = steadyInput']);
    eval(['sen',num2str(i),'_piece.steadyOutput = steadyOutput']);
    eval(['sen',num2str(i),'_piece.steadyState = steadyState']);
    
    eval(['sen',num2str(i),'_piece.u_stable_ = u_stable_']);
    eval(['sen',num2str(i),'_piece.x_stable_ = x_stable_']);
    
    eval(['sen',num2str(i),'_piece.y_index = y_index']);
    eval(['sen',num2str(i),'_piece.x_index = x_index']);
    eval(['sen',num2str(i),'_piece.K = K']);
    
    eval(['sen',num2str(i),'_piece.mean_design = mean_design']);
    eval(['sen',num2str(i),'_piece.P_i = P_i']);
    eval(['sen',num2str(i),'_piece.T_i = T_i']);
    
    eval(['sen',num2str(i),'_piece.U_index = U_index']);
    
    
    eval(['sen',num2str(i),'_piece.S = S']);
    
    
    eval(['save(''data_cal\\sen',num2str(i),'_piece.mat'',''sen',num2str(i),'_piece'')']);
    load('nonlinear_data\\health_data')
    load('nonlinear_data\\health_data1')
end

