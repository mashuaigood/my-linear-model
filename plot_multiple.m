
close all
load('multiple_data.mat')
t = 0:0.02:500;
aaa(:,1) =u.data(1,1,:); 
figure
color_vec = get(gca,'ColorOrder');
color_vec(1,:) = [0,0,0];
style_vec = {'-','--','-.',':','--','--','--'};
marker_vec = {'none','none','none','none','*','x','+'};
font_size = 16;



figure(1)
% subplot(221)
plot(t,aaa*0.5157,'k','lineWidth',2);
ylim([0.2,0.6])
ylabel('Wf(kg/s)','FontSize',14)
% xlabel({'Time(s)';'(a)'},'FontSize',14)
xlabel('Time(s)','FontSize',14)
grid on
set(gca,'fontsize',font_size);
% set(gca,'xlim',[0 4*pi]);
% set(gca,'xticklabel',[]);
% set(gca,'position',[0.1 0.65 0.8 0.27])
hold on
plot([50,120,200],[0.3,0.4261,0.48],'o',...
    'MarkerEdgeColor',color_vec(1,:),...
    'MarkerFaceColor',color_vec(1,:),...
    'lineWidth',5)
text(60,0.3,'\leftarrow P_2_1故障发生时间','fontsize',15)
text(130,0.4261,{'\leftarrow 执行机构故障发生时间'},'fontsize',15)
text(198,0.508,{'增压级故障发生时间','\downarrow'} ,'fontsize',16)
 
 
figure(2)
% subplot(222)
hold on
for i = 1:size(p_fault1,2)
plot(t,p_fault1(:,i),'color',color_vec(i,:),...
    'lineStyle',style_vec{i},...
    'Marker',marker_vec{i},...
    'MarkerEdgeColor',color_vec(i,:),...
    'MarkerFaceColor',color_vec(i,:),...
    'lineWidth',2)
end
ylim([0,1.4])
xlim([0,100])
ylabel('Mode Probality','FontSize',14)
% xlabel({'Time(s)';'(b)'},'FontSize',14)
xlabel('Time(s)','FontSize',14)
grid on
legend('f_1_1','f_1_2','f_1_3','f_1_4','f_1_5','f_1_6','f_1_7','Location','northwest','NumColumns',7,'fontsize',16)
% set(gca,'xlim',[0 4*pi]);
% set(gca,'xticklabel',[]);
% set(gca,'position',[0.1 0.11 0.8 0.27])
hold off
set(gca,'FontSize',font_size);

figure(3)
% subplot(223)
hold on
for i = 1:size(p_fault2,2)
plot(t,p_fault2(:,i),'color',color_vec(i,:),...
    'lineStyle',style_vec{i},...
    'Marker',marker_vec{i},...
    'MarkerEdgeColor',color_vec(i,:),...
    'MarkerFaceColor',color_vec(i,:),...
    'lineWidth',2)
end
ylim([0,1.4])
xlim([100,150])
ylabel('Mode Probality','FontSize',14)
% xlabel({'Time(s)';'(c)'},'FontSize',14)
xlabel('Time(s)','FontSize',14)
grid on
legend('f_2_1','f_2_2','f_2_3','f_2_4','f_2_5','f_2_6','f_2_7','Location','northwest','NumColumns',7,'fontsize',16)
% set(gca,'xlim',[0 4*pi]);
% set(gca,'xticklabel',[]);
% set(gca,'position',[0.1 0.11 0.8 0.27])
hold off
set(gca,'FontSize',font_size);

figure(4)
% subplot(224)
hold on
for i = 1:size(p_fault3,2)
plot(t,p_fault3(:,i),'color',color_vec(i,:),...
    'lineStyle',style_vec{i},...
    'Marker',marker_vec{i},...
    'MarkerEdgeColor',color_vec(i,:),...
    'MarkerFaceColor',color_vec(i,:),...
    'lineWidth',2)
end
ylim([0,1.4])
xlim([180,220])
ylabel('Mode Probality','FontSize',14)
% xlabel({'Time(s)';'(d)'},'FontSize',14)
xlabel('Time(s)','FontSize',14)
grid on
legend('f_3_1','f_3_2','f_3_3','f_3_4','f_3_5','f_3_6','f_3_7','Location','northwest','NumColumns',7,'fontsize',16)
% set(gca,'xlim',[0 4*pi]);
% set(gca,'xticklabel',[]);
% set(gca,'position',[0.1 0.11 0.8 0.27])
hold off
set(gca,'FontSize',font_size);
