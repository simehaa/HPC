import numpy as np
import matplotlib.pyplot as plt


numprocs = np.array([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16])
t1 = np.array([1388,1392,1390,1389,1383])
t2 = np.array([723,723,718,718,720])
t3 = np.array([620,612,610,613,613])
t4 = np.array([607,605,606,606,607])
t5 = np.array([688,683,687,644,690])
t6 = np.array([643,636,635,636,637])
t7 = np.array([630,630,628,630,627])
t8 = np.array([648,633,635,635,635])
t9 = np.array([729,730,723,755,722])
t10 = np.array([722,719,715,747,715])
t11 = np.array([731,707,685,720,711])
t12 = np.array([690,713,703,697,696])
t13 = np.array([710,745,688,713,729])
t14 = np.array([704,674,678,672,663])
t15 = np.array([691,827,854,755,670])
t16 = np.array([703,684,719,664,680])

t = np.array([t1.mean(),
    t2.mean(),
    t3.mean(),
    t4.mean(),
    t5.mean(),
    t6.mean(),
    t7.mean(),
    t8.mean(),
    t9.mean(),
    t10.mean(),
    t11.mean(),
    t12.mean(),
    t13.mean(),
    t14.mean(),
    t15.mean(),
    t16.mean()])

dt = np.array([t1.std(),
    t2.std(),
    t3.std(),
    t4.std(),
    t5.std(),
    t6.std(),
    t7.std(),
    t8.std(),
    t9.std(),
    t10.std(),
    t11.std(),
    t12.std(),
    t13.std(),
    t14.std(),
    t15.std(),
    t16.std()])

plt.errorbar(numprocs,t,dt,None,'bo-',barsabove=True,label="Average of 5 runs,\nwith uncertainty")
plt.title("Timing of denoising algorithm with MPI (100 iterations)")
plt.xlabel("No. of processors")
plt.ylabel("Time [ms]")
plt.legend()
plt.axis([0.5,16.5,0,1500])
plt.grid()
plt.show()

print(t1.mean()/t4.mean())
