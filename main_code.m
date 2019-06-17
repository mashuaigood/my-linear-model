%%% generate the sensor-fault data ,
% input: fault sensor and severity 
%%% augmented kalman filter design
%
clear
%% load the data and parameters
% load('nonlinear_data\\fault_data.mat');
load('nonlinear_data\\data_400s.mat');
data4sensor = train_data_400s.data;
% data = data(1:20000,:);
load('data_cal\\piece.mat');
num = 1:10;
seve = [0,-0.01,-0.02,-0.03,-0.04];
fault_time = 1;
cut = 500;
input1 = [];output1 = [];input2 = [];output2 = [];
f_vec = [];f_vec2 = [];

for j = 1:length(num)
    
    for k = 1:length(seve)
        %% preprocess the data,normalize by divide the design point data
        fault_vector = zeros(12,length(data4sensor));
        fault_vector(j,:) = seve(k);
        y_ = (data4sensor(:,piece.y_index)./piece.mean_design(:,piece.y_index))';
        u = (data4sensor(:,piece.U_index)./piece.mean_design(:,piece.U_index(1,1)))';
        x = (data4sensor(:,piece.x_index)./piece.mean_design(:,piece.x_index))';
        hp = data4sensor(:,piece.HP_index)'-1;
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
        for i = 1:size(data4sensor,1)-1
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
        f_vec = [f_vec,fault_vector];
        l = length(y);
        in = [fault_vector(:,cut:end);u(:,cut:end);ones(2,l-cut+1)];
        out = x_hat(3:end,cut:end);
        input1 = [input1,in];
        output1 = [output1,out];
        j
        k
    end
end
clear in out j k 
%% actuator and component fault data 
%  AC : actuator and component

for k = 1:15
    fault_vector = zeros(12,length(data4sensor));
    if k<=5
        AC_fault_data = eval(['train_data_400s_A_',num2str(k),'PerDe.data']);
        fault_vector(11,:) = eval(['-0.0',num2str(k)]);
    elseif k<=10
        AC_fault_data = eval(['train_data_400s_A_',num2str(k-5),'PerAs.data']);
        fault_vector(11,:) = eval(['0.0',num2str(k-5)]);
    else
        AC_fault_data = eval(['train_data_400s_C_',num2str(k-10),'P.data']);
        fault_vector(12,:) = eval(['-0.0',num2str(k-10)]);
    end
    y = (AC_fault_data (:,piece.y_index)./piece.mean_design(:,piece.y_index))';
    u = (AC_fault_data (:,piece.U_index)./piece.mean_design(:,piece.U_index(1,1)))';
    x = (AC_fault_data (:,piece.x_index)./piece.mean_design(:,piece.x_index))';
    hp = AC_fault_data (:,piece.HP_index)'-1;
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
    for i = 1:size(AC_fault_data ,1)-1
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
    f_vec2 = [f_vec2,fault_vector];
    l = length(y);
    in = [fault_vector(:,cut:end);u(:,cut:end);ones(2,l-cut+1)];
    out = x_hat(3:end,cut:end);
    input2 = [input2,in];
    output2 = [output2,out];
    k
end
input = [input1,input2];
output = [output1,output2];
% save('input.mat','input');
% save('output.mat','output');

