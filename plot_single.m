
close all
t = 0:0.02:500;
aaa(:,1) =u.data(1,1,:); 
figure
color_vec = get(gca,'ColorOrder');
color_vec(1,:) = [0,0,0];
style_vec = {'-','--','-.',':','--','--','--'};
marker_vec = {'none','none','none','none','*','x','+'};

subplot(311)
plot(t,aaa*0.5157,'k','lineWidth',2);
ylim([0.2,0.6])
ylabel('Wf(kg/s)','FontSize',14)
grid on
% set(gca,'xlim',[0 4*pi]);
set(gca,'xticklabel',[]);
set(gca,'position',[0.1 0.65 0.8 0.27])

subplot(312)
hold on
for i = 1:size(fault_vector,2)
plot(t,fault_vector(:,i)*100,'color',color_vec(i+1,:),...
    'lineStyle',style_vec{i+1},...
    'Marker',marker_vec{i+1},...
    'MarkerEdgeColor',color_vec(i+1,:),...
    'MarkerFaceColor',color_vec(i+1,:),...
    'lineWidth',2)
end
ylim([-3,3])
ylabel('Fault Severity(%)','FontSize',14)
% set(gca,'xlim',[0 4*pi]);
set(gca,'xticklabel',[]);
set(gca,'position',[0.1 0.38 0.8 0.27])
grid on
legend('F_2','F_3','F_4','F_5','F_6','F_7','Location','northwest','NumColumns',6)
hold off


subplot(313)
hold on
for i = 1:size(p_fault,2)
plot(t,p_fault(:,i),'color',color_vec(i,:),...
    'lineStyle',style_vec{i},...
    'Marker',marker_vec{i},...
    'MarkerEdgeColor',color_vec(i,:),...
    'MarkerFaceColor',color_vec(i,:),...
    'lineWidth',2)
end
ylim([0,1.2])
ylabel('Mode Probality','FontSize',14)
xlabel('time(s)','FontSize',14)
grid on
legend('F_1','F_2','F_3','F_4','F_5','F_6','F_7','Location','northwest','NumColumns',7)
% set(gca,'xlim',[0 4*pi]);
% set(gca,'xticklabel',[]);
set(gca,'position',[0.1 0.11 0.8 0.27])
hold off