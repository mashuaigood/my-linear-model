function [x_hat,y_hat,innov] = c_kalman(y,u,x0,K,A,B,C,D,Q,R)
%%% constant gain kalman filter,linear kalman filter,also simple kalman filter
%y   measurement data ,n*1
%u   control signal , p*1
%x0  the initial value of state value,m*1
%K   kalman gain
%A   m*m
%B   m*p
%C   n*m
%D   n*p
%Q   system noise covarience matrix ,m*m
%R   measurement noise covarience matrix ,n*n
