%%%��������һ��
%%%
function [P_norm_stable,T_norm_stable,Wf_norm_stable,N_norm_stable ,P_norm_step,...
    T_norm_step,Wf_norm_step,N_norm_step] = normal_data(data_stable,data_step,data_design,t,T)
% data_stable: stable data
% data_step: step data
% data_design: design data
% t :sample time
% T : sampling period
% �����������һ��ֵ��P ��T�������������һ���ģ���Ҫ�Լ���ȥָ����Ҫ���������У��¶���T�ģ�ѹ����P��
% Wf��ֱ�ӾͿ����ã��������һ��

% ��Ծ���̣�������ģ���ڽ�Ծ�����������������㣬�������ǰ������������ϵ�һ���ˣ���˶�����������
% ����8s���ݣ���������0.02s���õ�������Ӧ����401�������ǲɵ��ľ���403��
% �������û���ý�Ծ���õ��ǳ�������ô���ݾ���������
% if length(data_stable)~= length(data_step)||length(data_stable)~= length(data_design)
%     print('��һ�������У����ݳ��Ȳ�һ��������һ��')
% end
fs = 1/T;
% �����ݹ淶��ָ�����ȣ�ȥ�����������
L = t/T+1;
[a,b] = size(data_stable);
if L>a
    print('���ݳ��Ⱥ�������Ĳ���ʱ���Լ�����Ƶ�ʲ����ϣ�t/T+1�������ݳ�����')
end
data_stable = data_stable(1:L,1:b);
data_step = data_step(1:L,1:b);
data_design = data_design(1:L,1:b);

data_stable_T2 = data_stable(:,16);
data_stable_P2 = data_stable(:,17);
data_stable_Wf = data_stable(:,61);

data_step_T2 = data_step(:,16);
data_step_P2 = data_step(:,17);
data_step_Wf = data_step(:,61);

data_design_T2 = data_design(:,16);
data_design_P2 = data_design(:,17);
data_design_Wf = data_design(:,61);

P_norm_stable = pt_norm(data_stable,data_stable_P2,data_design,data_design_P2);
T_norm_stable = pt_norm(data_stable,data_stable_T2,data_design,data_design_T2);
Wf_norm_stable = Wf_norm(data_stable_Wf,data_stable_P2,data_stable_T2,...
    data_design_Wf,data_design_P2,data_design_T2);
N_norm_stable = N_norm(data_stable,data_stable_T2,data_design,data_design_T2);

P_norm_step = pt_norm(data_step,data_step_P2,data_design,data_design_P2);
T_norm_step = pt_norm(data_step,data_step_T2,data_design,data_design_T2);
Wf_norm_step = Wf_norm(data_step_Wf,data_step_P2,data_step_T2,...
    data_design_Wf,data_design_P2,data_design_T2);
N_norm_step = N_norm(data_step,data_step_T2,data_design,data_design_T2);
end
function PPT = pt_norm(PT,PT2,PT_S,PT2_S)
%%����P��T�Ĺ�һ����û�з��У�ֱ�Ӱ��������󶼼����ˣ�����������
% PT ���������
% PT2 : ��������T2����P2��һ��
% PT_s : ��Ƶ������
% PT2_s : ��Ƶ�����T2����P2��һ��
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

