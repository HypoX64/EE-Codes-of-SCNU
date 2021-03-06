function Hd = filter_FIR_ButterBPF(Fs,Fstop1,Fpass1,Fpass2,Fstop2)
%FILTER_FIR_BUTTERBPF Returns a discrete-time filter object.

% MATLAB Code
% Generated by MATLAB(R) 8.6 and the Signal Processing Toolbox 7.1.
% Generated on: 03-Dec-2017 21:39:40

% FIR Window Bandpass filter designed using the FIR1 function.

% All frequency values are in Hz.
%Fs = 1000;  % Sampling Frequency

%Fstop1 = 50;              % First Stopband Frequency
%Fpass1 = 90;              % First Passband Frequency
%Fpass2 = 110;             % Second Passband Frequency
%Fstop2 = 150;             % Second Stopband Frequency
Dstop1 = 0.001;           % First Stopband Attenuation
Dpass  = 0.057501127785;  % Passband Ripple
Dstop2 = 0.0001;          % Second Stopband Attenuation
flag   = 'scale';         % Sampling Flag

% Calculate the order from the parameters using KAISERORD.
[N,Wn,BETA,TYPE] = kaiserord([Fstop1 Fpass1 Fpass2 Fstop2]/(Fs/2), [0 ...
                             1 0], [Dstop1 Dpass Dstop2]);

% Calculate the coefficients using the FIR1 function.
b  = fir1(N, Wn, TYPE, kaiser(N+1, BETA), flag);
Hd = dfilt.dffir(b);

% [EOF]
