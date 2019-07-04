
close all
design_data = piece.mean_design;
pwl_err = abs(norm_PWL-y_obem)./y_obem;
HP_HKF_err = abs(norm_HP_HKF-y_obem)./y_obem;

com_pwl_err =  abs(com_PWL-y_obem1)./y_obem1;
com_HP_HKF_err = abs(com_HP_HKF-y_obem1)./y_obem1;
t = 0:0.02:500;
%%  zhengchang  
figure(1)
title('no fault model')
subplot 221
plot(u*design_data(piece.U_index(1)),'k')
ylim([0.25,0.52])
xlabel('Time(s)'),ylabel('Wf(kg/s)'),title('')

subplot 222
plot(t,pwl_err(:,1)*100,'k')
hold on
plot(t,HP_HKF_err(:,1)*100,'r--')
hold off
xlabel('Time(s)'),ylabel('errorN_l(%)'),title(''),legend('PWL','HP-HKF')
% 
% sum1 = sum(pwl_err(:,1))
% sum2 = sum(HP_HKF_err(:,1))
subplot 223
plot(t,pwl_err(:,4)*100,'k')
hold on
plot(t,HP_HKF_err(:,4)*100,'r--')
hold off
xlabel('Time(s)'),ylabel('errorT_2_1(%)'),title(''),legend('PWL','HP-HKF')

subplot 224
plot(t,pwl_err(:,9)*100,'k')
hold on
plot(t,HP_HKF_err(:,9)*100,'r--')
hold off
xlabel('Time(s)'),ylabel('errorP_4_5(%)'),title(''),legend('PWL','HP-HKF')

mse_pwl = sqrt(sum(pwl_err.^2,1));
mse_pwl = mse_pwl';
mse_hp_hkf = sqrt(sum(HP_HKF_err.^2,1));
mse_hp_hkf = mse_hp_hkf';



%%  增压级故障模型对比图
figure(2)
title('component fault model')
subplot 221
plot(u*design_data(piece.U_index(1)),'k')
ylim([0.25,0.52])
xlabel('Time(s)'),ylabel('Wf(kg/s)'),title('')

subplot 222
plot(t,com_pwl_err(:,1)*100,'k')
hold on
plot(t,com_HP_HKF_err(:,1)*100,'r--')
hold off
xlabel('Time(s)'),ylabel('errorN_l(%)'),title(''),legend('PWL','HP-HKF')
% 
% sum1 = sum(pwl_err(:,1))
% sum2 = sum(HP_HKF_err(:,1))
subplot 223
plot(t,com_pwl_err(:,4)*100,'k')
hold on
plot(t,com_HP_HKF_err(:,4)*100,'r--')
hold off
xlabel('Time(s)'),ylabel('errorT_2_1(%)'),title(''),legend('PWL','HP-HKF')

subplot 224
plot(t,com_pwl_err(:,9)*100,'k')
hold on
plot(t,com_HP_HKF_err(:,9)*100,'r--')
hold off
xlabel('Time(s)'),ylabel('errorP_4_5(%)'),title(''),legend('PWL','HP-HKF')

com_mse_pwl = sqrt(sum(com_pwl_err.^2,1));
com_mse_pwl = com_mse_pwl';
com_mse_hp_hkf = sqrt(sum(com_HP_HKF_err.^2,1));
com_mse_hp_hkf = com_mse_hp_hkf';