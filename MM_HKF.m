%%% multiple model fault diagnosis 

clear
%% load the data and parameters
load('nonlinear_data\\test_data_normal.mat');
data = test_data_normal.data;
load('nonlinear_data\\test_data_normal.mat');
data_normal = test_data_normal.data;
% data = data(1:10000,:);
load('data_cal\\piece.mat');
% load('net_normalANNfit');
load('lrn_net');
num = 1:10;
seve = [0,-0.01,-0.025,-0.03,-0.04];
fault_time = 1000;
cut = 500;
input = [];output = [];
j = 4; k = 3;

y_obem = (data_normal(:,piece.y_index)./piece.mean_design(:,piece.y_index))';
u_obem = (data_normal(:,piece.U_index)./piece.mean_design(:,piece.U_index(1,1)))';
x_obem = (data_normal(:,piece.x_index)./piece.mean_design(:,piece.x_index))';
hp_obem = data_normal(:,piece.HP_index)'-1;
%% preprocess the data,normalize by divide the design point data
y_ = (data(:,piece.y_index)./piece.mean_design(:,piece.y_index))';
u = (data(:,piece.U_index)./piece.mean_design(:,piece.U_index(1,1)))';
x = (data(:,piece.x_index)./piece.mean_design(:,piece.x_index))';
hp = data(:,piece.HP_index)'-1;

% % add fault to sensor data
y = y_;
% measure noise
N_noise = [0.051,0.051]*0.01;
P_noise = [0.164,0.164,0.15,0.15]*0.01;
T_noise = [0.23,0.23,0.097,0.097]*0.01;
y_svar = [N_noise,P_noise,T_noise];
R = diag(y_svar.^2);
meas_noise = sqrt(R)*randn(size(y));
y = y + meas_noise;
% y (num(j),fault_time:end)=  y_(num(j),fault_time:end)+seve(k);
%% kalman estimate
% interpolate the initial parameters
method = 'linear';
% method = 'spline';
x0 = interp1(piece.u_stable_(:,1),piece.x_stable_,u(1,1),method,'extrap');
A = interp_3d(piece.Nl,piece.A,x0(1,1),method);
B = interp_3d(piece.Nl,piece.B,x0(1,1),method);
C = interp_3d(piece.Nl,piece.C,x0(1,1),method);
D = interp_3d(piece.Nl,piece.D,x0(1,1),method);
K = interp_3d(piece.Nl,piece.K_s,x0(1,1),method);
x_s = interp_3d(piece.Nl,piece.steadyState,x0(1,1),method);
y_s = interp_3d(piece.Nl,piece.steadyOutput,x0(1,1),method);
u_s = interp_3d(piece.Nl,piece.steadyInput,x0(1,1),method);
hp_s = interp_3d(piece.Nl,piece.steadyHP,x0(1,1),method);
L = interp_3d(piece.Nl,piece.L,x0(1,1),method);
M = interp_3d(piece.Nl,piece.M,x0(1,1),method);
S = interp_3d(piece.Nl,piece.S_s,x0(1,1),method);
% initialize
delta_x_hat = zeros(size(x,1),size(x,2));
x_hat = zeros(size(x,1),size(x,2));% initialize the augmented x-hat
x_hat(:,1) = x_obem(:,1);
y_hat = zeros(size(y));% initialize y_hat
delta_y_hat = zeros(size(y));
err = zeros(size(y));

%需要插值的全部变成二维
[A_,size_A] = trans3d_2d(piece.A);     A_l = size_A(1)*size_A(2);
[B_,size_B] = trans3d_2d(piece.B);    B_l = size_B(1)*size_B(2);
[C_,size_C] = trans3d_2d(piece.C);    C_l = size_C(1)*size_C(2);
[D_,size_D] = trans3d_2d(piece.D);    D_l = size_D(1)*size_D(2);

[K_,size_K] = trans3d_2d(piece.K_s);    K_l = size_K(1)*size_K(2);
[x_s_,size_x] = trans3d_2d(piece.steadyState);    x_l = size_x(1)*size_x(2);
[y_s_,size_y] = trans3d_2d(piece.steadyOutput);    y_l = size_y(1)*size_y(2);
[u_s_,size_u] = trans3d_2d(piece.steadyInput);    u_l = size_u(1)*size_u(2);
[hp_s_,size_hp] = trans3d_2d(piece.steadyHP);    hp_l = size_hp(1)*size_hp(2);
[L_,size_L] = trans3d_2d(piece.L);    L_l = size_L(1)*size_L(2);
[M_,size_M] = trans3d_2d(piece.M);    M_l = size_M(1)*size_M(2);
[S_,size_S] = trans3d_2d(piece.S_s);    S_l = size_S(1)*size_S(2);
%吧二维的合并在一起，以便同时插值
vec = [A_,B_,C_,D_,K_,x_s_,y_s_,u_s_,hp_s_,L_,M_,S_];

fault_vector = [0,repmat(-0.03,1,12)];
 model_num = length(fault_vector);   

%interpolate

for j = 1:model_num
    % fault vector for ANN input
    f = fault_vector(j);
    input_f = zeros(model_num-1,1);
    if j ==1
        input_f;
    else
        input_f(j-1) = f;
    end
    tic
    for i = 1:size(data,1)-1
        
        % net input
        input_net(:,i) = [input_f;u(:,i);1;1];% 训练网络的时候，传感器故障向量吧输出也放进去了，并不是单纯的向量，现在需要先把输出加上
    % 重新训练一个网络之后在改
%         in_net = con2seq(input_net);

         hp(:,i) = lrn_net(input_net(:,i));
        delta_x_hat(:,i) = x_hat(:,i)-x_obem(:,i);
        delta_y_hat(:,i) = C*delta_x_hat(:,i)+M*hp(:,i);
        y_hat(:,i) = delta_y_hat(:,i)+y_obem(:,i);
        err(:,i) = y(:,i)-y_hat(:,i);
        delta_x_hat(:,i+1) = A*delta_x_hat(:,i)+L*hp(:,i)+K*err(:,i);
        x_hat(:,i+1) = delta_x_hat(:,i+1)+x_obem(:,i+1);
        up = x_hat(1,i+1);
        %概率计算，计算每一个模型的故障概率
%         f(j,i) = 1/(2*pi)^10/sqrt(5*10^-56)*exp(-0.5*err(:,i)'*inv(S)*err(:,i));
        ff(j,i) = exp(-0.5*err(:,i)'*inv(S)*err(:,i));
        
        %插值计算非常耗费时间，可以进行适当优化，吧所有数据归集到一个向量中，
        %进行一次插值，然后再进行分割。这样会节约很多时间，有时间需要进行优化..。。。拖延警告。。。。
        %  已优化,good job
        
        
        out = interp1(piece.Nl,vec,up,method,'extrap');
        % depart parameters
        A =    reshape(out(1:A_l),size_A);
        B =    reshape(out(A_l+1:A_l+B_l),size_B);
        C =    reshape(out(A_l+B_l+1:A_l+B_l+C_l),size_C);
        D =    reshape(out(A_l+B_l+C_l+1:A_l+B_l+C_l+D_l),size_D);
        K =    reshape(out(A_l+B_l+C_l+D_l+1:A_l+B_l+C_l+D_l+K_l),size_K);
        x_s =  reshape(out(A_l+B_l+C_l+D_l+K_l+1:A_l+B_l+C_l+D_l+K_l+x_l),size_x);
        y_s =  reshape(out(A_l+B_l+C_l+D_l+K_l+x_l+1:A_l+B_l+C_l+D_l+K_l+x_l+y_l),size_y);
        u_s =  reshape(out(A_l+B_l+C_l+D_l+K_l+x_l+y_l+1:A_l+B_l+C_l+D_l+K_l+x_l+y_l+u_l),size_u);
        hp_s = reshape(out(A_l+B_l+C_l+D_l+K_l+x_l+y_l+u_l+1:A_l+B_l+C_l+D_l+K_l+x_l+y_l+u_l+hp_l),size_hp);
        L =    reshape(out(A_l+B_l+C_l+D_l+K_l+x_l+y_l+u_l+hp_l+1:A_l+B_l+C_l+D_l+K_l+x_l+y_l+u_l+hp_l+L_l),size_L);
        M =    reshape(out(A_l+B_l+C_l+D_l+K_l+x_l+y_l+u_l+hp_l+L_l+1:A_l+B_l+C_l+D_l+K_l+x_l+y_l+u_l+hp_l+L_l+M_l),size_M);
        S =    reshape(out(A_l+B_l+C_l+D_l+K_l+x_l+y_l+u_l+hp_l+L_l+M_l+1:A_l+B_l+C_l+D_l+K_l+x_l+y_l+u_l+hp_l+L_l+M_l+S_l),size_S);
        
    end
    toc
    input_net(:,i+1) = [input_f;u(:,i+1);1;1];% 训练网络的时候，传感器故障向量吧输出也放进去了，并不是单纯的向量，现在需要先把输出加上
    % 重新训练一个网络之后在
%     in_net = con2seq(input_net);
    hp(:,i+1) = lrn_net(input_net(:,i+1));
    delta_y_hat(:,i+1) = C*delta_x_hat(:,i+1)+M*hp(:,i+1);
    y_hat(:,i+1) = delta_y_hat(:,i+1)+y_obem(:,i+1);
    err(:,i+1) = y(:,i+1)-y_hat(:,i+1);
%     f = exp(-0.5*)
    err_all(:,:,j) = err;
    ff(j,i+1) = exp(-0.5*err(:,i+1)'*inv(S)*err(:,i+1));
    hp_all{j} = hp;
    input_net_all{j} = input_net;
    j
end
p = zeros(size(ff))+0.001;
p0 = [1,zeros(1,12)+0.001]';
for i = 1:size(ff,2)
    vv = zeros(size(err,1),size(err_all,3));
%     for j = 1:size(err_all,3)
%         vv(:,j) = err_all(:,i,j);
%     end
%     f = exp(-0.5*vv'*piece.S_s*vv);

    if i == 1
        sum_ff = sum(ff(:,i).*p0);
        if sum_ff ==0
            sum_ff = 1;
        end
        p(:,i) = ff(:,i).*p0./sum_ff;
    else
         sum_ff = sum(ff(:,i).*p(:,i-1));
        if sum_ff ==0
            sum_ff = 1;
        end
        p(:,i) = ff(:,i).*p(:,i-1)./sum_ff;
    end
    p(p < 0.001) = 0.001;
   
end
    plot(p') 
    
    
clear A_ A_l B_ B_l C_ C_l D_ D_l K_ K_l x_s_ x_l y_s_ y_l u_s_ u_l hp_s_ hp_l ...
    size_A size_B size_C size_D size_K size_x size_y size_u size_hp

%网络输入参数，包括传感器信号，控制信号，马赫数以及飞行高度




