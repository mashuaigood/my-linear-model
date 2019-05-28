clear 
load('nonlinear_data\\data_design');
load('nonlinear_data\\health_data');
load('data_cal\\A.mat');load('data_cal\\BL.mat');
load('data_cal\\C.mat');load('data_cal\\DM.mat');
load('data_cal\\D.mat');load('data_cal\\M.mat');load('data_cal\\B.mat');load('data_cal\\L.mat');
load('data_cal\\Nl.mat');
load('data_cal\\P_stable.mat');load('data_cal\\T_stable.mat');
load('data_cal\\N_stable.mat');load('data_cal\\Wf_stable.mat');
load('nonlinear_data\\engine_data.mat');
test_data = engine_data.data;
load('data_cal\\K.mat');
load('data_cal\\A_k.mat');load('data_cal\\B_k.mat');load('data_cal\\C_k.mat');load('data_cal\\D_k.mat');
load('data_cal\\mean_design.mat');
load('data_cal\\HP_index.mat');load('data_cal\\T_index.mat');load('data_cal\\P_index.mat');load('data_cal\\U_index.mat');

t = (size(test_data,1)-1)*0.02;
T = 0.02;
index_data = [0,1,2,4,5,6,7,8,9,10,11,12,13];
% P_i = [16,22,28,38];%序号代表P13,P24,P3,P5,P45
% T_i = [15,21,27,37];%序号代表T13,T24,T3,T5,T45
P_i = [16,22,28,38];%序号代表P21,P24,P3,P5
T_i = [15,21,27,37];%序号代表T21,T24,T3,T5 
index_h = index_data(4:end);
[P_norm_stable,T_norm_stable,Wf_norm_stable,N_norm_stable ,P_norm_step,...
            T_norm_step,Wf_norm_step,N_norm_step] = normal_data(test_data,test_data,data_design,t,T);

clear A_k_ B_k_ C_k_ D_k_ P_stable_ T_stable_ N_stable_ Wf_stable_

% mean_design(1:2) = mean_design(1:2)*0.0025;
P_norm = P_norm_step(:,P_i)';
T_norm = T_norm_step(:,T_i)';
N_norm = N_norm_step(:,1:2)';
U_norm = [Wf_norm_step,test_data(:,50:51),test_data(:,index_h+49)-1]';

HP.time = [];
HP.signals.values = test_data(:,index_h+49)-1;
HP.signals.dimensions =length(HP_index);
U.time = [];
U.signals.values = [Wf_norm_step,test_data(:,50:51)];
U.signals.dimensions =length(U_index);


for i = 1:size(A,3)             %把三维矩阵变成2维，方便插值
    A_k__ = A(:,:,i);A_k_(i,:) = A_k__(:);
    B_k__ = BL(:,:,i);B_k_(i,:) = B_k__(:);
    C_k__ = C(:,:,i);C_k_(i,:) = C_k__(:);
    D_k__ = DM(:,:,i);D_k_(i,:) = D_k__(:);
    
    P_stable__ = P_stable{i}(1,P_i);P_stable_(i,:) = P_stable__(:);
    T_stable__ = T_stable{i}(1,T_i);T_stable_(i,:) = T_stable__(:);
    N_stable__ = N_stable{i}(1,[1,2]);N_stable_(i,:) = N_stable__(:);
    Wf_stable__ = Wf_stable{i}(1,:);Wf_stable_(i,:) = Wf_stable__(:);
    steadyInput(:,:,i) = Wf_stable__(:,1:3)';
    steadyState(:,:,i) = N_stable__';
    steadyOutput(:,:,i) =  [ N_stable__,P_stable__,T_stable__]';
    steadyHP(:,:,i) = Wf_stable__(:,4:end)';
end
clear A_k__ B_k__ C_k__ D_k__ P_stable__ T_stable__ N_stable__ Wf_stable__


% % Nl_(:,1) = N_norm(1,1);          %初始的索引转速
% % N_ = zeros(size(delta_x));
% delta_x = zeros(2,length(test_data));  Nl_ = zeros(size(delta_x));
% delta_u =  zeros(size(Wf_stable_,2),length(test_data));
% method = 'linear';               %插值方法, 'linear','spline','pchip',or 'cubic'
% for i = 1:length(test_data)-1 
%     N_ss = interp1(Wf_stable_(:,1),N_stable_,U_norm(1,i),method,'extrap')';
%     if i == 1
%         Nl_(:,i) = N_ss;
%     end
%     P_s = interp1(Nl,P_stable_,Nl_(1,i),method,'extrap')';           %根据转速进行插值，寻找转速对应的稳态值
%     T_s = interp1(Nl,T_stable_,Nl_(1,i),method,'extrap')';
%     N_s = interp1(Nl,N_stable_,Nl_(1,i),method,'extrap')';
%     Wf_s = interp1(Nl,Wf_stable_,Nl_(1,i),method,'extrap')';   
%     
%     A_k_0 = reshape(interp1(Nl,A_k_,Nl_(1,i),method,'extrap'),size(A(:,:,1)));   %根据转速进行插值，寻找转速对应的系数矩阵
%     B_k_0 = reshape(interp1(Nl,B_k_,Nl_(1,i),method,'extrap'),size(BL(:,:,1)));
%     C_k_0 = reshape(interp1(Nl,C_k_,Nl_(1,i),method,'extrap'),size(C(:,:,1)));
%     D_k_0 = reshape(interp1(Nl,D_k_,Nl_(1,i),method,'extrap'),size(DM(:,:,1)));
%     if i ==1
%         delta_u(:,i) = U_norm(:,i)-Wf_s;            %计算delta_u
%     end
%     x_dot = A_k_0*delta_x(:,i)+B_k_0*delta_u(:,i);  %状态估计
%     Nl_(:,i+1) = Nl_(:,i)+x_dot*T;
%     delta_x(:,i+1) = Nl_(:,i+1)-N_s;
%     delta_y(:,i) = C_k_0*delta_x(:,i+1)+D_k_0*delta_u(:,i);    %输出估计
%     delta_u(:,i+1) = U_norm(:,i+1)-Wf_s;
% %上面这里总是出错，顺序应该是这样子的：首先通过初始供油量索引出稳态转速，然后用这个稳态转速索引相应的参数ABCD和稳态燃油量。
% %接着用AB计算dotx,然后下一个点的转速就是对dotx积分，初始值是上一个点转速
%     
% end
% 
% plot(Nl_(1,:),'k')
% hold on
% axis tight
% plot(N_norm(1,:),'r')
% legend('linear','non-linear')
% hold off