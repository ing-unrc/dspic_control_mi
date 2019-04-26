%  CARGA DE PARAMETROS DE VEU
%  Proyecto: Tolerancia a fallas en sensores de un AE
%  Facundo Aguilera
%  2019
%--------------------------------------------------------------------------
%  Parámetros para dinámica longitudinal
%  Llamar al script para usar el modelo
%--------------------------------------------------------------------------


% Valores iniciales
w_w_0 = 0;
x_x_0 = 0;
v_x_0 = 00;
tita_w_0 = 0;

% Dimensiones VEU
m_v = 590; % masa
g = 9.81;% gravedad
fi_v = 8*pi/180 ;% inclinacion
L = 1.7; % distancia entre ejes
B = 1.02;
C = 0.68;
H = 0.47;

H_a = H;


% Neumático
n_s = 0.6;
d_s = 5;
K_s = 46;
A_s = 1.12;
B_s = (K_s/d_s)^(1/n_s);
C_s = 0.625;
D_s = 1;
C_r = 0; % coef. resistencia a la rodadura

% Sistema rotacional
J_wr = 1.95;    % inercia de la ruedas
J_wf = J_wr;    
J_t = 0;        % inercia transmision
J_m = 0.02;     % inercia máquina
sigma_wr = 0;   % amortiguamientos
sigma_m = 0.005752;
sigma_wf = sigma_wr;
N_t = 10.3;     % rel. de trans.
eta_t = 0.9;    % eficientia transmision
R = 0.268;      % radio rueda

% fuerza aerodinamica
ro_v = 1.225;
C_d = 0.5;
A_v = 1.4;
v_a_revancha = 0; % velocidad del aire