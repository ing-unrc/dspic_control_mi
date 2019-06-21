%  CARGA DE PARAMETROS DE MODELO DE MI
%  Proyecto: Tolerancia a fallas en sensores de un AE
%  Facundo Aguilera
%--------------------------------------------------------------------------
%  Máquina de 750 W
%  2019
%--------------------------------------------------------------------------

%% Parámetros control

Tsc = 0.000054;

vel_cte = 1;
k = 0.00001 ;
k1 = (.09 + 100/(Lm/b));%-0.01/(Lm/b)*0;
k2 = k*sign(vel_cte);

k_gam = 350000;


%% Parámetros de la MI (MATLAB) 

% Sonnaillon
vne = 15.2644;
vn = vne*sqrt(3);
vn_pico = vn*sqrt(2);
Pn =  751.2019;



Vrms_ll = 16.1560*sqrt(3);
P_n = 1250;
nu = 0.76;       % rendimiento
pf = 0.85;      % factor de potencia
f = 50; % frec nominal
P = 4; % polos
PP = P/2;
we_n = 2*pi*f;    
w_mr_n = 1435;  % Velocidad nominal
wr_n = w_mr_n*2*pi/60*P/2; 
wr_mec_n = w_mr_n*2*pi/60; 
wr_i = wr_n/(P/2);
B = 0.005752;
wn=wr_n;    % Velocidad eléctrica nominal



%% MI MSonaillon
Lm = 0.00266;%*1.06;    % Inductancia de magnetización  1.02
Lls = 0.00011;%*1; % Inductancia de estator
Llr = Lls;     % Inductancia de rotor
Rs = 0.0697;%*1.05;     % Resistencia de estator
Rr = 0.03471;%*0.89;%0.90;    % Resistencia de rotor 
J = 0.00294;

Tr=(Llr+Lm)/Rr;      % Constante de tiempo del rotor
 
b = (Lls+Lm).*(Llr+Lm)-Lm.^2;
a = ((Llr+Lm).^2.*Rs + Lm.^2.*Rr) ./ (b.*(Llr+Lm));
Lr = (Llr + Lm);
Ls = (Lls + Lm);
 
 
%% Parámetros del modelo en IQ15
%                 K_{InvTr}       &= \frac{1}{T_r} 2^{15}           &
%                 K_{k1\nu}       &=  k_1 2^{15} \\
%                 K_{k2\nu}       &=  k_2 2^{15} &
%                 K_{\omega}      &= \omega_0 2^{15}                 \\
%                 K_a             &=    -a 2^{15}                    &
%                 K_{L_M\_bT_r}   &= \frac{L_M^2}{b T_r}2^{15}      \\
%                  K_{L_M\_b}     &=  \frac{L_M^2}{b}2^{15}                   &
%                 K_{L_r\_b}      &=  \frac{L_r V_0}{b I_0}2^{15}             \\
%                 K_\gamma       &= -\gamma \frac{\lambda_0}{\omega_0}2^{15} &
%                 K_{T_s}         &= T_{sc} 2^{15}  


% Valores normalización
Imax = 150;
Vmax = 42;

I0= Imax/2^15;
lam0 = Lm*I0;
ome0 = (2*pi*50)/2^15;



% Valores de las constantes de ecuaciones en diferencias
estimZaki.K_InvTr = 1/Tr * 2^15;
estimZaki.K_k1nu  = k1 * 2^15  ;
estimZaki.K_k2nu  = k2 * 2^15  ;
estimZaki.K_ome   = ome0* 2^15 ;
estimZaki.K_a     = - a*2^15   ;
estimZaki.K_Lm_bTr     = Lm^2*2^15/(b*Tr);
estimZaki.K_Lm_b     = Lm^2*2^15/(b);
estimZaki.K_gam     = -k_gam*lam0*2^15/ome0;
estimZaki.K_Ts     =   Tsc * 2^15;


for i=0:15
    if abs(estimZaki.K_InvTr) < 2^15-1
        estimZaki.D_InvTr = i;
        break
    end
    estimZaki.K_InvTr = estimZaki.K_InvTr*1/2;
end

for i=0:15
    if abs(estimZaki.K_k1nu) < 2^15-1
        estimZaki.D_k1nu = i;
        break
    end
    estimZaki.K_k1nu = estimZaki.K_k1nu*1/2;
end

for i=0:15
    if abs(estimZaki.K_k2nu) < 2^15-1
        estimZaki.D_k2nu = i;
        break
    end
    estimZaki.K_k2nu = estimZaki.K_k2nu*1/2;
end

for i=0:15
    if abs(estimZaki.K_ome) < 2^15-1
        estimZaki.D_ome = i;
        break
    end
    estimZaki.K_ome = estimZaki.K_ome*1/2;
end

for i=0:15
    if abs(estimZaki.K_a) < 2^15-1
        estimZaki.D_a = i;
        break
    end
    estimZaki.K_a = estimZaki.K_a*1/2;
end

for i=0:15
    if abs(estimZaki.K_Lm_bTr) < 2^15-1
        estimZaki.D_Lm_bTr = i;
        break
    end
    estimZaki.K_Lm_bTr = estimZaki.K_Lm_bTr*1/2;
end

for i=0:15
    if abs(estimZaki.K_Lm_b) < 2^15-1
        estimZaki.D_Lm_b = i;
        break
    end
    estimZaki.K_Lm_b = estimZaki.K_Lm_b*1/2;
end

for i=0:15
    if abs(estimZaki.K_gam) < 2^15-1
        estimZaki.D_gam = i;
        break
    end
    estimZaki.K_gam = estimZaki.K_gam*1/2;
end

for i=0:15
    if abs(estimZaki.K_Ts) < 2^15-1
        estimZaki.D_Ts = i;
        break
    end
    estimZaki.K_Ts = estimZaki.K_Ts*1/2;
end






%% Textos para pegar en C




