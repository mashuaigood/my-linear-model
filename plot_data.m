

design_data = piece.mean_design;
pwl_err = abs(PWL-y_obem)./y_obem;
HP_HKF_err = abs(HP_HKF-y_obem)./y_obem;
t = 0:0.02:400;

figure(1)
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

sum1 = sum(pwl_err(:,1))
sum2 = sum(HP_HKF_err(:,1))
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
