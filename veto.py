import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys
from scipy import integrate

file = sys.argv[1]
tank = int(sys.argv[2])
sig = sys.argv[3]

muon_rate = 4.09e-8
if tank == 16:
    pmt = 5.7
elif tank == 22:
    pmt = 9.0
elif tank == 28:
    pmt = 12.0
    
#Read in rates as csv
df = pd.read_csv(file)
df = df.set_index('Component')

components = ["Hartlepool 1",\
"Hartlepool 2",\
"Heysham",\
"Heysham 2",\
"Torness",\
"World",\
"Geo",\
"Li9",\
"N17",\
"FN",\
]

radio = ["Li9",\
"N17",\
]

other = ["Hartlepool 1",\
"Hartlepool 2",\
"Heysham",\
"Heysham 2",\
"Torness",\
"World",\
"Geo",\
"FN",\
]

rates = []
fn_cl = 3.69
for i in components:
    if i == 'FN':
        if df.loc[i,"%i kept"%tank] == 0:
            df.loc[i,"%i kept"%tank]=fn_cl
            rates.append(df.loc[i,"%i kept"%tank]*df.loc[i,'%i rate'%tank]*86400/df.loc[i,'%i MC'%tank])
    else:
        rates.append(df.loc[i,"%i kept"%tank]*df.loc[i,'%i rate'%tank]*86400/df.loc[i,'%i MC'%tank])

d = {'components':components,'rates':rates}
df_analysis = pd.DataFrame(data=d)
df_analysis = df_analysis.set_index('components')

if sig == "hartlepool":
    signal_components = ["Hartlepool 1","Hartlepool 2"]
    background_components = ["Heysham",\
    "Torness",\
    "World",\
    "Geo",\
    "Li9",\
    "N17",\
    "FN",\
    ]
elif sig == "heysham":
    signal_components = ["Heysham"]
    background_components = ["Torness",\
    "World",\
    "Geo",\
    "Li9",\
    "N17",\
    "FN",\
    ]
elif sig == "heysham2":
    signal_components = ["Heysham 2"]
    background_components = ["Torness",\
    "World",\
    "Geo",\
    "Li9",\
    "N17",\
    "FN",\
    ]
elif sig == "torness":
    signal_components = ["Torness"]
    background_components = ["Heysham 2",\
    "World",\
    "Geo",\
    "Li9",\
    "N17",\
    "FN",\
    ]
elif sig == "heytor":
    signal_components = ["Torness","Heysham 2"]
    background_components = ["World",\
    "Geo",\
    "Li9",\
    "N17",\
    "FN",\
    ]

signal = 0
background = 0

d = {'components':components,'rates':rates}
df_muon = pd.DataFrame(data=d)
df_muon = df_muon.set_index('components')

muon_eff = 0.95
t_half_n17 = 4.173
t_half_li9 = 0.1783
def integrand_n17(t):
    return np.exp(-np.log(2)*t/t_half_n17)
def integrand_li9(t):
    return np.exp(-np.log(2)*t/t_half_li9)
t_dead = np.arange(0,15.5,1)

t3sigma = []
s_ = []
b_ = []
b_err_ = []
for i in range(len(t_dead)):
    s = 0
    b = 0
    f = 0
    ferr = 0.27
    li9 = 0
    li9err = 0.002
    n17 = 0
    n17err = 0.002
    world = 0
    world_err = 0.06
    geo = 0
    geoerr = 0.25
    R_n17_cor = 1-muon_eff+muon_eff*integrate.quad(integrand_n17,t_dead[i],np.infty)[0]/integrate.quad(integrand_n17,0,np.infty)[0]
    R_li9_cor = 1-muon_eff+muon_eff*integrate.quad(integrand_li9,t_dead[i],np.infty)[0]/integrate.quad(integrand_li9,0,np.infty)[0]

    for i in signal_components:
        s+=df_muon.loc[i,'rates']
    for k in background_components:
        if k!="Li9" and k!="N17" and k!="World" and k!="Geo":
            b+=df_muon.loc[k,'rates']
        elif k=="World":
            b+=df_muon.loc[k,'rates']
            world+=df_muon.loc[k,'rates']
        elif k=="Geo":
            b+=df_muon.loc[k,'rates']*.3
            geo+=df_muon.loc[k,'rates']*.3
        elif k=="Li9":
            b+=df_muon.loc[k,'rates']*R_li9_cor
            li9+=df_muon.loc[k,'rates']*R_li9_cor
        elif k=="N17":
            b+=df_muon.loc[k,'rates']*R_n17_cor
            n17+=df_muon.loc[k,'rates']*R_n17_cor

    b_err_1 = np.sqrt((li9err*li9)**2 + (n17err*n17)**2 + (world_err*world)**2 + (geoerr*geo)**2 + (ferr*f)**2)
    b_err = b*b_err_1
    t_3 = 9*b/(s**2 - 9*(b_err)**2)
    t3sigma.append(t_3)
    s_.append(s)
    b_.append(b)
    b_err_.append(b_err)

plt.plot(t_dead,t3sigma)
plt.ylim(0,max(t3sigma))
plt.xlim(np.argmax(t3sigma),max(t_dead))
plt.grid()
plt.ylabel("Time to 3\u03C3 [days]")
plt.xlabel("Deadtime [s]")
#plt.title("%s"%sig)
plt.clf()

if t3sigma[1]<0:
    print("Dwell time does not converge (Gaussian) for veto of %f s"%t_dead[1])
else:
    print("Dwell time (Gaussian) =",t3sigma[1],"days")

t = np.arange(0.01,30,0.01)
s = s_[1]
b = b_[1]
b_err = b_err_[1]
sigma = np.sqrt(2*((s*t + b*t)*np.log((s*t + b*t)*(b*t + b_err**2*t**2)/(b**2*t**2 + (s*t + b*t)*b_err**2*t**2))\
     - (b**2*t**2)*np.log(1 + (b_err**2*t**2*s*t)/(b*t*(b*t + b_err**2*t**2)))/(b_err**2*t**2)))

if max(sigma)<3:
    print("Dwell time does not converge (Poisson) for veto of %f s"%t_dead[1])
else:
    time_index = [ n for n,i in enumerate(sigma) if i>3][0]
    print("Dwell time (Gaussian) =",t[time_index],"days")
print("Signal rate =",s,"per day")
print("Background =",b,"+/-",b_err,"per day")