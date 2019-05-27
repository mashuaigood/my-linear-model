clear all

%% load data and paramater
data_test = load('nonlinear_data\\test_data_1.mat');
data_test1 = data_test.test_data1;
data_test2 = data_test.test_data2;
data_test3 = data_test.test_data3;
data_test4 = data_test.test_data4;
data_design = load('nonlinear_data\\data_design');
data_design = data_design.data_design;
data = load('nonlinear_data\\data_1.mat');

% norm the control variable wf
t = 30;
T = 0.02;
for i=1:4
    j = 1;
    data_stable = eval(['data.data',num2str(j)]);
    data_step = eval(['data_test.test_data',num2str(i)]);
    [P_norm_stable,T_norm_stable,Wf_norm_stable,N_norm_stable ,P_norm_step,...
        T_norm_step,Wf_norm_step,N_norm_step] = normal_data(data_stable,data_step,data_design,t,T);
%     P_i = [20,29,38];%序号代表P13,P22,P3,P5,P8
%     T_i = [19,28,37];%序号代表T13,T22,T3,T5,T8
    P_i = [19,22,28,41,38];%序号代表P13,P24,P3,P5,P45
    T_i = [18,21,27,40,37];%序号代表T13,T24,T3,T5,T45
    l_p = length(P_i);
    l_t = length(T_i);
    [size_a,size_b] = size(P_norm_stable);
    PP = zeros(size_a,l_p);
    PT = zeros(size_a,l_t);
    PN = zeros(size_a,2);
    for k = 1:l_p
        PP(:,k) = P_norm_step(:,P_i(k))-P_norm_stable(:,P_i(k));
    end
    for k = 1:l_t
        PT(:,k) = T_norm_step(:,T_i(k))-T_norm_stable(:,T_i(k));
    end
    for k =1:2
        PN(:,k) = N_norm_step(:,k)-N_norm_stable(:,k);
    end
    PWf = Wf_norm_step-Wf_norm_stable;
    delta_y{i} = [PN,PP,PT]';
    delta_x{i} = PN';
    delta_u{i} = PWf';
    delta_p{i} = data_step(:,52:58)'-1;
    delta_up{i} = [PWf';data_step(:,52:58)'-1];
end   

A_k = dlmread('A_k.mat');
B_k = dlmread('B_k.mat');
C_k = dlmread('C_k.mat');
D_k = dlmread('D_k.mat');
A = dlmread('A.mat');
B = dlmread('B.mat');
C = dlmread('C.mat');
D = dlmread('D.mat');
%% generate noise and covariance 
Q = 0.002^2*eye(size(A_k,2));
R = 0.002^2*eye(size(D_k,1));
w = 0.002^2*randn(size(delta_p{1},2),size(Q,1));
v = 0.002^2*randn(size(delta_p{1},2),size(R,1));
% w = mvnrnd(zeros(size(delta_p{1},2),size(Q,1)),Q);
% v = mvnrnd(zeros(size(delta_p{1},2),size(R,1)),R);

%% 
% 输入和测量值，都是带有噪声的，是从部件级模型上面得到的然后自己添加的噪声
y = delta_y{3}+v';
u = delta_u{3};

%% 计算卡尔曼增益
P = dare(A_k',C_k',Q',R');
K = P*C_k'/(C_k*P*C_k'+R);
xx = zeros(size(A_k,1),size(u,2)+1);
xx(:,1) = C_k\(y(:,1)-D_k*u(:,1));
for i=1:length(u)
    yy(:,i) = C_k*xx(:,i)+D_k*u(:,i);
    xx(:,i+1) = A_k*xx(:,i)+B_k*u(:,i)+K*(y(:,i)-yy(:,i));
%    +w(i,:)'
end

% xx(:,1) = C_k\(y(:,1)-D_k*u(:,1));
% plant = ss(A_k,[B_k B_k],C_k,[D_k D_k] ,-1,'inputname',{'u'},'outputname',{'y'});
% [kamlf z zz zzz ] = kalman(plant,Q,R);
% 
% [out,x] = lsim(kamlf,[u y]);
% kalman1(y',A_k)
i = 4;
plot(delta_y{3}(i,:),'k--');
hold on
plot(yy(i,:),'r:');
hold off
plot(xx(3:end,:)','DisplayName','xx(3:end,:)')