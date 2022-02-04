#/*---------------------------------------------------------------------
#This file has been adapted from the implementation
#(available at, Public Domain https://github.com/pq-crystals/kyber)
#of "CRYSTALS - Kyber: a CCA-secure module-lattice-based KEM"
#by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint,
#Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
#----------------------------------------------------------------------*/ 

import numpy as np
import matplotlib.pyplot as plt
from math import sqrt, exp, log, floor
from proba_util import *
from sage.all import *

load("../framework/instance_gen.sage")

# core SVP cost models
cost_model_c = lambda beta: 0.292 * beta
cost_model_q = lambda beta: 0.265 * beta

# estimate cost using leaky-LWE-Estimator https://eprint.iacr.org/2020/292.pdf
def estimate(n, q, m, D_e, D_s):
    A, b, dbdd = initialize_from_LWE_instance(DBDD_predict, n, q, n, D_e, D_s, verbosity=0)
    _ = dbdd.integrate_q_vectors(q, report_every=100)
    beta, delta = dbdd.estimate_attack()
    return beta


# search through parameter sets given D_s, q, k, n
def search_params(D_s, q, k, n, minsec, maxerror):
    logq=int(log(q,2))

    # loop over all p values that are a power of 2 (from 10, others are too low, by experiment)
    for logp in range(10,int(floor(log(q,2)))):
        p=int(2**logp)
        D_e = build_mod_switching_error_law(q, p)

        # security estimate
        beta = estimate(k*n, q, k*n, D_e, D_s)
        sec_c = cost_model_c(beta)

        # stop and break if under minimum security
        if sec_c < minsec:
            break
        
        # failure calculation part 1
        se = law_product(D_s, D_e)
        se2 = iter_law_convolution(se, k*n)
        se2 = convolution_remove_dependency(se2, se2, q, p)

        ### loop over all reconciliation values (note that p - T < q - p so that the security proof works)
        for logT in range(1,2*logp-logq+1):
            T=2**logT

            # failure calculation part 2
            e2 = build_mod_switching_error_law(q, T)
            D = law_convolution(se2, e2)

            prob = tail_probability(D, q/4.)
            if prob!=0:
    	        prob = log(256*prob,2)

            # if too low, search for a bigger T
            if prob > maxerror:
                continue

            ######################################################
            ### We have found good parameters, give a printout ###

            ### bandwidth calculation
            # size of b in bytes
            BWb=logp*k*n/8
            # size of c in bytes
            BWc = n*logT/8

            BWsfull = logq*k*n/8

            print('-- parameters --')
            print('q: ',log(q,2),'p: ',logp,'T: ',logT, 'l: ', k, 'n: ', n, 'D_s: ', D_s)
            
            print('-- bandwidth --')
            print('bandwidth b', BWb, 'bandwidth c', BWc, 'bandwidth total', 2*BWb + BWc + 256/8)
            print('KEM')
            #pk: b, seedA; sk: b, s, (z,seedA,H(pk))
            print('pk: ',BWb + 32, 'send: ', BWb+BWc)
            print('PKE')
            print('pk: ',BWb + 32, 'send: ', BWb+BWc)

            print('-- correctness --')
            print('failure probability: ', float(prob))

            print('-- security --')
            print('quantum: ', cost_model_q(beta), 'classical: ', cost_model_c(beta))

            print('\n\n')

            # succes, we found a b that is secure, and don't need to increase b 
            break


def main():
    # search_params(binomial coins, q, k, n, log2(classical_security), log2(failure probability)
    # script looks for optimal p and t
    # parameter for binomial distribution in Kyber is (binomial coins)/2
    print('-lightsaber-')
    D_s = build_centered_binomial_law(5)
    search_params(D_s, q = 2**13, k = 2, n = 256, minsec = 113, maxerror = -100)

    print('-saber-')
    D_s = build_centered_binomial_law(4)
    search_params(D_s, q = 2**13, k = 3, n = 256, minsec = 177, maxerror = -128)
    
    print('-firesaber-')
    D_s = build_centered_binomial_law(3)
    search_params(D_s, q = 2**13, k = 4, n = 256, minsec = 241, maxerror = -160)




if __name__ == '__main__':
    main()
