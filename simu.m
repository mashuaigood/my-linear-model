load('input1.mat');
load('output1.mat');
% 
L = length(input1);
N = fix(L/10);
input_re = input1(:,(1:N)*10);
output_re = output1(:,(1:N)*10);
% 
% omg = simout;
% % %从3000个开始，到3200
% % fir = 3001;
% % en = 3100;
% % l = en-fir+1;
% % xxx = [1,201];
% % yyy = [omg(fir,:)',omg(en,:)'];
% % xxxx = 1:l;
% % y_inter = spline(xxx,yyy,xxxx);
% % omg(fir:en,:) = y_inter';
% % omg(2999:3001,:) = ;
% plot(omg)
% om.time = [];
% om.signals.values = omg;
% om.signals.dimensions = 10;
