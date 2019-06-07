
%%% augmented kalman filter design
% 

%% load the data and parameters
load('nonlinear_data\\health_data0.mat');
data = health_data.data;
load('data_cal\\piece.mat');

%% preprocess the data,normalize by divide the design point data
y = (data(:,piece.y_index)./piece.mean_design(:,piece.y_index))';
u = (data(:,piece.U_index)./piece.mean_design(:,piece.U_index(1,1)))';
x = (data(:,piece.x_index)./piece.mean_design(:,piece.x_index))';
hp = data(:,piece.HP_index)'-1;

%% kalman estimate
% interpolate the initial parameters
method = 'linear';
x0 = interp1(piece.u_stable_(:,1),piece.x_stable_,u(1,1),method,'extrap');
A = interp_3d(piece.Nl,piece.A_k,x0(1,1),method);
B = interp_3d(piece.Nl,piece.B_k,x0(1,1),method);
C = interp_3d(piece.Nl,piece.C_k,x0(1,1),method);
D = interp_3d(piece.Nl,piece.D_k,x0(1,1),method);
K = interp_3d(piece.Nl,piece.K,x0(1,1),method);
x_s = interp_3d(piece.Nl,piece.steadyState,x0(1,1),method);
y_s = interp_3d(piece.Nl,piece.steadyOutput,x0(1,1),method);
u_s = interp_3d(piece.Nl,piece.steadyInput,x0(1,1),method);
hp_s = interp_3d(piece.Nl,piece.steadyHP,x0(1,1),method);
% estimate 
delta_x_hat = zeros(size(x,1)+size(hp,1),size(x,2));
x_hat = zeros(size(x,1)+size(hp,1),size(x,2));% initialize the augmented x-hat 
x_hat(:,1) = [x0';hp_s];
y_hat = zeros(size(y));% initialize y_hat
delta_y_hat = zeros(size(y));
err = zeros(size(y));
for i = 1:size(data,1)-1
    delta_y_hat(:,i) = C*delta_x_hat(:,i)+D*(u(:,i)-u_s);
    y_hat(:,i) = delta_y_hat(:,i)+y_s;
    err(:,i) = y(:,i)-y_hat(:,i);
    delta_x_hat(:,i+1) = A*delta_x_hat(:,i)+B*(u(:,i)-u_s)+K*err(:,i);
    x_hat(:,i+1) = delta_x_hat(:,i+1)+[x_s;hp_s];
    up = x_hat(1,i+1);
    A = interp_3d(piece.Nl,piece.A_k,up,method);
    B = interp_3d(piece.Nl,piece.B_k,up,method);
    C = interp_3d(piece.Nl,piece.C_k,up,method);
    D = interp_3d(piece.Nl,piece.D_k,up,method);
    K = interp_3d(piece.Nl,piece.K,up,method);
    x_s = interp_3d(piece.Nl,piece.steadyState,up,method);
    y_s = interp_3d(piece.Nl,piece.steadyOutput,up,method);
    u_s = interp_3d(piece.Nl,piece.steadyInput,up,method);
    hp_s = interp_3d(piece.Nl,piece.steadyHP,up,method);
    
end
