import numpy as np
import pandas 
from matplotlib import pyplot as plt, cm as cmap
import os 
os.chdir(os.path.dirname(os.path.abspath(__file__)))

### Constants
AIR_DENSITY     = 1.225         * 1e0   # kg/m**3
AIR_VISCOSITY   = 1.7894e-5     * 1e0   # kg/m/s  or Pa*s (Dynamic)

### Config
# MEAN_CHORD      = 200           * 1e-3  # mm
# WINGSPAN        = 1200          * 1e-3  # mm
# ASPECT_RATIO    = WINGSPAN/MEAN_CHORD

alpha,reynolds,cl,cd,cm = np.load("tkv2008_analysis_3.npy",allow_pickle=True)


def lift(WINGSPAN,WING_AREA,idrag):
    MEAN_CHORD = WING_AREA/WINGSPAN
    ASPECT_RATIO = WINGSPAN/MEAN_CHORD
    print(f'Wingspan {WINGSPAN}\nArea {WING_AREA}\nMean chord {MEAN_CHORD}\nAR {ASPECT_RATIO}')

    velocity = AIR_VISCOSITY * reynolds / AIR_DENSITY / MEAN_CHORD
    efficiency = 1/(1+idrag)

    CL = np.zeros(cl.shape)
    for index,rey in enumerate(reynolds):
        cl_r = cl[:,index]
        alpha_zero = np.nanargmin(np.abs(cl_r))
        cl_prime = cl_r[1:]-cl_r[:-1]

        a0 = np.insert(cl_prime,alpha_zero,0)
        # a = a0/np.sqrt(1+(a0/np.pi/ASPECT_RATIO)**2+(a0/np.pi/ASPECT_RATIO))
        a = a0/(1+(a0*180/np.pi/(np.pi*ASPECT_RATIO*efficiency)))
        for alph_forward in range(alpha_zero+1,cl.shape[0]):
            CL[alph_forward,index] = CL[alph_forward-1,index] + a[alph_forward]
        for alph_backward in range(alpha_zero-1,-1,-1):
            CL[alph_backward,index] = CL[alph_backward+1,index] - a[alph_backward]

    CD = cd + CL**2/np.pi/efficiency/ASPECT_RATIO
    CM = cm
    l = AIR_DENSITY * velocity**2 * MEAN_CHORD      * WINGSPAN * CL / 2
    d = AIR_DENSITY * velocity**2 * MEAN_CHORD      * WINGSPAN * CD / 2
    m = AIR_DENSITY * velocity**2 * MEAN_CHORD**2   * WINGSPAN * CM / 2
    return MEAN_CHORD,l

if __name__ == '__main__':
    mc,l = lift(1.4,0.345,0.02)
    velocity = AIR_VISCOSITY * reynolds / AIR_DENSITY / mc
    print(l[np.nanargmin(np.abs(alpha-1)),np.nanargmin(np.abs(velocity-10.5))]/9.8)