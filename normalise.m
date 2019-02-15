
function [Y1,Y2,Y3,Y4] = normalise(EngineCLMMSSC,EngineCLMMSSC_s)

%%%归一化非线性模型的输出，
% EngineCLMMSSC : 运行工况，跳变最好在10S处，总数据30S，如果不是需要在函数里面修改t,t1,t2
% EngineCLMMSSC_s ：设计点的数据
% Y1 ：跳变之前的归一化
% Y2 ：跳变之后的归一化
% Y3 : 没有归一化的原始数据，跳变之前
% Y4 : 没有归一化的原始数据，跳变之后
% 应该吧所有的数据都归一化的，这样还方便。以后再改。。。。。
data = EngineCLMMSSC;
data_s = EngineCLMMSSC_s;  % 设计点参数
t = 30;%采样时间30S
t1 = 8;
t2 = 20;
fs = 1/0.02;
% 10S时候加的阶跃，用第5秒和第20秒作为阶跃前后的稳定状态
% 状态量：高低压转子转速：Nl,Nh,分别在1,2列
Nl_1 = data(t1*fs,1);
Nh_1 = data(t1*fs,2);
Nl_2 = data(t2*fs,1);
Nh_2 = data(t2*fs,2);
Nl_s = data_s(t2*fs,1);
Nh_s = data_s(t2*fs,2);

% 控制变量：燃油流量Wf，高度H，马赫数Ma
Wf_1 = data(t1*fs,61);
Wf_2 = data(t2*fs,61);
Wf_s = data_s(1,61);   %kg/h
H_s = data_s(1,62);
Ma_s = data_s(1,63);
A8_1 = 1;
A8_2 = 1.5;
A8_s = 2;

% 输出值为 Nl,Nh,T22,T3,P3,P43,T5,P6,分别在1,2，28,37,38,53,55,59
T22_1 = data(t1*fs,28);
T3_1 = data(t1*fs,37);
P3_1 = data(t1*fs,38);
P43_1 = data(t1*fs,53);
T5_1 = data(t1*fs,55);
P6_1 = data(t1*fs,59);

T22_2 = data(t2*fs,28);
T3_2 = data(t2*fs,37);
P3_2 = data(t2*fs,38);
P43_2 = data(t2*fs,53);
T5_2 = data(t2*fs,55);
P6_2 = data(t2*fs,59);

T22_s = data_s(t2*fs,28);
T3_s = data_s(t2*fs,37);
P3_s = data_s(t2*fs,38);
P43_s = data_s(20*fs,53);
T5_s = data_s(t2*fs,55);
P6_s = data_s(t2*fs,59);

% others
T2_1 = data(t1*fs,16);
P2_1 = data(t1*fs,17);
T2_2 = data(t2*fs,16);
P2_2 = data(t2*fs,17);
T2_s = data_s(t2*fs,16);
P2_s = data_s(t2*fs,17);

% 归一化计算
PNl_1 = n_trans(Nl_1,T2_1,Nl_s,T2_s);
PNh_1 = n_trans(Nh_1,T2_1,Nh_s,T2_s);
PT22_1 = pt_trans(T22_1,T2_1,T22_s,T2_s);
PT3_1 = pt_trans(T3_1,T2_1,T3_s,T2_s);
PP3_1 =pt_trans(P3_1,P2_1,P3_s,P2_s);
PP43_1 = pt_trans(P43_1,P2_1,P43_s,P2_s);
PT5_1 = pt_trans(T5_1,T2_1,T5_s,T2_s);
PP6_1 = pt_trans(P6_1,P2_1,P6_s,P2_s);
PWf_1 = (Wf_1/P2_1/sqrt(T2_1))/(Wf_s/P2_s/sqrt(T2_s));
PA8_1 = A8_1/A8_s;

PNl_2 = n_trans(Nl_2,T2_2,Nl_s,T2_s);
PNh_2 = n_trans(Nh_2,T2_2,Nh_s,T2_s);
PT22_2 = pt_trans(T22_2,T2_2,T22_s,T2_s);
PT3_2 = pt_trans(T3_2,T2_2,T3_s,T2_s);
PP3_2 =pt_trans(P3_2,P2_2,P3_s,P2_s);
PP43_2 = pt_trans(P43_2,P2_2,P43_s,P2_s);
PT5_2 = pt_trans(T5_2,T2_2,T5_s,T2_s);
PP6_2 = pt_trans(P6_2,P2_2,P6_s,P2_s);
PWf_2 = (Wf_2/P2_2/sqrt(T2_2))/(Wf_s/P2_s/sqrt(T2_s));
PA8_2 = A8_2/A8_s;

Y1 = [PNl_1,PNh_1,PT22_1,PT3_1,PP3_1,PP43_1,PT5_1,PP6_1,PWf_1,PA8_1];
Y2 = [PNl_2,PNh_2,PT22_2,PT3_2,PP3_2,PP43_2,PT5_2,PP6_2,PWf_2,PA8_2];
Y3 = [Nl_1,Nh_1,T22_1,T3_1,P3_1,P43_1,T5_1,P6_1,Wf_1,A8_1];
Y4 = [Nl_2,Nh_2,T22_2,T3_2,P3_2,P43_2,T5_2,P6_2,Wf_2,A8_2];
% 

