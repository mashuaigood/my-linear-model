
close all
t = 15;
T = 0.02;
t_step = 1;
data_stable = EngineCLMMSSC_3000_15;
data_step = EngineCLMMSSC_3000_3060_1_15;;
data_design = EngineCLMMSSC_s_15;
[P_norm_stable,T_norm_stable,Wf_norm_stable,N_norm_stable ,P_norm_step,...
    T_norm_step,Wf_norm_step,N_norm_step] = normal_data(data_stable,data_step,data_design,t,T);

P_i = [38,53,59];%��Ŵ���P3,P46,P6
T_i = [28,37,55];%��Ŵ���T22,T3,T5
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

PP(PP<0.0000001) = 0;
PT(PT<0.0000001) = 0;
PN(PN<0.0000001) = 0;
% PWf(PWf<0.0000001) = 0;

delta_y = [PN,PP,PT]';
delta_x = PN';
delta_u = PWf';
delta_x_dot = diff(PN,1,1)/T;
delta_x_dot = [delta_x_dot;delta_x_dot(end,:)]';
delta_xx = delta_x(:,2:end);
delta_xx = [delta_xx,delta_x(:,end)];

A = P(1:2,1:2);B = P(1:2,3);C = P(3:end,1:2);D = P(3:end,3);
xx = zeros(size(delta_x));
yy = zeros(size(delta_y));
xx(:,1) = delta_x(:,1);
for i = 1:size_a
    xx(:,i+1) = A*xx(:,i)+B*delta_u(:,i);
    yy(:,i) = C*xx(:,i)+D*delta_u(:,i);
end    
i = 3;
plot(delta_y(i,:)*100,'k');
hold on
plot(yy(i,:)*100,'r--')
legend('nonlin','lin')
hold off



