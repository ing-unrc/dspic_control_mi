%  CARGA DE PARAMETROS DE MODELO DE MI
%  Proyecto: Tolerancia a fallas en sensores de un AE
%  Facundo Aguilera
%--------------------------------------------------------------------------
%  Máquina de 3 kw usada en VEU
%  Se cargan parámetros para simulación
%--------------------------------------------------------------------------

%% Parámetros de la MI (MATLAB) 
% Potencia nominal: 3500    
% Vll: 460
% Frec: 60
% Velocidad nominal: wr_n = 1750*2*pi/60*P/2
% J = 0.025


%% Control
Tsc = 0.000054


%% Valores de parámetros
Vrms_ll = 28*sqrt(3);
P_n = 3000;
nu = 0.76;       % rendimiento
pf = 0.85;      % factor de potencia
f = 50; % frec nominal
P = 4; % polos
PP = P/2;
we_n = 2*pi*f;    
w_mr_n      = 1410;  % Velocidad nominal
wr_n        = w_mr_n*2*pi/60*P/2; 
wr_mec_n    = w_mr_n*2*pi/60; 
wr_i        = wr_n/(P/2);
wn          = wr_n;    % Velocidad eléctrica nominal

% Valores preliminares (funcionan, 2.4 kW)
%Lm = 0.3698;    % Inductancia de magnetización
%Lls = 0.0128;   % Inductancia de estator
%Llr = Lls;     % Inductancia de rotor
%Rs = 1.7700;    % Resistencia de estator
%Rr = 1.2555;   % Resistencia de rotor

% Potencia nominal: 3730
%  Lm = 0.2037;    % Inductancia de magnetización
%  Lls = 0.005974; % Inductancia de estator
%  Llr = Lls;     % Inductancia de rotor
%  Rs = 1.115;     % Resistencia de estator
%  Rr = 1.083;    % Resistencia de rotor
%  J = 0.025;


%% MI MSonaillon
Rs = 0.0274;%*1.05;     % Resistencia de estator
Rr = 0.03841;%*0.89;%0.90;    % Resistencia de rotor 
Lm = 0.003940447;%*1.06;    % Inductancia de magnetización  1.02
Lls = 0.000180239;%*1; % Inductancia de estator
Llr = Lls;     % Inductancia de rotor
J = 0.00294;




 Tr=(Llr+Lm)/Rr;      % Constante de tiempo del rotor

 
b = (Lls+Lm).*(Llr+Lm)-Lm.^2;
a = ((Llr+Lm).^2.*Rs + Lm.^2.*Rr) ./ (b.*(Llr+Lm));
Lr = (Llr + Lm);
Ls = (Lls + Lm);
 
 sigma = (1- Lm^2/(Ls*Lr));
 
 ws = 0;
%% Valores de exitación y del modelo

Vp = sqrt(2) * Vrms_ll/sqrt(3);
%
tita0 = 0;
tita_r0 = 0;

% lambda_qd0sr = Lqd0 * iqdsr0
Lqd0 = [Lls+Lm, 0, 0, Lm, 0, 0; ...
        0, Lls+Lm, 0, 0, Lm, 0; ...
        0, 0, Lls, 0, 0, 0; ...
        Lm, 0, 0, Llr+Lm, 0, 0; ...
        0, Lm, 0, 0, Llr+Lm, 0; ...
        0, 0, 0, 0, 0, Llr];
 
inv_Lqd0 = inv(Lqd0);

 
%% Valores nominales

%wr_n = we_n
S = (we_n - wr_n)/we_n; 
Z_i = Rs + 1i*we_n*Lls +( 1/(1i*we_n*Lm) + 1/(Rr/S+1i*we_n*Llr) )^-1;
Isp_i = Vp / Z_i;
I1rp_i = -Isp_i * 1i*we_n*Lm / (Rr/S+1i*we_n*Llr+1i*we_n*Lm);
Te_i = 3*P*Lm/4 * imag(Isp_i * conj(I1rp_i))
Te_n = Te_i

Pot = wr_mec_n*Te_i
% CoRrientes qd0
iqs_i = real(Isp_i);
ids_i = -imag(Isp_i);
i0s_i = 0;

i1qr_i = real(I1rp_i);
i1dr_i = -imag(I1rp_i);
i10r_i = 0;

iqd0s_i = [iqs_i; ids_i; i0s_i];

i1qd0r_i = [i1qr_i; i1dr_i; i10r_i];


% Flujos qd0 
lambda_qd0sr_i = Lqd0 * [iqd0s_i; i1qd0r_i];
lambda_qd0s_i =  ...    % Flujos iniciales
    lambda_qd0sr_i(1:3);
lambda1_qd0r_i  = lambda_qd0sr_i(4:6);




%% Corrientes nominales control
iqs_n = real(Isp_i);
ids_n = -imag(Isp_i);
i1qr_n = real(I1rp_i);
i1dr_n = -imag(I1rp_i);
lambda_drn = Llr * i1dr_n + Lm * (ids_n + i1dr_n);