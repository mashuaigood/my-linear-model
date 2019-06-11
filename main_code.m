%%% generate the sensor-fault data ,
% input: fault sensor and severity 
%%% augmented kalman filter design
%
clear
%% load the data and parameters
load('nonlinear_data\\health_data.mat');
data = health_data.data;
% data = data(1:20000,:);
load('data_cal\\piece.mat');
num = 1:10;
seve = [0,-0.01,-0.02,-0.03,-0.04];
fault_time = 1;
cut = 500;
input = [];output = [];
for j = 1:length(num)
    for k = 1:length(seve)
        %% preprocess the data,normalize by divide the design point data
        y_ = (data(:,piece.y_index)./piece.mean_design(:,piece.y_index))';
        u = (data(:,piece.U_index)./piece.mean_design(:,piece.U_index(1,1)))';
        x = (data(:,piece.x_index)./piece.mean_design(:,piece.x_index))';
        hp = data(:,piece.HP_index)'-1;
        y = y_;
        y (num(j),fault_time:end)=  y_(num(j),fault_time:end)+seve(k);
        %% kalman estimate
        % interpolate the initial parameters
        method = 'linear';
        % method = 'spline';
        x0 = interp1(piece.u_stable_(:,1),piece.x_stable_,u(1,1),method,'extrap');
        A = interp_3d(piece.Nl,piece.A_k,x0(1,1),method);
        B = interp_3d(piece.Nl,piece.B_k,x0(1,1),method);
        C = interp_3d(piece.Nl,piece.C_k,x0(1,1),method);
        D = interp_3d(piece.Nl,piece.D_k,x0(1,1),method);
        K = interp_3d(piece.Nl,piece.K,x0(1,1),method);
        x_s = interp_3d(piece.Nl,piece.steadyState,x0(1,1),method);
        y_s = interp_3d(piece.Nl,piece.steadyOutput,x0(1,1),method);
        u_s = interp_3d(piece.Nl,piece.steadyInput,x0(1,1),method);
        hp_s = interp_3d(piece.Nl,piece.steadyHP,x0(1,1),method);
        % estimate
        delta_x_hat = zeros(size(x,1)+size(hp,1),size(x,2));
        x_hat = zeros(size(x,1)+size(hp,1),size(x,2));% initialize the augmented x-hat
        x_hat(:,1) = [x0';hp_s];
        y_hat = zeros(size(y));% initialize y_hat
        delta_y_hat = zeros(size(y));
        err = zeros(size(y));
        
        %需要插值的全部变成二维
        [A_,size_A] = trans3d_2d(piece.A_k);     A_l = size_A(1)*size_A(2);
        [B_,size_B] = trans3d_2d(piece.B_k);    B_l = size_B(1)*size_B(2);
        [C_,size_C] = trans3d_2d(piece.C_k);    C_l = size_C(1)*size_C(2);
        [D_,size_D] = trans3d_2d(piece.D_k);    D_l = size_D(1)*size_D(2);
        [K_,size_K] = trans3d_2d(piece.K);    K_l = size_K(1)*size_K(2);
        [x_s_,size_x] = trans3d_2d(piece.steadyState);    x_l = size_x(1)*size_x(2);
        [y_s_,size_y] = trans3d_2d(piece.steadyOutput);    y_l = size_y(1)*size_y(2);
        [u_s_,size_u] = trans3d_2d(piece.steadyInput);    u_l = size_u(1)*size_u(2);
        [hp_s_,size_hp] = trans3d_2d(piece.steadyHP);    hp_l = size_hp(1)*size_hp(2);
        %吧二维的合并在一起，以便同时插值
        vec = [A_,B_,C_,D_,K_,x_s_,y_s_,u_s_,hp_s_];
        %interpolate
        for i = 1:size(data,1)-1
            delta_y_hat(:,i) = C*delta_x_hat(:,i)+D*(u(:,i)-u_s);
            y_hat(:,i) = delta_y_hat(:,i)+y_s;
            err(:,i) = y(:,i)-y_hat(:,i);
            delta_x_hat(:,i+1) = A*delta_x_hat(:,i)+B*(u(:,i)-u_s)+K*err(:,i);
            x_hat(:,i+1) = delta_x_hat(:,i+1)+[x_s;hp_s];
            up = x_hat(1,i+1);
            %插值计算非常耗费时间，可以进行适当优化，吧所有数据归集到一个向量中，
            %进行一次插值，然后再进行分割。这样会节约很多时间，有时间需要进行优化..。。。拖延警告。。。。
            
            
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
            %     A = interp_3d(piece.Nl,piece.A_k,up,method);
            %     B = interp_3d(piece.Nl,piece.B_k,up,method);
            %     C = interp_3d(piece.Nl,piece.C_k,up,method);
            %     D = interp_3d(piece.Nl,piece.D_k,up,method);
            %     K = interp_3d(piece.Nl,piece.K,up,method);
            %     x_s = interp_3d(piece.Nl,piece.steadyState,up,method);
            %     y_s = interp_3d(piece.Nl,piece.steadyOutput,up,method);
            %     u_s = interp_3d(piece.Nl,piece.steadyInput,up,method);
            %     hp_s = interp_3d(piece.Nl,piece.steadyHP,up,method);
            
        end
        delta_y_hat(:,i+1) = C*delta_x_hat(:,i+1)+D*(u(:,i+1)-u_s);
        y_hat(:,i+1) = delta_y_hat(:,i+1)+y_s;
        err(:,i+1) = y(:,i+1)-y_hat(:,i+1);
        clear A_ A_l B_ B_l C_ C_l D_ D_l K_ K_l x_s_ x_l y_s_ y_l u_s_ u_l hp_s_ hp_l ...
            size_A size_B size_C size_D size_K size_x size_y size_u size_hp
        %网络输入参数，包括传感器信号，控制信号，马赫数以及飞行高度
        l = length(y);
        in = [y(:,cut:end);u(:,cut:end);ones(2,l-cut+1)];
        out = x_hat(3:end,cut:end);
        input = [input,in];
        output = [output,out];
        j
        k
    end
end
save('input.mat','input');
save('output.mat','output');

