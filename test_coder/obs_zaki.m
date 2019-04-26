function [dz,dw_est1] = obs_zaki(z_est, vv, ii,  w)

% Parametros necesarios
% - Observador
%   k, del
% 
% - Maquina
%   AA, BB

% Entradas

a = 1; b = 1; Tr= 1; Rs= 1; Ls = 1; Lm=1; Lr=1;  Rr=1; Tsc=1;

i_d  = ii(1);
i_q  = ii(2);
v_d  = vv(1);
v_q  = vv(2);


i_d_est = z_est(1);
lam_d_est = z_est(2);
lam_q_est = z_est(3);
i_q_est = z_est(4);


% estimador zaki
gama = 40000;


k = 0.001 ;
k1 = -1/(Lm/b);
k2 = k*sign(w);



% Funciones discontinuas


% == Paso 1
eid = i_d_est - i_d;
eiq = i_q_est - i_q;
%ld = 2/(1+exp(-2*eid))-1;
%lq = 2/(1+exp(-2*eiq))-1;
ld = (eid)./(abs(eid)+50);
lq = (eiq)./(abs(eiq)+50);
v_id = 7*ld;
v_iq = 7*lq;

w_est = w;




f1 = ( Lm/Tr*i_d - 1/Tr*lam_d_est - w_est*lam_q_est +( k1*v_id  + k2*v_iq ) );
f2 = ( Lm/Tr*i_q - 1/Tr*lam_q_est + w_est*lam_d_est +( -k2*v_id  + k1*v_iq ));
f3 = (-a*i_q_est + Lm/(b*Tr)*lam_q_est - Lm/b*w_est*lam_d_est + Lr/b*v_q - v_iq);
f4 = (-a*i_d_est + Lm/(b*Tr)*lam_d_est + Lm/b*w_est*lam_q_est + Lr/b*v_d - v_id);

f5 = -((ld*lam_q_est - lq*lam_d_est));

lam_d_est1  = lam_d_est + Tsc*f1;
lam_q_est1  = lam_q_est + Tsc*f2;
i_q_est1    = i_q_est   + Tsc*f3;
i_d_est1    = i_d_est   + Tsc*f4;
dw_est1     = w_est     + Tsc*f5;

% == Paso 2

eid = i_d_est1 - i_d;
eiq = i_q_est1 - i_q;
%ld = 2/(1+exp(-2*eid))-1;
%lq = 2/(1+exp(-2*eiq))-1;
ld = (eid)./(abs(eid)+50);
lq = (eiq)./(abs(eiq)+50);
v_id = 7*ld;
v_iq = 7*lq;

%dw_est1 = w;


f1b = (Lm/Tr*i_d - 1/Tr*lam_d_est1 - dw_est1*lam_q_est1 +( k1*v_id  + k2*v_iq ));
f2b = (Lm/Tr*i_q - 1/Tr*lam_q_est1 + dw_est1*lam_d_est1 +( -k2*v_id  + k1*v_iq ));
f3b = (-a*i_q_est1 + Lm/(b*Tr)*lam_q_est1 - Lm/b*dw_est1*lam_d_est1 + Lr/b*v_q - v_iq );
f4b = (-a*i_d_est1 + Lm/(b*Tr)*lam_d_est1 + Lm/b*dw_est1*lam_q_est1 + Lr/b*v_d - v_id );
f5b = -((ld*lam_q_est1 - lq*lam_d_est1));


lam_d_est1 = lam_d_est + Tsc/2*(f1 + f1b );
lam_q_est1 = lam_q_est + Tsc/2*(f2 + f2b );
i_q_est1   = i_q_est   + Tsc/2*(f3 + f3b ); 
i_d_est1   = i_d_est   + Tsc/2*(f4 + f4b );
dw_est1    = w_est     + gama*Tsc/2*(f5 + f5b );


dz = [i_d_est1; lam_d_est1; lam_q_est1; i_q_est1];


end