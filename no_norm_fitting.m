% 模型线性化，把文件夹中的阶跃数据线性化，得到一系列线性化参数ABCD，并保存起来
clear
t = 30;
T = 0.02;
t_step = 5;
data_design = load('nonlinear_data\\data_design');
data_design = data_design.data_design;
index_data = [0,1,2,4,5,6,7,8,9,10,11,12,13];
U_index = [47,50,51];
index_h = index_data(4:end);
HP_index = index_h+49;
index_l = length(index_data);
x_ = {};T2_index = 12; P2_index = 13; 
T2_design = mean(data_design(:,T2_index));
P2_design = mean(data_design(:,P2_index));
mean_design = mean(data_design,1);
P_i = [19,22,28,38];%序号代表P13,P24,P3,P5,P45
T_i = [18,21,27,37];%序号代表T13,T24,T3,T5,T45 
for j = 1:11
    data = eval(['load(''nonlinear_data\\data',num2str(j),'.mat'')']);
    data_stable = eval(['data.data',num2str(j)]);
    %把每一组数据的稳态工况下的T2和P2取出来，以方便后面的数据恢复工作。
    T2_stable = mean(data_stable(:,T2_index));
    P2_stable = mean(data_stable(:,P2_index));
    TP2_stable(:,j) = [T2_stable,P2_stable]';

    for i = 1:index_l
        data_step = eval(['data.data',num2str(j),'_',num2str(index_data(i))]);
        l_p = length(P_i);
        l_t = length(T_i);
        [size_a,size_b] = size(data_stable);
        PP = zeros(size_a,l_p);
        PT = zeros(size_a,l_t);
        PN = zeros(size_a,2);
        for k = 1:l_p
            PP(:,k) = data_step(:,P_i(k))-data_stable(:,P_i(k));
%             PP(:,k) = P_norm_step(:,P_i(k));
        end
        for k = 1:l_t
            PT(:,k) = data_step(:,T_i(k))-data_stable(:,T_i(k));
%             PT(:,k) = T_norm_step(:,T_i(k));
        end
        for k =1:2
            PN(:,k) = data_step(:,k)-data_stable(:,k);
%             PN(:,k) = N_norm_step(:,k);
        end
        
        PWf = data_step(:,U_index(1))-data_stable(:,U_index(1));
%         PWf = Wf_norm_step;
        
        delta_y{j,i} = [PN,PP,PT]';
        delta_x{j,i} = PN';   %状态变量
        delta_u{j,i} = [PWf';data_step(:,50:51)'];  %控制变量
        delta_p{j,i} = data_step(:,index_h+49)'-1;   %健康参数
        delta_up{j,i} = [delta_u{j,i};data_step(:,index_h+49)'-1];  %控制+健康
        delta_xx{j,i} = delta_x{j,i}(:,2:end);
        delta_xx{j,i} = [delta_xx{j,i},delta_x{j,i}(:,end)];
        x_{j,i} = [delta_x{j,i};delta_up{j,i}];
        y_{j,i} = [delta_xx{j,i};delta_y{j,i}];
    end
    P_stable{j} = data_stable;T_stable{j} = data_stable;N_stable{j} = data_stable;Wf_stable{j} = [data_stable(:,47),data_stable(:,50:51),data_step(:,index_h+49)-1];

    num_state = 2; num_output = l_p+l_t+2; num_control = 3; num_health = length(index_h);
    A = randn(num_state,num_state)*10;
    B = randn(num_state,num_control)*10;
    C = randn(num_output,num_state)*10;
    D = randn(num_output,num_control)*10;
    L = randn(num_state,num_health)*10;
    M = randn(num_output,num_health)*10;
    BL = [B,L];
    DM = [D,M];
    AA = [A,BL];
    CC = [C,DM];
    H0 = [AA;CC];
    yy = [];xx = [];
    for k = 1:size(x_,2)
        xx(:,:,k)=  x_{j,k};
        yy(:,:,k) = y_{j,k};
    end
    fun = @(H)yy - multiply23(H,xx);
    [P,pp] = lsqnonlin(fun,H0);
    P(abs(P)<0.000001) = 0;
    pp
    clear  l_p l_t size_a size_b  A B C D L M BL DM
    P_(:,:,j) = P;
    Nl(j) = data_stable(5,1);  %取一个风扇转速稳态值 
end
save('P_.mat','P_');save('Nl.mat','Nl');
save('P_stable.mat','P_stable');save('T_stable.mat','T_stable');save('N_stable.mat','N_stable');save('Wf_stable.mat','Wf_stable');
for j = 1:size(P_,3)
    Aa = P_(1:num_state,1:num_state,j);
    Ba = P_(1:num_state,num_state+1:num_state+1+num_control-1,j);
    La = P_(1:num_state,num_state+1+num_control:end,j);
    Ca = P_(num_state+1:end,1:num_state,j);
    Da = P_(num_state+1:end,num_state+1:num_state+1+num_control-1,j);
    Ma = P_(num_state+1:end,num_state+1+num_control:end,j);
    BLa = [Ba,La];DMa = [Da,Ma];
    % 把ABCD连续化。通过matlab自带的函数d2c。
%     sys = ss(Aa, BLa, Ca, DMa, T);
%     sys_c = d2c(sys);
%     A(:,:,j) = sys_c.A; BL(:,:,j) = sys_c.B; C(:,:,j) = sys_c.C; DM(:,:,j) = sys_c.D;
    A(:,:,j) = Aa; BL(:,:,j) = BLa; C(:,:,j) = Ca; DM(:,:,j) = DMa; 
end
%% save parameters
B = BL(:,1:size(Ba,2),:);L = BL(:,size(Ba,2)+1:end,:);D = DM(:,1:size(Da,2),:);M = DM(:,size(Da,2)+1:end,:);
save('A.mat','A');save('BL.mat','BL');save('C.mat','C');save('DM.mat','DM');save('D.mat','D');save('M.mat','M');save('B.mat','B');save('L.mat','L');

% 状态方程有变化,需要把健康参数增广到状态变量里面去。
% A_k = [[A,L];repmat([zeros(length(index_h),size(A,2)),zeros(length(index_h),size(L,2))],[1,1,size(A,3)])];
A_k = [[A,L];repmat([zeros(length(index_h),size(A,2)),eye(length(index_h))],[1,1,size(A,3)])];
B_k = [B;repmat(zeros(size(delta_p{1,1},1),size(B,2)),[1,1,size(B,3)])];
C_k = [C,M];
D_k = D;
save('A_k.mat','A_k');save('B_k.mat','B_k');save('C_k.mat','C_k');save('D_k.mat','D_k');
save('mean_design.mat','mean_design');save('TP2_stable.mat','TP2_stable');
save('P_index.mat','P_i');save('T_index.mat','T_i');save('HP_index.mat','HP_index');save('U_index.mat','U_index');



