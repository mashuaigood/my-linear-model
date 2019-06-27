p = con2seq(input_re);
t = con2seq(output_re);

lrn_net = layrecnet(1:2,15);
lrn_net.trainFcn = 'trainbr';
lrn_net.trainParam.show = 5;
lrn_net.trainParam.epochs = 500;

% lrn_net.inputs{1}.processFcns = {'removeconstantrows','mapminmax'};
% lrn_net.inputs{2}.processFcns = {'removeconstantrows','mapminmax'};

% lrn_net.divideFcn = 'dividerand';  % Divide data randomly
% lrn_net.divideMode = 'time';  % Divide up every sample
lrn_net.divideParam.trainRatio = 70/100;
lrn_net.divideParam.valRatio = 15/100;
lrn_net.divideParam.testRatio = 15/100;


% Choose a Performance Function
% For a list of all performance functions type: help nnperformance
lrn_net.performFcn = 'mse';  % Mean Squared Error

% Choose Plot Functions
% For a list of all plot functions type: help nnplot
lrn_net.plotFcns = {'plotperform','plottrainstate', 'ploterrhist', ...
    'plotregression', 'plotresponse', 'ploterrcorr', 'plotinerrcorr'};
% [Xs,Xi,Ai,Ts] = preparets(net,p,t);
lrn_net = train(lrn_net,p,t);


% Test the Network
% y = lrn_net(input_re);
% e = gsubtract(output_re,y);
% performance = perform(lrn_net,t,y)


save('lrn_net1.mat','lrn_net')