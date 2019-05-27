%%%将向量归一化
%%%
function [P_norm_stable,T_norm_stable,Wf_norm_stable,N_norm_stable ,P_norm_step,...
    T_norm_step,Wf_norm_step,N_norm_step] = normal_data(data_stable,data_step,data_design,t,T)
% data_stable: stable data
% data_step: step data
% data_design: design data
% t :sample time
% T : sampling period
% 输出的六个归一化值，P 和T都是整个矩阵归一化的，需要自己再去指定需要的在哪里列，温度用T的，压力用P的
% Wf是直接就可以用，输出就是一列


fs = 1/T;
% 把数据规范到指定长度，去掉多的两个点
L = t/T+1;
t2 = 12;p2 = 13;wf = 47;%t2 p2 wf 的索引位置


[a,b] = size(data_design);
if L>a
%     print('数据长度和你输入的采样时间以及采样频率不符合，t/T+1大于数据长度了')
    data_stable_ = repmat(data_stable(1,:),[L,1]);
    data_step = data_step(1:L,1:b);
    data_design_ = repmat(data_design(1,:),[L,1]);
else
    data_stable_ = data_stable(1:L,1:b);
    data_step = data_step(1:L,1:b);
    data_design_ = data_design(1:L,1:b);
end


data_stable_T2 = data_stable_(:,t2);
data_stable_P2 = data_stable_(:,p2);
data_stable_Wf = data_stable_(:,wf);

data_step_T2 = data_step(:,t2);
data_step_P2 = data_step(:,p2);
data_step_Wf = data_step(:,wf);

data_design_T2 = data_design_(:,t2);
data_design_P2 = data_design_(:,p2);
data_design_Wf = data_design_(:,wf);

P_norm_stable = pt_norm(data_stable_,data_stable_P2,data_design_,data_design_P2);
T_norm_stable = pt_norm(data_stable_,data_stable_T2,data_design_,data_design_T2);
Wf_norm_stable = Wf_norm(data_stable_Wf,data_stable_P2,data_stable_T2,...
    data_design_Wf,data_design_P2,data_design_T2);
N_norm_stable = N_norm(data_stable_,data_stable_T2,data_design_,data_design_T2);

P_norm_step = pt_norm(data_step,data_step_P2,data_design_,data_design_P2);
T_norm_step = pt_norm(data_step,data_step_T2,data_design_,data_design_T2);
Wf_norm_step = Wf_norm(data_step_Wf,data_step_P2,data_step_T2,...
    data_design_Wf,data_design_P2,data_design_T2);
N_norm_step = N_norm(data_step,data_step_T2,data_design_,data_design_T2);
end
function PPT = pt_norm(PT,PT2,PT_S,PT2_S)
%%计算P和T的归一化，没有分列，直接把整个矩阵都计算了，出来再挑吧
% PT ：输入矩阵
% PT2 : 输入矩阵的T2或者P2那一列
% PT_s : 设计点的数据
% PT2_s : 设计点矩阵的T2或者P2那一列
[c,d] = size(PT);
for i = 1:d
    PPT(:,i) = (PT(:,i)./PT2)./(PT_S(:,i)./PT2_S);
end
end

function PWf = Wf_norm(Wf,P2,T2,Wf_S,P2_S,T2_S)
    PWf = (Wf.*sqrt(T2)./P2)./(Wf_S.*sqrt(T2_S)./P2_S);
end

function PN = N_norm(N,T2,N_S,T2_S)
[c,d] = size(N);
for i = 1:d
    PN(:,i) = (N(:,i)./T2)./(N_S(:,i)./T2_S);
end
end

