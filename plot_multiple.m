
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




subplot(221)
plot(t,aaa*0.5157,'k','lineWidth',2);
ylim([0.2,0.6])
ylabel('Wf(kg/s)','FontSize',14)
xlabel({'Time(s)';'(a)'},'FontSize',14)
grid on
set(gca,'fontsize',font_size);
% set(gca,'xlim',[0 4*pi]);
% set(gca,'xticklabel',[]);
% set(gca,'position',[0.1 0.65 0.8 0.27])

subplot(222)
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
xlabel({'Time(s)';'(b)'},'FontSize',14)
grid on
legend('F_1_1','F_1_2','F_1_3','F_1_4','F_1_5','F_1_6','F_1_7','Location','northwest','NumColumns',7,'fontsize',16)
% set(gca,'xlim',[0 4*pi]);
% set(gca,'xticklabel',[]);
% set(gca,'position',[0.1 0.11 0.8 0.27])
hold off
set(gca,'FontSize',font_size);

subplot(223)
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
xlabel({'Time(s)';'(c)'},'FontSize',14)
grid on
legend('F_2_1','F_2_2','F_2_3','F_2_4','F_2_5','F_2_6','F_2_7','Location','northwest','NumColumns',7,'fontsize',16)
% set(gca,'xlim',[0 4*pi]);
% set(gca,'xticklabel',[]);
% set(gca,'position',[0.1 0.11 0.8 0.27])
hold off
set(gca,'FontSize',font_size);

subplot(224)
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
xlabel({'Time(s)';'(d)'},'FontSize',14)
grid on
legend('F_3_1','F_3_2','F_3_3','F_3_4','F_3_5','F_3_6','F_3_7','Location','northwest','NumColumns',7,'fontsize',16)
% set(gca,'xlim',[0 4*pi]);
% set(gca,'xticklabel',[]);
% set(gca,'position',[0.1 0.11 0.8 0.27])
hold off
set(gca,'FontSize',font_size);
