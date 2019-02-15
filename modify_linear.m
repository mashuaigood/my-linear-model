
data_stable = EngineCLMMSSC_3000_15;
data_step = EngineCLMMSSC_3000_3060_1_15;
data_design = EngineCLMMSSC_s_15;
t = 10;
T = 0.02;
t_step = 1;
[P_norm_stable,T_norm_stable,Wf_norm_stable,N_norm_stable ,P_norm_step,...
    T_norm_step,Wf_norm_step,N_norm_step] = normal_data(data_stable,data_step,data_design,t,T);
P_i = [38,53,59];%序号代表P3,P46,P6
T_i = [28,37,55];%序号代表T22,T3,T5
l_p = length(P_i);
l_t = length(T_i);
[size_a,size_b] = size(P_norm_stable);
PP = zeros(size_a,l_p);
PT = zeros(size_a,l_t);
PN = zeros(size_a,2);
for i = 1:l_p
    PP(:,i) = P_norm_step(:,P_i(i))-P_norm_stable(:,P_i(i));
end
for i = 1:l_t
    PT(:,i) = T_norm_step(:,T_i(i))-T_norm_stable(:,T_i(i));
end
for i =1:2
    PN(:,i) = N_norm_step(:,i)-N_norm_stable(:,i);
end
PWf = Wf_norm_step-Wf_norm_stable;
% 
% PP(PP<0.0000001) = 0;
% PT(PT<0.0000001) = 0;
% PN(PN<0.0000001) = 0;
% PWf(PWf<0.0000001) = 0;

delta_y = PN';
delta_x = PN';
delta_u = PWf';
delta_x_dot = diff(PN,1,1)/T;
delta_x_dot = [delta_x_dot;delta_x_dot(end,:)]';
delta_xx = delta_x(:,2:end);
delta_xx = [delta_xx,delta_x(:,end)];

%控制变量Wf,状态变量Nl,Nh,输出变量Nl,Nh，P3,P46,P6，T22,T3,T5
% A是2*2，B是2*1，C是8*2，D是8*1
A = randn(2,2)*10;
B = randn(2,1)*10;
H0 = [A,B];
% C = randn(8,2);
% D = randn(8,1);
delta_x_dot_l(:,1) = delta_x(:,1);
% for i = 1:size_a
%     
%     delta_x_dot_l(:,i) = A*delta_x(:,i)+B*delta_u(:,i);
%     delta_y_l(1:2,i) = eye(2)*delta_x_dot_l(:,i)+[0;0]*delta_u(:,i);
% end
x = [delta_x;delta_u];
y_ = [delta_xx;delta_y];
l = length(delta_u);
fun = @(H)H(:,1:2)*H(:,3)*delta_u-delta_y
[P,pp] = lsqnonlin(fun,H0);
P(abs(P)<0.000001) = 0;
pp
f =@(xx)(eye(2)-xx^l)*inv(eye(2)-xx)-P(:,1:2);
% xx0 = randn(2,2)*1;
[E,fval] = lsqnonlin(f,xx0)
clear P_i T_i l_p l_t size_a size_b 