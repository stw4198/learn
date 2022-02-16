import pandas as pd
import numpy as np
import sys
import ROOT
from array import array
from tqdm import tqdm

file = sys.argv[1]

df = pd.read_csv(file)

ROOT.PyConfig.IgnoreCommandLineOptions = True
ROOT.gROOT.SetBatch(1)

f = ROOT.TFile("ML_classified.root", "RECREATE")
tree = ROOT.TTree("data", "ML Classified Data")
mc_energy = array('f', [0.])
subid = array('f', [0.])
n100 = array('f', [0.])
n100_prev = array('f', [0.])
mcid = array('f', [0.])
innerPE = array('f', [0.])
code = array('i', [0])
tree.Branch("mc_energy", mc_energy, 'mc_energy/F')
tree.Branch("subid", subid, 'subid/F')
tree.Branch("n100", n100, 'n100/F')
tree.Branch("n100_prev", n100_prev, 'n100_prev/F')
tree.Branch("mcid", mcid, 'mcid/F')
tree.Branch("innerPE", innerPE, 'innerPE/F')
tree.Branch("code", code, 'code/I')

# f_fn = ROOT.TFile("fn_ML.root", "RECREATE")
# tree_fn = ROOT.TTree("data", "ML Classified Data")
# mc_energy_fn = array('f', [0.])
# subid_fn = n100_fn = array('f', [0.])
# tree_fn.Branch("mc_energy", mc_energy_fn, 'mc_energy/F')
# tree_fn.Branch("subid", subid_fn, 'subid/F')
# tree_fn.Branch("n100", n100_fn, 'n100/F')

# f_hey = ROOT.TFile("heysham_2_ML.root", "RECREATE")
# tree_hey = ROOT.TTree("data", "ML Classified Data")
# mc_energy_hey = array('f', [0.])
# subid_hey = array('f', [0.])
# n100_hey = array('f', [0.])
# tree_hey.Branch("mc_energy", mc_energy_hey, 'mc_energy/F')
# tree_hey.Branch("subid", subid_hey, 'subid/F')
# tree_hey.Branch("n100", n100_hey, 'n100/F')

# f_tor = ROOT.TFile("torness_ML.root", "RECREATE")
# tree_tor = ROOT.TTree("data", "ML Classified Data")
# mc_energy_tor = array('f', [0.])
# subid_tor = array('f', [0.])
# n100_tor = array('f', [0.])
# tree_tor.Branch("mc_energy", mc_energy_tor, 'mc_energy/F')
# tree_tor.Branch("subid", subid_tor, 'subid/F')
# tree_tor.Branch("n100", n100_tor, 'n100/F')

# f_size = ROOT.TFile("sizewell_b_ML.root", "RECREATE")
# tree_size = ROOT.TTree("data", "ML Classified Data")
# mc_energy_size = array('f', [0.])
# subid_size = array('f', [0.])
# n100_size = array('f', [0.])
# tree_size.Branch("mc_energy", mc_energy_size, 'mc_energy/F')
# tree_size.Branch("subid", subid_size, 'subid/F')
# tree_size.Branch("n100", n100_size, 'n100/F')

# f_hink = ROOT.TFile("hinkley_c_ML.root", "RECREATE")
# tree_hink = ROOT.TTree("data", "ML Classified Data")
# mc_energy_hink = array('f', [0.])
# subid_hink = array('f', [0.])
# n100_hink = array('f', [0.])
# tree_hink.Branch("mc_energy", mc_energy_hink, 'mc_energy/F')
# tree_hink.Branch("subid", subid_hink, 'subid/F')
# tree_hink.Branch("n100", n100_hink, 'n100/F')

# f_grav = ROOT.TFile("gravelines_ML.root", "RECREATE")
# tree_grav = ROOT.TTree("data", "ML Classified Data")
# mc_energy_grav = array('f', [0.])
# subid_grav = array('f', [0.])
# n100_grav = array('f', [0.])
# tree_grav.Branch("mc_energy", mc_energy_grav, 'mc_energy/F')
# tree_grav.Branch("subid", subid_grav, 'subid/F')
# tree_grav.Branch("n100", n100_grav, 'n100/F')

# f_world = ROOT.TFile("world_ML.root", "RECREATE")
# tree_world = ROOT.TTree("data", "ML Classified Data")
# mc_energy_world = array('f', [0.])
# subid_world = array('f', [0.])
# n100_world = array('f', [0.])
# tree_world.Branch("mc_energy", mc_energy_world, 'mc_energy/F')
# tree_world.Branch("subid", subid_world, 'subid/F')
# tree_world.Branch("n100", n100_world, 'n100/F')

# f_geo = ROOT.TFile("geo_ML.root", "RECREATE")
# tree_geo = ROOT.TTree("data", "ML Classified Data")
# mc_energy_geo = array('f', [0.])
# subid_geo = array('f', [0.])
# n100_geo = array('f', [0.])
# tree_geo.Branch("mc_energy", mc_energy_geo, 'mc_energy/F')
# tree_geo.Branch("subid", subid_geo, 'subid/F')
# tree_geo.Branch("n100", n100_geo, 'n100/F')

# f_li9 = ROOT.TFile("li9_ML.root", "RECREATE")
# tree_li9 = ROOT.TTree("data", "ML Classified Data")
# mc_energy_li9 = array('f', [0.])
# subid_li9 = array('f', [0.])
# n100_li9 = array('f', [0.])
# tree_li9.Branch("mc_energy", mc_energy_li9, 'mc_energy/F')
# tree_li9.Branch("subid", subid_li9, 'subid/F')
# tree_li9.Branch("n100", n100_li9, 'n100/F')

# f_n17 = ROOT.TFile("n17_ML.root", "RECREATE")
# tree_n17 = ROOT.TTree("data", "ML Classified Data")
# mc_energy_n17 = array('f', [0.])
# subid_n17 = array('f', [0.])
# n100_n17 = array('f', [0.])
# tree_n17.Branch("mc_energy", mc_energy_n17, 'mc_energy/F')
# tree_n17.Branch("subid", subid_n17, 'subid/F')
# tree_n17.Branch("n100", n100_n17, 'n100/F')

fn = fn_tot = fn_keep = 0
heysham_2 = heysham_2_tot = heysham_2_keep = 0
torness = torness_tot = torness_keep = 0
sizewell_b = sizewell_b_tot = sizewell_b_keep = 0
hinkley_c = hinkley_c_tot = hinkley_c_keep = 0
gravelines = gravelines_tot = gravelines_keep = 0
world = world_tot = world_keep = 0
geo = geo_tot = geo_keep = 0
li9 = li9_tot = li9_keep = 0
n17 = n17_tot = n17_keep = 0
energy = energy_tot = energy_keep = 0

df_fn = df_hey = df_tor = df_size = df_hink = df_grav = df_world = df_li9 = df_n17 = df_geo = pd.DataFrame()

for i in tqdm(range(len(df)-1)):
    if df['source'][i]==1:
        fn_tot+=1
        if df['classifier'][i]==1:
            fn+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            fn+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            fn+=1
        else:
            # df_fn = df_fn.append(df.loc[[i]])
            fn_keep+=1
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==2:
        geo_tot+=1
        if df['classifier'][i]==1:
            geo+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            geo+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            geo+=1
        else:
            geo_keep+=1
            # df_geo = df_geo.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==3:
        heysham_2_tot+=1
        if df['classifier'][i]==1:
            heysham_2+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            heysham_2+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            heysham_2+=1
        else:
            heysham_2_keep+=1
            # df_hey = df_hey.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==4:
        hinkley_c_tot+=1
        if df['classifier'][i]==1:
            hinkley_c+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            hinkley_c+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            hinkley_c+=1
        else:
            hinkley_c_keep+=1
            # df_hink = df_hink.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==5:
        sizewell_b_tot+=1
        if df['classifier'][i]==1:
            sizewell_b+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            sizewell_b+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            sizewell_b+=1
        else:
            sizewell_b_keep+=1
            # df_size = df_size.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==6:
        gravelines_tot+=1
        if df['classifier'][i]==1:
            gravelines+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            gravelines+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            gravelines+=1
        else:
            gravelines_keep+=1
            # df_grav = df_grav.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==7:
        li9_tot+=1
        if df['classifier'][i]==1:
            li9+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            li9+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            li9+=1
        else:
            li9_keep+=1
            # df_li9 = df_li9.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==8:
        n17_tot+=1
        if df['classifier'][i]==1:
            n17+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            n17+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            n17+=1
        else:
            n17_keep+=1
            # df_n17 = df_n17.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==9:
        torness_tot+=1
        if df['classifier'][i]==1:
            torness+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            torness+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1] and i<len(df):
            torness+=1
        else:
            torness_keep+=1
            # df_tor = df_tor.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==10:
        world_tot+=1
        if df['classifier'][i]==1:
            world+=1
        elif df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1] and i>0:
            world+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1]:
            world+=1
        else:
            world_keep+=1
            # df_world = df_world.append(df.loc[[i]])
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
    elif df['source'][i]==11:
        energy_tot+=1
        if df['classifier'][i]==1:
            energy+=1
        elif i>0 and df['classifier'][i]==0 and df['classifier'][i-1]==1 and df['mcid'][i]==df['mcid'][i-1]:
            energy+=1
        elif df['classifier'][i]==0 and df['classifier'][i+1]==1 and df['mcid'][i]==df['mcid'][i+1]:
            energy+=1
        else:
            energy_keep+=1
            mc_energy[0] = df['mc_energy'][i]
            n100[0] = df['n100'][i]
            n100_prev[0] = df['n100_prev'][i]
            subid[0] = df['subid'][i]
            mcid[0] = df['mcid'][i]
            innerPE[0] = df['innerPE'][i]
            code[0] = df['source'][i]
            tree.Fill()
tree.Write("data", ROOT.TObject.kOverwrite)
f.Close()
# tree_fn.Write("data", ROOT.TObject.kOverwrite)
# f_fn.Close()
# tree_hey.Write("data", ROOT.TObject.kOverwrite)
# f_hey.Close()
# tree_tor.Write("data", ROOT.TObject.kOverwrite)
# f_tor.Close()
# tree_size.Write("data", ROOT.TObject.kOverwrite)
# f_size.Close()
# tree_hink.Write("data", ROOT.TObject.kOverwrite)
# f_hink.Close()
# tree_grav.Write("data", ROOT.TObject.kOverwrite)
# f_grav.Close()
# tree_world.Write("data", ROOT.TObject.kOverwrite)
# f_world.Close()
# tree_geo.Write("data", ROOT.TObject.kOverwrite)
# f_geo.Close()
# tree_li9.Write("data", ROOT.TObject.kOverwrite)
# f_li9.Close()
# tree_n17.Write("data", ROOT.TObject.kOverwrite)
# f_n17.Close()

# df_keep = pd.DataFrame()
# df_keep = df_keep.append(df_fn)
# df_keep = df_keep.append(df_hey)
# df_keep = df_keep.append(df_tor)
# df_keep = df_keep.append(df_size)
# df_keep = df_keep.append(df_hink)
# df_keep = df_keep.append(df_grav)
# df_keep = df_keep.append(df_world)
# df_keep = df_keep.append(df_geo)
# df_keep = df_keep.append(df_li9)
# df_keep = df_keep.append(df_n17)
# df_keep.to_csv("ML_class.csv")
print("\nPost-ML:\n\n")
print("Fn total:%i\nFn:%i"%(fn_tot,fn_keep))
print("Heysham 2 total:%i\nHeysham 2:%i"%(heysham_2_tot,heysham_2_keep))
print("Torness total:%i\nTorness:%i"%(torness_tot,torness_keep))
print("Sizewell B total:%i\nSizewell B:%i"%(sizewell_b_tot,sizewell_b_keep))
print("Hinkley C total:%i\nHinkley C:%i"%(hinkley_c_tot,hinkley_c_keep))
print("Gravelines total:%i\nGravelines:%i"%(gravelines_tot,gravelines_keep))
print("World total:%i\nWorld:%i"%(world_tot,world_keep))
print("Geo total:%i\nGeo:%i"%(geo_tot,geo_keep))
print("Li9 total:%i\nLi9:%i"%(li9_tot,li9_keep))
print("N17 total:%i\nN17:%i"%(n17_tot,n17_keep))

hey_rate = 86400*6.894000e-06*heysham_2_keep/100000
tor_rate = 86000*4.419000e-06*torness_keep/100000
siz_rate = 86400*1.330000e-06*sizewell_b_keep/100000
hink_rate = 86400*2.563000e-06*hinkley_c_keep/100000
grav_rate = 86400*2.599000e-06*gravelines_keep/100000
world_rate = 86400*1.474000e-05*world_keep/95000
li9_rate = 86400*3.250000e-05*li9_keep/400000
n17_rate = 86400*1.990000e-05*n17_keep/410000
geo_rate = 86400*6.364000e-06*geo_keep/95000
fn_rate = 86400*0.03217*fn_keep/(0.5*7.897500e+06)

ferr = 0.27
li9err = 0.002
n17err = 0.002
world_err = 0.06
geoerr = 0.25

b_err = np.sqrt((li9err*li9_rate)**2 + (n17err*n17_rate)**2 + (world_err*world_rate)**2 + (geoerr*geo_rate)**2 + (ferr*fn_rate)**2 + (world_err*hink_rate)**2 + (world_err*grav_rate)**2 + (world_err*siz_rate)**2)
s = hey_rate
b = tor_rate + siz_rate + hink_rate + grav_rate + world_rate + li9_rate + n17_rate + geo_rate + fn_rate

t3sigma = 9*b/(s**2 - 9*(b_err)**2)
print(s,b,t3sigma)